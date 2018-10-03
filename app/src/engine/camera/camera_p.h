#ifndef CAMERA_P_H
#define CAMERA_P_H
#include "GL/gl3w.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera/camera.h"
#include <vector>

namespace kite
{
   class CameraImpl
   {
   public:
      CameraImpl(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
      CameraImpl(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
   
      //Returns the view matrix calculated using Eular Angles and the LookAt Matrix
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
      CameraImpl(const CameraImpl& rhs_) = delete;
      CameraImpl& operator=(const CameraImpl& rhs_) = delete;
   
      //update vector values according to yaw and pitch
      void updateCameraVectors();
   
      //init frustum planes from proj matix
      void initFrustumPlanes();

   private:
      glm::vec3                  m_position;                //current camera postion
      glm::vec3                  m_prev_position;           //previos camera postion (provide movement detection) 
      std::vector<glm::vec4>     m_frustumPlanes;           //frustum planes provided by projmatrix
      glm::vec3                  m_front;                   //forward vector
      glm::vec3                  m_up;                      //up vector
      glm::vec3                  m_right;                   //right vector
      glm::vec3                  m_worldUp;                 //TODO

      // Eular Angles
      GLfloat                    m_yaw = 0.f;               //Y axis rotation
      GLfloat                    m_pitch = 0.f;             //X axis rotation  

      // Camera options
      GLfloat                    m_movementSpeed = 0.f;     //speed of camera
      GLfloat                    m_mouseSensitivity = 0.f;  //level of sensitivity of camera
      GLfloat                    m_zoom = 0.f;              //zoom level
      bool                       m_isMoved = false;         //state of movement
   };
}
#endif//CAMERA_P_H