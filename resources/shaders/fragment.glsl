#version 330 core

in vec3 oCol;
in vec2 oTexCoord;

uniform sampler2D texture1;

void main ()
{
	gl_FragColor = texture(texture1, oTexCoord);
}