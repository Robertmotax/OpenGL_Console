#include "Texture.h"


Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;

	fileLocation = "";
}

Texture::Texture(const char* fileLoc) 
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileLoc;
}

/**
* @brief returns with GL_RGB
*/
bool Texture::LoadTexture()
{
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", fileLocation);
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//GL_REPEAT is a texture wrapping mode in OpenGL that repeats the texture across
	//the entire surface of a polygon, making the texture coordinates outside the[0, 1]
	//range repeat the texture image instead of clamping to the edge of the texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// mirrored-repeat if go esbeyond eedge of texture, it goes inverted of 1.0f
	// example: if 1.1f, instead of 0.1f it uses 0.9f 
	// // GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//border-parameter is legacy value
	//byte is basically char but byte is 8-bit, char is 1-bit.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

/**
* @brief returns with GL_RGBA
*/
bool Texture::LoadTextureA()
{
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", fileLocation);
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//GL_REPEAT is a texture wrapping mode in OpenGL that repeats the texture across
	//the entire surface of a polygon, making the texture coordinates outside the[0, 1]
	//range repeat the texture image instead of clamping to the edge of the texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// mirrored-repeat if go esbeyond eedge of texture, it goes inverted of 1.0f
	// example: if 1.1f, instead of 0.1f it uses 0.9f 
	// // GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//border-parameter is legacy value
	//byte is basically char but byte is 8-bit, char is 1-bit.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

void Texture::UseTexture() 
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);



}

void Texture::ClearTexture() 
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}



Texture::~Texture()
{
	ClearTexture();
}