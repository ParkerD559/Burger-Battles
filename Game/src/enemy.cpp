#include "enemy.h"
#include <timer.h>
#include <textureLoader.h>
#include <iostream>
#include <cmath>

using namespace std;

timer *tim = new timer();
timer *spawnRate = new timer();
textureLoader *enemyText = new textureLoader();


enemy::enemy(int *score)
{
    //ctor
    verticies[0].x = 0.0;verticies[0].y = 0.0;verticies[0].z = -1;
    verticies[1].x = .1;verticies[1].y = 0.0;verticies[1].z = -1;
    verticies[2].x = .1;verticies[2].y = .1;verticies[2].z = -1;
    verticies[3].x = 0.0;verticies[3].y = .1;verticies[3].z = -1;
    srand(time(0));
    Xpos = .9;
    ypos = -0.3;
    Ypos = ((double)(rand()%250)/1000*-1)-.05;
    runSpeed = .01;
    this->score = score;
}

enemy::~enemy()
{
    //dtor
}

void enemy::drawEnemy()
{

    glColor3f(1.0,1.0,1.0);
    enemyText->binder();
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,1.0);
    glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);

    glTexCoord2f(1.0,1.0);
    glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);

    glTexCoord2f(1.0,0.0);
    glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);

    glTexCoord2f(0.0,0.0);
    glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);

    glEnd();

}

void enemy::enemyInit()
{


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    tim->start();
    enemyText->binder();
    enemyText->bindTexture("images/pixelfries.png");
    spawnRate->start();
}

void enemy::deleteEnemy()
{

}

void enemy::enemyScroll(player *ply)
{

    if(tim->getTicks()>10){
        //cout << Xpos << endl;
        //cout << Ypos << endl;
        Xpos= Xpos - runSpeed;
        tim->reset();
    }
    if((Xpos > -.9 && Xpos <.8) && !isCollided(ply)){

        glTranslated(Xpos,Ypos,0);

        //cout << Ypos << endl;
        drawEnemy();
    }
    else{
        Ypos = ((double)(rand()%250)/1000*-1)-.05;
        //cout << Ypos;
        Xpos = .8;
        }

}

bool enemy::isCollided(player *ply)
{
    float xdistance = abs(ply->Xpos-Xpos);
    float ydistance = abs(ply->Ypos-Ypos);

    //cout << ply->Xpos << endl;;
    //cout << xdistance << endl;
    //cout << ydistance << endl;
    if (xdistance < .05 && ydistance < .05)
    {
        //cout << "COLLISION" << endl;
            *score += 100;
            return true;
    }
    /*
        float distance = sqrt(pow(abs(ply->Xpos)-abs(Xpos),2)+pow(abs(ply->Ypos)-abs(Ypos),2));

        if (distance < 1.4142135375){
            cout << "COLLISION" << endl;
            return false;
            }
            */
        return false;
}

