////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Функции для анализа кривизны поверхности.
\en Functions for surface curvature analysis. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CURVATURE_ANALYSIS_H
#define __ACTION_CURVATURE_ANALYSIS_H


#include <surface.h>
#include <topology.h>


//------------------------------------------------------------------------------
/** \brief \ru Алгоритмы поиска экстремумов на поверхности.
           \en Algorithms for finding extremes on the surface. \~
  \details \ru Константы, задающие вызываемый алгоритм поиска экстремальных значений функции на поверхности.
           \en Constants defining the called algorithm for searching for extreme values of a function on a surface. \~
  \ingroup  Algorithms_3D
*/
enum MbeExtremsSearchingMethod
{
  esm_GradientDescent = 1, ///< \ru Mетод градиентного спуска. \en Gradient Descent Method. 
  esm_LineSegregation = 2  ///< \ru Mетод выделения линий смены убывания / возрастания функции по u и по v. \en The method of segregation of lines of change of decrease / increase of the function in u and v directions.
};


//------------------------------------------------------------------------------
/** \brief \ru Функция, заданная на поверхности. 
           \en The function define on the surface. \~
  \details \ru Рассчитывает значение самой функции и ее градиент.
           \en Calculates the value of the function itself and its gradient. \~
  \ingroup  Algorithms_3D
*/
typedef void( *SurfaceFunction )( const MbSurface   & surf, // Поверхность,
                                  const MbCartPoint & pnt,  // точка на поверхности
                                        double      & func, // рассчитываемое значение функции,
                                        MbVector    * der );// рассчитываемое значение вектора градиента (если указатель не нулевой).

//------------------------------------------------------------------------------
/** \brief \ru Вычислить в точке поверхности минимальную нормальную кривизну, а также ее градиент.
           \en Calculate at the point of the surface the minimum normal curvature, as well as its gradient. \~
  \details \ru Вычисляется значение кривизны и опционально значение ее градиента в точке (если передается ненулевой указатель).
           \en The curvature value is calculated and, optionally, its gradient value at a point (if a non-zero pointer is passed). \~
  \param[in] surf - \ru Поверхность.
                    \en Surface. \~
  \param[in] pnt - \ru Точка расчета.
                    \en Point of calculation. \~
  \param[out] func - \ru Рассчитываемое значение кривизны.
                      \en Calculated curvature value. \~
  \param[out] der - \ru Рассчитываемое значение градиента кривизны.
                    \en The calculated value of the curvature gradient. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) MinSurfaceCurvature( const MbSurface & surf, const MbCartPoint & pnt, double & func, MbVector * der = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить в точке поверхности максимальну нормальную кривизну, а также ее градиент.
           \en Calculate at the point of the surface the maximum normal curvature, as well as its gradient. \~
  \details \ru Вычисляется значение кривизны и опционально значение ее градиента в точке (если передается ненулевой указатель).
           \en The curvature value is calculated and, optionally, its gradient value at a point (if a non-zero pointer is passed). \~
  \param[in] surf - \ru Поверхность.
                    \en Surface. \~
  \param[in] pnt - \ru Точка расчета.
                    \en Point of calculation. \~
  \param[out] func - \ru Рассчитываемое значение кривизны.
                      \en Calculated curvature value. \~
  \param[out] der - \ru Рассчитываемое значение градиента кривизны.
                    \en The calculated value of the curvature gradient. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) MaxSurfaceCurvature( const MbSurface & surf, const MbCartPoint & pnt, double & func, MbVector * der = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить в точке поверхности гауссову кривизну, а также ее градиент.
           \en Calculate at a surface point the Gaussian curvature, as well as its gradient. \~
  \details \ru Вычисляется значение кривизны и опционально значение ее градиента в точке (если передается ненулевой указатель).
           \en The curvature value is calculated and, optionally, its gradient value at a point (if a non-zero pointer is passed). \~
  \param[in] surf - \ru Поверхность.
                    \en Surface. \~
  \param[in] pnt - \ru Точка расчета.
                    \en Point of calculation. \~
  \param[out] func - \ru Рассчитываемое значение кривизны.
                      \en Calculated curvature value. \~
  \param[out] der - \ru Рассчитываемое значение градиента кривизны.
                    \en The calculated value of the curvature gradient. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) GaussCurvature( const MbSurface & surf, const MbCartPoint & pnt, double & func, MbVector * der = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить в точке поверхности среднюю кривизну, а также ее градиент.
           \en Calculate at the point of the surface the mean curvature, as well as its gradient. \~
  \details \ru Вычисляется значение кривизны и опционально значение ее градиента в точке (если передается ненулевой указатель).
           \en The curvature value is calculated and, optionally, its gradient value at a point (if a non-zero pointer is passed). \~
  \param[in] surf - \ru Поверхность.
                    \en Surface. \~
  \param[in] pnt - \ru Точка расчета.
                    \en Point of calculation. \~
  \param[out] func - \ru Рассчитываемое значение кривизны.
                      \en Calculated curvature value. \~
  \param[out] der - \ru Рассчитываемое значение градиента кривизны.
                    \en The calculated value of the curvature gradient. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) MeanCurvature( const MbSurface & surf, const MbCartPoint & pnt, double & func, MbVector * der = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить в точке поверхности нормальную кривизна в направлении u , а также ее градиент.
           \en Calculate at the surface point the normal curvature in the direction of u, as well as its gradient. \~
  \details \ru Вычисляется значение кривизны и опционально значение ее градиента в точке (если передается ненулевой указатель).
           \en The curvature value is calculated and, optionally, its gradient value at a point (if a non-zero pointer is passed). \~
  \param[in] surf - \ru Поверхность.
                    \en Surface. \~
  \param[in] pnt - \ru Точка расчета.
                    \en Point of calculation. \~
  \param[out] func - \ru Рассчитываемое значение кривизны.
                      \en Calculated curvature value. \~
  \param[out] der - \ru Рассчитываемое значение градиента кривизны.
                    \en The calculated value of the curvature gradient. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) UNormalCurvature( const MbSurface & surf, const MbCartPoint & pnt, double & func, MbVector * der = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить в точке поверхности нормальную кривизна в направлении v, а также ее градиент.
           \en Calculate at the surface point the normal curvature in the direction of v, as well as its gradient. \~
  \details \ru Вычисляется значение кривизны и опционально значение ее градиента в точке (если передается ненулевой указатель).
           \en The curvature value is calculated and, optionally, its gradient value at a point (if a non-zero pointer is passed). \~
  \param[in] surf - \ru Поверхность.
                    \en Surface. \~
  \param[in] pnt - \ru Точка расчета.
                    \en Point of calculation. \~
  \param[out] func - \ru Рассчитываемое значение кривизны.
                      \en Calculated curvature value. \~
  \param[out] der - \ru Рассчитываемое значение градиента кривизны.
                    \en The calculated value of the curvature gradient. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) VNormalCurvature( const MbSurface & surf, const MbCartPoint & pnt, double & func, MbVector * der = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Найти точки поверхности, в которых выбранная кривизна принимает наибольшие по модулю значения.
           \en Find the points of the surface at which the selected curvature takes the largest in modulus values. \~
  \details \ru Ищутся точки, в которых выбранная кривизна принимает на поверхности наибольшее положительное и наименьшее отрицательное значение.
           \en Looks for points at which the selected curvature takes on the surface the greatest positive and least negative value. \~
  \param[in] surf - \ru Исследуемая поверхность.
                    \en Test surface. \~
  \param[in] func - \ru Функция расчета кривизны в точке.
                    \en The function of calculating the curvature at a point. \~
  \param[out] maxNegCurv - \ru Наибольшее по модулю отрицательное значение кривизны (0, если нет такого).
                           \en The largest in modulus value negative curvature (0, if there is no such). \~
  \param[out] maxNegLoc - \ru Точка, в которой кривизна принимает наибольшее по модулю отрицательное значение.
                          \en The point at which the curvature takes the largest in modulus negative value. \~
  \param[out] maxPosCurv - \ru Наибольшее положительное значение кривизны (0, если нет такого).
                           \en The greatest positive value of curvature (0, if there is no such). \~
  \param[out] maxPosLoc - \ru Точка, в которой кривизна принимает наибольшее положительное значение.
                          \en The point at which the curvature takes the most positive value. \~
  \param[in] method - \ru Алгоритм поиска экстремумов.
                      \en Extremum search algorithm. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) SurfaceMinMaxCurvature(const MbSurface & surface, SurfaceFunction func, double & maxNegCurv, MbCartPoint & maxNegLoc, 
                                          double & maxPosCurv, MbCartPoint & maxPosLoc, MbeExtremsSearchingMethod  method = esm_LineSegregation );


//------------------------------------------------------------------------------
/** \brief \ru Найти точки оболочки, в которых выбранная кривизна принимает наибольшие по модулю значения.
           \en Find the points of the shell at which the selected curvature takes the most modulo values. \~
  \details \ru Ищутся точки на оболочке, в которых выбранная кривизна принимают наибольшее положительное и наименьшее отрицательное значение.
           \en Finds points on the shell at which the selected curvature takes the largest positive and lowest negative values. \~
  \param[in] faces - \ru Грани оболочки.
                     \en Faces of the shell. \~
  \param[in] func - \ru Функция расчета кривизны в точке.
                    \en The function of calculating the curvature at a point. \~
  \param[out] maxNegCurv - \ru Наибольшее по модулю отрицательное значение кривизны (0, если нет такого).
                           \en The largest in modulus value negative curvature (0, if there is no such). \~
  \param[out] maxNegFace - \ru Грань, в которой кривизна принимает наибольшее по модулю отрицательное значение.
                          \en The face at which the curvature takes the largest in modulus negative value. \~
  \param[out] maxNegLoc - \ru Точка, в которой кривизна принимает наибольшее по модулю отрицательное значение.
                          \en The point at which the curvature takes the largest in modulus negative value. \~
  \param[out] maxPosCurv - \ru Наибольшее положительное значение кривизны (0, если нет такого).
                           \en The greatest positive value of curvature (0, if there is no such). \~
  \param[out] maxPosFace - \ru Грань, в которой кривизна принимает наибольшее положительное значение.
                          \en The face at which the curvature takes the most positive value. \~
  \param[out] maxPosLoc - \ru Точка, в которой кривизна принимает наибольшее положительное значение.
                          \en The point at which the curvature takes the most positive value. \~
  \param[in] borderControl - \ru Учитывать границы граней при поиске экстремумов.
                             \en Take into account the boundaries of the faces when searching for extrema. \~
  \param[in] method - \ru Алгоритм поиска экстремумов.
                      \en Extremum search algorithm. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) FacesMinMaxCurvature( const RPArray<MbFace> & faces, SurfaceFunction func, double & maxNegCurv, MbFace *& maxNegFace, MbCartPoint & maxNegLoc,
                                        double & maxPosCurv, MbFace *& maxPosFace, MbCartPoint & maxPosLoc, bool borderControl = false, 
                                        MbeExtremsSearchingMethod  method = esm_LineSegregation );


//------------------------------------------------------------------------------
/** \brief \ru Найти точки на поверхности, в которых главные нормальные кривизны принимают наибольшие по модулю значения.
           \en Find the points on the surface at which the major normal curvatures take the largest values in the module. \~
  \details \ru Ищутся точки на поверхности, в которых главные нормальные кривизны принимают наибольшее положительное и наименьшее отрицательное значение. 
           \en Looks for points on the surface at which the major normal curvatures take the largest positive and smallest negative values. \~
  \param[in] surf - \ru Исследуемая поверхность.
                    \en Test surface. \~
  \param[out] maxNegCurv - \ru Наибольшее по модулю отрицательное значение кривизны (0, если нет такого).
                           \en The largest in modulus value negative curvature (0, if there is no such). \~
  \param[out] maxNegLoc - \ru Точка, в которой кривизна принимает наибольшее по модулю отрицательное значение.
                          \en The point at which the curvature takes the largest in modulus negative value. \~
  \param[out] maxPosCurv - \ru Наибольшее положительное значение кривизны (0, если нет такого).
                           \en The greatest positive value of curvature (0, if there is no such). \~
  \param[out] maxPosLoc - \ru Точка, в которой кривизна принимает наибольшее положительное значение.
                          \en The point at which the curvature takes the most positive value. \~
  \param[in] method - \ru Алгоритм поиска экстремумов.
                      \en Extremum search algorithm. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) SurfaceMinMaxCurvature(const MbSurface & surface, double & maxNegCurv, MbCartPoint & maxNegLoc, 
                                               double & maxPosCurv, MbCartPoint & maxPosLoc, MbeExtremsSearchingMethod  method = esm_LineSegregation );


//------------------------------------------------------------------------------
/** \brief \ru Найти точки на оболочке, в которых главные нормальные кривизны принимают наибольшие по модулю значения.
           \en Find the points on the shell at which the major normal curvatures take the largest values in the module. \~
  \details \ru Ищутся точки на оболочке, в которых главные нормальные кривизны принимают наибольшее положительное и наименьшее отрицательное значение. 
           \en Looks for points on the shell at which the major normal curvatures take the largest positive and smallest negative values. \~
  \param[in] faces - \ru Грани оболочки.
                     \en Faces of the shell. \~
  \param[out] maxNegCurv - \ru Наибольшее по модулю отрицательное значение кривизны (0, если нет такого).
                           \en The largest in modulus value negative curvature (0, if there is no such). \~
  \param[out] maxNegFace - \ru Грань, в которой кривизна принимает наибольшее по модулю отрицательное значение.
                          \en The face at which the curvature takes the largest in modulus negative value. \~
  \param[out] maxNegLoc - \ru Точка, в которой кривизна принимает наибольшее по модулю отрицательное значение.
                          \en The point at which the curvature takes the largest in modulus negative value. \~
  \param[out] maxPosCurv - \ru Наибольшее положительное значение кривизны (0, если нет такого).
                           \en The greatest positive value of curvature (0, if there is no such). \~
  \param[out] maxPosFace - \ru Грань, в которой кривизна принимает наибольшее положительное значение.
                          \en The face at which the curvature takes the most positive value. \~
  \param[out] maxPosLoc - \ru Точка, в которой кривизна принимает наибольшее положительное значение.
                          \en The point at which the curvature takes the most positive value. \~
  \param[in] borderControl - \ru Учитывать границы граней при поиске экстремумов.
                             \en Take into account the boundaries of the faces when searching for extrema. \~
  \param[in] method - \ru Алгоритм поиска экстремумов.
                      \en Extremum search algorithm. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) FacesMinMaxCurvature( const RPArray<MbFace> & faces, double & maxNegCurv, MbFace *& maxNegFace, MbCartPoint & maxNegLoc,
                                        double & maxPosCurv, MbFace *& maxPosFace, MbCartPoint & maxPosLoc, bool borderControl = false, 
                                        MbeExtremsSearchingMethod  method = esm_LineSegregation );


//------------------------------------------------------------------------------
/** \brief \ru Ориентированная кривизна для плоской кривой.
           \en Oriented curvature for a plane curve. \~
  \details \ru Для плоской кривой функция возвращает кривизну в точке, ориентированную относительно нормали плоскости, 
               в которой она лежит. Для неплоской кривой функция просто возвращает кривизну в точке.
           \en For a flat curve, the function returns the curvature at a point oriented relative to the normal to the plane,
                in which she lies. For a non-flat curve, the function simply returns the curvature at the point. \~
  \param[in] curve - \ru Исследуемая кривая.
                     \en Test curve. \~
  \param[in] param - \ru Параметр на кривой.
                     \en Parameter on the curve. \~
  \param[in] planeNorm - \ru Нормаль плоскости, в которой лежит кривая. Если нормаль не передается в функцию, алгоритм самостоятельно
                             выполняет проверку, лежит ли кривая в плоскости, и вычисляет нормаль, если проверка выполняется.
                         \en The normal of the plane in which the curve lies. If the normal is not passed to the function, the algorithm itself
                              checks if the curve is in the plane and calculates normal if the test is being performed. \~
  \return  \ru Возвращается значение ориентированной кривизны в точке.
           \en The value of the oriented curvature at the point is returned. \~

  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( double ) CurveOrientedCurvature(const MbCurve3D & curve, double & param, const MbVector3D * planeNorm = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Найти точки на кривой, в которых кривизна принимает наибольшее и наименьшее значения.
           \en Find the points on the curve at which the curvature takes the largest and smallest values. \~
  \details \ru Для плоской кривой наибольшее и  наименьшее значение может уходить в отрицательную область. 
               Для неплоской кривой наибольшее и наименьшее значение всегда неотрицательны.
           \en For a flat curve, the largest and smallest value may go into the negative region.
               For a non-planar curve, the largest and smallest values are always non-negative. \~
  \param[in] curve - \ru Исследуемая кривая.
                     \en Test curve. \~
  \param[out] maxCurv - \ru Наибольшее значение кривизны.
                        \en The greatest value of curvature. \~
  \param[out] maxParam - \ru Точка, в которой кривизна принимает наибольшее значение.
                          \en The point at which the curvature takes the largest value. \~
  \param[out] minCurv - \ru Наименьшее значение кривизны.
                        \en The smallest value of curvature. \~
  \param[out] minParam - \ru Точка, в которой кривизна принимает наибольшее значение.
                         \en The point at which the curvature takes the smallest value. \~
  \param[out] bendPoints - \ru Mассив параметров точек перегиба.
                           \en Array of parameters of bend points. \~
  \param[out] maxPoints - \ru Mассив параметров, в которых достигается локальный максимум кривизны по модулю.
                           \en An array of parameters in which the local maximum curvature modulo is reached. \~
  \param[out] minPoints - \ru Mассив параметров, в которых достигается локальный минимум кривизны по модулю.
                           \en An array of parameters in which the local minimum curvature modulo is reached. \~
  \param[out] rapPoints - \ru Mассив параметров, в которых кривизна терпит разрыв. 
                              Для каждого разрыва вставляются две точки, до и после.
                           \en Array of parameters in which curvature breaks.
                               For each break two points are inserted, before and after. \~
  \ingroup  Algorithms_3D
*/ 
MATH_FUNC( void ) CurveMinMaxCurvature( const MbCurve3D & curve, double & maxCurv, double & maxParam, double & minCurv, double & minParam, 
                                        std::vector<double> * bendPoints = NULL, std::vector<double> * maxPoints = NULL, 
                                        std::vector<double> * minPoints = NULL, std::vector<c3d::DoublePair> * rapPoints = NULL );

#endif // __ACTION_CURVATURE_ANALYSIS_H
