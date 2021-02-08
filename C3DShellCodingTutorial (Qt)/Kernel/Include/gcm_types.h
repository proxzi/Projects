//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Типы данных геометрического решателя
         \en Data types of geometric solver \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GCM_TYPES_H
#define __GCM_TYPES_H

#include <system_types.h>

class MtGeomSolver;
class MbPlacement3D;

#define GCM_ID_TYPE 1 // 1 - MtObjectId is a struct, 0 - MtObjectId is simple integer.

#if ( GCM_ID_TYPE == 1 )

typedef struct { uint32 id; } MtObjectId;
const MtObjectId _GCM_NULL = { SYS_MAX_UINT32 };
const MtObjectId _GCM_GROUND = { 0 };

#else // GCM_ID_TYPE

typedef uint32  MtObjectId;
const MtObjectId _GCM_NULL = SYS_MAX_UINT32;
const MtObjectId _GCM_GROUND = 0;

#endif // GCM_ID_TYPE

/** \addtogroup GCM_3D_API
    \{
*/

/// \ru Система геометрических ограничений. \en System of geometric constraints. \~
typedef MtGeomSolver* GCM_system;     
/// \ru Дескриптор геометрического объекта, зарегистрированного в контексте решателя. \en Descriptor of geometrical object registered in the solver context. 
typedef MtObjectId    GCM_object;       
/// \ru Дескриптор геометрического объекта, зарегистрированного в контексте решателя. \en Descriptor of geometrical object registered in the solver context. 
typedef GCM_object    GCM_geom;       
/// \ru Дескриптор ограничения, зарегистрированного в решателе. \en Descriptor of a constraint registered in the solver. 
typedef GCM_object    GCM_constraint;
/// \ru Дескриптор паттерна, зарегистрированного в решателе. \en Descriptor of a pattern registered in the solver. 
typedef GCM_object    GCM_pattern;
/// \ru Дескриптор пустого объекта или ограничения. \en Descriptor of empty object or constraint. \~
const   GCM_object    GCM_NULL = _GCM_NULL;
/** \brief \ru Дескриптор неподвижного подмножества объектов, заданных в глобальной системой координат. 
           \en Descriptor of rigid subset of objects which are given in global coordinate system. \~
*/
const   GCM_geom      GCM_GROUND = _GCM_GROUND;

//----------------------------------------------------------------------------------------
/** \brief \ru Словарь типов геометрических примитивов.
           \en Dictionary of geometric primitives types. \~
*/
// ---
typedef enum 
{
  /*
    (!) Do not change the integral constants (they are written to file permanently).
  */

    GCM_NULL_GTYPE = 0  ///< \ru Пустой геометрический объект. \en Empty geometric object.
  , GCM_POINT       ///< \ru Точка.     \en Point.
  , GCM_LINE        ///< \ru Прямая.    \en Line.
  , GCM_PLANE       ///< \ru Плоскость. \en Plane.
  , GCM_CYLINDER    ///< \ru Цилиндр.   \en Cylinder.
  , GCM_CONE        ///< \ru Конус.     \en Cone.
  , GCM_SPHERE      ///< \ru Сферическая поверхность.  \en Spherical surface.
  , GCM_TORUS       ///< \ru Тороидальная поверхность. \en Toroidal surface.
  , GCM_CIRCLE      ///< \ru Окружность.        \en Circle.
  , GCM_LCS         ///< \ru Система координат. \en Coordinate system.
  , GCM_MARKER      ///< \ru Точка и пара ортонормированных векторов. \en Point and pair of orthonormalized vectors.
  , GCM_SPLINE      ///< \ru Сплайновая кривая. \en Spline curve.
  , GCM_VECTOR      // Unit vector (internal use only)
  , GCM_AXIS        // Point with unit vector (internal use only)
  , GCM_UNKNOWN_GTYPE // \ru Геометрический тип, не поддерживаемый решателем. \en Some geometric type, which is not supported by the solver. \~  
  , GCM_LAST_GTYPE    // \ru Количество типов. \en The count of types.
} GCM_g_type;

//----------------------------------------------------------------------------------------
/** \brief \ru Словарь типов ограничения.
           \en Dictionary of constraint types. \~

  \note \ru Значения этого перечисления могут быть использованы для постоянного 
            хранения и останутся неизменными в следующих версиях.
        \en Values of this enum can be used for permanent storage 
            and will be kept in the future versions. \~
*/
//---
typedef enum
{
  /*
    (!) Do not change the integral constants (they are written to file permanently).
  */
    GCM_UNKNOWN         = -1  ///< \ru Не определенный тип. \en Unknown type.
  , GCM_COINCIDENT      =  0  ///< \ru Геометрическое совпадение. \en Coincidence of loci.
  , GCM_PARALLEL        =  1  ///< \ru Параллельность двух объектов, имеющих направление. \en Parallelism of two objects which have a direction vector.
  , GCM_PERPENDICULAR   =  2  ///< \ru Перпендикулярность двух объектов, имеющих направление. \en Perpendicularity of two objects which have a direction vector.
  , GCM_TANGENT         =  3  ///< \ru Касание двух поверхностей или кривых. \en Tangency of two objects, surfaces and curves.
  , GCM_CONCENTRIC      =  4  ///< \ru Концентричность двух объектов, имеющих ось или центр. \en Concentricity of two objects having a center or an axis.
  , GCM_DISTANCE        =  5  ///< \ru Линейное размер между объектами. \en Linear dimension between objects.
  , GCM_ANGLE           =  6  ///< \ru Угловой размер между векторными объектами. \en Angular dimension between directed objects (vectors).
  , GCM_TRANSMITTION    =  9  ///< \ru Механическая передача. \en Mechanical transmission. 
  , GCM_CAM_MECHANISM   = 10  ///< \ru Кулачковый механизм. \en Cam mechanism.
  , GCM_SYMMETRIC       = 11  ///< \ru Симметричность. \en Symmetry.
  , GCM_DEPENDENT       = 14  ///< \ru Зависимый объект. \en Dependent object.
  , GCM_PATTERNED       = 15  ///< \ru Элемент паттерна. \en Patterned object.
  , GCM_LINEAR_PATTERN  = 16  ///< \ru Линейный паттерн. \en Linear pattern.
  , GCM_ANGULAR_PATTERN = 17  ///< \ru Угловой паттерн. \en Angular pattern.
  , GCM_RADIUS          = 18  ///< \ru Радиальный размер. \en Radial dimension.
  , GCM_LAST_CTYPE
  , GCM_IN_PLACE =  7 // Deprecated
} GCM_c_type;

//----------------------------------------------------------------------------------------
/** \brief  \ru Варианты выравнивания направлений. 
            \en Variants of alignment. \~
  \note \ru Значения этого перечисления могут быть использованы для постоянного 
            хранения и останутся неизменными в следующих версиях.
        \en Values of this enum can be used for permanent storage 
            and will be kept in the future versions. \~
*/
//---
typedef enum
{
  /*
    (!) Do not change the constants (they are written to file permanently).
  */  
  GCM_MIN_ALIGNMENT= -1,  // Minimum value of this enum
  GCM_OPPOSITE     = -1,  ///< \ru Противонаправленные. \en Anti-align the directions. \~
  GCM_CLOSEST      =  0,  ///< \ru Ориентация согласно ближайшего решения. \en Orientation according to the nearest solution. \~
  GCM_COORIENTED   =  1,  ///< \ru Сонаправленные. \en Cooriented directions. \~  
  GCM_NO_ALIGNMENT =  2,  ///< \ru Нет определенной ориентации. \en No defined orientation. \~  
  /*
    Additional variants of alignment (they are used for tangency variants)
  */
  GCM_ALIGNED_0 = GCM_COORIENTED,
  GCM_ALIGNED_1 = 3,
  GCM_ALIGNED_2 = 4,
  GCM_ALIGNED_3 = 5,
  GCM_REVERSE_0 = GCM_OPPOSITE,
  GCM_REVERSE_1 = 6,
  GCM_REVERSE_2 = 7,
  GCM_REVERSE_3 = 8,
  /*
    Additional variants of alignment (they are used for patterns and symmetry)
  */  
  GCM_ALIGNED   = 1,  ///< \ru ЛСК с одинаковой ориентацией. \en Axis aligned local coordinate systems. \~
  GCM_ROTATED   = 9,  ///< Ротационное (вращательной) выравнивание элементов паттерна.
  GCM_ALIGN_WITH_AXIAL_GEOM = 10,  ///< Выровнять с объектом, задающим ось.

  GCM_MAX_ALIGNMENT, // Maximum value of this enum 
  
} GCM_alignment;

//----------------------------------------------------------------------------------------
/** \brief  \ru Вариант углового размера. 
            \en Variant of angular dimension. \~
    \note   \ru Значения этого перечисления могут быть использованы для постоянного
                хранения данных приложения и останутся неизменными в следующих версиях.
            \en Values of this enum can be used for permanent storing of app data
                and will be kept in the future versions. \~
*/
//---
typedef enum
{
  GCM_NONE_ANGLE  = 0,  ///< \ru Неопределен \en Undefined
  GCM_2D_ANGLE    = 1,  ///< \ru Угол для планарных соединений (0 .. 360 градусов) \en Angle of planar joints (0 .. 360 degrees) 
  GCM_3D_ANGLE    = 2,  ///< \ru Угол в пространстве (0 .. 180 градусов) \en Angle in space (0 .. 180 degrees)   
  GCM_PLANAR_ANGLE = GCM_2D_ANGLE
} GCM_angle_type;

//----------------------------------------------------------------------------------------
/** \brief  \ru Варианты касания поверхностей или кривых. 
            \en Variants of tangency of surfaces or curves. \~
    \note \ru Значения этого перечисления могут быть использованы для постоянного
              хранения данных приложения и останутся неизменными в следующих версиях.
          \en Values of this enum can be used for permanent storage of app data and will 
              be kept in the future versions. \~
*/
//---
typedef enum
{
  /*
    (!) Do not change the constants
  */
    GCM_TAN_NONE   =  0x00  ///< \ru Не выбрано. \en Not chosen.
  , GCM_TAN_POINT  =  0x01  ///< \ru Касание в общем случае (контакт точкой). \en Tangency in general case (contact at a point). 
  , GCM_TAN_LINE   =  0x02  ///< \ru Касание по образующей прямой (например два цилиндра с параллельными осями). \en Tangency by a generating line (for instance, two cylinders with parallel axes). 
  , GCM_TAN_CIRCLE =  0x04  ///< \ru Касание по окружности (например сфера в конусе). \en Tangency by a circle (for instance, a sphere inside a cone).
} GCM_tan_choice;


//----------------------------------------------------------------------------------------
/** \brief  \ru Диагностические коды 3d-решателя. \en Diagnostic codes of 3D-solver. \~
    \details \ru GCM_result перечисляет значения, возвращаемые вызовами API компонента GCM, 
  включая диагностические коды решения геометрических ограничений. Значения данного типа 
  возвращаются такими функциями, как GCM_Evaluate и GCM_EvaluationResult.
             \en GCM_result enumerates the values returned by the GCM API calls including 
  the diagnostic codes of solving geometric constraints. Values of this type are returned 
  by functions such as GCM_Evaluate and GCM_EvaluationResult.
    \note \ru Значения этого перечисления могут быть использованы для постоянного
              хранения данных приложения и останутся неизменными в следующих версиях.
          \en Values of this enum can be used for permanent storage of app data and will 
              be kept in the future versions. \~
*/
//---
typedef enum
{
    GCM_RESULT_None = 0                     ///< \ru  Код неопределенного результата или состояния. \en Code of undefined result or status. \~
  , GCM_RESULT_Ok   = 1                     ///< \ru  Успешный результат вызова API компонента GCM. \en The successful result of GCM API call. \~
  , GCM_RESULT_Satisfied = GCM_RESULT_Ok    ///< \ru  Ограничение или система ограничения решены. \en Constraint or system of constraints are fulfilled. \~
  , GCM_RESULT_Overconstrained = 2          ///< \ru  Ограничение переопределяет систему и противоречит другим условиям. \en Constraint is redundant and contradicts the other conditions. \~
  , GCM_RESULT_MatedFixation = 3            ///< \ru  Заданы ограничения для пары фиксированных объектов. \en Constraints are specified for pair of fixed objects. \~
  , GCM_RESULT_DraggingFailed = 4           ///< \ru  Неудачная попытка перемещения фиксированного объекта (равно, как объекта жестко-связанного с фиксированным). \en Failed attempt to move a fixed object (as the object rigidly connected with fixed). \~
  , GCM_RESULT_Not_Satisfied = 5            ///< \ru  Ограничение(я) не решено (по неизвестным причинам). \en Constraint(s) has not been solved (for unknown reasons). \~   
  , GCM_RESULT_Unsolvable = 6               ///< \ru  Ограничение(я) не разрешимо. \en Constraint(s) is not solvable. \~

  /**
    \brief \ru Ограничение GCM_DEPENDENT не вычислено или ее независимые аргументы находятся вне области решений.
           \en The GCM_DEPENDENT constraint is not solved or its independent arguments are out of the solution domain.
    \note  \ru Ситуация возникает, когда функция GCM_dependent_func возвращает false.
           \en The situation occurs when the GCM_dependent_func function returns false.
  */
  , GCM_RESULT_DependentConstraintUnsolved = 7
  , GCM_RESULT_Error = 8                    ///< \ru  Неизвестная ошибка, как правило, не связанная с процессом решения. \en  Unknown error is usually not related to the solving. \~  
  , GCM_RESULT_InappropriateAlignment = 9   ///< \ru  Опция выравнивания не подходит для данного типа ограничения. \en The alignment option is inappropriate to a given constraint type. \~
  , GCM_RESULT_InappropriateArgument = 10   ///< \ru  Геометрический тип аргумента не подходит для данного ограничения. \en Geometric type of an argument is inappropriate to the constraint. \~

  /*
    Additional message codes.
  */

  , GCM_RESULT_IncompatibleArguments = 3001   ///< \ru Несовместные типы аргументов ограничения. \en  Inconsistent types of constraint arguments. \~  
  , GCM_RESULT_InconsistentAngleType          ///< \ru Угловая опция несовместима со степенью свободы соединения (планарный тип угла применим только для соединения, оставляющего единственную степень свободы вращения). \en  Angular option is inconsistent with the degree of freedom of the joint (planar type of angle is only applicable for the joint leaving only one degree of freedom of rotation); \~
  , GCM_RESULT_InconsistentAlignment          ///< \ru Величина ориентации несовместна с другими сопряжениями. \en The orientation value is inconsistent with other mates. \~
  , GCM_RESULT_Duplicated                     ///< \ru Ограничение дублирует другое. \en Constraint duplicates another.
  , GCM_RESULT_CyclicDependence               ///< \ru Неразрешимая циклическая зависимость. \en Unsolvable cyclic dependence.
  , GCM_RESULT_MultiDependedGeom              ///< \ru Объект является зависимым от двух и более ограничений 'GCM_DEPENDED'. \en A geometric object is dependent on two or more constraints of 'GCM_DEPENDED' type.
  , GCM_RESULT_OverconstrainingDependedGeoms  ///< \ru Избыточное ограничение между зависимыми объектами. \en A redundancy constraint between depended geoms. \~  
  , GCM_RESULT_DependedGeomCantBeFixed        ///< \ru Зависимый аргумент ограничения 'GCM_DEPENDED' не может быть зафиксирован. \en The depended argument of 'GCM_DEPENDED' can't be fixed.  
  , GCM_RESULT_InvalidArguments               ///< \ru  В ограничении не заданы аргументы (пустые аргументы). \en Constraint has invalid or undefined (void) arguments.
  , mtResCode_UnsupportedTangencyChoice       ///< \ru  Для сопряжения касание - опция выбора по окружности или по образующей не поддреживается \en  For mate the option of tangency choice by circle or generating curve is unsupported.
  , mtResCode_IsNoPossibleForCircTanChoice    ///< \ru  Для данной пары поверхностей касание по окружности геометрически не возможно \en  For a given pair of surfaces the touching along the circle is geometrically impossible.
  , mtResCode_CoaxialMtGearTransmissionIsNotAvalable  ///< \ru Механическая передача вращения компонентов с совпадающими осями не поддерживается \en Mechanical transmission of components rotation with the same axis is not supported 
  , mtResCode_NoSeparatedSolutionForCamGear           ///< \ru В сборке присутствуют сопряжения (геометрические условия), создающие зависимость движения толкателя от движения кулачка, помимо самого кулачкового механизма \en The assembly contains mates (geometric conditions) creating dependence of the motion of the pusher from the motion of cam in addition to the cam gear 
  , mtResCode_CyclicDependenceForTwoOrMoreCamGears    ///< \ru Задана циклическая зависимость для двух или более кулачковых механизмов \en Given the cyclic dependence for two or more cam gears 
  , mtResCode_InconsistentFollowerAxis                ///< \ru Заданные сопряжения для толкателя не соответствую его оси движения \en Given mates for pusher doesn't correspond to its motion axis 
  , GCM_RESULT_InconsistentPlanarAngle                ///< \ru Не соблюдаются условия планарного угла (векторы сторон угла должны быть перпендикулярны оси). \en Planar angle conditions are not met (vectors from the sides of angle should be perpendicular to the axis).
  /*    
    ATTENTION: New error messages should be added only before this line.
  */

  /*
    \ru Сообщения о некорректных результатах вызовов API решателя (не вычислительные). 
    \en Messages about incorrect results of the solver API calls (not computational). \~
  */
  , GCM_RESULT_ItsNotDrivingDimension ///< \ru Данное ограничение должно быть управляющим размером. \en Given constraint should be a driving dimension.
  , GCM_RESULT_Unregistered           ///< \ru Обращение к недействительному объекту. \en Access to invalid object. 
  , GCM_RESULT_InternalError
  , GCM_RESULT_Aborted  ///< \ru Процесс вычислений был прерван по запросу приложения. \en The evaluation process aborted by the application. \~
  , GCM_RESULT_Last_    // The last error code of user for mates (adding before this line)
} GCM_result;

//----------------------------------------------------------------------------------------
/// \ru Характер зависимости пары тел (geoms) \en Dependency character of solid pair (geoms)
// ---
typedef enum 
{
    GCM_NO_DEPENDENCY = 0 ///< \ru Нет односторонней зависимости. \en It means no one-directed dependency.
  , GCM_1ST_DEPENDENT = 2 ///< \ru Первый объект зависит от другого(других). \en The first object is dependent on the other(s).  
  , GCM_2ND_DEPENDENT = 1 ///< \ru Второй объект зависит от другого(других). \en The second object is dependent on the other(s).
} GCM_dependency;

//----------------------------------------------------------------------------------------
/// \ru Тип связи между элементами в паттерне. \en The type of relationship between elements in the pattern.
// ---
typedef enum
{
  GCM_NO_SCALE = 0,
  GCM_RIGID = 1,        ///< \ru Шаг между элементами константен. Паттерн не масштабируется (не растягивается). \en Distance between elements is constant. The pattern is not scaled.
  GCM_LINEAR_SCALE = 2  ///< \ru Шаг между элементами линейно масштабируется при растяжениях. \en Distance between elements is linearly scaled when stretching.
} GCM_scale;

//----------------------------------------------------------------------------------------
/**
  \brief  \ru Режим поведения при манипулировании недоопределенной системой.
          \en Mode of the behavior when manipulating the undeconstrained system. \~
*/
// ---
typedef enum  
{
  /*
    Произвольное поведение (arbitrary behavior).
  */
    GCM_REPOSITION_FreeRotation ///< \ru Произвольная репозиция с преимуществом вращения. \en Arbitrary reposition with predominant rotation.
  , GCM_REPOSITION_FreeMoving   ///< \ru Произвольная репозиция с преимуществом перемещения. \en Arbitrary reposition with predominant moving.
  
  /*
    Строгое поведение (strict behavior).
  */
  , GCM_REPOSITION_Dragging   ///< \ru Перетаскивание в плоскости "экрана". \en Dragging in the plane of the screen.
  , GCM_REPOSITION_Rotation   ///< \ru Вращение вокруг неподвижной оси. \en Rotation around fixed axis.

  /** \brief \ru Перенос только для одного твердого тела. \en Shift only one solid.
      \note \ru Этот режим был задуман для процессов вставки нового тела в сборку САПР.
            \en This mode have been intended for insertion processes of a new solid in the CAD assembly.
  */
  , GCM_REPOSITION_Transfer
  
} GCM_reposition;

//----------------------------------------------------------------------------------------
/// \ru Координаты 3D-вектора. \en Coordinates of 3D-vector.
//---
struct GCM_vec3d { double x, y, z; };

//----------------------------------------------------------------------------------------
/// \ru Координаты точки 3D пространства. \en Coordinates of point in three-dimensional space.
//---
struct GCM_point { double x, y, z; };

//----------------------------------------------------------------------------------------
/** \brief  \ru Структура полей данных, представляющих геометрический объект.
            \en Structure of data fields representing a geometric object. \~
  \details  \ru Эта простая структура данных представляет варианты геометрических типов, 
                с которыми работает решатель.\n
            \en This plain data structure represents variants of geometric data types that 
                the solver works with.\n 
            \~
  \par
  \ru Кортежи, соответствующие типам геометрии:\n
  \en Corresponding tuples of geometric types:\n

  \~ { GCM_POINT    origin } - simple point;\n
     { GCM_SPHERE   origin radiusA } - center and radius of a sphere;\n
     { GCM_LINE     origin axisZ } - point and direction of a line;\n
     { GCM_PLANE    origin axisZ } - point and normal of a plane;\n     
     { GCM_CIRCLE   origin axisZ radiusA } - center, rotation axis and radius;\n
     { GCM_CYLINDER origin axisZ radiusA } - center, rotation axis and radius;\n
     { GCM_CONE     origin axisZ radiusA radiusB } - center, rotation axis and two radiuses;\n
     { GCM_TORUS    origin axisZ radiusA radiusB };\n
     { GCM_LCS      origin axisZ axisX axisY } - local coordinate system that specify a solid position.\n
*/
//---
struct GCM_g_record
{
  GCM_g_type  type;     ///< \ru Тип геометрии. \en Type of geometric object.
  GCM_point   origin;   ///< \ru Точка позиционирования геометрического объекта. \en Location of a geometric object.
  GCM_vec3d   axisZ;    ///< \ru Направляющий вектор прямой или вектор нормали плоскости. \en Direction of line, normal of plane, Z-axis of a local coordinate frame.
  GCM_vec3d   axisX;    ///< \ru Ось X локальной системы координат. \en X-axis of local coordinate frame .
  GCM_vec3d   axisY;    ///< \ru Ось Y локальной системы координат. \en Y-axis of local coordinate frame.
  double      radiusA;  ///< \ru Радиус окружности, сферы или цилиндра либо радиус основания конуса, "большой" радиус тора. \en Radius of circle, sphere and cylinder or major radius of cone and torus.
  double      radiusB;  ///< \ru "Малый" радиус тора или конуса. \en Minor radius of cone and torus.
};

//----------------------------------------------------------------------------------------
/** \brief  \ru Дополнительный параметр для функций типа #GCM_dependent_func.
            \en Additional parameter for functions of type #GCM_dependent_func. \~
    \sa #GCM_dependent_geom_func, #GCM_dependent_func
*/
//---
struct GCM_extra_param
{
  size_t  funcId;   // integral identifier of a user-defined callback
  void *  funcData; // pointer to an application data structure
  GCM_extra_param() { funcId = 0, funcData = 0; }
};

//----------------------------------------------------------------------------------------
// The function calculates position of a dependent geom regarding to other independent geoms.
/*
  Note: The dependent geom is first element of argument list inGeoms, and others are independent.
  argNb Number of arguments of dependency constraint, equals to size of inGeoms.
  g1 = f( g2 g3 ... gn );
*/
//---
typedef bool (*GCM_dependent_func) ( MbPlacement3D   gPlaces[]
                                   , size_t          gPlacesSize
                                   , GCM_extra_param exPar );

//----------------------------------------------------------------------------------------
/// \~ Alternative typename of #GCM_dependent_func
//---                                        
typedef GCM_dependent_func GCM_dependent_geom_func;

/** \} */ // GCM_3D_API

//----------------------------------------------------------------------------------------
// Argument of constraint to record in type 'GCM_c_record'
//--
struct GCM_c_arg
{
  union
  {    
    GCM_object      geom;       // Geometric object.
    GCM_alignment   alignVal;   // Variant of alignment.
    GCM_tan_choice  tanChoice;  // Option for tangency constraint only.
    GCM_angle_type  angType;    // Option for angular constraint only.
    GCM_scale       scale;      // Option for pattern constraint only.
    double          dimValue;   // Numeric value of a dimension.
    int             enumVal;
  };  
  GCM_c_arg & operator = ( double val )
  { 
    dimValue = val;
    return *this; 
  }
  template<class _Enum>
  GCM_c_arg & operator = ( const _Enum & val )
  { 
    enumVal = static_cast<int>( val );
    return *this; 
  }
  GCM_c_arg & operator = ( const GCM_geom & gId ) 
  {
    geom = gId;
    return *this;
  }
  GCM_c_arg() { dimValue = 0.0; }
};

//----------------------------------------------------------------------------------------
/** \brief  \en Structure of geometric constraint record.
            \ru Структура записи геометрического ограничения. \~
*/
/*
  The argument tuples of each constraint type:
  { GCM_c_type          GCM_c_arg  ...    GCM_c_arg }
  -------------------|-------------------------------
  { GCM_COINCIDENT      GCM_geom GCM_geom GCM_alignment }
  { GCM_CONCENTRIC      GCM_geom GCM_geom GCM_alignment }
  { GCM_PARALLEL        GCM_geom GCM_geom GCM_alignment }
  { GCM_PERPENDICULAR   GCM_geom GCM_geom GCM_alignment }  
  { GCM_IN_PLACE        GCM_geom GCM_geom GCM_NO_ALIGNMENT }
  { GCM_DISTANCE        GCM_geom GCM_geom double GCM_alignment }
  { GCM_TANGENT         GCM_geom GCM_geom GCM_alignment GCM_tan_choice }
  { GCM_ANGLE           GCM_geom GCM_geom GCM_geom double GCM_alignment } - planar kind of angle
  { GCM_ANGLE           GCM_geom GCM_geom GCM_NULL double GCM_alignment } - 3d kind of angle  
  { GCM_SYMMETRIC       GCM_geom GCM_geom GCM_geom GCM_alignment }
  { GCM_PATTERNED       GCM_geom GCM_geom GCM_geom double GCM_alignment GCM_scale }
  { GCM_LINEAR_PATTERN  GCM_geom GCM_geom GCM_geom GCM_alignment }
  { GCM_ANGULAR_PATTERN GCM_geom GCM_geom GCM_geom GCM_alignment }
  { GCM_TRANSMITTION    not specified }
  { GCM_CAM_MECHANISM   not specified }
  { GCM_RADIUS          GCM_geom double }
  { GCM_UNKNOWN }
  Sample of the journal line: (GCM_AddConstraint (GCM_COINCIDENT #1 #2 GCM_CLOSEST) #3)
*/
struct GCM_c_record
{
  static const size_t argsN = 5;
  GCM_c_type type;        // \ru Тип ограничения. \en Type of constraint.
  GCM_c_arg  args[argsN]; // \ru Аргументы ограничения. \en Arguments of constraint.
};

#if ( GCM_ID_TYPE == 1 )

inline bool operator == ( const MtObjectId & f, const MtObjectId & s ) { return f.id == s.id; }
inline bool operator != ( const MtObjectId & f, const MtObjectId & s ) { return f.id != s.id; }
inline bool operator <  ( const MtObjectId & f, const MtObjectId & s ) { return f.id < s.id;  }
inline       uint32 & _id( MtObjectId & obj ) { return obj.id; }
inline const uint32 & _id( const MtObjectId & obj ) { return obj.id; }

#else // GCM_ID_TYPE

inline       uint32 & _id( MtObjectId & obj ) { return obj; }
inline const uint32 & _id( const MtObjectId & obj ) { return obj; }

#endif // GCM_ID_TYPE

typedef GCM_alignment MtAlignType;
typedef GCM_g_type    MtGeometryType;
typedef GCM_result    MtResultCode3D;

/*
  The constants below are deprecated (2015)
*/

static const GCM_alignment GCM_NOT_ORIENTED = GCM_NO_ALIGNMENT;
static const GCM_alignment GCM_Opposite   = GCM_OPPOSITE;
static const GCM_alignment GCM_Closest    = GCM_CLOSEST;
static const GCM_alignment GCM_Cooriented = GCM_COORIENTED;
static const GCM_alignment GCM_None = GCM_NO_ALIGNMENT;
static const GCM_alignment GCM_Min  = GCM_OPPOSITE;
static const GCM_alignment GCM_Max  = GCM_MAX_ALIGNMENT;

static const GCM_g_type GCM_FIRST_GTYPE   = GCM_NULL_GTYPE;
static const GCM_g_type mgt_Cylinder      = GCM_CYLINDER;
static const GCM_c_type mct_Coincidence   = GCM_COINCIDENT;
static const GCM_c_type mct_Parallel      = GCM_PARALLEL;
static const GCM_c_type mct_Perpendicular = GCM_PERPENDICULAR;  
static const GCM_c_type mct_Tangency      = GCM_TANGENT;
static const GCM_c_type mct_Concentric    = GCM_CONCENTRIC;
static const GCM_c_type mct_Distance      = GCM_DISTANCE;
static const GCM_c_type mct_Angle         = GCM_ANGLE;  
static const GCM_c_type mct_InPlace       = GCM_IN_PLACE;
static const GCM_c_type mct_Unknown       = GCM_UNKNOWN;
static const GCM_c_type mct_CamMechanism  = GCM_CAM_MECHANISM;
static const GCM_c_type mct_Symmetry      = GCM_SYMMETRIC; 
static const GCM_c_type mct_Symmetric     = GCM_SYMMETRIC;
static const GCM_c_type mct_Parallelism   = GCM_PARALLEL;

static const GCM_result mtResCode_None        = GCM_RESULT_None;
static const GCM_result mtResCode_Ok          = GCM_RESULT_Ok;
static const GCM_result mtResCode_Satisfied   = GCM_RESULT_Ok;
static const GCM_result mtResCode_SystemError = GCM_RESULT_Error;
static const GCM_result mtResCode_Error       = GCM_RESULT_Error;
static const GCM_result mtResCode_Overconstrained   = GCM_RESULT_Overconstrained;
static const GCM_result mtResCode_Not_Satisfied     = GCM_RESULT_Not_Satisfied;
static const GCM_result mtResCode_MovingOfFixedGeom = GCM_RESULT_DraggingFailed;
static const GCM_result mtResCode_InvalidAxisOfPlanarAngle = GCM_RESULT_InconsistentPlanarAngle;
static const GCM_result mtResCode_CyclicDependence = GCM_RESULT_CyclicDependence;
static const GCM_result mtResCode_InvalidDependenceForOutGeom  = GCM_RESULT_MultiDependedGeom;
static const GCM_result mtResCode_InvalidDependenceForOutGeoms = GCM_RESULT_OverconstrainingDependedGeoms; // (2018)
static const GCM_result mtResCode_InvalidDependenceForFixGeom  = GCM_RESULT_DependedGeomCantBeFixed;

const GCM_dependency GCM_2ST_DEPENDENT = GCM_2ND_DEPENDENT;

/*
  Deprecated names of a dynamic reposition modes (2019)
*/
const GCM_reposition rep_FreeRotation   = GCM_REPOSITION_FreeRotation;
const GCM_reposition rep_FreeMoving     = GCM_REPOSITION_FreeMoving;
const GCM_reposition rep_MovingToPoint  = GCM_REPOSITION_Dragging;
const GCM_reposition rep_RotationAboutAxis   = GCM_REPOSITION_Rotation;
const GCM_reposition rep_TransferOneGeomOnly = GCM_REPOSITION_Transfer;


#endif

// eof
