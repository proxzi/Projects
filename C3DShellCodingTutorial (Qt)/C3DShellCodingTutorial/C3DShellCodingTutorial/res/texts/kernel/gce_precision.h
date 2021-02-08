//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Набор констант и величин погрешности для решения задач двумерных ограничений.
         \en Set of constants and tolerance values to solve two-dimensional constraint problems. \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PRECISION_H
#define __GC_PRECISION_H

#include <math_define.h>
#include <tool_cstring.h>

#define GC_GOLDEN_SECTION 0.381966011250105 // \ru Золотое сечение. \en Golden ratio.

/** 
  \addtogroup Constraints2D_API
  \{
*/

//----------------------------------------------------------------------------------------
/**
  \brief \ru Допуски для оценки точности геометрии.
         \en Tolerances to test the accuracy of geometry.
*/
// 
//---
struct MbGeomTol
{
  double  lenTol; /// \ru Абсолютная погрешность в единицах длины. \en Linear resolution (in length units).
  double  angTol; /// \ru Абсолютная погрешность в радианах. \en Angular resolution (radians).

  MbGeomTol( double lenEps, double angEps ) : lenTol(lenEps), angTol(angEps) {}
  MbGeomTol( double tol ) : lenTol(tol), angTol(tol) {}
};

//////////////////////////////////////////////////////////////////////////////////////////
//
/** \brief \ru Фиксированные точности решения задач двумерной параметризации и иные константы.
           \en Fixed tolerances of two-dimensional parametrization problems solving and other constants \~
    \details \ru Класс инкапсулирует все точности и прочие константы, распространяющиеся на задачи
  двумерной параметризации.
  \n
  1.  При проверке метрических величин или инцидентности точек в 2D-пространстве
      используется точность GcPrecision::lengthRegion. Т.е. любые две точки, 
      не совпадающие  с погрешностью GcPrecision::lengthRegion считаютя разными.\n
  2.  Для итерационных решателей используется точность параметра GcPrecision::newtonEpsilon,
      эта величина на 1-2 порядка выше, чем неразличимая область (lengthRegion, angleRegion).\n
  3.  Любое угловое, метрическое или параметрическое значение меньшее
      GcPrecision::tolerance считается нулем.\n
  4.  Величина newtonEpsilon всегда меньше либо равна lengthEpsilon и angleEpsilon.\n
  5.  Любой элемент матрицы меньший по модулю, чем GcPrecision::m_null - считается 
      нулем. Барьер GcPrecision::m_null влияет на быстродействие и точность разложения 
      и перемножения матриц. Чем выше m_null, тем быстрее может работать разложение, в ущерб
      вычислительной устойчивости.\n
             \en The class encapsulates all tolerances and other constants related to
  two-dimensional parametrization problems.
  \n
  1.  For check of metric values or points coincidence in 2D space
      tolerance GcPrecision::lengthRegion is used. I.e. any two points 
      which are not coincident with tolerance GcPrecision::lengthRegion are considered to be different.\n
  2.  For iterative solvers tolerance of parameter GcPrecision::newtonEpsilon is used.
      This value is 1-2 orders higher than  undistinguishable  domain (lengthRegion, angleRegion).\n
  3.  Any angular,metric or parametric value less than
      GcPrecision::tolerance is considered to be zero.\n
  4.  Value newtonEpsilon is always less or equal to lengthEpsilon and angleEpsilon.\n
  5.  Any element of matrix less than GcPrecision::m_null by absolute value is considered 
      to be zero. Threshold GcPrecision::m_null influences on performance and accuracy of decomposition 
      and multiplication of matrices. The higher m_null the faster the decomposition can work, to the prejudice of
      computational stability.\n \~
  \nosubgrouping
*/
//
//////////////////////////////////////////////////////////////////////////////////////////

struct GCE_CLASS GcPrecision
{
  /**
    \ru \name Точности
    \en \name Tolerances
    \{
  */

  const static  double    m_null;        ///< \ru Абсолютная точность, с которой определяется четкий нуль в матрице; \en Absolute tolerance with which the clear zero is determined in matrix; 
  const static  double    grshTol;       ///< \ru Относительная точность для оценки линейной зависимости при ортогонализации (Грамм-Шмидт) \en Relative tolerance for estimation of linear dependence during orthogonalizaiton (Gram-Schmidt) 
  const static  double    tolerance;     ///< \ru Точность для проверки на нуль вещественного числа (углового или метрического); \en Tolerance for checking a real number (angular or metric) for zero; 
  const static  double    degMetricEps;  ///< \ru Метрическая точность для проверки вырожденной геометрии; \en Metric tolerance for checking the geometry for degeneracy; 
  const static  double    lengthEpsilon; ///< \ru Вычислительная точность итерационных решателей и конструирования локусов пересечения ( линейная ); \en Computational tolerance of iterative solvers and intersection loci construction (linear); 
  const static  double    angleEpsilon;  ///< \ru Вычислительная точность итерационных решателей и конструирования локусов пересечения ( угловая  ); \en Computational tolerance of iterative solvers and intersection loci construction (angular); 
  const static  double    lengthRegion;  ///< \ru Неразличимая метрическая область (проверочная точность). \en Indistinguishable metric domain (satisfactory tolerance).
  const static  double    angleRegion;   ///< \ru Неразличимая угловая область (проверочная точность). \en Indistinguishable angular domain (satisfactory tolerance).
  const static  double    newtonEpsilon; ///< \ru Целевая точность итерационного решателя. \en Target accuracy of the iterative solver.
  const static  double    newtonRegion;  ///< \ru Удовлетворительная точность итерационного решения. \en Satisfactory accuracy of the iterative solution.
  const static  double    paramRegion;   ///< \ru Проверочная точность параметра \en Parameter checking tolerance 
  const static  double    maxRadius;     ///< \ru Максимально возможный радиус для 2d-эскиза \en Maximal possible radius for cutting of 2d-sketch
  const static  MbGeomTol satisfying;    ///< \ru Точность удовлетворенных ограничений; \en Satisfactory accuracy;
  const static  MbGeomTol newtonTol;     ///< \ru Точность решения системы уравнений итерационными методами; \en Tolerance of solving the equation system by iterative methods; 

  /**
    \}
    \ru \name Другие константы
    \en \name Other constants
    \{
  */

  const static  double    pi2;              ///< 2*M_PI (6.18...)
  const static  double    lastReal;         ///< \ru "Самое большое" число с плавающей точкой \en "The greatest" float number 
  const static  int       iterLimitCount;   ///< \ru Предельное количество итераций в численном методе Ньютона \en Limit of iterations in numerical Newton's method 
  const static  int       wellIterLimit;    ///< \ru Предельное количество итераций в хорошо-сходящихся процессах. \en Limit number of iterations in well-convergent processes.
        static  TCHAR     buff_512[512];    ///< \ru Текстовый буфер размером в 512 байт \en Text buffer of 512 bytes
  /** 
    \} 
  */
};

//----------------------------------------------------------------------------------------
/// \ru Число из дисткретного множества {-1,0,1}. \en A number from discrete set {-1,0,1}.
//---
typedef int8 sign_t;

/*! @} */

#endif

// eof
