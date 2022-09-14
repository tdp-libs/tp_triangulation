#include "tp_triangulation/Triangulation.h"

#include "tp_utils/Globals.h"

#include "clipper.hpp"

#include "earcut.hpp"

#include <array>

namespace tp_triangulation
{

//##################################################################################################
bool triangulate(const std::vector<Polygon>& srcData,
                 int triangleFan,
                 int triangleStrip,
                 int triangles,
                 std::map<int, std::vector<Contour>>& resultVerts)
{
  TP_UNUSED(triangleFan);
  TP_UNUSED(triangleStrip);

  const float scale = 100000;

  for(const Polygon& polygon : srcData)
  {
    if(polygon.contours.empty())
      continue;

    const Contour& contour = polygon.contours.at(0);
    if(contour.vertices.size()<3)
      continue;

    //-- Clean the polygon into one or more separate paths -----------------------------------------
    ClipperLib::Paths out_polys;
    {
      ClipperLib::Path in_poly;
      in_poly.reserve(contour.vertices.size());
      for(const auto& vert : contour.vertices)
        in_poly.push_back(ClipperLib::IntPoint(ClipperLib::cInt(vert.x*scale), ClipperLib::cInt(vert.y*scale)));

      ClipperLib::SimplifyPolygon(in_poly, out_polys, ClipperLib::pftNonZero);
    }

    //-- Chop those paths into triangles -----------------------------------------------------------
    {
      using Point = std::array<float, 2>;
      Contour packedTriangles;

      for(const ClipperLib::Path& path : out_polys)
      {
        if(path.size()<3)
          continue;

        std::vector<std::vector<Point>> polygon;
        polygon.resize(1);
        std::vector<Point>& poly = polygon[0];
        poly.resize(path.size());

        for(unsigned int p=0; p<path.size(); p++)
        {
          const ClipperLib::IntPoint& point = path.at(p);
          Point& pt = poly[p];
          pt[0] = float(point.X) / scale;
          pt[1] = float(point.Y) / scale;
        }

        for(size_t p : mapbox::earcut<size_t>(polygon))
        {
          Point& pt = poly[p];
          packedTriangles.vertices.emplace_back(glm::vec2(pt[0], pt[1]));
        }
      }

      resultVerts[triangles].push_back(packedTriangles);
    }
  }

  return false;
}

}
