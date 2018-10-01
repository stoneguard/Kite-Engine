#include "application.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include "tools/resource_manager.h"

///
using namespace kite;

void printHelp()
{
   std::cout << "\tUsage: kite --root [path]" << std::endl;
}

char* ParseArguments(int argc, char** arguments)
{
   char* path = nullptr;
   /*
      [0] - "kite"
      [1] - "--root"
      [2] - "path"
   */
   if (argc == 3)
   {
      if (strcmp(arguments[1], "--root") == 0)
      {
         struct stat info;

         char* priorPath = arguments[2];
         if (stat(priorPath, &info) != 0)
            printf("cannot access %s\n", priorPath);
         else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
         {
            //printf("%s is a directory\n", priorPath);
            return priorPath;
         }
         else
         {
            std::cout << "it is not a directory" << std::endl;
            return nullptr;
            //printf("%s is no directory\n", priorPath);
         }
      }
      else
      {
         std::cout << "no argument \'--root\' found" << std::endl;
         return nullptr;
      }
   }
   else
   {
      std::cout << "Invalid number of arguments" << std::endl;
      return nullptr;
   }

   return nullptr;
}

int main(int argc, char* argv[])
{
   char* rootPath = ParseArguments(argc, argv);
   if (!rootPath)
   {
      printHelp();
      return -1;
   }

   //init resource mgr
   ResourceManager& resMgr = ResourceManager::Instance();
   if (!resMgr.Initialize(rootPath))
   {
      std::cout << "Cannot initialize resource manager" << std::endl;
      printHelp();
      return -1;
   }

   Application instance;
   if (instance.Init())
   {
      //TODO add objects

      instance.Launch();
   }
   else
   {
      return -1;
   }

   return 0;
}
