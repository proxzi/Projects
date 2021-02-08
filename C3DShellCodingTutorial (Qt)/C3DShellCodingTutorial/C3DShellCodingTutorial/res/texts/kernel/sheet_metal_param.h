////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Cтруктуры параметров для листовых операций.
         \en Structures of parameters for sheet operation. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SHEET_METAL_PARAM_H
#define __SHEET_METAL_PARAM_H


#include <templ_dptr.h>
#include <mb_vector3d.h>
#include <surface.h>
#include <cur_contour.h>
#include <name_item.h>
#include <op_shell_parameter.h>
#include <op_swept_parameter.h>
#include <templ_p_array_rw.h>

class MATH_CLASS MbFace;


//------------------------------------------------------------------------------
/** \brief \ru Способ освобождения углов.
           \en Way of freeing angles. \~
  \ingroup Build_Parameters
*/
// ---
enum MbeReleaseType {
  rt_No = 0, ///< \ru Без освобождения углов. \en Without freeing angles. 
  rt_Only,   ///< \ru Только сгиб. \en Only bend. 
  rt_Bend,   ///< \ru Сгиб и его продолжение. \en Bend and its extension. 
  rt_All,    ///< \ru Все сгибы. \en All the bends. 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры сгиба.
           \en The bend parameters. \~
  \details \ru При k = 0.0 внутренняя грань сгиба разгибается без деформаций, при k = 1.0 - внешняя.\n
    Параметр radius равен радиусу внутренней цилиндрической грани сгиба, для конического сгиба не определён.\n
    Угол сгиба angle используется при создании цилиндрических сгибов в операциях "сгиб по ребру" и "сгиб по линии".\n
    Параметр coneAngle равен 0.0 для цилиндрического сгиба и больше 0.0 для конического.\n
           \en If k=0.0, then internal face of bend is unbend without deformation, if k = 1.0 - external.\n
    The parameter "radius" is equal to radius of inner cylindrical face of bend for conic bend is undefined.\n
    Bend angle "angle" is used in the creation of cylindrical bends in the operations of "bend by an edge" and "bend by a line".\n
    The parameter coneAngle is equal to 0.0 for cylindrical bend and greater than 0.0 for conical.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbBendValues {
public:
  double k;         ///< \ru Коэффициент, определяющий положение нейтрального слоя. \en Coefficient determining the position of the neutral layer. 
  double radius;    ///< \ru Внутренний радиус сгиба. \en The internal radius of the bend. 
  double angle;     ///< \ru Угол сгиба. \en The bend angle. 
  double coneAngle; ///< \ru Угол между осью и боковой образующей конуса. \en The angle between the axis and the side of the cone. 

public:
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbBendValues() : k( 0.0 ), radius( 0.0 ), angle( 0.0 ), coneAngle( 0.0 ) {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbBendValues( double coef, double rad, double ang, double coneAng ) : 
    k        ( coef ), 
    radius   ( rad ), 
    angle    ( ang ),
    coneAngle( coneAng ) {
  }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbBendValues( const MbBendValues & other ) : 
    k        ( other.k ), 
    radius   ( other.radius ), 
    angle    ( other.angle ),
    coneAngle( other.coneAngle ) {
  }
  /// \ru Инициализировать по конкретным параметрам. \en Initialize by specific parameters. 
  void Init( double coef, double rad, double ang, double coneAng ) {
    k         = coef;
    radius    = rad;
    angle     = ang;
    coneAngle = coneAng;
  }
  /// \ru Инициализировать по другой структуре. \en Initialize by another structure. 
  void Init( const MbBendValues & other ) { 
    k         = other.k; 
    radius    = other.radius; 
    angle     = other.angle; 
    coneAngle = other.coneAngle;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  const MbBendValues & operator = ( const MbBendValues & other ) {
    k         = other.k;
    radius    = other.radius;
    angle     = other.angle;
    coneAngle = other.coneAngle;

    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbBendValues & other, double accuracy ) const {
    bool isSame = false;

    if ( ::fabs( k - other.k ) < accuracy &&
         ::fabs( radius - other.radius ) < accuracy &&
         ::fabs( angle - other.angle ) < accuracy &&
         ::fabs( coneAngle - other.coneAngle ) < accuracy )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbBendValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры построения тела из листового материала.
           \en Parameters of solid construction from sheet material. \~
  \details \ru Параметры построения тела из листового материала для операций 
    "Листовое тело", "Пластина", "Отверстие", "Вырез". \n
    Параметр thickness - это толщина листа при выдавливании незамкнутого контура.\n
    Глубина выдавливания задаётся в параметрах side1 или side2, в зависимости от направления выдавливания.
    Коэффициент нейтрального слоя k нужен для построения листового тела по незамкнутому контуру в разогнутом виде.\n
    Параметр radius - это внутренний радиус цилиндрического сгиба, который формируется в месте негладкой стыковки
    двух прямолинейных сегментов незамкнутого контура.
           \en Parameters of solid construction from sheet material for operation 
    "Sheet solid", "Plate", "Hole", "Cut". \n
    The thickness parameter - is thickness of sheet when extruded of an open contour.\n
    Depth of extrusion is given in the parameters side1 and side2 depending on the direction of extrusion.
    Coefficient of neutral layer k is necessary for construction of sheet solid by open contour in unbent state.\n
    The radius parameter - is inner radius of cylindrical bend which is formed in a non-smooth connection
    of two straight segments of open contour. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbSheetMetalValues {
public:
  double thickness;   ///< \ru Толщина. \en The thickness. 
  double k;           ///< \ru Коэффициент, определяющий положение нейтрального слоя. \en Coefficient determining the position of the neutral layer. 
  double radius;      ///< \ru Внутренний радиус сгиба. \en The internal radius of the bend. 
  MbSweptSide  side1; ///< \ru Параметры для стороны, лежащей в направлении нормали к эскизу. \en Parameters for side lying along the direction of normal to the sketch. 
  MbSweptSide  side2; ///< \ru Параметры для противоположной стороны. \en Parameters for the opposite side. 

public:
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbSheetMetalValues() : thickness( 0.0 ), k( 0.0 ), radius( 0.0 ), side1(), side2() {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbSheetMetalValues( const MbSheetMetalValues &other ) : thickness( other.thickness ), k( other.k ), radius( other.radius ),
                                                          side1( other.side1 ), side2( other.side2 ) {}
  /// \ru Оператор присваивания. \en Assignment operator. 
  MbSheetMetalValues & operator = ( const MbSheetMetalValues &other ) {
    thickness = other.thickness;
    k = other.k;
    radius = other.radius;
    side1 = other.side1;
    side2 = other.side2;

    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbSheetMetalValues & other, double accuracy ) const {
    bool isSame = false;
    
    if ( ::fabs( thickness - other.thickness ) < accuracy &&
         ::fabs( k - other.k ) < accuracy &&
         ::fabs( radius - other.radius ) < accuracy &&
         side1.IsSame( other.side1, accuracy ) &&
         side2.IsSame( other.side2, accuracy ) )
      isSame = true;

    return isSame;
  }

  /** \ru \name Функции работы с поверхностями, до которых выдавливать.
      \en \name Functions for working with surfaces to which extrude.
      \{ */
  /// \ru Получить ограничивающую поверхность в направлении нормали. \en Get bounding surface in direction of normal. 
  MbSurface * GetSurface1() const { return side1.GetSurface(); }
  /// \ru Получить ограничивающую поверхность в противоположном направлении. \en Get bounding surface along the opposite direction. 
  MbSurface * GetSurface2() const { return side2.GetSurface(); }

  /// \ru Установить ограничивающую поверхность в направлении нормали. \en Set bounding surface along the direction of normal. 
  void SetSurface1( MbSurface *s ) { side1.SetSurface( s ); }
  /// \ru Установить ограничивающую поверхность в противоположном направлении. \en Set bounding surface along the opposite direction. 
  void SetSurface2( MbSurface *s ) { side2.SetSurface( s ); }
  /// \ru Поменять местами ограничивающие выдавливание поверхности. \en Swap bounding extrusions of surfaces. 
  void ExchangeSurfaces() {
    MbSurface *s = side1.GetSurface();
    MbSweptWay w = side1.way;
    double d = side1.distance;
    if (s!=NULL)
      s->AddRef();
    side1.SetSurface( side2.GetSurface() );
    side1.way = side2.way;
    side1.distance = side2.distance;
    side2.SetSurface( s );
    side2.way = w;
    side2.distance = d;
    if (s!=NULL)
      s->DecRef();
  }
  /** \} */

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbSheetMetalValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры разгрузки сгиба.
           \en The parameters of stress relieving of bending. \~
  \details \ru Разгрузка сгиба - это вырезы в базовом листе по обе стороны от места крепления сгиба. \n
    Радиус скругления разгрузки задаёт скругление углов этого выреза, находящихся внутри базового листа.\n
           \en Unloading of bend - is cuts in the base sheet on both sides of attachment points of bend. \n
    Fillet radius of unloading sets fillet of angles of this cut located inside base sheet.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbSlotValues {
public:
  double width;  ///< \ru Ширина  разгрузки сгиба. \en The width of bend unloading. 
  double depth;  ///< \ru Глубина разгрузки сгиба. \en The depth of bend unloading. 
  double radius; ///< \ru Радиус скругления разгрузки. \en The fillet radius of unloading. 

public:
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbSlotValues() : width( 0 ), depth( 0 ), radius( 0 ) {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbSlotValues( double w, double d, double r ) : width( w ), depth( d ), radius( r ) {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbSlotValues( const MbSlotValues &other ) : 
    width ( other.width ), 
    depth ( other.depth ), 
    radius( other.radius ) 
  {}
  /// \ru Инициализировать по конкретным параметрам \en Initialize by specific parameters 
  void    Init( double w, double d, double r ) {
    width  = w; 
    depth  = d; 
    radius = r;
  }
  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void    Init( const MbSlotValues &other ) { 
    width  = other.width; 
    depth  = other.depth; 
    radius = other.radius;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  const MbSlotValues & operator = ( const MbSlotValues &other ) {
    width  = other.width; 
    depth  = other.depth; 
    radius = other.radius;

    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbSlotValues & other, double accuracy ) const {
    bool isSame = false;

    if ( ::fabs( width - other.width ) < accuracy &&
         ::fabs( depth - other.depth ) < accuracy &&
         ::fabs( radius - other.radius ) < accuracy )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbSlotValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры построения сгиба по линии для операции "Сгиб по линии".
           \en The parameter of bend construction by line for operation "Bend by a line". \~
  \details \ru Смещение сгиба определяет величину отступа начала сгиба от прямолинейного эскиза
    в одну или другую сторону вдоль сгибаемой поверхности в зависимости от знака.\n
    Параметр leftFixed определяет с какой стороны от прямолинейного эскиза будет лежать несгибаемая часть листа.\n
           \en Displacement of bending determines value of indent of beginning of bend from a straight sketch
    to one side or other along a bendable surface depending on the sign. \n
    LeftFixed parameter determines which side of the straight sketch will lie unbendable part of the sheet.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbBendOverSegValues : public MbBendValues {
public:
  double         displacement; ///< \ru Смещение сгиба. \en The displacement of bending. 
  bool           leftFixed;    ///< \ru Неподвижная часть грани. \en The fixed part of face. 
  MbeReleaseType type;         ///< \ru Способ освобождения углов. \en Way of freeing angles. 

public:
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbBendOverSegValues() : MbBendValues(), displacement( 0.0 ), leftFixed( true ), type( rt_No ) {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbBendOverSegValues( double coef, double rad, double ang, double coneAng, double displ, bool left, MbeReleaseType tp ) :
    MbBendValues( coef, rad, ang, coneAng ),
    displacement( displ ),
    leftFixed( left ),
    type( tp )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbBendOverSegValues( const MbBendOverSegValues &other ) :
    MbBendValues( other ),
    displacement( other.displacement ),
    leftFixed( other.leftFixed ),
    type( other.type )
  {}
  /// \ru Инициализировать по конкретным параметрам. \en Initialize by specific parameters. 
  void    Init( double coef, double rad, double ang, double coneAng, double displ, bool left, MbeReleaseType tp ) {
    MbBendValues::Init( coef, rad, ang, coneAng );
    displacement = displ;
    leftFixed = left;
    type = tp;
  }
  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void    Init( const MbBendOverSegValues &other ) {
    MbBendValues::Init( other );
    displacement = other.displacement;
    leftFixed = other.leftFixed;
    type = other.type;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  MbBendOverSegValues & operator = ( const MbBendOverSegValues &other ) {
    MbBendValues::Init( other );
    displacement = other.displacement;
    leftFixed = other.leftFixed;
    type = other.type;
    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbBendOverSegValues & other, double accuracy ) const {
    bool isSame = false;

    if ( leftFixed == other.leftFixed &&
         type == other.type &&
         ::fabs( displacement - other.displacement ) < accuracy &&
         MbBendValues::IsSame( other, accuracy ) )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbBendOverSegValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры для операции "подсечка".
           \en The parameters for operation "undercutting". \~
  \details \ru Высота подсечки - это расстояние от неподвижной части сгибаемой поверхности до её подвижной части после выполнения операции.\n
    При включенном режиме добавления материала подсечка выполняется методом штамповки
    листа с неизменной длиной проекции детали на плоскость неподвижной грани.
    В разогнутом состоянии такая деталь будет тем длиннее, чем больше высота подсечки.
    При выключенном режиме добавления материала подсечка выполняется двумя сгибами,
    и соответственно проекция детали на плоскость неподвижной грани укорачивается.
    Параметр byInnerSide влияет на способ добавления материала.
           \en Height of undercutting - is distance from fixed part of unbendable surface to its movable part after operation.\n
    If the addition mode of material is enabled, then undercutting is performed by method of stamping 
    of sheet with a constant length of the part projection on the plane of the fixed face.
    In unbent state this detail will be longer as the greater height of undercutting.
    If the addition mode of material isn't enabled, then undercutting is performed by two methods, 
    and accordingly the detail projection on the plane of fixed face is shortened.
    The byInnerSide parameter affects the way of adding material. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbJogValues : public MbBendOverSegValues {
  double elevation;   ///< \ru Высота подсечки. \en A jog height. 
  bool   addMaterial; ///< \ru Вкл./откл. режим добавления материала. \en On/off mode of material adding. 
  bool   byInnerSide; ///< \ru Линия подсечки находится внутри/снаружи первого сгиба. \en Jog line is inside/outside of the first bend. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbJogValues() : MbBendOverSegValues(), elevation( 0.0 ), addMaterial( true ), byInnerSide( true ) {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbJogValues( double coef, double rad, double ang, double displ, bool left, MbeReleaseType tp, double elev, bool addMat, bool byInner ) :
    MbBendOverSegValues( coef, rad, ang, 0.0/*coneAng*/, displ, left, tp ),
    elevation( elev ),
    addMaterial( addMat ),
    byInnerSide( byInner )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbJogValues( const MbJogValues &other ) :
    MbBendOverSegValues( other ),
    elevation( other.elevation ),
    addMaterial( other.addMaterial ),
    byInnerSide( other.byInnerSide )
  {}
  /// \ru Инициализировать по конкретным параметрам. \en Initialize by specific parameters. 
  void Init( double coef, double rad, double ang, double displ, bool left, MbeReleaseType tp, double elev, bool addMat, bool byInner ) {
    MbBendOverSegValues::Init( coef, rad, ang, 0.0/*coneAng*/, displ, left, tp );
    elevation = elev;
    addMaterial = addMat;
    byInnerSide = byInner;
  }
  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void Init( const MbJogValues &other ) {
    MbBendOverSegValues::Init( other );
    elevation = other.elevation;
    addMaterial = other.addMaterial;
    byInnerSide = other.byInnerSide;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  MbJogValues & operator = ( const MbJogValues &other ) {
    MbBendOverSegValues::Init( other );
    elevation = other.elevation;
    addMaterial = other.addMaterial;
    byInnerSide = other.byInnerSide;
    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbJogValues & other, double accuracy ) const {
    bool isSame = false;

    if ( addMaterial == other.addMaterial &&
         byInnerSide == other.byInnerSide &&
         ::fabs( elevation - other.elevation ) < accuracy &&
         MbBendOverSegValues::IsSame( other, accuracy ) )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbJogValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры замыкания сгиба.
           \en The bend closure parameters. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbClosedCornerValues {
  /** \brief \ru Cпособ построения.
             \en Way of construction. \~
    \ingroup Build_Parameters
  */
  enum MbeCloseCornerWay {
    ccRip,     ///< \ru Замыкание встык. \en Closing butt. 
    ccOverlap, ///< \ru Замыкание с перекрытием. \en Closing with overlapping. 
    ccTight    ///< \ru Плотное замыкание. \en Dense closure. 
  };

  /** \brief \ru Обработка углов.
             \en Processing of angles. \~
    \ingroup Build_Parameters
  */
  enum MbeCloseBendsWay {
    cbNone,   ///< \ru Без обработки. \en Without processing.
    cbChord,  ///< \ru По хорде. \en By chord. 
    cbEdge,   ///< \ru По кромке. \en By fillet. 
    cbCircle  ///< \ru Круговая обработка. \en Circular processing.
  };

  /** \brief \ru Размещение отверстия (при круговой обработке углов).
             \en Disposition of the circle (for circular processing of angles). \~
    \ingroup Build_Parameters
  */
  enum MbeCloseBendsCirclePos {
    cpBend,  ///< \ru По центру сгиба. \en At bends center.
    cpAngle, ///< \ru По точке угла. \en At angle point.
    cpPoint  ///< \ru Через точку угла. \en Through angle point.
  };

  MbeCloseCornerWay              cornerWay;  ///< \ru Способ построения. \en Way of construction. 
  std::vector<MbeCloseBendsWay>  bendsWay;   ///< \ru Обработка углов. \en Processing of angles. 
  MbeCloseBendsCirclePos         circlePos;  ///< \ru Размещение отверстия (при круговой обработке углов). \en Disposition of the circle (for circular processing of angles).
  double                         gap;        ///< \ru Зазор. \en Gap.
  double                         diameter;   ///< \ru Диаметр отверстия (при круговой обработке углов). \en Diameter of the circle (for circular processing of angles).
  double                         shift;      ///< \ru Сдвиг отверстия (при круговой обработке углов). \en Shift of the circle (for circular processing of angles).
  double                         kPlus;      ///< \ru Коэффициент нейтрального слоя для сгиба, лежащего слева от ребра. \en Neutral layer coefficient for bend lying on the left of the edge. 
  double                         kMinus;     ///< \ru Коэффициент нейтрального слоя для сгиба, лежащего справа от ребра. \en Neutral layer coefficient for bend lying on the right of the edge. 
  double                         angle;      ///< \ru Угол замыкания для обработки только с одной стороны. \en Closure angle for processing only one side. 
  bool                           plus;       ///< \ru Перекрывающая часть находится слева от общего ребра (для способа ccOverlap). \en Overlapping part is on the left side of the common edge (for the method ccOverlap). 
  bool                           prolong;    ///< \ru С продолжением. \en With continuation. 
  bool                           acrossBend; ///< \ru Замыкание через сгиб (для замыкания с одной стороны). \en Closure by bend (for closing on one side). 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbClosedCornerValues()
    : cornerWay( ccRip ), bendsWay(), circlePos( cpBend ), gap( 0.0 ), diameter( 0.0 ), shift( 0.0 ), kPlus( 0.5 ), kMinus( 0.5 ),
      angle( M_PI_2 ), plus( true ), prolong( false ), acrossBend( false ) {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbClosedCornerValues( MbeCloseCornerWay cc, MbeCloseBendsWay cb, MbeCloseBendsCirclePos cp, double g, double dm, double sh,
                        double kP, double kM, double ang, bool pl, bool pr, bool ab )
    : cornerWay( cc ), bendsWay(), circlePos( cp ), gap( g ), diameter( dm ), shift( sh ), 
      kPlus( kP ), kMinus( kM ), angle( ang ), plus( pl ), prolong( pr ), acrossBend( ab ) { bendsWay.clear(); bendsWay.push_back(cb); }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbClosedCornerValues( const MbClosedCornerValues &other )
    : cornerWay( other.cornerWay ), bendsWay( other.bendsWay ), circlePos( other.circlePos ),
      gap( other.gap ), diameter( other.diameter ), shift( other.shift ),
      kPlus( other.kPlus ), kMinus( other.kMinus ), angle( other.angle),
      plus( other.plus ), prolong( other.prolong ), acrossBend( other.acrossBend ) {}

  /// \ru Инициализировать по конкретным параметрам. \en Initialize by specific parameters. 
  void Init( MbeCloseCornerWay cc, MbeCloseBendsWay cb, MbeCloseBendsCirclePos cp, double g, double dm, double sh,
             double kP, double kM, double ang, bool pl, bool pr, bool ab ) {
    cornerWay  = cc;
    bendsWay.clear();
    bendsWay.push_back( cb );
    circlePos  = cp;
    gap        = g;
    diameter   = dm;
    shift      = sh;
    kPlus      = kP;
    kMinus     = kM;
    angle      = ang;
    plus       = pl;
    prolong    = pr;
    acrossBend = ab;
  }

  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void Init( const MbClosedCornerValues &other ) {
    cornerWay  = other.cornerWay;
    bendsWay   = other.bendsWay;
    circlePos  = other.circlePos;
    gap        = other.gap;
    diameter   = other.diameter;
    shift      = other.shift;
    kPlus      = other.kPlus;
    kMinus     = other.kMinus;
    angle      = other.angle;
    plus       = other.plus;
    prolong    = other.prolong;
    acrossBend = other.acrossBend;
  }

  /// \ru Оператор присваивания. \en Assignment operator. 
  MbClosedCornerValues & operator = ( const MbClosedCornerValues &other ) { Init( other ); return *this; }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbClosedCornerValues & other, double accuracy ) const {
    bool isSame = false;

    if ( plus       == other.plus &&
         prolong    == other.prolong &&
         acrossBend == other.acrossBend &&
         cornerWay  == other.cornerWay &&
         circlePos  == other.circlePos &&
         ::fabs( gap - other.gap ) < accuracy &&
         ::fabs( diameter - other.diameter ) < accuracy &&
         ::fabs( shift - other.shift ) < accuracy &&
         ::fabs( kPlus - other.kPlus ) < accuracy &&
         ::fabs( kMinus - other.kMinus ) < accuracy &&
         ::fabs( angle - other.angle ) < accuracy &&
         bendsWay   == other.bendsWay )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbClosedCornerValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры замыкания сгиба с флагом выполнения.
           \en The bend closure parameters with the performing closure flag. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbMiterValues : public MbClosedCornerValues {
  bool allow; ///< \ru Флаг выполнения замыкания. \en Flag of performing closure. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbMiterValues() : MbClosedCornerValues(), allow( false ) {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbMiterValues( MbeCloseCornerWay cc, MbeCloseBendsWay cb, MbeCloseBendsCirclePos cp, double g, double dm, double sh, 
                 double kP, double kM, double ang, bool pl, bool pr, bool al, bool ab )
    : MbClosedCornerValues( cc, cb, cp, g, dm, sh, kP, kM, ang, pl, pr, ab ), allow( al ) {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbMiterValues( const MbMiterValues & other )
    : MbClosedCornerValues( other ), allow( other.allow ) {}
  /// \ru Инициализировать по конкретным параметрам. \en Initialize by specific parameters. 
  void Init( MbeCloseCornerWay cc, MbeCloseBendsWay cb, MbeCloseBendsCirclePos cp, double g, double dm, double sh, 
             double kP, double kM, double ang, bool pl, bool pr, bool al, bool ab ) {
    MbClosedCornerValues::Init( cc, cb, cp, g, dm, sh, kP, kM, ang, pl, pr, ab );
    allow = al;
  }
  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void Init ( const MbMiterValues & other ) {
    MbClosedCornerValues::Init( other );
    allow = other.allow;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  MbMiterValues & operator = ( const MbMiterValues & other ) { Init( other ); return *this; }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbMiterValues & other, double accuracy ) const {
    bool isSame = false;

    if ( allow  == other.allow &&
         MbClosedCornerValues::IsSame( other, accuracy ) )
      isSame = true;

    return isSame;
  }
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры построения сгиба для операции "Сгиб по ребру".
           \en The parameter of bend construction for operation "Bend by an edge". \~
  \details \ru Положительные значения увеличивают "тело" сгиба.\n
           \en Positive values increase the "solid" of bend.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbBendByEdgeValues : public MbBendValues {
public:
  /** \brief \ru Параметры одного края сгиба.
             \en Parameters of one boundary of bend. \~
    \details \ru Положительные значения увеличивают "тело" сгиба.
             \en Positive values increase the "solid" of bend. \~
    \ingroup Build_Parameters
  */
  struct MATH_CLASS MbSide {
    public: 
      double distance;  ///< \ru Отступ от края ребра. \en Distance from boundary of edge. 
      double angle;     ///< \ru Угол уклона края сгиба. \en Draft angle of bend boundary. 
      double deviation; ///< \ru Угол уклона продолжения (плоской части) сгиба. \en Draft angle of bend extension (the planar part). 
      double widening;  ///< \ru Расширение  продолжения (плоской части) сгиба. \en Expanding of bend extension (the planar part). 
      double length;    ///< \ru Длина продолжения (плоской части) сгиба. \en Length of bend extension (the planar part). 

    public:
      /// \ru Конструктор по умолчанию. \en Default constructor. 
      MbSide() : distance( 0 ), angle( 0 ), deviation( 0 ), widening( 0 ), length ( 0 ) {}
      /// \ru Конструктор по длине продолжения. \en Default by length of extension. 
      MbSide( double len ) : distance( 0 ), angle( 0 ), deviation( 0 ), widening( 0 ), length ( len ) {}
      /// \ru Конструктор копирования. \en Copy-constructor. 
      MbSide( const MbSide &other ) : 
        distance( other.distance ), angle( other.angle ), deviation( other.deviation ), widening( other.widening ), length ( other.length ) 
      {}
      /// \ru Инициализировать по конкретным параметрам. \en Initialize by specific parameters. 
      void    Init( double dis, double a, double dev, double w, double l ) {
         distance = dis; angle = a; deviation = dev; widening = w; length = l;
      }
      /// \ru Оператор присваивания. \en Assignment operator. 
      const MbSide & operator = ( const MbSide &other ) {
        distance  = other.distance;
        angle     = other.angle;
        deviation = other.deviation;
        widening  = other.widening;
        length    = other.length;

        return *this;
      }
      
      ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
      bool IsSame( const MbSide & other, double accuracy ) const {
        bool isSame = false;

        if ( ::fabs( distance - other.distance ) < accuracy &&
             ::fabs( angle - other.angle ) < accuracy &&
             ::fabs( deviation - other.deviation ) < accuracy &&
             ::fabs( widening - other.widening ) < accuracy &&
             ::fabs( length - other.length ) < accuracy )
          isSame = true;

        return isSame;
      }
  }; // \ru Параметры одного края сгиба \en Parameters of one boundary of bend 

public:
  double         deepness;    ///< \ru Смещение сгиба (расстояние от ребра до начала сгиба). \en Displacement of bend (the distance from the edge to the start of the bend). 
  MbSide         sideLeft;    ///< \ru Параметры левого  края сгиба. \en Parameters of the left boundary of bend. 
  MbSide         sideRight;   ///< \ru Параметры правого края сгиба. \en Parameters of the first boundary of bend. 
  MbMiterValues  miterBegin;  ///< \ru Параметры края в начале. \en The parameters of boundary at the beginning. 
  MbMiterValues  miterEnd;    ///< \ru Параметры края в конце. \en The parameters of boundary at the end. 
  MbMiterValues  miterMiddle; ///< \ru Параметры замыкания углов. \en The enclosure parameters of angles. 
  MbSlotValues   slot;        ///< \ru Разгрузкa сгиба. \en Bend unloading. 
  MbeReleaseType type;        ///< \ru Способ освобождения углов. \en Way of freeing angles. 

public:
  /// \ru Конструктор по-умолчанию. \en Default constructor. 
  MbBendByEdgeValues() : MbBendValues(), deepness( 0 ), sideLeft(), sideRight(), miterBegin(), miterEnd(), miterMiddle(), slot(), type( rt_No ) {}
  /// \ru Конструктор по конкретным параметрам (правая и левая стороены края продолжения одной длины). \en Constructor by specific parameters. 
  MbBendByEdgeValues( double coef, double rad, double ang, double coneAng, double len, double d, MbeReleaseType tp ) : 
    MbBendValues( coef, rad, ang, coneAng ), 
    deepness   ( d ),
    sideLeft   ( len ),
    sideRight  ( len ),
    miterBegin (),
    miterEnd   (),
    miterMiddle(),
    slot       (),
    type       ( tp ) {
  }
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbBendByEdgeValues( double coef, double rad, double ang, double coneAng, double lenL, double lenR, double d, MbeReleaseType tp ) : 
    MbBendValues( coef, rad, ang, coneAng ), 
    deepness   ( d ),
    sideLeft   ( lenL ),
    sideRight  ( lenR ),
    miterBegin (),
    miterEnd   (),
    miterMiddle(),
    slot       (),
    type       ( tp ) {
  }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbBendByEdgeValues( const MbBendByEdgeValues &other ) :
    MbBendValues( other ),
    deepness   ( other.deepness ),
    sideLeft   ( other.sideLeft ),
    sideRight  ( other.sideRight ),
    miterBegin ( other.miterBegin ),
    miterEnd   ( other.miterEnd ),
    miterMiddle( other.miterMiddle ),
    slot       ( other.slot ),
    type       ( other.type ) {
  }
  /// \ru Инициализировать параметры сгиба. \en Initialize the parameters of bend. 
  void    SheetMetalInit( double coef, double rad, double ang, double coneAng ) {
    MbBendValues::Init( coef, rad, ang, coneAng );
  }
  /// \ru Инициализировать длину, смещение и тип освобождения сгиба. \en Initialize the length, shift and type of freeing bend. 
  void    BendInit( double len, double d, MbeReleaseType tp ) {
    sideLeft.length = len;
    sideRight.length = len;

    deepness = d;
    type = tp;
  }
  /// \ru Инициализировать левую сторону сгиба. \en Initialize the left side of bend. 
  void    SideLeftInit( double dis, double a, double dev, double w ) {
    sideLeft.Init( dis, a, dev, w, sideLeft.length );
  }
  /// \ru Инициализировать правую сторону сгиба. \en Initialize the first side of bend. 
  void    SideRightInit( double dis, double a, double dev, double w ) {
    sideRight.Init( dis, a, dev, w, sideRight.length );
  }
  /// \ru Инициализировать левую сторону сгиба. \en Initialize the left side of bend. 
  void    SideLeftInit( double dis, double a, double dev, double w, double l ) {
    sideLeft.Init( dis, a, dev, w, l );
  }
  /// \ru Инициализировать правую сторону сгиба. \en Initialize the first side of bend. 
  void    SideRightInit( double dis, double a, double dev, double w, double l ) {
    sideRight.Init( dis, a, dev, w, l );
  }
  /// \ru Инициализировать параметры разгрузки сгиба. \en Initialize the parameters of bend unloading. 
  void    SlotInit( double w, double d, double r ) {
    slot.Init( w, d, r );
  }
  /// \ru Инициализировать замыкание угла в начале цепочки рёбер. \en Initialize corner closing at the beginning of the chain of edges. 
  void MiterBeginInit( MbClosedCornerValues::MbeCloseCornerWay cc, MbClosedCornerValues::MbeCloseBendsWay cb, MbClosedCornerValues::MbeCloseBendsCirclePos cp, double g, double dm, double sh, 
                       double kP, double kM, double ang, bool pl, bool pr, bool al, bool ab ) {
    miterBegin.Init( cc, cb, cp, g, dm, sh, kP, kM, ang, pl, pr, al, ab );
  }
  /// \ru Инициализировать замыкание угла в конце цепочки рёбер. \en Initialize corner closing at the end of the chain of edges. 
  void MiterEndInit( MbClosedCornerValues::MbeCloseCornerWay cc, MbClosedCornerValues::MbeCloseBendsWay cb, MbClosedCornerValues::MbeCloseBendsCirclePos cp, double g, double dm, double sh, 
                       double kP, double kM, double ang, bool pl, bool pr, bool al, bool ab ) {
    miterEnd.Init( cc, cb, cp, g, dm, sh, kP, kM, ang, pl, pr, al, ab );
  }
  /// \ru Инициализировать замыкание угла в середине цепочки рёбер. \en Initialize corner closing in the middle of the chain of edges. 
  void MiterMiddleInit( MbClosedCornerValues::MbeCloseCornerWay cc, MbClosedCornerValues::MbeCloseBendsWay cb, MbClosedCornerValues::MbeCloseBendsCirclePos cp, double g, double dm, double sh, 
                       double kP, double kM, double ang, bool pl, bool pr, bool al, bool ab ) {
    miterMiddle.Init( cc, cb, cp, g, dm, sh, kP, kM, ang, pl, pr, al, ab );
  }
  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void    Init( const MbBendByEdgeValues &other ) {
    MbBendValues::Init( other ); 
    deepness    = other.deepness; 
    sideLeft    = other.sideLeft; 
    sideRight   = other.sideRight; 
    miterBegin  = other.miterBegin;
    miterEnd    = other.miterEnd;
    miterMiddle = other.miterMiddle;
    slot        = other.slot; 
    type        = other.type;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  const MbBendByEdgeValues & operator = ( const MbBendByEdgeValues &other ) {
    MbBendValues::Init( other ); 
    deepness    = other.deepness; 
    sideLeft    = other.sideLeft;
    sideRight   = other.sideRight;
    miterBegin  = other.miterBegin;
    miterEnd    = other.miterEnd;
    miterMiddle = other.miterMiddle;
    slot        = other.slot;
    type        = other.type;

    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbBendByEdgeValues & other, double accuracy ) const {
    bool isSame = false;

    if ( type == other.type &&
         MbBendValues::IsSame( other, accuracy ) &&
         ::fabs( deepness - other.deepness ) < accuracy &&
         sideLeft.IsSame( other.sideLeft, accuracy ) &&
         sideRight.IsSame( other.sideRight, accuracy ) &&
         miterBegin.IsSame( other.miterBegin, accuracy ) &&
         miterEnd.IsSame( other.miterEnd, accuracy ) &&
         miterMiddle.IsSame( other.miterMiddle, accuracy ) &&
         slot.IsSame( other.slot, accuracy ) )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbBendByEdgeValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры комбинированного сгиба.
           \en The parameters of combined bend. \~
  \details \ru Параметры комбинированного сгиба (сгиба по эскизу). \n
    Положительные значения параметров distanceBegin и distanceEnd увеличивают "тело" сгиба, а отрицательные - уменьшают.\n
           \en The parameters of combined bend (bend by sketch). \n
    Positive values of parameters distanceBegin and distanceEnd increase the "solid" of bend and negative - decrease.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbJointBendValues : public MbBendValues {
  double         distanceBegin; ///< \ru Отступ от начала ориентированного ребра, принадлежащего листовой грани. \en Distance from beginning of the oriented edge owned sheet face. 
  double         distanceEnd;   ///< \ru Отступ от конца ориентированного ребра, принадлежащего листовой грани. \en Distance from end of the oriented edge owned sheet face. 
  MbMiterValues  miterBegin;    ///< \ru Параметры края в начале. \en The parameters of boundary at the beginning. 
  MbMiterValues  miterEnd;      ///< \ru Параметры края в конце. \en The parameters of boundary at the end. 
  MbMiterValues  miterMiddle;   ///< \ru Параметры замыкания углов. \en The enclosure parameters of angles. 
  MbSlotValues   slotValues;    ///< \ru Разгрузкa сгиба. \en Bend unloading. 
  MbeReleaseType releaseType;   ///< \ru Способ освобождения углов. \en Way of freeing angles. 

  /// \ru Конструктор по-умолчанию. \en Default constructor. 
  MbJointBendValues()
    : MbBendValues (),
      distanceBegin( 0.0 ),
      distanceEnd  ( 0.0 ),
      miterBegin   (),
      miterEnd     (),
      miterMiddle  (),
      slotValues   (),
      releaseType  ( rt_No ) {
  }
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbJointBendValues( double coef, double bendRad, double distBeg, double distEnd, bool plus,
                     MbClosedCornerValues::MbeCloseCornerWay ccb, MbClosedCornerValues::MbeCloseBendsWay cbb, MbClosedCornerValues::MbeCloseBendsCirclePos cpb,
                     double gapb, double dmb, double shb, double angb, bool alb, bool abb,
                     MbClosedCornerValues::MbeCloseCornerWay cce, MbClosedCornerValues::MbeCloseBendsWay cbe, MbClosedCornerValues::MbeCloseBendsCirclePos cpe,
                     double gape, double dme, double she, double ange, bool ale, bool abe,
                     MbClosedCornerValues::MbeCloseCornerWay ccm, MbClosedCornerValues::MbeCloseBendsWay cbm, MbClosedCornerValues::MbeCloseBendsCirclePos cpm,
                     double gapm, double dmm, double shm, bool alm,
                     double width, double depth, double relRad, MbeReleaseType rt )
    : MbBendValues ( coef, bendRad, 0.0/*angle*/, 0.0/*coneAng*/ ),
      distanceBegin( distBeg ),
      distanceEnd  ( distEnd ),
      miterBegin   ( ccb, cbb, cpb, gapb, dmb, shb, coef, coef, angb, plus, true/*prolong*/, alb, abb ),
      miterEnd     ( cce, cbe, cpe, gape, dme, she, coef, coef, ange, plus, true/*prolong*/, ale, abe ),
      miterMiddle  ( ccm, cbm, cpm, gapm, dmm, shm, coef, coef, 0.0,  plus, true/*prolong*/, alm, false/*acrossBend*/ ),
      slotValues   ( width, depth, relRad ),
      releaseType  ( rt ) {
  }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbJointBendValues( const MbJointBendValues & other )
    : MbBendValues ( other ),
      distanceBegin( other.distanceBegin ),
      distanceEnd  ( other.distanceEnd   ),
      miterBegin   ( other.miterBegin    ),
      miterEnd     ( other.miterEnd      ),
      miterMiddle  ( other.miterMiddle   ),
      slotValues   ( other.slotValues    ),
      releaseType  ( other.releaseType   ) {
  }
  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void Init( const MbJointBendValues & other ) {
    MbBendValues::Init( other );
    distanceBegin = other.distanceBegin;
    distanceEnd   = other.distanceEnd;
    miterBegin    = other.miterBegin;
    miterEnd      = other.miterEnd;
    miterMiddle   = other.miterMiddle;
    slotValues    = other.slotValues;
    releaseType   = other.releaseType;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  MbJointBendValues & operator = ( const MbJointBendValues & other ) {
    Init( other );
    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbJointBendValues & other, double accuracy ) const {
    bool isSame = false;

    if ( releaseType == other.releaseType &&
         MbBendValues::IsSame( other, accuracy ) &&
         ::fabs( distanceBegin - other.distanceBegin ) < accuracy &&
         ::fabs( distanceEnd - other.distanceEnd ) < accuracy &&
         miterBegin.IsSame( other.miterBegin, accuracy ) &&
         miterEnd.IsSame( other.miterEnd, accuracy ) &&
         miterMiddle.IsSame( other.miterMiddle, accuracy ) &&
         slotValues.IsSame( other.slotValues, accuracy ) )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbJointBendValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры штамповки.
           \en The parameters of stamping. \~
  \details \ru Эскиз штамповки задаёт конфигурацию её донышка. Штамповка строится по замкнутому или незамкнутому контуру.
    Замкнутый контур может целиком лежать внутри листовой грани, а может частично выходить за её пределы.
    Оба конца незамкнутого контура обязаны лежать за пределами штампуемой листовой грани.\n
    В зависимости от параметра wallInside боковые стенки штамповки располагаются внутри или снаружи от эскиза.\n
    Высота штамповки - это расстояние от плоскости листа до соответствующей ей выдавленной части штамповки.\n
    Параметр angle - это угол отклонения боковых стенок штамповки от вертикали в радианах.\n
    Параметр leftFixed указывает сторону эскиза, которая будет выштамповываться, а reverse - направление штамповки - по нормали к плоской грани или против.\n
    В случае открытой штамповки лист пробивается насквозь.\n
           \en Sketch of stamping sets the configuration of its bottom. Stamping is constructed by open or closed contour.
    Closed closed can lie entirely inside sheet face and can partially go out of its bounds.
    Both ends of open contour must lie outside of the stamped sheet face.\n
    Depending on the parameter wallInside the stamping sidewalls are located inside or outside from sketch.\n
    Height of stamping - is distance from plane of sheet to corresponding extruded part of stamping.\n
    The angle parameter - is the angle of sidewalls deviation of stamping from the vertical in radians.\n
    The leftFixed parameter indicates the side of the sketch which will be stamped and "reverse" - the direction of stamping along the normal to the planar face or along opposite to the normal. \n
    If stamping is open, then sheet makes its way through and through.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbStampingValues {
  double hight;              ///< \ru Высота штамповки. \en Stamping height. 
  double angle;              ///< \ru Угол наклона боковых стенок штамповки. \en Slope angle of stamping sidewalls. 
  double sketchFilletRadius; ///< \ru Радиус скругления эскиза (отрицательное значение запрещает скругление). \en Fillet radius of sketch (negative value prohibits fillet). 
  double baseFilletRadius;   ///< \ru Радиус скругления основания (отрицательное значение запрещает скругление). \en Fillet radius of base (negative value prohibits fillet). 
  double bottomFilletRadius; ///< \ru Радиус скругления дна (отрицательное значение запрещает скругление). \en Fillet radius of bottom (negative value prohibits fillet). 
  bool   wallInside;         ///< \ru Боковая стенка внутри. \en The sidewall is inside. 
  bool   leftFixed;          ///< \ru Изменяется геометрия справа от эскиза. \en Geometry changes to the right of the sketch. 
  bool   reverse;            ///< \ru Направление построения штамповки. \en Direction of stamping construction. 
  bool   open;               ///< \ru Открытая штамповка. \en Open stamping. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbStampingValues() :
    hight             ( 0.0 ),
    angle             ( 0.0 ),
    sketchFilletRadius( 0.0 ),
    baseFilletRadius  ( 0.0 ),
    bottomFilletRadius( 0.0 ),
    wallInside        ( true  ),
    leftFixed         ( true  ),
    reverse           ( false ),
    open              ( true  ) {
  }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbStampingValues( const MbStampingValues &other ) :
    hight             ( other.hight ),
    angle             ( other.angle ),
    sketchFilletRadius( other.sketchFilletRadius ),
    baseFilletRadius  ( other.baseFilletRadius ),
    bottomFilletRadius( other.bottomFilletRadius ),
    wallInside        ( other.wallInside ),
    leftFixed         ( other.leftFixed ),
    reverse           ( other.reverse ),
    open              ( other.open ) {
  }
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbStampingValues( double h, double ang, double sketchRad, double baseRad, double bottomRad,
                    bool inside, bool left, bool rev, bool op ) :
    hight             ( h ),
    angle             ( ang ),
    sketchFilletRadius( sketchRad ),
    baseFilletRadius  ( baseRad ),
    bottomFilletRadius( bottomRad ),
    wallInside        ( inside ),
    leftFixed         ( left ),
    reverse           ( rev ),
    open              ( op ) {
  }

  /// \ru Оператор присваивания. \en Assignment operator. 
  MbStampingValues & operator = ( const MbStampingValues &other ) { Init( other ); return *this; }
  /// \ru Инициализация по другому объекту. \en Initialization by another object. 
  void Init( const MbStampingValues &other ) {
    hight              = other.hight;
    angle              = other.angle;
    sketchFilletRadius = other.sketchFilletRadius;
    baseFilletRadius   = other.baseFilletRadius;
    bottomFilletRadius = other.bottomFilletRadius;
    wallInside         = other.wallInside;
    leftFixed          = other.leftFixed;
    reverse            = other.reverse;
    open               = other.open;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbStampingValues & other, double accuracy ) const {
    bool isSame = false;

    if ( wallInside == other.wallInside &&
         leftFixed == other.leftFixed &&
         reverse == other.reverse &&
         open == other.open &&
         ::fabs( hight - other.hight ) < accuracy &&
         ::fabs( angle - other.angle ) < accuracy &&
         ::fabs( sketchFilletRadius - other.sketchFilletRadius ) < accuracy &&
         ::fabs( baseFilletRadius - other.baseFilletRadius ) < accuracy &&
         ::fabs( bottomFilletRadius - other.bottomFilletRadius ) < accuracy )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbStampingValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры буртика.
           \en The bead parameters. \~
  \details \ru Буртик строится по замкнутому или незамкнутому контуру. На концах незамкнутого контура строятся законцовки,
    форма которых определяется параметром endType. Форма самого буртика определяется параметром beadType.\n
    Высота буртика - это расстояние от плоской грани, на которой он строится, до самой дальней от неё точки буртика.\n
    Параметор bottomWidth определяет ширину донышка U-образного буртика.\n
    Параметр angle определяет угол отклонения боковых стенок от вертикали в радианах. Если высота, радиус скругления
    дна и основания таковы, что боковые стенки отсутствуют, параметр angle игнорируется.\n
    Параметр reverse определяет направление построения - по нормали к плоской грани в случае false или против в случае true.\n
           \en Bead is constructed by open or closed contour. Tips are constructed at the ends of open contour,
    shape of which is defined by endType parameter. Shape of the bead is defined by beadType parameter.\n
    Height of the bead - is the distance from planar face on which it is constructed to the farthest point of bead.\n
    The bottomWidth parameter defines the bottom width of U-shaped bead.\n
    The angle parameter defines the deviation angle of sidewalls from the vertical in radians. If the height, fillet radius
    of the bottom and the base such that the sidewalls are absent, then angle parameter is ignored. \n
    The reverse parameter determines the direction of construction - along the normal to planar face if false or along opposite to the normal if true.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbBeadValues {
  /** \brief \ru Тип буртика.
             \en Type of the bead. \~
    \ingroup Build_Parameters
  */
  enum MbeBeadType {
    btRound = 0, ///< \ru Круглый. \en Circular. 
    btVType,     ///< \ru V-образный. \en V-shaped. 
    btUType,     ///< \ru U-образный. \en U-shaped. 
    btHalfRound  ///< \ru Полукруглый (для вытянутых жалюзи). \en Semicircular (for elongated jalousie). 
  };

  /** \brief \ru Тип законцовки буртика.
             \en Type of bead tip. \~
    \ingroup Build_Parameters
  */
  enum MbeBeadEndType {
    betClosed,  ///< \ru Закрытый. \en Closed. 
    betChopped, ///< \ru Рубленый. \en Chopped. 
  };

  double         hight;              ///< \ru Высота буртика. \en Height of the bead. 
  double         bottomWidth;        ///< \ru Ширина выпуклой части. \en Width of the convex part. 
  double         baseFilletRadius;   ///< \ru Радиус скругления основания. \en Fillet radius of the base. 
  double         bottomFilletRadius; ///< \ru Радиус скругления дна. \en Fillet radius of the bottom. 
  double         angle;              ///< \ru Угол уклона боковых стенок. \en Draft angle of sidewalls. 
  double         gap;                ///< \ru Зазор рубленой законцовки. \en Gap of chopped tip. 
  bool           reverse;            ///< \ru Направление построения буртика. \en Direction of the bead construction. 
  MbeBeadType    beadType;           ///< \ru Тип буртика. \en Type of the bead. 
  MbeBeadEndType endType;            ///< \ru Тип законцовки. \en Type of tip. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbBeadValues()
    : hight             ( 0.0       ),
      bottomWidth       ( 0.0       ),
      baseFilletRadius  ( 0.0       ),
      bottomFilletRadius( 0.0       ),
      angle             ( 0.0       ),
      gap               ( 0.0       ),
      reverse           ( false     ),
      beadType          ( btRound   ),
      endType           ( betClosed ) {
  }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbBeadValues( const MbBeadValues & other )
    : hight             ( other.hight              ),
      bottomWidth       ( other.bottomWidth        ),
      baseFilletRadius  ( other.baseFilletRadius   ),
      bottomFilletRadius( other.bottomFilletRadius ),
      angle             ( other.angle              ),
      gap               ( other.gap                ),
      reverse           ( other.reverse            ),
      beadType          ( other.beadType           ),
      endType           ( other.endType            ) {
  }
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbBeadValues( double h, double bottomW, double baseR, double bottomR,
                double ang, double g, bool rev, MbeBeadType bt, MbeBeadEndType bet )
    : hight             ( h       ),
      bottomWidth       ( bottomW ),
      baseFilletRadius  ( baseR   ),
      bottomFilletRadius( bottomR ),
      angle             ( ang     ),
      gap               ( g       ),
      reverse           ( rev     ),
      beadType          ( bt      ),
      endType           ( bet     ) {
  }

  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void Init( const MbBeadValues & other ) {
    hight              = other.hight;
    bottomWidth        = other.bottomWidth;
    baseFilletRadius   = other.baseFilletRadius;
    bottomFilletRadius = other.bottomFilletRadius;
    angle              = other.angle;
    gap                = other.gap;
    reverse            = other.reverse;
    beadType           = other.beadType;
    endType            = other.endType;
  }

  /// \ru Оператор присваивания. \en Assignment operator. 
  MbBeadValues & operator = ( const MbBeadValues & other ) { Init( other ); return *this; }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbBeadValues & other, double accuracy ) const {
    bool isSame = false;

    if ( reverse == other.reverse &&
         beadType == other.beadType &&
         endType == other.endType &&
         ::fabs( hight - other.hight ) < accuracy &&
         ::fabs( bottomWidth - other.bottomWidth ) < accuracy &&
         ::fabs( baseFilletRadius - other.baseFilletRadius ) < accuracy &&
         ::fabs( bottomFilletRadius - other.bottomFilletRadius ) < accuracy &&
         ::fabs( angle - other.angle ) < accuracy &&
         ::fabs( gap - other.gap ) < accuracy )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbBeadValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры жалюзи.
           \en The parameters of jalousie. \~
  \details \ru Жалюзи строятся по одному или нескольким отрезкам.\n
    Если параметр stretching имеет значение false - жалюзи строятся в виде отогнутой пластины, иначе - с полукруглым профилем.\n
    Высота жалюзи - это расстояние от плоской грани до самой верхней точки жалюзи. Ширина - это поперечный размер вырубаемого в листе выреза
    без учёта радиуса скругления.\n
    Коэффициент нейтрального слоя k учитывается при расчёте поперечного размера отогнутого жалюзи.\n
    При значении параметра reverse - false, жалюзи строятся в направлении нормали листовой грани, true - в противоположном направлении.\n
    Параметр normToThick определяет форму конца отогнутых жалюзи, при значении true - законцовка строится вдоль нормали к отогнутой пластине,
    при значении false - вдоль нормали к базовой листовой грани.\n
           \en Jalousie are built from one or more segments.\n
    If stretching parameter has value false - jalousie is built in the form of the bent plate, otherwise - with a semicircular profile.\n
    Height of jalousie - is the distance from planar face to the uppermost of jalousie point. Width - is transverse size of cut in the sheet
    without taking into account the fillet radius.\n
    Coefficient of neutral layer-k is taken into account when calculating the transverse size of the deflected jalousie.\n
    If reverse = false, then jalousie is built along the normal direction of sheet face, true - along the opposite direction.\n
    The normToThick parameter defines the shape of end of the deflected jalousie, if true - the tip is built along the normal to the deflected plate,
    if false - along the normal to the base sheet face.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbJalousieValues {
  double width;        ///< \ru Ширина. \en Width. 
  double hight;        ///< \ru Высота. \en Height. 
  double filletRadius; ///< \ru Радиус скругления. \en The fillet radius. 
  double k;            ///< \ru Коэффициент, определяющий положение нейтрального слоя. \en Coefficient determining the position of the neutral layer. 
  bool   reverse;      ///< \ru Направление построения жалюзи. \en Direction of jalousie construction. 
  bool   leftSide;     ///< \ru Сторона отрезка, по которой строятся жалюзи. \en The segment side which jalousie are constructed by. 
  bool   stretching;   ///< \ru Вытяжка. \en Stretch. 
  bool   normToThick;  ///< \ru По нормали к толщине. \en Along the normal to thickness. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbJalousieValues()
    : width       ( 0.0 ),
      hight       ( 0.0 ),
      filletRadius( 0.0 ),
      k           ( 0.0 ),
      reverse     ( false ),
      leftSide    ( false ),
      stretching  ( false ),
      normToThick ( false ) {
  }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbJalousieValues( const MbJalousieValues & other )
    : width       ( other.width        ),
      hight       ( other.hight        ),
      filletRadius( other.filletRadius ),
      k           ( other.k            ),
      reverse     ( other.reverse      ),
      leftSide    ( other.leftSide     ),
      stretching  ( other.stretching   ),
      normToThick ( other.normToThick  ) {
  }
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbJalousieValues( double wid, double high, double radius, double coef,
                    bool rev, bool left, bool stretch, bool norm )
    : width       ( wid     ),
      hight       ( high    ),
      filletRadius( radius  ),
      k           ( coef    ),
      reverse     ( rev     ),
      leftSide    ( left    ),
      stretching  ( stretch ),
      normToThick ( norm    ) {
  }

  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void Init( const MbJalousieValues & other ) {
    width        = other.width;
    hight        = other.hight;
    filletRadius = other.filletRadius;
    k            = other.k;
    reverse      = other.reverse;
    leftSide     = other.leftSide;
    stretching   = other.stretching;
    normToThick  = other.normToThick;
  }

  /// \ru Оператор присваивания. \en Assignment operator. 
  MbJalousieValues & operator = ( const MbJalousieValues & other ) {
    Init( other );
    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbJalousieValues & other, double accuracy ) const {
    bool isSame = false;

    if ( reverse == other.reverse &&
         leftSide == other.leftSide &&
         stretching == other.stretching &&
         normToThick == other.normToThick &&
         ::fabs( width - other.width ) < accuracy &&
         ::fabs( hight - other.hight ) < accuracy &&
         ::fabs( filletRadius - other.filletRadius ) < accuracy &&
         ::fabs( k - other.k ) < accuracy )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbJalousieValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры обечайки.
           \en A ruled shell parameters. \~
  \details \ru Обечайка строится по одному или двум эскизам. 
    В случае одного эскиза, второй расчитывается по параметрам height и slopeAngle. \n
    Зазор расчитывается оп следующему правилу: в зависимости от типа смещения зазора расчитывается точка на эскизе,
    в ней вычисляется нормаль, прямая проходящая вдоль этой нормали через расчитанную точку 
    на эскизе смещается влево и вправо на половину величины gapValue. 
    Получившиеся прямые определяют границы зазора.\n
           \en Shell ring is constructed by one or two sketches. 
    In the case of one sketch the second parameter is calculated from height and slopeAngle. \n
    Gap is calculated by the following rule: depending on the type of gap shift the point is calculated on the sketch,
    normal is calculated in its, line passing along this normal through calculated point 
    on the sketch shifted to the left and right at the half value gapValue. 
    Resulting straight lines define boundaries of the gap.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbRuledSolidValues {
  /** \brief \ru Тип смещения зазора.
             \en A displacement type of the gap. \~
    \details \ru За начало отсчёта принимается начальная точка контура. Угол отмеряется против часовой стрелки,
             а длина по направлению от начальной точки контура к конечной точке.
             \en Starting point of contour is taken as the origin. The angle is measured counterclockwise,
             and the length along the direction from the starting point of contour to the endpoint. \~
    \ingroup Build_Parameters
  */
  enum MbeGapShiftType {
    gsAngle = 0,   ///< \ru По углу. \en By angle. 
    gsLength,      ///< \ru По метрической длине. \en By metric length. 
    gsRatio,       ///< \ru В процентах от метрической длины. \en Percentage of the metric length.
    gsSegmentRatio ///< \ru В формате 1.3, где 1 - номер сегмента, а .3 - доля его метрической длины. \en In form 1.3 where 1 is a segment number and .3 is a ratio of its metric length.
  };

  MbPlacement3D          placement1;       ///< \ru Локальная система координат первого контура. \en The local coordinate system of the first contour.
  MbContour              contour1;         ///< \ru Первый контур. \en The first contour.
  DPtr< SArray<double> > breaks1;          ///< \ru Параметры разбивки первого контура. \en The fragmentation parameters of the first contour.
  DPtr<MbPlacement3D>    placement2;       ///< \ru Локальная система координат второго контура. \en The local coordinate system of the second contour.
  SPtr<MbContour>        contour2;         ///< \ru Второй контур. \en The second contour.
  DPtr< SArray<double> > breaks2;          ///< \ru Параметры разбивки второго контура. \en The fragmentation parameters of the second contour.
  double                 thickness;        ///< \ru Толщина листа. \en The sheet thickness. 
  double                 radius;           ///< \ru Радиус скругления эскизов. \en The fillet radius of sketch. 
  double                 slopeAngle;       ///< \ru Угол уклона (для создания по одному эскизу). \en Draft angle (for creating by one sketch). 
  double                 height;           ///< \ru Высота обечайки (для создания по одному эскизу). \en Height of shell ring (for creating by one sketch). 
  double                 gapValue;         ///< \ru Величина зазора. \en Gap value.
  double                 gapAngle;         ///< \ru Угол уклона зазора. \en Gap draft angle (for creating by one sketch).
  double                 gapShift;         ///< \ru Смещение зазора. \en Shift of the gap. 
  MbeGapShiftType        shiftType;        ///< \ru Тип смещения зазора. \en A displacement type of the gap. 
  bool                   guideSidesByNorm; ///< \ru Направляющие боковины по нормали к линейчатой поверхности. \en Guide sides along normal to the ruled surface. 
  bool                   generSidesByNorm; ///< \ru Образующие боковины по нормали к линейчатой поверхности. \en Generating sides along normal to the ruled surface. 
  bool                   cylindricBends;   ///< \ru Формировать сгибы с постоянным радиусом. \en Create bend with permanent radius.
  bool                   joinByVertices;   ///< \ru Соединять контура через вершины. \en Join contour through vertices. 
  double                 surfDistance;     ///< \ru Расстояние от поверхности surface. \en Distance from the surface "surface". 
  SPtr<MbSurface>        surface;          ///< \ru Поверхность, до которой выдавливать. \en Surface to extrude up to which. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbRuledSolidValues()
    : placement1      (         ),
      contour1        (         ),
      breaks1         (    NULL ),
      placement2      (    NULL ),
      contour2        (    NULL ),
      breaks2         (    NULL ),
      thickness       (     0.0 ),
      radius          (     0.0 ),
      slopeAngle      (     0.0 ),
      height          (     0.0 ),
      gapValue        (     0.0 ),
      gapAngle        (     0.0 ),
      gapShift        (     0.0 ),
      shiftType       ( gsAngle ),
      guideSidesByNorm(   false ),
      generSidesByNorm(   false ),
      cylindricBends  (   false ),
      joinByVertices  (    true ),
      surfDistance    (     0.0 ),
      surface         (    NULL ) {
  }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbRuledSolidValues( const MbRuledSolidValues & other )
    : placement1      ( other.placement1 ),
      contour1        (),
      breaks1         ( (other.breaks1 != NULL) ? new SArray<double>(*other.breaks1) : NULL ),
      placement2      ( (other.placement2 != NULL) ? new MbPlacement3D(*other.placement2) : NULL ),
      contour2        ( (other.contour2 != NULL) ? new MbContour() : NULL ),
      breaks2         ( (other.breaks2 != NULL) ? new SArray<double>(*other.breaks2) : NULL ),
      thickness       ( other.thickness ),
      radius          ( other.radius ),
      slopeAngle      ( other.slopeAngle ),
      height          ( other.height ),
      gapValue        ( other.gapValue ),
      gapAngle        ( other.gapAngle ),
      gapShift        ( other.gapShift ),
      shiftType       ( other.shiftType ),
      guideSidesByNorm( other.guideSidesByNorm ),
      generSidesByNorm( other.generSidesByNorm ),
      cylindricBends  ( other.cylindricBends ),
      joinByVertices  ( other.joinByVertices ),
      surfDistance    ( other.surfDistance ),
      surface         ( (other.surface != NULL) ? static_cast<MbSurface *>(&other.surface->Duplicate()) : NULL ) {
    contour1.Init( other.contour1 );
    if ( contour2 != NULL && other.contour2 != NULL )
      contour2->Init( *other.contour2 );
  }
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbRuledSolidValues( const MbPlacement3D & place1, const MbContour & cntr1, const SArray<double> * brks1,
                      const MbPlacement3D * place2, const MbContour * cntr2, const SArray<double> * brks2,
                      const double thick, const double rad, const double sAngle, const double h,
                      const double gap, const double shift, const MbeGapShiftType type,
                      const bool guideByNorm, const bool generByNorm, const bool cylBends, const bool joinByVert,
                      const double surfDist, const MbSurface * surf )
    : placement1( place1 ),
      contour1(),
      breaks1( (brks1 != NULL) ? new SArray<double>(*brks1) : NULL ),
      placement2( (place2 != NULL) ? new MbPlacement3D(*place2) : NULL ),
      contour2( (cntr2 != NULL) ? new MbContour() : NULL ),
      breaks2( (brks2 != NULL) ? new SArray<double>(*brks2) : NULL ),
      thickness( thick ),
      radius( rad ),
      slopeAngle( sAngle ),
      height( h ),
      gapValue( gap ),
      gapAngle( 0.0 ),
      gapShift( shift ),
      shiftType( type ),
      guideSidesByNorm( guideByNorm ),
      generSidesByNorm( generByNorm ),
      cylindricBends( cylBends ),
      joinByVertices( joinByVert ),
      surfDistance( surfDist ),
      surface( (surf != NULL) ? static_cast<MbSurface *>(&surf->Duplicate()) : NULL ) {
    contour1.Init( cntr1 );
    if ( (contour2 != NULL) && (cntr2 != NULL) )
      contour2->Init( *cntr2 );
  }

  /// \ru Инициализировать по другому объекту. \en Initialize by another object. 
  void Init( const MbRuledSolidValues & other ) {
    placement1.Init( other.placement1 );
    contour1.Init( other.contour1 );

    if ( other.breaks1 != NULL ) {
      if ( breaks1 != NULL )
        ((SArray<double> &)*breaks1) = *other.breaks1;
      else
        breaks1 = new SArray<double>( *other.breaks1 );
    }
    else
      breaks1 = NULL;

    if ( other.placement2 != NULL ) {
      if ( placement2 != NULL )
        placement2->Init( *other.placement2 );
      else
        placement2 = new MbPlacement3D( *other.placement2 );
    }
    else
      placement2 = NULL;

    if ( other.contour2 != NULL ) {
      if ( contour2 == NULL )
        contour2 = new MbContour();
      contour2->Init( *other.contour2 );
    }
    else
      contour2 = NULL;

    if ( other.breaks2 != NULL ) {
      if ( breaks2 != NULL )
        ((SArray<double> &)*breaks2) = *other.breaks2;
      else
        breaks2 = new SArray<double>( *other.breaks2 );
    }
    else
      breaks1 = NULL;

    thickness        = other.thickness;
    radius           = other.radius;
    slopeAngle       = other.slopeAngle;
    height           = other.height;
    gapValue         = other.gapValue;
    gapAngle         = other.gapAngle;
    gapShift         = other.gapShift;
    shiftType        = other.shiftType;
    guideSidesByNorm = other.guideSidesByNorm;
    generSidesByNorm = other.generSidesByNorm;
    cylindricBends   = other.cylindricBends;
    joinByVertices   = other.joinByVertices;
    surfDistance     = other.surfDistance;

    if ( other.surface != NULL )
      surface = static_cast<MbSurface *>( &other.surface->Duplicate() );
    else
      surface = NULL;
  }

  /// \ru Инициализировать контуры. \en Initialize contours. 
  void Init( const MbPlacement3D & place1, const MbContour & cntr1, const SArray<double> * brks1,
             const MbPlacement3D * place2, const MbContour * cntr2, const SArray<double> * brks2 ) {
    placement1.Init( place1 );
    contour1.Init( cntr1 );

    if ( brks1 != NULL ) {
      if ( breaks1 != NULL )
        ((SArray<double> &)*breaks1) = *brks1;
      else
        breaks1 = new SArray<double>( *brks1 );
    }
    else
      breaks1 = NULL;

    if ( place2 != NULL ) {
      if ( placement2 != NULL )
        placement2->Init( *place2 );
      else
        placement2 = new MbPlacement3D( *place2 );
    }
    else
      placement2 = NULL;

    if ( cntr2 != NULL ) {
      if ( contour2 == NULL )
        contour2 = new MbContour();
      contour2->Init( *cntr2 );
    }
    else
      contour2 = NULL;

    if ( brks2 != NULL ) {
      if ( breaks2 != NULL )
        ((SArray<double> &)*breaks2) = *brks2;
      else
        breaks2 = new SArray<double>( *brks2 );
    }
    else
      breaks1 = NULL;
  }

  /// \ru Оператор присваивания. \en Assignment operator. 
  MbRuledSolidValues & operator = ( const MbRuledSolidValues & other ) {
    Init( other );
    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbRuledSolidValues & other, double accuracy ) const {
    size_t i, cnt;
    bool isSame = false;

    if ( shiftType == other.shiftType &&
         guideSidesByNorm == other.guideSidesByNorm &&
         generSidesByNorm == other.generSidesByNorm &&
         cylindricBends == other.cylindricBends &&
         joinByVertices == other.joinByVertices &&
         placement1.IsSame( other.placement1, accuracy ) &&
         contour1.IsSame( other.contour1, accuracy ) &&
         ::fabs( thickness - other.thickness ) < accuracy &&
         ::fabs( radius - other.radius ) < accuracy &&
         ::fabs( slopeAngle - other.slopeAngle ) < accuracy &&
         ::fabs( height - other.height ) < accuracy &&
         ::fabs( gapValue - other.gapValue ) < accuracy &&
         ::fabs( gapAngle - other.gapAngle ) < accuracy &&
         ::fabs( gapShift - other.gapShift ) < accuracy &&
         ::fabs( surfDistance - other.surfDistance ) < accuracy ) {
      
      bool isBreaks1 = breaks1 != NULL;
      bool isOtherBreaks1 = other.breaks1 != NULL;
      bool isPlacement2 = placement2 != NULL;
      bool isOtherPlacement2 = other.placement2 != NULL;
      bool isContour2 = contour2 != NULL;
      bool isOtherContour2 = other.contour2 != NULL;
      bool isBreaks2 = breaks2 != NULL;
      bool isOtherBreaks2 = other.breaks2 != NULL;
      bool isSurf = surface != NULL;
      bool isOtherSurf = other.surface != NULL;

      if ( isBreaks1 == isOtherBreaks1 &&
           isPlacement2 == isOtherPlacement2 &&
           isContour2 == isOtherContour2 &&
           isBreaks2 == isOtherBreaks2 &&
           isSurf == isOtherSurf ) {
        isSame = true;
        if ( isSame && isBreaks1 && isOtherBreaks1 ) {
          if ( breaks1->Count() != other.breaks1->Count() )
            isSame = false;

          for ( i = 0, cnt = breaks1->Count(); i < cnt && isSame; i++ )
            if ( ::fabs( (*breaks1)[i] - (*other.breaks1)[i] ) >= accuracy ) {
              isSame = false;
              break;
            }
        }

        if ( isSame && isPlacement2 && isOtherPlacement2 && !placement2->IsSame( *other.placement2, accuracy ) )
          isSame = false;

        if ( isSame && isContour2 && isOtherContour2 && !contour2->IsSame( *other.contour2, accuracy ) )
          isSame = false;

        if ( isSame && isBreaks2 && isOtherBreaks2 ) {
          if ( breaks2->Count() != other.breaks2->Count() )
            isSame = false;

          for ( i = 0, cnt = breaks2->Count(); i < cnt && isSame; i++ )
            if ( ::fabs( (*breaks2)[i] - (*other.breaks2)[i] ) >= accuracy ) {
              isSame = false;
              break;
            }
        }

        if ( isSame && isSurf && isOtherSurf && !surface->IsSame( *other.surface, accuracy ) )
          isSame = false;
      }
    }
    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbRuledSolidValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры операции упрощения углов в развёртке листового тела.
           \en Parameters of the simplification corners operation.\n \~
  \details \ru Параметры операции упрощения углов в развёртке листового тела.\n
           \en Parameters of the simplification corners operation.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbSimplifyFlatPatternValues {
  bool uniteFaces;      ///< \ru Флаг слияния подобных граней. \en The merger faces flag. 
  bool cornerTreatment; ///< \ru Флаг упрощения углов развёртки. \en The simplification corners flag. 
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbSimplifyFlatPatternValues() : uniteFaces( false ), cornerTreatment( true ) {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbSimplifyFlatPatternValues( bool uFaces, bool cTreatment ) : 
    uniteFaces     ( uFaces   ),
    cornerTreatment( cTreatment ) {
  }
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbSimplifyFlatPatternValues( const MbSimplifyFlatPatternValues & other ) : 
    uniteFaces     ( other.uniteFaces ),
    cornerTreatment( other.cornerTreatment ) {
  }
  /// \ru Инициализировать по конкретным параметрам. \en Initialize by specific parameters. 
  void Init( bool uFaces, bool cTreatment ) {
    uniteFaces      = uFaces;
    cornerTreatment = cTreatment;
  }
  /// \ru Инициализировать по другой структуре. \en Initialize by another structure. 
  void Init( const MbSimplifyFlatPatternValues & other ) { 
    uniteFaces      = other.uniteFaces; 
    cornerTreatment = other.cornerTreatment;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  const MbSimplifyFlatPatternValues & operator = ( const MbSimplifyFlatPatternValues & other ) {
    uniteFaces      = other.uniteFaces;
    cornerTreatment = other.cornerTreatment;

    return *this;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbSimplifyFlatPatternValues & other ) const {
    bool isSame = false;

    if ( (!uniteFaces == !other.uniteFaces) && (!cornerTreatment == !other.cornerTreatment) )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbSimplifyFlatPatternValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры и имена элементов сгиба.
           \en Parameters and names of bend's elements. \~
  \details \ru Параметры сгиба. Имена внешней и внутренней граней сгиба, а также имена сегментов контура, между которыми строится сгиб.
           Используются для построения листовых тел выдавливанием эскизов. Дополнительное имя в операциях построения не используется.\n
           \en The bend parameters. Names of the outer and inner faces of the bend, and names of contour segments between which bend is built.
           Used to construct sheet solids by sketches extrusion. Additional name in operations of construction is not used.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbSMBendNames : public MbBendValues {
public:
  SimpleName segName1;      ///< \ru Имя первого из двух смежных сегментов контура. \en Name of the first of two adjacent segments of the contour. 
  SimpleName segName2;      ///< \ru Имя второго из двух смежных сегментов контура. \en Name of the second of two adjacent segments of the contour. 
  SimpleName extraName;     ///< \ru Дополнительное имя. \en Additional name. 
  uint       groupNumber;   ///< \ru Номер группы одновременно сгибаемых/разгибаемых сгибов. \en Group number of simultaneously bent/unbent bends.
  MbName     innerFaceName; ///< \ru Имя внутренней грани сгиба. \en Name of interior face of bend. 
  MbName     outerFaceName; ///< \ru Имя внешней грани сгиба. \en Name of exterior face of bend. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbSMBendNames() : MbBendValues(), 
                    segName1 ( SimpleName(SIMPLENAME_MAX) ), 
                    segName2 ( SimpleName(SIMPLENAME_MAX) ), 
                    extraName( SimpleName(SIMPLENAME_MAX) ),
                    groupNumber( SYS_MAX_UINT ),
                    innerFaceName(), 
                    outerFaceName() {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbSMBendNames( double coef, double rad, double ang, SimpleName sn1, SimpleName sn2, SimpleName exn = -1, uint groupNumber = SYS_MAX_UINT );
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbSMBendNames( const MbSMBendNames &init )
    : MbBendValues( init ),
      segName1     ( init.segName1 ),
      segName2     ( init.segName2 ),
      extraName    ( init.extraName ),
      groupNumber  ( init.groupNumber ),
      innerFaceName( init.innerFaceName ),
      outerFaceName( init.outerFaceName ) 
  {
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbSMBendNames & other, double accuracy ) const {
    bool isSame = false;

    if ( segName1 == other.segName1 &&
         segName2 == other.segName2 &&
         extraName == other.extraName &&
         groupNumber == other.groupNumber &&
         innerFaceName == other.innerFaceName &&
         outerFaceName == other.outerFaceName &&
         MbBendValues::IsSame( other, accuracy ) )
      isSame = true;

    return isSame;
  }

private:
  MbSMBendNames & operator = ( const MbSMBendNames & ); // \ru Не реализовано \en Not implemented 

  KNOWN_OBJECTS_RW_PTR_OPERATORS_EX( MbSMBendNames, MATH_FUNC_EX ) // \ru Для работы с указателями класса \en For working with pointers of class 
};


//------------------------------------------------------------------------------
/** \brief \ru Внешняя и внутренняя грани сгиба с параметрами.
           \en Outer and inner faces of bend with parameters. \~
  \details \ru Внешняя и внутренняя грани сгиба с внутренним радиусом и коэффициентом нейтрального слоя.
           Полностью определяет сгиб и связывает его с параметрами.\n
           \en Outer and inner faces of bend with inner radius and neutral layer coefficient.
           Completely determines the bend and associates it with parameters.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbSheetMetalBend : public MbBendValues {
public:
  RPArray<MbFace> innerFaces; ///< \ru Указатели на внутренние грани сгиба. \en Pointers to interior faces of bend. 
  RPArray<MbFace> outerFaces; ///< \ru Указатели на внешние грани сгиба. \en Pointers to exterior faces of bend. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbSheetMetalBend() : MbBendValues(), innerFaces( 1, 1 ), outerFaces( 1, 1 ) {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbSheetMetalBend( MbFace * inner, MbFace * outer, const double k, const double radius, const double angle, const double coneAngle )
    : MbBendValues( k, radius, angle, coneAngle ), innerFaces( 1, 1 ), outerFaces( 1, 1 ) {
    innerFaces.Add( inner );
    outerFaces.Add( outer );
  }
  MbSheetMetalBend( const RPArray<MbFace> & inners, const RPArray<MbFace> & outers, const double k, const double radius, const double angle, const double coneAngle )
    : MbBendValues( k, radius, angle, coneAngle ), innerFaces( inners.Count(), 1 ), outerFaces( outers.Count(), 1 ) {
    innerFaces.AddArray( inners );
    outerFaces.AddArray( outers );
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbSheetMetalBend & other, double accuracy ) const {
    bool isSame = false;

    if ( MbBendValues::IsSame( other, accuracy ) &&
         innerFaces.Count() == other.innerFaces.Count() &&
         outerFaces.Count() == other.outerFaces.Count() ) {
      isSame = true;

      size_t i, cnt;
      for ( i = 0, cnt = innerFaces.Count(); i < cnt && isSame; i++ )
        if ( innerFaces[i] == NULL || other.innerFaces[i] == NULL || !innerFaces[i]->IsSame( *other.innerFaces[i], accuracy ) ) {
          isSame = false;
          break;
        }

      for ( i = 0, cnt = outerFaces.Count(); i < cnt && isSame; i++ )
        if ( outerFaces[i] == NULL || other.outerFaces[i] == NULL || !outerFaces[i]->IsSame( *other.outerFaces[i], accuracy ) ) {
          isSame = false;
          break;
        }
    }

    return isSame;
  }

private:
  MbSheetMetalBend( const MbSheetMetalBend & );               // \ru Не реализовано \en Not implemented 
  MbSheetMetalBend & operator = ( const MbSheetMetalBend & ); // \ru Не реализовано \en Not implemented 
};


//------------------------------------------------------------------------------
// Индексы внешних и внутренних граней сгиба с параметрами.
// ---
struct MATH_CLASS MbBendIndices : public MbBendValues {
public:
  SArray<MbItemIndex> innerFacesIndices; ///< Индексы внутренних граней сгиба.
  SArray<MbItemIndex> outerFacesIndices; ///< Индексы внешних граней сгиба.

  /// Конструктор по умолчанию.
  MbBendIndices() : MbBendValues(), innerFacesIndices( 0, 1 ), outerFacesIndices( 0, 1 ) {}
  MbBendIndices( const MbBendIndices & other )
    : MbBendValues( other ), innerFacesIndices( other.innerFacesIndices ), outerFacesIndices( other.outerFacesIndices ) {}

  /// \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix.
  void Transform( const MbMatrix3D & matr ) {
    matr.TransformLength( radius );
    for ( size_t innerFaceIndex = innerFacesIndices.Count(); innerFaceIndex--; )
      innerFacesIndices[innerFaceIndex].Transform( matr );
    for ( size_t outerFaceIndex = outerFacesIndices.Count(); outerFaceIndex--; )
      outerFacesIndices[outerFaceIndex].Transform( matr );
  }
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void Move( const MbVector3D & to ) {
    for ( size_t innerFaceIndex = innerFacesIndices.Count(); innerFaceIndex--; )
      innerFacesIndices[innerFaceIndex].Move( to );
    for ( size_t outerFaceIndex = outerFacesIndices.Count(); outerFaceIndex--; )
      outerFacesIndices[outerFaceIndex].Move( to );
  }
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void Rotate( const MbAxis3D & axis, double ang ) {
    for ( size_t innerFaceIndex = innerFacesIndices.Count(); innerFaceIndex--; )
      innerFacesIndices[innerFaceIndex].Rotate( axis, ang );
    for ( size_t outerFaceIndex = outerFacesIndices.Count(); outerFaceIndex--; )
      outerFacesIndices[outerFaceIndex].Rotate( axis, ang );
  }
  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbBendIndices & other, double accuracy ) const {
    bool isSame = false;

    if ( MbBendValues::IsSame( other, accuracy ) &&
         innerFacesIndices.Count() == other.innerFacesIndices.Count() &&
         outerFacesIndices.Count() == other.outerFacesIndices.Count() ) {
      isSame = true;
      
      size_t i, cnt;
      for ( i = 0, cnt = innerFacesIndices.Count(); i < cnt && isSame; i++ )
        if ( !innerFacesIndices[i].IsSame( other.innerFacesIndices[i], accuracy ) ) {
          isSame = false;
          break;
        }

      for ( i = 0, cnt = outerFacesIndices.Count(); i < cnt && isSame; i++ )
        if ( !outerFacesIndices[i].IsSame( other.outerFacesIndices[i], accuracy ) ) {
          isSame = false;
          break;
        }
    }

    return isSame;
  }

private:
  MbBendIndices & operator = ( const MbBendIndices & ); // не реализовано

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbBendIndices ) // для работы со ссылками и объектами класса
};


//------------------------------------------------------------------------------
// Параметры нелистового сгиба.
// ---
struct MATH_CLASS MbAnyBend {
public:
  MbCartPoint origin;
  MbVector    vector;
  double      wideness;
  double      neutralRadius;

  /// Конструктор по умолчанию.
  MbAnyBend() : origin(), vector(), wideness( 0.0 ), neutralRadius( 0.0 ) {}
  MbAnyBend( const MbAnyBend & other )
    : origin( other.origin ), vector( other.vector ), wideness( other.wideness ), neutralRadius( other.neutralRadius ) {}

  void Transform( const MbMatrix3D & matr ) { matr.TransformLength( wideness ); matr.TransformLength( neutralRadius ); }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbAnyBend & other, double accuracy ) const {
    bool isSame = false;

    if ( c3d::EqualPoints( origin, other.origin, accuracy ) &&
         c3d::EqualVectors( vector, other.vector, accuracy ) &&
         ::fabs( wideness - other.wideness ) < accuracy &&
         ::fabs( neutralRadius - other.neutralRadius ) < accuracy )
      isSame = true;

    return isSame;
  }

private:
  MbAnyBend & operator = ( const MbAnyBend & ); // не реализовано

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbAnyBend ) // для работы со ссылками и объектами класса
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры штамповки телом-инструментом.
           \en The parameters of stamping by a tool solid. \~
  \details \ru Параметры шатмповки телом-инструментом определяют толщину формованной части и радиус скругления основания.\n
           \en The parameters of stamping by a tool solid is specified a thickness of a stamped part and fillet radius of stamping base.\n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbUserStampingValues {
  double baseFilletRadius; ///< \ru Радиус скругления основания (отрицательное значение запрещает скругление). \en Fillet radius of base (negative value prohibits fillet). 
  double stampThickness;   ///< \ru Толщина формованной части. \en Thickness of a stamped part. 

  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbUserStampingValues() :
    baseFilletRadius ( 0.0 ),
    stampThickness   ( 0.0 )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbUserStampingValues( const MbUserStampingValues & other ) :
    baseFilletRadius ( other.baseFilletRadius ),
    stampThickness   ( other.stampThickness   )
  {}
  /// \ru Конструктор по конкретным параметрам. \en Constructor by specific parameters. 
  MbUserStampingValues( double baseRad, double thick ) :
    baseFilletRadius  ( baseRad ),
    stampThickness    ( thick   )
  {}

  /// \ru Оператор присваивания. \en Assignment operator. 
  MbUserStampingValues & operator = ( const MbUserStampingValues &other ) { Init( other ); return *this; }
  /// \ru Инициализация по другому объекту. \en Initialization by another object. 
  void Init( const MbUserStampingValues & other ) {
    baseFilletRadius   = other.baseFilletRadius;
    stampThickness = other.stampThickness;
  }

  ///\ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool IsSame( const MbUserStampingValues & other, double accuracy ) const {
    bool isSame = false;

    if ( ::fabs(baseFilletRadius - other.baseFilletRadius) < accuracy &&
         ::fabs(stampThickness - other.stampThickness) < accuracy )
      isSame = true;

    return isSame;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbUserStampingValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};

#endif // __SHEET_METAL_PARAM_H