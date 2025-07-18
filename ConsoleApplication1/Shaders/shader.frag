#version 330

in vec4 vCol;
in vec2 texCoord;
// flat in vec3 Normal;
in vec3 Normal;
in vec3 FragPos;


out vec4 colour;

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct MaterialLight 
{
	float specularIntensity;
	float shininess;
};


uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform MaterialLight materialLight;

uniform vec3 eyePosition;


void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(Normal), directionalLight.direction), 0.0f);
	//^^^ basically represents A.B = |A||B|cos(angle)
	vec4 diffuseColour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
	
	vec4 specularColour = vec4(0,0,0,0);
	
	if (diffuseFactor > 0.0f) 
	{
		vec3 fragToEye = normalize(eyePosition - FragPos); // vector between camera and object
		
		//where actual ray is reflected		
		vec3 reflectedVertex = normalize(reflect(directionalLight.direction, normalize(Normal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0f) 
		{
			specularFactor = pow(specularFactor, materialLight.shininess); // exponential
			specularColour = vec4(directionalLight.colour * materialLight.specularIntensity * specularFactor, 1.0f);
		}
		
	}
	
	
	// colour = vCol;
	// colour = texture(theTexture, texCoord) * vCol;
	
	colour = texture(theTexture, texCoord) * (ambientColour + diffuseColour + specularColour);
}