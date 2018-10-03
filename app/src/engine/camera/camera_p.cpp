#include "camera_p.h"
#include "tools/constants.h"
#include <cmath>

namespace kite
{
   CameraImpl::CameraImpl(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) :
      m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVTY), m_zoom(ZOOM)
   {
      m_position = position;
      m_worldUp = up;
      m_yaw = yaw;
      m_pitch = pitch;
      updateCameraVectors();
   
      m_prev_position = m_position;
   
      //
      m_frustumPlanes.resize(6);
      initFrustumPlanes();
   }
   
   CameraImpl::CameraImpl(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
      m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVTY), m_zoom(ZOOM)
   {
      m_position = glm::vec3(posX, posY, posZ);
      m_worldUp = glm::vec3(upX, upY, upZ);
      m_yaw = yaw;
      m_pitch = pitch;
      updateCameraVectors();
   
      m_prev_position = m_position;
   
      initFrustumPlanes();
   }
   
   glm::vec4 normalizePlane(const glm::vec4& plane)
   {
      glm::vec4 normalized;
      float mag;
      mag = (float)std::sqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z);
      normalized.x = (plane.x / mag);
      normalized.y = (plane.y / mag);
      normalized.z = (plane.z / mag);
      normalized.w = (plane.w / mag);
   
      return normalized;
   }
   
   void CameraImpl::initFrustumPlanes()
   {
      // ax * bx * cx +  d = 0; store a,b,c,d
      const glm::mat4& projMat = GetProjMatrix();
      
      //left plane
      glm::vec4 leftPlane = glm::vec4(
         projMat[3][0] + projMat[0][0] * ((float)std::tan(glm::radians(m_zoom / 2)) * ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)),
         projMat[3][1] + projMat[0][1],
         projMat[3][2] + projMat[0][2],
         projMat[3][3] + projMat[0][3]);
   
      m_frustumPlanes[0] = normalizePlane(leftPlane);
   
      //right plane
      glm::vec4 rightPlane = glm::vec4(
         projMat[3][0] - projMat[0][0] * ((float)std::tan(glm::radians(m_zoom / 2)) * ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)),
         projMat[3][1] - projMat[0][1],
         projMat[3][2] - projMat[0][2],
         projMat[3][3] - projMat[0][3]);
   
      m_frustumPlanes[1] = normalizePlane(rightPlane);
   
      //bot plane
      glm::vec4 botPlane = glm::vec4(
         projMat[3][0] + projMat[1][0],
         projMat[3][1] + projMat[1][1] * (float)std::tan(glm::radians(m_zoom / 2)),
         projMat[3][2] + projMat[1][2],
         projMat[3][3] + projMat[1][3]);
   
      m_frustumPlanes[2] = normalizePlane(botPlane);
   
      //top plane
      glm::vec4 topPlane = glm::vec4(
         projMat[3][0] - projMat[1][0],
         projMat[3][1] - projMat[1][1] * (float)std::tan(glm::radians(m_zoom / 2)),
         projMat[3][2] - projMat[1][2],
         projMat[3][3] - projMat[1][3]);
   
      m_frustumPlanes[3] = normalizePlane(topPlane);
   
      //near plane
      glm::vec4 nearPlane = glm::vec4(
         projMat[3][0] + projMat[2][0],
         projMat[3][1] + projMat[2][1],
         projMat[3][2] + projMat[2][2],
         projMat[3][3] + projMat[2][3]);
   
      m_frustumPlanes[4] = normalizePlane(nearPlane);
   
      //far plane
      glm::vec4 farPlane = glm::vec4(
         projMat[3][0] - projMat[2][0],
         projMat[3][1] - projMat[2][1],
         projMat[3][2] - projMat[2][2],
         projMat[3][3] - projMat[2][3]);
   
      m_frustumPlanes[5] = normalizePlane(farPlane);
   }
   
   //Returns the view matrix calculated using Eular Angles and the LookAt Matrix
   glm::mat4 CameraImpl::GetViewMatrix() const
   {
      return glm::lookAt(m_position, m_position + m_front, m_up);
   }
   
   // returns projMatrix
   glm::mat4 CameraImpl::GetProjMatrix() const
   {
      return glm::perspective(glm::radians(m_zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, ZNEAR, ZFAR);
   }
   
   bool CameraImpl::IsMoved() const
   {
      return m_prev_position != m_position;
   }
   
   void CameraImpl::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
   {
      m_prev_position = m_position;
   
      GLfloat velocity = m_movementSpeed * deltaTime;
      if (direction == FORWARD)
         m_position += m_front * velocity;
      if (direction == BACKWARD)
         m_position -= m_front * velocity;
      if (direction == LEFT)
         m_position -= m_right * velocity;
      if (direction == RIGHT)
         m_position += m_right * velocity;
   }
   
   
   // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
   void CameraImpl::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch/* = true*/)
   {
      xoffset *= m_mouseSensitivity;
      yoffset *= m_mouseSensitivity;
   
      m_yaw += xoffset;
      m_pitch += yoffset;
   
      // Make sure that when pitch is out of bounds, screen doesn't get flipped
      if (constrainPitch)
      {
         if (m_pitch > 89.0f)
            m_pitch = 89.0f;
         if (m_pitch < -89.0f)
            m_pitch = -89.0f;
      }
   
      updateCameraVectors();
   }
   
   // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
   void CameraImpl::ProcessMouseScroll(GLfloat yoffset)
   {
      if (m_zoom >= 1.0f && m_zoom <= 45.0f)
         m_zoom -= yoffset;
      if (m_zoom <= 1.0f)
         m_zoom = 1.0f;
      if (m_zoom >= 45.0f)
         m_zoom = 45.0f;
   }
   
   glm::vec3 CameraImpl::GetPosition() const
   {
      return m_position;
   }
   
   void CameraImpl::SetPosition(const glm::vec3& pos_)
   {
      m_position = pos_;
   }
   
   const std::vector<glm::vec4>& CameraImpl::GetFrustums() const
   {
      return m_frustumPlanes;
   }
   
   void CameraImpl::updateCameraVectors()
   {
      // Calculate the new m_front vector
      glm::vec3 front;
      front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
      front.y = sin(glm::radians(m_pitch));
      front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
      m_front = glm::normalize(front);
      // Also re-calculate the m_right and m_up vector
      m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
      m_up = glm::normalize(glm::cross(m_right, m_front));
   }
}