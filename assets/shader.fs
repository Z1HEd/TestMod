#version 330 core

// Interpolated values from the vertex shaders
in vec4 fsColor;
//in vec4 fsNorm;

// Ouput data
out vec4 color;

// the direction that the light is coming from.
// must be normalized.
//uniform vec4 lightDir;

void main()
{
	//float light = max(dot(lightDir, fsNorm), 0.0);
	float light = 1.0;
	color = vec4(fsColor.rgb * light, fsColor.a);
}