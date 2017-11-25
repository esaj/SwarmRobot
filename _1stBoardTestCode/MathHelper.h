#ifndef MATHHELPER_H
#define MATHHELPER_H
#include <stdint.h>

inline float interpolate(float v1, float v2, float t)
{
  return (1.0f - t) * v1 + t * v1;
}

inline uint8_t interpolate(uint8_t v1, uint8_t v2, float t)
{
  return (uint8_t)((1.0f - t) * (float)v1 + t * (float)v1);
}

inline uint16_t interpolate(uint16_t v1, uint16_t v2, float t)
{
  return (uint16_t)((1.0f - t) * (float)v1 + t * (float)v1);
}

inline uint32_t interpolate(uint32_t v1, uint32_t v2, float t)
{
  return (uint32_t)((1.0f - t) * (float)v1 + t * (float)v1);
}


inline uint8_t simpleLowPass(uint8_t newValue, uint8_t oldValue, uint8_t shiftBits)
{
  return ((((uint32_t)oldValue) << shiftBits) - oldValue + newValue) >> shiftBits;
}

inline uint16_t simpleLowPass(uint16_t newValue, uint16_t oldValue, uint8_t shiftBits)
{
  //Higher shiftBits "slows down" the change (rejects fast changes, ie high "frequency")

  //Cast oldvalue to uint32_t to avoid overflows (up to a point),
  //shift left by shiftBits (multiply), subtract 1 old value
  //(so it's the equivalent of multiply by 2^n - 1, without having to do actual multiplication)
  //Add new value and shift right (divide) by shiftbits
  return ((((uint32_t)oldValue) << shiftBits) - oldValue + newValue) >> shiftBits;
}

inline uint32_t simpleLowPass(uint32_t newValue, uint32_t oldValue, uint8_t shiftBits)
{
  return ((oldValue << shiftBits) - oldValue + newValue) >> shiftBits;
}

inline float exponentialLowpass(float newValue, float oldValue, float factor)
{
  return newValue*factor + (1.0f - factor) * oldValue;
}

inline uint8_t exponentialLowpass(uint8_t newValue, uint8_t oldValue, float factor)
{
  return (uint8_t)(newValue*factor + (1.0f - factor) * oldValue);
}

inline uint16_t exponentialLowpass(uint16_t newValue, uint16_t oldValue, float factor)
{
  return (uint16_t)(newValue*factor + (1.0f - factor) * oldValue);
}

inline uint32_t exponentialLowpass(uint32_t newValue, uint32_t oldValue, float factor)
{
  return (uint32_t)(newValue*factor + (1.0f - factor) * oldValue);
}

#endif //#ifndef MATHHELPER_H
