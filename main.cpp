#include "qmlbridge.h"
#include "solver.h"
#include <QCommandLineParser>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

QString parseArguments(QCoreApplication &app)
{
    QCommandLineParser parser;
    parser.addPositionalArgument("input", "Input graph description", "/path/to/file");
    parser.addHelpOption();
    parser.process(app);
    auto list = parser.positionalArguments();
    if (list.isEmpty()) {
        throw std::runtime_error("No argument");
    }
    return list[0];
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QString input;
    try {
        input = parseArguments(app);
    } catch (const std::runtime_error &e) {
        qCritical() << e.what();
        return 1;
    }
    QQmlApplicationEngine engine;
    QmlBridge bridge(&engine);
    auto context = engine.rootContext();
    context->setContextProperty("qmlBridge", &bridge);

    QThread t;
    Solver s;
    s.moveToThread(&t);
    QObject::connect(&s, &Solver::newVertex, &bridge, &QmlBridge::newVertex);
    QObject::connect(&s, &Solver::newEdge, &bridge, &QmlBridge::newEdge);
    QObject::connect(&s, &Solver::edgeFlowChanged, &bridge, &QmlBridge::edgeFlowChanged);
    QObject::connect(&s, &Solver::flowFound, &bridge, &QmlBridge::flowFound);
    QObject::connect(&bridge,
                     &QmlBridge::delayChanged,
                     &s,
                     &Solver::delayChanged,
                     Qt::DirectConnection);
    QObject::connect(&s, &Solver::currentVertexChanged, &bridge, &QmlBridge::currentVertexChanged);
    QObject::connect(&s, &Solver::currentEdgeChanged, &bridge, &QmlBridge::currentEdgeChanged);
    QObject::connect(&bridge, &QmlBridge::nextIteration, &s, &Solver::nextIteration);
    QObject::connect(&bridge, &QmlBridge::algoChanged, &s, &Solver::setAlgorithm);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    t.start();
    s.initGraph(input);
    int res = app.exec();
    t.quit();
    t.wait();
    return res;
}
