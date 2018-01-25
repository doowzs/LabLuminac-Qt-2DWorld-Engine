#include "simuworld.h"
#include "ui_simuworld.h"
#include <vector>
#include <exception>
#include <QTimer>
#include <QTime>

std::vector<ball*> ballVector;
int fps = 0;
bool superFlag = true;

QTimer *timer1, *timer2;
int timer1Interval = 15;

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

    timer1 = new QTimer(this);
    timer1->start(timer1Interval);
    connect(timer1, SIGNAL(timeout()), this, SLOT(BallMoving()));

    timer2 = new QTimer(this);
    timer2->start(1000);
    connect(timer2, SIGNAL(timeout()), this, SLOT(ShowFPS()));
}

SimuWorld::~SimuWorld()
{
    delete ui;
}

void SimuWorld::BallMoving() {
    try{
        for(int i = 0; i<ballVector.size(); i++){
            ballVector[i]->fall();
            ballVector[i]->go();
            ballVector[i]->groundDetectRespond();
            for(int j = i+1; j<ballVector.size(); j++){
                ballVector[i]->collisionDetectRespond(ballVector[j]);
            }
        }

        fps++;
        ui->lcdNumber->display((int)ballVector.size());
    }catch (std::exception e){
        ui->label->setText(e.what());
        ClearAll();
    }
}

void SimuWorld::CreateBall() {
    //superFlag = true;
    timer1->start();
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

    //if(isFirstInit)BallMoving();
}

void SimuWorld::StopAll() {
    superFlag = false;
    timer1->stop();
    ui->stopButton->setEnabled(false);
    ui->continueButton->setEnabled(true);
}

void SimuWorld::ContinueAll() {
    superFlag = true;
    timer1->start();
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
    //ui->label->setText(QString::number(0));
    ui->stopButton->setEnabled(true);
    ui->continueButton->setEnabled(false);
}

void SimuWorld::ShowFPS() {
    if(fps>80) {
        timer1Interval++;
        timer1->stop();
        if(superFlag)timer1->start(timer1Interval);
    } else {
        if(fps>0 && timer1Interval>1)timer1Interval--;
        timer1->stop();
        if(superFlag)timer1->start(timer1Interval);
    }
    ui->label->setText("FPS: "+QString::number(fps));
    fps = 0;
}
