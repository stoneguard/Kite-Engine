#ifndef MODEL_H
#define MODEL_H
#include <glm/glm.hpp>

namespace kite
{
   /*
      \brief Represents 3d model loaded from HDD.
      Supported formates: 
         *obj
         *dae
   */
   class Model
   {
   public:
      //path to model
      Model(const char* path);
      ~Model();
      
      //
      void Draw();

      void SetTranslation(const glm::vec3& translation_);
      void SetScale(const glm::vec3& scale_);
      void SetRotation(const glm::vec3& rotation_);
   
      glm::mat4 GetWorldMatrix() const;
   private:
      class ModelImpl* p;//private impl
   };
}
#endif//MODEL_H