#include "convexhull.hpp"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConvexHull w;
    w.show();
    return a.exec();
}
