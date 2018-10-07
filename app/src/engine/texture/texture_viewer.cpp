#include "texture_viewer.h"
#include <GL/gl3w.h>

namespace kite
{
   TextureViewer::TextureViewer()
   {
      // Set up vertex data (and buffer(s)) and attribute pointers
      GLfloat vertices[] = {
         // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
         -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
      };
      GLuint indices[] = {  // Note that we start from 0!
         0, 1, 3, // First Triangle
         1, 2, 3  // Second Triangle
      };


      glGenVertexArrays(1, &m_VAO);
      glGenBuffers(1, &m_VBO);
      glGenBuffers(1, &m_EBO);

      glBindVertexArray(m_VAO);

      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      // Position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(0);
      // Color attribute
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
      glEnableVertexAttribArray(1);
      // TexCoord attribute
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
      glEnableVertexAttribArray(2);

      glBindVertexArray(0); // Unbind VAO
   }

   void TextureViewer::Draw(const Texture& tex_)
   {
      glActiveTexture(GL_TEXTURE0);
      // Bind Texture
      glBindTexture(GL_TEXTURE_2D, tex_.GetID());

      //TODO place shader support here

      glBindVertexArray(m_VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
   }
}