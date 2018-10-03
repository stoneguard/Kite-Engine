#include "camera/camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "tools/constants.h"
#include "camera_p.h"

namespace kite
{
   Camera& Camera::Instance()
   {
      static Camera inst(glm::vec3(0.0f, 0.0f, 0.0f));
      return inst;
   }
   
   // Constructor with vectors
   Camera::Camera(glm::vec3 position/* = glm::vec3(0.0f, 0.0f, 0.0f)*/, glm::vec3 up/* = glm::vec3(0.0f, 1.0f, 0.0f)*/, GLfloat yaw /*= YAW*/, GLfloat pitch/* = PITCH*/) 
   {
      p = new CameraImpl(position, up, yaw, pitch);
   }
   
   // Constructor with scalar values
   Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) 
   {
      p = new CameraImpl(posX, posY, posZ, upX, upY, upZ, yaw, pitch);
   }
   
   Camera::~Camera()
   {
      if (p)
      {
         delete p;
         p = nullptr;
      }
   }
   
   glm::mat4 Camera::GetProjMatrix() const
   {
      return p->GetProjMatrix();
   }
   
   glm::mat4 Camera::GetViewMatrix() const
   {
      return p->GetViewMatrix();
   }
   
   bool Camera::IsMoved() const
   {
      return p->IsMoved();
   }
   
   void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
   {
      p->ProcessKeyboard(direction, deltaTime);
   }
   
   void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch/* = true*/)
   {
      p->ProcessMouseMovement(xoffset, yoffset, constrainPitch);
   }
   
   void Camera::ProcessMouseScroll(GLfloat yoffset)
   {
      p->ProcessMouseScroll(yoffset);
   }
   
   glm::vec3 Camera::GetPosition() const
   {
      return p->GetPosition();
   }
   
   void Camera::SetPosition(const glm::vec3& pos_)
   {
      p->SetPosition(pos_);
   }
   
   const std::vector<glm::vec4>& Camera::GetFrustums() const
   {
      return p->GetFrustums();
   }
}