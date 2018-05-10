#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h>

#include<gl/gl.h>
#include<iostream>

using namespace std;

class GLScene
{
    public:
        GLScene(bool reset = true);
        virtual ~GLScene();
        GLint initGL();
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);
        GLvoid resetScene();

        int windMsg(HWND,UINT, WPARAM,LPARAM);

        //Font
        GLvoid buildFont();
        GLvoid killFont();
        GLvoid glPrint(const char *, ...);
        GLuint base;
        GLfloat cnt1;
        GLfloat cnt2;

        //Other Params
        WPARAM wParam;
        float screenHeight;
        float screenWidth;
        bool  sceneDone;
    protected:

    private:
};

#endif // GLSCENE_H
