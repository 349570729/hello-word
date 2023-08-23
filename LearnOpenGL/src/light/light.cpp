#include "light.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

#include "utils.h"
#include "Shader.h"
#include "proc.h"

Light::Light()
    : cubic_shader_(os::curProcDir() + "/light_cubic.vs", os::curProcDir() + "/light_cubic.fs")
    , src_shader_(os::curProcDir() + "/light_src.vs", os::curProcDir() + "/light_src.fs")
{}

void Light::prepare()
{
    const float *cubic_vertex = cubicVertexWithTex();
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
    glBufferData(GL_ARRAY_BUFFER, 180 * sizeof(float), cubic_vertex, GL_STATIC_DRAW);

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

    // set color
    glm::vec3 object_color = {0.2f, 0.3f, 0.5f};
    cubic_shader_.setVec3fv("object_color", 1, glm::value_ptr(object_color));
    glm::vec3 light_color = {1.0f, 1.0f, 1.0f};
    cubic_shader_.setVec3fv("light_color", 1, glm::value_ptr(light_color));
    glm::mat4 model{1.0f};
    model = glm::scale(model, glm::vec3(0.5f));
    cubic_shader_.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(model));
    // model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
    // // scale
    // model = glm::scale(model, glm::vec3(0.3f));
    // src_shader_.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(model));
}

void Light::drawTria(GLFWwindow *window)
{
    glBindVertexArray(VAO);
    cubic_shader_.use();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // src_shader_.use();
    // glDrawArrays(GL_TRIANGLES, 0, 36);
}

Shader *Light::shader()
{
    return &cubic_shader_;
}
