#include "simuworld.h"
#include "ui_simuworld.h"
#include <vector>

std::vector<ball> ballVector;
bool superFlag = true;

SimuWorld::SimuWorld(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimuWorld)
{
    ui->setupUi(this);
    //ui->ballTrigger->setVisible(false);
    connect(ui->ballTrigger, SIGNAL(clicked(bool)), this, SLOT(CreateBall()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(StopAll()));
}

SimuWorld::~SimuWorld()
{
    delete ui;
}

void SimuWorld::CreateBall() {
    superFlag = true;

    QPoint mousePos;
    mousePos = QWidget::mapFromGlobal(QCursor::pos());
    ui->label->setText("(" + QString::number(mousePos.x()) + "," + QString::number(mousePos.y()) + ")");

    ball *newball = new ball(mousePos.x(), mousePos.y(),
                           ui->ballTrigger->x(),
                           ui->ballTrigger->y()+ui->ballTrigger->height(),
                           this);
    ballVector.push_back(*newball);

    QElapsedTimer t;
    t.start();

    while(superFlag){
        if(t.elapsed()%20==0){
            for(int i = 0; i<ballVector.size(); i++){
                ballVector[i].fall();
                ballVector[i].groundDetectRespond();
                //ui->label->setText(QString::number(ballVector[i].posy)+" , "
                //+QString::number(ballVector[i].speedy));
            }
        }
        QCoreApplication::processEvents();
    }
}

void SimuWorld::StopAll() {
    superFlag = false;
    //while(!ballVector.empty()){
        //ball *tempball = &ballVector.back();
        //ballVector.pop_back();
        //delete tempball;
    //}
}
