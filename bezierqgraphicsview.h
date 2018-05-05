#ifndef BEZIERQGRAPHICSVIEW_H
#define BEZIERQGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QList>

class MyPoint : public QGraphicsEllipseItem
{
public:
        explicit MyPoint(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = 0);
};


class BezierQGraphicsView : public QGraphicsView
{
public:
    BezierQGraphicsView(QWidget *parent = 0);
    ~BezierQGraphicsView();
    void drawBezier();

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QGraphicsScene* scene;
    QPointF pt;
    QList<MyPoint*> pointlist;
    QList<QGraphicsLineItem*> linelist;
    bool drag;//drag'n'drop функционал
    MyPoint* draggedpoint;
};




#endif // BEZIERQGRAPHICSVIEW_H
