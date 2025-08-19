#include "Camera.h"

Camera::Camera() {}


Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
	GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	//up = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);


	movementSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}


//if using keys to control Camera
void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}

}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	//turnSpoeed when we move from x-y axis and stuff
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	//change position from mouse input
	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}


	update();

}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::vec3 Camera::getCameraDirection() 
{
	return glm::normalize(front);
}

glm::mat4 Camera::calculateViewMatrix()
{
	// lookAt designed for camera--- calculate matrix that apllies all correct rotations / translations
	return glm::lookAt(position, position + front, up);
}

// texture calculation
void Camera::update()
{
	front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
	front.y = sin(glm::radians(pitch));
	
	front.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));
	//normalize set of vector's length to 1.
	front = glm::normalize(front);

	// cross-product
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

// destruct
Camera::~Camera()

{
}