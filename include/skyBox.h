#ifndef SKYBOX_H
#define SKYBOX_H

#include "GL/gl.h"
#include "TextureLoader.h"

class skyBox
{
    public:
        skyBox();
        virtual ~skyBox();
        void loadTextures();
        void drawBox();

        float width;
        float height;
        float depth;

        textureLoader tLoad[6];

        float RotateX;
        float RotateY;
        float RotateZ;

        float translateX;
        float translateY;
        float translateZ;

    protected:

    private:
};

#endif // SKYBOX_H
