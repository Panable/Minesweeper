#version 330 core
out vec4 FragColor;
in vec3 colorToUse;

void main()
{
	FragColor = vec4(colorToUse, 1.0f);
}