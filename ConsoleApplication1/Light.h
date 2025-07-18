#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
	~Light();

	void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
				GLfloat diffuseIntensityLoction, GLfloat directionLocation);


private:
	vec3 colour;
	GLfloat ambientIntensity;

	vec3 direction;
	GLfloat diffuseIntensity;

};

