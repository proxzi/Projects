////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru NO TRANSLATION.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_ANNOTATIONGEOMETRY_H
#define __VSN_ANNOTATIONGEOMETRY_H

#include "vsn_meshgeometry.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class AnnotationGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
  \details \ru NO TRANSLATION. \n.
           \en NO TRANSLATION. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS AnnotationGeometry : public MeshGeometry
{
    VSN_OBJECT(AnnotationGeometry)
public:
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~AnnotationGeometry();
public:
    /// \ru Проверить является ли геометрия аннатационным. \en NO TRANSLATION. \~
    virtual bool IsAnnotation() const;
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION.
    AnnotationGeometry(AnnotationGeometryPrivate& dd, Node* pParent = nullptr);
    VSN_DECLARE_EX_PRIVATE(AnnotationGeometry)
};

VSN_END_NAMESPACE

#endif /* __VSN_ANNOTATIONGEOMETRY_H */
