//Main Class
#include <windows.h>
#include <string>
#include "Planet.h"

#include "SOIL.h"  // Simple OpenGL Image Library

GLuint texture[4];
string MyImages[4];



Planet * Sun=NULL;
Planet * Mercury=NULL;
Planet * Venus=NULL;
Planet *Earth=NULL;
Planet * Stars=NULL;

                                //The position of eye point
float Eyex = 0.0;
float Eyey =0.0;
float Eyez = 0.0;

//Position of center point
float centerx = 0.0;
float centery = 0.0;
float centerz = 0.0;

//position of reference point
float upx = 0.0;
float upy = 0.0;
float upz = 0.0;


float XAngle,YAngle,ZAngle;

		
#pragma comment(lib,"opengl32.lib")
void init(){
			


	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);


	MyImages[0] = "Sun.bmp";
	MyImages[1] = "Mercury.bmp";
	MyImages[2] = "Venus.bmp";
	MyImages[3] = "earth.bmp";

}



int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures Using SOIL
{
	const char* File;
	for (int x =0 ;x < 5; x++){ 
		File = MyImages[x].c_str();
    /* load an image file directly as a new OpenGL texture */
	 glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0.0,0.0,0.0,0.0);
	 glEnable(GL_TEXTURE_2D);
  texture[x] = SOIL_load_OGL_texture
        (
       File,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[x] == 0)
        return false;
 


    // Typical Texture Generation Using Data From The Bitmap

    glBindTexture(GL_TEXTURE_2D, texture[x]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	}


	glDisable(GL_TEXTURE_2D);
 return true;

}







 void SetUpPlanets(){

	 


								/*----------------------DECLARE PLANETS----------------------*/

//Planet = new Planet -> Distance From Sun , Orbit Speed, rotation speed , radius , Texture , Planet Name , is Light Source


//According to WolframAlpha sun makes one revolution in 25.04 days therefore 0.6 hours per 1 Degrees Angle
 Sun = new Planet(0.0, 0.0, 0.6, 4.91,texture[0],"Sun",1);

		
//According to WolframAlpha Mercury makes one revolution in 58.64 days therefore 0.25 hours per 1 Degrees Angle
//According to WolframAlpha Mercury`s orbital period is 87.96 days therefore 0.17 hours per 1 Degrees Angle

 Mercury= new Planet(67.0, 0.17, 0.25, 1.4839,texture[1],"Mercury",0); //dist = 67.5 * 10^6 km From sun//Radius 2439

 
//According to WolframAlpha Venus`s orbital period is 224.7 days therefore 0.06 hours per 1 Degrees Angle
//According to WolframAlpha Venus`s 243.01 days therefore 0.61 hours per 1 Degrees Angle
 Venus= new Planet(108.0, 0.066, 0.061, 2.121,texture[2],"Venus",0);//dist = 108 * 10^6 km From sun//Rad 6051.9km


 //365 * 24 
 Earth = new Planet(149.0, 0.041, 0.8, 3.126,texture[3],"earth",0);//dist = 149 * 10^6 km From sun

 //Stars = new Planet(0.0,0.0,0.0,600,texture[3],"BackGround",0);
}


 


void display(){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//GLfloat a[] = {0.1f,0.1f,0.1f,1.0f};
			

glPushMatrix();
glLoadIdentity();

	

	gluLookAt(Eyex,Eyey+40,Eyez+140, centerx , centery, centerz , 0.0f, 1.0f,  0.0f);
	
	glTranslatef(0.0,0.0,90.0);
		glRotatef(YAngle,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,-90.0);
	glRotatef(XAngle,1.0,0.0,0.0);
		
		glPushMatrix();
			
		

Sun->RenderPlanet();
//Sun->setTextureBinded(true);



Mercury->RenderPlanet();

//Mercury->setTextureBinded(true);


Venus->RenderPlanet();

//Venus->setTextureBinded(true);


Earth->RenderPlanet();


//Stars->RenderPlanet();
//Stars->setTextureBinded(true);

glPopMatrix();
glPopMatrix();

glPopMatrix();

glutSwapBuffers();

Sleep(5);
}



void Keys(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'd':
		centerx +=0.8f;
		Eyex +=0.8f;
		break;
		
	case 'a':
		centerx -=0.8f;
		Eyex -=0.8f;
		break;

	case 'w':
		centery +=0.4f;
		Eyey +=0.4f;
		break;
		
	case 's':
		centery -=0.4f;
		Eyey -=0.4f;
		break;

	case 't':
		Eyez -=0.8f;
		break;

	case 'g':
		Eyez +=0.8f;
		break;

	case 'W':
		XAngle +=0.5;
		break;
		
	case 'S':
		XAngle -=0.5f;
		break;
	case 'D':
		YAngle -=0.5;
		break;
		
	case 'A':
		YAngle +=0.5f;
		break;
	case 27:  
		glutDestroyWindow (1);
      exit (0);
      break;
  
		}
	glutPostRedisplay();
}






void update(int x){
	Sun ->UpdatePosition();
	Mercury->UpdatePosition();
	Venus->UpdatePosition();
	Earth->UpdatePosition();
	glutPostRedisplay();
	glutTimerFunc(100,update,x);
}


void handleResize(int w, int h) {
	
	
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 2000.0);
glMatrixMode(GL_MODELVIEW);


}



int main(int argc, char** argv) {

	    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

 glutCreateWindow(argv[0]);
 init();
		LoadGLTextures();
	SetUpPlanets();
	 glutDisplayFunc(display); 
	glutTimerFunc(100, update, 0);	
glutFullScreen();


  
   glutReshapeFunc(handleResize);
    glutKeyboardFunc(Keys);	
   //glutFullScreen();
 
   glutMainLoop();
    return 0;
} 