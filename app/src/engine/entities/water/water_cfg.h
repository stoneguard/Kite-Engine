#ifndef WATER_CFG_H
#define WATER_CFG_H
#include <glm/glm.hpp>

namespace kite
{
   class WaterConfiguration
   {
   public:
      WaterConfiguration() = default;
   
      void Load(const char* path_);
   
      inline int GetN() const { return m_N; }
      inline int GetL() const { return m_L; }
      inline float GetAmplitude() const { return m_amplitude; }
      inline glm::vec2 GetWindDirection() const { return m_windDirection; }
      inline float GetWindSpeed() const { return m_windSpeed; }
      inline float GetCappilarWavesSuppresion() const { return m_capillarWavesSupression; }
      inline float GetDelta() const { return m_t_delta;  }
      inline bool IsChoppy() const { return m_choppy; }
      inline float GetNormalStrenght() const { return m_normalStrength; }
      inline float GetDisplacementScale() const { return m_displacementScale; }
      inline float GetChoppiness() const { return m_choppiness; }
      inline int GetUvScale() const { return m_uvScale; }
      inline int GetTessellationFactor() const { return m_tessellationFactor; }
      inline float GetTessellationSlope() const { return m_tessellationSlope; }
      inline float GetTessellationShift() const { return m_tessellationShift; }
      inline int GetHighDetailRange() const { return m_highDetailRange; }
      inline float GetDistortion() const { return m_distortion; }
      inline float GetKReflection() const { return m_kReflection; }
      inline float GetKRefraction() const { return m_kRefraction; }
      inline float GetEmission() const { return m_emission; }
      inline float GetSpecular() const { return m_specular; }
      inline float GetMotion() const { return m_waveMotion; }
   
   private:
      int         m_N                           = 0;
      int         m_L                           = 0;
      float       m_amplitude                   = 0.f;
      glm::vec2   m_windDirection;
      float       m_windSpeed                  = 0.f;
      float       m_capillarWavesSupression    = 0.f;
      float       m_motion                     = 0.f;
      float       m_displacementScale          = 0.f;
      float       m_choppiness                 = 0.f;
      int         m_tessellationFactor         = 0;
      float       m_tessellationShift          = 0.f;
      float       m_tessellationSlope          = 0.f;
      int         m_highDetailRange            = 0;
      int         m_uvScale                    = 0;
      float       m_specular                   = 0.f;
      float       m_emission                   = 0.f;
      float       m_kReflection                = 0.f;
      float       m_kRefraction                = 0.f;
      float       m_distortion                 = 0.f;
      float       m_waveMotion                 = 0.f;
      float       m_normalStrength             = 0.f;
      float       m_t_delta                    = 0.f;
      bool        m_choppy                     = false;
   };
}
#endif//WATER_CFG_H
