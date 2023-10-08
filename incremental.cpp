#include "incremental.hpp"
#include <QPainter>
#include <QPolygonF>

Incremental::Incremental(QWidget *parent)
    : QWidget(parent)
{
    points.push_back(QPoint(40,40));
    points.push_back(QPoint(20,80));
    points.push_back(QPoint(60,80));
    points.push_back(QPoint(60,60));
    points.push_back(QPoint(80,140));
    points.push_back(QPoint(100,80));
    points.push_back(QPoint(120,40));
    points.push_back(QPoint(160,140));
}

void Incremental::paintEvent(QPaintEvent *)
{
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::red,4));
    painter->drawPoints(points.data(),static_cast<int>(points.size()));

    sortPoints(points.begin(),points.end());
    auto convexHull = createConvexHull();

    painter->setPen(QPen(Qt::green,2));
    painter->drawPolyline(convexHull.data(),static_cast<int>(convexHull.size()));

    painter->end();
}

PointVec Incremental::createConvexHull()
{
    PointVec hullPoints(points.begin(),points.begin()+3);
    hullPoints.push_back(points[0]);

    for(qsizetype i = 3; i< points.size() ; ++i){
            bool lastRight = false;
            PointIter p1 = points.begin();
            PointIter p2 = points.begin();
            for(auto it = hullPoints.begin(); it != std::prev(hullPoints.end()) ; ++it){
                if(isRight(*it,*std::next(it),points[i])){
                    if(!lastRight){
                        p1 = it;
                        lastRight = true;
                    }
                    p2 = std::next(it);
                }else{
                    if(lastRight){
                        p2 = it;
                        break;
                    }
                }
            }
            PointIter newIt = hullPoints.erase(std::next(p1),p2);
            hullPoints.insert(newIt,points[i]);
    }
    return hullPoints;
}

void Incremental::sortPoints(PointIter begin, PointIter end)
{
    std::sort(begin,end,[](QPoint a , QPoint b){
            return a.x() < b.x();
    });
}

bool Incremental::isLeft(QPoint p1, QPoint p2, QPoint p)
{
    QPoint vectorP1_P2 (p2.x() - p1.x() , p2.y() - p1.y());
    QPoint vectorP1_P (p.x() - p1.x() , p.y() - p1.y());

    auto alpha = vectorP1_P2.x() * vectorP1_P.y() - vectorP1_P.x() * vectorP1_P2.y();
    return alpha > 0;
}

bool Incremental::isRight(QPoint p1, QPoint p2, QPoint p){
    return !isLeft(p1,p2,p);
}

Incremental::~Incremental()
{
}

