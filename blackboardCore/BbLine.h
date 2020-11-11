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

    virtual void startDraw(QPointF& point);
    virtual void drawing(QPointF& point);
    virtual void finishDraw(QPointF& point);

private:
    BbScene* _scene;

    int     _lineWidth;
    QColor  _lineColor;

    QVector<QPointF> m_points;

    bool m_dirty = false;
    bool m_finished = false;
    QImage m_image;
};

#endif // BBLINE_H
