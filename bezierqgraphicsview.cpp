#include "bezierqgraphicsview.h"
#include <QtMath>

qint64 factorial(qint64 n)
{
    qint64 ret = 1;
    for(qint64 i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}
qreal bernstein(qint64 i, qint64 n, qreal t)
{
    return (factorial(n)/(factorial(i)*factorial(n-i))) * qPow(t, i) * qPow(1-t, n-i);
}

void BezierQGraphicsView::drawBezier()
{
    while(!linelist.isEmpty())
    {
        scene->removeItem(linelist.first());
        delete linelist.takeFirst();
    }
    if (pointlist.size() < 3) return;
    QPointF bufpoint1(pointlist.first()->x(), pointlist.first()->y()), bufpoint2;
    for(qreal t = 0; t <= 1; t+= 0.01){
        bufpoint2 = QPointF(0,0);
        for(int i = 0; i < pointlist.size(); ++i)
        {
            QPointF currentpoint(pointlist.at(i)->x(), pointlist.at(i)->y());
            bufpoint2 += bernstein(i, pointlist.size() - 1, t)*currentpoint;
        }
        QGraphicsLineItem* line = scene->addLine(bufpoint1.x(), bufpoint1.y(), bufpoint2.x(), bufpoint2.y());
        line->setPen(QPen(Qt::blue,3));
        linelist.append(line);
        bufpoint1 = bufpoint2;
    }
}

BezierQGraphicsView::BezierQGraphicsView(QWidget *parent) :
QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setSceneRect(60, 60, 400, 400);
    this->setScene(scene);
    drag = false;

}

BezierQGraphicsView::~BezierQGraphicsView()
{ }

void BezierQGraphicsView::mousePressEvent(QMouseEvent* event)
{//эта функция отвечает за добавление точек
    double rad = 1;
    pt = mapToScene(event->pos());
    if (!itemAt(event->pos())){
        MyPoint *point = new MyPoint(pt.x(), pt.y(), rad*14.0, rad*14.0);
        pointlist.append(point);
        scene->addItem(point);
    }
    else {
        for (int i = 0; i < pointlist.size(); ++i){//ищем точку в которую попали мышкой
            QPointF distance(pointlist.at(i)->pos() - pt);
            if (distance.x()*distance.x() + distance.y()*distance.y() < 144){
                if (event->button() == Qt::RightButton){
                    scene->removeItem(pointlist.at(i));
                    delete pointlist.takeAt(i);
                    return;
                }
                drag = true;
                draggedpoint = pointlist.at(i);
                break;
            }
        }
    }
}

void BezierQGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (drag == false) return;
    draggedpoint->setPos(mapToScene(event->pos()));
    drawBezier();

}

void BezierQGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    drawBezier();
    drag = false;
}

MyPoint::MyPoint(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) :
    QGraphicsEllipseItem(-5,-5,width, height, parent)
{
    setPos(x, y);
    setBrush(Qt::cyan);
}
