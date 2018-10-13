#ifndef MESH_GENERATOR
#define MESH_GENERATOR
#include <vector>
#include <glm/glm.hpp>

namespace kite
{
   /*
      brief Tool for generating mesh
   */
   class __declspec(dllexport) MeshGenerator
   {
   public:
      MeshGenerator() = default;
   
      static std::vector<glm::vec2> GeneratePatch();
      static std::vector<glm::vec2> GenerateWaterPatch(int patches_);
   };
}
#endif//MESH_GENERATOR