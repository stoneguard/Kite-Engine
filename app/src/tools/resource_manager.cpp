#include "tools/resource_manager.h"
#include "resource_manager_p.h"

namespace kite
{
   ResourceManager& ResourceManager::Instance()
   {
      static ResourceManager inst;
      return inst;
   }
   
   ResourceManager::ResourceManager()
   {
      p = new ResourceManagerImpl();
   }
   
   ResourceManager::~ResourceManager()
   {
      if (p)
      {
         delete p;
         p = nullptr;
      }
   }
   
   bool ResourceManager::Initialize(char* path_)
   {
      return p->Initialize(path_);
   }
   
   const char* ResourceManager::GetResourceDirectory() const
   {
      return p->GetResourceDirectory();
   }
   
   const char* ResourceManager::GetRootDirectory() const
   {
      return p->GetRootDirectory();
   }
}