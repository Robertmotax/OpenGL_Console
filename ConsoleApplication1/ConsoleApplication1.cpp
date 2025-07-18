#define STB_IMAGE_IMPLEMENTATION


#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "util.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;


Texture brickTexture;
Texture dirtTexture;


//Light class
Light mainLight;
//material class for specular lighting
Material shinyMaterial;
Material dullMaterial;


//We calculate the time 
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;


// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	//for texture, we wish to add more variables in here, also look Mesh.cpp
	//we need to tell the vertexAttribPointer to handle 2 more additional variables
	//GLfloat vertices[] = {
	//-1.0f, -1.0f, 0.0f,
	//0.0f, -1.0f, 1.0f,
	//1.0f, -1.0f, 0.0f,
	//0.0f, 1.0f, 0.0f
	//};
	GLfloat vertices[] = {
		// x	y		z	u		v	  nx	ny		nz = Normal position for diffuseIntensity
		-1.0f, -1.0f, -0.6f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,  0.5f, 1.0,   0.0f, 0.0f, 0.0f,
	};

	//compute per-vertex normals for smooth shading in OpenGL when rendering 3D models. 
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	// 	obj2->CreateMesh(vertices, indices, 12, 12);
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{

	mainWindow = Window(1000, 600);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTexture();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTexture();


	//material
	shinyMaterial = Material(1.0f, 32);
	dullMaterial = Material(0.3f, 4);

	//construct a new class Light
	mainLight = Light(1.0f, 1.0f, 1.0f, //color light
					0.2f,  //ambient intensity
					2.0, -1.0f, -2.0f, //direction of the light
					0.1f //diffusion intensity of the direction of the light
	);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0,
			uniformEyePosition = 0,
			uniformAmbientIntensity = 0, uniformAmbientColour = 0,
			uniformDirection = 0, uniformDiffuseIntensity = 0,
			uniformSpecularIntensity = 0, uniformShininess = 0;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		// If using SDL
		//SDL_GetPerformanceCounter();
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime; // ((now - lastTime) * 1000) / SDL_GetPerformanceFrequency();
		lastTime = now;
	



		// Get + Handle User Input
		glfwPollEvents();

		//check for key pressing
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.MouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		uniformDirection = shaderList[0].GetDirectionLocation();
		uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();
		uniformEyePosition = shaderList[0].GetEyePosition();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();


		mainLight.useLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);

		//for specular lighting, we move this before the translate and scale
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		//getting new location positoon for lighting
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		brickTexture.UseTexture();
		shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		/** 
			MUST REMEMBER that in matrices, the order really does maatter a lot, thus must 
			be cautious about how we order things. For instance, projection * view * model is different than
			projection * model * view
		
		*/
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		dirtTexture.UseTexture();
		dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}