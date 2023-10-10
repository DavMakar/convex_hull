#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP

#include <QWidget>
#include "incremental.hpp"

class ConvexHull : public QWidget
{
    Q_OBJECT
public:
    explicit ConvexHull(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent*) override;

    void drawConvexHull();
    void drawPoints();
private:
    Incremental incremental;
};

#endif // CONVEXHULL_HPP
