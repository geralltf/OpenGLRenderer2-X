#version 330 core
layout (location = 0) in vec4 vertex;
//layout (location = 0) in vec3 vertex_pos;
//layout (location = 1) in vec2 vertex_texcoord;

out vec2 TexCoords;

uniform mat4 MVP;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
	mat4 _MVP = projectionMatrix * viewMatrix * modelMatrix;
	
    gl_Position = _MVP * vec4(vertex.x, vertex.y, 0.0, 1.0);
    TexCoords = vertex.zw;
}  