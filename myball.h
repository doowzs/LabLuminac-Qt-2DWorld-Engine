#ifndef MYBALL_H
#define MYBALL_H

#include <QLabel>
#include <QCoreApplication>
#include <QElapsedTimer>
#include <cmath>

class ball {
public:
    ball(double x, double y, double gl,
         double gr, double gu, double gd, QWidget* pthis):
        posx(x), posy(y),
        gl(gl), gr(gr), gu(gu), gd(gd)
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
        speedy += 0.030;
    }

    void go() {
        posx += speedx;
        posy += speedy;

        myball->setGeometry((int)posx, (int)posy,
                            width, height);
    }

    void groundDetectRespond() {
        //左侧墙壁
        if (posx < gl) {
            posx = gl;
            speedx = 0 - speedx;
        }
        //右侧墙壁
        if (posx > gr-40) {
            posx = gr-40;
            speedx = 0 - speedx;
        }
        //地面
        if (posy > gd-40) {
            posy = gd-40;
            speedy *= 1;
            speedx *= 1;
            if(speedy <= 0.6){
                speedy = 0;
            }
            //if(speedx <= 0.05){
            //    speedx = 0;
            //}
            speedy = 0 - speedy;
        }
    }

    void collisionDetectRespond(ball* b) {
        double disx = posx - b->posx;
        double disy = posy - b->posy;
        double dis = sqrt(pow(disx,2) + pow(disy,2));

        if (dis < 40) {
            double e = 1 * (pow(speedx,2) + pow(speedy,2));
            double eb = 1 * (pow(b->speedx,2) + pow(b->speedy,2));
            if(!e)e+=0.1;if(!eb)eb+=0.1;
            speedx = sqrt(eb) * (disx / dis);
            speedy = sqrt(eb) * (disy / dis);
            b->speedx = - sqrt(e) * (disx / dis);
            b->speedy = - sqrt(e) * (disy / dis);
        }
    }

    ~ball() {
        delete myball;
    }

private:
    QLabel *myball;
    double posx = 0, posy = 0;
    int width = 40, height = 40;
    int gl = 0, gr = 0, gu = 0, gd = 0;
    double speedx = 0, speedy = 0;
};


#endif // MYBALL_H
