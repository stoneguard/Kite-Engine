#include "resource_manager_p.h"

namespace kite
{
   bool ResourceManagerImpl::Initialize(char * path_)
   {
      if (!path_)
         return false;
   
      m_rootPath = std::string(path_);
   
      if (m_rootPath.empty())
         return false;
   
      //relative path to resources
      m_resourcePath = m_rootPath + "/../resource/";
   
      return true;
   }
   
   const char* ResourceManagerImpl::GetResourceDirectory() const
   {
      return m_resourcePath.c_str();
   }
   
   const char* ResourceManagerImpl::GetRootDirectory() const
   {
      return m_rootPath.c_str();
   }
}