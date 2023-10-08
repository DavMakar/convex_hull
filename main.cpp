#include "incremental.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Incremental w;
    w.show();
    return a.exec();
}
