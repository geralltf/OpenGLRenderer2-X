#version 410

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texcoord; 

uniform mat4 MVP;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 TexCoords;

void main() 
{
	mat4 _MVP = projectionMatrix * viewMatrix * modelMatrix;

	TexCoords = vec2(vertex_texcoord.x, vertex_texcoord.y);
	TexCoords = vertex_position.xy;
	gl_Position = _MVP * vec4(vertex_position, 1.0);
}