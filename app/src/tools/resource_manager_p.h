#ifndef RESOURCE_MANAGER_P_H
#define RESOURCE_MANAGER_P_H
#include <string>

namespace kite
{
   /*
      \brief private implementation of RM
   */
   class ResourceManagerImpl
   {
   public:
      ResourceManagerImpl() = default;
   
      //Init RM with root path from arguments
      bool Initialize(char* path_);
   
      //
      const char* GetResourceDirectory() const;
   
      //
      const char* GetRootDirectory() const;
      
   private:
      ResourceManagerImpl(const ResourceManagerImpl&) = delete;
      ResourceManagerImpl& operator=(const ResourceManagerImpl&) = delete;
   
   private:
      std::string m_rootPath;       
      std::string m_resourcePath;   
   };
}

#endif//RESOURCE_MANAGER_P_H