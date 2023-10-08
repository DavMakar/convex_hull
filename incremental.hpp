#ifndef INCREMENTAL_HPP
#define INCREMENTAL_HPP

#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QPaintEvent>

using PointVec = QVector<QPoint>;
using PointIter = PointVec::iterator;

class Incremental : public QWidget
{
    Q_OBJECT

public:
    Incremental(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    ~Incremental();

private:
    PointVec createConvexHull();
    void sortPoints(PointIter begin, PointIter end);
    bool isLeft(QPoint p1 , QPoint p2 ,QPoint p);
    bool isRight(QPoint p1 , QPoint p2 ,QPoint p);
private:
    PointVec points;
};
#endif // INCREMENTAL_HPP
