#include "mesh.h"

namespace kite
{
   Mesh::Mesh(const std::vector<Vertex>& vertices_, const std::vector<unsigned int>& indices_, const std::vector<Texture*>& textures_)
   {
      m_vertices.assign(vertices_.begin(), vertices_.end());
      m_indices.assign(indices_.begin(), indices_.end());
      m_textures.assign(textures_.begin(), textures_.end());
   
      allocate();
   }
   
   Mesh::~Mesh()
   {
      release();
   
      for (auto& texture : m_textures)
      {
         delete texture;
         texture = nullptr;
      }
   }
   
   void Mesh::allocate()
   {
      glGenVertexArrays(1, &m_VAO);
      glGenBuffers(1, &m_VBO);
      glGenBuffers(1, &m_EBO);
   
      glBindVertexArray(m_VAO);
      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   
      glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
   
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
         &m_indices[0], GL_STATIC_DRAW);
   
      // vertex positions
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
   
      // vertex normals
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
   
      // vertex texture coords
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
   
      glBindVertexArray(0);
   }
   
   void Mesh::release()
   {
      glBindVertexArray(m_VAO);
      glDeleteBuffers(1, &m_VBO);
      glDeleteVertexArrays(1, &m_VAO);
      glBindVertexArray(0);
   }
   
   void Mesh::Draw()
   {
      glFrontFace(GL_CW);//render inside only
   
      glBindVertexArray(m_VAO);
      glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
   
      glFrontFace(GL_CCW);
      glBindVertexArray(0);
   }
}