////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Константы и переменные.
         \en Constants and variables. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MB_VARIABLES_H
#define __MB_VARIABLES_H

#include <math_define.h>
#include <tool_uuid.h>
#include <tool_multithreading.h>
#include <iostream>


/** \ru \name Общие константы
    \en \name Common constants
    \{ */
#define   MB_MAXDOUBLE      (1.0E+300) ///< \ru Максимальное значение double 1.7976931348623158E+308. \en Maximum value of double 1.7976931348623158E+308. 
#define   MB_MINDOUBLE      (1.0E-300) ///< \ru Минимальное значение double  2.2250738585072014E-308. \en Minimum value of double  2.2250738585072014E-308. 

// \ru Математические константы, округленные до 21 значащей цифры, определены в math.h \en Mathematical constants rounded to 21 significant digits, defined in math.h  
#if !defined( _MATH_DEFINES_DEFINED )
#ifdef C3D_WINDOWS// _MSC_VER // \ru Константы определены в math.h [Linux] \en Constants defined in math.h [Linux] 
#define   M_E               2.71828182845904523536  ///< \ru Экспонента. \en Exponent. 
#define   M_LOG2E           1.44269504088896340736  ///< \ru Логарифм M_E по основанию 2. \en Logarithm M_E to base 2. 
#define   M_LOG10E          0.434294481903251827651 ///< \ru Логарифм M_E по основанию 10. \en Logarithm M_E to base 10. 
#define   M_LN2             0.693147180559945309417 ///< \ru Натуральный логарифм 2. \en Natural logarithm 2. 
#define   M_PI_4            0.785398163397448309616 ///< M_PI / 4.0
#define   M_1_PI            0.318309886183790671538 ///< 1.0 / M_PI
#define   M_2_PI            0.636619772367581343076 ///< 2.0 / M_PI
#define   M_SQRT1_2         0.707106781186547524401 ///< \ru Корень из одной второй, sqrt(1/2). \en Root of one half, sqrt(1/2). 
#else // C3D_WINDOWS
  #ifndef   M_E 
    #define   M_E               2.71828182845904523536  ///< \ru Экспонента. \en Exponent. 
  #endif //  M_E
  #ifndef   M_LOG2E
    #define   M_LOG2E           1.44269504088896340736  ///< \ru Логарифм M_E по основанию 2. \en Logarithm M_E to base 2. 
  #endif //  M_LOG2E
  #ifndef   M_LOG10E
    #define   M_LOG10E          0.434294481903251827651 ///< \ru Логарифм M_E по основанию 10. \en Logarithm M_E to base 10. 
  #endif //  M_LOG10E
  #ifndef   M_LN2
    #define   M_LN2             0.693147180559945309417 ///< \ru Натуральный логарифм 2. \en Natural logarithm 2. 
  #endif //  M_LN2
  #ifndef   M_PI_4
    #define   M_PI_4            0.785398163397448309616 ///< M_PI / 4.0
  #endif //   M_PI_4
  #ifndef  M_1_PI
    #define   M_1_PI            0.318309886183790671538 ///< 1.0 / M_PI
  #endif //  M_1_PI
  #ifndef   M_2_PI 
    #define   M_2_PI            0.636619772367581343076 ///< 2.0 / M_PI
  #endif //  M_2_PI 
  #ifndef  M_SQRT1_2
    #define   M_SQRT1_2         0.707106781186547524401 ///< \ru Корень из одной второй, sqrt(1/2). \en Root of one half, sqrt(1/2). 
  #endif //  M_SQRT1_2
#endif // C3D_WINDOWS
#ifndef M_LN10
  #define   M_LN10            2.30258509299404568402  ///< \ru Натуральный логарифм 10, ln(10). \en Natural logarithm 10, ln(10).
#endif
#ifndef M_PI
  #define   M_PI              3.14159265358979323846  ///< \ru Отношение длины окружности к её диаметру, pi. \en Relation between circle length and its diameter, pi.
#endif
#ifndef M_PI_2
  #define   M_PI_2            1.57079632679489661923  ///< M_PI / 2.0
#endif
#ifndef M_2_SQRTPI
  #define   M_2_SQRTPI        1.12837916709551257390  ///< \ru Два разделить на корень из числа пи, 2/sqrt(pi). \en Two divided by root of pi, 2/sqrt(pi).
#endif
#ifndef M_SQRT2
  #define   M_SQRT2           1.41421356237309504880  ///< \ru Корень из двух, sqrt(2). \en Root of two, sqrt(2).
#endif
#endif // _MATH_DEFINES_DEFINED
#define   M_1_SQRTPI        0.564189583547756286948 ///< \ru Единица, деленная на корень из числа пи, 1/sqrt(pi). \en One divided by root of pi, 1/sqrt(pi). 
#define   M_PI2             (M_PI*2.0)              ///< \ru Отношение длины окружности к её радиусу, 2.0 * M_PI, 6.28318530717958647692 \en Relation between circle length and its radius, 2.0 * M_PI, 6.28318530717958647692 
#define   M_DEGRAD          (M_PI/180.0)            ///< \ru Коэффициент перевода градусов в радианы. \en Factor of conversion from degrees to radians. 
#define   M_RADDEG          (180.0/M_PI)            ///< \ru Коэффициент перевода радиан в градусы. \en Factor of conversion from radians to degrees. 
#define   M_FI              1.61803398874989484     ///< \ru Число золотого сечения, 1/M_FI = 0.6180339887499. \en Golden ratio, 1/M_FI = 0.6180339887499. 
#define   MM_INCH           25.4                    ///< \ru Количество миллиметров в дюйме. \en Millimeters per inch. 


#define   EPSILON           1E-10 ///< \ru Погрешность. \en Tolerance. 
#define   MAXIMON           1E+10 ///< \ru 10 в 10-й степени. \en 10 to the power of 10. 
#define   MAX_OVERALL_DIM   1E+12 ///< \ru Максимальное значение габарита. \en Maximal value of bounding box. 

#define   DETERMINANT_MAX   1E+137 ///< \ru Максимальная величина. \en Maximal value. 
#define   DETERMINANT_MIN   1E-171 ///< \ru Минимальная величина. \en Minimal value. 

#define   UNDEFINED_DBL    -MB_MAXDOUBLE ///< \ru Неопределенный double. \en Undefined double. 
#define   UNDEFINED_INT_T   SYS_MIN_ST   ///< \ru Неопределенный int. \en Undefined int. 

#define   DEVIATION_SAG     M_PI * 0.04  ///< \ru Угловая толерантность. \en Angular tolerance. 

#define   NULL_EPSILON      1E-30 ///< \ru Погрешность для проверки на равенство нулю. \en Tolerance for equality to zero. 
#define   NULL_REGION       1E-20 ///< \ru Погрешность для проверки на равенство нулю. \en Tolerance for equality to zero. 

#define   DOUBLE_EPSILON    1E-16 ///< \ru Погрешность. \en Tolerance. 
#define   DOUBLE_REGION     1E-15 ///< \ru Погрешность. \en Tolerance. 
#define   EXTENT_EQUAL      1E-14 ///< \ru Погрешность. \en Tolerance. 
#define   EXTENT_EPSILON    1E-12 ///< \ru Погрешность. \en Tolerance. 
#define   EXTENT_REGION     1E-11 ///< \ru Погрешность. \en Tolerance. 
#define   LENGTH_EPSILON    1E-10 ///< \ru Погрешность длины. \en Tolerance for length. 
#define   LENGTH_REGION     1E-9  ///< \ru Погрешность региона. \en Tolerance for region. 

#define   METRIC_EPSILON    1E-8  ///< \ru Погрешность расстояния в итерационных функциях. \en Tolerance for distance in iterative functions. 
#define   METRIC_REGION     1E-7  ///< \ru Неразличимая метрическая область. \en Indistinguishable metric region. 
#define   METRIC_PRECISION  1E-6  ///< \ru Метрическая погрешность. \en Metric tolerance. 
#define   METRIC_ACCURACY   1E-5  ///< \ru Наибольшая метрическая погрешность (абсолютная точность в мм ("размер" атома 5e-8 мм)). \en The largest metric tolerance (absolute tolerance expressed in mm ("size" of atom is 5e-8 mm)). 
#define   METRIC_NEAR       1E-4  ///< \ru Метрическая близость. \en Metric proximity tolerance. 

#define   PARAM_EPSILON     1E-8  ///< \ru Погрешность параметра в итерационных функциях. \en Tolerance for parameter in iterative functions. 
#define   PARAM_REGION      1E-7  ///< \ru Неразличимая параметрическая область. \en Indistinguishable parametric region. 
#define   PARAM_PRECISION   1E-6  ///< \ru Параметрическая погрешность. \en Parametric tolerance. 
#define   PARAM_ACCURACY    1E-5  ///< \ru Наибольшая параметрическая погрешность. \en The largest parametric tolerance. 
#define   PARAM_NEAR        1E-4  ///< \ru Параметрическая близость. \en Parametric proximity. 

#define   ANGLE_EPSILON     PARAM_EPSILON*M_PI ///< \ru Погрешность угла. \en Angular tolerance. 
#define   ANGLE_REGION      ANGLE_EPSILON*40   ///< \ru Погрешность угла, при которой углы считаются равными. \en Angular tolerance for equality of angles. 

#define   FAIR_MAX_DEGREE   11 ///< \ru Максимальный порядок NURBS при аппроксимации. \en Maxinum degree of the NURBS approximation. 


namespace c3d // namespace C3D
{

const double  METRIC_DELTA    = 0.05;    ///< \ru Величина отшагивания. \en Metric offset. 
const double  PARAM_DELTA_MIN = 0.005;   ///< \ru Минимальная  доля приращения параметра. \en Minimal portion of parameter increment. 
const double  PARAM_DELTA_MAX = 1.0;     ///< \ru Максимальная доля приращения параметра. \en Maximal portion of parameter increment. 

const double  MIN_LENGTH      = 1.0E-4;  ///< \ru Минимальная  длина объекта. \en Minimal object length. 
const double  MAX_LENGTH      = 5.0E+7;  ///< \ru Максимальная длина объекта. \en Maximal object length. 
const double  MIN_RADIUS      = 1.0E-4;  ///< \ru Минимальный  радиус объекта. \en Minimal object radius. 
const double  MAX_RADIUS      = 2.5E+7;  ///< \ru Максимальный радиус объекта. \en Maximal object radius. 

const double  DELTA_MIN       = 1E-3; ///< \ru Коэффициент уменьшения. \en Reduction factor. 
const double  DELTA_MID       = 1E-2; ///< \ru Коэффициент уменьшения. \en Reduction factor. 
const double  DELTA_MOD       = 1E-1; ///< \ru Коэффициент уменьшения. \en Reduction factor. 
const double  DELTA_MAX       = 1E+3; ///< \ru Коэффициент увеличения. \en Magnification factor. 
const double  POWER_1         = 1E+1; ///< \ru Коэффициент увеличения. \en Magnification factor. 
const double  POWER_2         = 1E+2; ///< \ru Коэффициент увеличения. \en Magnification factor. 
const double  POWER_3         = 1E+3; ///< \ru Коэффициент увеличения. \en Magnification factor. 
const double  POWER_4         = 1E+4; ///< \ru Коэффициент увеличения. \en Magnification factor. 
const double  POWER_5         = 1E+5; ///< \ru Коэффициент увеличения. \en Magnification factor. 

const double  ONE_THIRD       = 0.33333333333333333333;  ///< 1/3.
const double  TWO_THIRD       = 0.66666666666666666666;  ///< 2/3.
const double  ONE_SIXTH       = 0.166666666666666666667; ///< 1/6.
const double  ONE_FIFTH       = 0.2;                     ///< 1/5.
const double  TWO_FIFTH       = 0.4;                     ///< 2/5.
const double  ONE_QUARTER     = 0.25;                    ///< 1/4.
const double  ONE_EIGHTH      = 0.125;                   ///< 1/8.
const double  ONE_HALF        = 0.5;                     ///< 1/2.

// \ru Способы построения поверхности сопряжения (скругления или фаски). \en Ways for construction of smooth surface (fillet or chamfer). 
const double  _CONIC_MIN_     = 0.05; ///< \ru Минимальный  коэффициент полноты сечения поверхности сопряжения (при 0.5 - парабола, меньше - эллипс). \en Minimum factor of smooth surface section completeness (0.5 for parabola, less for ellipse).  
const double  _CONIC_MAX_     = 0.95; ///< \ru Максимальный коэффициент полноты сечения поверхности сопряжения (при 0.5 - парабола, больше - гипербола). \en Maximum factor of smooth surface section completeness (0.5 for parabola, greater for hyperbola). 
const double  _ARC_           = 0.0;  ///< \ru Коэффициент полноты сечения поверхности скругления при u = const соответствует дуге окружности. \en Factor of smooth surface section completeness in case of u = const corresponds to circle arc. 

const int32   TEN             =   10; ///< \ru Число 10. \en Number 10. 
const int32   TWENTY          =   20; ///< \ru Число 20. \en Number 20. 
const int32   TESSERA_MAX     = 4000; ///< \ru Максимальное количество ячеек в строке и ряду триангуляционной сетки. \en Maximum count of cell in rows and columns for triangulation grid. 
const int32   COUNT_MAX       =  512; ///< \ru Коэффициент увеличения. \en Magnification factor. 
const int32   COUNT_MID       =  256; ///< \ru Коэффициент увеличения. \en Magnification factor. 
const int32   COUNT_MIN       =  128; ///< \ru Коэффициент увеличения. \en Magnification factor. 
const int32   COUNT_BIN       =   64; ///< \ru Уровень вложенности. \en Inclusion level. 
const int32   WIRE_MAX        =  256; ///< \ru Максимальное количество линий отрисовочной сетки. \en The maximum number of mesh lines. 

const int32   ITERATE_COUNT   =   16; ///< \ru Число приближений в итерационном методе. \en Number of approximations in iterative method. 
const int32   ITERATE_LIMIT   =   32; ///< \ru Количество итераций для построения касательных окружностей. \en Count of iterations for construction of tangent circles. 

const int32   NEWTON_COUNT    =    8; ///< \ru Число приближений в итерационном методе. \en Number of approximations in iterative method. 
const int32   NEWTON_COUNT_2X =   16; ///< \ru Число приближений в итерационном методе. \en Number of approximations in iterative method. 
const int32   NEWTON_COUNT_3X =   24; ///< \ru Число приближений в итерационном методе. \en Number of approximations in iterative method. 
const int32   NEWTON_COUNT_4X =   32; ///< \ru Число приближений в итерационном методе. \en Number of approximations in iterative method. 
const int32   NEWTON_COUNT_8X =   64; ///< \ru Число приближений в итерационном методе. \en Number of approximations in iterative method. 

const int32   LIMIT_COUNT     =    4; ///< \ru Число приближений в итерационном методе. \en Number of approximations in iterative method. 
const int32   COUNT_DELTA     =   10; ///< \ru Коэффициент увеличения или уменьшения. \en Reduction or magnification factor. 
const int32   COUNT_DELTA_2X  =   20; ///< \ru Коэффициент увеличения или уменьшения. \en Reduction or magnification factor. 
const int32   ITEMS_COUNT     =   12; ///< \ru Число точек в шаговом методе. \en Number of points in step method. 

const int32   BEZIER_DEGREE   =    4; ///< \ru Порядок Безье-сплайна по умолчанию. \en Default degree of Bezier-spline. 
const int32   NURBS_DEGREE    =    4; ///< \ru Порядок NURBS по умолчанию. \en Degree of NURBS. 

const int32   NURBS_POINTS_COUNT      =   6; ///< \ru Число точек для NURBS по умолчанию для прямого редактирования. \en Default number of points for NURBS direct editing. 
const int32   NURBS_POINTS_MAX_COUNT  = 100; ///< \ru Максимальное число точек для NURBS по умолчанию для прямого редактирования. \en Default maximum number of points for NURBS direct editing. 
const int32   APPROX_POINTS_MUL_COEFF =   3; ///< \ru Коэффициент увеличения количества точек для метода наименьших квадратов. \en Factor of points count incrementing in method of least squares.  

const int32   SPACE_DIM       =    3;   ///< \ru Размерность 3D-пространства. \en Dimension of 3D space. 

const int32   TRT_FREE        =    0; ///< \ru Сопряжение отсутствует. \en No conjugation. 
const int32   TRT_TANGENT     =    1; ///< \ru Сопряжение по касательной. \en Tangent conjugation. 
const int32   TRT_NORMAL      =    2; ///< \ru Сопряжение по нормали. \en Normal conjugation. 


/** \ru \name Способ информирования о нарушении требований.~
    \en \name Assert violation notification.
*/
enum eAssertViolationNotify {
  avn_Mute,         ///< \ru Не сообщать о нарушении требований. \en Mute assert violations.
  avn_CERR,         ///< \ru Выводить сообщение в поток ошибок. \en Write message into error stream.
  avn_ASSERT        ///< \ru Обработка макросом ASSERT. \en ASSERT macro application.
};

} // namespace C3D


#define   MB_AMBIENT        0.4  ///< \ru Коэффициент рассеянного освещения (фон). \en Coefficient of backlighting. 
#define   MB_DIFFUSE        0.7  ///< \ru Коэффициент диффузного отражения. \en Coefficient of diffuse reflection. 
#define   MB_SPECULARITY    0.8  ///< \ru Коэффициент зеркального отражения. \en Coefficient of specular reflection. 
#define   MB_SHININESS     50.0  ///< \ru Блеск (показатель степени в законе зеркального отражения). \en Shininess (index according to the law of specular reflection). 
#define   MB_OPACITY        1.0  ///< \ru Коэффициент суммарного отражения (коэффициент непрозрачности). \en Coefficient of total reflection (opacity coefficient). 
#define   MB_EMISSION       0.0  ///< \ru Коэффициент излучения. \en Emissivity coefficient. 

#define   MB_DEFCOLOR       0x7F7F7F ///< \ru Цвет по умолчанию при импорте и экспорте (серый). \en Default color for import and export (grey). 
#define   MB_C3DCOLOR       0xFF7F00 ///< \ru Цвет по умолчанию для геометрических объектов. \en Default color for geometric objects. 

/// \ru Битовые флаги для матрицы и локальной системы координат. \en Bit flags for matrix and local coordinate system.  
#define   MB_IDENTITY       0x00 ///< \ru Единичная матрица. \en Identity. 
#define   MB_TRANSLATION    0x01 ///< \ru Присутствует смещение. \en Translation. 
#define   MB_ROTATION       0x02 ///< \ru Присутствует вращение. \en Rotation. 
#define   MB_SCALING        0x04 ///< \ru Присутствует масштабирование (компонент не 1.0). \en Scaling (factor is not equal to 1.0). 
#define   MB_REFLECTION     0x08 ///< \ru Присутствует зеркальная инверсия. \en Reflection. 
#define   MB_LEFT           0x08 ///< \ru Присутствует зеркальная инверсия (признак левой системы координат). \en Reflection (left coordinate system attribute). 
#define   MB_ORTOGONAL      0x10 ///< \ru Присутствует ортогональность, взводится только в случае аффинности. \en Orthogonality, is set up in case of affinity. 
#define   MB_AFFINE         0x20 ///< \ru Отсутствует ортогональность и нормированность (аффинное преобразование). \en Absence of orthogonality and normalization (affine transformation). 
#define   MB_PERSPECTIVE    0x40 ///< \ru Присутствует вектор перспективы (не нулевой). \en Vector of perspective (non-zero). 
#define   MB_UNSET          0x80 ///< \ru Битовые флаги не установлены. \en Bit flags not set. 

/** \} */


class MATH_CLASS MbRefItem;
class            VersionContainer;


//------------------------------------------------------------------------------
/** \brief \ru Общие статические данные алгоритмов и функций.
           \en Common static data of algorithms and functions. \~
  \details \ru Общие статические данные содержат константы, которые используются 
            в вычислениях как предельные величины. \n
            Статические данные не подлежат изменению. \n
           \en Common static data contains constants used 
            in computations as limit quantities. \n
            Static data cannot be changed. \n \~
  \ingroup Base_Items
*/
// ---
class MATH_CLASS Math {
public:
  // \ru Константы \en Constants 
  static const double PI2;          ///< \ru Отношение длины окружности к её радиусу. \en Relation between circle length and its radius. 
  static const double invPI2;       ///< \ru Отношение радиуса окружности к её длине. \en Relation between circle radius and its length. 
  static const double RADDEG;       ///< \ru Количество угловых градусов в радиане. \en Count of angular degrees in radian. 
  static const double DEGRAD;       ///< \ru Количество радиан в угловом градусе. \en Count of radians in angular degree. 

  static double doubleRegion;       ///< \ru Относительная погрешность double. \en Relative tolerance for double. 
  static double region;             ///< \ru Погрешность (PARAM_REGION). \en Tolerance (PARAM_REGION). 
  static double precision;          ///< \ru Погрешность аппроксимации (PARAM_PRECISION). \en Approximation tolerance (PARAM_PRECISION). 
  static double accuracy;           ///< \ru Погрешность (PARAM_ACCURACY). \en Tolerance (PARAM_ACCURACY). 

  static double determinantMax;     ///< \ru Максимально возможное значение определителя (DETERMINANT_MAX). \en Maximum possible value of determinant (DETERMINANT_MAX). 
  static double determinantMin;     ///< \ru Минимально возможное значение определителя (DETERMINANT_MIN). \en Minimum possible value of determinant (DETERMINANT_MIN). 

  static double LengthEps;          ///< \ru Точность вычисления длины (PARAM_PRECISION). \en Length calculation tolerance (PARAM_PRECISION). 
  static double AngleEps;           ///< \ru Точность вычисления угла. \en Angular tolerance. 
  static double NewtonEps;          ///< \ru Точность численного решения уравнений. \en Tolerance of numerical solution of equation. 
  static double NewtonReg;          ///< \ru Точность проверки решения уравнений. \en Solution of equation checking tolerance. 

  static double lengthEpsilon;      ///< \ru Погрешность длины. \en Tolerance for length. 
  static double lengthRegion;       ///< \ru Погрешность региона. \en Tolerance for region. 

  static double metricEpsilon;      ///< \ru Погрешность расстояния в итерационных функциях. \en Tolerance for distance in iterative functions. 
  static double metricRegion;       ///< \ru Неразличимая метрическая область. \en Indistinguishable metric region. 
  static double metricPrecision;    ///< \ru Метрическая погрешность. \en Metric tolerance. 
  static double metricAccuracy;     ///< \ru Наибольшая метрическая погрешность. \en Maximum metric tolerance. 
  static double metricNear;         ///< \ru Метрическая близость. \en Metric proximity tolerance. 

  static double paramEpsilon;       ///< \ru Точность параметра кривой. \en Curve parameter tolerance. 
  static double paramRegion;        ///< \ru Точность проверки параметра кривой. \en Curve parameter checking tolerance. 
  static double paramPrecision;     ///< \ru Параметрическая погрешность. \en Parametric tolerance. 
  static double paramAccuracy;      ///< \ru Наибольшая параметрическая погрешность. \en The largest parametric tolerance. 
  static double paramNear;          ///< \ru Параметрическая близость. \en Parametric proximity. 

  static double angleEpsilon;       ///< \ru Минимальная различимый угол. \en Minimum distinguishable angle. 
  static double angleRegion;        ///< \ru Неразличимая угловая область. \en Indistinguishable angular region. 

  static double lowRenderAng;       ///< \ru Угол для минимального количества отображаемых сегментов. \en Angle for minimum mapping segments count. 
  static double higRenderAng;       ///< \ru Угол для максимального количества отображаемых сегментов. \en Angle for maximum mapping segments count. 

  static double lengthMin;          ///< \ru Квадрат минимальной различимой длины. \en Square of minimum distinguishable length. 
  static double lengthMax;          ///< \ru Максимальная метрическая длина в системе. \en Maximum metric length in system. 

  static double deviateSag;         ///< \ru Угловая толерантность. \en Angular tolerance. 
  static double visualSag;          ///< \ru Величина стрелки прогиба для визуализации. \en Value of sag for visualization. 

  static double minLength;          ///< \ru Минимально  допустимая длина. \en Minimum legal length. 
  static double maxLength;          ///< \ru Максимально допустимая длина. \en Maximum legal length. 
  static double minRadius;          ///< \ru Минимально  допустимый радиус. \en Minimum legal radius. 
  static double maxRadius;          ///< \ru Максимально допустимый радиус. \en Maximum legal radius. 

  static double metricDelta;        ///< \ru Величина отшагивания. \en Metric offset. 
  static double paramDeltaMin;      ///< \ru Минимальное  приращение параметра. \en Minimum increment of parameter. 
  static double paramDeltaMax;      ///< \ru Максимальное приращение параметра. \en Maximum increment of parameter. 

  static double deltaMin;           ///< \ru Минимальное  приращение. \en Minimum increment. 
  static double deltaMax;           ///< \ru Максимальное приращение. \en Maximum increment. 

  static size_t newtonCount;        ///< \ru Число приближений в итерационном методе. \en Number of approximations in iterative method. 
  static size_t newtonLimit;        ///< \ru Количество итераций решения системы уравнений методом Newton. \en Iterations count for solving system of equations by Newton method. 
  static size_t curveDegree;        ///< \ru Порядок кривой (NURBS_DEGREE). \en Curve degree (NURBS_DEGREE). 
  static size_t uSurfaceDegree;     ///< \ru Порядок поверхности по U. \en Surface degree by U. 
  static size_t vSurfaceDegree;     ///< \ru Порядок поверхности по V. \en Surface degree by V. 

  static size_t tempIndex;          ///< \ru Временный коэффициент. \en Temporary coefficient. 
  static size_t nameIndex;          ///< \ru Индекс имени. \en Name index. 
  static size_t currentIndex;       ///< \ru Текущее имя. \en Current name. 
  static size_t mathState;          ///< \ru Состояние математического ядра. \en State of mathematical kernel. 


private:
  static const VersionContainer & defaultVersionContainer; ///< \ru Математическая версия по умолчанию. \en Default mathematical version.  

  static const MbUuid mathID;       ///< \ru Идентификатор ядра как приложения. \en Kernel ID.

  static bool   namesComplete;      ///< \ru Флаг полного именования объекта. \en Flag of object full naming. 
                                    ///< \ru Проименовать грани, рёбра, вершины оболочки после её создания (true) \en Name faces, edges, vertices of shell after creation (true) 
                                    ///< \ru Проименовать только грани оболочки после её создания (false) \en Name only faces of shell after creation (false) 
  static MbeMultithreadedMode multithreadedMode;  ///< \ru Флаг режима многопоточных вычислений (по умолчанию максимальный). \en Flag of multithreading mode (maximum by default).
                                    ///< \ru mtm_Off - Многопоточные вычисления отключены. \en Multithreading is off.
                                    ///< \ru mtm_Standard - Включена многопоточность ядра при обработке независимых объектов. \en Kernel multithreading is ON for independent objects.
                                    ///< \ru mtm_SafeItems - Обеспечивается потокобезопасность объектов типа MbItem. Выключена многопоточность ядра при обработке зависимых объектов. \en Ensured thread-safety of dependent objects MbItem. Kernel multithreading is OFF for objects with shared data.
                                    ///< \ru mtm_Items - Обеспечивается потокобезопасность объектов типа MbItem. Включена многопоточность ядра при обработке зависимых объектов. \en Ensured thread-safety of dependent objects MbItem. Kernel multithreading is ON for objects with shared data.
                                    ///< \ru mtm_Max - Включена максимальная многопоточность ядра. \en Maximal kernel multithreading is ON.
  static c3d::eAssertViolationNotify assertViolationNotification; ///< \ru Способ оповещения о нарушении требований. \en The way of assert violation notification.
public:
  static MbRefItem * selectCurve;   ///< \ru Запомненный объект (для отладки). \en Stored object (for debug). 
  static MbRefItem * selectSurface; ///< \ru Запомненный объект (для отладки). \en Stored object (for debug). 
  static MbRefItem * selectEdge;    ///< \ru Запомненный объект (для отладки). \en Stored object (for debug). 
  static MbRefItem * selectFace;    ///< \ru Запомненный объект (для отладки). \en Stored object (for debug). 
  static MbRefItem * selectSolid;   ///< \ru Запомненный объект (для отладки). \en Stored object (for debug). 

public: 

  // \ru Функции статических данных \en Functions of static data 

  /// \ru Математическая версия по умолчанию. \en Default mathematical version.  
  static const VersionContainer & DefaultVersion();
  /// \ru Математическая версия по умолчанию. \en Default mathematical version.  
  static VERSION DefaultMathVersion();

  /// \ru Идентификатор ядра как приложения. \en Kernel ID.
  static const MbUuid & MathID();

  /// \ru Установить значения переменных по умолчанию. \en Set default values of variables. 
  static void   SetDefaultValues();
  /// \ru Установить значение переменной.
  /// Необходимо учитывать, что изменение глобальных переменных может привести
  /// к непредсказуемым результатам при распараллеливании вычислений.
  /// \en Set value of variable. 
  /// It is necessary to keep in mind that modification of global variable could lead to
  /// unpredictable results when using parallel calculations.
  static void   SetUserValue( int index, double value );

/** \brief \ru Необходимо ли полное именование объекта.
           \en Is it necessary to full object naming. \~
  \details \ru Необходимо ли полное именование объекта.
           Если возвращает true,  то после создания оболочки именуются грани, рёбра, вершины,
           если возвращает false, то после создания оболочки именуются только грани. \n
           \en Is it necessary to full object naming. 
           If returns true then faces, edges, vertices are named after shell creation,
           If returns false then only faces are named after shell creation. \n \~
  \ingroup Base_Items
*/
  static bool   NamesComplete(); 

/** \brief \ru Установить необходимость полного именования объекта.
           \en Set flag of full object naming. \~
  \details \ru Установить необходимость полного именования объекта.
           Если передано true, то после создания оболочки будут именоваться грани, рёбра, вершины,
           если передано false, то после создания оболочки будут именоваться только грани. \n
           \en Set flag of full object naming. 
           If passed true then faces, edges, vertices are named after shell creation,
           if passed false then only faces are named after shell creation. \n \~
  \ingroup Base_Items
*/
  static void   SetNamesComplete( bool b ); 

/** \brief \ru Используются ли многопоточные вычисления?
           \en Are multithreaded calculations used? \~
  \details \ru Используются ли многопоточные вычисления? \n
           \en Are multithreaded calculations used? \n \~
  \ingroup Base_Items
*/
  static bool   Multithreaded();

/** \brief \ru Разрешить использовать многопоточные вычисления.
           \en Set flag for use multithreaded calculations. \~
  \details \ru Разрешить использовать многопоточные вычисления. \n
           Если передано true, то будут использоваться многопоточные вычисления. Устанавливается стандартный режим
           если передано false, то не будут использоваться многопоточные вычисления. \n
           \en Set flag for use multithreaded calculations.
           If passed true then will use multithreaded calculations, multithreaded mode will be set to the standard mode
           if passed false then will not use multithreaded calculations. \n \~
  \ingroup Base_Items
*/
  static void   SetMultithreaded( bool b );
  
/** \brief \ru Режим многопоточных вычислений
           \en Multithreaded mode \~
  \details \ru Режим многопоточных вычислений \n
           \en Multithreaded mode \n \~
  \ingroup Base_Items
*/  
  static MbeMultithreadedMode   MultithreadedMode();

/** \brief \ru Проверить режим многопоточных вычислений
           \en Check multithreaded mode \~
  \details \ru Проверить режим  многопоточных вычислений \n
           \en Check multithreaded mode \n \~
  \ingroup Base_Items
*/  
  static bool   CheckMultithreadedMode( MbeMultithreadedMode );

/** \brief \ru Установить режим многопоточных вычислений.
           \en Set flag for mode of multithreaded calculations. \~
  \details \ru Установить режим многопоточных вычислений. \n
           \en Set flag for mode of multithreaded calculations. \n \~
  \ingroup Base_Items
*/  
  static void    SetMultithreadedMode( MbeMultithreadedMode );

  /** \brief \ru Получить режим оповещения о нарушении требований.
  \en Get the mode of assert violations notification. \~  
  \ingroup Base_Items
  */  
  static c3d::eAssertViolationNotify CheckAssertNotify();

  /** \brief \ru Установить режим оповещения о нарушении требований.
  \en Set the mode of assert violations notification. \~  
  \ingroup Base_Items
  */  
  static void SetAssertNotify( c3d::eAssertViolationNotify );

};


//------------------------------------------------------------------------------
// Оставить от пути только имя файла.
// ---
MATH_FUNC( const char* ) C3DFileNameOnly( const char* path );

#if defined( C3D_WINDOWS )
  #define C3D_ASSERT_AS_CERR(expr) std::cerr << "C3D ASSERT VIOLATION in " << C3DFileNameOnly(__FILE__) << "@" << __LINE__ << std::endl;
#else
  #define C3D_ASSERT_AS_CERR(expr) fprintf(stderr, "C3D ASSERT VIOLATION in file %s, %d:\n `%s' in function: %s.\n", C3DFileNameOnly(__FILE__), __LINE__, #expr, __PRETTY_FUNCTION__);
#endif

#ifdef C3D_DEBUG
#define C3D_ASSERT_UNCONDITIONAL(expr) \
          { const c3d::eAssertViolationNotify notify = Math::CheckAssertNotify(); \
            if ( c3d::avn_ASSERT == notify ) { _ASSERT(false); } \
            else if ( c3d::avn_CERR == notify ) { C3D_ASSERT_AS_CERR(expr) } \
          }

//------------------------------------------------------------------------------
// Не рекомендуется использовать с параметром-константой
// (при сборке в VS2012 выдается - warning C4127: conditional expression is constant).
// ---
#define C3D_ASSERT(expr) \
          if (!(expr)) \
          C3D_ASSERT_UNCONDITIONAL(expr)

#else
  #define C3D_ASSERT_UNCONDITIONAL(expr) ((void)0)
  #define C3D_ASSERT(expr) ((void)0)
#endif


#endif // __MB_VARIABLES_H
