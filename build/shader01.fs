#version 460 core

out vec4 fragColor;

in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D ourTexture;

void main()
{
	fragColor = texture(ourTexture, ourTexCoord);
};