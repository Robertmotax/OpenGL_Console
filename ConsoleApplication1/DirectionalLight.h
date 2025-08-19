#pragma once

#include "Light.h" //includes glew,glfw,glm

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir);
	~DirectionalLight();

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint directionLocation);

protected:
	vec3 direction;
};

