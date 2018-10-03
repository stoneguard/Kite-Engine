#ifndef CAMERA_H
#define CAMERA_H

#include "GL/gl3w.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace kite
{
   // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
   enum Camera_Movement {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT
   };
   
   // Default camera values
   const GLfloat YAW = -90.0f;
   const GLfloat PITCH = 0.0f;
   const GLfloat SPEED = 500.f;
   const GLfloat SENSITIVTY = 0.25f;
   const GLfloat ZOOM = 45.0f;
   
   /*
      \brief A camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
   */
   class Camera
   {
   public:
      static Camera& Camera::Instance();
   
      // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
      glm::mat4 GetViewMatrix() const;
   
      // returns projMatrix
      glm::mat4 GetProjMatrix() const;
   
      //returns true if camera's been moved
      bool IsMoved() const;
   
      // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
      void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
   
      // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
      void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
      
      // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
      void ProcessMouseScroll(GLfloat yoffset);
   
      // Get current position of the camera
      glm::vec3 GetPosition() const;
   
      // Set current position of the camera
      void SetPosition(const glm::vec3& pos_);
   
      // Get frustum, provided by proj matrix
      const std::vector<glm::vec4>& GetFrustums() const;
   
   private:
      Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
      Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
      ~Camera();
   
      Camera(Camera const&) = delete;
      Camera& operator= (Camera const&) = delete;
   
      class CameraImpl* p;//private impl
   };
}
#endif//CAMERA_H