////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Нахождение пересечений двух областей.
         \en Calculation of intersection of two regions. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONTOUR_COMBINE_H
#define __CONTOUR_COMBINE_H

#include <templ_p_array.h>
#include <cur_contour.h>

class  MATH_CLASS MbCurve;


//------------------------------------------------------------------------------
/** \brief \ru Результат пересечения кривых.
           \en The curves intersection result. \~
  \details \ru Результат пересечения двух областей кривых.
           \en The result of two curves' regions intersection. \~       
  \ingroup Algorithms_2D
*/
// ---
enum MbeIntLoopsResult {
  ilr_error        = -1, ///< \ru Ошибка! Кривые не замкнуты или имеют самопересечения. \en Error! Curves are not closed or have self-intersections. 
  ilr_notIntersect =  0, ///< \ru Области под кривыми не пересекаются (массив кривых пересечения пуст). \en Regions of curves don't have intersections (intersection curve array is empty). 
  ilr_firstCurve   =  1, ///< \ru Пересечением областей является первая кривая (массив кривых пересечения пуст). \en The intersection of regions is the first curve (intersection curve array is empty). 
  ilr_secondCurve  =  2, ///< \ru Пересечением областей является вторая кривая (массив кривых пересечения пуст). \en The intersection of regions is the second curve (intersection curve array is empty). 
  ilr_success      =  3, ///< \ru Произвольное пересечение (одна и более кривых в массиве кривых пересечения). \en An arbitrary intersection (one or more curves in intersection curve array). 
};


//-------------------------------------------------------------------------------
/** \brief \ru Найти пересечение двух кривых.
           \en Calculate two curves intersection. \~
  \details \ru Найти пересечение областей двух замкнутых кривых.
           \en Calculate two closed curves' regions intersection. \~     
  \param[in]  iCheck   - \ru Признак проверки кривых на касание вершин.
                         \en Attribute of check of curves for vertices tangency. \~                 
  \param[in]  loop1    - \ru Первая замкнутая кривая.
                         \en The first closed curve. \~
  \param[in]  bOrient1 - \ru Ориентация первой замкнутой кривой:\n
                         true  - ее областью считаем внутренность,\n
                         false - внешность.
                         \en The first closed curve orientation:\n
                         true  - interior is considered to be the curve's region,\n
                         false - exterior is the curve's region. \~
  \param[in]  loop2    - \ru Вторая замкнутая кривая.
                         \en The second closed curve. \~
  \param[in]  bOrient2 - \ru Ориентация второй замкнутой кривой:\n
                         true  - ее областью считаем внутренность,\n
                         false - внешность.
                         \en The second closed curve orientation:\n
                         true  - interior is considered to be the curve's region,\n
                         false - exterior is the curve's region. \~
  \param[out] intLoops - \ru Массив кривых пересечения.
                         \en Intersection curve array. \~
  \attention \ru Устаревшая функция.
             \en An obsolete function. \~
  \return \ru Код результата пересечения.
          \en Intersection result code. \~
  \ingroup Algorithms_2D
*/
// ---
DEPRECATE_DECLARE MATH_FUNC ( MbeIntLoopsResult ) BooleanIntLoops( const MbCurve & loop1, bool bOrient1, 
                                                                   const MbCurve & loop2, bool bOrient2, 
                                                                   RPArray<MbCurve> & intLoops );

#endif // __CONTOUR_COMBINE_H