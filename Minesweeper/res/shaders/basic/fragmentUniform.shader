#version 330 core
out vec4 FragColor;
in vec3 colorToUse; //discard this value

uniform vec4 ourColor;

void main()
{
	FragColor = ourColor;

}