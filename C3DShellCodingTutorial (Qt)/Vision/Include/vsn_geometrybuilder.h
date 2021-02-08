////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru NOT TRANSLATED.
         \en NOT TRANSLATED. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GEOMETRYBUILDER_H
#define __VSN_GEOMETRYBUILDER_H

#include "vsn_node.h"
#include "vsn_global.h"

class MbMesh;
VSN_BEGIN_NAMESPACE
class Geometry;
//------------------------------------------------------------------------------
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS GeometryBuilder
{
public:
    virtual ~GeometryBuilder();
    virtual Geometry* operator()() = 0;
    virtual MbMesh* BuildGeometry() = 0;
    virtual bool operator ==(const GeometryBuilder& other) const = 0;
};
typedef std::shared_ptr<GeometryBuilder> GeometryBuilderPtr;

VSN_END_NAMESPACE

#endif /* __VSN_GEOMETRYBUILDER_H */
