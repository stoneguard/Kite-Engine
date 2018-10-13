#include "tools/mesh_generator.h"

namespace kite
{
   std::vector<glm::vec2> MeshGenerator::GeneratePatch()
   {
      std::vector<glm::vec2> vertices;
      vertices.resize(16);
   
      unsigned counter = 0;
   
      vertices[counter++] = glm::vec2(0.0f, 0.0f);
      vertices[counter++] = glm::vec2(0.333f, 0.0f);
      vertices[counter++] = glm::vec2(0.666f, 0.0f);
      vertices[counter++] = glm::vec2(1.f, 0.0f);
   
      vertices[counter++] = glm::vec2(0.0f, 0.333f);
      vertices[counter++] = glm::vec2(0.333f, 0.333f);
      vertices[counter++] = glm::vec2(0.666f, 0.333f);
      vertices[counter++] = glm::vec2(1.f, 0.333f);
   
      vertices[counter++] = glm::vec2(0.0f, 0.666f);
      vertices[counter++] = glm::vec2(0.333f, 0.666f);
      vertices[counter++] = glm::vec2(0.666f, 0.666f);
      vertices[counter++] = glm::vec2(1.f, 0.666f);
   
      vertices[counter++] = glm::vec2(0.0f, 1.0f);
      vertices[counter++] = glm::vec2(0.333f, 1.0f);
      vertices[counter++] = glm::vec2(0.666f, 1.0f);
      vertices[counter++] = glm::vec2(1.f, 1.0f);
   
      return vertices;
   }
   
   std::vector<glm::vec2> MeshGenerator::GenerateWaterPatch(int patches_)
   {
      int amountx = patches_;
      int amounty = patches_;
   
      // 16 vertices for each patch
      std::vector<glm::vec2> vertices;
      vertices.resize(amountx * amounty * 16);
   
      int index = 0;
      float dx = 1.f / amountx;
      float dy = 1.f / amounty;
   
      for (float i = 0; i<1.f; i += dx)
      {
         for (float j = 0; j<1.f; j += dy)
         {
            vertices[index++] = glm::vec2(i,j);
            vertices[index++] = glm::vec2(i + dx*0.33f,j);
            vertices[index++] = glm::vec2(i + dx*0.66f,j);
            vertices[index++] = glm::vec2(i + dx,j);
   
            vertices[index++] = glm::vec2(i,j + dy*0.33f);
            vertices[index++] = glm::vec2(i + dx*0.33f,j + dy*0.33f);
            vertices[index++] = glm::vec2(i + dx*0.66f,j + dy*0.33f);
            vertices[index++] = glm::vec2(i + dx,j + dy*0.33f);
   
            vertices[index++] = glm::vec2(i,j + dy*0.66f);
            vertices[index++] = glm::vec2(i + dx*0.33f,j + dy*0.66f);
            vertices[index++] = glm::vec2(i + dx*0.66f,j + dy*0.66f);
            vertices[index++] = glm::vec2(i + dx,j + dy*0.66f);
   
            vertices[index++] = glm::vec2(i,j + dy);
            vertices[index++] = glm::vec2(i + dx*0.33f,j + dy);
            vertices[index++] = glm::vec2(i + dx*0.66f,j + dy);
            vertices[index++] = glm::vec2(i + dx,j + dy);
         }
      }
   
      return vertices;
   }
}