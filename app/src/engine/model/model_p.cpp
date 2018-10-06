#include "model_p.h"
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>
#include "texture/texture.h"
#include "tools/resource_manager.h"

namespace kite
{
   ModelImpl::~ModelImpl()
   {
      for (auto& mesh : m_meshes)
      {
         delete mesh;
         mesh = nullptr;
      }
   }
   
   void ModelImpl::loadModel(const std::string& path_)
   {
      Assimp::Importer importer;
      const aiScene *scene = importer.ReadFile(path_, aiProcess_Triangulate | aiProcess_FlipUVs/* | aiProcess_GenNormals */);
   
      if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
      {
         std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
         return;
      }
      processNode(scene->mRootNode, scene);
   }
   
   void ModelImpl::processNode(aiNode *node, const aiScene *scene)
   {
      //process all meshes
      for (unsigned int i = 0; i < node->mNumMeshes; i++)
      {
         aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
         m_meshes.emplace_back(processMesh(mesh, scene));
      }

      //process all nodes
      for (unsigned int i = 0; i < node->mNumChildren; i++)
      {
         processNode(node->mChildren[i], scene);
      }
   }
   
   Mesh* ModelImpl::processMesh(aiMesh *mesh, const aiScene *scene)
   {
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;
      std::vector<Texture*> textures;
   
      for (unsigned int i = 0; i < mesh->mNumVertices; i++)
      {
         Vertex vertex;
         // обработка координат, нормалей и текстурных координат вершин
         glm::vec3 vector;
   
         //vertex
         vector.x = mesh->mVertices[i].x;
         vector.y = mesh->mVertices[i].y;
         vector.z = mesh->mVertices[i].z;
         vertex.Position = vector;
   
         //normal
         vector.x = mesh->mNormals[i].x;
         vector.y = mesh->mNormals[i].y;
         vector.z = mesh->mNormals[i].z;
         vertex.Normal = vector;
   
         //tex coords
         if (mesh->mTextureCoords[0]) // does the mesh have tex coords?
         {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
         }
         else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
   
         vertices.push_back(vertex);
      }
   
      //indexes process
      for (unsigned int i = 0; i < mesh->mNumFaces; i++)
      {
         aiFace face = mesh->mFaces[i];
         for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
      }
   
      //material process
      if (mesh->mMaterialIndex >= 0)
      {
         //diffuse material
         aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
         std::vector<Texture*> diffuseMaps = loadMaterialTextures(material,
            aiTextureType_DIFFUSE, "texture_diffuse");
         textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
   
         //normal maps material
         std::vector<Texture*> normalsMaps = loadMaterialTextures(material,
            aiTextureType_NORMALS, "texture_normals");
         textures.insert(textures.end(), normalsMaps.begin(), normalsMaps.end());
   
         std::vector<Texture*> specularMaps = loadMaterialTextures(material,
            aiTextureType_SPECULAR, "texture_specular");
         textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
      }
   
      return new Mesh(vertices, indices, textures);
   }
   
   std::vector<Texture*> ModelImpl::loadMaterialTextures(aiMaterial* const mat_, const aiTextureType type_, const std::string& typeName_)
   {
      std::vector<Texture*> textures;
   
      for (unsigned int i = 0; i < mat_->GetTextureCount(type_); i++)
      {
         aiString str;
         mat_->GetTexture(type_, i, &str);
         bool skip = false;
         for (unsigned int j = 0; j < m_loaded_textures.size(); j++)
         {
            if (std::strcmp(m_loaded_textures[j]->GetPath().c_str(), str.C_Str()) == 0)
            {
               textures.emplace_back(m_loaded_textures[j]);
               skip = true;
               break;
            }
         }
         if (!skip)
         {   
            //if model hasn't been loaded, do it
            std::string path = "models/" + std::string(str.C_Str());
            Texture* texture = new Texture(_R(path));//dynamicly allocated in order to keep texture alive during whole programm cycle

            //store loaded texture
            textures.emplace_back(texture);
            
            //TODO
            m_loaded_textures.emplace_back(texture);
         }
      }
      return std::move(textures);
   }
   
   
   void ModelImpl::Draw()
   {
      for (unsigned int i = 0; i < m_meshes.size(); i++)
         m_meshes[i]->Draw();
   }
   
   void ModelImpl::SetTranslation(const glm::vec3& translation_)
   {
      m_transform.SetTranslation(translation_);
   }
   
   void ModelImpl::SetScale(const glm::vec3& scale_)
   {
      m_transform.SetScaling(scale_);
   }
   
   void ModelImpl::SetRotation(const glm::vec3& rotation_)
   {
      m_transform.SetRotation(rotation_);
   }
   
   glm::mat4 ModelImpl::GetWorldMatrix() const
   {
      return m_transform.GetWorldMatrix();
   }
}