#ifndef MYBALL_H
#define MYBALL_H

#include <QLabel>
#include <QCoreApplication>
#include <QElapsedTimer>

class ball {
public:
    ball(double x, double y, double gx,
         double gy, QWidget* pthis):
        posx(x), posy(y),
        groundx(gx), groundy(gy)
    {
        myball = createBall(pthis);
    }

    QLabel *createBall(QWidget* pthis) {
        QLabel *tempball = new QLabel(pthis);

        tempball->setGeometry(posx, posy, width, height);
        tempball->setObjectName(QString::fromUtf8("ball"));
        tempball->setPixmap(QPixmap(
            "C:/Users/Tianyun Zhang/Documents/Qt/Simple2DEngine/Resources/ball.png"));
        tempball->setAlignment(Qt::AlignCenter);

        tempball->show();

        return tempball;
    }

    void fall() {
        speedy += 0.020;
        posx += speedx;
        posy += speedy;

        myball->setGeometry((int)posx, (int)posy,
                            width, height);
    }

    void groundDetectRespond() {
        if (posy > groundy-40) {
            posy = groundy-40;
            speedy *= 0.6;
            if(speedy <= 0.6){
                speedy = 0;
            }
            speedy = 0 - speedy;
        }
    }

    bool collisionDetectRespond(ball A, ball B) {

    }

    void destoryLabel() {
        myball->hide();
        delete myball;
    }

    ~ball() {
        //bug will appear here
    }

//private:
    QLabel *myball;
    double posx = 0, posy = 0;
    int width = 40, height = 40;
    int groundx = 0, groundy = 0;
    double speedx = 0, speedy = 0;
};


#endif // MYBALL_H
