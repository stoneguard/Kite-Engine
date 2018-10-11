#ifndef WATER_H_P
#define WATER_H_P

namespace kite
{
   /*
      \brief Private implementation of dynamic water model
   */
   class WaterImpl
   {
   public:
      WaterImpl();

      void Render();
   private:
      class BaseShader*    m_shader = nullptr;//should be able to switch to wireframe and back
   };
}

#endif//WATER_H_P