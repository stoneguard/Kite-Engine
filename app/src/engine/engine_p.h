#ifndef ENGINE_P_H
#define ENGINE_P_H
#include "engine/types/objects.h"
#include "renderer.h"

struct GLFWwindow;

namespace kite
{
   /*
      \brief Private engine implementation
   */
   class EngineImpl
   {
   public:
      EngineImpl() = default;
   
      //see Engine::Init
      bool Init();
   
      //see Engine::Start
      void Start();
   
      //see Engine::AddEntity
      void AddEntity(EntityType type_);
   
      //see Engine::GetEntity
      I3DEntity* GetEntity(EntityType type_) const;
   
   private:
      EngineImpl(const EngineImpl&) = delete;
      EngineImpl& operator=(const EngineImpl&) = delete;
   
      //handles key-press, mouse move
      void processInput(GLFWwindow *window);
   
      //viewport callback
      void framebuffer_size_callback(int width, int height);
   
      //mouse callback
      void mouse_callback(double xpos, double ypos);
   
      //scroll callback 
      void scroll_callback(double xoffset, double yoffset);
   
   private:
      Renderer       m_renderer;             //renderer, renders entities
      GLFWwindow*    m_window;               //opengl context window
      float          m_lastX = 0.f;          //mouse Xposition for calculating view/proj mat
      float          m_lastY = 0.f;          //mouse Yposition for calculating view/proj mat
      bool           m_firstMouse = true;    //fixing initial mouse-jolt at first launch
      float          m_deltaTime = 0.f;      //time differences between calls (in order to provide same speed at different hardware)
      float          m_lastFrame = 0.f;      //previous time stamp for calculating delta time
   };
}

#endif//ENGINE_P_H