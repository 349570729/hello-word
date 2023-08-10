#version 330 core
in vec2 texCoord;
out vec4 frag_color; 
uniform sampler2D box_texture; 
uniform sampler2D smile_texture; 
void main() {
	frag_color = mix(texture(box_texture, texCoord), texture(smile_texture, texCoord), 0.5);
}