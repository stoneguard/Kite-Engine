#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

namespace kite
{
   /*
      \brief Represents texture loaded from hdd to gpu memory
   */
   class Texture
   {
   public:
      Texture() = default;
      Texture(char const * path_);
      Texture(int width, int height, int levels);
      Texture(int width, int height);
      ~Texture();
   
      //get width
      int GetWidth() const;
   
      //get height
      int GetHeight() const;
   
      //apply default filter = nearest
      void noFilter();
   
      //apply filter = linear
      void bilinearFilter();
   
      //apply filter = mipmap linear
      void trilinearFilter();
   
      //bind to texture located at gpu
      void bind() const;
   
      //unbind from texture located at gpu
      void unbind() const;
   
      //get id of allocated resource(texture)
      unsigned GetID() const;
   
      //apply 2D storage
      void allocateStorage2D(int levels, int internalFormat);
   
      //apply texImage
      void allocateImage2D(int internalFormat, int format, int type);
   
      //apply clamp to edge
      void clampToEdge();
   
      //get path of texture (on hdd)
      std::string GetPath() const;
   
      //save image to hdd [DEBUG]
      int DEBUG_store(const char* filename_);
   
   private:
      //allocate gpu resource
      void allocate();

      //release gpu resource
      void free();
   
      //load file from hdd
      void load(char const* path_);
   
   private:
      unsigned       m_id = 0;      //internal gpu id
      int            m_width = 0;   //width of image
      int            m_height = 0;  //height of image
      unsigned       m_format = 0;  //format of image
      std::string    m_path;        //full path of image
   };
}


#endif//TEXTURE_H
