#include "water_cfg.h"
#include "pugixml.hpp"

namespace kite
{
   void WaterConfiguration::Load(const char * path_)
   {
      pugi::xml_document doc;
      pugi::xml_parse_result result = doc.load_file(path_);
   
      if (!result)
         return;
   
      m_choppy = doc.child("root").child("water").child("choppy").attribute("value").as_bool();
      m_displacementScale = doc.child("root").child("water").child("displacementScale").attribute("value").as_float();
      m_choppiness = doc.child("root").child("water").child("choppiness").attribute("value").as_float();
      m_distortion = doc.child("root").child("water").child("distortion").attribute("value").as_float();
      m_waveMotion = doc.child("root").child("water").child("wavemotion").attribute("value").as_float();
      m_uvScale = doc.child("root").child("water").child("uvScale").attribute("value").as_int();
      m_tessellationFactor = doc.child("root").child("water").child("tessellationFactor").attribute("value").as_int();
      m_tessellationSlope = doc.child("root").child("water").child("tessellationSlope").attribute("value").as_float();
      m_tessellationShift = doc.child("root").child("water").child("tessellationShift").attribute("value").as_float();
      m_highDetailRange = doc.child("root").child("water").child("highDetailRange").attribute("value").as_int();
      m_specular = doc.child("root").child("water").child("specular").attribute("value").as_float();
      m_emission = doc.child("root").child("water").child("emission").attribute("value").as_float();
      m_kReflection = doc.child("root").child("water").child("kReflection").attribute("value").as_float();
      m_kRefraction = doc.child("root").child("water").child("kRefraction").attribute("value").as_float();
      m_normalStrength = doc.child("root").child("water").child("normalStrength").attribute("value").as_float();
   
      //wind
      m_windDirection = glm::vec2(doc.child("root").child("water").child("wind").child("X").attribute("value").as_float(),
                                 doc.child("root").child("water").child("wind").child("Y").attribute("value").as_float());
      m_windDirection = glm::normalize(m_windDirection);
      m_windSpeed = doc.child("root").child("water").child("wind").child("speed").attribute("value").as_float();
   
      //FFT
      m_N = doc.child("root").child("water").child("fft").child("resolution").attribute("value").as_int();
      m_L = doc.child("root").child("water").child("fft").child("L").attribute("value").as_int();
      m_amplitude = doc.child("root").child("water").child("fft").child("amplitude").attribute("value").as_float();
      m_capillarWavesSupression = doc.child("root").child("water").child("fft").child("capillarwavesSuppression").attribute("value").as_float();
      m_t_delta = doc.child("root").child("water").child("t_delta").attribute("value").as_float();
   }
}