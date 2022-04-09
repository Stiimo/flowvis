#pragma once

#include <QObject>

class Edge : public QObject
{
    Q_OBJECT
public:
    Edge(int id, int c, QObject* parent = nullptr);

private:
    int mId;
    int mC;
    int mF{0};
};
