#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;


out vec4 vCol;
out vec2 texCoord;
//flat out vec3 Normal; // instead of interpolating each corner, it will use just one corner
out vec3 Normal;
out vec3 FragPos;


uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	
	texCoord = tex;
	
	Normal = mat3(transpose(inverse(model))) * norm; //we just need to know the position of the model's coordinates, no need for the 4th column and row's translation.
	
	FragPos = (model * vec4(pos, 1.0)).xyz;
	
	
	
}