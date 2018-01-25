#include "simuworld.h"
#include "ui_simuworld.h"
#include <vector>
#include <exception>
#include <QTime>

std::vector<ball*> ballVector;
bool superFlag = true;

SimuWorld::SimuWorld(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimuWorld)
{
    ui->setupUi(this);
    //ui->ballTrigger->setVisible(false);
    connect(ui->ballTrigger, SIGNAL(clicked(bool)), this, SLOT(CreateBall()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(StopAll()));
    connect(ui->continueButton, SIGNAL(clicked(bool)), this, SLOT(ContinueAll()));
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(ClearAll()));
}

SimuWorld::~SimuWorld()
{
    delete ui;
}

void SimuWorld::BallMoving() {
    QTime t;
    t.start();

    try{
        while(superFlag){
            ui->label->setText(QString::number(ballVector.size()));
            if(t.elapsed()%20==0){
                for(int i = 0; i<ballVector.size(); i++){
                    ballVector[i]->fall();
                    ballVector[i]->go();
                    ballVector[i]->groundDetectRespond();
                    for(int j = i+1; j<ballVector.size(); j++){
                        ballVector[i]->collisionDetectRespond(ballVector[j]);
                    }
                }
            }
            QCoreApplication::processEvents();
        }
    }catch (std::exception e){
        ui->label->setText(e.what());
        ClearAll();
    }
}

void SimuWorld::CreateBall() {
    superFlag = true;
    ui->stopButton->setEnabled(true);
    ui->continueButton->setEnabled(false);

    QPoint mousePos;
    mousePos = QWidget::mapFromGlobal(QCursor::pos());

    ball *newball = new ball(mousePos.x(), mousePos.y(),
                           ui->ballTrigger->x(),
                           ui->ballTrigger->x()+ui->ballTrigger->width(),
                           ui->ballTrigger->y(),
                           ui->ballTrigger->y()+ui->ballTrigger->height(),
                           this);
    ballVector.push_back(newball);

    BallMoving();
}

void SimuWorld::StopAll() {
    superFlag = false;
    ui->stopButton->setEnabled(false);
    ui->continueButton->setEnabled(true);
}

void SimuWorld::ContinueAll() {
    superFlag = true;
    ui->stopButton->setEnabled(true);
    ui->continueButton->setEnabled(false);
    BallMoving();
}

void SimuWorld::ClearAll() {
    ball *tempball = NULL;
    for(int i = 0; i<ballVector.size(); i++){
        delete ballVector[i];
    }
    ballVector.clear();
    ui->label->setText(QString::number(0));
    ui->stopButton->setEnabled(true);
    ui->continueButton->setEnabled(false);
}
