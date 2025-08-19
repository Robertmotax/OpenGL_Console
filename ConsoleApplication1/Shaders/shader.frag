#version 330

in vec4 vCol;
in vec2 texCoord;
// flat in vec3 Normal;
in vec3 Normal;
in vec3 FragPos;


out vec4 colour;

const int MAX_POINT_LIGHTS = 3; //meant to match in code
const int MAX_SPOT_LIGHTS  = 3;
//basic light class
struct Light 
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};


struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight 
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight 
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct MaterialLight 
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

//Design the lighting
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform MaterialLight materialLight;

uniform vec3 eyePosition;

//functuon in glsl
vec4 CalcLightByDirection(Light light, vec3 direction) 
{
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
	//^^^ basically represents A.B = |A||B|cos(angle)
	vec4 diffuseColour = vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	vec4 specularColour = vec4(0,0,0,0);
	
	if (diffuseFactor > 0.0f) 
	{
		vec3 fragToEye = normalize(eyePosition - FragPos); // vector between camera and object
		
		//where actual ray is reflected		
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0f) 
		{
			specularFactor = pow(specularFactor, materialLight.shininess); // exponential
			specularColour = vec4(light.colour * materialLight.specularIntensity * specularFactor, 1.0f);
		}
		
	}
	
	return (ambientColour + diffuseColour + specularColour);
}

vec4 CalcDirectionalLight() 
{
	return CalcLightByDirection(directionalLight.base, directionalLight.direction);
}

//just one singular light -- used mainly for spot light
vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = FragPos - pLight.position; // get the vector from the point light
	float distance = length(direction);
	direction = normalize(direction);
	
	vec4 colour = CalcLightByDirection(pLight.base, direction);
	//Quadratic formula
	float attenuation = pLight.exponent * distance * distance +
						pLight.linear * distance +
						pLight.constant;
						
	return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight) 
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);
	
	if (slFactor > sLight.edge) 
	{ 
		vec4 colour = CalcPointLight(sLight.base); //pass the point light
		return colour * (1.0f - (1.0f - slFactor) * (1.0f / (1.0f - sLight.edge)));
		
	} else {
		return vec4(0, 0, 0, 0);
	}

}

vec4 CalcPointLights() 
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for (int i = 0; i < pointLightCount; i++)
	{							
		totalColour += CalcPointLight(pointLights[i]);
	}
	return totalColour;
}

vec4 CalcSpotLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for (int i = 0; i < spotLightCount; i++)
	{							
		totalColour += CalcSpotLight(spotLights[i]);
	}
	return totalColour;
}

void main()
{
	// colour = vCol;
	// colour = texture(theTexture, texCoord) * vCol;
	
	vec4 finalColour = CalcDirectionalLight();
	finalColour += CalcPointLights(); //add it to the directionalLight as final product
	finalColour += CalcSpotLights();  //
	
	colour = texture(theTexture, texCoord) * finalColour;
}