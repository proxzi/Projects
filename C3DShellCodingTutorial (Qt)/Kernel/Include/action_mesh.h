////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Методы построения полигональных геометрических объектов.
         \en Functions for construction of the polygonal geometric object. \~
  \details \ru Полигональные геометрические объекты могут быть построены по набору точек или на базе других объектов.
           \en Polygonal geometric objects can be constructed using a set of point or on the basis of other objects. \~ 

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_MESH_H
#define __ACTION_MESH_H


#include <mb_cart_point.h>
#include <mb_cart_point3d.h>
#include <mesh.h>
#include <mb_enum.h>
#include <mb_operation_result.h>
#include <vector>


class  MATH_CLASS  MbPlacement3D;
class  MATH_CLASS  MbMesh;
class  MATH_CLASS  MbCurve3D;
class  MATH_CLASS  MbSurface;
class  MATH_CLASS  MbSolid;
class  MATH_CLASS  MbPlaneItem;
class  MATH_CLASS  MbSNameMaker;
class  MATH_CLASS  MbFace;
class  MATH_CLASS  MbCollection;


//------------------------------------------------------------------------------
  /** \brief \ru Расчет полигона кривой.
             \en Calculation of polygon of curve. \~
  \details \ru Расчет трехмерного полигона двумерной кривой в плоскости XOY локальная системы координат.
           \en Calculation of three-dimensional polygon of two-dimensional curve located in the XOY-plane of a local coordinate system. \~
  \param[in] curve - \ru Двумерная кривая.
                     \en A two-dimensional curve. \~
  \param[in] plane - \ru Локальная система координат.
                     \en Local coordinate system. \~
  \param[in] sag - \ru Максимальное допустимое отклонение полигона от оригинала по прогибу или по углу между соседними элементами.
                   \en Maximum allowable deviation of polygon from the original by sag or by angle between neighboring elements. \~
  \param[out] polygon - \ru Рассчитанный полигон.
                        \en Calculated polygon. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (void) CalculatePolygon( const MbCurve & curve, 
                                   const MbPlacement3D & plane,
                                         double sag, 
                                         MbPolygon3D & polygon );


//------------------------------------------------------------------------------
/** \brief \ru Построить полигональный двухмерный объект.
           \en Create a polygonal two-dimensional object. \~
  \details \ru Построить полигональный объект для двумерного объекта в плоскости XOY 
           локальной системы координат.
           \en Create a polygonal object for two-dimensional object in the XOY-plane 
           of the local coordinate system. \~
  \param[in] obj - \ru Двумерный объект (если NULL, то объект не создаётся).
                   \en Two-dimensional object (if NULL, object isn't created). \~
  \param[in] plane - \ru Локальная система координат.
                     \en A local coordinate system. \~
  \param[in] sag - \ru Максимальное отклонение полигонального объекта от оригинала по прогибу.
                   \en The maximum deviation of polygonal object from the original object by sag. \~
  \param[out] mesh - \ru Полигональный объект.
                     \en Polygonal object. \~
  \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC (void) CalculateWire( const MbPlaneItem & obj, 
                                const MbPlacement3D & plane, 
                                      double sag, 
                                      MbMesh & mesh );


//------------------------------------------------------------------------------
/** \brief \ru Построить икосаэдр в виде полигональной модели.
           \en Construct an icosahedron mesh. \~
  \details \ru Построить икосаэдр в виде полигональной модели. \n
           \en Construct an icosahedron mesh. \n \~
  \param[in] place - \ru Местная система координат.
                     \en Local placement. \~
  \param[in] radius - \ru Радиус описанной сферы.
                      \en The radius of the sphere. \~
  \param[in] fn - \ru Способ построения полигонального объекта.
                  \en Way for polygonal object constructing. \~
  \param[out] result - \ru Результат построения.
                       \en The resulting mesh. \~
  \return  \ru Возвращает код результата операции.
           \en Returns operation result code. \~
  \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC (MbResultType) CreateIcosahedron( const MbPlacement3D & place, 
                                                  double radius, 
                                                  const MbFormNote & fn,
                                                  MbMesh *& result );


//------------------------------------------------------------------------------
// .
/** \brief \ru Построить полигональную сферу.
           \en Construct an spherical mesh. \~
  \details \ru Построить аппроксимацию сферы выпуклым многогранником. \n
           \en Construct an approximation of the sphere by a convex polyhedron. \n \~
  \param[in] place - \ru Местная система координат.
                     \en Local placement. \~
  \param[in] radius - \ru Радиус сферы.
                      \en The radius of the sphere. \~
  \param[in] epsilon - \ru Параметр аппроксимации сферы.
                       \en The approximation parameter. \~
  \param[out] result - \ru Результат построения.
                       \en The resulting mesh. \~
  \return  \ru Возвращает код результата операции.
           \en Returns operation result code. \~
  \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC (MbResultType) CreateSpherePolyhedron( const MbPlacement3D & place, 
                                                       double radius, 
                                                       double & epsilon, 
                                                       MbMesh *& result );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить выпуклую оболочку для множества точек.
           \en Calculate a convex hull of a point set. \~
  \details \ru Вычислить сетку, представляющую выпуклой оболочку для множества точек.
           \en Calculate mesh being a convex hull of a point set. \~
  \return  \ru Возвращает код результата операции.
           \en Returns operation result code. \~
  \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC (MbResultType) CreateConvexPolyhedron( const SArray<MbFloatPoint3D> & points,
                                                       MbMesh *& result );


//------------------------------------------------------------------------------
/** \brief \ru Построить выпуклую оболочку для триангуляционной сетки.
           \en Construct the convex hull of triangulation grid. \~
  \details \ru Построить сетку, представляющую собой выпуклую оболочку для тела,
    заданного его триангуляционной сеткой. По заданному объекту MbMesh
    строится охватывающая его вершины выпуклая триангуляционная сетка.
    Расстояние offset задает смещение точек результирующей сетки относительно
    заданной вдоль нормалей к её граням. Если offset = 0, то результирующая сетка
    будет в точности охватывать все вершины заданной. Смещение по нормали может
    быть как положительным, так и отрицательным (внутрь сетки). Используется для
    определения пересечения с некоторым допуском (offset). \n
           \en Construct the convex hull of triangulation grid. \n \~
  \param[in] mesh - \ru Исходная триангуляционная сетка.
                    \en Initial triangulated mesh. \~
  \param[in] offset - \ru Отступ по нормали для результирующей сетки.
                      \en The offset along a normal for the resulting grid. \~
  \param[out] resMesh - \ru Результирующая выпуклая триангуляционная сетка.
                        \en The resulting triangulation convex grid. \~
  \return  \ru Возвращает код результата операции.
           \en Returns operation result code. \~
  \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC (MbResultType) CreateConvexPolyhedron( const MbMesh &  mesh, 
                                                       double    offset,
                                                       MbMesh *& result );


//------------------------------------------------------------------------------
/** \brief \ru Определить, пересекаются ли данные выпуклые сетки.
           \en Whether there is intersection of convex grids. \~
  \details \ru Определить, пересекаются ли данные выпуклые оболочки, заданные
    триангуляционными сетками. Пересечение определяется по алгоритму
    Гильберта-Джонсона-Керти (Gilbert-Johnson-Keerthi). Заданные сетки
    равноправны, их последовательность в алгоритме не важна. Сложность
    алгоритма линейная, зависит от количества вершин сеток. \n
           \en Whether there is intersection of convex grids. \n \~
  \param[in] mesh1 - \ru Первая выпуклая триангуляционная сетка.
                     \en The first convex grid. \~
  \param[in] mesh2 - \ru Вторая выпуклая триангуляционная сетка.
                     \en The second convex grid. \~
  \return \ru true - Выпуклые триангуляционные сетки пересекаются.
              false - Выпуклые триангуляционные сетки не пересекаются.
          \en true - true - there is an intersection, 
              false - there are no intersections. \~
  \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC (bool) AreIntersectConvexPolyhedrons( const MbMesh & mesh1, 
                                                const MbMesh & mesh2 );


//------------------------------------------------------------------------------
/** \brief \ru Отрезать часть полигонального объекта плоскостью.
           \en Cut a part of a polygonal object by a plane. \~
  \details \ru Отрезать часть полигонального объекта плоскостью XY локальной системы координат. \n
    part =  1 - оставляем часть объекта, расположенную сверху плоскости XY локальной системы координат, \n
    part = -1 - оставляем часть объекта, расположенную снизу  плоскости XY локальной системы координат. \n
           \en Cut a part of a polygonal object off by a plane XY of local coordinate system. \n
    part =  1 - a part of polygonal object above the XY plane is to be retained. \n
    part = -1 - a part of polygonal object below the XY plane is to be retained. \n \~
  \param[in] solid - \ru Исходный полигональный объект.
                     \en The source polygonal object. \~
  \param[in] sameShell - \ru Режим копирования исходного объекта.
                         \en The mode of copying of the source polygonal object. \~
  \param[in] surface - \ru Секущая плоскость.
                       \en A cutting plane. \~
  \param[in] part - \ru Направление отсечения.
                    \en The direction of cutting off. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] closed - \ru Флаг режима отсечения: true - сечем как тело, false - сечем как оболочку.
                      \en The flag of the cutting off mode: true - cut as a solid, false - cut as a shell. \~
  \param[out] result - \ru Построенный полигональный объект.
                       \en The resultant polygonal object. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC (MbResultType) MeshCutting(        MbMesh &        mesh, 
                                             MbeCopyMode     sameShell,
                                       const MbPlacement3D & place, 
                                             int             part, 
                                       const MbSNameMaker &  names,
                                             bool            closed, 
                                             MbMesh *&       result );


//------------------------------------------------------------------------------
/** \brief \ru Построить триангуляцию по облаку точек на основе алгоритма поворотного шара.
            \en Build a triangulation by point cloud with Ball Pivoting algorithm. \~
  \param[in]  collection - \ru Коллекция трехмерных элементов.
                           \en Collection of 3d elements. \~
  \param[in]  radius     - \ru Радиус поворотного шара, если radius==0 будет предпринята попытка его автоопределения.
                           \en Radius of the pivoting ball, if radius==0 an autoguess for the ball pivoting radius is attempted \~
  \param[in]  radiusMin  - \ru Радиус кластеризации ( в % от радиуса поворотного шара ).
                           \en Clusterization radius ( % from radius value). \~
  \param[in]  angle      - \ru Максимальный угол между двумя соседними элементами сетки.
                           \en Max angle between two mesh faces \~
  \param[out] result -     \ru Построенный полигональный объект.
                           \en The resultant polygonal object. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC (MbResultType) CalculateBallPivotingGrid( const MbCollection & collection, 
                                                          double         radius,
                                                          double         radiusMin,
                                                          double         angle,
                                                          MbMesh *&      result );


#endif // __ACTION_MESH_H
