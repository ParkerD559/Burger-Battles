#include "restaurantScene.h"
//#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <cmath>
//#include <random>

Model *modelPot = new Model();
Inputs *restaurantKbMs = new Inputs();
parallax *restaurantPlx = new parallax();
player *resturantPly = new player();
skyBox *restaurantSky = new skyBox();
Model *man[5] = { new Model(), new Model(), new Model(), new Model(), new Model() };
Model *cursor = new Model();
Model *rock = new Model();
Model *gun = new Model();

restaurantScene::restaurantScene()
{
    //ctor
    screenHeight= GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

restaurantScene::~restaurantScene()
{
    //dtor
}

GLint restaurantScene::initGL()
{
    srand(NULL);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

   // glEnable(GL_COLOR_MATERIAL);
    //GLLight SetLight(GL_LIGHT0);
    //GLLight Light(GL_LIGHT0);

    //modelTeapot->modelInit("images/player/player0.png",true);
    restaurantPlx->parallaxInit("images/secondstage.png");
    resturantPly->playerInit();
    restaurantSky->loadTextures();

    for(int i = 0; i < 5; i++) {
        man[i]->modelInit("images/spatula.png", true);
        man[i]->Zoom = -8.;
        man[i]->Ypos = 5.;
        man[i]->Xpos = (i * 4.0) - 10.0;
    }

    cursor->modelInit("images/cursor.png", true);

    rock->modelInit("images/Fork.png", true);
    rock->Zoom = -10.;
    rock->Xpos = 100.0;
    rock->Ypos = 100.0;

    gun->modelInit("images/GunOnly.png", true);
    gun->Zoom = -2.0;

    return true;
}

GLint restaurantScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix


    glPushMatrix();
      glScaled(3.33,3.33,1.0);
         restaurantPlx->drawSquare(screenWidth,screenHeight);
     glPopMatrix();
       //restaurantPlx->scroll(true,"right",0.005);

/*
    glPushMatrix();
        glDisable(GL_LIGHTING);
        glScaled(200,200,200);
        restaurantSky->drawBox();
        glEnable(GL_LIGHTING);
    glPopMatrix();
*/
/*
    glPushMatrix();
        //glTranslated(0,0,modelTeapot->Zoom);
        resturantPly->actions(resturantPly->actionTrigger);
    glPopMatrix();
*/

    glPushMatrix();
        glScaled(1.0, 1.0, 1.0);
        glTranslated(1.75, -0.8, gun->Zoom);
        gun->drawModel();
    glPopMatrix();

    for (int i = 0; i < 5; i++) {
        man[i]->Ypos -= rand() % 1000 * 0.000005;
        glPushMatrix();
            glScaled(1, 1, 1);
            glTranslated(0, man[i]->Ypos, man[i]->Zoom);
            man[i]->drawModel();
        glPopMatrix();
    }

    glPushMatrix();
        glScaled(1, 1, 1);
        glTranslated(0, 0, cursor->Zoom);
        cursor->drawModel();
    glPopMatrix();

    rock->Zoom -= 0.1;
    for(int i = 0; i < 5; i++) {
        if (rock->Zoom < (man[i]->Zoom - 20.0)) {
            if (((abs(rock->Xpos - man[i]->Xpos) < 0.4) && (abs(rock->Ypos - man[i]->Ypos) < 1.0)) || (man[i]->Ypos < -3.0)) {
                man[i]->Ypos = 5.0;
            }
        }
    }
    if (rock->Zoom < -40.0) {
        rock->Zoom = 0.;
        rock->Xpos = 100.0;
        rock->Ypos = 100.0;
    }

    glPushMatrix();
        glScaled(0.01, 0.01, 0.01);
        glTranslated(0, 0, rock->Zoom);
        rock->drawModel();
    glPopMatrix();

    return true;
}

GLvoid restaurantScene::resizeGLScene(GLsizei width, GLsizei height)
{
   GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
   glViewport(0,0,width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0,aspectRatio,0.1,1000);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int restaurantScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)									// Check For Windows Messages
	{

	    case WM_KEYDOWN:
	        restaurantKbMs->wParam = wParam;
	        restaurantKbMs->keyPressed(modelPot);
	        restaurantKbMs->keyEnv(restaurantPlx, 0.005);
	        restaurantKbMs->keyPressed(resturantPly);
	        restaurantKbMs->keyPressed(restaurantSky);

	    break;

	    case WM_KEYUP:								// Has A Key Been Released?
		{
			restaurantKbMs->wParam = wParam;
			restaurantKbMs->keyUP();
			restaurantKbMs->keyUp(resturantPly);
		break;								// Jump Back
		}

		case WM_LBUTTONDOWN:
        {
            restaurantKbMs->wParam = wParam;
            restaurantKbMs->mouseEventDown(modelPot,LOWORD(lParam),HIWORD(lParam));
            if ((rock->Xpos > 50.0) && (rock->Ypos > 50.0)){
                rock->Xpos = cursor->Xpos;
                rock->Ypos = cursor->Ypos;
                rock->Zoom = 0.0;
            }
        break;								// Jump Back
        }

   		case WM_RBUTTONDOWN:
        {
            restaurantKbMs->wParam = wParam;
            restaurantKbMs->mouseEventDown(modelPot,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

          case WM_MBUTTONDOWN:
        {
            restaurantKbMs->wParam = wParam;
            restaurantKbMs->mouseEventDown(modelPot,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            restaurantKbMs->mouseEventUp();
        break;								// Jump Back
        }

        case WM_MOUSEMOVE:
        {
             restaurantKbMs->mouseMove(rock, LOWORD(lParam), HIWORD(lParam));
             for(int i = 0; i < 5; i++) {
                restaurantKbMs->mouseMove(man[i], LOWORD(lParam),HIWORD(lParam));
             }
             restaurantKbMs->mouseMove(restaurantSky,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

        case WM_MOUSEWHEEL:
        {
            restaurantKbMs->mouseWheel(modelPot,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;								// Jump Back
        }
}
}
