////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Свойства математических объектов.
         \en Properties of mathematical objects. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MB_PROPERTY_H
#define __MB_PROPERTY_H


#include <math_define.h>
#include <templ_sptr.h>
#include <stdio.h>
#include <stdlib.h>
#include <templ_p_array.h>
#include <reference_item.h>
#include <mb_property_title.h>
#include <mb_cart_point3d.h>
#include <mb_cart_point.h>
#include <name_item.h>


#define GET_PROPERTY_VALUE( v ) _GetPropertyValue( &(v), sizeof(v) )


class MbAttribute;
class MbCurve;
class MbCurve3D;
class MbMultiline;
class MbMatrix3D;
class MbFloatPoint;
class MbFloatPoint3D;
class MbFloatVector3D;
class MbTriangle;
class MbQuadrangle;
class MbElement;
class MbApex3D;
class MbPolygon3D;
class MbGrid;
class MbNamedAttributeContainer;
class MbPlacement3D;
class MbMarker;
class MbSurface;
class MbPoint3D;
class MbPointFrame;
class MbWireFrame;
class MbSolid;
class MbInstance;
class MbAssembly;
class MbConstraintSystem;
class MbMesh;            
class MbItem;
class MbSpaceInstance;
class MbPlaneInstance;
class MbAssistingItem;
class MbCollection;
class MbModel;
class MbRegion;
class MbDirection;
class MbPlacement;
class MbMatrix;
class MbMultiline;
class MbRegion;
class MbSymbol;
class MbThread;
class MbFunction;
class MbVertex;       
class MbEdge;         
class MbCurveEdge;    
class MbOrientedEdge; 
class MbLoop;         
class MbFace;         
class MbFaceShell;    
class MbName;         
class MbCreator;
class MbAttributeContainer;
class MbAttributeAction;
class MbTransactions;
template <class Vector>
class MbPntMatingData;
class MbProperties;


//----------------------------------------------------------------------------------------
  /** \brief \ru Типы свойств.
             \en Types of properties. \~
  \details \ru Типы свойств. \n
   Свойства дают доступ к внутренним данным объектов.
           \en Types of properties. \n
   Properties give access to internal data of objects. \~
  \ingroup Geometric_Items
  */
// ---
enum PrePropType 
{
  pt_UndefinedProp, ///< \ru Свойство неизвестного типа данных. \en Property of unknown datatype. \n

  // \ru Атомарные свойства. \en Atomic properties. 
  pt_BoolProp,               ///< \ru Логическое значение. \en Logical value. 
  pt_IntProp,                ///< \ru Целое значение. \en Integer value. 
  pt_UIntProp,               ///< \ru Беззнаковое целое значение. \en Unsigned integer value. 
  pt_DoubleProp,             ///< \ru Действительное значение. \en Real value. 
  pt_StringProp,             ///< \ru Строковое значение. \en String value. 
  pt_CharProp,               ///< \ru Строковое значение. \en String value. 
  pt_VersionProp,            ///< \ru Свойство-версия. \en Version property. \n

  // \ru Комплексные свойства плоских объектов . \en Complex properties of planar objects. 
  pt_CartPointProp,          ///< \ru Cвойство точки. \en Property of point. 
  pt_VectorProp,             ///< \ru Cвойство вектора. \en Property of vector. 
  pt_DirectionProp,          ///< \ru Cвойство вектора. \en Property of vector. 
  pt_PlacementProp,          ///< \ru Cвойство системы координат. \en Property of coordinate system. 
  pt_MatrixProp,             ///< \ru Cвойство матрицы. \en Property of matrix. 
  pt_CurveProp,              ///< \ru Cвойство кривой. \en Property of curve. 
  pt_MultilineProp,          ///< \ru Свойство мультилинии. \en Property of multiline. 
  pt_RegionProp,             ///< \ru Свойство региона. \en Property of region. 
  pt_PntMatingProp,          ///< \ru Свойство сопряжения в точке. \en Property of conjugation at a point. \n
    
  // \ru Комплексные свойства пространственных объектов. \en Complex properties of spatial objects. 
  pt_CartPoint3DProp,        ///< \ru Cвойство точки. \en Property of point. 
  pt_Vector3DProp,           ///< \ru Cвойство вектора. \en Property of vector. 
  pt_Placement3DProp,        ///< \ru Cвойство системы. \en Property of coordinate system. 
  pt_Matrix3DProp,           ///< \ru Cвойство матрицы. \en Property of matrix. 
  pt_FloatPointProp,         ///< \ru Cвойство параметра. \en Property of parameter. 
  pt_FloatPoint3DProp,       ///< \ru Cвойство точки. \en Property of point. 
  pt_FloatVector3DProp,      ///< \ru Cвойство вектора. \en Property of vector. 
  pt_TriangleProp,           ///< \ru Cвойство треугольника. \en Property of triangle. 
  pt_QuadrangleProp,         ///< \ru Cвойство четырехугольника. \en Property of quadrangle. 
  pt_ElementProp,            ///< \ru Cвойство элемента. \en Property of element. 
  pt_Apex3DProp,             ///< \ru Cвойство аперса. \en Property of apex. 
  pt_Polygon3DProp,          ///< \ru Cвойство полигона. \en Property of polygon. 
  pt_GridProp,               ///< \ru Cвойство триангуляции. \en Property of triangulation. \n

  // \ru Комплексные свойства геометрических объектов. \en Complex properties of geometric objects. 
  pt_FunctionProp,           ///< \ru Cвойство функции. \en Property of function. 
  pt_Curve3DProp,            ///< \ru Cвойство кривой. \en Property of curve. 
  pt_SurfaceProp,            ///< \ru Cвойство поверхности. \en Property of surface. 
  pt_Point3DProp,            ///< \ru Cвойство точки. \en Property of point.   
  pt_MarkerProp,             ///< \ru Cвойство маркера ("точка присоединения"). \en Property of marker ("point of joint"). 
  pt_SymbolProp,             ///< \ru Cвойство условного обозначения. \en Property of conventional notation. 
  pt_ThreadProp,             ///< \ru Cвойство резьбы. \en Property of thread. 
  pt_Pnt3DMatingProp,        ///< \ru Cвойство сопряжения в точке. \en Property of conjugation at a point. \n
    
  // \ru Комплексные свойства тел и топологических объектов. \en Complex properties of solids and topological objects. 
  pt_CreatorProp,            ///< \ru Cвойство строителя тела. \en Property of solid creator. 
  pt_VertexProp,             ///< \ru Cвойство вершины. \en Property of vertex. 
  pt_EdgeProp,               ///< \ru Cвойство ребра-кривой. \en Property of edge curve. 
  pt_CurveEdgeProp,          ///< \ru Cвойство ребра грани. \en Property of face edge. 
  pt_OrientedEdgeProp,       ///< \ru Cвойство ориентированного ребра. \en Property of oriented edge. 
  pt_LoopProp,               ///< \ru Cвойство цикла. \en Property of loop. 
  pt_FaceProp,               ///< \ru Cвойство грани. \en Property of face.                            
  pt_FaceShellProp,          ///< \ru Cвойство оболочки. \en Property of shell. 
  pt_NameProp,               ///< \ru Cвойство имени. \en Property of name. \n
    
  // \ru Комплексные свойства объектов модели. \en Complex properties of model objects. 
  pt_AssistingItemProp,      ///< \ru Cвойство вспомогательного объекта. \en Property of assisting item. 
  pt_CollectionProp,         ///< \ru Cвойство коллекции 3D элементов. \en Property of the collection of 3D elements. \n
  pt_PointFrameProp,         ///< \ru Cвойство точечного каркаса. \en Property of point frame. 
  pt_WireFrameProp,          ///< \ru Cвойство проволочного каркаса. \en Property of wire frame. 
  pt_SolidProp,              ///< \ru Cвойство тела. \en Property of solid. 
  pt_InstanceProp,           ///< \ru Cвойство вставки объекта. \en Property of object instance. 
  pt_AssemblyProp,           ///< \ru Cвойство сборочной единицы. \en Property of assembly unit. 
  pt_ConstraintSystem,       ///< \ru Cвойство системы ограничений. \en Property of constraint system.
  pt_MeshProp,               ///< \ru Cвойство сетки. \en Property of mesh. 
  pt_SpaceInstanceProp,      ///< \ru Cвойство объекта. \en Property of object. 
  pt_PlaneInstanceProp,      ///< \ru Cвойство плоского объекта. \en Property of flat object. 
  pt_ConstraintModelProp,    ///< \ru Cвойство схемы сопряжений. \en Property of conjugation scheme. 
  pt_ItemProp,               ///< \ru Cвойство объекта. \en Property of object. 
  pt_ModelProp,              ///< \ru Cвойство объектной модели. \en Property of object model. 
  pt_TransactionsProp,       ///< \ru Cвойство журнала построения. \en Property of build log. 
  pt_AttributeContainerProp, ///< \ru Cвойство контейнера атрибутов. \en Property of attribute container. 
  pt_AttributeProp,          ///< \ru Cвойство атрибута. \en Property of attribute. 
  pt_NamedAttributeContainerProp, ///< \ru Cвойство именованного контейнера атрибутов. \en Property of named attribute container. 
  pt_AttributeActionProp,    ///< \ru Cвойство атрибута. \en Property of attribute. \n

  pt_LastPropType,           ///< \ru Последний тип свойства, все остальные добавлять перед ним. \en Last type of property, any other ones must be added before. 
};


//-----------------------------------------------------------------------------
/// \ru Структура соответствия типа объекта и типа свойства. \en Object type and property type correspondence structure. 
//---
template<class Type>
struct PropType { static const PrePropType propId = pt_UndefinedProp; };


//-----------------------------------------------------------------------------
// \ru Специализация шаблона PropType - организует таблицу соответствий \en PropType template specialization - organizes lookup table 
//---
template<> struct PropType<MbCartPoint>                  { static const PrePropType propId = pt_CartPointProp;               };
template<> struct PropType<MbVector>                     { static const PrePropType propId = pt_VectorProp;                  };
template<> struct PropType<MbDirection>                  { static const PrePropType propId = pt_DirectionProp;               };
template<> struct PropType<MbPlacement>                  { static const PrePropType propId = pt_PlacementProp;               };
template<> struct PropType<MbMatrix>                     { static const PrePropType propId = pt_MatrixProp;                  };
template<> struct PropType<MbCurve>                      { static const PrePropType propId = pt_CurveProp;                   };
template<> struct PropType<MbMultiline>                  { static const PrePropType propId = pt_MultilineProp;               };
template<> struct PropType<MbRegion>                     { static const PrePropType propId = pt_RegionProp;                  };
template<> struct PropType<MbSymbol>                     { static const PrePropType propId = pt_SymbolProp;                  };
template<> struct PropType<MbThread>                     { static const PrePropType propId = pt_ThreadProp;                  };
template<> struct PropType<MbCartPoint3D>                { static const PrePropType propId = pt_CartPoint3DProp;             };
template<> struct PropType<MbVector3D>                   { static const PrePropType propId = pt_Vector3DProp;                };
template<> struct PropType<MbPlacement3D>                { static const PrePropType propId = pt_Placement3DProp;             };
template<> struct PropType<MbMatrix3D>                   { static const PrePropType propId = pt_Matrix3DProp;                };
template<> struct PropType<MbFloatPoint>                 { static const PrePropType propId = pt_FloatPointProp;              };
template<> struct PropType<MbFloatPoint3D>               { static const PrePropType propId = pt_FloatPoint3DProp;            };
template<> struct PropType<MbFloatVector3D>              { static const PrePropType propId = pt_FloatVector3DProp;           };
template<> struct PropType<MbTriangle>                   { static const PrePropType propId = pt_TriangleProp;                };
template<> struct PropType<MbQuadrangle>                 { static const PrePropType propId = pt_QuadrangleProp;              };
template<> struct PropType<MbElement>                    { static const PrePropType propId = pt_ElementProp;                 };
template<> struct PropType<MbApex3D>                     { static const PrePropType propId = pt_Apex3DProp;                  };
template<> struct PropType<MbPolygon3D>                  { static const PrePropType propId = pt_Polygon3DProp;               };
template<> struct PropType<MbGrid>                       { static const PrePropType propId = pt_GridProp;                    };
template<> struct PropType<MbMarker>                     { static const PrePropType propId = pt_MarkerProp;                  };
template<> struct PropType<MbCurve3D>                    { static const PrePropType propId = pt_Curve3DProp;                 };
template<> struct PropType<MbSurface>                    { static const PrePropType propId = pt_SurfaceProp;                 };
template<> struct PropType<MbPoint3D>                    { static const PrePropType propId = pt_Point3DProp;                 };
template<> struct PropType<MbPointFrame>                 { static const PrePropType propId = pt_PointFrameProp;              };
template<> struct PropType<MbWireFrame>                  { static const PrePropType propId = pt_WireFrameProp;               };
template<> struct PropType<MbSolid>                      { static const PrePropType propId = pt_SolidProp;                   };
template<> struct PropType<MbInstance>                   { static const PrePropType propId = pt_InstanceProp;                };
template<> struct PropType<MbAssembly>                   { static const PrePropType propId = pt_AssemblyProp;                };
template<> struct PropType<MbConstraintSystem>           { static const PrePropType propId = pt_ConstraintSystem;            };
template<> struct PropType<MbMesh>                       { static const PrePropType propId = pt_MeshProp;                    };
template<> struct PropType<MbItem>                       { static const PrePropType propId = pt_ItemProp;                    };
template<> struct PropType<MbSpaceInstance>              { static const PrePropType propId = pt_SpaceInstanceProp;           };
template<> struct PropType<MbPlaneInstance>              { static const PrePropType propId = pt_PlaneInstanceProp;           };
template<> struct PropType<MbAssistingItem>              { static const PrePropType propId = pt_AssistingItemProp;           };
template<> struct PropType<MbCollection>                 { static const PrePropType propId = pt_CollectionProp;              };
template<> struct PropType<MbModel>                      { static const PrePropType propId = pt_ModelProp;                   };
template<> struct PropType<MbFunction>                   { static const PrePropType propId = pt_FunctionProp;                };
template<> struct PropType<MbVertex>                     { static const PrePropType propId = pt_VertexProp;                  };
template<> struct PropType<MbEdge>                       { static const PrePropType propId = pt_EdgeProp;                    };
template<> struct PropType<MbCurveEdge>                  { static const PrePropType propId = pt_CurveEdgeProp;               };
template<> struct PropType<MbOrientedEdge>               { static const PrePropType propId = pt_OrientedEdgeProp;            };
template<> struct PropType<MbLoop>                       { static const PrePropType propId = pt_LoopProp;                    };
template<> struct PropType<MbFace>                       { static const PrePropType propId = pt_FaceProp;                    };
template<> struct PropType<MbFaceShell>                  { static const PrePropType propId = pt_FaceShellProp;               };
template<> struct PropType<MbName>                       { static const PrePropType propId = pt_NameProp;                    };
template<> struct PropType<MbCreator>                    { static const PrePropType propId = pt_CreatorProp;                 };
template<> struct PropType<MbAttributeContainer>         { static const PrePropType propId = pt_AttributeContainerProp;      };
template<> struct PropType<MbAttribute>                  { static const PrePropType propId = pt_AttributeProp;               };
template<> struct PropType<MbAttributeAction>            { static const PrePropType propId = pt_AttributeActionProp;         };
template<> struct PropType<MbTransactions>               { static const PrePropType propId = pt_TransactionsProp;            };
template<> struct PropType<MbNamedAttributeContainer>    { static const PrePropType propId = pt_NamedAttributeContainerProp; };
template<> struct PropType<MbPntMatingData<MbVector> >   { static const PrePropType propId = pt_PntMatingProp;               };
template<> struct PropType<MbPntMatingData<MbVector3D> > { static const PrePropType propId = pt_Pnt3DMatingProp;             };


//------------------------------------------------------------------------------
/** \brief \ru Свойство.
           \en Property. \~
  \details \ru Свойство является базовым классом для доступа к внутренним данным объектов.
    Наследники свойства содержать внутренние данные объектов или их копии.
    Свойства предназначены для просмотра и модификации внутренних данных объектов.
           \en Property is the base class for access to internal data of objects.
    Inheritors of property may contain internal data of objects or its copies.
    Properties are intended for reading and changing internal data of objects. \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS MbProperty 
{
private:
  MbePrompt prompt;     ///< \ru Номер подсказки. \en Number of hint string.
  bool      changeable; ///< \ru Признак редактируемости. \en Attribute of editability.

public:
  /// \ru Конструктор. \en Constructor. 
  MbProperty( MbePrompt name, bool change = true ) : prompt( name ), changeable( change ) {}
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbProperty();

  /// \ru Выдать тип свойства. \en Get type of property. 
  virtual PrePropType IsA() const = 0;
  /// \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void        GetCharValue( TCHAR * v ) const = 0;
  /// \ru Выдать значение свойства. \en Get value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t size ) const = 0;
  /// \ru Установить новое значение свойства. \en Set the new value of the property. 
  virtual void        SetPropertyValue( TCHAR * v ) = 0;
  /// \ru Выдать кортеж свойств составного свойства (не атомарный объект). \en Get tuple of the complex property (non-atomic object).
  virtual void        GetProperties( MbProperties & ) {}
  /// \ru Задать кортеж свойств составного свойства (не атомарный объект). \en Set tuple of the complex property (non-atomic object).
  virtual void        SetProperties( const MbProperties & ) {}
          /// \ru Выдать подсказку. \en Get a hint. 
  virtual size_t      GetPrompt() const { return prompt; }
          /// \ru Выдать подсказку. \en Get a hint. 
          MbePrompt & SetPrompt() { return prompt; }
          /// \ru Можно ли изменять данные. \en Is it possible to change data. 
          bool        IsChangeable() const { return changeable; }

OBVIOUS_PRIVATE_COPY( MbProperty )
}; // MbProperty


//------------------------------------------------------------------------------
/** \brief \ru bool свойство.
           \en Bool property. \~
  \details \ru bool свойство предназначено для просмотра и модификации данных типа bool.\n
           \en Bool property is intended for reading and changing data of boolean type.\n \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS BoolProperty : public MbProperty {
public :
  bool value; ///< \ru Значение. \en Value. 

  /// \ru Конструктор. \en Constructor. 
  BoolProperty( MbePrompt name, bool initValue, bool change = true )
    : MbProperty( name, change )
    , value( initValue )
  {}
  /// \ru Деструктор. \en Destructor. 
  virtual ~BoolProperty();

  virtual PrePropType IsA() const; // \ru Выдать тип свойства. \en Get type of property. 
  virtual void        GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t size ) const; // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void        SetPropertyValue( TCHAR * v ); // \ru Установить новое значение свойства. \en Set the new value of the property. 

OBVIOUS_PRIVATE_COPY( BoolProperty )
}; // BoolProperty


//------------------------------------------------------------------------------
/** \brief \ru int свойство.
           \en Int property. \~
  \details \ru int свойство предназначено для просмотра и модификации данных типа int.\n
           \en Int property is intended for reading and changing data of integer type.\n \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS IntProperty : public MbProperty {
public :
  int64 value; ///< \ru Значение. \en Value. 

  /// \ru Конструктор. \en Constructor. 
  IntProperty( MbePrompt name, int64 initValue, bool change = true )
    : MbProperty( name, change )
    , value( (int64)initValue )
  {}

  /// \ru Деструктор. \en Destructor. 
  virtual ~IntProperty();

  virtual PrePropType IsA() const; // \ru Выдать тип свойства. \en Get type of property. 
  virtual void        GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t size ) const; // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void        SetPropertyValue( TCHAR * v ); // \ru Установить новое значение свойства. \en Set the new value of the property. 

OBVIOUS_PRIVATE_COPY( IntProperty )
}; // IntProperty


//------------------------------------------------------------------------------
/** \brief \ru uint свойство.
           \en Uint property. \~
  \details \ru uint свойство предназначено для просмотра и модификации данных типа uint64.\n
           \en Uint property is intended for reading and changing data of uint64 type.\n \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS UIntProperty : public MbProperty {
public :
  uint64 value; ///< \ru Значение. \en Value. 
  
  /// \ru Конструктор. \en Constructor. 
  UIntProperty( MbePrompt name, size_t initValue, bool change = true )
    : MbProperty( name, change )
    , value( (uint64)initValue )
  {}

  /// \ru Деструктор. \en Destructor. 
  virtual ~UIntProperty();
  
  virtual PrePropType IsA() const; // \ru Выдать тип свойства. \en Get type of property. 
  virtual void        GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t size ) const; // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void        SetPropertyValue( TCHAR * v ); // \ru Установить новое значение свойства. \en Set the new value of the property. 

OBVIOUS_PRIVATE_COPY( UIntProperty )
}; // UIntProperty


//------------------------------------------------------------------------------
/** \brief \ru double свойство.
           \en Double property. \~
  \details \ru double свойство предназначено для просмотра и модификации данных типа double.\n
           \en Double property is intended for reading and changing data of double type.\n \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS DoubleProperty : public MbProperty {
public :
  double value; ///< \ru Значение. \en Value. 

  /// \ru Конструктор. \en Constructor. 
  DoubleProperty( MbePrompt name, double initValue, bool change = true )
    : MbProperty( name, change )
    , value( initValue )
  {}
  /// \ru Деструктор. \en Destructor. 
  virtual ~DoubleProperty();

  virtual PrePropType IsA() const; // \ru Выдать тип свойства. \en Get type of property. 
  virtual void        GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t size ) const; // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void        SetPropertyValue( TCHAR * v ); // \ru Установить новое значение свойства. \en Set the new value of the property. 

OBVIOUS_PRIVATE_COPY( DoubleProperty )
}; // DoubleProperty


//------------------------------------------------------------------------------
/** \brief \ru double свойство с номером.
           \en Double property with number. \~
  \details \ru double свойство с номером предназначено для просмотра и модификации данных типа double, имеющих порядковый номер.\n
           \en Double property with number is intended for reading and changing data of double type which have number.\n \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS NDoubleProperty : public MbProperty {
public :
  double value;  ///< \ru Значение. \en Value. 
  uint32 number; ///< \ru Номер. \en Number. 

  /// \ru Конструктор. \en Constructor. 
  NDoubleProperty( MbePrompt name, double initValue, bool change = true, uint32 n = 0 )
    : MbProperty( name, change )
    , value( initValue )
    , number( n )
  {}
  /// \ru Деструктор. \en Destructor. 
  virtual ~NDoubleProperty();

  virtual PrePropType IsA() const; // \ru Выдать тип свойства. \en Get type of property. 
  virtual void        GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t size ) const; // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void        SetPropertyValue( TCHAR * v ); // \ru Установить новое значение свойства. \en Set the new value of the property. 

OBVIOUS_PRIVATE_COPY( NDoubleProperty )
}; // NDoubleProperty


//----------------------------------------------------------------------------------------
/** \brief \ru string свойство.
           \en String property. \~
  \details \ru string свойство предназначено для просмотра и модификации данных типа TCHAR *.\n
           \en String property is intended for reading and changing TCHAR * like data.\n \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS StringProperty : public MbProperty
{
  TCHAR * value; ///< \ru Значение. \en Value.

public:
  /// \ru Конструктор. \en Constructor. 
  StringProperty( MbePrompt name, const TCHAR * initValue, bool change = true );
  /// \ru Деструктор. \en Destructor. 
  virtual ~StringProperty();

  virtual PrePropType IsA() const; // \ru Выдать тип свойства. \en Get type of property. 
  virtual void        GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t size ) const; // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void        SetPropertyValue( TCHAR * v ); // \ru Установить новое значение свойства. \en Set the new value of the property. 
  const TCHAR *       CharValue() const { return value; }
  
OBVIOUS_PRIVATE_COPY(StringProperty)
}; // StringProperty


typedef StringProperty CharProperty; 


//------------------------------------------------------------------------------
/** \brief \ru Version свойство.
           \en Version property. \~
  \details \ru Version свойство предназначено для просмотра и модификации данных типа VERSION.\n
           \en Version property is intended for reading and changing VERSION like data.\n \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS VersionProperty : public MbProperty {
public :
  VERSION value; ///< \ru Значение. \en Value. 

  /// \ru Конструктор. \en Constructor. 
  VersionProperty( MbePrompt name, VERSION initValue, bool change = true )
    : MbProperty( name, change )
    , value( initValue )
  {}
  /// \ru Деструктор. \en Destructor. 
  virtual ~VersionProperty() {}

  virtual PrePropType IsA() const; // \ru Выдать тип свойства. \en Get type of property. 
  virtual void        GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t size ) const; // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void        SetPropertyValue( TCHAR * v ); // \ru Установить новое значение свойства. \en Set the new value of the property. 

OBVIOUS_PRIVATE_COPY( VersionProperty )
}; // IntProperty


//------------------------------------------------------------------------------
/** \brief \ru Выдать строковое значение данного свойства для данного его поля.
           \en Get string value of given property for its given field. \~
  \details \ru Функция определена для случая "по умолчанию", для конкретных типов FieldType, 
    следует перегрузить для статического сопоставления типов компилятором.\n
           \en In "default" case function is defined for explicit types FieldType, 
    it should be overloaded for static mapping of types by compiler.\n \~
  \ingroup Model_Properties
*/
//---
template <class PropType, class FieldType> 
inline void GetCharValue( const PropType *, const FieldType *, uint32 n, TCHAR * v )
{
  C3D_ASSERT( v != NULL );
  if ( v != NULL ) {
    if ( n == 0 ) {
      v[0] = _T(' ');
      v[1] = _T('\0');
    }
    else
      _sntprintf( v, 64, _T("%d\t"), n );
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Выдать свойства двумерной точки.
           \en Get properties of two-dimensional point. \~
  \details \ru Выдать свойства двумерной точки MbCartPoint.\n
           \en Get properties of two-dimensional point MbCartPoint.\n \~
  \ingroup Model_Properties
*/
//---
template <class PropType> 
inline void GetCharValue( const PropType *, const MbCartPoint * value, uint32 n, TCHAR * v )
{
  C3D_ASSERT( value != NULL && v != NULL );
  if ( value != NULL && v != NULL ) {
    if ( n == 0 )
      _sntprintf( v, 64, _T("%.3f\t%.3f"), value->x, value->y );
    else
      _sntprintf( v, 64, _T("%d   %.3f\t%.3f"), n, value->x, value->y );
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Выдать свойства двумерного вектора.
           \en Get properties of two-dimensional vector. \~
  \details \ru Выдать свойства двумерного вектора MbVector.\n
           \en Get properties of two-dimensional vector MbVector.\n \~
  \ingroup Model_Properties
*/
// ---
template <class PropType> 
inline void GetCharValue( const PropType *, const MbVector * value, uint32 n, TCHAR * v ) 
{
  C3D_ASSERT( value != NULL && v != NULL );
  if ( value != NULL && v != NULL ) {
    if ( n == 0 )
      _sntprintf( v, 64, _T("%.3f\t%.3f"), value->x, value->y );
    else
      _sntprintf( v, 64, _T("%d   %.3f\t%.3f"), n, value->x, value->y );
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Выдать свойства двумерного нормированного вектора.
           \en Get properties of two-dimensional normalized vector. \~
  \details \ru Выдать свойства двумерного нормированного вектора MbDirection.\n
           \en Get properties of two-dimensional normalized vector MbDirection.\n \~
  \ingroup Model_Properties
*/
// ---
template <class PropType> 
inline void GetCharValue( const PropType *, const MbDirection * value, uint32 n, TCHAR * v ) 
{
  C3D_ASSERT( value != NULL && v != NULL );
  if ( value != NULL && v != NULL ) {
    double angle(0.0);
    if ( value->ax==0 && value->ay==0 )
      angle = 0.0;
    else
      angle = 180 / M_PI * atan2( value->ay, value->ax );
    if ( n == 0 )
      _sntprintf( v, 64, _T("%.3f\t"), angle );
    else
      _sntprintf( v, 64, _T("%d   %.3f\t"), n, angle );
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Выдать свойства трёхмерной точки.
           \en Get properties of three-dimensional point. \~
  \details \ru Выдать свойства трёхмерной точки MbCartPoint3D.\n
           \en Get properties of three-dimensional point MbCartPoint3D.\n \~
  \ingroup Model_Properties
*/
// ---
template <class PropType> 
inline void GetCharValue( const PropType *, const MbCartPoint3D * value, uint32 n, TCHAR * v ) 
{
  C3D_ASSERT( value != NULL && v != NULL );
  if ( value != NULL && v != NULL ) {
    if ( n == 0 )
      _sntprintf( v, 64, _T("%.3f\t%.3f\t%.3f"), value->x, value->y, value->z );
    else
      _sntprintf( v, 64, _T("%d   %.3f\t%.3f\t%.3f"), n, value->x, value->y, value->z );
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Выдать свойства трёхмерного вектора.
           \en Get properties of three-dimensional vector. \~
  \details \ru Выдать свойства трёхмерного вектора MbVector3D.\n
           \en Get properties of three-dimensional vector MbVector3D.\n \~
  \ingroup Model_Properties
*/
// ---
template <class PropType> 
inline void GetCharValue( const PropType *, const MbVector3D * value, uint32 n, TCHAR * v ) 
{
  C3D_ASSERT( value != NULL && v != NULL );
  if ( value != NULL && v != NULL ) {
    if ( n == 0 )
      _sntprintf( v, 64, _T("%.3f\t%.3f\t%.3f"), value->x, value->y, value->z );
    else
      _sntprintf( v, 64, _T("%d   %.3f\t%.3f\t%.3f"), n, value->x, value->y, value->z );
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Выдать свойства имени объекта.
           \en Get properties of object name. \~
  \details \ru Выдать свойства имени объекта MbName.\n
           \en Get properties of object name MbName.\n \~
  \ingroup Model_Properties
*/
// ---
template <class PropType> 
inline void GetCharValue( const PropType *, const MbName * value, uint32 n, TCHAR * v ) 
{
  C3D_ASSERT( v != NULL );
  if ( v != NULL ) {
    if ( value != NULL ) {
      c3d::string_t str;
      value->ToString( str );

      if ( n !=0 ) {
        _sntprintf( v, 64, _T("%d   "), n );
        _tcscat( v, str.c_str() );
      }
      else {
        _tcscpy( v, str.c_str() );
      }
    }
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Свойство объекта.
           \en The property of the object. \~
  \details \ru Обертка, реализующая свойство объекта с настройкой владения ним.\n
           \en Wrapper that implements property of an object with its ownership setting.\n \~
  \ingroup Model_Properties
*/
// ---
template <class Type>
class MathItemProperty : public MbProperty {
public :
  Type * value;  ///< \ru Объект. \en Object. 
  uint32 number; ///< \ru Номер.  \en Number. 
  
public :
  /// \ru Конструктор. \en Constructor. 
  MathItemProperty( MbePrompt name, Type * initValue, bool change, uint32 n = 0 ) 
    : MbProperty( name, change )
    , value( initValue )
    , number( n )
  {}
  /// \ru Деструктор. \en Destructor. 
  virtual ~MathItemProperty() {}
  
public :
  // \ru Выдать тип свойства. \en Get type of property. 
  virtual PrePropType IsA() const { return PropType<Type>::propId; }
  // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void        GetCharValue( TCHAR * v ) const { ::GetCharValue( this, value, number, v ); } 
  // \ru Выдать свойства неатомарного объекта. \en Get properties of the non-atomic object.
  virtual void        GetProperties( MbProperties & );
  // \ru Задать свойства неатомарного объекта объекта. \en Set properties of the non-atomic object.
  virtual void        SetProperties( const MbProperties & );
  // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t /*size*/ ) const { *(Type**)v = value; }
  // \ru Установить новое значение свойства. \en Set the new value of the property. 
  virtual void        SetPropertyValue( TCHAR * ) {} 
  
OBVIOUS_PRIVATE_COPY( MathItemProperty<Type> )
};


//------------------------------------------------------------------------------
/** \brief \ru Свойство объекта.
\en The property of the object. \~
\details \ru Обертка, реализующая свойство объекта с настройкой владения ним.\n
\en Wrapper that implements property of an object with its ownership setting.\n \~
\ingroup Model_Properties
*/
// ---
template <class Type>
class MathItemCopyProperty : public MbProperty {
public:
  Type   value;  ///< \ru Объект. \en Object. 
  uint32 number; ///< \ru Номер.  \en Number. 

public:
  /// \ru Конструктор. \en Constructor. 
  MathItemCopyProperty( MbePrompt name, const Type & initValue, bool change, uint32 n = 0 )
    : MbProperty( name, change )
    , value( initValue )
    , number( n )
  {}
  /// \ru Деструктор. \en Destructor. 
  virtual ~MathItemCopyProperty() {}

public:
  // \ru Выдать тип свойства. \en Get type of property. 
  virtual PrePropType IsA() const { return PropType<Type>::propId; }
  // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void        GetCharValue( TCHAR * v ) const { ::GetCharValue( this, &value, number, v ); }
  // \ru Выдать свойства неатомарного объекта объекта. \en Get properties of the non-atomic object.
  virtual void        GetProperties( MbProperties & );
  // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void       _GetPropertyValue( void * v, size_t /*size*/ ) const { *(Type**)v = const_cast<Type*>(&value); }
  // \ru Установить новое значение свойства. \en Set the new value of the property. 
  virtual void        SetPropertyValue( TCHAR * ) {}

OBVIOUS_PRIVATE_COPY( MathItemCopyProperty<Type> )
};


//------------------------------------------------------------------------------
/** \brief \ru Cвойство объекта.
           \en The property of the object. \~
  \details \ru Обертка, реализующая свойство объекта со счетчиком ссылок.\n
           \en Wrapper that implements property of an object with reference counter.\n \~
  \ingroup Model_Properties
*/
// ---
template <class Type>
class RefItemProperty : public MbProperty {
public :
  SPtr<Type> value;  ///< \ru Объект. \en Object. 
  uint32     number; ///< \ru Номер.  \en Number. 
  
public :
  /// \ru Конструктор. \en Constructor. 
  RefItemProperty( MbePrompt name, Type * initValue, bool change, uint32 n = 0 ) 
    : MbProperty( name, change )
    , value   ( initValue    )
    , number( n )
  {}  
  /// \ru Деструктор. \en Destructor. 
  virtual ~RefItemProperty() {} 

  // \ru Выдать тип свойства. \en Get type of property. 
  virtual PrePropType IsA() const { return PropType<Type>::propId; }
  // \ru Выдать строковое значение свойства. \en Get string value of the property. 
  virtual void  GetCharValue( TCHAR * v ) const { ::GetCharValue( this, value.get(), number, v ); } 
  // \ru Выдать свойства неатомарного объекта объекта. \en Get properties of the non-atomic object.
  virtual void  GetProperties( MbProperties & );
  // \ru Задать свойства неатомарного объекта объекта. \en Set properties of the non-atomic object.
  virtual void  SetProperties( const MbProperties & );
  // \ru Выдать значение свойства. \en Get value of the property. 
  virtual void _GetPropertyValue( void * v, size_t /*size*/ ) const { *(Type**)v = value.get(); }
  // \ru Установить новое значение свойства. \en Set the new value of the property.
  virtual void  SetPropertyValue( TCHAR * ) {} 
  
OBVIOUS_PRIVATE_COPY( RefItemProperty<Type> )
};


//------------------------------------------------------------------------------
/** \brief \ru Множество свойств объекта.
           \en Set of object properties. \~
  \details \ru Множество свойств объекта представляет собой контейнер, вызывающий деструктор своих элементов. \n
           \en Set of object properties is container that calls destructor of its elements. \n \~
  \ingroup Model_Properties
*/
// ---
class MATH_CLASS MbProperties : public PArray<MbProperty> 
{
  MbePrompt name; ///< \ru Имя объекта. \en A name of an object. 

public:
  /// \ru Конструктор. \en Constructor. 
  MbProperties() 
    : PArray<MbProperty>()
    , name( IDS_ITEM_0000 ) {}

public:
  /// \ru Выдать имя объекта. \en Get name of object. 
  MbePrompt &   SetName() { return name; } 
  /// \ru Выдать имя объекта. \en Get name of object. 
  size_t        GetName() const { return (size_t)name; } 
  /// \ru Выдать имя объекта. \en Get name of object. 
  MbePrompt     Name() const { return name; } 
  /// \ru Установить имя объекта. \en Set name of the object. 
  void          SetName( MbePrompt s ) { name = s; } 
  /// \ru Установить имя объекта. \en Set name of the object. 
  void          SetName( size_t s ) { name = (MbePrompt)s; } 
  /// \ru Найти свойство по имени и типу. \en Find property by name and type. 
  MbProperty *  FindByPrompt( MbePrompt, uint type ) const; 
  /// \ru Найти индекс свойства в массиве по имени и типу. \en Find index of property in array by name and type. 
  size_t        FindByPrompt( uint type, MbePrompt ) const; 

OBVIOUS_PRIVATE_COPY( MbProperties )
}; // MbProperties

//----------------------------------------------------------------------------------------
// \ru Выдать свойства неатомарного объекта объекта. \en Get properties of the non-atomic object.
//---
template<class Type>
void MathItemProperty<Type>::GetProperties( MbProperties & props )
{
  if ( value )
    value->GetProperties( props );
}

//----------------------------------------------------------------------------------------
// \ru Задать свойства неатомарного объекта объекта. \en Set properties of the non-atomic object.
//---
template<class Type>
void MathItemProperty<Type>::SetProperties( const MbProperties & props )
{
  if ( value )
    value->SetProperties( props );
}

//----------------------------------------------------------------------------------------
// \ru Выдать свойства неатомарного объекта объекта. \en Get properties of the non-atomic object.
//---
template<class Type>
void MathItemCopyProperty<Type>::GetProperties( MbProperties & props )
{
  value.GetProperties( props );
}

//----------------------------------------------------------------------------------------
// \ru Выдать свойства неатомарного объекта объекта. \en Get properties of the non-atomic object.
//---
template<class Type>
void RefItemProperty<Type>::GetProperties( MbProperties & props ) 
{
  if ( value )
    value->GetProperties( props );
}

//----------------------------------------------------------------------------------------
// \ru Выдать свойства неатомарного объекта объекта. \en Get properties of the non-atomic object.
//---
template<class Type>
void RefItemProperty<Type>::SetProperties( const MbProperties & props ) 
{
  if ( value )
    value->SetProperties( props );
}


#endif // __PROPERTY_H
