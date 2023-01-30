#ifndef tp_triangulation_Triangulation_h
#define tp_triangulation_Triangulation_h

#include "tp_triangulation/Globals.h"

#include "glm/glm.hpp" // IWYU pragma: keep

#include <vector>
#include <map>

namespace tp_triangulation
{

//##################################################################################################
struct TP_TRIANGULATION_EXPORT Contour
{
  std::vector<glm::vec2> vertices;
};

//##################################################################################################
struct TP_TRIANGULATION_EXPORT Polygon
{
  std::vector<Contour> contours;
};

//##################################################################################################
//! Triangulate a list of polygons potentially with holes in them.
/*!
This will triangle a list of polygons into sets of triangles, triangle fans, and triangle strips. In
a format convinient for OpenGL.

The results will be returned in a map, the key of the map will be one of the triangleFan,
triangleStrip, or triangles values passed into this method. If working with OpenGL these values can
be set to GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP, and GL_TRIANGLES respectivly.

\param srcData The polygons to be triangulated.
\param triangleFan The map key to use for triangle fans.
\param triangleStrip The key to use for triangle strips.
\param triangles The key to use for individual triangles.
\param resultVerts The results will be placed in here.

\return True if all went well.
*/
bool TP_TRIANGULATION_EXPORT triangulate(const std::vector<Polygon>& srcData,
                                                int triangleFan,
                                                int triangleStrip,
                                                int triangles,
                                                std::map<int, std::vector<Contour>>& resultVerts);

}

#endif
