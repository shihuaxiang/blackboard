#ifndef BBSCENE_H
#define BBSCENE_H

#include <QGraphicsScene>

#include "blackboardcore_global.h"

class BLACKBOARDCORESHARED_EXPORT BbScene : public QGraphicsScene
{
    Q_OBJECT
public:
	explicit BbScene(double w = 1280, double h = 720, int pageNum = 1, QObject *parent = 0);
    ~BbScene();

	double getPageWidth();
	double getPageHeight();
	QRectF getPageRect(int pageIndex);

	void testAddRect();
	void testAddText();
	void testAddPixmap();

signals:

public slots:

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual void drawBackground(QPainter* painter, const QRectF& rect);

private:
	int _width;
	int _height;

};

#endif // BBSCENE_H
