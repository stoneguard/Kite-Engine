#include "engine_p.h"
#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "tools/constants.h"
#include "camera/camera.h"
//entities
#include "entities/atmosphere/Atmosphere.h"
#include "entities/water/water.h"

namespace kite
{
   bool EngineImpl::Init() 
   {
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
      m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Kite-Engine", NULL, NULL);
      if (!m_window)
      {
         glfwTerminate();
         std::cout << "Failed to create GLFW window" << std::endl;
         return false;
      }
   
      //create context
      //WARNING: it is valid only at current dll
      glfwMakeContextCurrent(m_window);
   
      //callback to this class
      glfwSetWindowUserPointer(m_window, this);
      
      //viewport callback
      glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow *win, int w, int h)
      {
         EngineImpl* window = static_cast<EngineImpl*>(glfwGetWindowUserPointer(win));
         window->framebuffer_size_callback(w, h);
      });
      
      //mouse callback
      glfwSetCursorPosCallback(m_window, [](GLFWwindow *win, double xpos, double ypos)
      {
         EngineImpl* window = static_cast<EngineImpl*>(glfwGetWindowUserPointer(win));
         window->mouse_callback(xpos, ypos);
      });
   
      //scroll callback
      glfwSetScrollCallback(m_window, [](GLFWwindow *win, double xpos, double ypos)
      {
         EngineImpl* window = static_cast<EngineImpl*>(glfwGetWindowUserPointer(win));
         window->scroll_callback(xpos, ypos);
      });
   
      // tell GLFW to capture our mouse
      glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   
      //frequency
      glfwSwapInterval(1);
   
      if (gl3wInit() != 0)
      {
         std::cout << "Failed to initialize OpenGL" << std::endl;
         return false;
      }
   
      glEnable(GL_DEPTH_TEST);
      
      // draw in wireframe
      //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      return true;
   }
   
   void EngineImpl::Start()
   {
      while (!glfwWindowShouldClose(m_window))
      {
         // per-frame time logic
         // --------------------
         float currentFrame = static_cast<float>(glfwGetTime());
         m_deltaTime = currentFrame - m_lastFrame;
         m_lastFrame = currentFrame;
   
         // input
         // -----
         processInput(m_window);
   
         // render
         // ------
         glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
         m_renderer.Render();
   
         // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
         // -------------------------------------------------------------------------------
         glfwSwapBuffers(m_window);
         glfwPollEvents();
      }
   
      glfwTerminate();
   }
   
   void EngineImpl::AddEntity(EntityType type_)
   {
      switch (type_)
      {
      case kite::WATER:
         m_renderer.AddEntity(new Water());
         break;
      case kite::ATMOSPHERE:
         m_renderer.AddEntity(new Atmosphere());
         break;
      default:
         break;
      }
   }
   
   I3DEntity* EngineImpl::GetEntity(EntityType type_) const
   {
      return nullptr;
   }
   
   void EngineImpl::framebuffer_size_callback(int width, int height)
   {
      // make sure the viewport matches the new window dimensions; note that width and 
      // height will be significantly larger than specified on retina displays.
      glViewport(0, 0, width, height);
   }
   void EngineImpl::mouse_callback(double xpos, double ypos)
   {
      if (m_firstMouse)
      {
         m_lastX = static_cast<float>(xpos);
         m_lastY = static_cast<float>(ypos);
         m_firstMouse = false;
      }
   
      float xoffset = static_cast<float>(xpos) - m_lastX;
      float yoffset = m_lastY - static_cast<float>(ypos); // reversed since y-coordinates go from bottom to top
   
      m_lastX = static_cast<float>(xpos);
      m_lastY = static_cast<float>(ypos);

      Camera& camera = Camera::Instance();
      camera.ProcessMouseMovement(xoffset, yoffset);
   }
   
   void EngineImpl::scroll_callback(double xoffset, double yoffset)
   {
      Camera& camera = Camera::Instance();
      camera.ProcessMouseScroll(static_cast<float>(yoffset));
   }
   
   void EngineImpl::processInput(GLFWwindow * window)
   {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         glfwSetWindowShouldClose(window, true);

      Camera& camera = Camera::Instance();
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
         camera.ProcessKeyboard(FORWARD, m_deltaTime);//move forward

      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
         camera.ProcessKeyboard(BACKWARD, m_deltaTime);//move backward

      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
         camera.ProcessKeyboard(LEFT, m_deltaTime);////move to the left

      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
         camera.ProcessKeyboard(RIGHT, m_deltaTime);//move to the right
   }
}