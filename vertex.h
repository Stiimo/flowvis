#pragma once

#include <QMap>
#include <QObject>

class Edge;

class Vertex : public QObject
{
    Q_OBJECT    
public:
    explicit Vertex(QObject *parent = nullptr);
};
