#version 430 core
out vec4 outColor;                  // result color

//light
uniform vec3 lightDir;

//scattering 
uniform float fScale;               // 1 / (fOuterRadius - fInnerRadius)
uniform float fScaleDepth;	         // The scale depth (i.e. the altitude at which the atmosphere's average density is found)
uniform float fInnerRadius;         // The inner (planetary) radius	
uniform float fScaleOverScaleDepth; // fScale / fScaleDepth
uniform vec3 v3InvWavelength;       // 1 / pow(wavelength, 4) for the red, green, and blue channels
uniform float fKr4PI;               // Kr * 4 * PI (Rayleigh)
uniform float fKm4PI;               // Km * 4 * PI (Mie)
uniform float g;                    // The Mie phase asymmetry factor
uniform float g2;                   // squared factor
             
//
uniform vec3 cameraPosition;
in vec3 vertex_posistion;

const float fSamples = 2.0;
const int nSamples = 2;

// scale function
float scale(float fCos)
{
	float x = 1.0 - fCos;
	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

// Calculates the Rayleigh phase function
float getRayleighPhase(float fCos2)
{
	return 0.75 + 0.75*fCos2;
}

void main()
{
   // Get the ray from the camera to the vertex and its length (which
   // is the far point of the ray passing through the atmosphere)
   vec3 v3Ray = (vertex_posistion - cameraPosition);
	float fFar = length(v3Ray);
   v3Ray /= fFar;
   
   //needn't to calculate intersections, since we inside the atmosphere
   
   // Calculate the ray's start and end positions in the atmosphere,
   // then calculate its scattering offset 
   vec3 v3Start = cameraPosition;
   float fHeight = length(v3Start);
   float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
	float fStartAngle = dot(v3Ray, v3Start) / fHeight;
	float fStartOffset = fDepth*scale(fStartAngle);
   
   float fSampleLength = fFar / fSamples;
   float fScaledLength = fSampleLength * fScale;
   vec3 v3SampleRay = v3Ray * fSampleLength;
	vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
   
   //loop through sample points
   vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
   for(int i=0; i<nSamples; i++)
   {
      float fHeight = length(v3SamplePoint);
      float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));

      float fLightAngle = dot(lightDir, v3SamplePoint) / fHeight;
      float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
      float fScatter = (fStartOffset + fDepth * (scale(fLightAngle) - scale(fCameraAngle)));
      vec3 v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
      v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
      v3SamplePoint += v3SampleRay;
	}
   
   //TODO move sun light coef to c++ code
   vec3 frontColor = v3FrontColor * (v3InvWavelength) * 1.20;//rayleigh scattering
   vec3 frontSecondaryColor = v3FrontColor * 1;//mie scattering
   
   //mie scattering function
   vec3 v3Direction = cameraPosition - vertex_posistion;
   float fCos = dot(lightDir, v3Direction) / length(v3Direction);
   float fMiePhase = 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos*fCos) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
   
   //in scattering = mie phase func + rayleight phase func
   vec3 inScattering = frontColor * getRayleighPhase(fCos* fCos) + frontSecondaryColor * fMiePhase;
   
   //high dynamic range
   outColor = vec4(1.0 - exp(-1.0 * inScattering), 1.0f);
}