#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <string>

#define _P(path) std::string(std::string(ResourceManager::Instance().GetRootDirectory()) + std::string(path)).c_str()
#define _R(path) std::string(std::string(ResourceManager::Instance().GetResourceDirectory()) + std::string(path)).c_str()

namespace kite
{
   /*
      Resource manager(RM) helps get resource directories and get access to root folder.
   */
   class __declspec(dllexport) ResourceManager
   {
   private:
      ResourceManager();
      ~ResourceManager();

      ResourceManager(ResourceManager const&) = delete;
      ResourceManager& operator= (ResourceManager const&) = delete;

   public:
      static ResourceManager& Instance();

      //Init RM with root path from arguments
      bool Initialize(char* path_);

      //
      const char* GetRootDirectory() const;
      
      //
      const char* GetResourceDirectory() const;

   private:
      class ResourceManagerImpl* p;
   };
}
#endif//RESOURCE_MANAGER_H