#ifndef SIMUWORLD_H
#define SIMUWORLD_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QVector>
#include "myball.h"

namespace Ui {
class SimuWorld;
}

class SimuWorld : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimuWorld(QWidget *parent = 0);
    ~SimuWorld();

public slots:
    void CreateBall();
    void StopAll();
    void ContinueAll();
    void ClearAll();

private:
    QVector<int> vector;
    Ui::SimuWorld *ui;

//protected:
//    void MouseMoveEvent(QMouseEvent *event);
};

#endif // SIMUWORLD_H
