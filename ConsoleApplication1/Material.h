#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>


class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);
	~Material();


	void useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

private:
	GLfloat specularIntensity; //low== dim, high == shiny spot, so how much it absorbs
	GLfloat shininess; // or specularPower == how smooth the surface is portrayed...ex: small = spread out, high = concentrated



};

