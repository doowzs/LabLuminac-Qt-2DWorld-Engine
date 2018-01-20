#include "simuworld.h"
#include "ui_simuworld.h"

SimuWorld::SimuWorld(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimuWorld)
{
    ui->setupUi(this);
}

SimuWorld::~SimuWorld()
{
    delete ui;
}
