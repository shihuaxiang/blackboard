#ifndef BBSCENE_H
#define BBSCENE_H

#include <QObject>

class BbScene : public QObject
{
    Q_OBJECT
public:
    explicit BbScene(QObject *parent = 0);
    ~BbScene();

signals:

public slots:
};

#endif // BBSCENE_H
