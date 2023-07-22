#include "cord_system.h"
#include <iostream>
#include <proc.h>
#include "stb_image.h"
#include "glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

cord::~cord()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteTextures(1, &box_texture);
    glDeleteTextures(1, &smile_texture);
    glDeleteProgram(program);
}

void cord::beforeLoop()
{
    createProgram();
    setTex();
    applyTransform();
    // float vertices[] = {
    //     // 3�����꣬3��������ɫ��2����������
    //     // front surface
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 1.0f
    //     // back surface
    //     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f
    //     // left surface
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //     -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //     // right surface
    //     0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    //     // top surface
    //     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //     // bottom surface
    //     -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //     };
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

    glEnable(GL_DEPTH_TEST);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    // ���ö�������
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    // ���ö�������
    glEnableVertexAttribArray(1);
}

void cord::drawTria(GLFWwindow *window)
{
    applyTransform();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, box_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, smile_texture);
    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // ����Ҳ���Ի�������ÿһ�������ζ���һ��id�����Ա�vertex shader���ʵ���gl_InstanceID��
    // glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 2);
}

void cord::createProgram()
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

GLuint cord::createVertexShader()
{

    // ����������ɫ��
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // ������ɫ����Դ��,location��Ϊ�˱�����CPU��׼����������
    // ������ɫ����Ҫ�����CPU�˽�������
    const char *vertex_src = "#version 330 \n"
                             "layout (location=0) in vec3 myPos; \n"
                             "layout (location=1) in vec2 inTexCoord; \n"
                             "out vec2 texCoord;\n"
                             "uniform mat4 trans;\n"
                             "void main() \n"
                             "{ \n"
                             "	gl_Position = trans * vec4(myPos.x, myPos.y, myPos.z, 1.0f); \n"
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

GLuint cord::createFragmentShader()
{
    // ��Ƭ��ɫ��������ͬ������ɫ��
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // Ƭ����ɫ����Ҫ����������յ���ɫ���������ȾΪ��ɫ
    const char *fragment_src = "#version 330 core \n"
                               "in vec2 texCoord;\n"
                               "out vec4 frag_color; \n"
                               "uniform sampler2D box_texture; \n"
                               "uniform sampler2D smile_texture; \n"
                               "void main() { \n"
                               "	frag_color = mix(texture(box_texture, texCoord), texture(smile_texture, texCoord), 0.5); \n"
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

void cord::setTex()
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

void cord::applyTransform()
{
    glm::mat4 model(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(-75.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 trans = projection * view * model;
    GLint loc = glGetUniformLocation(program, "trans");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
}