#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ShadowMap.h"

using namespace glm;

class Light
{
public:
	Light();
	Light(GLuint shadowWidth, GLuint shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity);
	~Light();

	ShadowMap* getShadowMap() { return shadowMap; }

	// virtual void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLoction);


protected:
	vec3 colour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	glm::mat4 lightProj;

	ShadowMap* shadowMap;
};

