#include "cord_system.h"
#include <iostream>
#include <proc.h>
#include "stb_image.h"
#include "glfw3.h"
#include <glm/gtc/matrix_transform.hpp>

cord::cord()
:shader_(os::curProcDir() + "/cord.vs", os::curProcDir() + "/cord.fs")
{
}

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
    float vertices[] = {
        // 3�����꣬3��������ɫ��2����������
        // front surface
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        // back surface
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        // left surface
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        // right surface
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        // top surface
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        // bottom surface
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
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
    window_ = window;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, box_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, smile_texture);
    shader_.use();
    glBindVertexArray(VAO);
    applyView();
    applyProject();
    applyModel1();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    applyModel2();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cord::setFov(float fov)
{
    fov_ = fov;
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
    glm::mat4 projection = glm::perspective(fov_, 4.0f / 3.0f, 0.1f, 100.0f);
    shader_.setMat4fv("project", 1, GL_FALSE, glm::value_ptr(projection));
}

void cord::applyView()
{
    glm::mat4 view = createCamera();
    shader_.setMat4fv("view", 1, GL_FALSE, glm::value_ptr(view));
}

glm::mat4 cord::createCamera()
{
    return moveCameraWithKeyboard();
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

glm::mat4 cord::moveCameraWithKeyboard()
{
    double xpos, ypos;
    const static glm::vec3 up{0.0f, 1.0f, 0.0f};
    const static glm::vec3 move_front{0.0f, 0.0f, -1.0f};
    const static glm::vec3 move_back{0.0f, 0.0f, 1.0f};
    const static glm::vec3 move_left = glm::normalize(glm::cross(up, move_front));
    const static glm::vec3 move_right = glm::normalize(glm::cross(move_front, up));
    const static float speed_per_ms = 0.01f;
    const static float speed_per_pixel = 0.01f;
    if (first_draw_)
    {
        last_time_ = std::chrono::high_resolution_clock::now();
        glm::mat4 view = glm::lookAt(eye_, glm::vec3(0.0f, 0.0f, 0.0f), up);
        first_draw_ = false;
        return view;
    }
    if (GLFW_PRESS ==  glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT))
    {
        if (first_clicked_)
        {
            glfwGetCursorPos(window_, &last_xpos_, &last_ypos_);
            first_clicked_ = false;
        } else {
            double xpos, ypos;
            glfwGetCursorPos(window_, &xpos, &ypos);
            center_ +=  (float)(xpos - last_xpos_) * speed_per_pixel * move_left;
            center_ +=  (float)(ypos - last_ypos_) * speed_per_pixel * up;
            last_xpos_ = xpos;
            last_ypos_ = ypos;
        }
    } else if (GLFW_RELEASE ==  glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT)) {
        first_clicked_ = true;
    }

    auto time = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time - last_time_);
    last_time_ = time;
    if (GLFW_PRESS == glfwGetKey(window_, GLFW_KEY_W)) {
        eye_ += speed_per_ms * duration_ms.count() * move_front;
    } else if (GLFW_PRESS == glfwGetKey(window_, GLFW_KEY_S)) {
        eye_ += speed_per_ms * duration_ms.count() * move_back;
    } else if (GLFW_PRESS == glfwGetKey(window_, GLFW_KEY_A)) {
        eye_ += speed_per_ms * duration_ms.count() * move_left;
    } else if (GLFW_PRESS == glfwGetKey(window_, GLFW_KEY_D)) {
        eye_ += speed_per_ms * duration_ms.count() * move_right;
    } else if (GLFW_PRESS == glfwGetKey(window_, GLFW_KEY_H)) {
        // reset camera
        eye_ = glm::vec3{0.0f, 4.0f, 10.0f};
        center_ = glm::vec3{0.0f, 0.0f, 0.0f};
        fov_ = 45.0f;
    }
    glm::mat4 view = glm::lookAt(eye_, center_, up);
    return view;
}
