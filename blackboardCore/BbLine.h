#ifndef BBLINE_H
#define BBLINE_H

#include <QGraphicsPathItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "BbScene.h"

class BbLine : public QGraphicsPathItem
{
public:
    explicit BbLine(BbScene* scene, QGraphicsItem *parent = 0);
    ~BbLine();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void startDraw(QPointF& point);
    virtual void drawing(QPointF& point);
    virtual void finishDraw(QPointF& point);

private:
    BbScene* _scene;

    int     _lineWidth;
    QColor  _lineColor;

    QVector<QPointF> m_points;

    bool m_finished = false;
    QImage m_image;
 
    // 0 -- lineto
    // 1 -- quadTo
    int m_drawMode = 0;
};

#endif // BBLINE_H
