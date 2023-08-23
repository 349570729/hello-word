#version 330
layout (location=0) in vec3 myPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 project;
void main()
{ 
	gl_Position = project * view * model * vec4(myPos, 1.0f); 
}