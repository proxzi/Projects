//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Тестовый генератор 3D-сопряжений
         \en Test generator of 3D-mates \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GCM_MATES_GENERATOR_H
#define __GCM_MATES_GENERATOR_H

#include <gcm_geom.h>
#include <gcm_constraint.h>
#include <gcm_reposition.h>
#include <gce_precision.h>
#include <mt_ref_item.h>
#include <tool_cstring.h>

#include <list>

class MtGeomSolver;

//----------------------------------------------------------------------------------------
// Параметры сопряжений.
// ---
struct TMParameters
{
  typedef GCM_alignment AlignCondition;

  GCM_c_type    matetype; // Constraint type.
  GCM_alignment align;    // Alignment condition.  
  double        realpar;  // Dimension value.

  TMParameters( AlignCondition al, MtMateType mtype, double par = 0. )
    : align   ( al )
    , matetype( mtype )
    , realpar ( par )
  {}
  TMParameters( GCM_c_type mtype, double par = 0.0, GCM_alignment al = GCM_NO_ALIGNMENT )
    : align   ( al )
    , matetype( mtype )
    , realpar ( par )
  {}
};

//----------------------------------------------------------------------------------------
/// \ru Размеры кирпича. \en Box sizes.
// ---
struct TMBoxSize
{
public:
  double length; ///< \ru Длина (вдоль OX). \en Length (along OX). 
  double width;  ///< \ru Ширина (вдоль OY). \en Width (along OY). 
  double height; ///< \ru Высота (вдоль OZ). \en Height (along OZ). 
  double radius; ///< \ru Радиус отверстия посередине. Если < MIN_RADIUS, значит сплошной кирпич без отверстий. \en Radius of hole in the middle. If < MIN_RADIUS therefore a solid box without holes. 

public:
  TMBoxSize()
    : length( 30. )
    , width ( 60. )
    , height( 90. )
    , radius( 20. )
  {}

  TMBoxSize( double l, double w, double h, double r )
    : length( l )
    , width ( w )
    , height( h )
    , radius( r )
  {}
};

//----------------------------------------------------------------------------------------
// \ru Элементарный кирпич для наложения сопряжений. \en Elementary box for the overlay of mates. 
// ---
class MATH_CLASS TMBox : public ItGeom
                       , public MtRefItem
{
public:
  enum MateMarker ///< \ru маркер для наложения сопряжения. \en marker for overlay of mate. 
  {
    front, 
    back,
    left, 
    right,
    up,
    down,
    axis,
    distance
  };

private:
  MbPlacement3D   place; // \ru ЛСК кирпича. \en LCS of box. 
  TMBoxSize       size;  // \ru Размер кирпича. \en Box size. 
  c3d::mt_string  name;  // \ru Имя. \en Name. 

public:
  TMBox( const MbPlacement3D & p, const TMBoxSize & sz, const c3d::mt_char * n = _T("B") ); // \ru Конструктор. \en Constructor. 

public:
  /// \ru Задать новую ЛСК. \en Set the new LCS. 
  void       SetPlacement( const MbPlacement3D & p ) { place.Init( p ); }
  void       SetName( const c3d::mt_char * n ) { name = n; } // \ru Задать имя. \en Set the name. 
  double     Length() const { return size.length; }   // \ru Выдать длину. \en Get the length. 
  double     Width() const { return size.width; }     // \ru Выдать ширину. \en Get the width. 
  double     Height() const { return size.height; }   // \ru Выдать высоту. \en Get the height. 
  double     Radius() const { return size.radius; }   // \ru Выдать радиус. \en Get the radius. 
  bool       IsHoled() const { return size.radius > c3d::MIN_RADIUS - GcPrecision::lengthRegion; } // \ru С цилиндром ли кирпич. \en Whether there is a hole. 
  MbVector3D CylinderAxis() const { return place.GetAxisX(); } // \ru выдать ось цилиндра. \en Get the cylinder axis. 

public: // Реализация ItGeom

  /// \ru Выдать положение объекта ItGeom; \en Get position of ItGeom object;  
  virtual       void       GetPlacement( MbPlacement3D & p ) const { p.Init(place); }
  /// \ru Выдать null-terminated строку имени геометрического объекта \en Get null-terminated name string of geometric object   
  virtual const c3d::mt_char * GetName() const { return name.c_str(); }  
  virtual       refcount_t AddRef() const { return MtRefItem::AddRef(); }
  virtual       refcount_t Release() const { return MtRefItem::Release(); }

private:
  TMBox();
  TMBox( const TMBox & );
  TMBox & operator = ( const TMBox & );
};


//----------------------------------------------------------------------------------------
// \ru Наложение сопряжения на 2 кирпича. \en Overlaying mate onto two boxes. 
// ---
class MATH_CLASS MtBoxConstraint : public MtRefItem
                                 , public ItConstraintItem                      
{
  SPtr<TMBox>       box1;       // \ru Кирпич 1. \en Box 1.
  SPtr<TMBox>       box2;       // \ru Кирпич 2. \en Box 2.
  TMBox::MateMarker side1;      // \ru Маркер сопряжения 1. \en Marker of mate 1.
  TMBox::MateMarker side2;      // \ru Маркер сопряжения 2. \en Marker of mate 2.
  GCM_alignment     aligncond;  // \ru Условие выравнивания. \en Condition of alignment.
  MtMateType        matetype;   // \ru Тип сопряжения. \en The mate type.
  double            realpar;    // \ru Расстояние. \en Distance.
  MtResultCode3D    rescode;    // \ru Коды ошибки сопряжения. \en Error code of mate.
    
public:
  MtBoxConstraint( TMBox & b1, TMBox::MateMarker s1, TMBox & b2, TMBox::MateMarker s2, TMParameters );

public: // \ru Запросы (const-методы) \en Requests (const-methods) 
  virtual GCM_alignment   AlignType() const { return aligncond; }                 // \ru Выдать параметр условия выравнивания \en Get the parameter of alignment condition 
  virtual GCM_angle_type  AngleType() const { return GCM_NONE_ANGLE; }            // \ru Выдать тип угла (3D или планарный) \en Get the angle type (3D or planar)       
  virtual GCM_geom_axis   AxisOfPlanarAngle() const { return GCM_geom_axis(); }   // \ru Выдать ось для планарного углового сопряжения, заданную в ЛСК некоторого тела \en Get the axis for planar angular mate. Axis is given in the LCS of some solid 
  virtual MbVector3D      AxisOf3DAngleType() const { return MbVector3D::zero; }  // \ru Взять ось для планарного углового сопряжения \en Get the axis for planar angular mate 
  virtual MtMateType      ConstraintType() const { return matetype; }             // \ru Выдать тип сопряжения \en Get the mate type   
  virtual ItGeomPtr       GeomItem( int nb ) const { return (nb==1)? box1.get(): box2.get(); }                      // \ru Выдать первый сопрягаемый объект \en Get the first mating object 
  virtual double          DimParameter() const { return realpar; }                // \ru Выдать вещественный параметр \en Get the real parameter 
  virtual GCM_tan_choice  TangencyChoice() const { return GCM_TAN_NONE; }         // \ru Выдать вариант касания \en Get the tangency choice 
  /// \ru Диагностический код ошибки, прикрепленный к данному ограничению. \en Diagnostic error code attached to this constraint. 
  virtual MtResultCode3D  ErrorCode() const { return rescode; }
  virtual VERSION         Version() const { return GetCurrentMathFileVersion(); } // \ru Выдать версию сопряжения, которая совпадает с версией потока \en Get the mate version which same as the stream version

public:
  void  SetDistance( double dist ) { realpar = dist; }

public: // \ru Методы для обратной связи (задающие) \en Callback methods 
  /// \ru Задать код ошибки для неудовлетворенного сопряжения \en Set the error code for unsatisfied mate 
  virtual void  SetErrorCode( MtResultCode3D res ) { rescode = res; }
  /// \ru Задать ось для углового сопряжения с трехмерным типом измерения; \en Set axis for angular mate with three-dimensional type of dimension; 
  virtual void  SetAxisOf3DAngleType( const MbVector3D & /*axis*/ ) { /*planarang.axis = axis;*/ }

public: // \ru Методы для Smart-указателей \en The methods for Smart-pointers 
  virtual refcount_t  AddRef() const { return MtRefItem::AddRef(); }
  virtual refcount_t  Release() const { return MtRefItem::Release(); }

private:
  virtual MtGeomVariant _LinkageItem( int geomNb ) const;

private:
  MtBoxConstraint();
  MtBoxConstraint( const MtBoxConstraint & );
  MtBoxConstraint & operator = ( const MtBoxConstraint & );
};

//----------------------------------------------------------------------------------------
// \ru Земля. \en Ground. 
// ---
class MATH_CLASS TMGround : public ItGeom
                          , public MtRefItem
{
private:
  MbPlacement3D place;

public:
  explicit TMGround( const MbPlacement3D & p );

public:
  /// \ru Выдать null-terminated строку имени геометрического объекта \en Get null-terminated name string of geometric object   
  virtual const TCHAR * GetName() const;  
  virtual refcount_t  AddRef() const { return MtRefItem::AddRef(); }
  virtual refcount_t  Release() const { return MtRefItem::Release(); }

private:
  /// \ru Выдать положение объекта ItGeom; \en Get position of ItGeom object;  
  virtual  void  GetPlacement( MbPlacement3D & p ) const { p.Init(place); }

private:
  TMGround();
  TMGround( const TMGround & );
  TMGround & operator = ( const TMGround & );
};

//----------------------------------------------------------------------------------------
// \ru Управление положением в сборке. \en Position control in the assembly. 
// ---
struct MATH_CLASS TMBoxPositioner : public MtRefItem
                                  , public ItPositionManager
{
private:
  TMGround & ground;

public:
  explicit TMBoxPositioner( TMGround & );
  TMBoxPositioner( const TMBoxPositioner & );

public:
  /// \ru Установить новое положение объекта \en Set new position of the object 
  virtual void            Reposition( ItGeom & geom, const MbPlacement3D & pos );
  /// \ru Выдать геометрический объект-земля, со степенью свободы = 0 (жёстко привязанный к ГСК); \en Get geometric object- ground with the degree of freedom = 0 (hard bound to GCS); 
  virtual ItGeom &        GetGround() const { return ground; }
  /// \ru Выдать характер связи для пары сопрягаемых тел (направленность соединения) \en Get the link character for pair of mating solids (direct connection) 
  virtual GCM_dependency  GetJointStatus( const ItGeom &, const ItGeom & ) const { return GCM_NO_DEPENDENCY; }
  virtual refcount_t      AddRef() const { return MtRefItem::AddRef(); }
  virtual refcount_t      Release() const { return MtRefItem::Release(); }

private:
  TMBoxPositioner();
  TMBoxPositioner & operator = ( const TMBoxPositioner & );
};

typedef std::vector<SPtr<TMBox> > MtBoxVector;
typedef std::vector<MtBoxVector>  MtBlocksVector;

//----------------------------------------------------------------------------------------
/// \ru Генератор сборок. \en Assembly generator. 
// ---
class MATH_CLASS AssemblyGenerator
{
public:
  enum TMMateType ///< \ru Тип связи между блоками в сборке. \en Type of connection between the bricks in the assembly. 
  {
    tmt_Rigid1Brick = 1,
    tmt_Rigid3Bricks,
    tmt_Rigid2Axis,
    tmt_NonRigid2Axis,
    tmt_NonRigidAxisDist,
    tmt_NonRigidAxis
  };

  enum TMBrickMateType ///< \ru Тип связи между кирпичами. \en Type of connection between the boxes. 
  {
    tbmt_1Mate = 1, ///< \ru Совпадение протипоположных плоскостей. \en Coincidence of opposite planes. 
    tbmt_2Mate = 2, ///< \ru Совпадение протипоположных плоскостей + 1-ой пары сонаправленных. \en Coincidence of opposite planes + 1-pair of codirected. 
    tbmt_3Mate = 3, ///< \ru Совпадение протипоположных плоскостей + 2-ух пар сонаправленных (жесткая связь). \en Coincidence of opposite planes + 2-pairs of codirected (hard link). 
    tbmt_Rigid = tbmt_3Mate ///< \ru  Жесткая связь. \en  Rigid link. 
  };

public:
  std::list<SPtr<MtBoxConstraint> > dimConstrs;

private:
  MtGeomSolver & manager; ///< \ru Решатель сборки. \en Solver of the assembly. 
  
public:
  AssemblyGenerator( MtGeomSolver & m ) : manager( m ), dimConstrs() {}

private:
  AssemblyGenerator();
  AssemblyGenerator( const AssemblyGenerator & );
  AssemblyGenerator & operator = ( const AssemblyGenerator & );

public:
  /// \ru Сгенерировать линию из кирпичей. \en Generate a line from boxes. 
  size_t GenerateLine( MtBoxVector & line, size_t n, TMBrickMateType mttype = tbmt_Rigid ); 
  /// \ru Сгенерировать стенку из кирпичей. \en Generate a wall from boxes. 
  size_t GenerateWall( MtBoxVector & wall, size_t n, TMBrickMateType mttype = tbmt_Rigid ); 
  /// \ru Сгенерировать куб из кирпичей. \en Generate a cube from boxes. 
  size_t GenerateCube( MtBoxVector & cube, size_t n, TMBrickMateType mttype = tbmt_Rigid ); 
  /// \ru Сгенерировать фрактал. \en Generate fractal. 
  size_t GenerateFractal( MtBlocksVector & fractal, size_t n, TMMateType mttype = tmt_Rigid3Bricks, TMBrickMateType bmttype = tbmt_3Mate );
  /// \ru Сгенерировать нежестко сопряженную сборку с распределенными степенями свободы. \en Generate a non-rigid mating assembly with distributed degrees of freedom. 
  size_t NonRigidDistributedDoF( MtBlocksVector & assembly, size_t nBlocks
                               , TMMateType mttype = tmt_NonRigidAxis, TMBrickMateType bmttype = tbmt_3Mate );
  /// \ru Сгенерировать жестко сопряженную сборку с распределенными степенями свободы. \en Generate a rigid mating assembly with distributed degrees of freedom. 
  size_t RigidDistributedDoF( MtBlocksVector & assembly, size_t nRings, size_t nBlocksInRing
                            , TMMateType matetype = tmt_Rigid2Axis, TMBrickMateType bmttype = tbmt_3Mate, double dist = 0. );

  /// \ru Передвинуть кирпичи. \en Shift boxes. 
  void   ShiftBoxes( MtBoxVector & boxes, const MbVector3D & shift, bool comulative, bool shiftfirst = false );
  /// \ru Передвинуть блоки. \en Shift blocks.  
  void   ShiftBoxes( MtBlocksVector & boxes, const MbVector3D & shift, bool comulative, bool shiftfirst = false );
  /// \ru Повернуть кирпичи. \en Rotate boxes. 
  void   RotateBoxes( MtBoxVector & boxes, const MbVector3D & angles, bool comulative );
  /// \ru Повернуть блоки. \en Rotate blocks. 
  void   RotateBoxes( MtBlocksVector & boxes, const MbVector3D & angles, bool comulative );
  
private:
  /// \ru Сгенерировать N кирпичей. \en Generate N boxes.
  void   GenerateNBoxes( MtBoxVector & boxes, size_t n, const TMBoxSize & size ) const;  
  void   SetBoxesNames( const MtBoxVector & boxes ); // \ru Задать имена кирпичей. \en Set names for boxes. 
  size_t CreateBlock( MtBoxVector & block, TMBrickMateType bmttype, bool solve = true ); // \ru Создать блок. \en Create a block. 
  void   GetFractal( size_t & mtCnt, MtBlocksVector & boxes, size_t nBlocks, TMMateType mttype, TMBrickMateType bmttype, size_t ind = 0 ); // \ru Создать фрактал. \en Create a fractal. 
};

#endif // __GCM_MATES_GENERATOR_H
