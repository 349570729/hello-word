#include "tex.h"
#include <iostream>
#include <proc.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::~Texture()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &box_texture);
	glDeleteTextures(1, &smile_texture);
	glDeleteProgram(program);
}

void Texture::beforeLoop()
{
	createProgram();
	setTex();
	float vertices[] = {
		// 3�����꣬3��������ɫ��2����������
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// OpenGL����ģʽҪ��ʹ��VAO
	// VAO���ס�����һЩ״̬
	//
	// ��������buffer
	glGenBuffers(1, &VBO);
	// �󶨻������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ������������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����vertices�е�������ʲô���壬�����ö�������ָ��
	// 0��vertex_src����location��ֵ
	// 3����Ϊ�������Ե�������vec3��3������
	// GL_FLOAT ���������ͣ�GL_FALSE��ʾ�������ݱ�׼��
	// �������Դ�vertices[0]��ʼ��ȡ���������0
	// �����ݴ���myPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	// ���ö�������
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	// ���ö�������
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	// ���ö�������
	glEnableVertexAttribArray(2);
}

void Texture::drawTria(GLFWwindow *window)
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, box_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, smile_texture);
	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// ����Ҳ���Ի�������ÿһ�������ζ���һ��id�����Ա�vertex shader���ʵ���gl_InstanceID��
	// glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 2);
}

void Texture::createProgram()
{
	GLuint vertex_shader = createVertexShader();
	GLuint fragment_shader = createFragmentShader();

	// ����һ����ɫ������������ɫ�����ţ����ź���ܵ���
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char errorInfo[512];
		glGetProgramInfoLog(program, 512, nullptr, errorInfo);
		std::cout << "program link error: " << errorInfo << std::endl;
	}

	// ���ź�Ϳ����ͷ�shader��
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

GLuint Texture::createVertexShader()
{

	// ����������ɫ��
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	// ������ɫ����Դ��,location��Ϊ�˱�����CPU��׼����������
	// ������ɫ����Ҫ�����CPU�˽�������
	const char *vertex_src = "#version 330 \n"
							 "layout (location=0) in vec3 myPos; \n"
							 "layout (location=1) in vec3 myColor; \n"
							 "layout (location=2) in vec2 inTexCoord; \n"
							 "out vec3 cust_color;\n"
							 "out vec2 texCoord;\n"
							 "void main() \n"
							 "{ \n"
							 "	gl_Position = vec4(myPos.x, myPos.y, myPos.z, 1.0f); \n"
							 "	cust_color = myColor;\n"
							 "	texCoord = inTexCoord;\n"
							 "} \0";
	// ��ɫ������Դ��
	glShaderSource(vertex_shader, 1, &vertex_src, nullptr);

	// ������ɫ��
	glCompileShader(vertex_shader);
	int success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char errorInfo[512];
		glGetShaderInfoLog(vertex_shader, 512, nullptr, errorInfo);
		std::cout << "vertex shader compile failed: " << errorInfo << std::endl;
	}
	return vertex_shader;
}

GLuint Texture::createFragmentShader()
{
	// ��Ƭ��ɫ��������ͬ������ɫ��
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	// Ƭ����ɫ����Ҫ����������յ���ɫ���������ȾΪ��ɫ
	const char *fragment_src = "#version 330 core \n"
							   "in vec3 cust_color;\n"
							   "in vec2 texCoord;\n"
							   "out vec4 frag_color; \n"
							   "uniform sampler2D box_texture; \n"
							   "uniform sampler2D smile_texture; \n"
							   "void main() { \n"
							   // linearly interpolate between both textures (80% container, 20% awesomeface)
							   // mix color
							   //    "	frag_color = texture(smile_texture, texCoord) * vec4(cust_color, 1.0f); \n"
							   // mix two pictures
							   //    "	frag_color = mix(texture(box_texture, texCoord), texture(smile_texture, texCoord), 0.2f); \n"
							   // exersize 1: flip left and right smile
							   "	frag_color = mix(texture(box_texture, texCoord), texture(smile_texture, vec2(1.0f - texCoord.x, texCoord.y)), 0.2f); \n"
							   "}\0";
	glShaderSource(fragment_shader, 1, &fragment_src, nullptr);
	glCompileShader(fragment_shader);
	int success;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char errorInfo[512];
		glGetShaderInfoLog(fragment_shader, 512, nullptr, errorInfo);
		std::cout << "fragment shader compile failed: " << errorInfo << std::endl;
	}
	return fragment_shader;
}

void Texture::setTex()
{
	glGenTextures(1, &box_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, box_texture);
	// S �� T�� �����ظ�����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, channel;
	std::string path = os::curProcDir() + "/wall.jpg";

	unsigned char *data = stbi_load(path.data(), &width, &height, &channel, 0);
	if (nullptr == data)
	{
		printf("stbi load image fail:%s\n", path.data());
		return;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// add smile texture
	glGenTextures(1, &smile_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, smile_texture);
	// S �� T�� �����ظ�����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	path = os::curProcDir() + "/awesomeface.png";
	stbi_set_flip_vertically_on_load(1);
	data = stbi_load(path.data(), &width, &height, &channel, 0);
	if (nullptr == data)
	{
		printf("stbi load image fail:%s\n", path.data());
		return;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// tell opengl uniform box_texture is corresponding to box_texture, and smile_texture to smile_texture
	printf("bind uniform...\n");
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "box_texture"), 0);
	glUniform1i(glGetUniformLocation(program, "smile_texture"), 1);
}
