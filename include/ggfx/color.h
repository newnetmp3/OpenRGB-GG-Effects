#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
namespace ggfx {
struct Color { std::uint8_t r=0,g=0,b=0; };
enum class Blend { Normal, Add, Multiply, Screen };
inline std::uint8_t byte(double x) { return static_cast<std::uint8_t>(std::lround(std::clamp(x,0.0,255.0))); }
inline Color blend(Color background, Color foreground, double opacity, Blend mode) {
 const double a=std::clamp(opacity,0.0,1.0);
 auto channel=[&](std::uint8_t b,std::uint8_t f) {
  double v=f;
  switch(mode) {
   case Blend::Normal: break;
   case Blend::Add: v=std::min(255.0,double(b)+f); break;
   case Blend::Multiply: v=double(b)*f/255.0; break;
   case Blend::Screen: v=255.0-(255.0-b)*(255.0-f)/255.0; break;
  }
  return byte(b*(1.0-a)+v*a);
 };
 return {channel(background.r,foreground.r),channel(background.g,foreground.g),channel(background.b,foreground.b)};
}
inline double aperture(double x,double y,double cx,double cy,double radius,double feather) {
 if(radius<=0) return 0;
 const double distance=std::hypot(x-cx,y-cy);
 if(feather<=0) return distance<=radius ? 1.0 : 0.0;
 return std::clamp((radius-distance)/feather,0.0,1.0);
}
}
