#version 330 core

layout(location = 0) in vec4 vert;
//layout(location = 1) in vec4 norm;
layout(location = 1) in vec4 color;

out vec4 gsColor;
//out vec4 gsNorm;

// model view matrix
uniform float MV[25];

void main()
{
	// multiply the vertex by MV
	float v[5] = float[5](vert.x, vert.y, vert.z, vert.w, 1.0);
	vec4 result = vec4(0.0, 0.0, 0.0, 0.0);
	//vec4 normal = vec4(0.0, 0.0, 0.0, 0.0);
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			result[row] += MV[col * 5 + row] * v[col];
			//normal[row] += MV[col * 5 + row] * norm[col];
		}
		result[row] += MV[4 * 5 + row] * v[4];
	}

	gl_Position = result;
	gsColor = color;
	//gsNorm = normal;
}