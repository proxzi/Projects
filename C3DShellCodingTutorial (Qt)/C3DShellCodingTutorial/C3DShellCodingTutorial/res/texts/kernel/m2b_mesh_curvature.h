////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Структура для хранения кривизн, их направлений и нормалей в вершине сетки.
         \en Struct to store curvatures, principal curvature directions and normals at mesh vertex. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __M2B_MESH_CURVATURE_H
#define __M2B_MESH_CURVATURE_H

#include <math_define.h>
#include <mb_vector3d.h>


//------------------------------------------------------------------------------
/** \brief \ru Данные о кривизне и главных направлениях изменений кривизны.
           \en Curvature and principal curvature direction data. \~
  \details \ru Структура для хранения информации о кривизне и главных направлениях изменений кривизны поверхности,
               рассчитанной в вершине полигональной сетки.
           \en Structure for store curvature and principal curvature direction data calculated at the polygon vertex. \~
  \ingroup Polygonal_Objects
*/
// ---
struct MATH_CLASS MbCurvature
{
  double k_h;             ///< \ru Средняя кривизна. \en Mean curvature.
  double k_g;             ///< \ru Гауссова кривизна. \en Gaussian curvature.
  double k1;              ///< \ru Максимальная кривизна. \en Maximum principal curvature.
  double k2;              ///< \ru Минимальная кривизна. \en Minimum principal curvature.
  MbVector3D normal;      ///< \ru Нормаль (вычислена по оператору кривизны). \en Normal (calculated by curvature operator).
  MbVector3D meanNormal;  ///< \ru Нормаль (вычислена как взвешенное среднее нормалей соседних граней). \en Normal (calculated as weighted mean of the normals of neighboring faces).
  MbVector3D cdir1;       ///< \ru Направление максимальной кривизны. \en Maximum principal curvature direction.
  MbVector3D cdir2;       ///< \ru Направление минимальной кривизны. \en Minimum principal curvature direction.
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbCurvature() : k_h( 0.0 ), k_g( 0.0 ), k1 ( 0.0 ), k2 ( 0.0 ) {}
};


#endif // __M2B_MESH_CURVATURE_H
