#include "texture.h"
#include "GL/gl3w.h"
#include <stb_image_aug.h>
#include <iostream>
#include <vector>
#include "SOIL.h"
#include <glm/glm.hpp>
#include "tools/constants.h"

namespace kite
{
   Texture::Texture(char const * path_)
   {
      load(path_);
   }
   
   Texture::Texture(int width, int height)
   {
      //TODO separate class
      allocate();
      m_width = width;
      m_height = height;
   }
   
   Texture::Texture(int width, int height, int levels)
   {
      //TODO separate class
      allocate();
      m_width = width;
      m_height = height;
      //m_format = GL_RGBA32F;
   
      bind();
      allocateStorage2D(levels, GL_RGBA32F);
      unbind();
   }
   
   Texture::~Texture()
   {
      free();
   }
   
   void Texture::allocate()
   {
      glGenTextures(1, &m_id);
   }
   
   void Texture::free()
   {
      glDeleteTextures(1, &m_id);
   }
   
   void Texture::load(char const * path_)
   {
      allocate();
   
      int width, height, nrComponents;
      unsigned char *data = stbi_load(path_, &width, &height, &nrComponents, 0);
      if (data)
      {
         GLenum format;
         if (nrComponents == 1)
            format = GL_RED;
         else if (nrComponents == 3)
            format = GL_RGB;
         else if (nrComponents == 4)
            format = GL_RGBA;
   
         //
         bind();
         
         glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
         glGenerateMipmap(GL_TEXTURE_2D);
   
         //по умолчанию не будет устанавливать фильтры
   
         m_width = width;
         m_height = height;
         m_format = format;
         m_path = path_;
   
         stbi_image_free(data);
         unbind();
      }
      else
      {
         std::cout << "Texture failed to load at path: " << path_ << std::endl;
         stbi_image_free(data);
      }
   }
   
   int Texture::DEBUG_store(const char* filename_)
   {
      bind();
      std::vector< unsigned char > rgbdata(4 * m_width * m_height);
   
      if(m_format != 0)
         glGetTexImage(GL_TEXTURE_2D, 0, m_format, GL_UNSIGNED_BYTE, &rgbdata[0]);
      else
         glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, &rgbdata[0]);
   
      int save_result = stbi_write_bmp(filename_, m_width, m_height, 3, &rgbdata[0]);
      unbind();
   
      return save_result;
   }
   
   int Texture::GetWidth() const
   {
      return m_width;
   }
   
   int Texture::GetHeight() const
   {
      return m_height;
   }
   
   void Texture::bind() const
   {
      glBindTexture(GL_TEXTURE_2D, m_id);
   }
   
   void Texture::unbind() const
   {
      glBindTexture(GL_TEXTURE_2D, 0);
   }
   
   unsigned Texture::GetID() const
   {
      return m_id;
   }
   
   void Texture::noFilter()
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   }
   
   void Texture::bilinearFilter()
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   }
   
   void Texture::trilinearFilter()
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glGenerateMipmap(GL_TEXTURE_2D);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   }
   
   void Texture::allocateStorage2D(int levels, int internalFormat)
   {
      glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, m_width, m_height);
   }
   
   void Texture::allocateImage2D(int internalFormat, int format, int type)
   {
      glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, type, nullptr);
   }
   
   void Texture::clampToEdge()
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   }
   
   std::string Texture::GetPath() const
   {
      return m_path;
   }
}