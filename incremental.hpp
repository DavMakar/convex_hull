#ifndef INCREMENTAL_HPP
#define INCREMENTAL_HPP

#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QPaintEvent>

using PointVec = QVector<QPoint>;
using PointIter = PointVec::iterator;

class Incremental{
public:
    Incremental();
    ~Incremental();
public:
    PointVec createConvexHull();
    PointVec getAllPoints();
    void addPoint(QPoint p);
    void sortPoints(PointIter begin , PointIter end);
private:
    void makeFirstTriangel(PointVec& hullPoints);
    bool isLeft(QPoint p1 , QPoint p2 ,QPoint p);
    bool isRight(QPoint p1 , QPoint p2 ,QPoint p);
private:
    PointVec points;
};
#endif // INCREMENTAL_HPP
