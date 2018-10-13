#include "patchVBO.h"
#include "GL/gl3w.h"

namespace kite
{
   PatchVBO::PatchVBO()
   {
      glGenBuffers(1, &m_VBO);
      glGenVertexArrays(1, &m_VAO);
   }
   
   PatchVBO::~PatchVBO()
   {
      release();
   }
   
   void PatchVBO::allocate(const std::vector<glm::vec2>& vertices_, int patches_)
   {
      m_size = (unsigned)vertices_.size();
   
      glBindVertexArray(m_VAO);
      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   
      glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vertices_[0]), &vertices_[0], GL_STATIC_DRAW);
   
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)0);
      glEnableVertexAttribArray(0);
   
      glPatchParameteri(GL_PATCH_VERTICES, patches_);
   
      glBindVertexArray(0);
   }
   
   void PatchVBO::allocate(const std::vector<glm::vec3>& vertices_)
   {
      m_size = (unsigned)vertices_.size();
   
      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
      glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vertices_[0]), &vertices_[0], GL_STATIC_DRAW);
   
      glBindVertexArray(m_VAO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)0);
      glEnableVertexAttribArray(0);
   
      glBindVertexArray(0);
   }
   
   void PatchVBO::drawPoints() const
   {
      glBindVertexArray(m_VAO);
   
      glEnableVertexAttribArray(0);
   
      glDrawArrays(GL_POINTS, 0, m_size);
   
      glDisableVertexAttribArray(0);
   
      glBindVertexArray(0);
   }
   
   void PatchVBO::draw() const
   {
      glBindVertexArray(m_VAO);
      glDrawArrays(GL_PATCHES, 0, m_size);
      //glDisableVertexAttribArray(0);
      glBindVertexArray(0);
   }
   
   void PatchVBO::release()
   {
      glBindVertexArray(m_VAO);
      glDeleteBuffers(1, &m_VBO);
      glDeleteVertexArrays(1, &m_VAO);
      glBindVertexArray(0);
   }
}