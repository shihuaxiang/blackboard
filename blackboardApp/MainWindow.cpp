#include <QActionGroup>
#include <QDebug>
#include <QSignalMapper>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    createActionGroup();
    createTestAction();

    //this->setGeometry(100,100,1282,778);
	this->setGeometry(100, 100, 300, 200);

    bbView = new BbView(this,1280,720,3);
    this->setCentralWidget(bbView);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::createTestAction()
{
    {
        QAction* tempAction = new QAction("Add", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotAdd()));
    }

    {
        QAction* tempAction = new QAction("Print", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotPrint()));
    }

    {
        QAction* tempAction = new QAction("1280", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotSize1280X720()));
    }

    {
        QAction* tempAction = new QAction("800", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotSize800X600()));
    }

    {
        QAction* tempAction = new QAction("600", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotSize600X600()));
    }

    {
        QAction* tempAction = new QAction("zoomin", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotZoomin()));
    }

    {
        QAction* tempAction = new QAction("zoomout", this);
        mainToolBar->addAction(tempAction);
        connect(tempAction, SIGNAL(triggered()), this, SLOT(slotZoomout()));
    }

    //
    QActionGroup * testActionGroup = new QActionGroup(this);

    for (int i = 0; i < 6; i++)
    {
        QString text;
        if (i < 3)
            text = QString("test%1").arg(i);
        else if (i < 6)
            text = QString("mode%1").arg(i-3);

        QAction* actionTest = new QAction(this);
        actionTest->setCheckable(true);
        actionTest->setText(text);
        mainToolBar->addAction(actionTest);

        testActionGroup->addAction(actionTest);

        connect(actionTest, &QAction::triggered, [this, i](){
            slotTest(i);
        });
    }
}

void MainWindow::createActionGroup()
{
    {
        actionArrow = new QAction(this);
        actionArrow->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionArrow->setIcon(icon);

        mainToolBar->addAction(actionArrow);
        connect(actionArrow, SIGNAL(triggered()), this, SLOT(on_actionArrow_triggered()));
    }

    {
        actionPencil = new QAction(this);
        actionPencil->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPencil->setIcon(icon);

        mainToolBar->addAction(actionPencil);
        connect(actionPencil, SIGNAL(triggered()), this, SLOT(on_actionPencil_triggered()));
    }

    {
        actionText = new QAction(this);
        actionText->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/text.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionText->setIcon(icon);

        mainToolBar->addAction(actionText);
        connect(actionText, SIGNAL(triggered()), this, SLOT(on_actionText_triggered()));
    }

    {
        actionPoint = new QAction(this);
        actionPoint->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/point.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPoint->setIcon(icon);

        mainToolBar->addAction(actionPoint);
        connect(actionPoint, SIGNAL(triggered()), this, SLOT(on_actionPoint_triggered()));
    }

    actionGroup = new QActionGroup(this);
    actionGroup->addAction(actionArrow);
    actionGroup->addAction(actionPencil);
    actionGroup->addAction(actionText);
    actionGroup->addAction(actionPoint);
    actionArrow->setChecked(true);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "MainWindow Size:" << this->size();

    QMainWindow::resizeEvent(event);
}

void MainWindow::on_actionArrow_triggered()
{
    if(actionArrow->isChecked())
        bbView->setMode(BbView::OperateMode::SelectMode);
}

void MainWindow::on_actionPencil_triggered()
{
    if(actionPencil->isChecked())
        bbView->setMode(BbView::OperateMode::DrawMode);
}

void MainWindow::on_actionText_triggered()
{
    if(actionText->isChecked())
        bbView->setMode(BbView::OperateMode::TextMode);
}

void MainWindow::on_actionPoint_triggered()
{
    if (actionPoint->isChecked())
        bbView->setMode(BbView::OperateMode::PointMode);
}

void MainWindow::slotSize1280X720()
{
    QRect theRect = bbView->contentsRect();

    int dw = 1280 - theRect.width();
    int dh = 720 - theRect.height();

    this->resize(width()+dw,height()+dh);
}

void MainWindow::slotSize800X600()
{
    QRect theRect = bbView->contentsRect();

    int dw = 800 - theRect.width();
    int dh = 600 - theRect.height();

    this->resize(width() + dw, height() + dh);
}

void MainWindow::slotSize600X600()
{
    QRect theRect = bbView->contentsRect();

    int dw = 600 - theRect.width();
    int dh = 600 - theRect.height();

    this->resize(width() + dw, height() + dh);
}

void MainWindow::slotZoomin()
{
    bbView->scale(2, 2);
}

void MainWindow::slotZoomout()
{
    bbView->scale(0.5, 0.5);
}

void MainWindow::slotPrint()
{
    //qDebug() << "MainWindow rect:" << this->rect();
    //qDebug() << "bbView rect:" << bbView->rect();
    //qDebug() << "bbView contentsRect:" << bbView->contentsRect();

    bbView->print();
}

void MainWindow::slotAdd()
{
    bbView->getScene()->testAddRect();
    bbView->getScene()->testAddText();
    bbView->getScene()->testAddPixmap();
}

void MainWindow::slotTest(int index)
{
    qDebug() << index;

	switch (index)
	{
	case 0:
		bbView->turnNextPage();
		break;

	case 1:
		bbView->turnPrevPage();
		break;

	case 2:
		bbView->replay();
		break;

    case 3:
    case 4:
    case 5:
        bbView->changeCurveMode(index - 3);
        break;

	default:
		break;
	}
}
