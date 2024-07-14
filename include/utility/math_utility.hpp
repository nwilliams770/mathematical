#ifndef MATH_UTILITY_HPP
#define MATH_UTILITY_HPP

namespace MathUtility
{
  float inline lerp(float start, float end, float interpolationFactor)
  {
    return start + (end - start) * interpolationFactor;
  }
}

#endif