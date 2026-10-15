#pragma once
#include "effects.h"
#include <algorithm>
#include <cstddef>
#include <vector>
namespace ggfx {
// Convert arbitrary OpenRGB LED coordinates to unit-space without assuming
// a particular keyboard size. Missing geometry gets a stable row fallback.
struct Point { double x=0,y=0; };
inline std::vector<Led> normalize_layout(const std::vector<Point>& points) {
 std::vector<Led> out;
 out.reserve(points.size());
 if(points.empty()) return out;
 auto xbounds=std::minmax_element(points.begin(),points.end(),[](Point a,Point b){return a.x<b.x;});
 auto ybounds=std::minmax_element(points.begin(),points.end(),[](Point a,Point b){return a.y<b.y;});
 const double minx=xbounds.first->x,maxx=xbounds.second->x;
 const double miny=ybounds.first->y,maxy=ybounds.second->y;
 for(std::size_t i=0;i<points.size();++i) {
  const auto p=points[i];
  const double x=maxx>minx?(p.x-minx)/(maxx-minx):(points.size()>1?double(i)/(points.size()-1):.5);
  const double y=maxy>miny?(p.y-miny)/(maxy-miny):.5;
  out.push_back({std::clamp(x,0.0,1.0),std::clamp(y,0.0,1.0)});
 }
 return out;
}
inline std::vector<Led> fallback_layout(std::size_t count,std::size_t columns=15) {
 std::vector<Led> out;out.reserve(count);
 columns=std::max(std::size_t(1),columns);
 const std::size_t rows=(count+columns-1)/columns;
 for(std::size_t i=0;i<count;++i) {
  const std::size_t row=i/columns,col=i%columns;
  out.push_back({columns>1?double(col)/(columns-1):.5,rows>1?double(row)/(rows-1):.5});
 }
 return out;
}
}
