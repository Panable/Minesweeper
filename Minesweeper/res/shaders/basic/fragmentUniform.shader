#version 330 core

in vec3 colorToUse; //discard this value
in vec2 TexCoord;

out vec4 FragColor;


uniform sampler2D ourTexture;

void main()
{
	vec4 texColor = texture(ourTexture, TexCoord);
	//FragColor = vec4(TexCoord.x, TexCoord.y, 0.0, 1.0); 
	
	//FragColor = vec4(texColor.z, 0.0f, 0.0f, 1.0f);

	FragColor = texture(ourTexture, TexCoord);

}