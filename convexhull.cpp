#include "convexhull.hpp"
#include <QPainter>
#include <QPen>
#include <QPushButton>

ConvexHull::ConvexHull(QWidget *parent)
    : QWidget{parent}
{

}

void ConvexHull::paintEvent(QPaintEvent *)
{
    drawPoints();
    drawConvexHull();
}

void ConvexHull::mousePressEvent(QMouseEvent* ev)
{
    QPoint clickPos = ev->pos();
    clickPos.setY(height() - clickPos.y());
    incremental.addPoint(clickPos);
    update();
}

void ConvexHull::drawPoints(){
    auto points = incremental.getAllPoints();

    QPainter* painter = new QPainter(this);

    painter->translate(0,height());
    painter->scale(1.0, -1.0);
    painter->setPen(QPen(Qt::green, 5));
    painter->drawPoints(points.data(),static_cast<int>(points.size()));
    painter->end();
}

void ConvexHull::drawConvexHull()
{
    auto convexHull = incremental.createConvexHull();
    //incremental.sortPoints(convexHull.begin(),convexHull.end());

    QPainter* painter = new QPainter(this);
    painter->translate(0,height());
    painter->scale(1.0, -1.0);
    painter->setPen(QPen(Qt::red,2));
    painter->drawPolyline(convexHull.data(), static_cast<int>(convexHull.size()));
    painter->end();
}

