#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace kite
{
   const float M_PI = 3.14159265358979323846f;
   const float SPHERE_RADIUS = 5000.f;          //radius of the "earth"
   
   //atmospheric scattering
   const float INNER_RADIUS = 0.1f;
   const float OUTER_RADIUS = SPHERE_RADIUS;
   const float K_R = 0.0025f;		               // Rayleigh scattering constant;
   const float K_M = 0.0010f;		               // Mie scattering constant;
   const float K_R_4PI = K_R*4.0f*M_PI;
   const float K_M_4PI = K_M*4.0f*M_PI;
   const float RAYLEIGHT_SCALE_DEPTH = 0.1f;
   const float G = -0.880f;		               // The Mie phase asymmetry factor
   //wave lenghts
   const float RED_WAVE_LENGHT = 0.650f;		   // 650 nm for red
   const float GREEN_WAVE_LENGHT = 0.570f;      // 570 nm for green
   const float BLUE_WAVE_LENGHT = 0.475f;		   // 475 nm for red

   const float RED_WAVE_LENGHT_POWERED = powf(RED_WAVE_LENGHT, 4.0f);		   // 650 nm for red
   const float GREEN_WAVE_LENGHT_POWERED = powf(GREEN_WAVE_LENGHT, 4.0f);      // 570 nm for green
   const float BLUE_WAVE_LENGHT_POWERED = powf(BLUE_WAVE_LENGHT, 4.0f);		   // 475 nm for red
}

#endif//CONSTANTS_H