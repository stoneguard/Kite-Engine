#ifndef HKT_H
#define HKT_H
#include "texture/texture.h"

namespace kite
{
   class HktShader;
   
   /*
      \brief Time depended equation, which produce necessary factors at each dimension, in order to provide properly generated heightmaps of ocean waves
   */
   class Hkt
   {
   public:
      Hkt(int N, int L);
      ~Hkt();
   
      //need to pass evaluated texture from h0k
      void SetH0K(const Texture& tex_);
   
      //need to pass evaluated texture from h0k
      void SetH0MinusK(const Texture& tex_);
   
      const Texture& GetImageDyCoeficcients() const;
   
      const Texture& GetImageDxCoeficcients() const;
   
      const Texture& GetImageDzCoeficcients() const;
   
      //Since it is time depended, renders the frame at time t
      void Render(float t);
   
   private:
      //result of equation calculation stores at texures(according to each dimension)
      Texture     m_imageDyCoefficients;
      Texture     m_imageDxCoefficients;
      Texture     m_imageDzCoefficients;
   
      //should be evaluated at h0k. Part of initial equation
      Texture     m_imageH0k;             
      Texture     m_imageH0minusK;        
   
      int         m_N = 0;
      int         m_L = 0;
      HktShader*  m_shader;
   };
}
#endif//HKT_H
