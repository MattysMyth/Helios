#version 330 core

layout(location = 0) 
in vec3 position;

layout(location = 1)
in vec4 color;

out vec4 interpColor;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
	interpColor = color;
};