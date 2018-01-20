#include "simuworld.h"
#include "ui_simuworld.h"

SimuWorld::SimuWorld(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimuWorld)
{
    ui->setupUi(this);
    //ui->ballTrigger->setVisible(false);
    connect(ui->ballTrigger, SIGNAL(clicked(bool)), this, SLOT(CreateBall()));
}

SimuWorld::~SimuWorld()
{
    delete ui;
}

void SimuWorld::CreateBall() {
    QPoint mousePos;
    mousePos = QCursor::pos();
    ui->label->setText("(" + QString::number(mousePos.x()) + "," + QString::number(mousePos.y()) + ")");
}
