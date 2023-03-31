#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 colorInput;
layout(location = 2) in vec2 aTexCoord;


out vec3 colorToUse;
out vec2 TexCoord;


void main()
{
	gl_Position = position;
	colorToUse = colorInput;
	TexCoord = aTexCoord;
};