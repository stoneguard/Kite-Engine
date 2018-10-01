#ifndef APPLICATION_H
#define APPLICATION_H

namespace kite
{
   /*
      \brief Access point to engine
   */
   class Application
   {
   public:
      Application();
   
      bool Init();
      void Launch();
      void AddObject();
   private:
      //TODO engine
   };
}
#endif//APPLICATION_H