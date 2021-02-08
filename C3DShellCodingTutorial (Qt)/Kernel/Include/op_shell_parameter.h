////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Параметры операций над телами.
         \en Parameters of operations on the solids. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __OP_SHELL_PARAMETERS_H
#define __OP_SHELL_PARAMETERS_H


#include <templ_rp_array.h>
#include <templ_array2.h>
#include <templ_css_array.h>
#include <math_version.h>
#include <math_define.h>
#include <mb_nurbs_function.h>
#include <op_binding_data.h>
#include <op_boolean_flags.h>
#include <cr_split_data.h>
#include <vector>
#include <utility>


class  MATH_CLASS  MbPoint3D;
class  MATH_CLASS  MbPolyCurve3D;
class  MATH_CLASS  MbPolyline3D;
class  MATH_CLASS  MbSurface;
class  MATH_CLASS  MbSurfaceCurve;
class  MATH_CLASS  MbPlane;
class  MATH_CLASS  MbCurveEdge;
class  MATH_CLASS  MbFace;
class  MATH_CLASS  MbFaceShell;
class  MATH_CLASS  MbSolid;
class  MATH_CLASS  MbSNameMaker;
class              MbRegTransform;
class              MbRegDuplicate;


//------------------------------------------------------------------------------
/** \brief \ru Параметры скругления или фаски ребра.
           \en Parameters of fillet or chamfer of edge. \~
  \details \ru Параметры скругления или фаски ребра содержат информацию, необходимую для выполнения операции. \n
           \en The parameter of fillet or chamfer of edge contain Information necessary to perform the operation. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS SmoothValues {
public:
  /// \ru Способы обработки углов стыковки трёх рёбер. \en Methods of processing corners of connection by three edges.
  enum CornerForm {
    ec_pointed = 0, ///< \ru Обработка угла отсутствует. \en Processing of corner is missing.
    ec_either  = 1, ///< \ru Стыкующиеся в одной точке три ребра обрабатываются в порядке внутренней нумерации ребер без учета выпуклости и вогнутости. \en Mating at one point of three edges are processed in the order of internal indexation of edges without convexity and concavity.
    ec_uniform = 2, ///< \ru Если в точке стыкуются два выпуклых (вогнутых) и одно вогнутое (выпуклое) ребро, то первым  обрабатывается вогнутое (выпуклое) ребро. \en If two convex (concave) and one concave (convex) edge are mated at the point, then concave (convex) edge is processed at the first.
    ec_sharp   = 3, ///< \ru Если в точке стыкуются два выпуклых (вогнутых) и одно вогнутое (выпуклое) ребро, то первыми обрабатываются выпуклые (вогнутые) ребра. \en If two convex (concave) and one concave (convex) edge are mated at the point, then concave (convex) edges are processed at the first.
  };

public:
  double        distance1;    ///< \ru Радиус кривизны/катет на первой поверхности. \en Radius of curvature/leg on the first surface.
  double        distance2;    ///< \ru Радиус кривизны/катет на второй поверхности. \en Radius of curvature/leg on the second surface.
  double        conic;        ///< \ru Коэффициент формы, изменяется от 0.05 до 0.95 (при 0 - дуга окружности). \en Coefficient of shape is changed from 0.05 to 0.95 (if 0 - circular arc).
  double        begLength;    ///< \ru Расстояние от начала скругления до точки остановки (UNDEFINED_DBL - остановки нет). \en Distance from the beginning of fillet to the stop point (UNDEFINED_DBL  - no stop).
  double        endLength;    ///< \ru Расстояние от конца  скругления до точки остановки (UNDEFINED_DBL - остановки нет). \en Distance from the end of fillet to the stop point (UNDEFINED_DBL  - no stop).
  MbeSmoothForm form;         ///< \ru Тип сопряжения скругление/фаска. \en Mate type of fillet/chamfer.
  CornerForm    smoothCorner; ///< \ru Способ обработки углов стыковки трёх рёбер. \en Method of processing corners of connection by three edges.
  bool          prolong;      ///< \ru Продолжить по касательной. \en Prolong along the tangent.
  ThreeStates   keepCant;     ///< \ru Автоопределение сохранения кромки (ts_neutral), сохранение поверхности (ts_negative), сохранение кромки (ts_positive). \en Auto detection of boundary saving (ts_neutral), surface saving (ts_negative), boundary saving (ts_positive).
  bool          strict;       ///< \ru При false скруглить хотя бы то, что возможно. \en If false - round at least what is possible.
  bool          equable;      ///< \ru В углах сочленения вставлять тороидальную поверхность (для штамповки листового тела). \en In corners of the joint insert toroidal surface (for stamping sheet solid).

private:
  MbVector3D    vector1;      ///< \ru Вектор нормали к плоскости, по которой выполняется усечение скругления в начале цепочки. \en Normal vector of the plane cutting the fillet at the beginning of chain.
  MbVector3D    vector2;      ///< \ru Вектор нормали к плоскости, по которой выполняется усечение скругления в конце цепочки.  \en Normal vector of the plane cutting the fillet at the end of chain.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  SmoothValues()
    : distance1     ( 1.0         )
    , distance2     ( 1.0         )
    , conic         ( c3d::_ARC_  )
    , begLength     (UNDEFINED_DBL)
    , endLength     (UNDEFINED_DBL)
    , form          ( st_Fillet   )
    , smoothCorner  ( ec_uniform  )
    , prolong       ( false       )
    , keepCant      ( ts_negative )
    , strict        ( true        )
    , equable       ( false       )
    , vector1       (             )
    , vector2       (             )
  {}

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по параметрам.
             \en Constructor by parameters. \~
    \param[in] d1, d2 - \ru Радиусы кривизны/катеты.
                        \en Radii of curvature/catheti. \~
    \param[in] f      - \ru Способ построения поверхности сопряжения.
                        \en Method of construction of mating surface. \~
    \param[in] c      - \ru Коэффициент формы, изменяется от 0.05 до 0.95 (при 0 - дуга окружности).
                        \en Coefficient of shape is changed from 0.05 to 0.95 (if 0 - circular arc). \~
    \param[in] pro    - \ru Продолжить по касательной.
                        \en Prolong along the tangent. \~
    \param[in] cor    - \ru Способ скругления "чемоданных" углов.
                        \en Method for bending corner of three surfaces. \~
    \param[in] autoS  - \ru Автоопределение сохранения кромки/поверхности.
                        \en Auto detection of boundary/surface saving. \~
    \param[in] keep   - \ru Сохранять кромку (true) или сохранять поверхность скругления/фаски (false).
                        \en Keep boundary (true) or keep surface of fillet/chamfer (false). \~
    \param[in] str    - \ru Строгое скругление. Если false, скруглить хотя бы то, что возможно.
                        \en Strict fillet. If false - round at least what is possible. \~
    \param[in] equ    - \ru В углах сочленения вставлять тороидальную поверхность.
                        \en In corners of the joint insert toroidal surface. \~
  */
  SmoothValues( double d1, double d2, MbeSmoothForm f, double c, bool pro,
                CornerForm cor, bool autoS, bool keep, bool str, bool equ )
    : distance1     ( d1    )
    , distance2     ( d2    )
    , conic         ( c     )
    , begLength     (UNDEFINED_DBL)
    , endLength     (UNDEFINED_DBL)
    , form          ( f     )
    , smoothCorner  ( cor   )
    , prolong       ( pro   )
    , keepCant      ( ts_negative )
    , strict        ( str   )
    , equable       ( equ   )
    , vector1       (       )
    , vector2       (       )
  {
    keepCant = autoS ? ts_neutral : ts_negative;
    if ( keep )
      keepCant = ts_positive;

  }

  /// \ru Конструктор копирования. \en Copy-constructor.
  SmoothValues( const SmoothValues & other, MbRegDuplicate * iReg = NULL );
  /// \ru Деструктор. \en Destructor.
  virtual ~SmoothValues(){}

  /// \ru Функция инициализации. \en Initialization function.
  void        Init( const SmoothValues & other );
public:
  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * ireg = NULL );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  virtual void    Move     ( const MbVector3D &, MbRegTransform * /*ireg*/ = NULL ){}
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  virtual void    Rotate   ( const MbAxis3D &, double ang, MbRegTransform * ireg = NULL );

  /// \ru Установить плоскость, параллельно которой будет выполнена остановка скругления в начале цепочки. \en Set the plane by which parallel will be carry out stop of the fillet at the begin.
  bool        SetStopObjectAtBeg( const MbSurface * object, bool byObject = true );
  /// \ru Установить плоскость, параллельно которой будет выполнена остановка скругления в конце цепочки.  \en Set the plane by which parallel will be carry out stop of the fillet at the end.
  bool        SetStopObjectAtEnd( const MbSurface * object, bool byObject = true );
  /// \ru Установить вектор нормали к плоскости остановки скругления в начале цепочки. \en Set normal to the bound plane at the begin.
  void        SetBegVector( const MbVector3D & vect ) { vector1.Init( vect ); }
  /// \ru Установить вектор нормали к плоскости остановки скругления в конце цепочки.  \en Set normal to the bound plane at the end.
  void        SetEndVector( const MbVector3D & vect ) { vector2.Init( vect ); }
  /// \ru Получить вектор нормали к плоскости остановки в начале скругления. \en Get normal vector to the bound plane at the begin of the fillet.
  void        GetBegVector( MbVector3D & vect ) const { vect.Init( vector1 ); }
  /// \ru Получить вектор нормали к плоскости остановки в конце скругления. \en Get normal vector to the bound plane at the end of the fillet.
  void        GetEndVector( MbVector3D & vect ) const { vect.Init( vector2 ); }

  /// \ru Оператор присваивания. \en Assignment operator.
  SmoothValues & operator = ( const SmoothValues & other ) {
    Init( other );
    return *this;
  }
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const SmoothValues & other, double accuracy ) const; 

public:
  KNOWN_OBJECTS_RW_REF_OPERATORS( SmoothValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры скругления грани.
           \en Parameters of face fillet. \~
  \details \ru Параметры скругления грани содержат информацию, необходимую для выполнения операции. \n
           \en The parameters of face fillet contain Information necessary to perform the operation. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS FullFilletValues {
public:
  bool        prolong; ///< \ru Продолжить по касательной. \en Prolong along the tangent.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  FullFilletValues()
    : prolong       ( true )
  {}

  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  FullFilletValues( bool prlg )
    : prolong       ( prlg )
  {}

  /// \ru Конструктор копирования. \en Copy-constructor.
  FullFilletValues( const FullFilletValues & other, MbRegDuplicate * iReg = NULL );

  /// \ru Деструктор. \en Destructor.
  ~FullFilletValues(){}
public:
  /// \ru Функция инициализации. \en Initialization function.
  void        Init( const FullFilletValues & other );
  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D &, MbRegTransform * ireg = NULL );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D &, MbRegTransform * /*ireg*/ = NULL ){}
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D &, double ang, MbRegTransform * ireg = NULL );

  /// \ru Оператор присваивания. \en Assignment operator.
  FullFilletValues & operator = ( const FullFilletValues & other ) {
    Init( other );
    return *this;
  }
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const FullFilletValues & other, double accuracy ) const; 

public:
  KNOWN_OBJECTS_RW_REF_OPERATORS( FullFilletValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры скругления вершины.
           \en Parameters of vertex fillet. \~
  \details \ru Параметры скругления вершины, в которой стыкуются три ребра, содержат информацию, необходимую для выполнения операции. \n
           \en Fillet parameters of vertex (where three edges are connected) contain information necessary to perform the operation \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS CornerValues {
public:
  /// \ru Способы скругления вершины стыковки трёх рёбер. \en Methods of vertices fillet of connection by three edges.
  enum CornerForm {
    ef_sphere = 0,  ///< \ru Скругление вершины сферической поверхностью. \en Vertex fillet by spherical surface.
    ef_smart  = 1,  ///< \ru Скругление вершины гладкой поверхностью. \en Vertex fillet by smooth surface.
    ef_delta  = 3,  ///< \ru Скругление вершины треугольной поверхностью. \en Vertex fillet by triangular surface.
    ef_elbow1 = 4,  ///< \ru Скругление вершины четырёхугольной поверхностью, четвёртую сторону располагать напротив range1. \en Vertex fillet by quadrangular surface, the fourth side is opposite the range1.
    ef_elbow2 = 5,  ///< \ru Скругление вершины четырёхугольной поверхностью, четвёртую сторону располагать напротив range2. \en Vertex fillet by quadrangular surface, the fourth side is opposite the range2.
    ef_elbow3 = 6,  ///< \ru Скругление вершины четырёхугольной поверхностью, четвёртую сторону располагать напротив range3. \en Vertex fillet by quadrangular surface, the fourth side is opposite the range3.
  };

public:
  double     radius0;    ///< \ru Радиус сферы в вершине. \en Radius of the sphere of the vertex.
  double     radius1;    ///< \ru Радиус первого  ребра вершины. \en Radius of the first edge of the vertex.
  double     radius2;    ///< \ru Радиус второго  ребра вершины. \en Radius of the second edge of the vertex.
  double     radius3;    ///< \ru Радиус третьего ребра вершины. \en Radius of the third edge of the vertex.
  CornerForm cornerForm; ///< \ru Способ скругления вершины стыковки трёх рёбер. \en Method of vertex fillet of connection by three edges.
  uint8      additive;   ///< \ru Сдвиг в нумерации рёбер вершины (добавка к номеру ребра). \en Shift in the indexation of vertex edges (addition to the index of edge).

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  CornerValues()
    : radius0   ( 0.0 )
    , radius1   ( 1.0 )
    , radius2   ( 1.0 )
    , radius3   ( 1.0 )
    , cornerForm( ef_smart )
    , additive  ( 0 )
  {}
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  CornerValues( double r0, double r1, double r2, double r3, CornerForm ck )
    : radius0   ( ::fabs(r0) )
    , radius1   ( ::fabs(r1) )
    , radius2   ( ::fabs(r2) )
    , radius3   ( ::fabs(r3) )
    , cornerForm( ck )
    , additive  ( 0 )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  CornerValues( const CornerValues & other )
    : radius0   ( other.radius0    )
    , radius1   ( other.radius1    )
    , radius2   ( other.radius2    )
    , radius3   ( other.radius3    )
    , cornerForm( other.cornerForm )
    , additive  ( other.additive   )
  {}
  /// \ru Деструктор. \en Destructor.
  virtual ~CornerValues();

  /// \ru Функция инициализации. \en Initialization function.
  void        Init( const CornerValues & other ) {
    radius0    = other.radius0;
    radius1    = other.radius1;
    radius2    = other.radius2;
    radius3    = other.radius3;
    cornerForm = other.cornerForm;
    additive   = other.additive;
  }
  /// \ru Циклическая перестановка параметров. \en Cyclic permutation of the parameters.
  void        CiclicSwap( bool increase );
  /// \ru Поменять местами радиусы (constRadius = 1,2,3). \en Swap radii (constRadius = 1,2,3).
  void        Swap( int constRadius );
  /// \ru Оператор присваивания. \en Assignment operator.
  CornerValues & operator = ( const CornerValues & other ) {
    Init( other );
    return *this;
  }
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const CornerValues & other, double accuracy ) const; 

  KNOWN_OBJECTS_RW_REF_OPERATORS( CornerValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Типы выемки.
           \en Types of notch. \~
  \details \ru Типы выемки. Служат для определения одного из построений: отверстий, карманов, пазов. \n
           \en Types of notch. These are used to determine one from the constructions: holes, pockets, grooves. \n \~
  \ingroup Build_Parameters
*/
// ---
enum MbeHoleType {
  ht_BorerValues  = 0, ///< \ru Отверстие. \en Hole.
  ht_PocketValues = 1, ///< \ru Карман. \en Pocket.
  ht_SlotValues   = 2, ///< \ru Паз. \en Slot.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры выемки.
           \en The parameters of notch. \~
  \details \ru Общие параметры построения выемки: отверстия, фигурного паза, кармана (бобышки). \n
           \en The common parameters of notch construction: holes, figure slot, pocket (boss). \n \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS HoleValues {
public:
  double      placeAngle;   ///< \ru Угол между осью и нормалью к поверхности (0 <= placeAngle <= M_PI_2). \en Angle between axis and normal to the surface (0 <= placeAngle <= M_PI_2).
  double      azimuthAngle; ///< \ru Угол поворота оси вокруг нормали поверхности (-M_PI2 <= azimuthAngle <= M_PI2). \en Angle of rotation around the surface normal (-M_PI2 <= azimuthAngle <= M_PI2).
protected:
  MbSurface * surface;      ///< \ru Обрабатываемая поверхность (если NULL, то считается плоской). \en Processing surface (if NULL, then is considered planar).
  bool        doPhantom;    ///< \ru Создавать фантом результата операции. \en Create the phantom of the operation.

protected:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров выемки с нулевыми углами и плоской поверхностью.
             \en Constructor of notch parameters with zero angles and planar surfaces. \~
  */
  HoleValues();

  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default.
  HoleValues( const HoleValues & other );
  /// \ru Конструктор копирования. \en Copy-constructor.
  HoleValues( const HoleValues & other, MbRegDuplicate * iReg );

public:
  /// \ru Деструктор. \en Destructor.
  virtual ~HoleValues();

public:
  /// \ru Тип выемки. \en Type of notch.
  virtual MbeHoleType Type() const = 0;
  /// \ru Построить копию объекта. \en Create a copy of the object.
  virtual HoleValues & Duplicate( MbRegDuplicate * ireg = NULL ) const = 0;
  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * ireg = NULL ) = 0;
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  virtual void        Move     ( const MbVector3D &, MbRegTransform * ireg = NULL );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  virtual void        Rotate   ( const MbAxis3D &, double ang, MbRegTransform * ireg = NULL );

  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSame( const HoleValues &, double accuracy ) const;

  /// \ru Оператор присваивания. \en Assignment operator.
  virtual void        operator = ( const HoleValues & other ) = 0;
          /// \ru Функция копирования. \en Copy function.
          void        Init( const HoleValues & init );
          /// \ru Получить поверхность. \en Get the surface.
    const MbSurface * GetSurface() const { return surface; }
          /// \ru Заменить поверхность. \en Replace surface.
          void        SetSurface( MbSurface * s );
          /// \ru Установить флаг создания фантома. \en Set the phantom flag.
          void        SetPhantom( bool s ) { doPhantom = s; }
          /// \ru Получить флаг создания фантома. \en Get the phantom flag.
          bool        GetPhantom() const   { return doPhantom; }
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры отверстия.
           \en The hole parameters. \~
  \details \ru Параметры для построения отверстий различных типов. \n
    Законцовка отверстия управляется параметром spikeAngle.
    При #spikeAngle = 0    - сферическая законцовка отверстия, \n
    при #spikeAngle = M_PI - плоская законцовка отверстия, \n
    в остальных случаях   - коническая законцовка отверстия. \n
           \en The parameters for construction of holes with different types. \n
    Tip of hole is controlled by the spikeAngle parameter.
    If # spikeAngle = 0 - spherical tip of hole, \n
    If # spikeAngle = M - planar tip of hole, \n
    in other cases - conical tip of hole. \n \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS BorerValues : public HoleValues {
public:
  /** \brief \ru Типы отверстий.
             \en Types of holes. \~
    \details \ru Тип определяет форму отверстия.
             \en The type determines the hole shape. \~
    \ingroup Build_Parameters
  */
  enum BorerType {
                             //
                             //    _______________
                             //   /|             |
                             //  +-+-------------+
    bt_SimpleCylinder  = 0,  ///< \ru Простое цилиндрическое отверстие. \en Simple cylindrical hole.
                             //                 __
                             //    _____________||
                             //   /|            ||
                             //  +-+------------++
    bt_TwofoldCylinder = 1,  ///< \ru Двойное цилиндрическое отверстие. \en Double cylindrical hole.
                             //                  /
                             //    _____________/|
                             //   /|            ||
                             //  +-+------------++
    bt_ChamferCylinder = 2,  ///< \ru Цилиндрическое отверстие с фаской. \en Cylindrical hole with a chamfer.
                             //               ____
                             //    __________/|  |
                             //   /|         ||  |
                             //  +-+---------++--+
    bt_ComplexCylinder = 3,  ///< \ru Двойное цилиндрическое отверстие с переходом. \en Double cylindrical hole with a transition.
                             //
                             //    _______________
                             //   /|             |
                             //  +-+-------------+
    bt_SimpleCone      = 4,  ///< \ru Простое коническое отверстие. \en Simple conical hole.
                             //                  |
                             //    ____________ /|
                             //   /|         |   |
                             //  +-+---------+---+
    bt_ArcCylinder     = 5,  ///< \ru Центровое отверстие формы R (дугообразное). \en Center hole of form R (arcuate).
  };

public:
  double         capDiameter; ///< \ru Диаметр головки                          (для отверстий типа #bt_TwofoldCylinder, #bt_ChamferCylinder, #bt_ComplexCylinder). \en Diameter cap (for hole with type #bt_TwofoldCylinder, #bt_ChamferCylinder, #bt_ComplexCylinder).
  double         capDepth;    ///< \ru Глубина под головку                      (для отверстий типа #bt_TwofoldCylinder, #bt_ComplexCylinder). \en Depth for cap (for hole with type #bt_TwofoldCylinder, #bt_ChamferCylinder, #bt_ComplexCylinder).
  double         capAngle;    ///< \ru Угол фаски под головку                   (для отверстий типа #bt_ChamferCylinder, #bt_ComplexCylinder), capAngle <= M_PI. \en Chamfer angle for cap (for holes with type #bt_ChamferCylinder, #bt_ComplexCylinder), capAngle <= M_PI.
  double         diameter;    ///< \ru Диаметр отверстия под резьбу             (для всех типов отверстий). \en Hole diameter for thread (for all the types of holes).
  double         depth;       ///< \ru Глубина отверстия под резьбу             (для всех типов отверстий). \en Hole depth for thread                            (for all the types of holes).
  double         angle;       ///< \ru Угол конусности отверстия под резьбу     (для отверстия типа #bt_SimpleCone), 0 < angle < M_PI. \en Angle of hole conicity for thread                 (for hole with type #bt_SimpleCone), 0 < angle < M_PI.
  double         spikeAngle;  ///< \ru Угол раствора конца отверстия            (для всех типов отверстий), spikeAngle <= M_PI. \en Apex angle of the hole end                    (for all the types of holes), spikeAngle <= M_PI.
  double         arcRadius;   ///< \ru Радиус дуги                              (для отверстия типа #bt_ArcCylinder). \en Arc radius                                   (for hole with type #bt_ArcCylinder).
  bool           prolong;     ///< \ru Флаг продления сверла в обратную сторону (для всех типов отверстий), по умолчанию true (есть продление). \en Flag of drill extension along the opposite direction (for all the types of holes), default true (the extension exists).
  bool           down;        ///< \ru Направление оси отверстия: true - прямое (против оси Z локальной системы), false - обратное. \en Direction of hole axis: true - forward (opposite to the Z of the local system), false - backward.
  BorerType      type;        ///< \ru Тип отверстия. \en Type of hole.

private :
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default.
  BorerValues( const BorerValues & other );
  /// \ru Конструктор копирования. \en Copy-constructor.
  BorerValues( const BorerValues & other, MbRegDuplicate * ireg );
public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор простого цилиндрического отверстия.
             \en Constructor of simple cylindrical hole. \~
  */
  BorerValues()
    : HoleValues ()
    , capDiameter( 20.0 )
    , capDepth   ( 5.0 )
    , capAngle   ( M_PI_2 )
    , diameter   ( 10.0 )
    , depth      ( 25.0 )
    , angle      ( M_PI_2 )
    , spikeAngle ( M_PI * c3d::TWO_THIRD )
    , arcRadius  ( 10. )
    , prolong    ( true )
    , down       ( true )
    , type       ( bt_SimpleCylinder )
  {}

  /// \ru Деструктор. \en Destructor.
  virtual ~BorerValues();

public:
  virtual MbeHoleType Type() const; // \ru Тип выемки. \en Type of notch.
  virtual HoleValues & Duplicate( MbRegDuplicate * ireg = NULL ) const; // \ru Построить копию. \en Create a copy.
  virtual void        Transform( const MbMatrix3D & matr, MbRegTransform * ireg = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix.
  virtual bool        IsSame( const HoleValues &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual void        operator = ( const HoleValues & other ); // \ru Оператор присваивания. \en Assignment operator.
private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default.
          void        operator = ( const BorerValues & other );
public:
  KNOWN_OBJECTS_RW_REF_OPERATORS( BorerValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры кармана или бобышки.
           \en The parameters of pocket or boss. \~
  \details \ru Параметры прямоугольного кармана или бобышки со скруглёнными углами. \n
           \en The parameters of rectangular pocket or boss with rounded corners. \n \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS PocketValues : public HoleValues {
public:
  double        length;       ///< \ru Длина   кармана или бобышки. \en The length of pocket or boss.
  double        width;        ///< \ru Ширина  кармана или бобышки. \en The width of pocket or boss.
  double        depth;        ///< \ru Глубина кармана или бобышки. \en The depth of pocket or boss.

  /** \brief \ru Радиус скругления углов кармана или бобышки.
             \en Fillet radius of corners of pocket or boss. \~
    \details \ru Радиус скругления углов кармана или бобышки, 2 * cornerRadius <= std_min( width, length ).
             При length == width == 2 * cornerRadius получим карман в виде отверстия.
             \en Fillet radius of corners of pocket or boss, 2 * cornerRadius <= std_min( width, length ).
             If length == width == 2 * cornerRadius, then pocket as a hole. \~
  */
  double        cornerRadius;

  double        floorRadius;  ///< \ru Радиус скругления дна кармана или верха бобышки. \en Fillet radius of bottom of pocket or top of boss.
  double        taperAngle;   ///< \ru Угол уклона стенок кармана или верха бобышки (отклонение от вертикали в радианах). \en Draft angle of pocket walls or top of boss (vertical deviation in radians)
  bool          type;         ///< \ru type == false - карман, type == true - бобышка. \en Type == false - pocket, type == true - boss.

private :
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default.
  PocketValues( const PocketValues & other );
  /// \ru Конструктор копирования. \en Copy-constructor.
  PocketValues( const PocketValues & other, MbRegDuplicate * ireg );

public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор кармана.
             \en Constructor of pocket. \~
  */
  PocketValues()
    : HoleValues  ()
    , length      ( 20.0 )
    , width       ( 10.0 )
    , depth       (  5.0 )
    , cornerRadius(  2.0 )
    , floorRadius (  1.0 )
    , taperAngle  (  0.0 )
    , type        ( false )
  {}

  /// \ru Деструктор. \en Destructor.
  virtual ~PocketValues();

public:
  virtual MbeHoleType Type() const; // \ru Тип выемки. \en Type of notch.
  virtual HoleValues & Duplicate( MbRegDuplicate * ireg = NULL ) const; // \ru Построить копию. \en Create a copy.
  virtual void        Transform( const MbMatrix3D & matr, MbRegTransform * ireg = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix.
  virtual bool        IsSame( const HoleValues &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual void        operator = ( const HoleValues & other ); // \ru Оператор присваивания. \en Assignment operator.
private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default.
          void        operator = ( const PocketValues & other );
public:
  KNOWN_OBJECTS_RW_REF_OPERATORS( PocketValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры паза.
           \en The parameters of slot. \~
  \details \ru Параметры фигурного паза. \n
    Вид паза сверху представляет собой разрезанную пополам окружность,
    половинки которой раздвинуты на длину паза, а края соединены отрезками.
           \en The parameters of figure slot. \n
    View of slot from above is cut in half to circle,
    halves of which are spread apart by the length of slot and the edges are connected by segments. \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS SlotValues : public HoleValues {
public:
                             // \ru Вид паза сверху. \en View of slot from above. \~
                             //          --
                             //        /    \
                             //       |      |
                             //       |      |
                             //       |      |
                             //       |      |
                             //        \    /
                             //          --
  enum SlotType {
                             //       ________         *
                             //       |      |         *
                             //       +------+         *
                             //        \    /          *
                             //          --            *
    st_BallEnd     = 0,  ///< \ru Цилиндрический в донной части. \en Cylindrical in the bottom part.
                             //       ________         *
                             //       |      |         *
                             //       |      |         *
                             //       |      |         *
                             //       +------+         *
    st_Rectangular = 1,  ///< \ru Прямоугольный. \en Rectangular.
                             //       ________         *
                             //       |      |         *
                             //    +--+------+--+      *
                             //    |            |      *
                             //    +------------+      *
    st_TShaped     = 2,  ///< \ru T-образный. \en T-shaped.
                             //       ________         *
                             //      /        \        *
                             //     /          \       *
                             //    /            \      *
                             //   +--------------+     *
    st_DoveTail    = 3,  ///< \ru Ласточкин хвост. \en Dovetail
  };

public:
  double        length;      ///< \ru Длина   паза. \en Slot length.
  double        width;       ///< \ru Ширина  паза. \en Slot width.
  double        depth;       ///< \ru Глубина паза. \en Slot depth.
  double        bottomWidth; ///< \ru Ширина донной части T-образного паза, должна превосходить ширину width. \en Width of the bottom part of T-shaped slot must be greater than the width "width".
  double        bottomDepth; ///< \ru Глубина донной части ласточкиного хвоста. \en Depth of the bottom part of dovetail.

  /** \brief \ru Радиус скругления дна паза.
             \en Fillet radius of the slot bottom. \~
    \details \ru Радиус скругления дна паза (2 * floorRadius <= width).
             При width == 2 * floorRadius получим паз типа st_BallEnd.
             floorRadius = 0 для пазов типа st_TShaped и st_DoveTail.
             \en Fillet radius of slot bottom (2 * floorRadius <= width).
             If width == 2 * floorRadius, then slot has type st_BallEnd.
             floorRadius = 0 for slots with type st_TShaped and st_DoveTail. \~
  */
  double        floorRadius;
  double        tailAngle;   ///< \ru Угол уклона стенок паза типа st_DoveTail (отклонение от вертикали в радианах). \en Draft angle of walls of slot with type st_DoveTail (vertical deviation in radians).
  SlotType      type;        ///< \ru Тип паза. \en Type of slot.

private :
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default.
  SlotValues( const SlotValues & other );
  /// \ru Конструктор копирования. \en Copy-constructor.
  SlotValues( const SlotValues & other, MbRegDuplicate * ireg );

public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор прямоугольного паза.
             \en Constructor of rectangular slot. \~
  */
  SlotValues()
    : HoleValues ()
    , length     ( 10.0  )
    , width      ( 10.0  )
    , depth      (  5.0  )
    , bottomWidth( 15.0  )
    , bottomDepth( 10.0  )
    , floorRadius(  1.0  )
    , tailAngle  ( M_PI_4 )
    , type       ( st_Rectangular )
  {}

  /// \ru Деструктор. \en Destructor.
  virtual ~SlotValues();

public:
  virtual MbeHoleType Type() const; // \ru Тип выемки. \en Type of notch.
  virtual HoleValues & Duplicate( MbRegDuplicate * ireg = NULL ) const; // \ru Построить копию. \en Create a copy.
  virtual void        Transform( const MbMatrix3D & matr, MbRegTransform * ireg = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix.
  virtual bool        IsSame( const HoleValues &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual void        operator = ( const HoleValues & other ); // \ru Оператор присваивания. \en Assignment operator.
private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default.
          void        operator = ( const SlotValues & other );
public:
  KNOWN_OBJECTS_RW_REF_OPERATORS( SlotValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief    \ru Параметры крепежа.
              \en The parameters of fastener elements. \~
    \details  \ru Параметры крепежных элементов. \n
              \en The parameters of fastener elements. \n \~
*/
// ---
class MATH_CLASS FastenersValues {
public:
  //------------------------------------------------------------------------------
  /** \brief  \ru Типы крепежа.
  \en Fastener Types. \~
  */
  // ---
  enum MbeFastenerType {
    ft_CountersunkHeadRivet = 0,    ///< \ru Заклепка с (полу)потайной головкой. \en (semi)Countersunk head rivet.  
    ft_UniversalHeadRivet,          ///< \ru Заклепка с универсальной головкой. \en Universal head rivet.
    ft_RoundHeadRivet,              ///< \ru Заклепка с полукруглой головкой. \en Round head rivet.
    ft_FlatHeadRivet                ///< \ru Заклепка с плоской головкой. \en Flat head rivet.
  };
private:
  MbeFastenerType fastenerType; ///< \ru Тип крепежа. \en Fastener type.
  double diameter;              ///< \ru Диаметр крепежа. \en Fastener diameter.
  double angle;                 ///< \ru Угол фаски. \en Countersunk angle.
  double depth;                 ///< \ru Глубина фаски. \en Depth of chamfer.
  double headDiameter;          ///< \ru Диаметр основания головки. \en Diameter of the head base.
  double headHeight;            ///< \ru Высота головки. \en Head height.

  ThreeStates rivetAndHole;     ///< \ru ts_negative - создать только отверстия (без крепежа), ts_neutral - создать только крепёж (без отверстий), ts_positive - создать крепеж и отверстия.
                                ///< \en ts_negative - create holes only (without rivets), ts_neutral - create rivets only (without holes), ts_positive - create rivets and holes. \~

public:
  /** \brief  \ru Конструктор крепежа по типу и диаметру.
              \en Constructor of fastener based on type and diameter. \~
  \details \ru Конструктор крепежа по типу и диаметру.
           \en Constructor of fastener based on type and diameter. \~
  \param[in] ft - \ru Тип крепежа.
                  \en Fastener type. \~
  \param[in] d -  \ru Диаметр крепежа.
                  \en Fastener diameter. \~
  */
  FastenersValues( MbeFastenerType ft, double d ) 
    : fastenerType      ( ft )
    , diameter          ( d  )
    , angle             ( M_PI_4  )
    , depth             ( d * c3d::ONE_HALF )
    , headDiameter      ( 2 * d )
    , headHeight        ( d )
    , rivetAndHole      ( ts_positive )
  {}

  /** \brief  \ru Конструктор крепежа по типу, диаметру, углу, катету.
              \en Constructor of fastener based on type, diameter, angle and side length. \~
  \details \ru Конструктор крепежа по типу, диаметру, углу, катету.
           \en Constructor of fastener based on type, diameter, angle and side length. \~
  \param[in] ft   -   \ru Тип крепежа.
                      \en Fastener type. \~
  \param[in] d    -   \ru Диаметр крепежа.
                      \en Fastener diameter. \~
  \param[in] a    -   \ru Угол.
                      \en Angle. \~
  \param[in] dd   -   \ru Глубина (фаски).
                      \en Depth. \~
  \param[in] hd  -    \ru Диаметр основания головки.
                      \en Head base diameter \~
  \param[in] hh   -   \ru Высота головки.
                      \en Head height. \~
  
  \param[in] ho -  \ru Создать только отверстие.
                   \en Create hole only. \~
  */
  FastenersValues( MbeFastenerType ft, double d, double a, double dd, double hd, double hh, ThreeStates ho ) 
    : fastenerType      ( ft  )
    , diameter          ( d   )
    , angle             ( a   )
    , depth             ( dd  )
    , headDiameter      ( hd )
    , headHeight        ( hh  )
    , rivetAndHole      ( ho )
  {}

  /// \ru Выдать тип крепежа. \en Return type of fastener.
  MbeFastenerType GetType() const { return fastenerType; }
  /// \ru Выдать значение диаметра. \en Return diameter value.
  double GetDiameter() const { return diameter; }
  /// \ru Установить значение диаметра. \en Set diameter value.
  void SetDiameter( double d ) { diameter = d; }
  /// \ru Выдать значение угла. \en Return angle value.
  double GetAngle() const { return angle; }
  /// \ru Установить значение угла. \en Set angle value.
  void SetAngle( double a ) { angle = a; }
  /// \ru Выдать значение глубины фаски. \en Return chamfer depth value.
  double GetDepth() const { return depth; }
  /// \ru Установить значение глубины фаски. \en Set chamfer depth value.
  void SetDepth( double d ) { depth = d; }
  /// \ru Выдать значение диаметра основания головки. \en Return chamfer depth value.
  double GetHeadDiameter() const { return headDiameter; }
  /// \ru Установить значение диаметра основания головки. \en Set chamfer depth value.
  void SetHeadDiameter( double hd ) { headDiameter = hd; }
  /// \ru Выдать значение высоты головки. \en Return head height value.
  double GetHeadHeight() const { return headHeight; }
  /// \ru Установить значение высоты головки. \en Set head height value.
  void SetHeadHeight( double hh ) { headHeight = hh; }

  /// \ru Только отверстие? \en Hole only?
  ThreeStates RivetAndHole() const { return rivetAndHole; }
  /// \ru Функция инициализации. \en Initialization function.
  void   Init( const FastenersValues & other ) {
    fastenerType      = other.fastenerType;
    diameter          = other.diameter;
    angle             = other.angle;
    depth             = other.depth;
    headDiameter      = other.headDiameter;
    headHeight        = other.headHeight;
    rivetAndHole      = other.rivetAndHole;
  }
  /// \ru Оператор присваивания. \en Assignment operator.
  FastenersValues & operator = ( const FastenersValues & other ) {
    Init( other );
    return *this;
  }

private:
  /// \ru Конструктор по умолчанию - запрещен. \en Default constructor - forbidden.
  FastenersValues() 
  {}
public:
  KNOWN_OBJECTS_RW_REF_OPERATORS( FastenersValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры заплатки.
           \en The parameters of patch. \~
  \details \ru Параметры заплатки. \n
    Содержат информацию о типе заплатки и флаге проверки самопересечений.
           \en The parameters of patch. \n
    Contain Information about type of patch and flag of checking self-intersection. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS PatchValues {
public:
  /** \brief \ru Тип заплатки.
             \en Type of patch. \~
    \details \ru Флаг можно установить через вызов PatchValues::SetType(). 
             \en The flag can be set by calling PatchValues::SetType(). \~
  */
  enum SurfaceType {
    ts_tang,         ///< \ru По касательной. \en Along the tangent.
    ts_norm,         ///< \ru По нормали. \en Along the normal.
    ts_none,         ///< \ru Не определено. \en Undefined.
    ts_plane         ///< \ru Плоская заплатка. \en Plane patch.
  };
private:
  SurfaceType type;         ///< \ru Тип заплатки. \en Type of patch.
  bool        checkSelfInt; ///< \ru Флаг проверки самопересечений (вычислительно "тяжелыми" методами). \en Flag for checking of self-intersection (computationally by "heavy" methods).

public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров заплатки не определенного типа без проверки самопересечений.
             \en Constructor of parameters of patch with undefined type and without checking of self-intersection. \~
  */
  PatchValues()
    : type        ( ts_none )
    , checkSelfInt( false   )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  PatchValues( const PatchValues & other )
    : type        ( other.type         )
    , checkSelfInt( other.checkSelfInt )
  {}
  /// \ru Деструктор. \en Destructor.
  ~PatchValues()
  {}

public:
  /// \ru Выдать тип заплатки. \en Get type of patch.
  SurfaceType GetType() const { return type; }
  /// \ru Выдать тип заплатки для изменения. \en Get type of patch for changing.
  SurfaceType & SetType()     { return type; }
  /// \ru Получить флаг проверки самопересечений. \en Get the flag of checking self-intersection.
  bool        CheckSelfInt() const { return checkSelfInt; }
  /// \ru Установить флаг проверки самопересечений. \en Set the flag of checking self-intersection.
  void        SetCheckSelfInt( bool c ) { checkSelfInt = c; }
  /// \ru Оператор присваивания. \en Assignment operator.
  void        operator = ( const PatchValues & other ) { type = other.type; checkSelfInt = other.checkSelfInt; }
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool        IsSame( const PatchValues & obj, double ) const { return ((obj.type == type) && (obj.checkSelfInt == checkSelfInt)); }

  KNOWN_OBJECTS_RW_REF_OPERATORS( PatchValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Кривая для построения заплатки.
           \en Curve for the patch construction. \~
  \details \ru Кривая для построения заплатки и параметры её окружения. \n
           \en Curve for the patch construction and parameters of its environment. \n \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS MbPatchCurve : public MbRefItem {
private:
  MbCurve3D *  curve;        ///< \ru Кривая. \en A curve.
  double       begTolerance; ///< \ru Толерантность привязки в начале. \en Binding tolerance at the start.
  double       endTolerance; ///< \ru Толерантность привязки в начале. \en Binding tolerance at the start.
  bool         isSurfaceOne; ///< \ru В ребре есть грань с первой поверхностью из кривой пересечения. \en There is face with the first surface from the intersection curve in the edge.
  bool         isSurfaceTwo; ///< \ru В ребре есть грань со второй поверхностью из кривой пересечения. \en There is face with the second surface from the intersection curve in the edge.
  mutable bool isUsed;       ///< \ru Флаг использования. \en An using flag.

public:
  /// \ru Конструктор по кривой (копирует кривую, трансформируя по матрице). \en Constructor by a curve (copies a curve, transforms by the matrix).
  MbPatchCurve( const MbCurve3D & crv, const MbMatrix3D & mtr );
  /// \ru Конструктор по ребру (копирует кривую, трансформируя по матрице). \en Constructor by an edge (copies a curve, transforms by the matrix).
  MbPatchCurve( const MbCurveEdge & edge, const MbMatrix3D & mtr );
  /// \ru Деструктор. \en Destructor.
  virtual ~MbPatchCurve();

public:
  /// \ru В ребре есть грань с первой поверхностью из кривой пересечения. \en There is face with the first surface from the intersection curve in the edge.
  bool        IsSurfOne() const { return isSurfaceOne; }
  /// \ru В ребре есть грань со второй поверхностью из кривой пересечения. \en There is face with the second surface from the intersection curve in the edge.
  bool        IsSurfTwo() const { return isSurfaceTwo; }
  /// \ru Толерантность привязки в начале. \en Binding tolerance at the start.
  double      GetBegTolerance() const { return begTolerance; }
  /// \ru Толерантность привязки в начале. \en Binding tolerance at the start.
  double      GetEndTolerance() const { return endTolerance; }
  /// \ru Получить кривую. \en Get a curve.
  const MbCurve3D & GetCurve() const { return *curve; }
  /// \ru Получить кривую для изменения. \en Get a curve for changing.
  MbCurve3D & SetCurve()       { return *curve; }
  /// \ru Кривая используется? \en Is curve used?
  bool        IsUsed() const { return isUsed; }
  /// \ru Установить флаг использования кривой. \en Set flag of using curve.
  void        SetUsed( bool b ) const { isUsed = b; }

  OBVIOUS_PRIVATE_COPY( MbPatchCurve )
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры масштабирования объекта.
           \en The parameters of object scaling. \~
  \details \ru Масштабирование объекта выполняется преобразованием по матрице. \n
           \en Object scaling is performed by the transformation matrix. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS TransformValues {

protected:
  MbMatrix3D    matrix;     ///< \ru Матрица преобразования . \en A transformation matrix.
  // \ru Остальные параметры не обязательны (нужны для расчета matrix по деформации габаритного куба функцией MbCube::CalculateMatrix) \en Other parameters are optional (they are necessary for the calculation of matrix by deformation of bounding box by the function MbCube::CalculateMatrix)
  MbCartPoint3D fixedPoint; ///< \ru Неподвижная точка преобразования (используется, если useFixed = true). \en A fixed point of transformation. (It is used if useFixed = true).
  bool          useFixed;   ///< \ru Использовать неподвижную точку преобразования (если true). \en Use fixed point of transformation (if true).
  bool          isotropy;   ///< \ru Использовать одинаковое масштабирование по осям (если true). \en Use the same axes scaling (if true).

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  TransformValues()
    : matrix()
    , fixedPoint()
    , useFixed( false )
    , isotropy( false )
  {}
  /// \ru Конструктор по матрице. \en Constructor by matrix.
  TransformValues( const MbMatrix3D & m )
    : matrix( m )
    , fixedPoint()
    , useFixed( false )
    , isotropy( false )
  {}
  /// \ru Конструктор по матрице и неподвижной точке преобразования. \en Constructor by matrix and fixed point of transformation.
  TransformValues( const MbMatrix3D & m, const MbCartPoint3D & f, bool fix = false, bool iso = false )
    : matrix( m )
    , fixedPoint( f )
    , useFixed( fix )
    , isotropy( iso )
  {}
  /// \ru Конструктор по неподвижной точке преобразования и масштабам по осям. \en Constructor by fixed point of transformation and axes scale.
  TransformValues( double sX, double sY, double sZ, const MbCartPoint3D & fP );
  /// \ru Конструктор. \en Constructor.
  TransformValues( const TransformValues & other )
    : matrix ( other.matrix )
    , fixedPoint ( other.fixedPoint )
    , useFixed ( other.useFixed )
    , isotropy ( other.isotropy )
  {}
  /// \ru Деструктор. \en Destructor.
  ~TransformValues() {}
public:
  /// \ru Функция инициализации. \en Initialization function.
  void        Init( const TransformValues & other ) {
    matrix = other.matrix;
    fixedPoint = other.fixedPoint;
    useFixed = other.useFixed;
    isotropy = other.isotropy;
  }
  /// \ru Оператор присваивания. \en Assignment operator.
  TransformValues & operator = ( const TransformValues & other ) {
    matrix = other.matrix;
    fixedPoint = other.fixedPoint;
    useFixed = other.useFixed;
    isotropy = other.isotropy;
    return *this;
  }

  /// \ru Выдать матрицу преобразования для использования. \en Get a transformation matrix for use.
  const MbMatrix3D & GetMatrix() const { return matrix; }
  /// \ru Выдать неподвижную точку преобразования для использования. \en A fixed point of transformation for use.
  const MbCartPoint3D & GetFixedPoint() const { return fixedPoint; } 
  /// \ru Использовать неподвижную точку преобразования?. \en Is fixed point use?
  bool        IsFixed() const { return useFixed; } 
  /// \ru Одинаковое масштабирование по осям? \en Is the isotropic scaling?
  bool        Isisotropy() const { return isotropy; }

  /// \ru Выдать матрицу преобразования для редактирования. \en Get a transformation matrix for modify.
  MbMatrix3D & SetMatrix() { return matrix; }
  /// \ru Выдать неподвижную точку преобразования для редактирования. \en A fixed point of transformation for modify.
  MbCartPoint3D & SetFixedPoint() { return fixedPoint; } 
  /// \ru Использовать неподвижную точку преобразования. \en Use fixed point of transformation.
  void        SetFixed( bool b ) { useFixed = b; } 
  /// \ru Использовать одинаковое масштабирование по осям. \en Use the same axes scaling.
  void        SetIsotropy( bool b ) { isotropy = b; }  

  /// \ru Используется ли неподвижная точка преобразования? \en Whether the fixed point of transformation is used?
  bool        IsUsingFixed() const { return useFixed; }
  /// \ru Является ли преобразование изотропным? \en Whether the transformation is isotropic?
  bool        IsIsotropy()   const { return isotropy; }
  /// \ru Рассчитать неподвижную точку преобразования. \en Calculate a fixed point of transformation.
  bool        CalculateFixedPoint();
  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D & matr );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D & to );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D & axis, double ang );
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const TransformValues & other, double accuracy ) const; 

  KNOWN_OBJECTS_RW_REF_OPERATORS( TransformValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Типы модификации.
            \en Type of modification. \~
  \details \ru Тип определяет действия при прямом моделировании.
            \en Type determines direct modeling actions. \~
  \ingroup Build_Parameters
*/
enum MbeModifyingType {
  dmt_Remove = 0, ///< \ru Удаление из тела выбранных граней с окружением. \en Removal of the specified faces with the neighborhood from a solid.
  dmt_Create,     ///< \ru Создание тела из выбранных граней с окружением. \en Creation of a solid from the specified faces with the neighborhood.
  dmt_Action,     ///< \ru Перемещение выбранных граней с окружением относительно оставшихся граней тела. \en Translation of the specified faces with neighborhood relative to the other faces of the solid.
  dmt_Offset,     ///< \ru Замена выбранных граней тела эквидистантными гранями (перемещение по нормали, изменение радиуса). \en Replacement of the specified faces of a solid with the offset faces (translation along the normal, change of the radius).
  dmt_Fillet,     ///< \ru Изменение радиусов выбранных граней скругления. \en Change of radii of the specified fillet faces.
  dmt_Supple,     ///< \ru Замена выбранных граней тела деформируемыми гранями (превращение в NURBS для редактирования). \en Replacement of the specified faces of a solid with a deformable faces (conversion to NURBS for editing).
  dmt_Purify,     ///< \ru Удаление из тела выбранных скруглений. \en Removal of the specified fillets from a solid.
  dmt_Merger,     ///< \ru Слияние вершин ребёр и удаление рёбер. \en Merging vertices of edges and edges removal.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры прямого редактирования тела.
           \en Parameter for direct editing of solid. \~
  \details \ru Параметры прямого редактирования тела. \n
    Параметры содержат информацию о типе модификации и векторе перемещения.
           \en Parameter for direct editing of solid. \n
    The parameters contain Information about modification type and movement vector. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS ModifyValues {

public:
  MbeModifyingType way;       ///< \ru Тип модификации. \en Type of modification.
  MbVector3D       direction; ///< \ru Перемещение при модификации. \en Moving when modifying.

public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров операции удаления из тела выбранных граней.
             \en Constructor of operation parameters of removing the specified faces from the solid. \~
  */
  ModifyValues()
    : way( dmt_Remove )
    , direction( 0.0, 0.0, 0.0 )
  {}
  /// \ru Конструктор по способу модификации и вектору перемещения. \en Constructor by way of modification and movement vector.
  ModifyValues( MbeModifyingType w, const MbVector3D & p )
    : way      ( w )
    , direction( p )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  ModifyValues( const ModifyValues & other )
    : way      ( other.way )
    , direction( other.direction )
  {}
  /// \ru Деструктор. \en Destructor.
  ~ModifyValues() {}
public:
  /// \ru Функция копирования. \en Copy function.
  void        Init( const ModifyValues & other ) {
    way       = other.way;
    direction = other.direction;
  }
  /// \ru Оператор присваивания. \en Assignment operator.
  ModifyValues & operator = ( const ModifyValues & other ) {
    way       = other.way;
    direction = other.direction;
    return *this;
  }
  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D & matr );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D & to );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D & axis, double ang );
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const ModifyValues & other, double accuracy ) const; 

  KNOWN_OBJECTS_RW_REF_OPERATORS( ModifyValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры деформируемой грани.
           \en Parameters of the deformable face. \~
  \details \ru Параметры деформируемой грани используются при замене поверхности выбранной грани тела
    NURBS-поверхностью и при дальнейшем редактировании этой грани. \n
           \en Parameters of the deformable face are used when replacing the surface of selected face of solid
    by NURBS-surface and with further editing of this face. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS NurbsValues {
public:
  MbNurbsParameters uParameters; ///< \ru Параметры u-направления NURBS-поверхности. \en Parameters of u-direction of NURBS-surface.
  MbNurbsParameters vParameters; ///< \ru Параметры v-направления NURBS-поверхности. \en Parameters of v-direction of NURBS-surface.

public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров деформированной грани для замены
      поверхности NURBS-поверхностью 4 порядка по всей области определения по направлениям u и v.
             \en Constructor of parameters of deformed face for replacement
      of surface by NURBS-surface of the fourth order in the entire domain along the u and v directions. \~
  */
  NurbsValues()
    : uParameters()
    , vParameters()
  {}

  /** \brief \ru Конструктор по параметрам.
             \en Constructor by parameters. \~
    \details \ru Конструктор параметров деформированной грани.
             \en Constructor of parameters of deformed face. \~
    \param[in] ud,         vd         - \ru Порядок NURBS-копии по u и по v.
                                        \en Order of NURBS-copy along u and v. \~
    \param[in] uc,         vc         - \ru Количество контрольных точек по u и по v.
                                        \en The count of control points along u and v. \~
    \param[in] umin, umax, vmin, vmax - \ru Диапазоны параметров по u и v для деформирования грани.
                                        \en Parameter ranges along u and v for deforming face. \~
    \param[in] uapprox,    vapprox    - \ru Флаги возможного построения приближенной поверхности, а не точной.
                                        \en Flags of the possible constructing of approximate surface, not exact. \~
  */
  NurbsValues( size_t ud, size_t uc, double umin, double umax, bool uapprox,
               size_t vd, size_t vc, double vmin, double vmax, bool vapprox )
    : uParameters( ud, uc, umin, umax, uapprox )
    , vParameters( vd, vc, vmin, vmax, vapprox )
  {}

  /// \ru Конструктор копирования. \en Copy-constructor.
  NurbsValues( const NurbsValues & other )
    : uParameters( other.uParameters )
    , vParameters( other.vParameters )
  {}
  /// \ru Деструктор. \en Destructor.
  ~NurbsValues() {}

public:
  /// \ru Функция копирования. \en Copy function.
  void        Init( const NurbsValues & other ) {
    uParameters = other.uParameters;
    vParameters = other.vParameters;
  }
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const NurbsValues & other, double accuracy ) const; 
  /// \ru Оператор присваивания. \en Assignment operator.
  NurbsValues & operator = ( const NurbsValues & other ) {
    uParameters = other.uParameters;
    vParameters = other.vParameters;
    return *this;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( NurbsValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//--------------------------------------------------------------------
/** \brief \ru Параметры для построения NURBS-блока.
           \en The parameters for construction of NURBS-block. \~
  \details \ru Параметры для построения блока из NURBS-поверхностей. \n
           \en The parameters for construction of block.from NURBS-surfaces. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS NurbsBlockValues {
public:
  // \ru Параметры для построения блока из nurbs-поверхностей. \en The parameters for construction of block.from nurbs-surfaces.
  //
  // \ru +Z   (N) - номер грани   *-----* \en +Z   (N) - index of face   *-----*
  //         |                       |     |
  //         *--------*              | (5) |
  //        /|       /|              |     |
  //       / |      / |        *-----*-----*-----*-----*
  //      /  |     /  |        |     |     |     |     |
  //     *---+----*   |        | (2) | (3) | (4) | (1) |
  //     |   |    |   |        |     |     |     |     |
  //     |   *----+---*-- +Y   *-----*-----*-----*-----*
  //     |  /     |  /               |     |
  //     | /      | /                | (0) |
  //     |/       |/                 |     |
  //     *--------*                  *-----*
  //    /
  // \ru +X  Развертка граней блока внешней стороной к наблюдателю. \en +X  Unfolding the outer side of block faces to the viewer.
  //
  // \ru Принцип соответствия номеров и граней. \en Principle of correspondence of indices and faces.
  // \ru Элементы матрицы структуры соответствуют параметрам поверхностей следующих граней блока: \en Matrix elements of the structure correspond to surfaces parameters the following blocks:
  // \ru - элемент 0 - грани 0, 5 ( нижняя и верхняя грани ); \en - element 0 - faces 0, 5 ( lower and upper faces );
  // \ru - элемент 1 - грани 1, 3 ( боковые грани ); \en - element 1 - faces 1, 3 ( lateral faces );
  // \ru - элемент 2 - грани 2, 4 ( боковые грани ). \en - element 2 - faces 2, 4 ( lateral faces ).

  ptrdiff_t udeg[3]; ///< \ru Порядок nurbs-сплайнов по первому параметру для трех пар поверхностей граней блока. \en Order of nurbs-splines along the first parameter for three pairs of block faces.
  ptrdiff_t vdeg[3]; ///< \ru Порядок nurbs-сплайнов по второму параметру для трех пар поверхностей граней блока. \en Order of nurbs-splines along the second parameter for three pairs of block faces.
  ptrdiff_t ucnt[3]; ///< \ru Количество контрольных точек вдоль первого параметра для трех пар поверхностей граней блока. \en The count of matrix elements of control points along the first and for three pairs of block faces.
  ptrdiff_t vcnt[3]; ///< \ru Количество контрольных точек вдоль второго параметра для трех пар поверхностей граней блока. \en The count of matrix elements of control points along the second and for three pairs of block faces.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры сплайновой поверхности.
           \en The parameters of spline surface. \~
  \details \ru Параметры определяют контрольные точки, веса, узлы сплайновой поверхности. \n
           \en The parameters determines control points, weights, knots of spline surface. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS NurbsSurfaceValues {
  friend class MbNurbsSurfacesSolid;
private:
  ptrdiff_t                udegree;        ///< \ru Порядок В-сплайна по U. \en Spline degree along U.
  ptrdiff_t                vdegree;        ///< \ru Порядок В-сплайна по V. \en Spline degree along V.
  bool                     uclosed;        ///< \ru Признак замкнутости по U. \en Attribute of closedness along U.
  bool                     vclosed;        ///< \ru Признак замкнутости по V. \en Attribute of closedness along V.
  Array2<MbCartPoint3D>    points;         ///< \ru Множество точек. \en Set of points.
  double                   weight;         ///< \ru Вес точек в случае одинаковости весов. \en Points weight in the case of equal weights.
  Array2<double> *         weights;        ///< \ru Веса точек (может быть NULL). \en Weights of points (can be NULL).
  bool                     throughPoints;  ///< \ru Строить поверхность, проходящую через точки. \en Build surface passing through points.
  bool                     pointsCloud;    ///< \ru Облако точек (массив не упорядочен). \en Point cloud (disordered array).
  MbPlane *                cloudPlane;     ///< \ru Опорная плоскость облака точек. \en Support plane of point cloud.
  bool                     ownCloudPlane;  ///< \ru Собственная опорная плоскость облака точек. \en Own support plane of point cloud.
  bool                     checkSelfInt;   ///< \ru Искать самопересечения. \en Find self-intersection.
  mutable CSSArray<size_t> checkLnNumbers; ///< \ru Номера проверяемых строк. \en The indices of checked rows.
  mutable CSSArray<size_t> checkCnNumbers; ///< \ru Номера проверяемых столбцов. \en The indices of checked columns.
  mutable ptrdiff_t        minCloudDegree; ///< \ru Минимально  возможный порядок сплайнов по облаку точек. \en The smallest possible order of splines by point cloud.
  mutable ptrdiff_t        maxCloudDegree; ///< \ru Максимально возможный порядок сплайнов по облаку точек. \en The maximum possible order of splines by point cloud.

public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров не замкнутой сплайновой поверхности
      второго порядка по направлениям u и v.
             \en Constructor of parameters of non-closed spline surface
      of second order along the u and v directions. \~
  */
  NurbsSurfaceValues();

  /// \ru Конструктор копирования. \en Copy-constructor.
  NurbsSurfaceValues( const NurbsSurfaceValues & );
  /// \ru Деструктор. \en Destructor.
  ~NurbsSurfaceValues();

public:
  /** \brief \ru Инициализация по сетке точек.
             \en Initialization by grid of points. \~
    \details \ru Инициализация параметров сплайновой поверхности по сетке точек.
             \en Initialization of parameters of spline surface by grid of points. \~
    \param[in] uDeg, vDeg   - \ru Порядок по u и по v.
                              \en Order along u and v. \~
    \param[in] uCls, vCls   - \ru Признаки замкнутости поверхности по u и по v.
                              \en Attribute of surface closedness along u and v. \~
    \param[in] pnts         - \ru Набор точек.
                              \en A point set. \~
    \param[in] checkSelfInt - \ru Признак проверки на самопересечение.
                              \en Attribute of check for self-intersection. \~
    \return \ru false при некорректных параметрах.
            \en False if incorrect parameters. \~
  */
  bool        InitMesh( ptrdiff_t uDeg, bool uCls,
                        ptrdiff_t vDeg, bool vCls,
                        const Array2<MbCartPoint3D> & pnts,
                        bool checkSelfInt );

  /** \brief \ru Инициализация по сетке точек.
             \en Initialization by grid of points. \~
    \details \ru Инициализация параметров сплайновой поверхности по сетке точек.
             \en Initialization of parameters of spline surface by grid of points. \~
    \param[in] uDeg, vDeg   - \ru Порядок по u и по v.
                              \en Order along u and v. \~
    \param[in] uCls, vCls   - \ru Признаки замкнутости поверхности по u и по v.
                              \en Attribute of surface closedness along u and v. \~
    \param[in] pnts         - \ru Набор точек.
                              \en A point set. \~
    \param[in] wts          - \ru Веса точек.
                              \en Weights of points. \~
    \param[in] checkSelfInt - \ru Признак проверки на самопересечение.
                              \en Attribute of check for self-intersection. \~
    \return \ru false при некорректных параметрах.
            \en False if incorrect parameters. \~
  */
  bool        InitMesh( ptrdiff_t uDeg, bool uCls,
                        ptrdiff_t vDeg, bool vCls,
                        const Array2<MbCartPoint3D> & pnts,
                        const Array2<double> * wts, bool checkSelfInt );

  /** \brief \ru Инициализация по облаку точек.
             \en Initialization by point cloud. \~
    \details \ru Инициализация по облаку точек (используется оригинал плоскости).\n
      Если uvDeg < 0, то будет создаваться набор треугольных пластин \n
      (триангуляцией проекций точек на cloudPlace)
             \en Initialization by point cloud (used the original plane).\n
      If uvDeg < 0, then set of triangular plates is created \n
      (by triangulation of points projections on the cloudPlace) \~
    \param[in] uvDeg        - \ru Порядок по u и по v.
                              \en Order along u and v. \~
    \param[in] pnts         - \ru Множество точек.\n
                              Набор точек подходит для инициализации (является облаком точек)
                              в случае, если это одномерный массив точек,
                              не лежащих на одной прямой, без совпадений.
                              \en Set of points.\n
                              Set of points is suitable for initialization (is a point cloud)
                              if it is one-dimensional array of points
                              which don't lie on a straight line without coincidence. \~
    \param[in] cloudPlace   - \ru Опорная плоскость облака точек.
                              \en Support plane of point cloud. \~
    \param[in] checkSelfInt - \ru Признак проверки на самопересечение.
                              \en Attribute of check for self-intersection. \~
    \return \ru true при корректных параметрах.
            \en True if correct parameters. \~
  */
  bool        InitCloud(       ptrdiff_t               uvDeg,
                         const Array2<MbCartPoint3D> & pnts,
                         const MbPlacement3D *         cloudPlace,
                               bool                    checkSelfInt );

  /// \ru Оператор копирования. \en Copy-operator.
  void        operator = ( const NurbsSurfaceValues & );

public:
  /// \ru Первичная проверка корректности параметров. \en Initial check of parameters correctness
  bool        IsValid( bool checkPoints ) const;

  /// \ru Получить порядок сплайнов по U. \en Get splines degree along U.
  ptrdiff_t   GetUDegree() const { return udegree; }
  /// \ru Получить порядок сплайнов по V. \en Get splines degree along V.
  ptrdiff_t   GetVDegree() const { return vdegree; }
  /// \ru Замкнутость по U. \en Closedness along U.
  bool        GetUClosed() const { return uclosed; }
  /// \ru Замкнутость по V. \en Closedness along V.
  bool        GetVClosed() const { return vclosed; }
  /// \ru Количество точек по U. \en A count of points along U.
  size_t      GetUCount() const { return points.Columns(); }
  /// \ru Количество точек по V. \en A count of points along V.
  size_t      GetVCount() const { return points.Lines();   }

  /// \ru Установить порядок сплайна по u. \en Set spline degree along u.
  bool        SetUDegree( size_t uDeg );
  /// \ru Установить порядок сплайна по v. \en Set spline degree along v.
  bool        SetVDegree( size_t vDeg );
  /// \ru Установить замкнутость по U. \en Set closedness along U.
  void        SetUClosed( bool uCls ) { uclosed = uCls; }
  /// \ru Установить замкнутость по V. \en Set closedness along V.
  void        SetVClosed( bool vCls ) { vclosed = vCls; }

  /// \ru Получить точку по позиции. \en Get point by position.
  bool        GetUVPoint ( size_t ui, size_t vi, MbCartPoint3D & ) const;
  /// \ru Получить вес по позиции. \en Get weight by position.
  bool        GetUVWeight( size_t ui, size_t vi, double        & ) const;
  /// \ru Получить общий вес (вернет true, если вес у всех точек одинаковый). \en Get total weight (return true if all the weights are the same).
  bool        GetCommonWeight( double & ) const;
  /// \ru Установить точки по позиции. \en Set points by position.
  bool        SetUVPoint ( size_t ui, size_t vi, const MbCartPoint3D & );
  /// \ru Установить вес по позиции. \en Set weight by position.
  bool        SetUVWeight( size_t ui, size_t vi, const double        & );
  /// \ru Установить общий вес. \en Set total weight.
  bool        SetCommonWeight( double );

  /// \ru Преобразовать данные согласно матрице. \en Transform data according to the matrix.
  void        Transform( const MbMatrix3D &, MbRegTransform * ireg );
  /// \ru Сдвинуть данные вдоль вектора. \en Move data along a vector.
  void        Move     ( const MbVector3D &, MbRegTransform * ireg );
  /// \ru Повернуть данные вокруг оси на заданный угол. \en Rotate data at a given angle around an axis.
  void        Rotate   ( const MbAxis3D   &, double angle, MbRegTransform * ireg );

  bool        IsSame( const NurbsSurfaceValues &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?

  /// \ru Установить размерность массивов точек и весов без сохранения или с сохранением имеющихся данных. \en Set the size of arrays of points and weights without saving or with saving of existing data.
  bool        SetSize( size_t ucnt, size_t vcnt, bool keepData = false );
  /// \ru Установить флаг прохождения поверхности через точки. \en Set flag of surface passing through the points.
  void        SetThroughPoints( bool tp );
  /// \ru Будет ли поверхность проходить через точки? \en Whether the surface passes through the points?
  bool        IsThroughPoints() const { return throughPoints; }
  /// \ru Является ли массив облаком точек? \en Whether the array is point cloud?
  bool        IsPointsCloud() const   { return pointsCloud; }
  /// \ru Используется ли собственная плоскость проецирования (в случае массива по облаку точек)? \en Whether the own plane of projection is used (in the case of array by point cloud)?
  bool        IsOwnCloudPlane() const { return ownCloudPlane; }
  /// \ru Нужно ли проверять самопересечения? \en Whether it is necessary to check self-intersections?
  bool        CheckSelfInt() const { return checkSelfInt; }
  /// \ru Получить массив номеров проверяемых строк. \en Get the array of indices of checked rows.
  void        GetCheckLines( CSSArray<size_t> & checkNumbers ) const { checkNumbers = checkLnNumbers; }
  /// \ru Получить массив номеров проверяемых столбцов. \en Get the array of indices of checked columns.
  void        GetCheckCols ( CSSArray<size_t> & checkNumbers ) const { checkNumbers = checkCnNumbers; }
  /// \ru Получить количество строк. \en Get the count of rows.
  size_t      GetPointsLines  () const { return points.Lines();   } //-V524
  /// \ru Получить количество столбцов. \en Get the count of columns.
  size_t      GetPointsColumns() const { return points.Columns(); } //-V524
  /// \ru Получить массив точек. \en Get array of points.
  bool        GetPoints ( Array2<MbCartPoint3D> & pnts ) const { return pnts.Init( points ); }
  /// \ru Если ли веса? \en Is there weights?
  bool        IsWeighted() const { return (weights != NULL); }
  /// \ru Получить массив весов. \en Get array of weights.
  bool        GetWeights( Array2<double> & wts ) const;
  /// \ru Получить плоскость проецирования. \en Get the plane of projection.
  const MbPlane * GetCloudPlane() const { return (pointsCloud ? cloudPlane : NULL);}

  /** \brief \ru Минимально возможный порядок сплайнов в случае облака точек.
             \en The smallest possible order of splines in the case of point cloud. \~
    \details \ru Минимально возможный порядок сплайнов в случае облака точек.\n
      Запрашивать после успешного создания поверхности, иначе вернет отрицательное значение.
             \en The smallest possible order of splines in the case of point cloud.\n
      Request after the successful creation of the surface otherwise returns a negative value. \~
  */
  ptrdiff_t   GetMinCloudDegree() const { return minCloudDegree; }

  /** \brief \ru Максимально возможный порядок сплайнов в случае облака точек.
             \en The maximum possible order of splines in the case of point cloud. \~
    \details \ru Максимально возможный порядок сплайнов в случае облака точек.\n
      Запрашивать после успешного создания поверхности, иначе вернет отрицательное значение.
             \en The maximum possible order of splines in the case of point cloud.\n
      Request after the successful creation of the surface otherwise returns a negative value. \~
  */
  ptrdiff_t   GetMaxCloudDegree() const { return maxCloudDegree; }

  /// \ru Выставить максимально возможный порядок по обработанному (регуляризованному) облаку точек. \en Set the maximum possible order by processed (regularized) point cloud.
  bool        SetCloudDegreeRange( const NurbsSurfaceValues & meshParam ) const;

private:
  void        DeleteWeights();
  bool        CreateWeights( double wt );
  void        SetCloudPlane( MbPlane * );
  bool        CreateOwnCloudPlane();
public:
  KNOWN_OBJECTS_RW_REF_OPERATORS_EX( NurbsSurfaceValues, MATH_FUNC_EX )
};


//------------------------------------------------------------------------------
// \ru Получить веса \en Get weights
// ---
inline bool NurbsSurfaceValues::GetWeights( Array2<double> & wts ) const
{
  if ( weights != NULL ) {
    if ( wts.Init( *weights ) )
      return true;
  }
  return false;
}


//------------------------------------------------------------------------------
// \ru Установить порядок сплайна по u \en Set spline degree along u
// ---
inline bool NurbsSurfaceValues::SetUDegree( size_t uDeg )
{
  if ( uDeg > 1 ) {
    udegree = uDeg;
    return true;
  }
  return false;
}


//------------------------------------------------------------------------------
// \ru Установить порядок сплайна по v \en Set spline degree along v
// ---
inline bool NurbsSurfaceValues::SetVDegree( size_t vDeg )
{
  if ( vDeg > 1 ) {
    vdegree = vDeg;
    return true;
  }
  return false;
}


//------------------------------------------------------------------------------
// \ru Получить точку \en Get a point
// ---
inline bool NurbsSurfaceValues::GetUVPoint( size_t ui, size_t vi, MbCartPoint3D & pnt ) const
{
  if ( ui < GetUCount() && vi < GetVCount() ) {
    pnt = points( vi, ui );
    return true;
  }
  return false;
}


//------------------------------------------------------------------------------
// \ru Установить точку \en Set a point
// ---
inline bool NurbsSurfaceValues::SetUVPoint( size_t ui, size_t vi, const MbCartPoint3D & pnt )
{
  bool bRes = false;

  if ( ui < GetUCount() && vi < GetVCount() ) {
    MbCartPoint3D bakPoint( points( vi, ui ) );
    points( vi, ui ) = pnt;

    if ( pointsCloud && ownCloudPlane ) {
      if ( CreateOwnCloudPlane() )
        bRes = true;
      else
        points( vi, ui ) = bakPoint;
    }
  }
  return bRes;
}


//------------------------------------------------------------------------------
// \ru Получить вес \en Get a weight
// ---
inline bool NurbsSurfaceValues::GetUVWeight( size_t ui, size_t vi, double & wt ) const
{
  if ( weights != NULL && ui < GetUCount() && vi < GetVCount() ) {
    wt = (*weights)( vi, ui );
    return (wt != UNDEFINED_DBL); //-V550
  }
  wt = weight;
  return (wt != UNDEFINED_DBL); //-V550
}


//------------------------------------------------------------------------------
// \ru Получить общий вес, вернет true, если вес у вес одинаковый \en Get total weight, return true if all the weights are the same
// ---
inline bool NurbsSurfaceValues::GetCommonWeight( double & wt ) const
{
  if ( weights == NULL && weight != UNDEFINED_DBL ) { //-V550
    wt = weight;
    return true;
  }
  return false;
}


//------------------------------------------------------------------------------
// \ru Установить флаг прохождения поверхности через точки \en Set flag of surface passing through the points
// ---
inline void NurbsSurfaceValues::SetThroughPoints( bool tp )
{
  throughPoints = tp;

  if ( throughPoints ) {
    DeleteWeights();
    weight = 1.0;
  }
  if ( weights == NULL && weight == UNDEFINED_DBL ) //-V550
    weight = 1.0;
}


//-----------------------------------------------------------------------------
/** \brief \ru Параметры поверхности по сетке кривых.
           \en Surface parameter by grid of curves. \~
  \details \ru Параметры содержат необходимые данные для построения поверхности по сетке кривых. \n
           \en The parameters contain the necessary data to construct a surface by grid of curves. \n \~
  \ingroup Build_Parameters
*/
//---
struct MATH_CLASS MeshSurfaceValues {
  friend class MbMeshShell;

private:
  RPArray<MbCurve3D> curvesU;     ///< \ru Набор кривых по первому направлению. \en Set of curves along the first direction.
  RPArray<MbCurve3D> curvesV;     ///< \ru Набор кривых по второму направлению. \en Set of curves along the second direction.
  RPArray<MbPolyline3D> chainsU; ///< \ru Набор цепочек по первому направлению. \en Set of chains along the first direction. 
  RPArray<MbPolyline3D> chainsV; ///< \ru Набор цепочек по второму направлению. \en Set of chains along the second direction. 
  bool               uClosed;     ///< \ru Замкнутость по U направлению. \en Closedness along U direction.
  bool               vClosed;     ///< \ru Замкнутость по V направлению. \en Closedness along V direction.
  bool               checkSelfInt;///< \ru Искать самопересечения. \en Find self-intersections.
  // \ru Сопряжения на границе (если сопряжения заданы, то кривые должны быть SurfaceCurve или контур из SurfaceCurve). \en Mates on the boundary (if mates are given, then curves must be SurfaceCurve or contour from SurfaceCurve).
  MbeMatingType      type0;       ///< \ru Сопряжение на границе 0. \en Mate on the boundary 0.
  MbeMatingType      type1;       ///< \ru Сопряжение на границе 1. \en Mate on the boundary 1.
  MbeMatingType      type2;       ///< \ru Сопряжение на границе 2. \en Mate on the boundary 2.
  MbeMatingType      type3;       ///< \ru Сопряжение на границе 3. \en Mate on the boundary 3.
   
  MbSurface *        surface0;    ///< \ru Сопрягаемая поверхность через границу 0 (curvesU[0]). \en Mating surface through the boundary 0 (curvesU[0]).
  MbSurface *        surface1;    ///< \ru Сопрягаемая поверхность через границу 1 (curvesV[0]). \en Mating surface through the boundary 1 (curvesV[0]).
  MbSurface *        surface2;    ///< \ru Сопрягаемая поверхность через границу 2 (curvesU[maxU]). \en Mating surface through the boundary 2 (curvesU[maxU]).
  MbSurface *        surface3;    ///< \ru Сопрягаемая поверхность через границу 3 (curvesV[maxV]). \en Mating surface through the boundary 3 (curvesV[maxV]).
  MbPoint3D *        point;       ///< \ru Точка на поверхности. Используется для уточнения. \en Point on the surface. Used for specializing.

  bool               defaultDir0; ///< \ru Направление сопряжения на границе 0 по умолчанию. \en Default mate direction through the boundary 0.
  bool               defaultDir1; ///< \ru Направление сопряжения на границе 1 по умолчанию. \en Default mate direction through the boundary 1.
  bool               defaultDir2; ///< \ru Направление сопряжения на границе 2 по умолчанию. \en Default mate direction through the boundary 2.
  bool               defaultDir3; ///< \ru Направление сопряжения на границе 3 по умолчанию. \en Default mate direction through the boundary 3.
  mutable uint8      directOrderV;///< \ru По второму семейству кривых порядок кривых совпадает. \en Order of the curves coincides by the second set of curves.
private:
  /// \ru Конструктор копирования. \en Copy-constructor.
  MeshSurfaceValues( const MeshSurfaceValues &, MbRegDuplicate * ireg );
public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MeshSurfaceValues();
  /// \ru Деструктор. \en Destructor.
  ~MeshSurfaceValues();

public:
  /** \brief \ru Функция инициализации.
             \en Initialization function. \~
    \details \ru Функция инициализации на оригиналах кривых и копиях поверхностей.
             \en Initialization function on the original curves and copies of surfaces. \~
    \param[in] curvesU, curvesV - \ru Наборы кривых по первому и второму направлению.
                                  \en Sets of curves along the first and second directions. \~
    \param[in] chainsU, chainsV - \ru Наборы цепочек по первому и второму направлению.
                                  \en Sets of chains along the first and second directions. \~
    \param[in] uClosed, vClosed - \ru Признак замкнутости по направлениям u и v.
                                  \en Closedness attribute along the u and v directions. \~
    \param[in] checkSelfInt - \ru Флаг проверки на самопересечение.
                              \en Flag of check for self-intersection. \~
    \param[in] type0, type1, type2, type3 - \ru Типы сопряжений на границах.
                                            \en Mates types on the boundaries. \~
    \param[in] surfaces0, surfaces1, surfaces2, surfaces3 - \ru Соответствующие сопрягаемые поверхности.
                                                            \en Corresponding mating surfaces. \~
    \param[in] modify - \ru Флаг модификации кривых по сопряжениям.
                        \en Flag of curves modification by mates. \~
  */
  bool        Init( const RPArray<MbCurve3D> & curvesU, bool uClosed,
                    const RPArray<MbCurve3D> & curvesV, bool vClosed,
                    bool checkSelfInt,
                    const RPArray<MbPolyline3D> * chainsU = NULL,
                    const RPArray<MbPolyline3D> * chainsV = NULL,
                    MbeMatingType type0 = trt_Position, MbeMatingType type1 = trt_Position,
                    MbeMatingType type2 = trt_Position, MbeMatingType type3 = trt_Position,
                    const MbSurface * surf_0 = NULL, // \ru Сопрягаемые поверхности через curvesU[0] \en Mating surfaces through curvesU[0]
                    const MbSurface * surf_1 = NULL, // \ru Сопрягаемые поверхности через curvesV[0] \en Mating surfaces through curvesV[0]
                    const MbSurface * surf_2 = NULL, // \ru Сопрягаемые поверхности через curvesU[maxU] \en Mating surfaces through curvesU[maxU]
                    const MbSurface * surf_3 = NULL, // \ru Сопрягаемые поверхности через curvesV[maxV] \en Mating surfaces through curvesV[maxV]
                    const MbPoint3D * pnt = NULL,
                    bool modify = true,
                    bool direct0 = true, bool direct1 = true, bool direct2 = true, bool direct3 = true );

  /** \brief \ru Функция инициализации.
             \en Initialization function. \~
    \details \ru Функция инициализации на оригиналах или копиях кривых и поверхностей.
             \en Initialization function on the originals or copies of curves and surfaces. \~
    \param[in] pars - \ru Исходные параметры.
                      \en Initial parameters. \~
    \param[in] sameItems - \ru Флаг использования оригиналов кривых и поверхностей.
                           \en Flag of using originals of curves and surfaces. \~
  */
  void        Init( const MeshSurfaceValues & pars, bool sameItems );

  /** \brief \ru Лежит ли кривая на поверхности.
             \en Determine whether the curve lies on the surface. \~
    \details \ru Лежит ли кривая полностью на поверхности.
             \en Determine whether the curve entirely lies on the surface. \~
    \param[in] curve - \ru Проверяемая кривая.
                       \en Checking curve. \~
    \param[in] surf  - \ru Проверяемая поверхность.
                       \en Checking surface. \~
  */
  bool        IsCurveOnSurface( const MbCurve3D & curve, const MbSurface & surf ) const;

  /** \brief \ru Сопрягаются ли кривые с поверхностью   точках пересечения с otherCurve.
             \en Whether the curves are mated with surface in the points of intersection with otherCurve. \~
    \details \ru Сопрягаются ли кривые (касательно, по нормали, гладко) с поверхностью в точках пересечения с otherCurve.
             \en Whether the curves are mated (tangentially, along the normal, smoothly) with surface in the points of intersection with otherCurve. \~
    \param[in]  curves     - \ru Набор проверяемых кривых.
                             \en Set of checking curves. \~
    \param[in]  surf       - \ru Поверхность.
                             \en The surface. \~
    \param[in]  otherCurve - \ru Кривая на этой поверхности.
                             \en Curve on this surface. \~
    \param[out] isTangent  - \ru Признак касательного сопряжения.
                             \en Attribute of the tangent mate. \~
    \param[out] isNormal   - \ru Признак сопряжения по нормали.
                             \en Attribute of normal mate. \~
    \param[out] isSmooth   - \ru Признак гладкого сопряжения.
                             \en Attribute of the smooth mate. \~
  */
  void        AreCurvesMatingToSurface( const RPArray<MbCurve3D> & curves,
                                        const MbSurface          & surf,
                                        const MbCurve3D          * otherCurve,
                                              bool               & isTangent,
                                              bool               & isNormal,
                                              bool               & isSmooth ) const;

  /// \ru Получить точки скрещивания-пересечения кривой с семейством кривых. \en Get crossing-intersection points of curves with the set of curves.
  bool        GetPointsOfCrossing( const MbCurve3D & curve, const RPArray<MbCurve3D> & otherCurves,
                                   SArray<MbCartPoint3D> & res ) const;
  /// \ru Проверка на наличие контуров и ломаных. \en Check for contours and broken lines.
  bool        CheckMultiSegment( const MbSNameMaker & snMaker ) const;
  /// \ru Обратить порядок следования кривых по второму направлению, чтобы directOrderV был true. \en Invert order of curves along the second direction to directOrderV is true.
  void        InvertCurvesV ();

  /// \ru Получить кривую на границе с номером i. \en Get i-th curve on the boundary.
  const MbCurve3D * GetBorderCurve( ptrdiff_t i ) const;
  /// \ru Получить тип сопряжения на границе с номером i. \en Get i-th mate type on the boundary.
  MbeMatingType GetTransitType( ptrdiff_t i ) const;
  /// \ru Получить поверхность сопряжения на границе с номером i. \en Get i-th mate surface on the boundary.
  const MbSurface * GetSurface( size_t i ) const;
  /// \ru Получить поверхность сопряжения на границе с номером i. \en Get i-th mate surface on the boundary.
  MbSurface * SetSurface( size_t i );
  /// \ru Получить направление сопряжения на границе с номером i. \en Get i-th mate direction on the boundary.
  bool IsDefaultDirection( size_t i ) const;

  /// \ru Замкнутость по U направлению. \en Closedness along U direction.
  bool        GetUClosed() const { return uClosed; }
  /// \ru Замкнутость по V направлению. \en Closedness along V direction.
  bool        GetVClosed() const { return vClosed; }
  /// \ru Замкнутость по U направлению. \en Closedness along U direction.
  void        SetUClosed( bool cls ) { uClosed = cls; }
  /// \ru Замкнутость по V направлению. \en Closedness along V direction.
  void        SetVClosed( bool cls ) { vClosed = cls; }

  /// \ru Количество кривых по U. \en The count of curves along U.
  size_t      GetCurvesUCount() const { return curvesU.Count(); }
  /// \ru Максимальный индекс в массиве кривых по U. \en The maximum index in the array of curves along U.
  ptrdiff_t   GetCurvesUMaxIndex() const { return curvesU.MaxIndex(); }
  /// \ru Получить кривую по индексу. \en Get the curve by the index.
  const MbCurve3D * GetCurveU( size_t k ) const { return ((k < curvesU.Count()) ? curvesU[k] : NULL); }
  /// \ru Получить кривую по индексу. \en Get the curve by the index.
  MbCurve3D * SetCurveU( size_t k )       { return ((k < curvesU.Count()) ? curvesU[k] : NULL); }
  /// \ru Получить кривые по U. \en Get curves along U.
  void        GetCurvesU( RPArray<MbCurve3D> & curves ) const { curves.AddArray(curvesU); }
  /// \ru Установить кривые по U. \en Set curves along U.
  void        SetCurvesU( const RPArray<MbCurve3D> & newCurves );
  /// \ru Отцепить кривые по U. \en Detach curves along U.
  void        DetachCurvesU( RPArray<MbCurve3D> & curves );
  /// \ru Найти кривую. \en Find curve.
  size_t      FindCurveU( const MbCurve3D * curve ) const { return curvesU.FindIt( curve ); }

  /// \ru Количество кривых по V. \en The count of curves along V.
  size_t      GetCurvesVCount() const { return curvesV.Count(); }
  /// \ru Максимальный индекс в массиве кривых по V. \en The maximum index in the array of curves along V.
  ptrdiff_t   GetCurvesVMaxIndex() const { return curvesV.MaxIndex(); }
  /// \ru Получить кривую по индексу. \en Get the curve by the index.
  const MbCurve3D * GetCurveV( size_t k ) const { return ((k < curvesV.Count()) ? curvesV[k] : NULL); }
  /// \ru Получить кривую по индексу. \en Get the curve by the index.
  MbCurve3D * SetCurveV( size_t k ) const { return ((k < curvesV.Count()) ? curvesV[k] : NULL); }
  /// \ru Получить кривые по V. \en Get curves along V.
  void        GetCurvesV( RPArray<MbCurve3D> & curves ) const { curves.AddArray(curvesV); }
  /// \ru Установить кривые по V. \en Set curves along V.
  void        SetCurvesV( const RPArray<MbCurve3D> & newCurves );
  /// \ru Отцепить кривые по V. \en Detach curves along V.
  void        DetachCurvesV( RPArray<MbCurve3D> & curves );
  /// \ru Найти кривую. \en Find curve.
  size_t      FindCurveV( const MbCurve3D * curve ) const { return curvesV.FindIt( curve ); }

  /// \ru Количество цепочек по U. \en The count of chains along U.
  size_t      GetChainsUCount() const { return chainsU.Count(); }
  /// \ru Максимальный индекс в массиве цепочек по U. \en The maximum index in the array of chains along U.
  ptrdiff_t   GetChainsUMaxIndex() const { return chainsU.MaxIndex(); }
  /// \ru Получить цепочку по индексу. \en Get the chain by the index.
  const MbPolyline3D * GetChainU( size_t k ) const { return ( ( k < chainsU.Count() ) ? chainsU[k] : NULL ); }
  /// \ru Получить цепочку по индексу. \en Get the chain by the index.
  MbPolyline3D * SetChainU( size_t k ) { return ( ( k < chainsU.Count() ) ? chainsU[k] : NULL ); }
  /// \ru Получить цепочки по U. \en Get chains along U.
  void        GetChainsU( RPArray<MbPolyline3D> & chains ) const { chains.AddArray( chainsU ); }
  /// \ru Установить цепочки по U. \en Set chains along U.
  void        SetChainsU( const RPArray<MbPolyline3D> & newChains );
  /// \ru Отцепить цепочки по U. \en Detach chains along U.
  void        DetachChainsU( RPArray<MbPolyline3D> & chains );
  /// \ru Найти цепочку. \en Find chain.
  size_t      FindChainU( const MbPolyline3D * curve ) const { return chainsU.FindIt( curve ); }

  /// \ru Количество цепочек по V. \en The count of chains along V.
  size_t      GetChainsVCount() const { return chainsV.Count(); }
  /// \ru Максимальный индекс в массиве цепочек по V. \en The maximum index in the array of chains along V.
  ptrdiff_t   GetChainsVMaxIndex() const { return chainsV.MaxIndex(); }
  /// \ru Получить цепочку по индексу. \en Get the chain by the index.
  const MbPolyline3D * GetChainV( size_t k ) const { return ( ( k < chainsV.Count() ) ? chainsV[k] : NULL ); }
  /// \ru Получить цепочку по индексу. \en Get the chain by the index.
  MbPolyline3D * SetChainV( size_t k ) { return ( ( k < chainsV.Count() ) ? chainsV[k] : NULL ); }
  /// \ru Получить цепочки по V. \en Get chains along V.
  void        GetChainsV( RPArray<MbPolyline3D> & chains ) const { chains.AddArray( chainsV ); }
  /// \ru Установить цепочки по V. \en Set chains along V.
  void        SetChainsV( const RPArray<MbPolyline3D> & newChains );
  /// \ru Отцепить цепочки по V. \en Detach chains along V.
  void        DetachChainsV( RPArray<MbPolyline3D> & chains );
  /// \ru Найти цепочку. \en Find chain.
  size_t      FindChainV( const MbPolyline3D * curve ) const { return chainsV.FindIt( curve ); }

  /// \ru Установить точку. \en Set point.
  void        SetPoint( const MbPoint3D * pnt );
  /// \ru Получить точку. \en Get point.
  const MbPoint3D * GetPoint() const { return point; }
  /// \ru Получить точку. \en Get point.
  MbPoint3D * SetPoint() { return point; }


  /**
    \ru \name Вспомогательные функции геометрических преобразований.
    \en \name Auxiliary functions of geometric transformations.
    \{ */
  /// \ru Преобразовать кривые согласно матрице. \en Transform curves according to the matrix.
  void        Transform( const MbMatrix3D &, MbRegTransform * ireg );
  /// \ru Сдвинуть кривые вдоль вектора. \en Move curves along a vector.
  void        Move     ( const MbVector3D &, MbRegTransform * ireg );
  /// \ru Повернуть кривые вокруг оси на заданный угол. \en Rotate curves at a given angle around an axis.
  void        Rotate   ( const MbAxis3D   &, double angle, MbRegTransform * ireg );
  /// \ru Привести кривые к поверхностной форме (кривые на поверхности) \en Convert curves to the surface form (curves on the surface)
  bool        TransformCurves();
  /** \} */

  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool        IsSame( const MeshSurfaceValues &, double accuracy ) const;

  /// \ru Набор граничных поверхность пуст? \en Whether the set of boundary surfaces is empty?
  bool        AreSurfacesEmpty() const { return (surface0 == NULL && surface1 == NULL && surface2 == NULL && surface3 == NULL); }
  /// \ru Нужно ли проверять самопересечения? \en Whether it is necessary to check self-intersections?
  bool        CheckSelfInt() const { return checkSelfInt; }

private:
  void        AddRefCurves();    // \ru Увеличить счетчик ссылок у кривых. \en Increase the reference count of curves.
  void        AddRefPoint();    // \ru Увеличить счетчик ссылок у точки. \en Increase the reference count of point.
  void        AddRefSurfaces();  // \ru Увеличить счетчик ссылок у поверхностей. \en Increase the reference count of surfaces.
  void        ReleaseCurves();   // \ru Удалить кривые. \en Release curves.
  void        ReleasePoint();   // \ru Удалить точку. \en Release point.
  void        ReleaseSurfaces(); // \ru Удалить поверхности. \en Release surfaces.
  // \ru Определить порядок следования кривых по второму направлению. \en Determine the order of curves along the second direction.
  void        CalculateOrderV() const;
  // \ru Привести кривую к типу поверхностной кривой или к контура из SurfaceCurve. \en Convert the curve to type of surface curve or contour from SurfaceCurve.
  bool        TransformToSurfaceCurve( const MbCurve3D          & initCurve,
                                       const MbSurface          & surface,
                                       const RPArray<MbCurve3D> & constrCurves,
                                             MbSurfaceCurve    *& resCurve ) const;
public:
  KNOWN_OBJECTS_RW_REF_OPERATORS_EX( MeshSurfaceValues, MATH_FUNC_EX )
  OBVIOUS_PRIVATE_COPY( MeshSurfaceValues )
};


//------------------------------------------------------------------------------
// \ru Получить тип сопряжения на границе с номером i \en Get i-th mate type on the boundary
//---
inline
MbeMatingType MeshSurfaceValues::GetTransitType( ptrdiff_t i ) const
{
  MbeMatingType res = trt_Position;

  switch ( i ) {
    case 0: res = type0; break;
    case 1: res = type1; break;
    case 2: res = type2; break;
    case 3: res = type3; break;
  }

  return res;
}


//------------------------------------------------------------------------------
/** \brief \ru Данные для построения линейчатой поверхности.
           \en Data for the construction of a ruled surface. \~
  \details \ru Данные для построения линейчатой поверхности по двум кривым. \n
           \en Data for the construction of a ruled surface by two curves. \n \~
  \ingroup Build_Parameters
*/
//---
struct MATH_CLASS RuledSurfaceValues {
  friend class MbRuledShell;
private:
  MbCurve3D *    curve0;         ///< \ru Первая кривая \en The first curve.
  MbCurve3D *    curve1;         ///< \ru Вторая кривая. \en The second curve.
  SArray<double> breaks0;        ///< \ru Параметры разбиения первой кривой curve0. \en Splitting parameters of the first curve0 curve.
  SArray<double> breaks1;        ///< \ru Параметры разбиения второй кривой curve1. \en Splitting parameters of the second curve1 curve.
  bool           joinByVertices; ///< \ru Соединять контура с одинаковым количеством сегментов через вершины. \en Join contour with the same count of segments through vertices.
  bool           checkSelfInt;   ///< \ru Искать самопересечения. \en Find self-intersections.
  bool           simplifyFaces;  ///< \ru Упрощать грани. \en SimplifyFaces.
private:
  /// \ru Конструктор копирования. \en Copy-constructor.
  RuledSurfaceValues( const RuledSurfaceValues &, MbRegDuplicate * ireg );
public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  RuledSurfaceValues();
  /// \ru Деструктор. \en Destructor.
  ~RuledSurfaceValues();

public:
  /** \brief \ru Функция инициализации.
             \en Initialization function. \~
    \details \ru Функция инициализации на оригиналах кривых.
      Контейнеры параметров разбиения кривых будут очищены.
             \en Initialization function on the curves originals.
      Containers of parameters of splitting curves will be cleared. \~
    \param[in] inCurve0 - \ru Кривая для замены первой кривой.
                          \en The curve for the replacement of the first curve. \~
    \param[in] inCurve1 - \ru Кривая для замены второй кривой.
                          \en The curve for the replacement of the second curve. \~
    \param[in] selfInt  - \ru Флаг проверки самопересечений.
                          \en Flag of self-intersections checking. \~
    \return \ru Результат первичной проверки параметров.
            \en The result of the primary scan of parameters. \~
  */
  bool        Init( const MbCurve3D      & inCurve0,
                    const MbCurve3D      & inCurve1,
                          bool             selfInt = false );

  /** \brief \ru Функция инициализации.
             \en Initialization function. \~
    \details \ru Функция инициализации на оригиналах кривых.
             \en Initialization function on the curves originals. \~
    \param[in] inCurve0 - \ru Кривая для замены первой кривой.
                          \en The curve for the replacement of the first curve. \~
    \param[in] inCurve1 - \ru Кривая для замены второй кривой.
                          \en The curve for the replacement of the second curve. \~
    \param[in] pars0    - \ru Параметры разбиения кривой inCurve0.
                          \en The parameters of splitting curve inCurve0. \~
    \param[in] pars1    - \ru Параметры разбиения кривой inCurve1.
                          \en The parameters of splitting curve inCurve1. \~
    \param[in] selfInt  - \ru Флаг проверки самопересечений.
                          \en Flag of self-intersections checking. \~
    \return \ru Результат первичной проверки параметров.
            \en The result of the primary scan of parameters. \~
  */
  bool        Init( const MbCurve3D      & inCurve0,
                    const MbCurve3D      & inCurve1,
                    const SArray<double> & pars0,
                    const SArray<double> & pars1,
                          bool             selfInt = false );

  /** \brief \ru Функция инициализации.
             \en Initialization function. \~
    \details \ru Функция инициализации на оригиналах или копиях кривых.
             \en Initialization function on the curves originals or copies of curve. \~
    \param[in] obj - \ru Копируемые параметры.
                     \en Copy parameters. \~
    \param[in] sameCurves - \ru Флаг использования оригиналов кривых.
                            \en Flag of using originals of curves. \~
  */
  void        Init( const RuledSurfaceValues & obj, bool sameCurves );

  /// \ru Первичная проверка корректности параметров. \en Initial check of parameters correctness
  bool        IsValid() const;
  /// \ru Преобразовать по матрице. \en Transform by matrix.
  void        Transform( const MbMatrix3D &, MbRegTransform * ireg );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D &, MbRegTransform * ireg );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D   &, double angle, MbRegTransform * ireg );
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool        IsSame( const RuledSurfaceValues &, double accuracy ) const;

  /// \ru Получить кривую (первую или вторую). \en Get curve (the first or second).
  const MbCurve3D * GetCurve( bool first ) const { return (first ? curve0 : curve1); }
  /// \ru Получить кривую (первую или вторую). \en Get curve (the first or second).
  MbCurve3D * SetCurve( bool first )       { return (first ? curve0 : curve1); }

  /// \ru Выдать количество параметров разбиения. \en Get the count of splitting parameters.
  size_t      GetParamsCount( bool first ) const { return (first ? breaks0.Count() : breaks1.Count()); }
  /// \ru Выдать массив разбиения. \en Get splitting array.
  void        GetParams( bool first, SArray<double> & breaks ) const { breaks = (first ? breaks0 : breaks1); }
  /// \ru Получить параметр разбиения по индексу. \en Get splitting parameter by index.
  double      GetParam( bool first, size_t k ) const { C3D_ASSERT( k < GetParamsCount( first ) ); return (first ? breaks0[k] : breaks1[k]); }
  /// \ru Установить массив параметров разбиения. \en Set array of splitting parameters.
  void        SetParams( bool first, const SArray<double> & ps ) { if ( first ) breaks0 = ps; else breaks1 = ps; }
  /// \ru Заполнены ли массивы параметров разбиения? \en Whether arrays of splitting parameters are filled?
  bool        IsEmpty()  const { return (breaks0.Count() < 1); }
  /// \ru Нужно ли проверять самопересечения \en Whether it is necessary to check self-intersections
  bool        CheckSelfInt() const { return checkSelfInt; }
  /// \ru Установить флаг соединения через вершины \en Set flag of connection through vertices
  void        SetJoinByVertices( bool byVerts ) { joinByVertices = byVerts; }
  /// \ru Соединяются ли кривые через вершины? \en Whether curves are joined through vertices?
  bool        GetJoinByVertices() const { return joinByVertices; }
  /// \ru Установить флаг упрощения граней. \en Set flag of faces simplification.
  void        SetSimplifyFaces( bool simplFaces ) { simplifyFaces = simplFaces; }
  /// \ru Получить флаг упрощения граней. \en Get flag of faces simplification.
  bool        GetSimplifyFaces() const { return simplifyFaces; }

private:
  // \ru Проверить наличие параметров вершин контура в массиве параметров \en Check for loop vertices parameters in the parameters array
  bool        CheckVertices( const MbCurve3D      & curve,
                             const SArray<double> & breaks ) const;

public:
  KNOWN_OBJECTS_RW_REF_OPERATORS_EX( RuledSurfaceValues, MATH_FUNC_EX )
  OBVIOUS_PRIVATE_COPY( RuledSurfaceValues )
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры удлинения оболочки.
           \en The shell extension parameters. \~
  \details \ru Параметры удлинения оболочки путём продления грани или достраивания грани. \n
           \en The parameters of extension shell by extending or face-filling. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS ExtensionValues {
public:
  /** \brief \ru Типы удлинения.
             \en Types of extension. \~
    \details \ru Типы удлинения оболочки. Указывает форму поверхности удлинения.
             \en Types of shell extension. Indicates the form extension surface. \~
  */
  enum ExtensionType {
    et_same = 0,           ///< \ru По той же поверхности. \en Along the same surface.
    et_tangent,            ///< \ru По касательной к краю. \en Along tangent to the edge.
    et_direction,          ///< \ru По направлению. \en Along the direction.
  };
  /** \brief \ru Способы удлинения.
             \en Ways of extension. \~
    \details \ru Способы удлинения оболочки.
             \en Ways of shell extension. \~
  */
  enum ExtensionWay {
    ew_distance = -2,      ///< \ru Продолжить на расстояние. \en Prolong on the distance.
    ew_vertex   = -1,      ///< \ru Продолжить до вершины. \en Prolong to the vertex.
    ew_surface  =  0,      ///< \ru Продолжить до поверхности. \en Prolong to the surface.
  };
  /** \brief \ru Способы построения боковых рёбер.
             \en Methods of construction of the lateral edges. \~
    \details \ru Способы построения боковых рёбер при удлинении оболочки.
             \en Methods of construction of the lateral edges when extending shell. \~
  */
  enum LateralKind {
    le_normal = 0,         ///< \ru По нормали к кромке. \en Along the normal to boundary.
    le_prolong,            ///< \ru Продлить исходные рёбра. \en Extend the initial edges.
  };

public:
  ExtensionType type;      ///< \ru Тип удлинения. \en Type of extension.
  ExtensionWay  way;       ///< \ru Способ удлинения. \en Way of extension.
  LateralKind   kind;      ///< \ru Способ построения боковых рёбер. \en Method of construction of the lateral edges.
  MbCartPoint3D point;     ///< \ru Точка, до которой удлинить. \en The point to extend.up to which.
  MbVector3D    direction; ///< \ru Направление удлинения. \en Direction of extension.
  double        distance;  ///< \ru Расстояние. \en Distance.
  bool          prolong;   ///< \ru Продолжить по гладко стыкующимся рёбрам. \en Prolong along smoothly mating edges.
  bool          combine;   ///< \ru Объединять грани при возможности. \en Combine faces if it is possible.
private:
  MbFaceShell * shell;     ///< \ru Оболочка. \en A shell.
  MbItemIndex   faceIndex; ///< \ru Номер грани в оболочке. \en The index of face in the shell.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  ExtensionValues();
  /// \ru Конструктор копирования. \en Copy-constructor.
  ExtensionValues( const ExtensionValues & other );
  /// \ru Конструктор. \en Constructor.
  ExtensionValues( ExtensionType t, ExtensionWay w, LateralKind k, const MbCartPoint3D & p,
                   const MbVector3D & dir, double d, bool pro, bool comb, const MbFaceShell * s, const MbItemIndex & fIndex );
  /// \ru Деструктор. \en Destructor.
  virtual ~ExtensionValues();
public:
  /** \brief \ru Функция инициализации.
             \en Initialization function. \~
    \details \ru Функция инициализации удлинения на расстояние.
             \en Initialization function of extending to a distance. \~
    \param[in] t - \ru Тип удлинения.
                   \en Type of extension. \~
    \param[in] k - \ru Способ построения боковых рёбер.
                   \en Method of construction of the lateral edges. \~
    \param[in] v - \ru Направление удлинения.
                   \en Direction of extension. \~
    \param[in] d - \ru Величина удлинения.
                   \en Value of extension. \~
  */
  void        InitByDistance( ExtensionType t, LateralKind k, const MbVector3D & v, double d );

  /** \brief \ru Функция инициализации.
             \en Initialization function. \~
    \details \ru Функция инициализации удлинения до вершины.
             \en Initialization function of extension to the vertex. \~
    \param[in] t - \ru Тип удлинения.
                   \en Type of extension. \~
    \param[in] k - \ru Способ построения боковых рёбер.
                   \en Method of construction of the lateral edges. \~
    \param[in] v - \ru Вершина, до которой строится удлинение.
                   \en The vertex to construct up to. \~
  */
  void        InitByVertex  ( ExtensionType t, LateralKind k, const MbCartPoint3D & v );

  /** \brief \ru Функция инициализации.
             \en Initialization function. \~
    \details \ru Функция инициализации удлинения до поверхности.
             \en Initialization function of extension to the surface. \~
    \param[in] t - \ru Тип удлинения.
                   \en Type of extension. \~
    \param[in] k - \ru Способ построения боковых рёбер.
                   \en Method of construction of the lateral edges. \~
    \param[in] f - \ru Грань оболочки.
                   \en Face of the shell. \~
    \param[in] s - \ru Тело для замены оболочки.
                   \en Solid for replacement of shell. \~
  */
  void        InitBySurface ( ExtensionType t, LateralKind k, const MbFace * f, const MbSolid * s );

  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D & matr, MbRegTransform * ireg = NULL );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D & to, MbRegTransform * ireg = NULL );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D & axis, double ang, MbRegTransform * ireg = NULL );

  /// \ru Получить оболочку. \en Get the shell.
  const MbFaceShell * GetShell() const { return shell; }
  /// \ru Номер грани в оболочке. \en The index of face in the shell.
  const MbItemIndex & GetFaceIndex() const { return faceIndex; }
  /// \ru Замена оболочки и ее выбранной грани. \en Replacement of shell and its selected face.
  void        SetShell( const MbFace * f, const MbSolid * s );
  /// \ru Оператор присваивания. \en Assignment operator.
  void        operator = ( const ExtensionValues & other );

  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool        IsSame( const ExtensionValues & other, double accuracy ) const;

  KNOWN_OBJECTS_RW_REF_OPERATORS( ExtensionValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Данные для построения поверхности соединения.
           \en Data for construction of surface of the joint. \~
  \details \ru Данные для построения поверхности соединения по двум кривым на поверхностях. \n
           \en Data for the construction of surface of the joint by two curves on the surfaces. \n \~
  \ingroup Build_Parameters
*/
//---
struct MATH_CLASS JoinSurfaceValues {
public:
  /** \brief \ru Типы сопряжения поверхностей.
             \en Type of surfaces join. \~
    \details \ru Типы сопряжения поверхностей определяет стыковку края сопрягаемой поверхности и поверхности сопряжения.
             \en Types of join of surfaces determines join of edge of joining surface and surface of the joint. \~
  */
  enum JoinConnType {
    js_Position = 0,  ///< \ru По позиции. \en By position.
    js_NormPlus,      ///< \ru По нормали в положительном направлении вектора нормали. \en Along the normal in the positive direction of normal vector.
    js_NormMinus,     ///< \ru По нормали в отрицательном направлении вектора нормали. \en Along the normal in the negative direction of normal vector.
    js_G1Plus,        ///< \ru По касательной к поверхности, слева по направлению касательной к кривой пересечения. \en The type of conjugation along the tangent to the surface, to the left along the tangent to the intersection curve.
    js_G1Minus,       ///< \ru По касательной к поверхности, справа по направлению касательной к кривой пересечения. \en The type of conjugation along the tangent to the surface, to the right along the tangent to the intersection curve.
    js_G2Plus,        ///< \ru По касательной к поверхности, слева по направлению касательной к кривой пересечения, гладкая. \en The type of conjugation along the tangent to the surface, to the left along the tangent to the intersection curve, smooth.
    js_G2Minus,       ///< \ru По касательной к поверхности, справа по направлению касательной к кривой пересечения, гладкая. \en The type of conjugation along the tangent to the surface, to the right along the tangent to the intersection curve, smooth.
  };
public:
  JoinConnType          connType1;        ///< \ru Тип сопряжения поверхности соединения с поверхностью 1. \en Join type of surface of the joint with the surface 1.
  JoinConnType          connType2;        ///< \ru Тип сопряжения поверхности соединения с поверхностью 2. \en Join type of surface of the joint with the surface 2.
  double                tension1;         ///< \ru Натяжение для соединения с поверхностью 1. \en Tension for joining with surface 1.
  double                tension2;         ///< \ru Натяжение для соединения с поверхностью 2. \en Tension for joining with surface 2.
  SArray<double>        breaks0;          ///< \ru Параметры разбиения первой кривой curve0. \en Splitting parameters of the first curve0 curve.
  SArray<double>        breaks1;          ///< \ru Параметры разбиения первой кривой curve1. \en Splitting parameters of the first curve1 curve.
  bool                  checkSelfInt;     ///< \ru Искать самопересечения. \en Find self-intersections.
  bool                  edgeConnType1;    ///< \ru Построение боковой границы как продолжение ребра. \en Construct lateral boundary as edge extension.
  bool                  edgeConnType2;    ///< \ru Построение боковой границы как продолжение ребра. \en Construct lateral boundary as edge extension.
  MbVector3D          * boundDirection11; ///< \ru Вектор направления, определяющий боковую границу, в точке (0, 0) поверхности. \en Direction vector determines lateral boundary in the point (0, 0) of the surface.
  MbVector3D          * boundDirection12; ///< \ru Вектор направления, определяющий боковую границу, в точке (1, 0) поверхности. \en Direction vector determines lateral boundary in the point (1, 0) of the surface.
  MbVector3D          * boundDirection21; ///< \ru Вектор направления, определяющий боковую границу, в точке (0, 1) поверхности. \en Direction vector determines lateral boundary in the point (0, 1) of the surface.
  MbVector3D          * boundDirection22; ///< \ru Вектор направления, определяющий боковую границу, в точке (1, 1) поверхности. \en Direction vector determines lateral boundary in the point (1, 1) of the surface.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  JoinSurfaceValues()
    : connType1         ( js_G1Plus )
    , connType2         ( js_G1Plus )
    , tension1          ( 0.5       )
    , tension2          ( 0.5       )
    , breaks0           ( 0, 1      )
    , breaks1           ( 0, 1      )
    , checkSelfInt      ( false     )
    , edgeConnType1     ( false     )
    , edgeConnType2     ( false     )
    , boundDirection11  ( NULL      )
    , boundDirection12  ( NULL      )
    , boundDirection21  ( NULL      )
    , boundDirection22  ( NULL      )
  {}
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  JoinSurfaceValues( JoinConnType t1, JoinConnType t2, double tens1, double tens2, bool selfInt = false )
    : connType1         ( t1      )
    , connType2         ( t2      )
    , tension1          ( tens1   )
    , tension2          ( tens2   )
    , breaks0           ( 0, 1    )
    , breaks1           ( 0, 1    )
    , checkSelfInt      ( selfInt )
    , edgeConnType1     ( false   )
    , edgeConnType2     ( false   )
    , boundDirection11  ( NULL    )
    , boundDirection12  ( NULL    )
    , boundDirection21  ( NULL    )
    , boundDirection22  ( NULL    )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  JoinSurfaceValues( const JoinSurfaceValues & other );

public:
  /// \ru Деструктор. \en Destructor.
  virtual ~JoinSurfaceValues();
  /// \ru Функция инициализации. \en Initialization function.
  bool        Init( const SArray<double> & initBreaks0,
                    const SArray<double> & initBreaks1,
                          bool             initCheckSelfInt,
                          JoinConnType     initConnType1,
                          double           initTension1,
                          bool             initEdgeConnType1,
                    const MbVector3D *     initBoundDir11,
                    const MbVector3D *     initBoundDir12,
                          JoinConnType     initConnType2,
                          double           initTension2,
                          bool             initEdgeConnType2,
                    const MbVector3D *     initBoundDir21,
                    const MbVector3D *     initBoundDir22 );
  /// \ru Функция копирования. \en Copy function.
  void        Init( const JoinSurfaceValues & other );
  /// \ru Оператор присваивания. \en Assignment operator.
  void        operator = ( const JoinSurfaceValues & other ) { Init( other ); }

  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D &, MbRegTransform * ireg );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D &, MbRegTransform * ireg );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D   &, double angle, MbRegTransform * ireg );

  /// \ru Выдать количество параметров разбивки. \en Get the count of splitting parameters.
  size_t      GetParamsCount( bool first ) const { return (first ? breaks0.size() : breaks1.size()); }
  /// \ru Получить параметры разбивки (первую или вторую группу). \en Get splitting parameters (the first or second group).
  void        GetParams( bool first, SArray<double> & breaks ) const { breaks = (first ? breaks0 : breaks1); }
  /// \ru Получить параметры разбивки (первую или вторую группу). \en Get splitting parameters (the first or second group).
  double      GetParam( bool first, size_t k ) const { C3D_ASSERT( k < GetParamsCount( first ) ); return (first ? breaks0[k] : breaks1[k]); }
  /// \ru Установить параметры разбивки. \en Set splitting parameters.
  void        SetParams( bool first, const SArray<double> & ps ) { if ( first ) breaks0 = ps; else breaks1 = ps; }
  /// \ru Параметры разбивки не заполнены? \en Whether splitting parameters are not filled?
  bool        IsEmpty()  const { return breaks0.empty(); }
  /// \ru Получить флаг проверки самопересечений. \en Get the flag of checking self-intersection.
  bool        CheckSelfInt() const { return checkSelfInt; }
  /// \ru Установить флаг проверки самопересечений. \en Set the flag of checking self-intersection.
  void        SetSelfInt( bool aChech ) { checkSelfInt = aChech; }

  /// \ru Выдать параметры параметры установки боковых граней. \en Get setting parameters of lateral faces.
  bool        GetEdgeConnType( bool isFirst = true ) const { return isFirst ? edgeConnType1 : edgeConnType2; }
  /// \ru Установить параметры параметры установки боковых граней. \en Set setting parameters of lateral faces.
  void        SetEdgeConnType( bool connType, bool isFirst = true ) { isFirst ? edgeConnType1 = connType : edgeConnType2 = connType; }

  /** \brief \ru Выдать вектор направления.
             \en Get the direction vector. \~
    \details \ru Выдать вектор направления, определяющий боковую границу.
             \en Get the direction vector determining lateral boundary. \~
    \param[in] num - \ru Номер границы:\n
                     num = 1 - вектор boundDirection11,\n
                     num = 2 - вектор boundDirection12,\n
                     num = 3 - вектор boundDirection21,\n
                     num = 4 - вектор boundDirection22.
                     \en The index of boundary:\n
                     num = 1 - vector boundDirection11,\n
                     num = 2 - vector boundDirection12,\n
                     num = 3 - vector boundDirection21,\n
                     num = 4 - vector boundDirection22. \~
  */
  const MbVector3D * GetBoundDirection( size_t num ) const;

  /** \brief \ru Установить вектор направления.
             \en Set the direction vector. \~
    \details \ru Установить вектор направления, определяющий боковую границу.
             \en Set the direction vector determining lateral boundary. \~
    \param[in] num - \ru Номер границы:\n
                     num = 1 - изменяем вектор boundDirection11,\n
                     num = 2 - изменяем вектор boundDirection12,\n
                     num = 3 - изменяем вектор boundDirection21,\n
                     num = 4 - изменяем вектор boundDirection22.
                     \en The index of boundary:\n
                     num = 1 - change vector boundDirection11,\n
                     num = 2 - change vector boundDirection12,\n
                     num = 3 - change vector boundDirection21,\n
                     num = 4 - change vector boundDirection22. \~
    \param[in] aDirect - \ru Новый вектор направления.
                         \en The new direction vector. \~
  */
  void        SetBoundDirection( size_t num, const MbVector3D * aDirect );

  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool        IsSame( const JoinSurfaceValues & other, double accuracy ) const
  {
    bool isSame = false;

    if ( (other.connType1 == connType1) &&
         (other.connType2 == connType2) &&
         (other.checkSelfInt == checkSelfInt) &&
         (other.edgeConnType1 == edgeConnType1) &&
         (other.edgeConnType2 == edgeConnType2) &&
         (::fabs(other.tension1 - tension1) < accuracy) &&
         (::fabs(other.tension2 - tension2) < accuracy) )
    {
      const size_t breaksCnt0 = breaks0.size();
      const size_t breaksCnt1 = breaks1.size();
      if ( (other.breaks0.size() == breaksCnt0) && (other.breaks1.size() == breaksCnt1) ) {
        isSame = true;

        size_t k;
        for ( k = 0; k < breaksCnt0 && isSame; ++k ) {
          if ( ::fabs(other.breaks0[k] - breaks0[k]) > accuracy )
            isSame = false;
        }
        if ( isSame ) {
          for ( k = 0; k < breaksCnt1 && isSame; ++k ) {
            if ( ::fabs(other.breaks1[k] - breaks1[k]) > accuracy )
              isSame = false;
          }
        }
        if ( isSame ) {
          bool isBoundDir11 = ((other.boundDirection11 != NULL) && (boundDirection11 != NULL));
          bool isBoundDir12 = ((other.boundDirection12 != NULL) && (boundDirection12 != NULL));
          bool isBoundDir21 = ((other.boundDirection21 != NULL) && (boundDirection21 != NULL));
          bool isBoundDir22 = ((other.boundDirection22 != NULL) && (boundDirection22 != NULL));

          if ( isSame && isBoundDir11 )
            isSame = c3d::EqualVectors( *other.boundDirection11, *boundDirection11, accuracy );
          if ( isSame && isBoundDir12 )
            isSame = c3d::EqualVectors( *other.boundDirection12, *boundDirection12, accuracy );
          if ( isSame && isBoundDir21 )
            isSame = c3d::EqualVectors( *other.boundDirection21, *boundDirection21, accuracy );
          if ( isSame && isBoundDir22 )
            isSame = c3d::EqualVectors( *other.boundDirection22, *boundDirection22, accuracy );
        }
      }
    }
    return isSame;
  }

public:
  KNOWN_OBJECTS_RW_REF_OPERATORS( JoinSurfaceValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
  DECLARE_NEW_DELETE_CLASS( JoinSurfaceValues )
  DECLARE_NEW_DELETE_CLASS_EX( JoinSurfaceValues )
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры преобразования триангуляции в оболочку.
           \en Operation parameters of grids-to-shell conversion. \~
  \details \ru Параметры преобразования триангуляции в оболочку.
           \en Operation parameters of grids-to-shell conversion. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS GridsToShellValues {
public:
  bool sewGrids;        ///< \ru Сшивать наборы граней от разных сеток триангуляции. \en Sew together faces of grids.
  bool mergeFaces;      ///< \ru Сливать подобные грани (true). \en Whether to merge similar faces (true). 
  bool useGridSurface;  ///< \ru Использовать поверхность на базе триангуляции. \en Use the surface based on triangulation.
public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  GridsToShellValues()
    : sewGrids      ( true  )
    , mergeFaces    ( false )
    , useGridSurface( false )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  GridsToShellValues( const GridsToShellValues & other )
    : sewGrids      ( other.sewGrids       )
    , mergeFaces    ( other.mergeFaces     )
    , useGridSurface( other.useGridSurface )
  {}
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  GridsToShellValues( bool sg, bool mf, bool ugs = false )
    : sewGrids      ( sg )
    , mergeFaces    ( mf )
    , useGridSurface( ugs )
  {}
  /// \ru Оператор присваивания. \en Assignment operator.
  GridsToShellValues & operator = ( const GridsToShellValues & other )
  {
    sewGrids = other.sewGrids;
    mergeFaces = other.mergeFaces;
    useGridSurface = other.useGridSurface;
    return *this;
  }
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры создания срединной оболочки между выбранными гранями тела.
           \en Operation parameters of median shell between selected faces of solid. \~
  \details \ru Параметры создания срединной оболочки между выбранными гранями тела.
               Выбранные грани должны быть эквидистантны по отношению друг к другу.
               Грани должны принадлежать одному и тому же телу.
           \en Operation parameters of median shell between selected faces of solid.
               Selected face pairs should be offset from each other. 
               The faces must belong to the same body.\~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MedianShellValues {
public:
  double position; ///< \ru Параметр смещения срединной оболочки относительно первой грани из пары. По умолчанию равен 50% расстояния между гранями. \en Parameter of shift the median surface from first face in faces pair. By default is 50% from distance between faces in pair.
  double dmin;     ///< \ru Минимальный параметр эквидистантности. \en Minimal equidistation value.
  double dmax;     ///< \ru Максимальный параметр эквидистантности. \en Maximal equidistation value.
public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MedianShellValues()
    : position   ( 0.5  )
    , dmin       ( 0.0  )
    , dmax       ( 0.0  )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  MedianShellValues( const MedianShellValues & other )
    : position   ( other.position )
    , dmin       ( other.dmin     )
    , dmax       ( other.dmax     )
  {}
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  MedianShellValues( double pos, double d1, double d2 )
    : position   ( pos  )
    , dmin       ( d1   )
    , dmax       ( d2   )
  {}

public:
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MedianShellValues & obj, double accuracy ) const
  {
    if ( (::fabs(dmin - obj.dmin) < accuracy) && 
         (::fabs(dmax - obj.dmax) < accuracy) &&
         (::fabs( position - obj.position) < accuracy ) )
    {
      return true;
    }
    return false;
  }

public:
  /// \ru Оператор присваивания. \en Assignment operator.
  MedianShellValues & operator = ( const MedianShellValues & other )
  {
    position = other.position;
    dmin = other.dmin;
    dmax = other.dmax;
    return *this;
  }

KNOWN_OBJECTS_RW_REF_OPERATORS( MedianShellValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Множество граней для создания срединной оболочки.
           \en Set of faces for build a median shell. \~
\details \ru Множество граней для создания срединной оболочки.
         \en Set of faces for build a median shell.\~
\ingroup Build_Parameters
*/
// ---
class MATH_CLASS MedianShellFaces {
private:
  std::vector<c3d::ItemIndexPair> facePairs; ///< \ru Набор пар выбранных граней. \en Set of selected faces pairs.
  std::vector<double>             distances; ///< \ru Вектор смещений второй грани по отношению к первой в каждой паре. \en Vector of shift values of second face in reference to first face in each pair.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MedianShellFaces() {
    facePairs.resize( 0 );
    distances.resize( 0 );
  }
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  MedianShellFaces( const std::vector<c3d::ItemIndexPair> & pairs )
  {
    facePairs = pairs;
    distances.resize( pairs.size() );
  }
  /// \ru Деструктор. \en Destructor.
  ~MedianShellFaces() {}

public:
  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D & );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move( const MbVector3D & );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate( const MbAxis3D   &, double angle );
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool        IsSame( const MedianShellFaces & obj, double accuracy ) const;

public:
  /// \ru Добавить в набор пару граней. \en Add pair of faces.
  void                  AddFacePair( const MbItemIndex & f1, const MbItemIndex & f2, double dist = 0.0 )
  {
    facePairs.push_back( c3d::ItemIndexPair(f1,f2) );
    distances.push_back( dist );
  }
  /// \ru Получить пару граней по индексу. \en Get pair of faces by index.
  const c3d::ItemIndexPair & _GetFacePair( size_t index ) const { return facePairs[index];}
  /// \ru Удалить пару граней из набора. \en Remove pair of faces from set.
  void                  RemovePairByIndex( size_t index )
  {
    facePairs.erase( facePairs.begin() + index );
    distances.erase( distances.begin() + index );
  }
  /// \ru Вернуть расстояние между гранями. \en Get distance between faces.
  const double &       _GetDistance( size_t index ) const { return distances[index]; }
  /// \ru Установить расстояние между гранями. \en Set distance between faces.
  void                 _SetDistance( size_t index, double value ) { distances[index] = value; }
  /// \ru Вернуть количество пар граней в наборе. \en Get count of pairs in given set.
  size_t                Count() const { return facePairs.size(); }
  /// \ru Оператор присваивания. \en Assignment operator.
  MedianShellFaces &    operator = ( const MedianShellFaces & other ) {
    facePairs = other.facePairs;
    distances = other.distances;
    return *this;
  }
  /// \ru Очистка текущего набора. \en Clear current faces set.
  void                  Clear() { facePairs.clear(); distances.clear(); }

KNOWN_OBJECTS_RW_REF_OPERATORS( MedianShellFaces ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/// \ru Типы продления секущих поверхностей. \en Prolongation types of cutter surfaces.
// ---
enum MbeSurfaceProlongType {
  cspt_None            = 0x00, // 0000 ///< \ru Не продлевать. \en Don't prolong. 
  cspt_Planar          = 0x01, // 0001 ///< \ru Плоские поверхности. \en Planar surfaces. 
  cspt_RevolutionAxis  = 0x02, // 0010 ///< \ru Поверхности вращения (вдоль оси). \en Revolution surfaces (along axis). 
  cspt_RevolutionAngle = 0x04, // 0100 ///< \ru Поверхности вращения (по углу). \en Revolution surfaces (by angle). 
  cspt_Revolution      = 0x06, // 0110 ///< \ru Поверхности вращения. \en Revolution surfaces. 
};

//------------------------------------------------------------------------------
/** \brief \ru Параметры операции резки оболочки.
           \en Shell cutting operation parameters. \~
  \details \ru Параметры операции резки оболочки. \n
           \en Shell cutting operation parameters. \n \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS MbShellCuttingParams {
public:
  /// \ru Состояние типа продления секущих поверхностей. \en State of prolongation types of cutter surfaces.
  struct ProlongState {
    typedef uint8 UintType;
  protected:
    bool      active; ///< \ru Включено ли дополнительное управление продлением. \en Whether additional prolongation control is active.
    UintType  type;   ///< \ru Тип продления секущей поверхности. \en Prolongation type of cutting surface. 
  public:
    ProlongState() : active( false ), type( cspt_None ) {}
    explicit ProlongState( MbeSurfaceProlongType t ) : active( true ), type( (UintType)t ) {}
    ProlongState( const ProlongState & ps ) { active = ps.active; type = ps.type; }
  public:
    const ProlongState &  operator =  ( const ProlongState & ps ) { active = ps.active; type = ps.type; return *this; }
          bool            operator == ( const ProlongState & ps ) const { return (active == ps.active && type == ps.type); }
  public:
          void            Reset() { active = false; type = cspt_None; }
          void            Init( const ProlongState & ps ) { active = ps.active; type = ps.type; }
          void            Init( bool a, UintType t ) { active = a; type = t; }
          bool            IsActive() const { return active; }
          void            SetActive( bool a ) { active = a; }
          UintType        GetType() const { return type;  }
          void            SetType( MbeSurfaceProlongType t ) { type  = (UintType)t; }
          void            AddType( MbeSurfaceProlongType t ) { type |= (UintType)t; }
          void            SetActiveType( bool a, MbeSurfaceProlongType t ) { active = a; type =  (UintType)t; }
          void            AddActiveType( bool a, MbeSurfaceProlongType t ) { active = a; type |= (UintType)t; }
  };
private:
  MbSplitData    cutterData;    ///< \ru Данные секущего объекта. \en Cutter object(s) data.
  MbBooleanFlags booleanFlags;  ///< \ru Управляющие флаги булевой операции. \en Control flags of the Boolean operation.
  MbSNameMaker   nameMaker;     ///< \ru Именователь операции. \en An object defining names generation in the operation.
  ThreeStates    retainedPart;  ///< \ru Направление отсечения (сохраняемая часть исходной оболочки). \en The direction of cutting off (a part of the source shell to be kept).
  ProlongState   prolongState;  ///< \ru Тип продления режущей поверхности. \en Prolongation type of cutter surface.

public:
  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор. \n
             \en Constructor. \n \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  MbShellCuttingParams( int part, const MbMergingFlags & mergingFlags, bool cutAsClosed, 
                        const MbSNameMaker & snMaker )
    : cutterData  (             )
    , booleanFlags(             )
    , nameMaker   ( snMaker     )
    , retainedPart( ts_neutral  )
    , prolongState(             )
  {
    booleanFlags.InitCutting( cutAsClosed );
    booleanFlags.SetMerging( mergingFlags );
    SetRetainedPart( part );
  }
  /** \brief \ru Конструктор по контуру.
             \en Constructor by a contour. \~
    \details \ru Конструктор по контуру. \n
             \en Constructor by a contour. \n \~
    \param[in]  place          - \ru Локальная система координат, в плоскости XY которой расположен двумерный контур.
                                 \en A local coordinate system the two-dimensional contour is located in XY plane of. \~
    \param[in]  contour        - \ru Двумерный контур выдавливания расположен в плоскости XY локальной системы координат.
                                 \en The two-dimensional contour of extrusion is located in XY plane of the local coordinate system. \~
    \param[in]  sameContour    - \ru Использовать исходный контур (true) или его копию (false).
                                 \en Use the source contour (true) or its copy (false). \~
    \param[in]  dir            - \ru Направление выдавливания контура.
                                 \en Extrusion direction of the contour. \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  MbShellCuttingParams( const MbPlacement3D & place, const MbContour & contour, bool sameContour, const MbVector3D & dir, int part, 
                        const MbMergingFlags & mergingFlags, bool cutAsClosed,
                        const MbSNameMaker & snMaker )
    : cutterData( place, dir, contour, sameContour )
    , booleanFlags(             )
    , nameMaker   ( snMaker     )
    , retainedPart( ts_neutral  )
    , prolongState(             )
  {
    booleanFlags.InitCutting( cutAsClosed );
    booleanFlags.SetMerging( mergingFlags );
    SetRetainedPart( part );
  }
  /** \brief \ru Конструктор по контуру.
             \en Constructor by a contour. \~
    \details \ru Конструктор по контуру. \n
             \en Constructor by a contour. \n \~
    \param[in]  place          - \ru Локальная система координат, в плоскости XY которой расположен двумерный контур.
                                 \en A local coordinate system the two-dimensional contour is located in XY plane of. \~
    \param[in]  contour        - \ru Двумерный контур выдавливания расположен в плоскости XY локальной системы координат.
                                 \en The two-dimensional contour of extrusion is located in XY plane of the local coordinate system. \~
    \param[in]  sameContour    - \ru Использовать исходный контур (true) или его копию (false).
                                 \en Use the source contour (true) or its copy (false). \~
    \param[in]  dir            - \ru Направление выдавливания контура.
                                 \en Extrusion direction of the contour. \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  MbShellCuttingParams( const MbPlacement3D & place, const MbContour & contour, bool sameContour, const MbVector3D & dir, 
                        const MbMergingFlags & mergingFlags, bool cutAsClosed,
                        const MbSNameMaker & snMaker )
    : cutterData( place, dir, contour, sameContour )
    , booleanFlags(             )
    , nameMaker   ( snMaker     )
    , retainedPart( ts_neutral  )
    , prolongState(             )
  {
    booleanFlags.InitCutting( cutAsClosed );
    booleanFlags.SetMerging( mergingFlags );
  }
  /** \brief \ru Конструктор по поверхности.
             \en Constructor by a surface. \~
    \details \ru Конструктор по поверхности. \n
             \en Constructor by a surface. \n \~
    \param[in]  surface        - \ru Режущая поверхность.
                                 \en Cutting plane. \~
    \param[in]  sameSurface    - \ru Использовать исходную поверхность (true) или её копию (false).
                                 \en Use the source surface (true) or its copy (false). \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  MbShellCuttingParams( const MbSurface & surface, bool sameSurface, int part, 
                        const MbMergingFlags & mergingFlags, bool cutAsClosed,
                        const MbSNameMaker & snMaker )
    : cutterData( surface, sameSurface )
    , booleanFlags(             )
    , nameMaker   ( snMaker     )
    , retainedPart( ts_neutral  )
    , prolongState(             )
  {
    booleanFlags.InitCutting( cutAsClosed );
    booleanFlags.SetMerging( mergingFlags );
    SetRetainedPart( part );
  }
  /** \brief \ru Конструктор по поверхности.
             \en Constructor by a surface. \~
    \details \ru Конструктор по поверхности. \n
             \en Constructor by a surface. \n \~
    \param[in]  surface        - \ru Режущая поверхность.
                                 \en Cutting plane. \~
    \param[in]  sameSurface    - \ru Использовать исходную поверхность (true) или её копию (false).
                                 \en Use the source surface (true) or its copy (false). \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  MbShellCuttingParams( const MbSurface & surface, bool sameSurface,
                        const MbMergingFlags & mergingFlags, bool cutAsClosed,
                        const MbSNameMaker & snMaker )
    : cutterData( surface, sameSurface )
    , booleanFlags(             )
    , nameMaker   ( snMaker     )
    , retainedPart( ts_neutral  )
    , prolongState(             )
  {
    booleanFlags.InitCutting( cutAsClosed );
    booleanFlags.SetMerging( mergingFlags );
  }
  /** \brief \ru Конструктор по оболочке.
             \en Constructor by a shell. \~
    \details \ru Конструктор по оболочке. \n
             \en Constructor by a shell. \n \~
    \param[in]  solid          - \ru Режущая оболочка.
                                 \en Cutting shell. \~
    \param[in]  sameSolid      - \ru Использовать исходную поверхность (true) или её копию (false).
                                 \en Use the source surface (true) or its copy (false). \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  MbShellCuttingParams( const MbSolid & solid, bool sameSolid,
                        int part, const MbMergingFlags & mergingFlags, bool cutAsClosed,
                        const MbSNameMaker & snMaker )
    : cutterData( solid, sameSolid, true )
    , booleanFlags(            )
    , nameMaker   ( snMaker    )
    , retainedPart( ts_neutral )
    , prolongState(            )
  {
    booleanFlags.InitCutting( cutAsClosed );
    booleanFlags.SetMerging( mergingFlags );
    SetRetainedPart( part );
  }
  /// \ru Копирующий конструктор. \en Copy constructor. 
  MbShellCuttingParams( const MbShellCuttingParams & other, MbRegDuplicate * iReg )
    : cutterData  ( other.cutterData, false, iReg )
    , booleanFlags( other.booleanFlags )
    , nameMaker   ( other.nameMaker    )
    , retainedPart( other.retainedPart )
    , prolongState( other.prolongState )
  {
  }
  ~MbShellCuttingParams()
  {}
public:
  /** \brief \ru Инициализация по контуру.
             \en Initialize by a contour. \~
    \details \ru Инициализация по контуру. \n
             \en Initialize by a contour. \n \~
    \param[in]  place          - \ru Локальная система координат, в плоскости XY которой расположен двумерный контур.
                                 \en A local coordinate system the two-dimensional contour is located in XY plane of. \~
    \param[in]  contour        - \ru Двумерный контур выдавливания расположен в плоскости XY локальной системы координат.
                                 \en The two-dimensional contour of extrusion is located in XY plane of the local coordinate system. \~
    \param[in]  sameContour    - \ru Использовать исходный контур (true) или его копию (false).
                                 \en Use the source contour (true) or its copy (false). \~
    \param[in]  dir            - \ru Направление выдавливания контура.
                                 \en Extrusion direction of the contour. \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  bool InitPlaneContour( const MbPlacement3D & place, const MbContour & contour, bool sameContour, const MbVector3D & dir,
                         int part, const MbMergingFlags & mergingFlags, bool cutAsClosed,
                         const MbSNameMaker & snMaker )
  {
    if ( cutterData.InitPlaneContour( place, dir, contour, sameContour ) ) {
      nameMaker.SetName( snMaker, true );
      booleanFlags.InitCutting( cutAsClosed );
      booleanFlags.SetMerging( mergingFlags );
      SetRetainedPart( part );
      prolongState.Reset();
      return true;
    }
    return false;
  }
  /** \brief \ru Инициализация по контуру.
             \en Initialize by a contour. \~
    \details \ru Инициализация по контуру. \n
             \en Initialize by a contour. \n \~
    \param[in]  place          - \ru Локальная система координат, в плоскости XY которой расположен двумерный контур.
                                 \en A local coordinate system the two-dimensional contour is located in XY plane of. \~
    \param[in]  contour        - \ru Двумерный контур выдавливания расположен в плоскости XY локальной системы координат.
                                 \en The two-dimensional contour of extrusion is located in XY plane of the local coordinate system. \~
    \param[in]  sameContour    - \ru Использовать исходный контур (true) или его копию (false).
                                 \en Use the source contour (true) or its copy (false). \~
    \param[in]  dir            - \ru Направление выдавливания контура.
                                 \en Extrusion direction of the contour. \~
  */
  bool InitPlaneContour( const MbPlacement3D & place, const MbContour & contour, bool sameContour, const MbVector3D & dir )
  {
    if ( cutterData.InitPlaneContour( place, dir, contour, sameContour ) ) {
      prolongState.Reset();
      return true;
    }
    return false;
  }
  /** \brief \ru Конструктор по поверхности.
             \en Constructor by a surface. \~
    \details \ru Конструктор по поверхности. \n
             \en Constructor by a surface. \n \~
    \param[in]  surface        - \ru Режущая поверхность.
                                 \en Cutting plane. \~
    \param[in]  sameSurface    - \ru Использовать исходную поверхность (true) или её копию (false).
                                 \en Use the source surface (true) or its copy (false). \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  bool InitSurface( const MbSurface & surface, bool sameSurface,
                    int part, const MbMergingFlags & mergingFlags, bool cutAsClosed,
                    const MbSNameMaker & snMaker )
  {
    if ( cutterData.InitSurfaces( surface, sameSurface ) ) {
      nameMaker.SetName( snMaker, true );
      booleanFlags.InitCutting( cutAsClosed );
      booleanFlags.SetMerging( mergingFlags );
      SetRetainedPart( part );
      prolongState.Reset();
      return true;
    }
    return false;
  }
  /** \brief \ru Конструктор по поверхности.
             \en Constructor by a surface. \~
    \details \ru Конструктор по поверхности. \n
             \en Constructor by a surface. \n \~
    \param[in]  surface        - \ru Режущая поверхность.
                                 \en Cutting plane. \~
    \param[in]  sameSurface    - \ru Использовать исходную поверхность (true) или её копию (false).
                                 \en Use the source surface (true) or its copy (false). \~
    \param[in]  prType         - \ru Тип продления режущей поверхности.
                                 \en Cutter surface prolong type. \~
  */
  bool InitSurface( const MbSurface & surface, bool sameSurface, ProlongState prState )
  {
    if ( cutterData.InitSurfaces( surface, sameSurface ) ) {
      prolongState.Init( prState );
      return true;
    }
    return false;
  }
  /** \brief \ru Конструктор по оболочке.
             \en Constructor by a shell. \~
    \details \ru Конструктор по оболочке. \n
             \en Constructor by a shell. \n \~
    \param[in]  solid          - \ru Режущая оболочка.
                                 \en Cutting shell. \~
    \param[in]  sameSolid      - \ru Использовать исходную поверхность (true) или её копию (false).
                                 \en Use the source surface (true) or its copy (false). \~
    \param[in]  part           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                                 \en A part of the source shell to be kept (+1, -1). \~
    \param[in]  mergingFlags   - \ru Флаги слияния элементов оболочки.
                                 \en Control flags of shell items merging. \~
    \param[in]  cutAsClosed    - \ru Построить замкнутую оболочку.
                                 \en Create a closed shell. \~
    \param[in]  snMaker        - \ru Именователь операции.
                                 \en An object defining names generation in the operation. \~
  */
  bool InitSolid( const MbSolid & solid, bool sameSolid,
                  int part, const MbMergingFlags & mergingFlags, bool cutAsClosed,
                  const MbSNameMaker & snMaker )
  {
    if ( cutterData.InitSolid( solid, sameSolid, true ) ) {
      nameMaker.SetName( snMaker, true );
      booleanFlags.InitCutting( cutAsClosed );
      booleanFlags.SetMerging( mergingFlags );
      SetRetainedPart( part );
      prolongState.Reset();
      return true;
    }
    return false;
  }
  /** \brief \ru Конструктор по оболочке.
             \en Constructor by a shell. \~
    \details \ru Конструктор по оболочке. \n
             \en Constructor by a shell. \n \~
    \param[in]  solid          - \ru Режущая оболочка.
                                 \en Cutting shell. \~
    \param[in]  sameSolid      - \ru Использовать исходную поверхность (true) или её копию (false).
                                 \en Use the source surface (true) or its copy (false). \~
  */
  bool InitSolid( const MbSolid & solid, bool sameSolid )
  {
    if ( cutterData.InitSolid( solid, sameSolid, true ) ) {
      prolongState.Reset();
      return true;
    }
    return false;
  }
  /** \brief \ru Конструктор по оболочке.
             \en Constructor by a shell. \~
    \details \ru Конструктор по оболочке. \n
             \en Constructor by a shell. \n \~
    \param[in]  creators       - \ru Построители режущей оболочки.
                                 \en Cutting shell creators. \~
    \param[in]  sameCreators   - \ru Использовать оригиналы (true) или копии (false) построителей.
                                 \en Use original creators (true) or its copies (false). \~
  */
  template <class CreatorsVector>
  bool InitSolid( const CreatorsVector & creators, bool sameCreators )
  {
    if ( cutterData.InitSolid( creators, sameCreators ) ) {
      prolongState.Reset();
      return true;
    }
    return false;
  }
public:
  /// \ru Это резка плоским контуром? \en Is cutting by planar contour?
        bool              IsCuttingByPlanarContour()  const { return (cutterData.GetSketchCurvesCount() > 0 && cutterData.GetSketchCurve(0) != NULL); }
  /// \ru Это резка поверхностью? \en Is cutting by surface?
        bool              IsCuttingBySurface() const { return (cutterData.GetSurfacesCount() > 0 && cutterData.GetSurface(0) != NULL); }
  /// \ru Это резка оболочкой? \en Is cutting by shell?
        bool              IsCuttingBySolid()   const { return (cutterData.GetCreatorsCount() > 0 && cutterData.GetCreator(0) != NULL) || (cutterData.GetSolidShell() != NULL); }

  /// \ru Получить данные секущего объекта. \en Get cutter object(s) data.
  const MbSplitData &     GetCutterData() const { return cutterData; }

  /// \ru Получить управляющие флаги булевой операции. \en Get control flags of the Boolean operation.
  const MbBooleanFlags &  GetBooleanFlags() const { return booleanFlags; }
  /// \ru Получить управляющие флаги булевой операции. \en Get control flags of the Boolean operation.
        MbBooleanFlags &  SetBooleanFlags()       { return booleanFlags; }

  /// \ru Получить именователь операции. \en Get the object defining names generation in the operation.
  const MbSNameMaker &    GetNameMaker() const { return nameMaker;  }

  /// \ru Получить требование по оставляемой части. \en Get retained part demand.
        ThreeStates       GetRetainedPart() const { return retainedPart; }
  /// \ru Установить требование по оставляемой части. \en Set retained part demand.
        void              SetRetainedPart( int part );

  /// \ru Получить тип продления режущей поверхности. \en Get cutter surface prolong type.
  const ProlongState &    GetProlongState() const { return prolongState; }
  /// \ru Получить тип продления режущей поверхности. \en Get cutter surface prolong type.
        void              ResetProlongState() { prolongState.Reset(); }
  /// \ru Добавить тип продления режущей поверхности. \en Add cutter surface prolong type.
        void              SetSurfaceProlongType( MbeSurfaceProlongType pt ) { prolongState.SetActiveType( true, pt ); }
  /// \ru Добавить тип продления режущей поверхности. \en Add cutter surface prolong type.
        void              AddSurfaceProlongType( MbeSurfaceProlongType pt ) { prolongState.AddActiveType( true, pt ); }

  /// \ru Получить локальную систему координат двумерных кривых. \en Get the local coordinate system of two-dimensional curves. 
  const MbPlacement3D &   GetSketchPlace() const { return cutterData.GetSketchPlace(); }
  /// \ru Получить вектор направления выдавливания двумерных кривых. \en Get the extrusion direction vector of two-dimensional curves. 
  const MbVector3D &      GetSketchDirection() const { return cutterData.GetSketchDirection(); }
  /// \ru Получить двумерную кривую. \en Get two-dimensional curve. 
  const MbContour *       GetSketchCurve() const { return cutterData.GetSketchCurve( 0 ); }

  /// \ru Получить поверхность. \en Get a surface. 
  const MbSurface *       GetSurface() const { return cutterData.GetSurface( 0 );  }

  /// \ru Сливать подобные грани (true)? \en Whether to merge similar faces (true)? 
        bool              MergeFaces() const { return booleanFlags.MergeFaces(); }
  /// \ru Сливать подобные ребра (true)? \en Whether to merge similar edges (true)? 
        bool              MergeEdges() const { return booleanFlags.MergeEdges(); }
  /// \ru Построить замкнутую оболочку. \en Create a closed shell.
        bool              IsCuttingAsClosed() const  { return booleanFlags.IsCutting(); }

OBVIOUS_PRIVATE_COPY ( MbShellCuttingParams )
};


//------------------------------------------------------------------------------
// \ru Установить требование по оставляемой части. \en Set retained part demand.
// ---
inline
void MbShellCuttingParams::SetRetainedPart( int part )
{
  retainedPart = ts_neutral;    // If part == 0 retain both parts 
  if ( part > 0 )               // If part > 0
    retainedPart = ts_positive; // retain a part above cutter surface.
  else if ( part < 0 )          // if part < 0
    retainedPart = ts_negative; // Retain part below cutter surface..                                             
}


//------------------------------------------------------------------------------
/** \brief \ru Параметры развёртки грани на плоскость.
           \en Parameter for an unwrapping the face on a plane. \~
  \details \ru Параметры развёртки грани на плоскость. \n
    Параметры содержат информацию о положении развёртки и свойствах материала.
           \en Parameter for an unwrapping the face on a plane. \n
    The parameters contain information about the scan position and material properties. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS RectifyValues {

protected :
  MbPlacement3D place;    ///< \ru Локальная система координат развернутой поверхности грани. \en The local coordinat system for result surface. \~
  MbCartPoint   init;     ///< \ru Параметры поверхности, которые будут соответствовать начальной точке place. \en The parameters of the surface, which will correspond to the origin of the place. \~
  MbStepData    stepData; ///< \ru Данные для вычисления шага при триангуляции. \en Data for step calculation during triangulation. \~
  double        myu;      ///< \ru Коэффициент Пуассона материала грани. \en The Poisson's ratio of face material. \~
  bool          faceted;  ///< \ru Добавить в атрибуты мозаичный объект (true) или нет (false). \en Add to the attributes a mosaic object (true), or do't. \~

public :
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров операции удаления из тела выбранных граней.
             \en Constructor of operation parameters of removing the specified faces from the solid. \~
  */
  RectifyValues()
    : place()
    , init()
    , stepData()
    , myu( 0.25 )
    , faceted( false )
  {}
  /// \ru Конструктор по способу модификации и вектору перемещения. \en Constructor by way of modification and movement vector.
  RectifyValues( const MbPlacement3D & pl, const MbCartPoint & r, const MbStepData & s, double m = 0.25, bool fset = false )
    : place( pl )
    , init( r )
    , stepData( s )
    , myu( m )
    , faceted( fset )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  RectifyValues( const RectifyValues & other )
    : place   ( other.place )
    , init    ( other.init )
    , stepData( other.stepData )
    , myu     ( other.myu )
    , faceted ( other.faceted )
  {}
  /// \ru Деструктор. \en Destructor.
  ~RectifyValues() {}
public:
  /// \ru Функция копирования. \en Copy function.
  void        Init( const RectifyValues & other ) {
    place.Init( other.place );
    init.Init( other.init );
    stepData.Init( other.stepData );
    myu     = other.myu;
    faceted = other.faceted;
  }
  /// \ru Оператор присваивания. \en Assignment operator.
  RectifyValues & operator = ( const RectifyValues & other ) {
    place.Init( other.place );
    init.Init( other.init );
    stepData.Init( other.stepData );
    myu     = other.myu;
    faceted = other.faceted;
    return *this;
  }

  // \ru Локальная система координат развернутой поверхности грани. \en The local coordinat system for result surface. \~
  void        SetPlacement( const MbPlacement3D & pl ) { place.Init( pl ); } 
  const MbPlacement3D & GetPlacement() const { return place; }
  // \ru Параметры поверхности, которые будут соответствовать начальной точке place. \en The parameters of the surface, which will correspond to the origin of the place. \~
  void        SetOrigin( const MbCartPoint & r ) { init = r; }
  const MbCartPoint & GetOrigin()    const { return init; }
  // \ru Данные для вычисления шага при триангуляции. \en Data for step calculation during triangulation. \~
  void        SetStepData( const MbStepData & step ) { stepData = step; } 
  const MbStepData & GetStepData()  const { return stepData; }
  // \ru Коэффициент Пуассона материала грани. \en The Poisson's ratio of face material. \~
  void        SetPoissonsRatio( double m ) { myu = m; }
  double      GetPoissonsRatio() const { return myu; }
  // \ru Добавить в атрибуты мозаичный объект (true) или нет (false). \en Add to the attributes a mosaic object (true), or do't. \~
  void        SetAddFacet( bool b ) { faceted = b; }
  bool        AddFacet() const { return faceted; }

  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D & matr );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D & to );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D & axis, double ang );
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const RectifyValues & other, double accuracy ) const; 

  KNOWN_OBJECTS_RW_REF_OPERATORS( RectifyValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
}; // RectifyValues


#endif // __OP_SHELL_PARAMETERS_H
