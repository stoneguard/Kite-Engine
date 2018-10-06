#include "model/model.h"
#include <iostream>
#include "GL/gl3w.h"
#include <glm/glm.hpp>
#include "model_p.h"

namespace kite
{
   Model::Model(const char* path_)
   {
      p = new ModelImpl();
      p->loadModel(path_);
   }
   
   Model::~Model()
   {
      if (p)
      {
         delete p;
         p = nullptr;
      }
   }
   
   void Model::Draw()
   {
      p->Draw();
   }
   
   void Model::SetTranslation(const glm::vec3& translation_)
   {
      p->SetTranslation(translation_);
   }
   
   void Model::SetScale(const glm::vec3& scale_)
   {
      p->SetScale(scale_);
   }
   
   void Model::SetRotation(const glm::vec3& rotation_)
   {
      p->SetRotation(rotation_);
   }
   
   glm::mat4 Model::GetWorldMatrix() const
   {
      return p->GetWorldMatrix();
   }
}