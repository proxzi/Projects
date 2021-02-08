//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file     
  \brief \ru Программный интерфейс для системы КОМПАС
         \en Program interface for KOMPAS system. \~
  \details \ru Данный файл содержит классы и методы, ориентированные на типы  
            данных CAD-системы КОМПАС. Для других приложений это API может оказаться
            не удобным, а его методы могут быть удалены или изменены в будущих 
            версиях. Рекомендуется применять эту часть API решателя, только если 
            не удасться найти требуемую функциональность в заголовочных файлах 
            gce_api.h или gce_types.h.
           \en This file contains classes and methods oriented to  
            data types of CAD-system KOMPAS. For other applications this API can be
            inconvenient and its methods can be deleted or modified in future 
            versions. It is recommended to apply this part of solver API only if 
            the required functionality is not found in header files 
            gce_api.h or gce_types.h. \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GCE_GEOM_H
#define __GCE_GEOM_H
//
#include <math_define.h>
#include <mb_cart_point.h>
#include <pars_tree_variable.h>
//
#include "gce_types.h"


class MATH_CLASS  MbPolyCurve;
struct            IfGeomPoint2d;

//----------------------------------------------------------------------------------------
// \ru Перечисление параметрических объектов \en Enumeration of parametric objects. 
//---
enum GcGeomType 
{
  vt_NULL,              ///< \ru Несуществующий тип. \en Nonexistent type. 
  gt_Point2d,           ///< \ru Точка. \en Point. 
  gt_Line2d,            ///< \ru Прямая. \en Line. 
  gt_LineSegment2d,     ///< \ru Отрезок. \en Segment. 
  gt_Circle2d,          ///< \ru Окружность. \en Circle. 
  gt_Arc2d,             ///< \ru Дуга. \en Arc. 
  gt_Ellipse2d,         ///< \ru Эллипс. \en Ellipse. 
  gt_EllipseArc2d,      ///< \ru Дуга эллипса. \en Ellipse arc. 
  // gt_ViewPointerArrow,  ///< \ru Отрезок. \en Segment. 
};

//----------------------------------------------------------------------------------------
// \ru Макросы \en Macros 
// ---
#define CAST_PTR(T) IfGeom2dPtr<If ## T,iidr_ ## T> // \ru Указатель с функцией приведения типов \en Pointer with function of type conversion 
#define GEOM_PTR(T) IfGeom2dPtr<T,iidr_ ## T>       // \ru Указатель с функцией приведения типов \en Pointer with function of type conversion 
#define CAST2PTR(T,arg) (arg) != NULL ? (T*)((arg)->GetInterfacingGeom(iidr_ ## T)) : NULL  // \ru Привести к другому типу \en Convert to another type 

//////////////////////////////////////////////////////////////////////////////////////////
// \ru Координата геометрического объекта или переменной \en Coordinate of a geometric object or a variable 
//////////////////////////////////////////////////////////////////////////////////////////
struct ItGeomCoord : public ItCoord
{
  virtual refcount_t    AddRef() const = 0;
  virtual refcount_t    Release() const = 0; 
};

//////////////////////////////////////////////////////////////////////////////////////////
/*\ru Надкласс примитивных геометрических объектов решателя
  Внимание: Применяется только для САПР КОМПАС. Рекомендуется вместо него использовать вызовы API из gce_api.h
  объектом IfSomething. Вместо макроса IFPTR применять GEOM_PTR.\n
  После того, как MdViewObj будет наконец-то, освобождать память по правилам 
  IfSomething, нужно:\n
    1) Все слова IfSomethingGeom2d заменить на IfSomething;\n
    2) Все слова GetInterfacingGeom заменить на QueryInterface;\n
    3) Удалить этот класс;\n
    4) Компилятор сам подскажет, какие места нужно доправить;\n

  \en Used while there is no correct work with MdViewObj in 2D model
  as with object IfSomething. GEOM_PTR is to be applied instead of macro IFPTR.\n
  After MdViewObj has been implemented it is required to free memory by rules IfSomething, 
  it is necessary to:\n
    1) All words IfSomethingGeom2d replace by IfSomething;\n
    2) All words GetInterfacingGeom replace by QueryInterface;\n
    3) Delete this class;\n
    4) Compiler will prompt which places are to be corrected;\n \~
*/
//////////////////////////////////////////////////////////////////////////////////////////
struct IfSomethingGeom2d 
{
  virtual IfSomethingGeom2d * GetInterfacingGeom( unsigned int iid ) = 0;  
};

//////////////////////////////////////////////////////////////////////////////////////////
// \ru Геометрический объект параметризации \en Geometric object of parametrization 
/*\ru Этот тип и его подтипы соответствуют словарю типов решателя, а не типам пользователя.
  \en This type and its subtypes correspond to the dictionary of types of the solver but not to the user types. \~
*/
//////////////////////////////////////////////////////////////////////////////////////////
struct IfGeom2d: public IfSomethingGeom2d
{
  virtual GcGeomType  GetGeomType() const = 0;
  /// \ru Выдать обозначение контрольной точки, принадлежащей объекту \en Get notation of the control point belonging to the object 
  virtual point_type  IdentCtrlPoint( const IfGeomPoint2d & ) const = 0;
  /// \ru Выдать обозначение координаты, принадлежащей объекту \en Get notation of coordinate belonging to the object 
  virtual coord_name  IdentCoord( const ItGeomCoord & ) const = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////
// \ru Точка на плоскости \en Point on the plane 
//////////////////////////////////////////////////////////////////////////////////////////
struct GCE_CLASS IfGeomPoint2d: public IfGeom2d
{
  virtual GcGeomType    GetGeomType() const { return gt_Point2d; }        
  virtual ItGeomCoord * GetXCoord() const = 0;
  virtual ItGeomCoord * GetYCoord() const = 0;  
  /// \ru Выдать обозначение контрольной точки, принадлежащей объекту \en Get notation of the control point belonging to the object 
  virtual coord_name    IdentCoord( const ItGeomCoord & ) const;

public:
  inline  MbCartPoint   GetValue() const;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Deprecated (2017). Use GCE_AddLine instead this.
/*
  КОМПАС отвязан от этого интерфейса.
*/
//////////////////////////////////////////////////////////////////////////////////////////
struct GCE_CLASS IfGeomLine2d: public IfGeom2d 
{
  virtual GcGeomType    GetGeomType() const { return gt_Line2d; }
  virtual ItGeomCoord * GetACoord() = 0;  ///< \ru Выдать угол нормали прямой \en Get angle of line normal 
  virtual ItGeomCoord * GetDCoord() = 0;  ///< \ru Выдать расстояние до начала СК в направлении нормали \en Get distance to the coordinate system origin in the normal direction   
  /// \ru Выдать обозначение контрольной точки, принадлежащей объекту \en Get notation of the control point belonging to the object 
  virtual coord_name    IdentCoord( const ItGeomCoord & ) const;
};

//////////////////////////////////////////////////////////////////////////////////////////
// \ru Отрезок на плоскости \en Segment on the plane 
//////////////////////////////////////////////////////////////////////////////////////////
struct GCE_CLASS IfGeomLineSeg2d: public IfGeom2d 
{
  virtual GcGeomType      GetGeomType() const { return gt_LineSegment2d; }
  virtual IfGeomPoint2d * GetEnd( int nb ) = 0; ///< \ru Выдать конец отрезка 1,2 \en Get end of segment 1,2 
  virtual bool            IsFixedLength() = 0;  ///< \ru Признак отрезка постоянной длины (для стрелки взгляда) \en Flag of segment of constant length (for the view vector) 
  // \ru Выдать обозначение контрольной точки, принадлежащей объекту \en Get notation of the control point belonging to the object 
  virtual coord_name      IdentCoord( const ItGeomCoord & ) const { return GCE_NULL_CRD; }
  inline  GCE_point       EndPoint( int nb );   ///< \ru Выдать конец отрезка 1,2 \en Get end of segment 1,2
};

//////////////////////////////////////////////////////////////////////////////////////////
// Deprecated (2017). Use GCE_AddCircle instead this.
/*
  КОМПАС отвязан от этого интерфейса.
*/
//////////////////////////////////////////////////////////////////////////////////////////
struct GCE_CLASS IfGeomCircle2d: public IfGeom2d 
{
  virtual GcGeomType      GetGeomType() const { return gt_Circle2d; }
  virtual IfGeomPoint2d * GetCentre() = 0;
  virtual ItGeomCoord   * GetRadius() = 0;
  // \ru Выдать обозначение контрольной точки, принадлежащей объекту \en Get notation of the control point belonging to the object 
  virtual coord_name      IdentCoord( const ItGeomCoord & ) const;
};

//////////////////////////////////////////////////////////////////////////////////////////
// \ru Эллипс на плоскости \en Ellipse on the plane 
//////////////////////////////////////////////////////////////////////////////////////////
struct GCE_CLASS IfGeomEllipse2d: public IfGeom2d
{
  virtual GcGeomType      GetGeomType() const { return gt_Ellipse2d; }
  virtual IfGeomPoint2d * GetCentre() = 0;    // \ru Выдать центр эллипса \en Get ellipse center 
  virtual ItGeomCoord   * GetACoord() = 0;    // \ru Выдать размер полуоси а \en Get size of semiaxis a 
  virtual ItGeomCoord   * GetBCoord() = 0;    // \ru Выдать размер полуоси b \en Get size of semiaxis b 
  virtual ItGeomCoord   * GetPhiCoord() = 0;  // \ru Выдать угол оси a \en Get angle of axis a 
  virtual coord_name      IdentCoord( const ItGeomCoord & ) const; // \ru Выдать обозначение контрольной точки, принадлежащей объекту \en Get notation of the control point belonging to the object 
  virtual bool            IsClockwise() const = 0;  // \ru Вернет true, усли параметризация эллипса по часовой стрелке. \en Returns true if the ellipse parametrization is directed clockwise. 
};

//////////////////////////////////////////////////////////////////////////////////////////
// \ru Дуга эллипса на плоскости \en Elliptical arc on the plane 
//////////////////////////////////////////////////////////////////////////////////////////
struct GCE_CLASS IfGeomEllipseArc2d: public IfGeomEllipse2d 
{
  virtual GcGeomType      GetGeomType() const { return gt_EllipseArc2d; }
  virtual IfGeomPoint2d * GetEnd( int nb ) = 0;
  inline  MbCartPoint     GetEndValue( int nb )
  {
    if ( const IfGeomPoint2d * bnd = GetEnd(nb) )
    {
      return bnd->GetValue();
    }
    return MbCartPoint();
  }
};

//----------------------------------------------------------------------------------------
// \ru Выдать true, если оба указателя представляют одну и ту же точку параметрическую точку \en Return true if both pointers represent the same parametric point 
/*\ru Поведение соответствует ParPoint::IsEqual
  \en Behavior corresponds to ParPoint::IsEqual \~
*/
//---
inline bool SamePoints( const IfGeomPoint2d * p1, const IfGeomPoint2d * p2 )
{  
  if ( p2 == p1 )
  {
    return true;
  }
  if ( p1 && p2 )
  {
    if ( p1->GetXCoord() == p2->GetXCoord() )
    {      
      return true;
    }
  }

  return false;  
}

//----------------------------------------------------------------------------------------
//
//---
inline MbCartPoint IfGeomPoint2d::GetValue() const
{
  MbCartPoint val;
  if ( const ItGeomCoord * x = GetXCoord() )
  {
    if ( const ItGeomCoord * y = GetYCoord() )
    {
      val.Init( x->GetValue(), y->GetValue() );
    }    
  }  
  return val;
}

//----------------------------------------------------------------------------------------
//
//---
inline GCE_point IfGeomLineSeg2d::EndPoint( int nb )
{
  GCE_point val;
  if ( IfGeomPoint2d * pnt = GetEnd(nb) )
  {
    const MbCartPoint xy = pnt->GetValue();
    val.x = xy.x;
    val.y = xy.y;
  }  
  return val;
};


//////////////////////////////////////////////////////////////////////////////////////////
// \ru Аналог IfPtr без работы со счетчиком ссылок \en Analog of IfPtr without working with reference counter 
/*\ru Указатель с сервисом приведения типов
  \en Pointer with type conversion service \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

template <class T, const unsigned int iid>
class IfGeom2dPtr 
{
  T * m_pI;

public:
  IfGeom2dPtr() : m_pI(0) {}
  IfGeom2dPtr( T * pI ): m_pI(pI) {}
  IfGeom2dPtr( IfSomethingGeom2d * pI ) : m_pI(0) { if ( pI != 0 ) m_pI = (T*)pI->GetInterfacingGeom(iid); }
  IfGeom2dPtr( const IfGeom2dPtr<T,iid> & o ) : m_pI( o.m_pI ) {}

public:  
  unsigned int  GetIid() const { return iid; }
  operator      T*() const { return m_pI; }
  T&            operator *() { C3D_ASSERT(m_pI != 0); return *m_pI; }
  T**           operator &() { C3D_ASSERT(m_pI == 0); return &m_pI; }
  T*            operator->() { C3D_ASSERT(m_pI != 0); return m_pI;  }
  T*            operator->() const { C3D_ASSERT(m_pI != 0); return m_pI;  }
  T*            Get() const { return m_pI; }
  T*            operator= ( T* pI ) { m_pI = pI; }
  T*            operator= ( const IfGeom2dPtr<T,iid> & o ) { return operator=(o.m_pI); }
  T*            operator= ( IfSomethingGeom2d * pI );
};

//----------------------------------------------------------------------------------------
// \ru Присвоить другой интерфейс \en Assign another interface 
// ---
template <class T, const unsigned int iid>
inline T* IfGeom2dPtr<T, iid>::operator = ( IfSomethingGeom2d * pI ) {
  T * pOld = m_pI;
  m_pI = 0;
  if ( pI != 0 )
    m_pI = (T*)pI->GetInterfacingGeom( iid );

  return m_pI;
}

//----------------------------------------------------------------------------------------
// \ru Идентификаторы интерфейсов решателя сопряжений \en Identifiers of constraint solver interfaces 
//---
typedef enum 
{
  // \ru Геометрические объекты \en Geometrical objects 
  iidr_IfSomethingGeom2d,  
  iidr_IfGeom2d,              ///< \ru Плоский геометрический объект \en Planar geometric object   
  iidr_IfGeomPoint2d,
  iidr_IfGeomLine2d,
  iidr_IfGeomLineSeg2d,
  iidr_IfGeomCircle2d,
  iidr_IfGeomArc2d,
  iidr_IfGeomEllipse2d,
  iidr_IfGeomEllipseArc2d,
  iidr_ParSolvingObj,         ///< \ru Интерфейс неизвестного чертежного объекта, не обязательно примитивного, \en Interface of unknown drawing object, not necessary primitive 
} EIfIDRolesMathGC;

//////////////////////////////////////////////////////////////////////////////////////////
// Deprecated (2016). Use GCE_AddBoundedCurve with GCE_AddCircle instead this.
/*
  КОМПАС отвязан от этого интерфейса.
*/
//////////////////////////////////////////////////////////////////////////////////////////
struct IfGeomArc2d: public IfGeomCircle2d
{
private:
  virtual GcGeomType      GetGeomType() const { return gt_Arc2d; }
  virtual bool            GetClockwise() const = 0;
  virtual IfGeomPoint2d * GetEnd( int nb ) = 0;
};

#endif

// eof