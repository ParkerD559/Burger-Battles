#include <player.h>
#include <timer.h>

timer *T = new timer();

textureLoader stand[2];
textureLoader runText[10];
//textureLoader jump[];

player::player()
{
    //ctor
    verticies[0].x = 0.0;verticies[0].y = 0.0;verticies[0].z = -1.0;
    verticies[1].x = 1.0;verticies[1].y = 0.0;verticies[1].z = -1.0;
    verticies[2].x = 1.0;verticies[2].y = 1.0;verticies[2].z = -1.0;
    verticies[3].x = 0.0;verticies[3].y = 1.0;verticies[3].z = -1.0;

    runspeed  =0;
    jumpspeed =0;
    actionTrigger = 0;
}

player::~player()
{
    //dtor
}
void player::drawPlayer()
{
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();
    glTexCoord2f(0.0,1.0);

    glBegin(GL_QUADS);
    glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);

    glTexCoord2f(1.0,1.0);
    glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);

    glTexCoord2f(1.0,0.0);
    glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);

    glTexCoord2f(0.0,0.0);
    glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);
    glEnd();

    glPopMatrix();
}

void player::playerInit()
{
    T->start();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    stand[0].bindTexture("img/player/play.png");

    runText[0].bindTexture("img/player/player0.png");
    runText[1].bindTexture("img/player/player1.png");
    runText[2].bindTexture("img/player/player2.png");
    runText[3].bindTexture("img/player/player3.png");
    runText[4].bindTexture("img/player/player4.png");
    runText[5].bindTexture("img/player/player5.png");
    runText[6].bindTexture("img/player/player6.png");
    runText[7].bindTexture("img/player/player7.png");
    runText[8].bindTexture("img/player/player8.png");
    runText[9].bindTexture("img/player/player9.png");
    runText[10].bindTexture("img/player/player10.png");
}

void player::actions(int action)
{
    switch(action){
    case 0:
        glPushMatrix();
        glTranslated(-.8,-.75,-1);
        stand[0].binder();
        drawPlayer();

        glPopMatrix();
        break;
    case 1:

        glPushMatrix();
        glTranslated(-.8,-.75,-1);

        if(T -> getTicks() >15){
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();

        }
        runText[runspeed].binder();

        drawPlayer();
        glPopMatrix();
        break;
    }
}
