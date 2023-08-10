#version 330
layout (location=0) in vec3 myPos;
layout (location=1) in vec2 inTexCoord; 
out vec2 texCoord;
uniform mat4 model;
uniform mat4 project;
uniform mat4 view;
void main() 
{ 
	gl_Position = project * view * model * vec4(myPos.x, myPos.y, myPos.z, 1.0f); 
	texCoord = inTexCoord;
}