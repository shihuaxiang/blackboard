#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QActionGroup>
#include "../blackboardCore/BbView.h"
#include "../blackboardCore/BbScene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActionGroup();
	void createTestAction();

private slots:
    void on_actionPen_triggered();
    void on_actionArrow_triggered();
    void on_actionPoint_triggered();

    void slotSize1280X720();
	void slotSize800X600();
	void slotSize600X600();
	void slotZoomin();
	void slotZoomout();
    void slotPrint();
	void slotAdd();
	void slotTest(int index);

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    BbView* bbView;

    QAction *actionPen;
    QAction *actionArrow;
    QAction *actionPoint;
    QActionGroup* actionGroup;

	QToolBar *mainToolBar;
	QStatusBar *statusBar;
};

#endif // MAINWINDOW_H
