//Head File -> Function Declarations

#include <GL/freeglut.h>
#include <String>


#ifndef PLANET_H
#define PLANET_H



using namespace std;
class Planet
 {
 public:
		

 Planet(float distanceFromSun, float orbitSpeed, float rotationSpeed, float radius ,GLuint Texture,string Pname,bool isLightSource);

 Planet(void);

 ~Planet(void);


 void UpdatePosition();  // Planet moves

 void PlanetOrbit(); // Define the orbit of the Planet 

 void RenderPlanet(); // Draw the Planet and its orbit

 void TexturePlanet(string Planet_Name);

  void PlanetInit();
  void setTextureBinded(bool bind);
 private:
	 string Pname;
	 float distanceFromSun,orbitSpeed;
		float rotationSpeed,radius,inclination;
		bool isLightSource;
	    GLuint texture;
	bool Binded ;
 };




#endif


