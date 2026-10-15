#include "ggfx/effects.h"
#include "ggfx/layout.h"
#include <cassert>
int main() {
 using namespace ggfx;
 const Color black{},white{255,255,255};
 auto eq=[](Color a,Color b){return a.r==b.r&&a.g==b.g&&a.b==b.b;};
 assert(eq(blend(black,white,0,Blend::Normal),black));
 assert(eq(blend(black,white,1,Blend::Normal),white));
 assert((eq(blend({100,50,0},{200,50,255},1,Blend::Add),Color{255,100,255})));
 assert((eq(blend(white,{128,64,0},1,Blend::Multiply),Color{128,64,0})));
 assert((eq(blend(black,{128,64,0},1,Blend::Screen),Color{128,64,0})));
 assert(aperture(.5,.5,.5,.5,.3,.1)==1);
 assert(aperture(1,1,.5,.5,.3,.1)==0);
 const std::vector<Led> leds={{0,0},{.5,.5},{1,1}};
 for(auto e:{Effect::Solid,Effect::Rainbow,Effect::Wave,Effect::Breathing,Effect::ReactiveRipple,Effect::ReactiveLine,Effect::ReactiveSingleKey,Effect::Heatmap})
  assert(render(e,leds,0,1).size()==leds.size());
 const auto fallback=fallback_layout(61,15);
 assert(fallback.size()==61);
 assert(fallback[0].x==0);
 const auto normalized=normalize_layout({{10,20},{20,40}});
 assert(normalized.size()==2 && normalized[0].x==0 && normalized[1].y==1);
 const std::vector<KeyHit> hits={{1,0}};
 auto reactive=render(Effect::ReactiveSingleKey,leds,.1,1,black,white,hits);
 assert(reactive[1].r>reactive[0].r);
 assert(eq(render(Effect::ReactiveSingleKey,leds,.1,1,black,white)[1],black));
}
