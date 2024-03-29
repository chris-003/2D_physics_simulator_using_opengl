#if 0

#include "RenderText.h"
#include "Application.h"
#include "ShaderProgram.h"
#include <glm/vec4.hpp>
#include <iostream>
#include <string>

namespace engine {
namespace renderText {
Characters defaultCharacters;

void RenderText(ShaderProgram &s, const std::string &text, GLfloat x, GLfloat y,
                GLfloat scale, const glm::vec4 &color) {
#error
    // 激活对应的渲染状态
    // s.Use();
    glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y,
                color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // 遍历文本中所有的字符
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // 对每个字符更新VBO
        GLfloat vertices[6][4] = {
            {xpos, ypos + h, 0.0, 0.0},    {xpos, ypos, 0.0, 1.0},
            {xpos + w, ypos, 1.0, 1.0},

            {xpos, ypos + h, 0.0, 0.0},    {xpos + w, ypos, 1.0, 1.0},
            {xpos + w, ypos + h, 1.0, 0.0}};
        // 在四边形上绘制字形纹理
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // 更新VBO内存的内容
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // 绘制四边形
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // 更新位置到下一个字形的原点，注意单位是1/64像素
        x += (ch.Advance >> 6) *
             scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
} // namespace renderText
} // namespace engine

#endif