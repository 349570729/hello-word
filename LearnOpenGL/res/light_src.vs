#version 330
layout (location=0) in vec3 myPos;
uniform mat4 model;
uniform mat4 project;
uniform mat4 view;
void main()
{ 
	gl_Position = model * vec4(myPos, 1.0f); 
}