#ifndef MODEL_P_H
#define MODEL_P_H
#include <assimp/material.h>
#include "tools/transform.h"
#include <vector>

struct aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;

namespace kite
{
   class Mesh;
   class Texture;

   /*
      \brief private implementaion of 3d model

      \see Model
   */
   class ModelImpl
   {
   public:
      ModelImpl() = default;
      ~ModelImpl();
   
      void Draw();
      void loadModel(const std::string& path);
   
      void SetTranslation(const glm::vec3& translation_);
      void SetScale(const glm::vec3& scale_);
      void SetRotation(const glm::vec3& rotation_);
   
      glm::mat4 ModelImpl::GetWorldMatrix() const;
   private:
      ModelImpl(const ModelImpl& rhs_) = delete;
      ModelImpl& operator=(const ModelImpl& rhs_) = delete;
    
      //Since 3d model include tree of nodes, we need to walk through these tree and process each node. Each node has mesh -> see process mesh
      void processNode(aiNode *node, const aiScene *scene);

      //Extract vertex data, normals and textures coords from mesh (within node)
      Mesh* processMesh(aiMesh *mesh, const aiScene *scene);

      //
      std::vector<Texture*> loadMaterialTextures(aiMaterial* const mat, const aiTextureType type, const std::string& typeName);
   private:
      std::vector<Mesh*>           m_meshes;            //model consists of several separate meshes
      std::vector<Texture*>        m_loaded_textures;   //if exists, textures for model
      Transform                    m_transform;         //world transform
   };
}
#endif//MODEL_P_H