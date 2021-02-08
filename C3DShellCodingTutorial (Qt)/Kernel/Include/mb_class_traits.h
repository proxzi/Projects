//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file \brief  \ru Характеристики типов для математических классов ядра "Mb..."
                \en Type traits of the math basic classes of the kernel "Mb..." \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MB_CLASS_TRAITS_H
#define __MB_CLASS_TRAITS_H

#include <plane_item.h>
#include <space_item.h>
#include <topology_item.h>


class MATH_CLASS MbLineSegment;
class MATH_CLASS MbArc;
class MATH_CLASS MbNurbs;
class MATH_CLASS MbLine;
class MATH_CLASS MbPlaneInstance;
class MATH_CLASS MbSpaceInstance;
class MATH_CLASS MbAssembly;
class MATH_CLASS MbInstance;
class            MbSolid;
class MATH_CLASS MbWireFrame;
class MATH_CLASS MbMesh;
class MATH_CLASS MbLineSegment3D;
class MATH_CLASS MbArc3D;
class MATH_CLASS MbFace;
class MATH_CLASS MbEdge;
class MATH_CLASS MbVertex;


//----------------------------------------------------------------------------------------
/** \brief  \ru Характеристики классов геометрического ядра C3D. 
            \en Class traits of C3D geometric kernel.
    \attention  \ru Экспериментальный класс. Пока приведены не все типы классов.
                \en Experimental class. While not all listed types of classes. \~
*/
//---
template<class Type>
struct MbClassTraits
{
private:
  // \ru Идентификатор класса математического ядра. \en Identifier of class of the geometric kernel.
  static const MbeSpaceType typeId = st_Undefined;
};

/*
  2D-curve sub-classes.
*/
template<>
struct MbClassTraits<MbLineSegment>   { static const MbePlaneType typeId = pt_LineSegment; };
template<>
struct MbClassTraits<MbArc>           { static const MbePlaneType typeId = pt_Arc; };
template<>
struct MbClassTraits<MbNurbs>         { static const MbePlaneType typeId = pt_Nurbs; };
template<>
struct MbClassTraits<MbLine>          { static const MbePlaneType typeId = pt_Line; };
/*
  C3D model sub-classes. Inherited from MbItem.
*/
template<>
struct MbClassTraits<MbPlaneInstance> { static const MbeSpaceType typeId = st_PlaneInstance; };
template<>
struct MbClassTraits<MbSpaceInstance> { static const MbeSpaceType typeId = st_SpaceInstance; };
template<>
struct MbClassTraits<MbAssembly>      { static const MbeSpaceType typeId = st_Assembly; };
template<>
struct MbClassTraits<MbInstance>      { static const MbeSpaceType typeId = st_Instance; };
template<>
struct MbClassTraits<MbSolid>      { static const MbeSpaceType typeId = st_Solid; };
template<>
struct MbClassTraits<MbWireFrame>     { static const MbeSpaceType typeId = st_WireFrame; };
template<>
struct MbClassTraits<MbMesh>          { static const MbeSpaceType typeId = st_Mesh; };
/*
  3D-curve sub-classes.
*/
template<>
struct MbClassTraits<MbLineSegment3D> { static const MbeSpaceType typeId = st_LineSegment3D; };
template<>
struct MbClassTraits<MbArc3D>         { static const MbeSpaceType typeId = st_Arc3D; };

/*
  Topology sub-classes.
*/
template<>
struct MbClassTraits<MbFace>    { static const MbeTopologyType typeId = tt_Face; };
template<>
struct MbClassTraits<MbEdge>    { static const MbeTopologyType typeId = tt_Edge; };
template<>
struct MbClassTraits<MbVertex>  { static const MbeTopologyType typeId = tt_Vertex; };

//----------------------------------------------------------------------------------------
// \ru Статическое приведение из типа <Type*> к <Type> (разадресация типа) \en Static cast from type <Type*> to <Type> 
//---
template<class _Type> struct Deref { private: typedef _Type Type; };
template<class _Type> struct Deref<const _Type*> { typedef _Type Type; };
template<class _Type> struct Deref<_Type*> { typedef _Type Type; };
template<class _Type> struct Deref<_Type&> { typedef _Type Type; };

//----------------------------------------------------------------------------------------
/** \brief  \ru Динамическое приведение типа, основанное на функции Derived::IsA(). 
            \en Dynamic type cast based on the function Derived::IsA().
*/
//---
template< class DerivedPtr, class ParentType >
DerivedPtr isa_cast ( ParentType * obj )
{  
  if ( (obj != NULL) && obj->IsA() == MbClassTraits<typename Deref<DerivedPtr>::Type>::typeId )
  {
    return static_cast<DerivedPtr>( obj );
  }
  return static_cast<DerivedPtr>( NULL );
}

//----------------------------------------------------------------------------------------
//
//---
template< class DerivedPtr, class ParentPtr >
DerivedPtr _IsaCast( ParentPtr * obj, const MbTopItem * tItem )
{  
  if ( (obj != tItem) && obj->RefType() == rt_TopItem )
  {
    tItem = static_cast<const MbTopItem*>( obj );
  } 
  return isa_cast<DerivedPtr>( tItem );
}

//----------------------------------------------------------------------------------------
/** \brief  \ru Динамическое приведение типа, основанное на функции Derived::IsA(). 
            \en Dynamic type cast based on the function Derived::IsA().
*/
//---
template< class DerivedPtr >
DerivedPtr isa_cast ( const MbRefItem * obj )
{  
  DerivedPtr resPtr = NULL;
  return _IsaCast<DerivedPtr>( obj, resPtr );
}

#endif // __MB_CLASS_TRAITS_H

// eof