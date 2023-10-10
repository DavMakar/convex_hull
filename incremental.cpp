#include "incremental.hpp"

Incremental::Incremental()
{
    points.push_back(QPoint(50,10));
    points.push_back(QPoint(20,15));
    points.push_back(QPoint(15,40));
}

PointVec Incremental::createConvexHull()
{
    sortPoints(points.begin(),points.end());

    PointVec hullPoints;
    makeFirstTriangel(hullPoints);

    for(qsizetype i = 3; i< points.size() ; ++i){
        bool lastRight = false;
        PointIter p1 = hullPoints.begin();
        PointIter p2 = hullPoints.begin();
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

PointVec Incremental::getAllPoints()
{
    return points;
}

void Incremental::addPoint(QPoint p)
{
    points.push_back(p);
}

void Incremental::sortPoints(PointIter begin, PointIter end)
{
    std::sort(begin,end,[](QPoint a , QPoint b){
            return a.x() < b.x();
    });
}

void Incremental::makeFirstTriangel(PointVec &hullPoints)
{
    hullPoints.push_back(points[0]);
    if(points[1].y() > points[0].y()){
        hullPoints.push_back(points[2]);
        hullPoints.push_back(points[1]);

    }else{
        hullPoints.push_back(points[1]);
        hullPoints.push_back(points[2]);
    }
    hullPoints.push_back(points[0]);
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

