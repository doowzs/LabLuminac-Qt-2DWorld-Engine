#ifndef SIMUWORLD_H
#define SIMUWORLD_H

#include <QMainWindow>

namespace Ui {
class SimuWorld;
}

class SimuWorld : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimuWorld(QWidget *parent = 0);
    ~SimuWorld();

private:
    Ui::SimuWorld *ui;
};

#endif // SIMUWORLD_H
