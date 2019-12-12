#ifndef BBTEXT_H
#define BBTEXT_H

#include <QGraphicsTextItem>
#include "BbScene.h"

class BbText : public QGraphicsTextItem
{
public:
    explicit BbText(BbScene* scene, QGraphicsItem *parent = 0);
    ~BbText();

    virtual void startDraw(QPointF& point);
    virtual void drawing(QPointF& point);
    virtual void finishDraw(QPointF& point);

    void startEdit();
    void stopEdit();

protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    BbScene* m_scene;

    QString m_textContent;
    QColor  m_textColor = Qt::red;
    int     m_fontPixelSize = 48;
    bool    m_isEditing = false;
};

#endif // BBTEXT_H
