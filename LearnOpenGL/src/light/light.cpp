#include "light.h"
#include "utils.h"

light::light()
    : shader_(os::curProcDir() + "/light.vs", os::curProcDir() + "/light.fs")
{}

void light::beforeLoop()
{
    float *cubic_vertex = cubicVertexWithTex();
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
}

void light::drawTria(GLFWwindow *window)
{
    shader_.use();
    glBindVertexArray(VAO);
    applyProject();
    applyModel1();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    applyModel2();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Shader *light::shader()
{
    return &shader_;
}
