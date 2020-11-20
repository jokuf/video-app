#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 Color;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	Color = vec4(0.5f, 0.5f, 0.9f, 0.1f);
}