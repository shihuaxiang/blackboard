#ifndef BBLINE_H
#define BBLINE_H

#include <QGraphicsPathItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "BbScene.h"
#include "BbView.h"

class BbLine : public QGraphicsPathItem
{
public:
    explicit BbLine(BbScene* scene, BbView* bbView, QGraphicsItem *parent = 0);
    ~BbLine();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void startDraw(QPointF& point);
    virtual void drawing(QPointF& point);
    virtual void finishDraw(QPointF& point);

    int getCurveMode();

private:
    BbScene* _scene;
    BbView* _view;

    int     _lineWidth;
    QColor  _lineColor;

    QVector<QPointF> m_points;

    bool m_finished = false;
    QImage m_image;
};

#endif // BBLINE_H
