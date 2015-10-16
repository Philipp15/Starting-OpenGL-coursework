
#include "SOIL.h"  // Simple OpenGL Image Library
#include <glut.h>
#include <string>



std::string Filename; //Name of the texture


GLuint texture[9];  // Array of Textures



int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures Using SOIL
{


    /* load an image file directly as a new OpenGL texture */
	 glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0.0,0.0,0.0,0.0);
	 glEnable(GL_TEXTURE_2D);


   texture[0] = SOIL_load_OGL_texture
        (
        "earth.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[0] == 0)
        return false;
 


    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	    
	glDisable(GL_TEXTURE_2D);
 return true;

}

