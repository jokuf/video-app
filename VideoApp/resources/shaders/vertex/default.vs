#version 330 core
layout (location = 0) in vec3 aPos;
uniform float xOffset;

out vec4 Color;

void main()
{
	float xPos = aPos.x + xOffset;

	if (xPos >= 1) {
		xPos = xPos - int(xPos);
	}

	gl_Position = vec4(xPos, aPos.y, aPos.z, 1.0);

	Color = vec4(1.0f, 1.0f, 0.2f, 0.1f);
}