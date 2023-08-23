#version 330 core
out vec4 frag_color;
uniform vec3 object_color;
uniform vec3 light_color;
void main() {
	frag_color = vec4(object_color * light_color, 1.0);
}