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

    rock->modelInit("images/fry.png", true);
    rock->Zoom = -2.0;
    rock->Xpos = 100.0;
    rock->Ypos = 100.0;
    rock->set_scale(.25,.25);

    gun->modelInit("images/GunOnly.png", true);
    gun->Ypos = -0.4;
    gun->Xpos = 0.0;
    gun->Zoom = -2.0;
    gun->set_scale(.25,.25);

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
        //glScalef(0.2, 0.2, 1);
        //glTranslated(0, 0, rock->Zoom);
        if (shotMoving) {
            rock->Ypos += 0.01;

        }
        if (rock->Ypos > .4) {
            shotMoving = false;
            rock->Ypos = 1000;
        }
        rock->drawModel();
    glPopMatrix();

    glPushMatrix();
        glScaled(1.0, 1.0, 1.0);
        if (gunMoveLeft && (gun->Xpos > -.75)) {
            gun->Xpos -= 0.01;
        } else if (gunMoveRight && (gun->Xpos < .5)) {
            gun->Xpos += 0.01;
        }
        //glScalef(0.2, 0.2, 1);
        //glTranslated(0, gun->Ypos, gun->Zoom);
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
        //cursor->drawModel();
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
	        if (wParam == VK_LEFT) {
                gunMoveLeft = true;
	        } else if (wParam == VK_RIGHT) {
	            gunMoveRight = true;
	        } else if (wParam == VK_SPACE && !shotMoving) {
                rock->Xpos = gun->Xpos;
                rock->Ypos = gun->Ypos;
                shotMoving = true;
            }
	    break;

	    case WM_KEYUP:								// Has A Key Been Released?
		{
	        if (wParam == VK_LEFT) {
                gunMoveLeft = false;
	        } else if (wParam == VK_RIGHT) {
	            gunMoveRight = false;
	        }
		break;								// Jump Back
		}

		case WM_LBUTTONDOWN:
        {
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
            //restaurantKbMs->mouseEventUp();
        break;								// Jump Back
        }

        case WM_MOUSEMOVE:
        {

        break;								// Jump Back
        }

        case WM_MOUSEWHEEL:
        {
            restaurantKbMs->mouseWheel(modelPot,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;								// Jump Back
        }
}
}
