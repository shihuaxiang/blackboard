#ifndef BBVIEW_H
#define BBVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsRectItem>

#include "blackboardcore_global.h"

class BbScene;
class BbLine;

class BLACKBOARDCORESHARED_EXPORT BbView : public QGraphicsView
{
    Q_OBJECT
public:
	explicit BbView(QWidget *parent = 0, double w = 1280, double h = 720, int pageNum = 1);
    ~BbView();
	bool isFixedRatio();
	void setFixedRatio(bool fixedRatio);

    enum OperateMode   //模式
    {
        DrawMode,     //绘制模式
        SelectMode,   //选择模式
        ViewMode,	  //浏览模式
        PointMode
    };

    BbScene* getScene();
    BbView::OperateMode getMode();
    void setMode(BbView::OperateMode operateMode);
	void print();

	void turnNextPage();
	void turnPrevPage();
	void setViewRect();

signals:

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
	virtual void drawBackground(QPainter* painter, const QRectF& rect);

private:
    BbView::OperateMode mode;

    BbLine* line;

	int		_pageIndex;
	int		_pageNum;
	bool	_fixedRatio;
};

#endif // BBVIEW_H
