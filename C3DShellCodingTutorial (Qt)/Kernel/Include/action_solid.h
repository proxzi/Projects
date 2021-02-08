////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Функции создания тел, операции с телами.
         \en Functions for creation of solids, operations on solids. \~
  \details \ru Процесс построения тел в геометрическом моделировании похож на процесс 
    изготовления моделируемого объекта. Сначала создаются тела простой формы, а далее 
    выполняется набор действий, позволяющих из тел простой формы получить более сложные тела.
    При необходимости создаются вспомогательные объекты. Редактировать и создавать подобные
    тела можно путём изменения параметров с последующим повторением процесса построения тел.\n 
    Все функции создания тел содержат в качестве входного параметр MbSNameMaker, 
    обеспечивающий именование граней, рёбер и вершин. 
    Первым параметром конструктора генератора имён MbSNameMaker служит главное имя операции. 
    По главному имени можно определить, в какой функции рождена та или иная грань, ребро, вершина.
    Главное имя выдаёт метод GetMainName().\n 
           \en The process of solids creation in geometric modeling is similar to the process 
    of the modeled object manufacturing. Firstly solids of a simple form are created, and then 
    a set of operations are performed to obtain a more complex solids from solids of a simple form.
    Auxiliary objects are created if necessary. The similar solids can be edited and created
    by modifying of the parameters and further repeating the process of the solids creation.\n  
    All of the function contain input parameter MbSNameMaker, 
    providing the naming of faces, edges and vertices.
    The first parameter to the constructor MbSNameMaker is the main name of the function.
    You can determine which function is born one or the other face, edge, vertex by main name.
    GetMainName() gives the main name of the function (face.GetMainName(), edge.GetMainName(), vertex.GetMainName()).\~ 
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SOLID_H
#define __ACTION_SOLID_H


#include <templ_s_array.h>
#include <mb_cart_point3d.h>
#include <space_item.h>
#include <op_boolean_flags.h>
#include <op_shell_parameter.h>
#include <op_swept_parameter.h>
#include <topology_faceset.h>
#include <mb_operation_result.h>
#include <op_duplication_parameter.h>


class  MATH_CLASS MbCurve;
class  MATH_CLASS MbCurve3D;
class  MATH_CLASS MbSurface;
class  MATH_CLASS MbCurveEdge;
class  MATH_CLASS MbFace;
class  MATH_CLASS MbSolid;
class  MATH_CLASS MbItem;
class  MATH_CLASS MbSNameMaker;
class  MATH_CLASS MbPartSolidIndices;
class  MATH_CLASS MbSpine;
class  MATH_CLASS MbMesh;
class  MATH_CLASS MbGrid;
class  MATH_CLASS MbCollection;
class  MATH_CLASS IProgressIndicator;


//------------------------------------------------------------------------------
/** \brief \ru Создать элементарное тело.
           \en Create an elementary solid. \~
  \details \ru Создать одно из элементарных тел по заданным точкам и типу: \n
    solidType = et_Sphere      - шар          (3 точки), \n
    solidType = et_Torus       - тор          (3 точки), \n
    solidType = et_Cylinder    - цилиндр      (3 точки), \n
    solidType = et_Cone        - конус        (3 точки), \n
    solidType = et_Block       - блок         (4 точки), \n
    solidType = et_Wedge       - клин         (4 точки), \n
    solidType = et_Prism       - призма       (количество вершин основания+1 точка), \n
    solidType = et_Pyramid     - пирамида     (количество вершин основания+1 точка), \n
    solidType = et_Plate       - плита        (4 точки), 
    solidType = et_Icosahedron - икосаэдр     (3 точки), \n
    solidType = et_Polyhedron  - многогранник (3 точки), \n
    solidType = et_Tetrapipe   - тетра-труба  (3 точки), \n
    solidType = et_Octapipe    - окта-труба   (3 точки). \n
           \en Create one of elementary solids from the specified points and type: \n
    solidType = et_Sphere      - a sphere       (3 points), \n 
    solidType = et_Torus       - a torus        (3 points), \n
    solidType = et_Cylinder    - a cylinder     (3 points), \n
    solidType = et_Cone        - a cone         (3 points), \n
    solidType = et_Block       - a block        (4 points), \n
    solidType = et_Wedge       - a wedge        (4 points), \n
    solidType = et_Prism       - a prism        (points count is equal to the base vertices count + 1), \n
    solidType = et_Pyramid     - a pyramid      (points count is equal to the base vertices count + 1), \n
    solidType = et_Plate       - a plate        (4 points), \n 
    solidType = et_Icosahedron - an icosahedron (3 points), \n
    solidType = et_Polyhedron  - a polyhedron   (3 points), \n 
    solidType = et_Tetrapipe   - a tetra-pipe   (3 points), \n
    solidType = et_Octapipe    - an octa-pipe   (3 points). \n \~
  \param[in] points - \ru Набор точек. \n
             points[0] определяет начало локальной системы координат. \n
             Для сферы, тора, цилиндра и конуса: \n
             points[1] определяет направление оси Z локальной системы. \n
             points[2] определяет направление оси X локальной системы. \n
             Для блока, клина и плиты: \n
             points[1] определяет направление оси X локальной системы. \n
             points[2] определяет направление оси Y локальной системы. \n
             Кроме того, \n
             points[1] определяет высоту цилиндра, высоту конуса, 
             большой радиус тора, длину блока, длину клина. \n
             points[2] определяет радиус цилиндра, угол конуса как угол между векторами v1(points[0],points[1]) и v2(points[0],points[2]), 
             радиус сферы, малый радиус тора, ширину блока, ширину клина. \n
             В случае конуса вектора v1(points[0],points[1]) и v2(points[0],points[2]) не должны быть параллельны или перпендикулярны друг другу. \n
             Последняя точка определяет высоту блока, клина, плиты, вершину пирамиды.
                      \en A point set. \n
             points[0] determines a local coordinate system origin. \n
             For a sphere, a torus, a cylinder or a cone: \n
             points[1] determines the direction of Z-axis of a local coordinate system. \n
             points[2] determines the direction of X-axis of a local coordinate system. \n
             For a block, a plate or a wedge: \n
             points[1] determines the direction of X-axis of a local coordinate system. \n
             points[2] determines the direction of Y-axis of a local coordinate system. \n
             Also, \n
             points[1] determines the height of a cylinder or a cone, 
             the major radius of a torus, the length of a block or a wedge. \n
             points[2] determines the radius of a cylinder, cone angle as angle between vectors v1(points[0],points[1]) and v2(points[0],points[2]), 
             radius of a sphere, the minor radius of a torus, the width of a block or a wedge. \n
             In the case of the cone of the vector v1(points [0], points [1]) and v2(points [0], points [2]) must not be parallel or perpendicular to each other. \n
             The last point determines the height of a block, a wedge or a plate, the vertex of a pyramid. \~
  \param[in] solidType - \ru Тип создаваемого тела.
                         \en The solid type. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) ElementarySolid( const SArray<MbCartPoint3D> & points,
                                                ElementaryShellType     solidType, 
                                          const MbSNameMaker &          names, 
                                                MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по поверхности.
           \en Create a solid from a surface. \~
  \details \ru Создать тело по элементарной поверхности. \n
    Допускается только тип поверхности - цилиндр, конус, сфера, тор.
           \en Create a solid from an elementary surface. \n
    The only acceptable surface types are cylinder, cone, sphere, torus. \~
  \param[in] surface - \ru Поверхность.
                       \en The surface. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) ElementarySolid( const MbSurface &    surface,
                                          const MbSNameMaker & names, 
                                                MbSolid *&     result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело на основе полигональной модели.
           \en Create a solid on the basis of a polygonal geometric object. \~
  \details \ru Создать тело #MbSolid на основе полигональной модели #MbMesh. \n
           \en Create a solid #MbSolid on the basis of a polygonal geometric object #MbMesh. \n \~
  \param[in] mesh - \ru Полигональная модель.
                    \en The polygonal geometric object. \~
  \param[in] params - \ru Параметры операции.
                      \en Operation parameters. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) MeshSolid( const MbMesh &             mesh, 
                                    const GridsToShellValues & params,
                                    const MbSNameMaker &       names,
                                          MbSolid *&           result,
                                          IProgressIndicator * prog = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело на основе триангуляции.
           \en Create a solid on the basis of a triangulation. \~
  \details \ru Создать тело #MbSolid на основе триангуляции #MbGrid. \n
           \en Create a solid #MbSolid on the basis of a triangulation #MbGrid. \n \~
  \param[in] grid - \ru Полигональная модель.
                    \en The polygonal geometric object. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) GridSolid( const MbGrid &             grid, 
                                    const MbSNameMaker &       names,
                                          MbSolid *&           result,
                                          IProgressIndicator * prog = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело на основе коллекции элементов.
           \en Create a solid on the basis of elements. \~
  \details \ru Создать тело #MbSolid на основе коллекции элементов #MbCollection. \n
           \en Create a solid #MbSolid on the basis of elements #MbCollection. \n \~
  \param[in] grid - \ru Коллекция элементов.
                    \en The elements collection. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) CollectionSolid( const MbCollection &       grid, 
                                          const MbSNameMaker &       names,
                                                MbSolid *&           result,
                                                IProgressIndicator * progBar = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело c заданной оболочкой.
           \en Create a solid with a given shell. \~
  \details \ru Создать тело без истории построения с заданной оболочкой. \n
           \en Create a solid with a given shell without a history. \n \~
  \param[in] shell - \ru Оболочка.
                     \en A shell. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \return \ru Возвращает тело без истории.
          \en Returns a solid without the history. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbSolid *) CreateSolid(       MbFaceShell &  shell, 
                                   const MbSNameMaker & names );


//------------------------------------------------------------------------------
/** \brief \ru Рассчитать глубину выдавливания или угол вращения.
           \en Compute the extrusion depth or the rotation angle. \~
  \details \ru Рассчитать value - глубину выдавливания или угол вращения (0.0 : M_PI2) 
    для последующего построения тела путем выдавливания или вращения образующей кривой. \n
           \en Compute 'value' - the extrusion depth or the rotation angle (0.0 : M_PI2) 
    for the further construction of a solid by extrusion or revolution of the generating curve. \n \~  
  \param[in] sweptData - \ru Данные об образующей.
                         \en The generating curve data. \~
  \param[in] axis - \ru Ось вращения.
                    \en Rotation axis. \~
  \param[in] direction - \ru Направление выдавливания.
                         \en An extrusion direction. \~
  \param[in] rotation - \ru Вращение или выдавливание.
                        \en Rotation or extrusion. \~
  \param[in] operationDirection - \ru Вперед\назад.
                                  \en Forward or backward direction. \~
  \param[in] point - \ru Точка, до которой требуется вращать или выдавливать поверхность.
                     \en The point to rotate or extrude the surface up to. \~
  \param[out] value - \ru Глубина выдавливания или угол вращения.
                      \en The extrusion depth or the rotation angle. \~
  \return \ru Возвращает true, если расчет выполнен успешно.
          \en Returns true if the value has been successfully calculated. \~
  \warning \ru Вспомогательная функция операций ExtrusionSolid, RevolutionSolid, ExtrusionResult и RevolutionResult.
           \en An auxiliary function of operations ExtrusionSolid, RevolutionSolid, ExtrusionResult and RevolutionResult. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (bool) GetSweptValue( const MbSweptData &   sweptData,
                                const MbAxis3D &      axis,
                                const MbVector3D &    direction,
                                const bool            rotation,
                                const bool            operationDirection,
                                const MbCartPoint3D & point,
                                      double &        value );


//------------------------------------------------------------------------------
/** \brief \ru Получить начальное приближение для нахождения образа при вращении/выдавливании.
           \en Get the initial approximation for image calculation while rotating/extruding. \~
  \details \ru Вычислить положение образа точки образующей кривой на поверхности для последующего 
    построения тела путем выдавливания или вращения образующей кривой до заданной поверхности. \n
           \en Compute the position of a generating curve point image on a surface for further 
    solid construction by extrusion or revolution of the generating curve up to the specified surface. \n \~
  \param[in] generatrix - \ru Кривая.
                          \en The curve. \~
  \param[in] surface - \ru Поверхность, до которой строим операцию.
                       \en The surface to construct up to. \~
  \param[in] direction - \ru Направление выдавливания.
                         \en An extrusion direction. \~
  \param[in] axis - \ru Ось вращения.
                    \en Rotation axis. \~
  \param[in] rotation - \ru Вращение (true) или выдавливание (false)
                        \en Rotation (true) or extrusion (false) \~
  \param[out] imagePosition - \ru Точка образа на поверхности.
                              \en The image point on the surface. \~
  \param[out] resType - \ru Код результата операции.
                        \en Operation result code. \~
  \warning \ru Вспомогательная функция операций ExtrusionSolid, RevolutionSolid, ExtrusionResult и RevolutionResult.
           \en An auxiliary function of operations ExtrusionSolid, RevolutionSolid, ExtrusionResult and RevolutionResult. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (void) GetSweptImagePosition( const MbCurve3D &    generatrix, 
                                        const MbSurface &    surface, 
                                        const MbVector3D &   direction,
                                        const MbAxis3D &     axis,
                                        const bool           rotation,
                                              MbCartPoint &  imagePosition,
                                              MbResultType & resType );


//------------------------------------------------------------------------------
/** \brief \ru Найти расстояния/углы от образующей до поверхности при вращении/выдавливании.
           \en Calculate the distances/angles from generating curve to the surface while rotating/extruding. \~
  \details \ru Вычислить глубины выдавливания в прямом и обратном направлениях или углы вращения 
    в прямом и обратном направлениях для последующего построения тела путем выдавливания или вращения 
    образующей кривой до заданной поверхности, а также и габарит образа кривой. \n
           \en Calculate the extrusion depths in forward and backward directions or the rotating angles 
    in forward and backward directions for further solid construction by extrusion or revolution 
    of the generating curve up to the specified surface; and also calculate the bounding box of the curve image. \n \~
  \param[in] surface - \ru Поверхность, до которой строим операцию.
                       \en The surface to construct up to. \~
  \param[in] curve - \ru Образующая кривая.
                     \en The generating curve. \~
  \param[in] direction - \ru Направление выдавливания.
                         \en An extrusion direction. \~
  \param[in] axis - \ru Ось вращения.
                    \en Rotation axis. \~
  \param[in] rotation - \ru Вращение (true) или выдавливание (false).
                        \en Revolution (true) or extrusion (false). \~
  \param[in] operationDirection - \ru Направление движения: вперед (true) или назад (false).
                                  \en The motion direction: forward (true) or backward (false). \~
  \param[out] imagePosition - \ru Точка на части поверхности, в которой лежит образ.
                              \en A point on a surface part that contains the image. \~
  \param[out] range - \ru Расстояния до поверхности в обратном и прямом направлениях.
                      \en The distance to surface in the backward and the forward directions. \~
  \param[out] rectOnSurface - \ru Габарит образа на поверхности.
                              \en The bounding box of image on the surface. \~
  \param[out] resType - \ru Код результата операции.
                        \en Operation result code. \~
  \warning \ru Вспомогательная функция операций ExtrusionSolid, RevolutionSolid, ExtrusionResult и RevolutionResult.
           \en An auxiliary function of operations ExtrusionSolid, RevolutionSolid, ExtrusionResult and RevolutionResult. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (void) GetRangeToSurface( const MbSurface &    surface,
                                    const MbCurve3D &    curve,
                                    const MbVector3D &   direction,
                                    const MbAxis3D &     axis,
                                    const bool           rotation,
                                    const bool           operationDirection,
                                    const MbCartPoint &  imagePosition,
                                          double         range[2],
                                          MbRect &       rectOnSurface,
                                          MbResultType & resType );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить площадь проекции кривой на виртуальную координатную плоскость.
           \en Compute the area of a curve projection onto a virtual coordinate plane. \~
  \details \ru Вычислить площадь проекции кривой на виртуальную координатную плоскость \n
    для определения ориентации образующей кривой в оболочке выдавливания и вращения. \n
    Параметры direction и axis определяют направление выдавливания и ось вращения,
    а параметр rotation определяет тип операции: \n
    - выдавливание, вычисляется площадь проекции на плоскость XOY, \n
    - вращение, вычисляется площадь "проекции" на "плоскость" ROZ.
    Для незамкнутой кривой в расчет добавляется "замыкание отрезком".
           \en Compute the area of a curve projection onto a virtual coordinate plane \n
    to determine the generating curve orientation in the shell of extrusion and revolution. \n
    Parameters 'direction' and 'axis' determine the extrusion direction and the rotation axis,
    and parameter 'rotation' determines the operation type: \n
    - extrusion, the area of projection onto the plane XOY is computed, \n
    - revolution, the area of "projection" to the "plane" ROZ is computed.
    For an open curve "enclosure by a segment" is considered. \~
  \param[in] curve - \ru Кривая.
                     \en The curve. \~
  \param[in] axis - \ru Ось вращения.
                    \en Rotation axis. \~
  \param[in] direction - \ru Направление выдавливания.
                         \en An extrusion direction. \~
  \param[in] rotation - \ru Вращение (true) или выдавливание (false).
                        \en Revolution (true) or extrusion (false). \~
  \return \ru Возвращает площадь проекции.
          \en Returns the projection area. \~
  \warning \ru Вспомогательная функция операций ExtrusionSolid, RevolutionSolid, ExtrusionResult и RevolutionResult.
           \en An auxiliary function of operations ExtrusionSolid, RevolutionSolid, ExtrusionResult and RevolutionResult. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (double) AreaSign( const MbCurve3D &  curve, 
                             const MbAxis3D &   axis, 
                             const MbVector3D & direction, 
                                   bool         rotation );


//------------------------------------------------------------------------------
/** \brief \ru Определить ориентацию секущей грани относительно тела выдавливания/вращения.
           \en Determine the orientation of a cutting surface relative to the extrusion/revolution solid. \~
  \details \ru Определить ориентацию секущей поверхности относительно тела, которое будет строиться 
    путём выдавливания или вращения образующей кривой до заданной поверхности. \n
           \en Determine the orientation of a cutting surface relative to the solid which is to be constructed 
    by extrusion or revolution the generation curve up to the specified surface. \n \~
  \param[in] cuttingSurface - \ru Поверхность для анализа.
                              \en A surface to analyze. \~
  \param[in] imagePosition - \ru Место образа на поверхности.
                             \en An image location on the surface. \~
  \param[in] curve - \ru Образующая кривая.
                     \en The generating curve. \~
  \param[in] direction - \ru Направление выдавливания.
                         \en An extrusion direction. \~
  \param[in] axis - \ru Ось вращения.
                    \en Rotation axis. \~
  \param[in] rotation - \ru Вращение (true) или выдавливание (false).
                        \en Revolution (true) or extrusion (false). \~
  \param[in] operationDirection - \ru Направление движения: вперед (true) или назад (false).
                                  \en The motion direction: forward (true) or backward (false). \~
  \param[out] relativeSense - \ru Ориентация поверхности по отношению к операции.
                              \en The surface orientation relative to the operation. \~
  \param[out] resType - \ru Код результата операции.
                        \en Operation result code. \~
  \warning \ru Вспомогательная функция операций ExtrusionSolid, RevolutionSolid, ExtrusionResult и RevolutionResult.
           \en An auxiliary function of operations ExtrusionSolid, RevolutionSolid, ExtrusionResult and RevolutionResult. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (void) AnalyzeSurfaceRelationToSweptOperation( const MbSurface &   cuttingSurface,
                                                         const MbCartPoint & imagePosition,
                                                         const MbCurve3D &   curve,
                                                         const MbVector3D &  direction,
                                                         const MbAxis3D &    axis,
                                                         const bool          rotation,
                                                               bool          operationDirection,
                                                               bool &        relativeSense,
                                                               MbResultType& resType );


//------------------------------------------------------------------------------
/** \brief \ru Найти сегменты контура на поверхности, соответствующие швам и полюсам.
           \en Find contour segments corresponding to the seams and poles. \~
  \details \ru Найти сегменты контура на поверхности, соответствующие швам и полюсам. \n
           \en Find contour segments corresponding to the seams and poles. \n \~
  \param[in] surface - \ru Поверхность.
                       \en Surface. \~
  \param[in] contour - \ru Контур.
                       \en Contour. \~
  \param[out] seamsAndPoles - \ru Номера сегментов, соответствующих швам и полюсам.
                              \en Segment numbers corresponding to the seams and poles. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (void) FindPolesAndSeamsInContour( const MbSurface &    surface, 
                                             const MbContour &    contour,
                                             c3d::IndicesVector & seamsAndPoles );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело выдавливания.
           \en Create an extrusion solid. \~
  \details \ru Создать тело выдавливания. \n
    solid1 и solid2 используются с опцией "До ближайших граней" этих тел. \n
           \en Create an extrusion solid. \n
    solid1 and solid2 are used with option "Up to the closest faces" of these solids. \n \~
  \param[in]      sweptData         - \ru Данные об образующей кривой.
                                      \en The generating curve data. \~
  \param[in]      direction         - \ru Направление выдавливания.
                                      \en An extrusion direction. \~
  \param[in]      solid1            - \ru До ближайших граней этого тела в прямом направлении.
                                      \en Up to the closest faces of this solid in the forward direction. \~
  \param[in]      solid2            - \ru До ближайших граней этого тела в обратном направлении.
                                      \en Up to the closest faces of this solid in the backward direction. \~
  \param[in]      checkIntersection - \ru Объединять тела solid1 и solid2 с проверкой пересечения.
                                      \en Whether to union the solids solid1 and solid2 with the check for intersections. \~
  \param[in, out] params            - \ru Параметры выдавливания.
    Возвращают информацию для построения элементов массива операций до поверхности.
                                      \en The extrusion parameters.
    Returns the information for construction of the up-to-surface operation array elements. \~
  \param[in]      operNames         - \ru Именователь операции.
                                      \en An object defining names generation in the operation. \~
  \param[in]      contoursNames     - \ru Именователи сегментов образующего контура.
                                      \en An objects defining a names of the generating contour segments. \~
  \param[out]     result            - \ru Построенная оболочка (тело).
                                      \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) ExtrusionSolid( const MbSweptData &           sweptData, 
                                         const MbVector3D &            direction,
                                         const MbSolid *               solid1,
                                         const MbSolid *               solid2, 
                                               bool                    checkIntersection,
                                         const ExtrusionValues &       params, 
                                         const MbSNameMaker &          operNames, 
                                         const RPArray<MbSNameMaker> & contoursNames,
                                               MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело вращения.
           \en Create a solid of revolution. \~
  \details \ru Создать тело вращения по данным об образующей. \n
           \en Create a solid of revolution by the generating curve data. \n \~
  \param[in]      sweptData     - \ru Данные об образующей кривой.
                                  \en The generating curve data. \~
  \param[in]      axis          - \ru Ось вращения.
                                  \en Rotation axis. \~
  \param[in, out] params        - \ru Параметры вращения.
    Возвращают информацию для построения элементов массива операций до поверхности.
                                  \en The revolution parameters.
    Returns the information for construction of the up-to-surface operation array elements. \~
  \param[in]      operNames     - \ru Именователь операции.
                                  \en An object defining names generation in the operation. \~
  \param[in]      contoursNames - \ru Именователи сегментов образующего контура.
                                  \en An objects defining a names of the generating contour segments. \~
  \param[out]     result        - \ru Построенная оболочка (тело).
                                  \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) RevolutionSolid( const MbSweptData &           sweptData,
                                          const MbAxis3D &              axis,
                                          const RevolutionValues &      params, 
                                          const MbSNameMaker &          operNames, 
                                          const RPArray<MbSNameMaker> & contoursNames,
                                                MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать кинематическое тело.
           \en Create a sweeping solid. \~
  \details \ru Создать кинематическое тело путем движения образующей кривой вдоль направляющей кривой. \n
           \en Create a sweeping solid by moving the generating curve along the guide curve. \n \~
  \param[in]  sweptData     - \ru Данные об образующей.
                              \en The generating curve data. \~
  \param[in]  spine         - \ru Направляющая кривая.
                              \en The spine curve. \~
  \param[in]  params        - \ru Параметры операции.
                              \en The operation parameters. \~
  \param[in]  operNames     - \ru Именователь операции.
                              \en An object defining names generation in the operation. \~
  \param[in]  contoursNames - \ru Именователь контуров образующей.
                              \en An object defining the names of generating curve contours. \~
  \param[in]  spineNames    - \ru Именователь направляющей.
                              \en An object defining the name of a guide curve. \~
  \param[out] result        - \ru Построенная оболочка (тело).
                              \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) EvolutionSolid( const MbSweptData &           sweptData, 
                                         const MbCurve3D &             spine,
                                         const EvolutionValues &       params, 
                                         const MbSNameMaker &          operNames,
                                         const RPArray<MbSNameMaker> & contoursNames, 
                                         const MbSNameMaker &          spineNames, 
                                               MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать кинематическое тело.
           \en Create a sweeping solid. \~
  \details \ru Создать кинематическое тело путем движения образующей кривой вдоль направляющей кривой c дополнительной информацией. \n
           \en Create a sweeping solid by moving the generating curve along the guide curve with additional data. \n \~
  \param[in]  sweptData     - \ru Данные об образующей.
                              \en The generating curve data. \~
  \param[in]  spine         - \ru Направляющая кривая c дополнительной информацией.
                              \en The spine curve with additional data. \~
  \param[in]  params        - \ru Параметры операции.
                              \en The operation parameters. \~
  \param[in]  operNames     - \ru Именователь операции.
                              \en An object defining names generation in the operation. \~
  \param[in]  contoursNames - \ru Именователь контуров образующей.
                              \en An object defining the names of generating curve contours. \~
  \param[in]  spineNames    - \ru Именователь направляющей.
                              \en An object defining the name of a guide curve. \~
  \param[out] result        - \ru Построенная оболочка (тело).
                              \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) EvolutionSolid( const MbSweptData &           sweptData, 
                                         const MbSpine &               spine,
                                         const EvolutionValues &       params, 
                                         const MbSNameMaker &          operNames,
                                         const RPArray<MbSNameMaker> & contoursNames, 
                                         const MbSNameMaker &          spineNames, 
                                               MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по плоским сечениям.
           \en Create a solid from a planar sections. \~
  \details \ru Создать тело по плоским сечениям c направляющей линией. \n
           \en Create a solid from a planar sections with a guide curve. \n \~
  \param[in] pl - \ru Множество систем координат образующих контуров.
                  \en An array of generating contours coordinate systems. \~
  \param[in] c - \ru Множество образующих контуров.
                 \en An array of generating contours. \~
  \param[in] spine - \ru Направляющая кривая (может быть NULL).
                     \en A guide curve (can be NULL). \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] ps - \ru Множество точек на образующих контурах, задающий их начальные точки.
                  \en A point array on the generating contours which determines the start points of the contours. \~
  \param[in] names - \ru Именователь операции.
                     \en An object defining names generation in the operation. \~
  \param[in] ns - \ru Именователи образующих контуров.
                  \en The objects defining the names of generating contours. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) LoftedSolid(       SArray<MbPlacement3D> & pl,
                                            RPArray<MbContour> &    c,
                                      const MbCurve3D *             spine,
                                      const LoftedValues &          params,
                                            SArray<MbCartPoint3D> * ps,
                                      const MbSNameMaker &          names,
                                            RPArray<MbSNameMaker> & ns,
                                            MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по пространственным сечениям.
           \en Create a solid from a space sections. \~
  \details \ru Создать тело по пространственным сечениям c направляющей линией. \n
           \en Create a solid from a space sections with a guide curve. \n \~
  \param[in] pl - \ru Множество систем координат образующих контуров.
                  \en An array of generating contours coordinate systems. \~
  \param[in] c - \ru Множество образующих контуров.
                 \en An array of generating contours. \~
  \param[in] spine - \ru Осевая кривая (может быть NULL).
                     \en A guide curve (can be NULL). \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] guideCurves - \ru Множество направляющих кривых, задающих траектории соответствующих точек контуров.
                           \en An array of the guide curves that determines the trajectories of the corresponding points of the contours. \~
  \param[in] ps - \ru Множество точек на образующих контурах, задающее соответствующие точки (цепочки точек).
                  \en A point array on the generating contours which determines the corresponding points of the contours (chains of points). \~
  \param[in] names - \ru Именователь операции.
                     \en An object defining names generation in the operation. \~
  \param[in] ns - \ru Именователи образующих контуров.
                  \en The objects defining the names of generating contours. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) LoftedSolid(       SArray<MbPlacement3D> & pl,
                                            RPArray<MbContour> &    c,
                                      const MbCurve3D *             spine, // осевая линия может быть NULL
                                      const LoftedValues &          params,
                                            RPArray<MbCurve3D> *    guideCurves,
                                            SArray<MbCartPoint3D> * ps,
                                      const MbSNameMaker &          names,
                                            RPArray<MbSNameMaker> & ns,
                                            MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по пространственным сечениям.
           \en Create a solid from a space sections. \~
  \details \ru Создать тело по пространственным сечениям c направляющей линией. \n
           \en Create a solid from a space sections with a guide curve. \n \~
  \param[in] surfs - \ru Множество поверхностей образующих контуров.
                     \en An array of surfaces of generating contours. \~
  \param[in] c - \ru Множество образующих контуров.
                 \en An array of generating contours. \~
  \param[in] spine - \ru Осевая кривая (может быть NULL).
                     \en A guide curve (can be NULL). \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] guideCurves - \ru Множество направляющих кривых, задающих траектории соответствующих точек контуров.
                           \en An array of the guide curves that determines the trajectories of the corresponding points of the contours. \~
  \param[in] ps - \ru Множество точек на образующих контурах, задающее соответствующие точки (цепочки точек).
                  \en A point array on the generating contours which determines the corresponding points of the contours (chains of points). \~
  \param[in] names - \ru Именователь операции.
                     \en An object defining names generation in the operation. \~
  \param[in] ns - \ru Именователи образующих контуров.
                  \en The objects defining the names of generating contours. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) LoftedSolid(       RPArray<MbSurface> &    surfs,
                                            RPArray<MbContour> &    c,
                                      const MbCurve3D *             spine, // осевая линия может быть NULL
                                      const LoftedValues &          params,
                                            RPArray<MbCurve3D> *    guideCurves,
                                            SArray<MbCartPoint3D> * ps,
                                      const MbSNameMaker &          names,
                                            RPArray<MbSNameMaker> & ns,
                                            MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело выдавливания и выполнить булеву операцию.
           \en Create an extrusion solid and perform a boolean operation. \~
  \details \ru Создать тело выдавливания и выполнить булеву операцию типа oType с телом solid. 
    Принимаемые значения OperationType для тел: \n
    bo_Union      - объединение, \n
    bo_Intersect  - пересечение, \n
    bo_Difference - вычитание.
           \en Create an extrusion solid and perform a boolean operation of type 'oType' with solid 'solid'. 
    The possible values of 'OperationType' for solids: \n
    bo_Union      - union, \n
    bo_Intersect  - intersection, \n
    bo_Difference - subtraction. \~
  \param[in]       solid         - \ru Первое тело для булевой операции.
                                   \en The first solid for a boolean operation. \~
  \param[in]       sameShell     - \ru Режим копирования тела.
                                   \en Whether to copy the solid. \~
  \param[in]       sweptData     - \ru Данные об образующих кривых.
                                   \en The generating curve data. \~
  \param[in]       direction     - \ru Направление выдавливания.
                                   \en An extrusion direction. \~
  \param[in, out]  params        - \ru Параметры выдавливания.
    Возвращают информацию для построения элементов массива операций до поверхности.
                                   \en The extrusion parameters.
    Returns the information for construction of the up-to-surface operation array elements. \~
  \param[in]       oType         - \ru Тип булевой операции.
                                   \en A boolean operation type. \~
  \param[in]       operNames     - \ru Именователь операции.
                                   \en An object defining names generation in the operation. \~
  \param[in]       contoursNames - \ru Именователи образующих кривых.
                                   \en The objects defining the names of generating lines. \~
  \param[out]      result        - \ru Построенное тело.
                                   \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) ExtrusionResult(       MbSolid &               solid, 
                                                MbeCopyMode             sameShell, 
                                          const MbSweptData &           sweptData,
                                          const MbVector3D &            direction,
                                          const ExtrusionValues &       params, 
                                                OperationType           oType, 
                                          const MbSNameMaker &          operNames, 
                                          const RPArray<MbSNameMaker> & contoursNames,
                                                MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело вращения и выполнить булеву операцию.
           \en Create a revolution solid and perform a boolean operation. \~
  \details \ru Создать тело вращения и выполнить булеву операцию типа oType с телом solid. 
    Принимаемые значения OperationType для тел: \n
    bo_Union      - объединение, \n
    bo_Intersect  - пересечение, \n
    bo_Difference - вычитание.
           \en Create a revolution solid and perform a boolean operation of type oType with solid 'solid'. 
    The possible values of 'OperationType' for solids: \n
    bo_Union      - union, \n
    bo_Intersect  - intersection, \n
    bo_Difference - subtraction. \~
  \param[in]       solid         - \ru Первое тело для булевой операции.
                                   \en The first solid for a boolean operation. \~
  \param[in]       sameShell     - \ru Режим копирования тела.
                                   \en Whether to copy the solid. \~
  \param[in]       sweptData     - \ru Данные об образующих кривых.
                                   \en The generating curve data. \~
  \param[in]       axis          - \ru Ось вращения.
                                   \en Rotation axis. \~
  \param[in, out]  params        - \ru Параметры вращения.
    Возвращают информацию для построения элементов массива операций до поверхности.
                                   \en The revolution parameters.
    Returns the information for construction of the up-to-surface operation array elements. \~
  \param[in]       oType         - \ru Тип булевой операции.
                                   \en A boolean operation type. \~
  \param[in]       operNames     - \ru Именователь операции.
                                   \en An object defining names generation in the operation. \~
  \param[in]       contoursNames - \ru Именователи образующих кривых.
                                   \en The objects defining the names of generating lines. \~
  \param[out]      result        - \ru Построенное тело.
                                   \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) RevolutionResult(       MbSolid &               solid, 
                                                 MbeCopyMode             sameShell,
                                           const MbSweptData &           sweptData,
                                           const MbAxis3D &              axis,
                                           const RevolutionValues &      params, 
                                                 OperationType           oType, 
                                           const MbSNameMaker &          operNames, 
                                           const RPArray<MbSNameMaker> & contoursNames,
                                                 MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Сориентировать образующий контур и направляющую кинематики.
           \en Determine the orientation for a generating contour and for a guide curve of kinematics (evolution). \~
  \details \ru Выполнить ориентацию образующего контура и направляющей кривой для построения кинематического тела. \n
           \en Orientate the generating contour and the guide curve for a sweeping solid construction. \n \~
  \param[in] surface - \ru Поверхность.
                       \en The surface. \~
  \param[in] contours - \ru Образующие контуры.
                        \en Generating contours. \~
  \param[in] guide - \ru Направляющая кривая.
                     \en The spine curve. \~
  \param[in] parameters - \ru Параметры операции.
                          \en The operation parameters. \~
  \param[out] axis - \ru Ось доворота образующей.
                     \en The axis for the generating curve additional turn. \~
  \param[out] angle - \ru Угол доворота образующей.
                      \en The additional turn for generating line. \~
  \param[in] version - \ru Версия операции.
                       \en The version of the operation. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \warning \ru Вспомогательная функция операций EvolutionSolid и EvolutionResult.
           \en An auxiliary function of operations EvolutionSolid and EvolutionResult. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) EvolutionNormalize( const MbSurface          & surface,
                                             const RPArray<MbContour> & contours,
                                             const MbCurve3D          & guide,
                                             const EvolutionValues    & parameters,
                                                   MbAxis3D           & axis,
                                                   double             & angle,
                                                   VERSION              version );


//------------------------------------------------------------------------------
/** \brief \ru Создать усеченную замкнутую кривую на копии кривой.
           \en Create a trimmed closed curve on a curve copy. \~
  \details \ru Выполнить построение копии замкнутой кривой с началом в точке, определяемой параметром t. \n
           \en Create a copy of a closed curve starting at a point with parameter t. \n \~
  \param[in] curve - \ru Направляющая кривая.
                     \en The spine curve. \~
  \param[in] t - \ru Параметр кривой.
                 \en A curve parameter. \~
  \return \ru При удачной работе функция возвращает построенную копию кривой 
    с началом в заданной точке, в противном случае функция возвращает ноль.
          \en Returns a constructed curve copy starting at the specified point if it has been successfully created, 
    otherwise it returns null. \~
  \warning \ru Вспомогательная функция операций EvolutionSolid и EvolutionResult.
           \en An auxiliary function of operations EvolutionSolid and EvolutionResult. \~
  \ingroup Curve3D_Modeling
*/
// ---
MATH_FUNC (MbCurve3D *) TrimClosedSpine( const MbCurve3D & curve, 
                                               double      t );


//------------------------------------------------------------------------------
/** \brief \ru Создать кинематическое тело и выполнить булеву операцию.
           \en Create an evolution solid and perform a boolean operation. \~
  \details \ru Создать кинематическое тело и выполнить булеву операцию типа oType с телом solid. 
    Принимаемые значения OperationType для тел: \n
    bo_Union      - объединение, \n
    bo_Intersect  - пересечение, \n
    bo_Difference - вычитание.
           \en Create an evolution solid and perform a boolean operation of type oType with solid 'solid'. 
    The possible values of 'OperationType' for solids: \n
    bo_Union      - union, \n
    bo_Intersect  - intersection, \n
    bo_Difference - subtraction. \~
  \param[in]  solid         - \ru Первое тело для булевой операции.
                              \en The first solid for a boolean operation. \~
  \param[in]  sameShell     - \ru Режим копирования тела.
                              \en Whether to copy the solid. \~
  \param[in]  sweptData     - \ru Данные об образующей.
                              \en The generating curve data. \~
  \param[in]  spine         - \ru Направляющая кривая.
                              \en The spine curve. \~
  \param[in]  params        - \ru Параметры кинематической операции.
                              \en Parameters of the sweeping operation. \~
  \param[in]  oType         - \ru Тип булевой операции.
                              \en A boolean operation type. \~
  \param[in]  operNames     - \ru Именователь.
                              \en An object for naming the new objects. \~
  \param[in]  contoursNames - \ru Именователь контуров образующей.
                              \en An object defining the names of generating curve contours. \~
  \param[in]  spineNames    - \ru Именователь направляющей.
                              \en An object defining the name of a guide curve. \~
  \param[out] result        - \ru Построенное тело.
                              \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC(MbResultType) EvolutionResult(       MbSolid &               solid, 
                                               MbeCopyMode             sameShell,
                                         const MbSweptData &           sweptData,
                                         const MbCurve3D &             spine,
                                         const EvolutionValues &       params,
                                               OperationType           oType, 
                                         const MbSNameMaker &          operNames, 
                                         const RPArray<MbSNameMaker> & contoursNames,
                                         const MbSNameMaker &          spineNames, 
                                               MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по плоским сечениям и выполнить булеву операцию.
           \en Create a solid from the planar sections and perform a boolean operation. \~
  \details \ru Создать тело по плоским сечениям и выполнить булеву операцию типа oType с телом solid. 
    Принимаемые значения OperationType для тел: \n
    bo_Union      - объединение, \n
    bo_Intersect  - пересечение, \n
    bo_Difference - вычитание.
           \en Create a solid from a planar sections and perform a boolean operation of type oType with solid 'solid'. 
    The possible values of 'OperationType' for solids: \n
    bo_Union      - union, \n
    bo_Intersect  - intersection, \n
    bo_Difference - subtraction. \~
  \param[in] solid - \ru Первое тело для булевой операции.
                     \en The first solid for a boolean operation. \~
  \param[in] sameShell - \ru Режим копирования тела.
                         \en Whether to copy the solid. \~
  \param[in] pl - \ru Множество систем координат образующих контуров.
                  \en An array of generating contours coordinate systems. \~
  \param[in] c - \ru Множество образующих контуров.
                 \en An array of generating contours. \~
  \param[in] spine - \ru Направляющая кривая (может быть NULL).
                     \en A guide curve (can be NULL). \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] oType - \ru Тип булевой операции.
                     \en A boolean operation type. \~
  \param[in] ps - \ru Множество точек на образующих контурах, задающий их начальные точки.
                  \en A point array on the generating contours which determines the start points of the contours. \~
  \param[in] names - \ru Именователь операции.
                     \en An object defining names generation in the operation. \~
  \param[in] ns - \ru Именователи образующих контуров.
                  \en The objects defining the names of generating contours. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC(MbResultType) LoftedResult(       MbSolid &               solid,
                                            MbeCopyMode             sameShell,
                                            SArray<MbPlacement3D> & pl,
                                            RPArray<MbContour> &    c,
                                      const MbCurve3D *             spine,
                                      const LoftedValues &          params,
                                            OperationType           oType,
                                            SArray<MbCartPoint3D> * ps,
                                      const MbSNameMaker &          names,
                                            RPArray<MbSNameMaker> & ns,
                                            MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по пространственным сечениям и выполнить булеву операцию.
           \en Create a solid from the space sections and perform a boolean operation. \~
  \details \ru Создать тело по пространственным сечениям и выполнить булеву операцию типа oType с телом solid. 
    Принимаемые значения OperationType для тел: \n
    bo_Union      - объединение, \n
    bo_Intersect  - пересечение, \n
    bo_Difference - вычитание.
           \en Create a solid from a space sections and perform a boolean operation of type oType with solid 'solid'. 
    The possible values of 'OperationType' for solids: \n
    bo_Union      - union, \n
    bo_Intersect  - intersection, \n
    bo_Difference - subtraction. \~
  \param[in] solid - \ru Первое тело для булевой операции.
                     \en The first solid for a boolean operation. \~
  \param[in] sameShell - \ru Режим копирования тела.
                         \en Whether to copy the solid. \~
  \param[in] surfs - \ru Множество поверхностей контуров.
                     \en An array of generating contours surfaces. \~
  \param[in] c - \ru Множество образующих контуров.
                 \en An array of generating contours. \~
  \param[in] spine - \ru Осевая кривая (может быть NULL).
                     \en A guide curve (can be NULL). \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] oType - \ru Тип булевой операции.
                     \en A boolean operation type. \~
  \param[in] guideCurves - \ru Массив направляющих кривых.
                           \en An array of the guide curves. \~
  \param[in] ps - \ru Множество точек на образующих контурах, задающий их начальные точки.
                  \en A point array on the generating contours which determines the start points of the contours. \~
  \param[in] names - \ru Именователь операции.
                     \en An object defining names generation in the operation. \~
  \param[in] ns - \ru Именователи образующих контуров.
                  \en The objects defining the names of generating contours. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC(MbResultType) LoftedResult(       MbSolid &               solid,
                                            MbeCopyMode             sameShell,
                                            RPArray<MbSurface> &    surfs,
                                            RPArray<MbContour> &    c,
                                      const MbCurve3D *             spine,
                                      const LoftedValues &          params,
                                            OperationType           oType,
                                            RPArray<MbCurve3D> *    guideCurves,
                                            SArray<MbCartPoint3D> * ps,
                                      const MbSNameMaker &          names,
                                            RPArray<MbSNameMaker> & ns,
                                            MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Выполнить булеву операцию.
           \en Perform a Boolean operation. \~
  \details \ru Функция выполняет указанную булеву операцию над двумя телами с возможностью управления слиянием граней и рёбер.\n
           \en The function performs the specified Boolean operation on two solids with faces and edges merging control.\n \~
  \param[in]  solid1         - \ru Набор граней первого тела.
                               \en The set of faces of the first solid. \~
  \param[in]  sameShell1     - \ru Способ копирования граней первого тела.
                               \en Method of copying the faces of the first solid. \~
  \param[in]  solid2         - \ru Набор граней второго тела.
                               \en The second solid face set. \~
  \param[in]  sameShell2     - \ru Способ копирования граней второго тела.
                               \en Method of copying the faces of the second solid. \~
  \param[in]  oType          - \ru Тип булевой операции.
                               \en A Boolean operation type. \~
  \param[in]  flags          - \ru Управляющие флаги булевой операции.
                               \en Control flags of the Boolean operation. \~
  \param[in]  operNames      - \ru Именователь операции.
                               \en An object defining names generation in the operation. \~
  \param[out] result         - \ru Построенный набор граней.
                               \en Constructed set of faces. \~  
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) BooleanResult(       MbSolid &        solid1, 
                                              MbeCopyMode      sameShell1,
                                              MbSolid &        solid2, 
                                              MbeCopyMode      sameShell2,
                                              OperationType    oType,
                                        const MbBooleanFlags & flags,
                                        const MbSNameMaker &   operNames,
                                              MbSolid *&       result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело путем булевой операции.
           \en Create a solid using a boolean operation. \~
  \details \ru Создать тело путем булевой операции типа oType для тел solid1 и solid2. 
    Принимаемые значения OperationType для тел: \n
    bo_Union      - объединение, \n
    bo_Intersect  - пересечение, \n
    bo_Difference - вычитание. \n
    Функция работает только с замкнутыми телами, сливает подобные грани и рёбра. 
    Функция выполняет одноимённую булеву операцию над множествами точек,
    расположенными внутри и на поверхности тел.
           \en Create a solid by applying a boolean operation of type oType to solids 'solid1' and 'solid2'. 
    The possible values of 'OperationType' for solids: \n
    bo_Union      - union, \n
    bo_Intersect  - intersection, \n
    bo_Difference - subtraction. \n
    The function accepts only closed solids, similar faces and similar edges will be merged. 
    The function performs a boolean operation of the same name with a point sets
    located inside the solids and on their boundary. \~
  \param[in] solid1 - \ru Первое тело.
                      \en The first solid. \~
  \param[in] sameShell1 - \ru Режим копирования первого тела.
                          \en Whether to copy the first solid. \~
  \param[in] solid2 - \ru Второе тело.
                      \en The second solid. \~
  \param[in] sameShell2 - \ru Режим копирования второго тела.
                          \en Whether to copy the second solid. \~
  \param[in] oType - \ru Тип булевой операции.
                     \en A boolean operation type. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) BooleanSolid(       MbSolid &      solid1, 
                                             MbeCopyMode    sameShell1,
                                             MbSolid &      solid2,
                                             MbeCopyMode    sameShell2,
                                             OperationType  oType,
                                       const MbSNameMaker & names,
                                             MbSolid *&     result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело путем булевой операции.
           \en Create a solid using a boolean operation. \~
  \details \ru Создать тело путем булевой операции типа oType для оболочек solid1 и solid2.
    Один из операндов solid1 или solid2 - незамкнутая оболочка. 
    Принимаемые значения OperationType для оболочек: \n
      bo_Variety  - объединение, \n
      bo_Internal - пересечение, \n
      bo_External - вычитание.
           \en Create a solid applying a boolean operation of type oType to shells 'solid1' and solid2'.
    One of the operands 'solid1' and 'solid2' should be an open shell. 
    Possible values of 'OperationType' for a shells are: \n
      bo_Variety  - a union, \n
      bo_Internal - an intersection, \n
      bo_External - a subtraction. \~
  \param[in] solid1 - \ru Первое тело.
                      \en The first solid. \~
  \param[in] sameShell1 - \ru Режим копирования первого тела.
                          \en Whether to copy the first solid. \~
  \param[in] solid2 - \ru Второе тело.
                      \en The second solid. \~
  \param[in] sameShell2 - \ru Режим копирования второго тела.
                          \en Whether to copy the second solid. \~
  \param[in] oType - \ru Тип булевой операции.
                     \en A boolean operation type. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) BooleanShell(       MbSolid &      solid1,
                                             MbeCopyMode    sameShell1,
                                             MbSolid &      solid2,
                                             MbeCopyMode    sameShell2,
                                             OperationType  oType,
                                       const MbSNameMaker & names,
                                             MbSolid *&     result );


//------------------------------------------------------------------------------
/** \brief \ru Отрезать часть тела поверхностью.
           \en Cut a part of a solid off by a surface. \~
  \details \ru Отрезать часть тела пересекающей его поверхностью. \n
    part =  1 - оставляем часть тела, расположенную сверху поверхности. \n
    part = -1 - оставляем часть тела, расположенную снизу  поверхности. \n
           \en Cut a part of a solid off by a surface that intersects the solid. \n
    part =  1 - a part of solid above the surface is to be retained. \n
    part = -1 - a part of solid below the surface is to be retained. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования исходного тела.
                         \en The mode of copying of the source solid. \~
  \param[in] surface - \ru Секущая поверхность.
                       \en A cutting plane. \~
  \param[in] retainedPart - \ru Направление отсечения.
                            \en The direction of cutting off. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] closed - \ru Флаг режима отсечения: true - сечем как тело, false - сечем как оболочку.
                      \en The flag of the cutting off mode: true - cut as a solid, false - cut as a shell. \~
  \param[in] flags - \ru Флаги слияния элементов оболочки.
                     \en Control flags of shell items merging. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) SolidCutting(       MbSolid &        solid, 
                                             MbeCopyMode      sameShell,
                                       const MbSurface &      surface, 
                                             int              retainedPart,
                                       const MbSNameMaker &   names,
                                             bool             closed,
                                       const MbMergingFlags & flags,
                                             MbSolid *&       result );


//------------------------------------------------------------------------------
/** \brief \ru Отрезать часть тела выдавленным плоским контуром.
           \en Cut a part of a solid off with an extruded planar contour. \~ 
  \details \ru Отрезать часть тела оболочкой, полученной выдавливанием плоского контура. \n
    part =  1 - оставляем часть тела, расположенную сверху поверхности выдавливания. \n
    part = -1 - оставляем часть тела, расположенную снизу  поверхности выдавливания. \n
           \en Cut a part of a solid by a shell of planar contour extrusion. \n
    part =  1 - a part of solid above the extrusion surface is to be retained. \n
    part = -1 - a part of solid below the extrusion surface is to be retained. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] place - \ru Система координат образующего контура.
                     \en The generating contour coordinate system. \~
  \param[in] contour - \ru Образующий контур.
                       \en The generating contour. \~
  \param[in] direction - \ru Направление выдавливания образующего контура.
                         \en An extrusion direction of the generating contour. \~
  \param[in] retainedPart - \ru Направление отсечения.
                            \en The direction of cutting off. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] closed - \ru Флаг режим отсечения: true - сечем как тело, false - сечем как оболочку.
                      \en The cutting off mode flag: true - cut as a solid, false - cut as a shell. \~
  \param[in] flags - \ru Флаги слияния элементов оболочки.
                     \en Control flags of shell items merging. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) SolidCutting(       MbSolid &        solid, 
                                             MbeCopyMode      sameShell,
                                       const MbPlacement3D &  place, 
                                       const MbContour &      contour,
                                       const MbVector3D &     direction, 
                                             int              retainedPart, 
                                       const MbSNameMaker &   names,
                                             bool             closed, 
                                       const MbMergingFlags & flags,
                                             MbSolid *&       result );


//------------------------------------------------------------------------------
/** \brief \ru Разрезать тело поверхностью.
           \en Cut a solid off by a surface. \~
  \details \ru Разрезать тело поверхностью с построением всех отрезанных частей. \n
           \en Cut a solid off by a surface, keep all parts of the solid. \n
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования исходного тела. При sameShell != cm_Copy построенные тела нельзя перемещать относительно друг друга.
                         \en Whether to copy the source solid. Built bodies can not move relative to each other when sameShell != Vm_Copy. \~
  \param[in] surface - \ru Секущая поверхность.
                       \en A cutting plane. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] closed - \ru Флаг режима отсечения: true - сечем как тело, false - сечем как оболочку.
                      \en The flag of the cutting off mode: true - cut as a solid, false - cut as a shell. \~
  \param[in] flags - \ru Флаги слияния элементов оболочки.
                     \en Control flags of shell items merging. \~
  \param[out] result - \ru Построенные тела.
                       \en The resultant solids. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
DEPRECATE_DECLARE
MATH_FUNC (MbResultType) SolidCutting(       MbSolid &          solid, 
                                             MbeCopyMode        sameShell,
                                       const MbSurface &        surface, 
                                       const MbSNameMaker &     names,
                                             bool               closed,
                                       const MbMergingFlags &   flags,
                                             RPArray<MbSolid> & result );


//------------------------------------------------------------------------------
/** \brief \ru Разрезать тело выдавленным плоским контуром.
           \en Cut a solid off with an extruded planar contour. \~ 
  \details \ru Разрезать тело оболочкой, полученной выдавливанием плоского контура, с построением всех отрезанных частей. \n
           \en Cut a solid by a shell of planar contour extrusion, keep all parts of the solid. \n
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования исходного тела. При sameShell != cm_Copy построенные тела нельзя перемещать относительно друг друга.
                         \en Whether to copy the source solid. Built bodies can not move relative to each other when sameShell != Vm_Copy. \~
  \param[in] place - \ru Система координат образующего контура.
                     \en The generating contour coordinate system. \~
  \param[in] contour - \ru Образующий контур.
                       \en The generating contour. \~
  \param[in] direction - \ru Направление выдавливания образующего контура.
                         \en An extrusion direction of the generating contour. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] closed - \ru Флаг режим отсечения: true - сечем как тело, false - сечем как оболочку.
                      \en The cutting off mode flag: true - cut as a solid, false - cut as a shell. \~
  \param[in] flags - \ru Флаги слияния элементов оболочки.
                     \en Control flags of shell items merging. \~
  \param[out] result - \ru Построенные тела.
                       \en The resultant solids. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
DEPRECATE_DECLARE
MATH_FUNC (MbResultType) SolidCutting(       MbSolid &          solid, 
                                             MbeCopyMode        sameShell,
                                       const MbPlacement3D &    place, 
                                       const MbContour &        contour,
                                       const MbVector3D &       direction, 
                                       const MbSNameMaker &     names,
                                             bool               closed,
                                       const MbMergingFlags &   flags,
                                             RPArray<MbSolid> & result );


//------------------------------------------------------------------------------
/** \brief \ru Разрезать тело на части.
           \en Cut a solid into parts. \~
  \details \ru Разрезать тело на части. \n
           \en Cut a solid into parts. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in]  sameShell - \ru Режим копирования исходного тела.
                          \en The mode of copying of the source solid. \~
  \param[in]  cuttingParams - \ru Параметры операции.
                              \en Operation parameters. \~
  \param[out] results - \ru Построенные тела.
                       \en The resultant solids. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) SolidCutting(       MbSolid &              solid, 
                                             MbeCopyMode            sameShell,
                                       const MbShellCuttingParams & cuttingParams, 
                                             RPArray<MbSolid> &     results );


//------------------------------------------------------------------------------
/** \brief \ru Создать симметричное тело относительно плоскости.
           \en Create a symmetric solid relative to a plane. \~
  \details \ru Создать симметричное тело относительно плоскости XY локальной системы координат. \n
    Функция создаёт симметричное тело с заданной плоскостью симметрии следующим образом. 
    Исходное тело режется плоскостью XY локальной системы координат, берётся часть исходного тела, 
    расположенная сверху режущей плоскости, строится зеркальная копия выбранной части исходного тела
    и объединяется с выбранной частью исходного тела. \n
           \en Crate a symmetric solid relative to XY-plane of a local coordinate system. \n
    The function creates a symmetric solid with the specified plane of symmetry in the following way. 
    The source solid is cut off by the plane XY of the local coordinate system; a part of the source solid above the cutting plane 
    is retained. A mirror copy of the chosen part is created
    and then is united with the chosen part of the source solid. \n \~
  \param[in] solid - \ru Исходная оболочка.
                     \en The source shell. \~
  \param[in] sameShell - \ru Режим копирования оболочки.
                         \en Whether to copy the shell. \~
  \param[in] place - \ru Система координат плоскости симметрии.
                     \en The symmetry plane coordinate system. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) SymmetrySolid(       MbSolid &       solid, 
                                              MbeCopyMode     sameShell,
                                        const MbPlacement3D & place, 
                                        const MbSNameMaker &  names,
                                              MbSolid *&      result );


//------------------------------------------------------------------------------
/** \brief \ru Создать зеркальную копию тела относительно плоскости.
           \en Create a mirror copy of a solid relative to a plane. \~
  \details \ru Создать зеркальную копию тела относительно плоскости XY локальной системы координат. \n
           \en Create a mirror copy of a solid relative to the XY-plane of a local coordinate system. \n \~
  \param[in] solid - \ru Исходная оболочка.
                     \en The source shell. \~
  \param[in] place - \ru Система координат плоскости симметрии.
                     \en The symmetry plane coordinate system. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) MirrorSolid( const MbSolid &       solid, 
                                      const MbPlacement3D & place, 
                                      const MbSNameMaker &  names,
                                            MbSolid *&      result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело с ребром жёсткости.
           \en Create a solid with a rib. \~
  \details \ru Создать тело с ребром жёсткости. \n
    По заданному контуру функция строит ребро жёсткости и объединяет его с исходным телом. 
    Сегмент контура с указанным номером устанавливает вектор уклона. \n
           \en Create a solid with a rib. \n
    The function creates a rib from a given contour and unites it with the source solid. 
    The segment of the contour with the given number determines the slope vector. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] place - \ru Система координат образующего контура.
                     \en The generating contour coordinate system. \~
  \param[in] contour - \ru Формообразующий контур на плоскости XY системы координат place.
                       \en The generating contour on XY-plane of coordinate system 'place'. \~
  \param[in] index - \ru Номер сегмента в контуре.
                     \en The segment number in the contour. \~
  \param[in] pars - \ru Параметры ребра жёсткости.
                    \en Parameters of a rib. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) RibSolid(       MbSolid &       solid, 
                                         MbeCopyMode     sameShell,
                                   const MbPlacement3D & place, 
                                   const MbContour &     contour,
                                         size_t          index, 
                                         RibValues &     pars, 
                                   const MbSNameMaker &  names,
                                         MbSolid *&      result );


//------------------------------------------------------------------------------
/** \brief \ru Создать отдельное ребро жёсткости.
           \en Create a separate rib. \~
  \details \ru Создать отдельное ребро жёсткости для исходного тела без приклеивания. \n
           \en Create a separate rib for source solid without gluing. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] place - \ru Система координат образующего контура.
                     \en The generating contour coordinate system. \~
  \param[in] contour - \ru Образующий контур.
                       \en The generating contour. \~
  \param[in] index - \ru Номер сегмента в контуре.
                     \en The segment number in the contour. \~
  \param[in] pars - \ru Параметры ребра жёсткости.
                    \en Parameters of a rib. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) RibElement( const MbSolid &       solid, 
                                     const MbPlacement3D & place, 
                                           MbContour &     contour,
                                           size_t          index, 
                                           RibValues &     pars, 
                                     const MbSNameMaker &  names,
                                           MbSolid *&      result );


//------------------------------------------------------------------------------
/** \brief \ru Скруглить ребра постоянным радиусом.
           \en Fillet edges with a constant radius. \~
  \details \ru Скруглить указанные рёбра тела постоянным радиусом. \n
    Функция выполняет замену указанных рёбер исходного тела гранями, 
    гладко сопрягающими смежные грани указанных рёбер. В поперечном сечении 
    сопрягающие грани могут иметь форму дуги окружности, эллипса, гиперболы, параболы. \n
           \en Fillet the specified edges of the solid with a constant radius. \n
    The function performs the replacement of the specified edges of the source solid by faces 
    smoothly connecting the adjacent faces of the specified edges. The cross-section 
    of the connecting faces can be of the form of a circle, an ellipse, a hyperbola or a parabola. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] initCurves - \ru Множество скругляемых ребер тела.
                          \en A set of edges of the solid to fillet. \~
  \param[in] initBounds - \ru Множество граней для обрезки торцов.
                          \en A set of faces for trimming of the butt-ends. \~
  \param[in] params - \ru Параметры скругления рёбер.
                      \en Parameters of edges fillet. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) FilletSolid(       MbSolid &              solid, 
                                            MbeCopyMode            sameShell,
                                            RPArray<MbCurveEdge> & initCurves, 
                                            RPArray<MbFace> &      initBounds, 
                                      const SmoothValues &         params, 
                                      const MbSNameMaker &         names, 
                                            MbSolid *&             result );


//------------------------------------------------------------------------------
/** \brief \ru Скруглить ребра переменным радиусом.
           \en Fillet edges with a variable radius. \~
  \details \ru Скруглить указанные ребра тела переменным радиусом, задаваемым MbEdgeFunction.function. \n
    Функция выполняет замену указанных рёбер исходного тела гранями, 
    гладко сопрягающими смежные грани указанных рёбер. В поперечном сечении 
    сопрягающие грани могут иметь форму дуги окружности, эллипса, гиперболы, параболы. 
    Параметры поперечного сечения могут изменяться по заданному закону. \n
           \en Fillet the given edges of the solid with a variable radius specified by MbEdgeFunction.function. \n
    The function performs the replacement of the specified edges of the source solid by faces 
    smoothly connecting the adjacent faces of the specified edges. The cross-section 
    of the connecting faces can be of the form of a circle, an ellipse, a hyperbola or a parabola. 
    The parameters of the cross-section can vary by the specified law. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] initCurves - \ru Множество скругляемых ребер тела с функциями изменения радиуса.
                          \en An array of edges of the solid to fillet together with the radius laws. \~
  \param[in] initBounds - \ru Множество граней для обрезки торцов.
                          \en A set of faces for trimming of the butt-ends. \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) FilletSolid(       MbSolid &                solid, 
                                            MbeCopyMode              sameShell,
                                            SArray<MbEdgeFunction> & initCurves, 
                                            RPArray<MbFace> &        initBounds, 
                                      const SmoothValues &           params, 
                                      const MbSNameMaker &           names, 
                                            MbSolid *&               result );


//------------------------------------------------------------------------------
/** \brief \ru Скруглить вершины и примыкающие к ней рёбра постоянным радиусом.
           \en Create fillets on vertices and the edges adjacent to these vertices with a constant radius. \~
  \details \ru Скруглить вершины и примыкающие к ней рёбра тела постоянным радиусом. \n
    В вершинах должно стыковаться три ребра.
    Функция выполняет замену указанных вершин и рёбер исходного тела гранями, 
    гладко сопрягающими смежные грани указанных вершин и рёбер. В поперечном сечении 
    сопрягающие грани могут иметь форму дуги окружности, эллипса, гиперболы, параболы. \n
           \en Create fillets on vertices and the edges of the solid adjacent to these vertices with a constant radius. \n
    Three edges must be incident to each vertex.
    The functions performs replacement of the specified vertices and edges of the source solid by faces of the solid 
    smoothly connecting the faces adjacent to the specified vertices and edges. The cross-section 
    of the connecting faces can be of the form of a circle, an ellipse, a hyperbola or a parabola. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] initCurves - \ru Множество скругляемых ребер тела.
                          \en A set of edges of the solid to fillet. \~
  \param[in] initBounds - \ru Множество граней для обрезки торцев.
                          \en A set of faces for trimming of the butt-ends. \~
  \param[in] initVertices - \ru Множество скругляемых вершин.
                            \en A set of vertices to fillet. \~
  \param[in] params - \ru Параметры скругления рёбер.
                      \en Parameters of edges fillet. \~
  \param[in] cornerData - \ru Параметры скругления вершин.
                          \en Parameters of vertices fillet. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) FilletSolid(       MbSolid &              solid, 
                                            MbeCopyMode            sameShell,
                                            RPArray<MbCurveEdge> & initCurves, 
                                            RPArray<MbFace> &      initBounds, 
                                            RPArray<MbVertex> &    initVertices,
                                      const SmoothValues &         params, 
                                      const CornerValues &         cornerData,
                                      const MbSNameMaker &         names, 
                                            MbSolid *&             result );


//------------------------------------------------------------------------------
/** \brief \ru Скруглить цепочку граней тела.
           \en Create a fillet of faces of the solid. \~
  \details \ru Скруглить указанные грани тела. \n
    Функция выполняет замену указанных граней исходного тела гранями, 
    гладко сопрягающими грани, связанные с указанными гранью.
    В поперечном сечении сопрягающие грани имеют форму
    дуги окружности, касающейся трёх граней исходного тела. \n
           \en Create a fillet on the specified faces of the solid. \n
    The function performs replacement of the specified faces of the source solid with faces 
    smoothly connecting the faces adjacent to the specified faces.
    The cross-section of the connecting faces has a form of
    a circle arc tangent to three faces of the source solid. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] initFaces - \ru Набор граней для скругления.
                         \en A set of faces to fillet. \~
  \param[in] initFacesLeft - \ru Набор ограничивающих слева граней.
                             \en A set of left bounding faces. \~
  \param[in] initFacesRight - \ru Набор ограничивающих справа граней.
                              \en A set of right bounding faces. \~
  \param[in] params - \ru Параметры скругления.
                      \en Parameters of fillet. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) FullFilletSolid(       MbSolid &          solid, 
                                                MbeCopyMode        sameShell,
                                          const RPArray<MbFace> &  initFaces,
                                          const RPArray<MbFace> &  initFacesLeft,
                                          const RPArray<MbFace> &  initFacesRight,
                                          const FullFilletValues & params,
                                          const MbSNameMaker &     names, 
                                                MbSolid *&         result );


//------------------------------------------------------------------------------
/** \brief \ru Построить фаски ребер тела.
           \en Create chamfers for edges of the solid. \~
  \details \ru Построить фаски указанных ребер тела. \n
    Функция выполняет замену указанных рёбер исходного тела гранями фасок. \n
           \en Create chamfers for the specified edges of the solid. \n
    The function performs replacement of the specified edges of the source solid with faces of chamfers. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] initCurves - \ru Множество скругляемых ребер тела.
                          \en An array of edges to create chamfer on. \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) ChamferSolid(       MbSolid &              solid, 
                                             MbeCopyMode            sameShell,
                                             RPArray<MbCurveEdge> & initCurves, 
                                       const SmoothValues &         params, 
                                       const MbSNameMaker &         names, 
                                             MbSolid *&             result );


//------------------------------------------------------------------------------
/** \brief \ru Создать эквидистантное тело.
           \en Create а equidistant solid. \~
  \details \ru Создать эквидистантное тело или оболочку. \n
           \en Create an offset solid by equidistant faces or create an equidistant shell. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] offset - \ru Расстояние смещения граней.
                      \en The equidistant parameter. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) OffsetSolid(       MbSolid &         solid, 
                                            MbeCopyMode       sameShell, 
                                            double            offset, 
                                      const MbSNameMaker &    names,
                                            MbSolid *&        result );

//------------------------------------------------------------------------------
/** \brief \ru Создать тонкостенное тело исключением граней.
           \en Create a thin-walled solid by exclusion of faces. \~
  \details \ru Создать тонкостенное тело исключением граней outFaces \n
    и приданием одинаковой толщины оставшимся граням \n
    или создание незамкнутой оболочки. \n
           \en Create a thin-walled solid by exclusion of faces outFaces \n
    and supplying the rest of faces with the same thickness \n
    or create an open shell. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] outFaces - \ru Вскрываемые грани тела.
                        \en Faces of the solid to open. \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in]  copyFaceAttrs - \ru Копировать атрибуты из исходных граней в эквидистантные.
                              \en Copy attributes of initial faces to offset faces. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) ThinSolid(       MbSolid &         solid, 
                                          MbeCopyMode       sameShell, 
                                          RPArray<MbFace> & outFaces, 
                                          SweptValues &     params, 
                                    const MbSNameMaker &    names,
                                          bool              copyFaceAttrs,
                                          MbSolid *&        result );


//------------------------------------------------------------------------------
/** \brief \ru Создать тонкостенное тело исключением граней.
           \en Create a thin-walled solid by exclusion of faces. \~
  \details \ru Создать тонкостенное тело исключением граней outFaces \n
    и приданием различной толщины оставшимся граням \n
    или создание незамкнутой оболочки. \n
           \en Create a thin-walled solid by exclusion of faces outFaces \n
    and supplying the rest of faces with different thickness \n
    or create an open shell. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] outFaces - \ru Вскрываемые грани тела.
                        \en Faces of the solid to open. \~
  \param[in] offFaces - \ru Множество граней, для которых заданы индивидуальные значения толщин.
                        \en An array of faces for which the individual values of thickness are specified. \~
  \param[in] offDists - \ru Множество индивидуальных значений толщин (должен быть синхронизирован с массивом offFaces).
                        \en An array of individual values of thickness (must be synchronized with the array 'offFaces'). \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in]  copyFaceAttrs - \ru Копировать атрибуты из исходных граней в эквидистантные.
                              \en Copy attributes of initial faces to offset faces. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
  \warning \ru Операция ПОЛНОЦЕННО НЕ РЕАЛИЗОВАНА!
           \en The operation is NOT COMPLETELY IMPLEMENTED! \~
*/
// ---
MATH_FUNC (MbResultType) ThinSolid(       MbSolid &         solid, 
                                          MbeCopyMode       sameShell, 
                                          RPArray<MbFace> & outFaces, 
                                          RPArray<MbFace> & offFaces, 
                                          SArray<double> &  offDists,
                                          SweptValues &     params, 
                                    const MbSNameMaker &    names,
                                          bool              copyFaceAttrs,
                                          MbSolid *&        result );


//------------------------------------------------------------------------------
/** \brief \ru Выполнить разбиение граней оболочки.
           \en Perform splitting of a shell faces. \~
  \details \ru Выполнить разбиение граней оболочки поверхностями выдавливания контуров. \n
    Функция создаёт копию тела и разбивает указанные грани поверхностями выдавливания контуров. \n
           \en Perform splitting of a shell faces with surfaces of the contours extrusion. \n
    The function creates a copy of a solid and splits the specified faces with surfaces of the contours extrusion. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] spPlace - \ru Система координат контуров.
                       \en The coordinate system of the contours. \~
  \param[in] spType - \ru Направление вытягивания.
                      \en The extrusion direction. \~
  \param[in] spContours - \ru Контура разбиения.
                          \en The contours of splitting. \~
  \param[in] spSame - \ru Использовать оригиналы или копии кривых.
                      \en Whether to use the originals or copies of curves. \~
  \param[in] selFaces - \ru Выбранные грани входного тела.
                        \en The chosen faces of the input solid. \~
  \param[in] flags - \ru Флаги слияния элементов оболочки.
                     \en Control flags of shell items merging. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) SplitSolid(       MbSolid &            solid,
                                           MbeCopyMode          sameShell,
                                     const MbPlacement3D &      spPlace,
                                           MbeSenseValue        spType,
                                     const RPArray<MbContour> & spContours,
                                           bool                 spSame,
                                           RPArray<MbFace> &    selFaces,
                                     const MbMergingFlags &     flags,
                                     const MbSNameMaker &       names,
                                           MbSolid *&           result );


//------------------------------------------------------------------------------
/** \brief \ru Выполнить разбиение граней оболочки.
           \en Perform splitting of a shell faces. \~
  \details \ru Выполнить разбиение граней оболочки пространственными кривыми, поверхностями и оболочками. \n
    Функция создаёт копию тела и разбивает указанные грани пространственными кривыми, поверхностями и оболочками. \n
    Пространственные элементы разбиения не должны иметь полных или частичных наложений, а также - самопересечений. \n
           \en Perform splitting of the shell faces with space curves, surfaces and shells. \n
    The function creates a copy of the solid and splits the specified faces with space curves, surfaces and shells. \n
    The spatial elements of a splitting must not have complete or partial overlaps, and also self-intersections. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] spItems - \ru Пространственные элементы разбиения.
                       \en A spatial elements of splitting. \~
  \param[in] spSame - \ru Использовать оригиналы или копии кривых.
                      \en Whether to use the originals or copies of curves. \~
  \param[in] selFaces - \ru Выбранные грани входного тела.
                        \en The chosen faces of the input solid. \~
  \param[in] flags - \ru Флаги слияния элементов оболочки.
                     \en Control flags of shell items merging. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) SplitSolid(       MbSolid &              solid,
                                           MbeCopyMode            sameShell,
                                     const RPArray<MbSpaceItem> & spItems,
                                           bool                   spSame,
                                           RPArray<MbFace> &      selFaces,
                                     const MbMergingFlags &       flags,
                                     const MbSNameMaker &         names,
                                           MbSolid *&             result );


//------------------------------------------------------------------------------
/** \brief \ru Уклонить указанные грани тела.
           \en Slope the specified faces of the solid. \~
  \details \ru Уклонить указанные грани тела от нейтральной изоплоскости на заданный угол. \n
           \en Slope the specified faces of the solid at the specified angle relative to the neutral isoplane. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования входного тела.
                         \en Whether to copy the input solid. \~
  \param[in] neutralPlace - \ru Нейтральная плоскость.
                            \en The neutral plane. \~
  \param[in] angle - \ru Угол уклона.
                     \en The slope angle. \~
  \param[in] faces - \ru Уклоняемые грани во входном теле.
                     \en The faces of input solid to be sloped. \~
  \param[in] fp - \ru Признак захвата граней, гладко стыкующихся с уклоняемыми гранями.
                  \en Whether to capture the faces smoothly connected with the faces being sloped. \~
  \param[in] reverse - \ru Флаг обратного направления уклона.
                       \en Whether to slope in the reverse direction. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) DraftSolid(       MbSolid &          solid, 
                                           MbeCopyMode        sameShell,
                                     const MbPlacement3D &    neutralPlace,
                                           double             angle,
                                     const RPArray<MbFace> &  faces,
                                           MbeFacePropagation fp,
                                           bool               reverse,
                                     const MbSNameMaker &     names,
                                           MbSolid *&         result );


//------------------------------------------------------------------------------
/** \brief \ru Выполнить объединение пересекающихся тел.
           \en Perform the union of intersecting solids. \~
  \details \ru Выполнить объединение пересекающихся тел и булеву операцию oType с телом solid, если оно не нулевое: \n
           bo_Union      - объединение, \n
           bo_Intersect  - пересечение, \n
           bo_Difference - вычитание. \n
    Если флаг проверки пересечения checkIntersect == true, то выполняется проверка на пересечение тел
    и булева операция объединения пересекающихся тел заданного множества в одно тело. В противном случае
    объединение тел заданного множества выполняется простым перекладыванием граней всех тел в одно новое тело. \n
	  Если флаг регулярности множества тел isArray == true, то тела множества расположены в узлах 
    прямоугольной или круговой сетки и позиции тел заданы в именах граней. \n
           \en Perform the union of intersecting solids and a boolean operation oType with solid 'solid' if it is not null: \n
           bo_Union      - union, \n
           bo_Intersect  - intersection, \n
           bo_Difference - subtraction. \n
    If the flag of intersection check checkIntersect == true, check for solids intersection is performed
    and the boolean operation of union the intersection solids of the specified set into one solid is performed. Otherwise
    the union of solids from the given set is performed by simple moving the faces of all the solids into a new solid. \n
	  If the flag of solid set regularity isArray == true, the solids are located at the nodes 
    of rectangular or circular grid and positions of solids are specified in the names of faces. \n \~
  \param[in] solid - \ru Тело.
                     \en A solid. \~
  \param[in] sameShell - \ru Режим копирования тела.
                         \en Whether to copy the solid. \~
  \param[in] solids - \ru Множество тел.
                      \en An array of solids. \~
  \param[in] sameShells - \ru Режим копирования тел.
                          \en Whether to copy the solids. \~
  \param[in] oType - \ru Тип булевой операции между телом и массивом тел.
                     \en The type of the boolean operation for the solid and the set of solids. \~
  \param[in] checkIntersect - \ru Проверять пересечение тел.
                              \en Whether to check the solids intersection. \~
  \param[in] mergeFaces     - \ru Сливать подобные грани.
                              \en \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] isArray - \ru Флаг регулярности множества тел.
                       \en A flag of solid set regularity. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \param[out] notGluedSolids - \ru Множество тел, которые не получилось приклеить.
                               \en An array of solids which was not glued. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) UnionResult(       MbSolid *          solid, 
                                            MbeCopyMode        sameShell, 
                                            RPArray<MbSolid> & solids, 
                                            MbeCopyMode        sameShells, 
                                            OperationType      oType, 
                                            bool               checkIntersect,
                                            bool               mergeFaces,
                                      const MbSNameMaker &     names, 
                                            bool               isArray,
                                            MbSolid *&         result,
                                            RPArray<MbSolid> * notGluedSolids = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Создать одно тело из присланных тел.
           \en Create a solid from the specified solids. \~ 
  \details \ru Создать тело с объединением или без объединения пересекающихся тел. \n
    Если флаг проверки пересечения checkIntersect == true, то выполняется проверка на пересечение тел 
    и булева операция объединения пересекающихся тел заданного множества в одно тело. В противном случае
    объединение тел заданного множества выполняется простым перекладыванием граней всех тел в одно новое тело. \n
	  Если флаг регулярности множества тел isArray == true, то тела множества расположены в узлах 
    прямоугольной или круговой сетки и позиции тел заданы в именах граней. \n
           \en Create a solid with or without union of the intersecting solids. \n
    If the flag of intersection check checkIntersect == true, check for solids intersection is performed 
    and the boolean operation of union the intersection solids of the specified set into one solid is performed. Otherwise
    the union of solids from the given set is performed by simple moving the faces of all the solids into a new solid. \n
	  If the flag of solid set regularity isArray == true, the solids are located at the nodes 
    of rectangular or circular grid and positions of solids are specified in the names of faces. \n \~
  \param[in] solids - \ru Множество тел.
                      \en An array of solids. \~
  \param[in] sameShells - \ru Режим копирования тел.
                          \en Whether to copy the solids. \~
  \param[in] checkIntersect - \ru Проверять пересечение тел.
                              \en Whether to check the solids intersection. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] isArray - \ru Флаг регулярности множества тел.
                       \en A flag of solid set regularity. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \param[out] notGluedSolids - \ru Множество тел, которые не получилось приклеить.
                               \en An array of solids which was not glued. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) UnionSolid(       RPArray<MbSolid> & solids, 
                                           MbeCopyMode        sameShells,
                                           bool               checkIntersect,
                                     const MbSNameMaker &     names, 
                                           bool               isArray,
                                           MbSolid *&         result,
                                           RPArray<MbSolid> * notGluedSolids = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Создать одно тело из присланных тел.
           \en Create a solid from the specified solids. \~ 
  \details \ru Создать одно тело из присланных тел, не меняя их. \n
    Объединение тел заданного множества выполняется простым перекладыванием 
    граней всех тел в одно новое тело. \n
           \en Create a solid from the specified solids without the modification of the given solids. \n
    The union of solids from the specified set is performed by simple moving 
    the faces of all the solids into a new solid. \n \~
  \param[in] solids - \ru Множество тел.
                      \en An array of solids. \~
  \param[in] names  - \ru Именователь.
                      \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) UnionSolid( const RPArray<MbSolid> & solids, 
                                     const MbSNameMaker &     names,
                                           MbSolid *&         result );


//------------------------------------------------------------------------------
/** \brief \ru Разделить тело на отдельные части.
           \en Split the solid into separate parts. \~
  \details \ru Если исходное тело распадается на части, то наибольшая часть остаётся в исходном теле, 
    а остальные части части будут сложены в присланный контейнер тел. \n
    Если флаг сортировки sort == true, то в исходном теле останется часть с наибольшим габаритом, 
    а отделённые части будут сортированы по убыванию габарита. В противном случае в исходном теле 
    останется часть, топологически связанная с первой гранью, а отделённые части будут сортированы
    по номеру начальной грани в исходном теле. \n
           \en If the source solid is decomposed, the greatest part remains in the source solid, 
    and the other parts are put into the given array of solids. \n
    If 'sort' == 'true', the part with the greatest bounding box will remain in the source solid, 
    and separated parts will be sorted by bounding box size in descending order. Otherwise a part topologically connected with the first face will remain in the source solid 
    and the separated parts will be sorted
    by the number of the initial face in the source solid. \n \~
  \param[in,out] solid - \ru Исходное модифицируемое тело.
                         \en The source solid to be modified. \~
  \param[out] parts - \ru Отделённые части тела.
                      \en The separated parts of the solid. \~
  \param[in] sort - \ru Сортировать по убыванию габарита.
                    \en Whether to sort by the bounding box size in descending order. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \return \ru Возвращает количество отделенных частей.
          \en Returns the number of the separated parts. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (size_t) DetachParts(       MbSolid &          solid, 
                                      RPArray<MbSolid> & parts, 
                                      bool               sort,
                                const MbSNameMaker &     names );


//------------------------------------------------------------------------------
/** \brief \ru Разделить тело на отдельные части.
           \en Split the solid into separate parts. \~
  \details \ru Если исходное тело распадается на части, то все его части будут сложены в присланный контейнер тел. \n
    Исходное тело остаётся неизменённым. \n
           \en If the source solid is decomposed, all the parts of the solid will be put into the given array of solids. \n
    The source solid remains unchanged. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[out] parts - \ru Части тела.
                      \en The parts of the solid. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \return \ru Возвращает количество созданных частей.
          \en Returns the number of created parts. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (size_t) CreateParts( const MbSolid &          solid, 
                                      RPArray<MbSolid> & parts, 
                                const MbSNameMaker &     names );


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку тела по поверхности и толщине.
           \en Create a shell of the solid from a surface and a thickness. \~
  \details \ru Выполнить построение тела путём придания толщины заданной поверхности. \n
           \en Create a solid by supplying the surface with a thickness. \n \~
  \param[in] surface - \ru Поверхность.
                       \en The surface. \~
  \param[in] faceSense - \ru Ориентация нормали поверхности.
                         \en The surface normal orientation. \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] name - \ru Основное простое имя.
                    \en The main simple name. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) ThinSolid( const MbSurface &    surface, 
                                          bool           faceSense, 
                                          SweptValues &  params, 
                                    const MbSNameMaker & names, 
                                          SimpleName     name, 
                                          MbSolid *&     result );


//------------------------------------------------------------------------------
/** \brief \ru Cоздать отверстие, карман, фигурный паз в теле.
           \en Create a hole, a pocket, a groove in the solid. \~
  \details \ru Cоздать отверстие, карман, фигурный паз в теле или создать cверло, бобышку, если solid==NULL. \n
           \en Create a hole, a pocket, a groove in the solid or create a drill, a boss if 'solid' == NULL. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The source solid. \~
  \param[in] sameShell - \ru Режим копирования тела.
                         \en Whether to copy the solid. \~
  \param[in] place - \ru Местная система координат для операции.
                     \en A local coordinate system for the operation. \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] names  - \ru Именователь.
                      \en An object for naming the new objects. \~
  \param[out] result - \ru Построенное тело.
                       \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) HoleSolid(       MbSolid *       solid, 
                                          MbeCopyMode     sameShell,
                                    const MbPlacement3D & place, 
                                    const HoleValues &    params, 
                                    const MbSNameMaker &  names,
                                          MbSolid *&      result );


//------------------------------------------------------------------------------
/** \brief \ru Выделить в отдельное тело указанную часть распадающегося на части тела.
           \en Extract the specified part of decomposing solid to a separate solid. \~
  \details \ru Создать тело, из указанной части тела, распадающегося на части. 
    Исходное тело должно состоять из отдельных частей. \n
           \en Create a solid from the specified part of decomposing solid. 
    The source solid should consist of separate parts. \n \~
  \param[in] solid - \ru Разделяемое на части тело.
                     \en A decomposing solid. \~
  \param[in] id - \ru Номер выбранной части тела
                  \en The number of selected part of the solid. \~
  \param[in] path - \ru Идентификатор для выбранной части.
                    \en An identifier for the selected part. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in,out] partIndices - \ru Индексы частей тела.
                               \en Indices of the parts of the solid. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) ShellPart( const MbSolid &            solid, 
                                          size_t               id, 
                                    const MbPath &             path, 
                                    const MbSNameMaker &       names,
                                          MbPartSolidIndices & partIndices, 
                                          MbSolid *&           result );


//------------------------------------------------------------------------------
/** \brief \ru Размножить тело.
           \en Duplicate the solid. \~
  \details \ru Размножить тело согласно параметрам и объединить копии в одно тело.\n
           \en Duplicate the solid by the parameters and unite copies in one solid. \n \~
  \param[in] solid   - \ru Исходное тело.
                       \en The source solid. \~
  \param[in]  params - \ru Параметры размножения. 
                       \en The parameters of duplication. \~
  \param[in]  names  - \ru Именователь операции.
                       \en An object defining names generation in the operation. \~
  \param[out] result - \ru Результирующее тело.
                       \en The result solid. \~
  \return \ru Возвращает код результата операции.
          \en . \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) DuplicationSolid( const MbSolid &           solid, 
                                           const DuplicationValues & params, 
                                           const MbSNameMaker &      names, 
                                                 MbSolid *&          result );


//------------------------------------------------------------------------------
/** \brief \ru Cоздать одно тело слиток из присланных объектов.
           \en Create an ingot solid from the specified objects. \~ 
  \details \ru Cоздать одно тело слиток из присланных объектов. \n
    Среди присланных объектов используются тела, вставки тел и сборки тел, из которых строится одно тело, 
    которое по внешности совпадает с присланными телами и служит их упрощенным заменителем по внешним параметрам. \n
           \en Create an ingot solid from the specified solids without the modification of the given solids. \n
    Among the objects sent using the body, insert bodies and assembling bodies of which is built the same body,
    which in appearance coincides with the bodies had been sent and serves as a substitute for their simplistic external parameters. \n \~
  \param[in] solids   - \ru Множество тел.
                        \en An array of solids. \~
  \param[in] names    - \ru Именователь.
                        \en An object for naming the new objects. \~
  \param[in] makeCopy - \ru Флаг копирования тел перед использованием: true - копировать, false - не копировать.
                        \en The flag of the copying solid before using: true - copy solid, false - not copy. \~
  \param[out] result  - \ru Построенное тело.
                        \en The resultant solid. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbResultType) IngotSolid(       RPArray<MbItem> & solids, 
                                           bool              makeCopy,
                                     const MbSNameMaker &    names,
                                           MbSolid *&        result );


#endif // __ACTION_SOLID_H
