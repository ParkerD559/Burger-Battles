#ifndef RESTAURANTSCENE_H
#define RESTAURANTSCENE_H

#include <windows.h>

#include<gl/gl.h>
#include<iostream>

using namespace std;

class restaurantScene
{
    public:
        restaurantScene();
        virtual ~restaurantScene();
        GLint initGL();
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        int windMsg(HWND,UINT, WPARAM,LPARAM);


        WPARAM wParam;
        float screenHeight;
        float screenWidth;
    protected:

    private:
};

#endif // RESTAURANTSCENE_H
