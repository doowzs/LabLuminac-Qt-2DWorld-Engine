#ifndef MYBALL_H
#define MYBALL_H

#include <QLabel>
#include <QCoreApplication>
#include <QElapsedTimer>
#include <cmath>
#include <ctime>
#include <random>
#include <QDir>
#include <QDebug>

class ball {
public:
    ball(int count, double x, double y, double gl,
         double gr, double gu, double gd, QWidget* pthis):
        posx(x), posy(y),
        gl(gl), gr(gr), gu(gu), gd(gd)
    {
        myball = createBall(count, pthis);
    }

    QLabel *createBall(int count, QWidget* pthis) {
        QLabel *tempball = new QLabel(pthis);

        tempball->setGeometry(posx, posy, width, height);
        tempball->setObjectName(QString::fromUtf8("ball")+QString::number(count));
        tempball->setAlignment(Qt::AlignCenter);

        srand((unsigned)time(0));
        int pixNum = rand()%5 + 1;

        QPixmap circle = QPixmap(
            "../Simple2DEngine/Resources/ball"
                    + QString::number(pixNum) + ".png");

        qDebug() << "Ball " + tempball->objectName() + " with color "
                    + QString::number(pixNum) + " generated at ("
                    + QString::number(posx) + ", " + QString::number(posy) + ").";

        tempball->setPixmap(circle);

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
        //Left wall
        if (posx < gl) {
            posx = gl;
            speedx = 0 - speedx;
            qDebug() << myball->objectName() + " touches the left wall.";
        }
        //Right wall
        if (posx > gr-width) {
            posx = gr-width;
            speedx = 0 - speedx;
            qDebug() << myball->objectName() + " touches the right wall.";
        }
        //Ground
        if (posy > gd-height) {
            posy = gd-height;
            speedy *= 1;
            speedx *= 1;
            //This commit does not make balls stop as in the real world.
            /*
            if(speedy <= 0.6){
                speedy = 0;
            }
            if(speedx <= 0.05){
                speedx = 0;
            }
            */
            speedy = 0 - speedy;
            qDebug() << myball->objectName() + " touches the ground.";
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
