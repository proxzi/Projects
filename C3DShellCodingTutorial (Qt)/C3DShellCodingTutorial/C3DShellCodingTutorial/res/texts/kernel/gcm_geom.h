//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Геометрические типы данных
         \en Geometrical types of data \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GCM_GEOM_H
#define __GCM_GEOM_H

#include <tool_cstring.h>
#include <templ_sptr.h>
#include <mb_matrix3d.h>
#include <mb_placement3d.h>
#include <marker.h>
#include <gcm_types.h>
#include <cur_line3d.h>

/**
  \addtogroup GCM_3D_ObjectAPI
  \{
*/

//----------------------------------------------------------------------------------------
//
//---
typedef GCM_geom        MtGeomId;
typedef GCM_constraint  MtConstraintId;
typedef GCM_geom        MtPatternId;
typedef GCM_g_type      MtGeomType;
typedef GCM_c_type      MtMateType;

/** \} */

//----------------------------------------------------------------------------------------
/** \brief    \ru Геометрический объект. \en Geometrical object. \~
    \details  \ru Геометрический объект этого типа данных, характеризуется матрицей 
   трансформации, которая переводит его в настоящее положение из некоторого стандартного 
   положения. Подразумевается, что для каждого типа объекта имеется 
   стандартное положение, которое, как правило, совпадает с мировой системой 
   координат.\n
      Например,  если экземпляром ItGeom является точка, то матрица TransMatrix()
   задаст положение  точки, как преобразование начала координат в некоторое 
   произвольное место пространства.\n
      Если экземпляром ItGeom является жесткое тело в пространстве, то матрица TransMatrix()
   будет служить в качестве ЛСК этого тела и задавать его положение в пространстве 
   моделирования.
           \en Geometric object of this data type is described by a matrix 
  of transformation which transforms this object to real position from some 
  standard position. The implication is that each type of object has 
  a standard position which usually coincides with the global system 
  of coordinates. \n
    For example, if ItGeom is a point, then the matrix TransMatrix()
  sets the position of a point as the transformation of the origin to some 
  arbitrary place of the space.\n 
    If ItGeom is rigid solid in the space, then the matrix TransMatrix()
  can be used as LCS of this solid and set its position in the space 
  of modeling. \~
    \ingroup GCM_3D_ObjectAPI
*/
//---
struct ItGeom
{
  MtGeomId objectId; // (!) Будет закрыто
  ItGeom() : objectId( GCM_NULL ) {}
  /// \ru Тип геометрического объекта. \en Type of geometric object. \~
  virtual GCM_g_type    GeomType() const { return GCM_LCS; }
  /// \ru Строковое имя геометрического объекта. \en String name of geometric object.
  virtual const TCHAR * GetName() const = 0;
  /// \ru Выдать положение детали в виде ортонормированной ЛСК. \en Get position of part as orthonormalized LCS.
  virtual void          GetPlacement( MbPlacement3D & pl ) const { pl = MbPlacement3D::global; }
  /// \ru Выдать трансформацию из стандартного положения. \en Get transformation from standard position. \~
  inline  void          GetTransMatrix( MbMatrix3D & ) const;
  /// \ru Трансформация из стандартного положения. \en Transformation from the standard position. \~
          MbMatrix3D    TransMatrix() const;

public: /*
          Reference counting support.
        */
  virtual refcount_t  AddRef() const = 0;
  virtual refcount_t  Release() const = 0;

protected:
  virtual ~ItGeom() {}

private:  // It will be removed ... use GetPlacement instead.
  virtual void  GetGeomPlacement( MbPlacement3D & ) const {}
};

/*
  ItGeom as pointer type.
*/
typedef ItGeom *  ItGeomPtr;

//----------------------------------------------------------------------------------------
// \ru Трансформация из стандартного положения \en Transformation from the standard position 
//---
inline MbMatrix3D ItGeom::TransMatrix() const
{
  MbMatrix3D tValue;  
  GetTransMatrix( tValue );
  return tValue;
}

//----------------------------------------------------------------------------------------
//  \ru Выдать трансформацию из стандартного положения. 
//  \en Get transformation from standard position.
//---
inline void ItGeom::GetTransMatrix( MbMatrix3D & mat ) const
{
  MbPlacement3D place;
  GetPlacement( place );
  place.GetMatrixFrom( mat );
}

//----------------------------------------------------------------------------------------
// Internal data types
//---
struct MtUnifiedGeom;
class  MtParGeom;


//----------------------------------------------------------------------------------------
/** \brief \ru Геометрический объект, аргумент геометрического ограничения.
           \en Geometric object, argument of geometric constraint. \~
    \ingroup GCM_3D_ObjectAPI
*/
//---
class GCM_CLASS MtGeomVariant
{
public:
  MtGeomVariant() : m_value( NULL ) {}
  MtGeomVariant( const MbCartPoint3D & );
  MtGeomVariant( const MtGeomVariant & );
  MtGeomVariant( const MtParGeom & g ) : m_value( NULL ) { Assign(g); }
  MtGeomVariant( const GCM_g_type );
  MtGeomVariant( MtParGeom & g ) : m_value( NULL ) { Share(g); }
  MtGeomVariant & operator = ( const MtGeomVariant & gVar ) { return Assign( gVar ); }
 ~MtGeomVariant();

public:
  /// \ru Тип геометрии, которому удовлетворяет объект. \en Type of geometry which is satisfied by the object.
  MtGeomType   GeomType() const;
  /// \ru Выдать трансформацию объекта. \en Get transformation of the object.
  MbMatrix3D & GetTransMatrix( MbMatrix3D & ) const;
  /// \ru Определить, является ли объект пустым. \en Define whether the object is empty.
  bool         IsNull() const;

public: /* Assigning methods 
        */   
  MtGeomVariant &  Assign( const MtGeomVariant & );
  MtGeomVariant &  Assign( MtParGeom & );
  MtGeomVariant &  Assign( const MtParGeom & );
  MtGeomVariant &  Assign( MtGeomType, const MbCartPoint3D & org, const MbVector3D & zAxis
                         , const MbVector3D & xAxis, double r1 = 0.0, double r2 = 0.0 );
  template<class GeomDS>
  MtGeomVariant &  Assign( GeomDS * );
  MtGeomVariant &  Reset(); ///< \ru Задать как тип GCM_NULL_GTYPE. \ru Set as GCM_NULL_GTYPE type. \~
  MtGeomVariant &  SetAsPoint( const MbCartPoint3D & );
  MtGeomVariant &  SetAsLine( const MbCartPoint3D & org, const MbVector3D & dir );  
  MtGeomVariant &  SetAsPlane( const MbCartPoint3D & org, const MbVector3D & normal );
  MtGeomVariant &  SetAsPlane( const MbPlacement3D & );
  MtGeomVariant &  Transform( const MbMatrix3D & ); 

public:  /* Methods for internal use
         */
  const MtParGeom & ParGeom() const;
  MtUnifiedGeom &   GetTuple( MtUnifiedGeom & ) const;

private:
  MtGeomVariant & Share( MtParGeom & );

private:
  MtParGeom * m_value;
};

//----------------------------------------------------------------------------------------
//
//---
template<class GeomDS>
MtGeomVariant & MtGeomVariant::Assign( GeomDS * gDs )
{
  if ( gDs )
  {
    return Assign( *gDs );
  }
  return Reset();
}


//----------------------------------------------------------------------------------------
/** \brief \ru Структура данных сопрягаемой геометрии.
           \en Data structure for matched geometry. \~
  \details \ru Эта структура используется для передачи информации о геометрическом 
  объекте, который участвует в ограничениях. Геометрический объект, передаваемый
  через эту структуру данных, может быть задан в ЛСК жесткого тела или в мировой 
  системе координат модели. \n  
    Следует учитывать, что геометрический объект, возвращаемый функцию 
  #MtMatingGeometry::GetMatingGeom(), задан в ЛСК с матрицей 
  #MtMatingGeometry::LCSMatrix(), т.е. решатель внутри интерпретирует #MtMatingGeometry
  как объект #MtMatingGeometry::GetMatingGeom(), заданный в #MtMatingGeometry::LCSMatrix().
           \en This structure is used for passing information about geometric 
  object involved in constraints. Geometric object passed
  via this data structure can be specified in LCS of a rigid solid or in the world 
  coordinate system. \n
    It should be taken into account that the geometric object returned from the function 
  #MtMatingGeometry::GetMatingGeom(), is given in LCS with matrix 
  #MtMatingGeometry::LCSMatrix(), i.e. the solver interprets  #MtMatingGeometry
  as object #MtMatingGeometry::GetMatingGeom() specified in #MtMatingGeometry::LCSMatrix(). \~
          \ingroup GCM_3D_ObjectAPI
*/
//---
class MtMatingGeometry
{
public:
  enum Orient ///< \ru Трехзначное свойство ориентации \en Three-valued property of orientation 
  {
    Opposite   = 0, ///< \ru "Обратное направление" \en "Reverse direction" 
    Cooriented = 1, ///< \ru "Прямое направление" \en "Forward direction" 
    Unoriented = 2  ///< \ru Ориентация не свойственна или "Прямое направление" \en Orientation is nonrelevant or "Forward direction" 
  };
  static const MtGeomType geom_Marker = GCM_MARKER;

private:
  MtGeomType              myGeomType;     // \ru Кодирует тип сопрягаемой геометрии \en Encodes type of mating geometry   
  SPtr<const MbSpaceItem> myGeom;         // \ru Геометрический объект сопряжения \en Geometric object of mating 
  Orient                  myOrientation;  // \ru Ориентация геометрического объекта myMatingGeom \en Orientation of geometric object myMatingGeom   
  MbMatrix3D *            myLCSMatrix;    // \ru Матрица преобразования (ЛСК сопрягаемого тела) \en Transformation matrix (LCS of the mating solid) 
  
public:
  MtMatingGeometry()
    : myGeom( NULL )
    , myOrientation( Unoriented )
    , myLCSMatrix( NULL )
  {}
  ~MtMatingGeometry()
  {
    _ClearMatrix();
  }

public:
  /// \ru Выдать тип сопрягаемой геометрии \en Get type of mating geometry 
        MtGeomType    GetGeomType() const { return myGeomType; }        
  /// \ru Выдать ориентацию; \en Get orientation; 
        Orient        GetOrientation() const { return myOrientation; }
        /// \ru Выдать геометрический объект сопряжения. Если =NULL, то это точка, заданная MtMatingGeometry::myMatingPoint; \en Get geometric object of the mating. If =NULL, then this is a point specified by MtMatingGeometry::myMatingPoint; 
  const MbSpaceItem * GetMatingGeom() const { return myGeom; }
        /// \ru Выдать матрицу ЛСК, в которой задан геометрический объект сопряжения \en Get matrix of LCS in which the geometric object of the mating is specified 
  const MbMatrix3D &  LCSMatrix() const;


  /**
    \brief \ru Задать структуру данных как представление прямой.
           \en Set the data structure to line representation.  \~
  */
  void  SetAsLine( const MbCartPoint3D &, const MbVector3D & );

  /** \brief  \ru Инициализировать структуру данных маркером.
              \en Initialize the data structure with a marker.\~  */
  void  SetAsMarker( const MbCartPoint3D &, const MbVector3D & z, const MbVector3D & x );
  /**
    \brief  \ru Инициализировать структуру данных маркером.
            \en Initialize the data structure with a marker.\~
    \param  \ru gArg  маркер (! аргумент не передается во владение структуры)
            \en gArg is marker (!  the argument is not transferred to the structure ownership) \~
  */
  void  SetAsMarker( const MbMarker & );

  /// \ru Присвоить структуре значение ЛСК; \en Assign this data structure with a value of LCS \~ 
  void  SetAsLCS( const MbPlacement3D & lcs );
  void  Assign( const MbPlacement3D & lcs ) { SetAsLCS(lcs); }

  /// \ru Инициализировать структуру данных кривой или поверхностью; \en Initialize data structure with a curve or a surface; 
  /**
    \param \ru gItem геометрический объект, подкласс MbSpaceItem (! передается во владение структуры)
           \en gItem is geometric object, subclass of MbSpaceItem (! transferred to the structure ownership) \~
    \param \ru gDir  флаг ориентации геометрического объекта
           \en gDir is flag of geometric object orientation \~ 
    \param \ru gSpan матрица, задающая подпространство объекта
           \en gSpan is matrix specifying subspace of the object \~
  */
  void  SetAsMatingGeomItem( SPtr<const MbSpaceItem> gItem, Orient gDir, const MbMatrix3D & gSpan );
  /// \ru Задать пустой объект \en Specify an empty object 
  void  SetNull();

public:
  /*
    (!) Deprecated
    \brief  \ru Инициализировать структуру данных маркером или ЛСК.
            \en Initialize the data structure with a marker or a LCS.\~
    \param  \ru gType тип геометрии, для которой маркер является аргументом (описателем геометрии)
            \en gType is a type of geometry for which the marker is an argument (geometry descriptor) \~
    \param  \ru gArg  маркер (! аргумент не передается во владение структуры)
            \en gArg is marker (!  the argument is not transferred to the structure ownership) \~
  */
  void  SetAsMarker( MtGeomType gType, const MbMarker & gArg );

  // Internal use only
  MtGeomVariant GeomVariant( VERSION c3dVer ) const;

private:
  void _SetLCSMatrix( const MbMatrix3D & );
  void _ClearMatrix();

private: // \ru Реализовать при необходимости \en Implement if necessary 
  MtMatingGeometry( const MtMatingGeometry & );
  MtMatingGeometry & operator = ( const MtMatingGeometry & );
};


//----------------------------------------------------------------------------------------
// \ru Выдать матрицу ЛСК, в которой задан геометрический объект сопряжения \en Get matrix of LCS in which the geometric object of the mating is specified 
//---
inline const MbMatrix3D & MtMatingGeometry::LCSMatrix() const
{
  if ( myLCSMatrix != NULL )
    return *myLCSMatrix;
  return MbMatrix3D::identity;
}

//----------------------------------------------------------------------------------------
// Задать структуру данных как представление прямой.
//---
inline void MtMatingGeometry::SetAsLine( const MbCartPoint3D & org, const MbVector3D & dir )
{
  myGeomType = GCM_LINE;
  myGeom = new MbLine3D( org, dir );
  myOrientation = Cooriented;
  _ClearMatrix();
}

//----------------------------------------------------------------------------------------
// \ru Инициализировать структуру данных кривой или поверхностью; \en Initialize data structure with a curve or a surface; 
//---
inline void MtMatingGeometry::SetAsMarker( MtGeomType gType, const MbMarker & gArg )
{
  C3D_ASSERT( gType == GCM_MARKER );
  myGeomType = gType;
  myGeom = new MbMarker( gArg );
  myOrientation = Unoriented;
  _ClearMatrix();
}

//----------------------------------------------------------------------------------------
// 
//---
inline void MtMatingGeometry::SetAsMarker( const MbMarker & gArg )
{
  myGeomType = GCM_MARKER;
  myGeom = new MbMarker( gArg );
  myOrientation = Unoriented;
  _ClearMatrix();
}

//----------------------------------------------------------------------------------------
/* \ru Инициализировать структуру данных маркером.
   \en Initialize the data structure with a marker.\~  */
//---
inline void MtMatingGeometry::SetAsMarker( const MbCartPoint3D & org, const MbVector3D & z, const MbVector3D & x )
{
  myGeomType = GCM_MARKER;
  myGeom = new MbMarker( org, z, x );
  myOrientation = Unoriented;
  _ClearMatrix();
}

//----------------------------------------------------------------------------------------
// \ru Присвоить структуре значение ЛСК; \en Assign this data structure with a value of LSC
//---
inline void MtMatingGeometry::SetAsLCS( const MbPlacement3D & lcs )
{
  myGeomType = GCM_LCS;  
  myGeom = NULL; // new MbMarker( MbCartPoint::origin, MbVector3D::zAxis, MbVector3D::xAxis );
  myOrientation = Unoriented;
  _SetLCSMatrix( lcs.GetMatrixFrom() );
}

//----------------------------------------------------------------------------------------
// Initialize the data structure by a curve or a surface 
//---
inline void MtMatingGeometry::SetAsMatingGeomItem(  SPtr<const MbSpaceItem> gItem
                                                  , Orient gDir
                                                  , const MbMatrix3D & gSpan )
{    
  if ( gItem )
  {
    myGeomType = GCM_LAST_GTYPE;
    myGeom = gItem;
    myOrientation = gDir;      
    _SetLCSMatrix( gSpan );
  }
}

//----------------------------------------------------------------------------------------
//
//---
inline void MtMatingGeometry::_ClearMatrix()
{
  if ( myLCSMatrix != NULL )
  {
    delete myLCSMatrix;
  }
  myLCSMatrix = NULL;
}

//----------------------------------------------------------------------------------------
//
//---
inline void MtMatingGeometry::_SetLCSMatrix( const MbMatrix3D & gSpan )
{
  if ( gSpan.IsSingle() )
  {
    _ClearMatrix(); // \ru Единичная матрица эквивалентна её очистке \en Unit matrix is equal to its flush 
  }
  else
  {
    if ( myLCSMatrix == NULL )
      myLCSMatrix = new MbMatrix3D( gSpan );
    else
      *myLCSMatrix = gSpan;
  }
}

//----------------------------------------------------------------------------------------
// \ru Задать пустой объект \en Specify an empty object 
//---
inline void MtMatingGeometry::SetNull()
{
  myGeomType = GCM_NULL_GTYPE;
  myGeom = NULL;
  myOrientation = Unoriented; 
  _ClearMatrix();
}

//----------------------------------------------------------------------------------------
// \ru Конвертировать структуру MtMatingGeometry в аргумент ограничения \en Convert the structure MtMatingGeometry to the argument of constraint 
//---
GCM_FUNC(MtGeomVariant) GeomArgument( const MtMatingGeometry &, VERSION constraintVersion );

//----------------------------------------------------------------------------------------
//
//---
typedef       ItGeom *  IfGeomPtr;  // deprecated
typedef const ItGeom *  IfConstGeomPtr; // deprecated

#endif // __IT_GEOM_H

// eof
