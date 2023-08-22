#include "cord_system.h"

#include <proc.h>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "stb_image.h"
#include "camera.h"
#include "utils.h"

cord::cord()
    : shader_(os::curProcDir() + "/cord.vs", os::curProcDir() + "/cord.fs")
{}

cord::~cord()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteTextures(1, &box_texture);
    glDeleteTextures(1, &smile_texture);
}

void cord::beforeLoop()
{
    setTex();

    const float *vertices = cubicVertexWithTex();
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
    glBufferData(GL_ARRAY_BUFFER, 180 * sizeof(float), vertices, GL_STATIC_DRAW);

    // ����vertices�е�������ʲô���壬�����ö�������ָ��
    // 0��vertex_src����location��ֵ
    // 3����Ϊ�������Ե�������vec3��3������
    // GL_FLOAT
    // ���������ͣ�GL_FALSE��ʾ�������ݱ�׼��
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
    window_ = window;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, box_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, smile_texture);
    shader_.use();
    glBindVertexArray(VAO);
    applyProject();
    applyModel1();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    applyModel2();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Shader *cord::shader()
{
    return &shader_;
}

void cord::setCamera(Camera *camera)
{
    camera_ = camera;
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
    if (nullptr == data) {
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
    if (nullptr == data) {
        printf("stbi load image fail:%s\n", path.data());
        return;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // tell opengl uniform box_texture is corresponding to box_texture, and
    // smile_texture to smile_texture
    printf("bind uniform...\n");
    shader_.use();
    shader_.setInt("box_texture", 0);
    shader_.setInt("smile_texture", 1);
}

void cord::applyModel1()
{
    glm::mat4 model(1.0f);
    shader_.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(model));
}

void cord::applyModel2()
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(1.5f, 2.0f, 2.0f));
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(70.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    shader_.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(model));
}

void cord::applyProject()
{
    glm::mat4 projection = glm::perspective(camera_->fov(), 4.0f / 3.0f, 0.1f, 100.0f);
    shader_.setMat4fv("project", 1, GL_FALSE, glm::value_ptr(projection));
}

void cord::applyView()
{
    glm::mat4 view = createCamera();
    shader_.setMat4fv("view", 1, GL_FALSE, glm::value_ptr(view));
}

glm::mat4 cord::createCamera()
{
    return moveCameraWithTime();
}

glm::mat4 cord::moveCameraWithTime()
{
    glm::mat4 view(1.0f);
    float radius(10.0f);
    float camX = radius * std::sin(glfwGetTime());
    float camZ = radius * std::cos(glfwGetTime());
    view = glm::lookAt(glm::vec3(camX, 4.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    return view;
}
