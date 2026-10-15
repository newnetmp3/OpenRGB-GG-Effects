#pragma once
#include "color.h"
#include <algorithm>
#include <cmath>
#include <vector>
namespace ggfx {
struct Led { double x=0.5,y=0.5; };
struct KeyHit { std::size_t led=0; double at=0; };
enum class Effect { Solid, Rainbow, Wave, Breathing, ReactiveRipple, ReactiveLine, ReactiveSingleKey, Heatmap };
constexpr double pi=3.14159265358979323846;
inline Color hsv(double h,double s,double v) {
 h-=std::floor(h); s=std::clamp(s,0.0,1.0);v=std::clamp(v,0.0,1.0);
 const double f=h*6, c=v*s, x=c*(1-std::abs(std::fmod(f,2.0)-1)),m=v-c;
 double r=0,g=0,b=0;
 if(f<1){r=c;g=x;}else if(f<2){r=x;g=c;}else if(f<3){g=c;b=x;}else if(f<4){g=x;b=c;}else if(f<5){r=x;b=c;}else{r=c;b=x;}
 return {byte((r+m)*255),byte((g+m)*255),byte((b+m)*255)};
}
inline std::vector<Color> render(Effect effect,const std::vector<Led>& leds,double seconds,double speed,
 Color base={18,30,65},Color accent={0,230,255},const std::vector<KeyHit>& hits={}) {
 std::vector<Color> result;result.reserve(leds.size());
 speed=std::max(0.01,speed);
 for(std::size_t i=0;i<leds.size();++i) {
  const auto p=leds[i];Color color=base;
  switch(effect) {
   case Effect::Solid: break;
   case Effect::Rainbow: color=hsv(p.x+seconds*speed*0.1,1,1);break;
   case Effect::Wave: color=hsv(p.x*0.8+p.y*0.3-seconds*speed*0.15,1,1);break;
   case Effect::Breathing: {double a=0.1+0.9*(0.5+0.5*std::cos(seconds*speed*pi));color={byte(base.r*a),byte(base.g*a),byte(base.b*a)};break;}
   default: {
    double intensity=0,heat=0;
    for(const auto& hit:hits) {
     if(hit.led>=leds.size())continue;
     const double age=seconds-hit.at;
     if(age<0 || age>12.5/speed)continue;
     const auto origin=leds[hit.led];
     const double dx=p.x-origin.x,dy=p.y-origin.y,dist=std::hypot(dx,dy);
     double v=0;
     switch(effect) {
      case Effect::ReactiveRipple: {const double front=dist-age*speed*1.6;v=std::exp(-front*front/0.008)*std::max(0.0,1-age*speed/0.25);break;}
      case Effect::ReactiveLine: {const double front=std::abs(dx)-age*speed*0.9;v=std::exp(-front*front/0.008)*std::exp(-dy*dy/0.05)*std::max(0.0,1-age*speed/0.5);break;}
      case Effect::ReactiveSingleKey: v=i==hit.led ? std::max(0.0,1-age*speed/1.25):0;break;
      case Effect::Heatmap: v=std::exp(-dist*9)*std::exp(-age*speed*0.6);break;
      default:break;
     }
     intensity=std::max(intensity,v);heat+=v;
    }
    if(effect==Effect::Heatmap)intensity=1-std::exp(-heat*0.85);
    intensity=std::clamp(intensity,0.0,1.0);
    color={byte(base.r*(1-intensity)+accent.r*intensity),byte(base.g*(1-intensity)+accent.g*intensity),byte(base.b*(1-intensity)+accent.b*intensity)};
   }
  }
  result.push_back(color);
 }
 return result;
}
}
