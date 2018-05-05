#include "mainwindow.h"
#include <QApplication>
#include <bezierqgraphicsview.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    BezierQGraphicsView* view = new BezierQGraphicsView;
    w.setGeometry(100, 100, 800, 800);
    w.setCentralWidget(view);
    w.show();

     int ret = a.exec();
     return ret;
}
