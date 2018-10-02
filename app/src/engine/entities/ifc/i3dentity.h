#ifndef ENTITY_H
#define ENTITY_H

namespace kite
{
   /*
      \brief Base interface class for rendered entities
   */
   class __declspec(dllexport) I3DEntity
   {
   public:
      virtual ~I3DEntity() = default;
      
      //
      virtual void Render() = 0;
   };
}

#endif//ENTITY_H
