//Function Definitions



#include "Planet.h"
#include <GL\freeglut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include <String>
#include "SOIL.h"  // Simple OpenGL Image Library
//#include <math.h>


GLUquadricObj *sphere = NULL;

float hours;

GLuint textures;




Planet::Planet(float distanceFS, float roundSpeed, float rotateSpeed, float Radius,GLuint Texture,string PlanetName,bool LightSource){
	
	

	distanceFromSun = distanceFS;
	orbitSpeed = roundSpeed;
	rotationSpeed = rotateSpeed;
	radius = Radius;
	Pname = PlanetName;
	isLightSource = LightSource;
	texture = Texture;
	Binded = false;

}





void Planet::PlanetOrbit(){


	glPushMatrix();

	 glBegin(GL_LINES);
	 

	 for (int i = 0; i < 90; ++i) {//Drawing Lines
		 glVertex3d(cos((i*4)*3.141/180.0) * 	distanceFromSun, 0, sin((i*4)*3.141/180.0) * 	distanceFromSun);
		 glVertex3d(cos(((i+1)*4)*3.141/180.0) * 	distanceFromSun, 0, sin(((i+1)*4)*3.141/180.0) * 	distanceFromSun);
	 }

	 glEnd();
	 glPopMatrix();

}


void Planet::setTextureBinded(bool binded){
	this->Binded = binded;
}




void Planet::RenderPlanet(){
	
		PlanetOrbit(); // Draw orbit 

	GLfloat sunny[] = {0.9f, 0.9f,0.9f, 1.0f};
	GLfloat Gloomy[] = {0.1f, 0.1f,0.1f, 1.0f};
	sphere = gluNewQuadric();


glPushMatrix(); // Start Camera 

GLfloat lightColor[] = {15.0f,15.0f,15.0f,1.0f}; // Set the Colour of the Light
			GLfloat lightPosition[] = {0.0f,0.0f,0.0f,1.0f}; // Set the Position of the Light ie Center the Sun 

			
		//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,a);

	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightColor);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0001);

	

	

	glPushMatrix(); // Draw Planet
	
	if(this->isLightSource == true){
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sunny);

	}else

	glMaterialfv(GL_FRONT, GL_EMISSION, Gloomy);

	//Orbit Speed
	glRotatef(fmod((orbitSpeed * hours) , 360) , 0.0 , 1.0 , 0.0);
	glTranslatef(distanceFromSun,0.0,0.0);

	//Rotation Speed
	glRotatef (fmod((rotationSpeed * hours) , 360) , 0.0 , 1.0 , 0.0);
	glRotatef(90,1.0,0.0,0.0);


	//if (this->Binded == false){//check if Binded already 

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);


	//glGenTextures( 1, &texture );
	glBindTexture(GL_TEXTURE_2D,texture);//we use glBindTextures to specify which texture to create and to select a specific texture.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	gluQuadricTexture(sphere,1);
	

	


	gluSphere(sphere,radius, 10, 10);
	//this->Binded = true;
	//}
	
	gluQuadricTexture(sphere,1);
	
	gluSphere(sphere,radius, 100, 100);
	
	

	glPopMatrix();

	glPopMatrix();
	

}

void Planet :: UpdatePosition(){

	
	hours += 1;


}


Planet::~Planet()
{
	glDeleteTextures( 1, &texture );

}