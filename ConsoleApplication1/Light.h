#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);
	~Light();

	// virtual void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLoction);


protected:
	vec3 colour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

};

