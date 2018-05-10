#include "skyBox.h"

skyBox::skyBox()
{
    RotateX = 0;
    RotateY = 0;
    RotateZ = 0;

    translateX = 0;
    translateY = 0;
    translateZ = 0;
}

skyBox::~skyBox()
{
    //dtor
}

void skyBox::loadTextures()
{
    glEnable(GL_TEXTURE_2D);
    //glGenTextures(6, tLoad);

    //tLoad[0].bindTexture("img/skybox/sky.png");
    tLoad[0].bindTexture("img/skybox/front.jpg");
    tLoad[1].bindTexture("img/skybox/back.jpg");
    tLoad[2].bindTexture("img/skybox/top.jpg");
    tLoad[3].bindTexture("img/skybox/bottom.jpg");
    tLoad[4].bindTexture("img/skybox/left.jpg");
    tLoad[5].bindTexture("img/skybox/right.jpg");
}

void skyBox::drawBox()
{
    //front
    tLoad[0].binder();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);glVertex3f(-1.0,1.0,1.0);
        glTexCoord2f(1.0,0.0);glVertex3f(1.0,1.0,1.0);
        glTexCoord2f(1.0,1.0);glVertex3f(1.0,-1.0,1.0);
        glTexCoord2f(0.0,0.0);glVertex3f(-1.0,-1.0,1.0);
    glEnd();

    //back
    tLoad[1].binder();
    glBegin(GL_QUADS);
        glTexCoord2f(1.0,0.0);glVertex3f(-1.0,1.0,-1.0);
        glTexCoord2f(1.0,1.0);glVertex3f(-1.0,-1.0,-1.0);
        glTexCoord2f(0.0,1.0);glVertex3f(1.0,-1.0,-1.0);
        glTexCoord2f(0.0,0.0);glVertex3f(1.0,1.0,-1.0);
    glEnd();

    //top
    tLoad[2].binder();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0);glVertex3f(1.0,1.0,-1.0);
        glTexCoord2f(0.0,0.0);glVertex3f(1.0,1.0,1.0);
        glTexCoord2f(1.0,0.0);glVertex3f(-1.0,1.0,1.0);
        glTexCoord2f(1.0,1.0);glVertex3f(-1.0,1.0,-1.0);
    glEnd();

    //bottom
    tLoad[3].binder();
    glBegin(GL_QUADS);
        glTexCoord2f(1.0,1.0);glVertex3f(-1.0,-1.0,1.0);
        glTexCoord2f(0.0,1.0);glVertex3f(1.0,-1.0,1.0);
        glTexCoord2f(0.0,0.0);glVertex3f(1.0,-1.0,-1.0);
        glTexCoord2f(1.0,0.0);glVertex3f(-1.0,-1.0,-1.0);
    glEnd();

    //left
    tLoad[4].binder();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);glVertex3f(-1.0,1.0,-1.0);
        glTexCoord2f(1.0,0.0);glVertex3f(-1.0,1.0,1.0);
        glTexCoord2f(1.0,1.0);glVertex3f(-1.0,-1.0,-1.0);
        glTexCoord2f(0.0,1.0);glVertex3f(-1.0,-1.0,1.0);
    glEnd();

    //right
    tLoad[5].binder();
    glBegin(GL_QUADS);
        glTexCoord2f(1.0,0.0);glVertex3f(1.0,1.0,-1.0);
        glTexCoord2f(1.0,1.0);glVertex3f(1.0,-1.0,-1.0);
        glTexCoord2f(0.0,1.0);glVertex3f(1.0,-1.0,1.0);
        glTexCoord2f(0.0,0.0);glVertex3f(1.0,1.0,1.0);
    glEnd();
}

