////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Перечисления.
         \en The enumerations. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MB_ENUM_H
#define __MB_ENUM_H


#include <mb_variables.h>


//------------------------------------------------------------------------------
/** \brief \ru Результат выполнения итерационного метода.
           \en The result of the iterative method. \~
  \details \ru Результат выполнения итерационного метода сообщает о нахождении решения.
           \en The result of the iterative method reports about finding solutions. \~
  \ingroup Data_Structures
*/
// ---
enum MbeNewtonResult {
  nr_Failure  = -1, ///< \ru Решение не найдено. \en The solution wasn't found. 
  nr_Special  =  0, ///< \ru Решение не сошлось за заданное количество итераций. \en The solution has not converged for a specified number of iterations. 
  nr_Success  =  1, ///< \ru Решение найдено. \en The solutions was found. 
  nr_Specific =  2, ///< \ru Требуется уточнение. \en Correction is required. 
};


//------------------------------------------------------------------------------
/** \brief \ru Положение объекта.
           \en The position of an object. \~
  \details \ru Положение объекта относительно другого объекта.
           \en The position of an object relative to another object. \~
  \ingroup Data_Structures
*/
// ---
enum MbeItemLocation {
  iloc_Undefined = -3,  ///< \ru Не определялось. \en Not defined. 
  iloc_Unknown   = -2,  ///< \ru Не получилось определить. \en Failed to define. 
  iloc_OutOfItem = -1,  ///< \ru Вне объекта. \en Outside the object. 
  iloc_OnItem    =  0,  ///< \ru На объекте (на границе). \en On the object (on the boundary). 
  iloc_InItem    =  1,  ///< \ru Внутри объекта. \en Inside the object. 
  iloc_ByItem    =  2,  ///< \ru Условно внутри объекта (для незамкнутых оболочек). \en Conditionally inside the object (for non-closed shells). 
};


//------------------------------------------------------------------------------
/** \brief \ru Положение двумерной точки. 
           \en Two-dimensional point position. \~
  \details \ru Положение двумерной точки относительно двумерной кривой. 
           \en Two-dimensional point position relative to the curve. \~
  \ingroup Data_Structures
*/
// ---
enum MbeLocation {
  loc_Undefined = iloc_Unknown,   ///< \ru Положение не определено, кривая разомкнута.  \en Failed to define, curve is not closed. 
  loc_Outside   = iloc_OutOfItem, ///< \ru Точка снаружи замкнутой кривой. \en Outside the curve. 
  loc_OnCurve   = iloc_OnItem,    ///< \ru Точка на кривой. \en On the curve. 
  loc_Inside    = iloc_InItem,    ///< \ru Точка внутри замкнутой кривой. \en Inside the curve. 
};


//------------------------------------------------------------------------------
/** \brief \ru Состояние объекта после модификации. 
           \en Object condition after modification. \~
  \details \ru Используется для определения состояние кривой после резки. 
           \en Used to determine the state of the curve after the cutting. \~
  \ingroup Data_Structures
*/
// ---
enum MbeState {
  dp_NoChanged = 0, ///< \ru Объект не изменился. \en The object is not changed.
  dp_Changed,       ///< \ru Объект изменился. \en The object has changed.
  dp_Degenerated,   ///< \ru Объект выродился. \en The object has degenerated. \~
};


//------------------------------------------------------------------------------
/** \brief \ru Состояние выполнения процесса.
           \en State of the process. \~
  \details \ru Состояние выполнения процесса сообщает о ходе работы функции, операции и т.п.
           \en State of the process reports about progress of work of function, operation, etc. \~
  \ingroup Data_Structures
*/
// ---
enum MbeProcessState {
  mps_Error         = -3, ///< \ru Ошибка. \en Error. 
  mps_Skip          = -2, ///< \ru Пропущено. \en Has been skipped. 
  mps_Stop          = -1, ///< \ru Остановлено. \en Has been stopped. 
  mps_Success       =  0, ///< \ru Выполнено. \en Done. 
  mps_SelfIntersect = 24, ///< \ru Выполнено. Объект самопересекается. \en Done. Self-intersecting object.
};


//------------------------------------------------------------------------------
/** \brief \ru Направление.
           \en Direction. \~
  \details \ru Направление движения относительно базового объекта.
           \en The direction of a movement relative to the base object. \~
  \ingroup Data_Structures
*/
//---
enum MbeSenseValue {
  orient_BOTH = 0,  ///< \ru Оба направления (неориентированный). \en Both directions (nonoriented). 
  orient_FORWARD,   ///< \ru Прямое направление. \en Forward direction. 
  orient_BACK,      ///< \ru Обратное направление. \en Backward direction. 
};


//------------------------------------------------------------------------------
/** \brief \ru Тип параметризации сплайновых объектов.
           \en The parameterization type of spline objects. \~
  \details \ru Тип параметризации сплайновых объектов. \n
           \en The parameterization type of spline objects. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeSplineParamType {
  spt_Unstated      = 0,  ///< \ru Неустановленный. \en Unstated. 
  spt_EquallySpaced = 1,  ///< \ru Равномерная. \en Equally spaced. 
  spt_ChordLength   = 2,  ///< \ru По длине хорды (расстоянию между точками). \en By the chord length (the distance between the points). 
  spt_Centripetal   = 3,  ///< \ru Центростремительная (квадратный корень расстояния между точками). \en Centripetal (square root of the distance between the points). 
};


//-------------------------------------------------------------------------------
/** \brief \ru Типы форм NURBS-кривой.
           \en Types of NURBS-curve forms. \~
  \details \ru Типы форм сплайновой кривой NURBS. \n
           \en Types of spline NURBS-curve forms \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeNurbsCurveForm	{
  ncf_Unspecified = 0, ///< \ru Неопределенная форма. \en Undefined form 
  ncf_PolylineForm,    ///< \ru Ломаная. \en Polyline. 
  ncf_CircularArc,     ///< \ru Дуга окружности. \en Circle arc. 
  ncf_EllipticArc,     ///< \ru Дуга эллипса. \en Ellipse arc. 
  ncf_ParabolicArc,    ///< \ru Дуга параболы. \en Parabola arc. 
  ncf_HyperbolicArc,   ///< \ru Дуга гиперболы. \en Hyperbola arc 
  ncf_BezierForm,      ///< \ru Сплайн Безье. \en Bezier spline. 
  ncf_HermitForm,      ///< \ru Сплайн Эрмита. \en Hermite spline. 
  ncf_SurfacePoleForm, ///< \ru Сплайн в полюсе поверхности. \en Spline in the pole of surface. 
};


//------------------------------------------------------------------------------
/** \brief \ru Тип сопряжения.
           \en The conjugation type. \~
  \details \ru Тип сопряжения определяет способ сопряжения краёв сплайна с контактирующими объектами.
           \en The conjugation type defines the method of conjugation of spline boundary with contact objects. \~
  \ingroup Data_Structures
*/
//---
enum MbeMatingType {
  // \ru Не менять номера, тип пишется и читается, новые добавлять в конец \en Do not change the numbers. Type is written and read. Append new types to the end 
  trt_None     = -1, ///< \ru Без сопряжений. \en Without conjugations. 
  trt_Position =  0, ///< \ru Соединение по позиции      (эквивалентно tt_SmoothG0). \en The connection by the position (equivalent to tt_SmoothG0). 
  trt_Tangent  =  1, ///< \ru Соединение по касательной  (эквивалентно tt_SmoothG1). \en Tangential connection  (equivalent to tt_SmoothG1). 
  trt_Normal   =  2, ///< \ru Соединение перпендикулярно (эквивалентно tt_SmoothG1). \en Perpendicular connection (equivalent to tt_SmoothG1). 
  trt_SmoothG2 =  3, ///< \ru Гладкое соединение по первой производной касательной (по кривизне). \en The smooth connection by the first derivative of the tangent (the curvature). 
  trt_SmoothG3 =  4, ///< \ru Гладкое сопряжение по второй производной касательной.               \en The smooth conjugation by the second derivative of the tangent.                    //-V112 
};


//------------------------------------------------------------------------------
/** \brief \ru Тип сопряжения по ребрам.
           \en The type of conjugation by edges. \~
  \details \ru Тип сопряжения по ребрам определяет способ сопряжения поверхности грани с поверхностью смежной по ребру грани.
           \en The type of conjugation by edges defines the method of conjugation of face surface with surface of adjacent faces by face edge \~
  \ingroup Data_Structures
*/
//---
enum MbeConjugationType {
  cjt_NormPlus  = 0,    ///< \ru По нормали в положительном направлении вектора нормали к грани. \en The type of conjugation by normal in the positive direction of face normal vector. 
  cjt_NormMinus = 1,    ///< \ru По нормали в отрицательном направлении вектора нормали к грани. \en The type of conjugation by normal in the negative direction of face normal vector. 
  cjt_G1Plus    = 2,    ///< \ru По касательной к поверхности, слева по направлению касательной к кривой пересечения. \en The type of conjugation by tangent to the surface, to the left in the direction of intersection curve tangent. 
  cjt_G1Minus   = 3,    ///< \ru По касательной к поверхности, справа по направлению касательной к кривой пересечения. \en The type of conjugation by tangent to the surface, to the right in the direction of intersection curve tangent. 
};


//------------------------------------------------------------------------------
/** \brief \ru Тип сглаживания.
           \en The type of blending. \~
  \details \ru Тип сглаживания при перемещении узлов в процессе прямого редактирования.
           \en The type of blending while moving nodes in the process of direct editing. \~
  \ingroup Data_Structures
*/
//---
enum MbeDirectSmoothType {
  dst_None     = -1, ///< \ru Без сглаживания. \en Without blending. 
  dst_Convex   =  0, ///< \ru Выпуклый. \en Convex. 
  dst_Concave  =  1, ///< \ru Вогнутый. \en Concave. 
  dst_Smooth   =  2, ///< \ru Плавный переход. \en Smooth transition. 
};


//------------------------------------------------------------------------------
/** \brief \ru Типы двумерной сетки.
           \en Types of two-dimensional mesh. \~
  \details \ru Типы двумерной сетки. \n
           \en Types of two-dimensional mesh. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeItemGridType {
  igt_Rectangular = 0, ///< \ru Прямоугольная сетка. \en Rectangular mesh. 
  igt_Concentric  = 1, ///< \ru Концентрическая сетка. \en Concentric mesh. 
  igt_Hexagonal   = 2, ///< \ru Гексагональная сетка. \en Hexagonal mesh. 
};


//------------------------------------------------------------------------------
/** \brief \ru Направление на поверхности.
           \en Direction on the surface. \~
  \details \ru Используемое в итерационном методе направление на поверхности. \n
           \en Direction on the surface which is used in the iterative method. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeParamDir {
  pd_DirU = 0, ///< \ru U-направление на поверхности. \en U-direction on the surface. 
  pd_DirV = 1, ///< \ru V-направление на поверхности. \en V-direction on the surface. 
};


//------------------------------------------------------------------------------
/** \brief \ru Типы кривой пересечения поверхностей по построению.
           \en Types of surfaces intersection curve by construction. \~
  \details \ru Типы кривой пересечения поверхностей как результат итерационного метода.
           \en Types of surfaces intersection curve as a result of the iterative method. \~
  \ingroup Data_Structures
*/
// ---
enum MbeCurveBuildType {
  cbt_Boundary = -1, ///< \ru Кривая по которой идет граница оболочки. \en Curve which the boundary of the shell goes through. 
  cbt_Ordinary =  0, ///< \ru Аналитическая кривая. \en Analytical curve.  
  cbt_Specific =  1, ///< \ru Кривая построена по отдельным точкам. \en Curve is constructed from single points.  
  cbt_Tolerant =  2, ///< \ru Аналитическая кривая пересечения, рассчитанная неточно. \en The analytical curve of intersection which is calculated imprecisely.  
};


//------------------------------------------------------------------------------
/** \brief \ru Типы поверхности сопряжения.
           \en Types of blend surface. \~
  \details \ru Типы поверхности сопряжения (скругления или фаски) по построению.
           \en The type of blend surface (fillet or chamfer) by a construction. \~
  \ingroup Data_Structures
*/
// ---
enum MbeSurfaceType {
  sst_OrdinarySurface =  0, ///< \ru Аналитическая поверхность. \en Analytic surface.  
  sst_SpecificSurface =  1, ///< \ru Специальная поверхность сопряжения (скругления или фаски) построена по отдельным точкам. \en Special blend surface (fillet or chamfer) is constructed by separate points.  
};


//------------------------------------------------------------------------------
/** \brief \ru Типы кривой пересечения поверхностей по топологии.
           \en Curve types of surfaces intersection by topology. \~
  \details \ru Типы кривой пересечения поверхностей по топологии. \n
           \en Curve types of surfaces intersection by topology. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeCurveGlueType {
 cgt_Unknown = 0, ///< \ru Неустановленное значение типа кривой. \en Undefined type of curve. 
 cgt_Pole    = 1, ///< \ru Полюсная кривая. \en Pole curve. 
 cgt_Edge    = 2, ///< \ru Кривая пересечения разных поверхностей. \en Intersection curve of different surfaces. 
 cgt_Stitch  = 3, ///< \ru Шовное ребро или линия разъема из конвертеров (правило выбора первой параметрической кривой). \en Seam edge or parting line from converters (rule for choice of the first parametric curve). 
 cgt_Split   = 4, ///< \ru Кривая пересечения - линия разъема. \en Intersection curve is a parting line. 
};


//------------------------------------------------------------------------------
/** \brief \ru Способы вычисления приращения параметра по объекту.
           \en Methods of calculation of parameter increment by the object. \~
  \details \ru Используются три общих способа вычисления приращения параметра кривой или поверхности:
    по стрелке прогиба, по углу отклонения, по длине.
    Для визуализации геометрической формы используется первый способ. \n
    Для операций построения используется второй способ. \n
    Для 3D принтеров используется все три перечисленные способа. \n
    Ещё три специализированных способа вычисления приращения параметра используются для конкретных целей: 
    для привязки объектов к параметрам поверхности,
    для определения столкновений элементов модели,
    для вычисления инерционных характеристик. 
           \en Methods of calculation of parameter increment by the object. \n \~
    There are three types of steps: by sag, by deviation angle, by length. 
    Step by sag is used for visualizations.
    Step by deviation angle is used for calculation.
    Step by length is used for 3D printer (plus by sag and by deviation angle). \n
    There are three special types of steps also.
    Special step is used for linking with surface parameters.
    Special step is used for collision detection of model elements.
    Special step is used for calculation of inertial characteristics. \~
  \ingroup Data_Structures
*/
// ---
enum MbeStepType {
  ist_SpaceStep     =  0x01, ///< \ru Шаг по стрелке прогиба. \en Step by sag. 
  ist_DeviationStep =  0x02, ///< \ru Шаг по углу отклонения. \en Step by the deflection angle.  
  ist_MetricStep    =  0x04, ///< \ru Шаг по длине. \en Step by length.
  ist_ParamStep     =  0x08, ///< \ru Шаг с привязкой объектов к параметрам поверхности. \en Step with binding of objects to the parameters of surface. 
  ist_CollisionStep =  0x10, ///< \ru Шаг для определения столкновений элементов модели. \en Step for collision detection of model elements. 
  ist_MipStep       =  0x20, ///< \ru Шаг для расчета инерционных характеристик. \en Step for mass-inertial characteristics. 
};


//------------------------------------------------------------------------------
/** \brief \ru Рабочие метки.
           \en Working label. \~
  \details \ru Рабочие метки для операций, используются в MbTopologyItem::GetLabel и MbTopologyItem::SetOwnLabel.
           \en Working label for operations are used in MbTopologyItem::GetLabel and MbTopologyItem::SetOwnLabel. \~
  \ingroup Data_Structures
*/
// ---
enum MbeLabelState {
  ls_None       = -1, ///< \ru Объект не будет использоваться. \en The object is not to be used. 
  ls_Null       =  0, ///< \ru Объект не рассматривался. \en Object was not considered. 
  ls_Used       =  1, ///< \ru Объект используется. \en Object is used. 
  ls_Delete     =  2, ///< \ru Объект предназначен для удаления. \en The object is to be deleted. 
  ls_Rebuild    =  3, ///< \ru Объект нуждается в перестроении. \en The object needs to be rebuilt. 
  ls_FirstPass  =  4, ///< \ru Объект затронут первым проходом алгоритма. \en The object is affected by the first pass of the algorithm. 
  ls_SecondPass =  5, ///< \ru Объект затронут вторым проходом алгоритма. \en The object is affected by the second pass of the algorithm. 
  ls_Error      =  6, ///< \ru Объект нужно удалить и возвести ошибку. \en The object must be removed, and the error must be returned. 
  ls_Doubtful   =  7, ///< \ru Объект сомнительный, рассматривается в последнюю очередь. \en The object is doubtful.
  ls_TempMark   =  8  ///< \ru Временная метка (для сбора объектов). \en Temporary mark (for collection of objects).
};


//------------------------------------------------------------------------------
/** \brief \ru Способы построения поверхности сопряжения (скругления или фаски).
           \en Methods of construction of a blend surface (fillet or chamfer). \~
  \details \ru Способы построения поверхности сопряжения (скругления или фаски). \n
           \en Methods of construction of a blend surface (fillet or chamfer). \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeSmoothForm {
  st_Span    = -1,  ///< \ru Скругление с заданной хордой. \en Fillet with a given chord. 
  st_Fillet  =  0,  ///< \ru Скругление с заданными радиусами. \en Fillet with given radii. 
  st_Chamfer =  1,  ///< \ru Фаска с заданными катетами. \en Chamfer with given cathetuses. 
  st_Slant1  =  2,  ///< \ru Фаска по катету и углу (катет distance2 рассчитан для прямого угла между гранями и определяет прилегающий к катету distance1 угол). \en Chamfer by cathetus and angle (distance2 cathetus is calculated for right angle between faces and defines angle adjacent to the distance1 cathetus). 
  st_Slant2  =  3,  ///< \ru Фаска по углу и катету (катет distance1 рассчитан для прямого угла между гранями и определяет прилегающий к катету distance2 угол). \en Chamfer by angle and cathetus (distance1 cathetus is calculated for right angle between faces and defines angle adjacent to the distance2 cathetus). 
};


//------------------------------------------------------------------------------
/** \brief \ru Типы булевых операций над твердыми телами.
           \en Types of boolean operations on solids. \~
  \details \ru Типы булевых операций над твердыми телами. \n
           \en Types of boolean operations on solids. \n \~
  \ingroup Data_Structures
*/
// ---
enum OperationType {
  bo_Internal   = -4, ///< \ru Пересечение оболочек. \en Shells intersection. 
  bo_External   = -3, ///< \ru Вычитание   оболочек. \en Shells subtraction. 
  bo_Intersect  = -2, ///< \ru Пересечение тел. \en Solids intersection. 
  bo_Difference = -1, ///< \ru Вычитание   тел. \en Solids subtraction. 
  bo_Unknown    =  0, ///< \ru Неопределённая операция. \en Undefined operation. 
  bo_Union      =  1, ///< \ru Объединение тел. \en Solids union. 
  bo_Base       =  2, ///< \ru Исходное состояние. \en Initial state. 
  bo_Variety    =  3, ///< \ru Объединение оболочек. \en Shells union. 
};


//------------------------------------------------------------------------------
/** \brief \ru Типы булевых операций над двумерными регионами.
           \en Types of boolean operations on two-dimensional regions. \~
  \details \ru Типы булевых операций над двумерными регионами. \n
           \en Types of boolean operations on two-dimensional regions. \n \~
\ingroup Data_Structures
*/
// ---
enum RegionOperationType {
  rbo_Intersect = -2,  ///< \ru Операция пересечение. \en Intersection operation. 
  rbo_Difference = -1, ///< \ru Операция разность. \en Subtraction operation. 
  rbo_Unknown = 0,     ///< \ru Неопределенная операция. \en Undefined operation. 
  rbo_Union = 1,       ///< \ru Операция объединение. \en Union operation. 
};


//------------------------------------------------------------------------------
/** \brief \ru Способы сопряжения кривых.
           \en Methods of curves conjugation. \~
  \details \ru Способы сопряжения двух кривых третьей кривой.
           \en Methods of two curves conjugation by the third curve. \~
  \ingroup Data_Structures
*/
// ---
enum MbeConnectingType {
  ft_Fillet    = 0, ///< \ru Скругление круговое на цилиндре. \en Circular fillet on the cylinder. 
  ft_OnSurface = 1, ///< \ru Скругление пересечением цилиндра и общей поверхности сопрягаемых кривых. \en Fillet by intersection of the cylinder and common surface of the mating curves. 
  ft_Spline    = 2, ///< \ru Сопряжение сплайном. \en Conjugation by spline. 
  ft_Double    = 3, ///< \ru Сопряжение двумя дугами. \en Conjugation by two arcs. 
  ft_Bridge    = 4, ///< \ru Сопряжение кубической кривой. \en Conjugation by a cubic curve. 
};


//------------------------------------------------------------------------------
/** \brief \ru Cпособы передачи данных при копировании оболочек.
           \en Methods of transferring data while copying shells. \~
  \details \ru Cпособы передачи данных при копировании оболочек в операциях над телами. \n
  Любая операция, и удачная, и ошибочная, безвозвратно модифицирует вершины, рёбра и грани оболочек операндов. \n
  Для сохранения неизменной исходной оболочки операнда применяется полное или частичное копирование данных. \n
  Используются четыре способа передачи данных в операцию. \n
  Если не требуется сохранить данные, то оболочка не копируется, а используется исходная. \n
  Если требуется, чтобы операция не портила исходную оболочку и максимально экономила память, 
  то в копии оболочки сохраняются базовые поверхности и вершины.
  Кроме того, после операции копия и исходная оболочка имеют общие неизменённые операцией грани. \n
  Если требуется, чтобы операция не портила исходную оболочку и имела высокую скорость выполнения, 
  то в копии оболочки сохраняются базовые поверхности и вершины. \n
  Если требуется, чтобы результат операции не был связан с исходными объектами, 
  то вершины, рёбра, поверхности и грани операндов полностью копируются.
  Такой подход используется в операциях, трансформирующих тело, например при зеркальном копировании. \n
           \en Methods of transferring data while copying shells in operations on solids.  \n
  Any operation (successful or faulty) modifies vertices, edges and shell faces of operands irreversibly. \n
  Used full or partial copying of data to save the initial operand shell. \n
  Four methods of transferring data to operation are used. \n
  If it is not required to save the data, then the shell isn't copied and the original shell is used. \n
  If it is required that the operation should not spoil the original shell and save memory, 
  then the base surfaces and vertices are saved in a copy of the shell.
  In addition after operation a copy and the initial shell have common faces unchanged by operation. \n
  If it is required that the operation should not spoil the original shell and had a high speed, 
  then the base surfaces and vertices are saved in a copy of the shell. \n
  If it is required that the operation result should not relate to the original objects, 
  then the vertices, edges, surfaces and faces of operands are copied.
  This approach is used in operations which transform solid, such as mirroring. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeCopyMode {
  cm_Same = 0,    ///< \ru Оболочка не копируется. \en Shell is not copied. 
  cm_KeepHistory, ///< \ru Исходная оболочка и её копия имеют общие базовые поверхности, вершины и неизменённые операцией грани. \en Initial shell and its copy have common base surfaces, vertices and faces unchanged by operation. 
  cm_KeepSurface, ///< \ru Исходная оболочка и её копия имеют общие базовые поверхности. \en Initial shell and its copy have common base surfaces. 
  cm_Copy,        ///< \ru Исходная оболочка и её копия не имеют общих данных. \en Initial shell and its copy don't have common data. 
};


//------------------------------------------------------------------------------
/** \brief \ru Поддерживаемые типы производных на кривой.
           \en Supported types of derivatives on the curve. \~
  \details \ru Поддерживаемые типы производных на кривой. Они же индексы производных в общем массиве. \n
           \en Supported types of derivatives on the curve. They are the indices of derivatives in the general array. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeCurveDerivativeType {
  cdt_CurPoint = 0, ///< \ru Точка (нулевой порядок) \en A point (zero order) 
  cdt_FirstDer,     ///< \ru Первая производная \en First derivative. 
  cdt_SecondDer,    ///< \ru Вторая производная \en Second derivative 
  cdt_ThirdDer,     ///< \ru Третья производная \en Third derivative 
  // \ru Новые производные вставлять по порядку перед количеством \en New derivatives are to be inserted before the number of derivatives 
  cdt_CountDer,     ///< \ru Количество запоминаемых значений (порядков) \en The number of memorized values (orders) 
};          


//------------------------------------------------------------------------------
/** \brief \ru Поддерживаемые типы производных на поверхности.
           \en Supported types of derivatives on the surface. \~
  \details \ru Поддерживаемые типы производных на поверхности. Они же индексы производных в общем массиве. \n
           \en Supported types of derivatives on the surface. They are the indices of derivatives in the general array. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeSurfaceDerivativeType {   
  sdt_SurPoint = 0, ///< \ru Точка. \en A point. 
  sdt_DeriveU,      ///< \ru Частная производная по U. \en Partial derivative by U. 
  sdt_DeriveV,      ///< \ru Частная производная по V. \en Partial derivative by V. 
  sdt_DeriveUU,     ///< \ru Частная производная по UU. \en Partial derivative by UU. 
  sdt_DeriveUV,     ///< \ru Частная производная по UV. \en Partial derivative by UV. 
  sdt_DeriveVV,     ///< \ru Частная производная по VV. \en Partial derivative by VV. 
  sdt_DeriveUUU,    ///< \ru Частная производная по UUU. \en Partial derivative by UUU. 
  sdt_DeriveUUV,    ///< \ru Частная производная по UUV. \en Partial derivative by UUV. 
  sdt_DeriveUVV,    ///< \ru Частная производная по UVV. \en Partial derivative by UVV. 
  sdt_DeriveVVV,    ///< \ru Частная производная по UVV. \en Partial derivative by UVV. 
  sdt_Normal,       ///< \ru Нормаль. \en Normal. 
  sdt_NormalU,      ///< \ru Частная производная нормали по U. \en Partial derivative of normal by U. 
  sdt_NormalV,      ///< \ru Частная производная нормали по V. \en Partial derivative of normal by V. 
  sdt_NormalUU,     ///< \ru Частная производная нормали по UU. \en Partial derivative of normal by UU. 
  sdt_NormalUV,     ///< \ru Частная производная нормали по UV. \en Partial derivative of normal by UV. 
  sdt_NormalVV,     ///< \ru Частная производная нормали по VV. \en Partial derivative of normal by VV. 
  // \ru Новые производные вставлять по порядку перед количеством \en New derivatives are to be inserted before the number of derivatives 
  sdt_CountNor,     ///< \ru Количество запоминаемых значений. \en The number of memorized values. 
  sdt_CountDer = sdt_Normal,     ///< \ru Количество запоминаемых значений. \en The number of memorized values. 
};


//------------------------------------------------------------------------------
/** \brief \ru Перечисление способов захвата граней.
           \en Enumeration of faces capturing methods. \~
  \details \ru Перечисление способов захвата граней. \n
           \en Enumeration of faces capturing methods. \n \~
  \ingroup Base_Items
  \attention \ru Идентификаторы не менять (пишутся в файл)!
             \en Do not change identifiers (they are written to file)! \~
*/
//---
enum MbeFacePropagation {
  fp_None                 = 0,  ///< \ru Без захвата. \en Without capture. 
  fp_All                  = 1,  ///< \ru Захват всех граней. \en Capture all faces. 
  fp_SmoothlyJointedAlong = 2,  ///< \ru Прохождение по гладкостыкующимся граням через сонаправленные ребра (прямолинейные). \en Movement on smooth-joint faces through collinear edges (straight). 
  fp_SmoothlyJointedOrtho = 3,  ///< \ru Прохождение по гладкостыкующимся граням через ортогональные ребра (прямолинейные.) \en Movement on smooth-joint faces through orthogonal edges (straight). 
  fp_SmoothlyJointed      = 4,  ///< \ru Прохождение по гладкостыкующимся граням через прямолинейные ребра. \en Movement on smooth-joint faces through straight edges. //-V112 
};


//------------------------------------------------------------------------------
/** \brief \ru Типы точек пересечения.
           \en Types of intersection points. \~
  \details \ru Типы точек пересечения. \n
           \en Types of intersection points. \n \~
  \ingroup Point_Modeling
*/
// ---
enum MbeIntersectionType { 
  ipt_Simple  = 0, ///< \ru Обыкновенная точка пересечения. \en Ordinary intersection point. 
  ipt_Tangent = 1, ///< \ru Касательная точек пересечения. \en Tangent of intersection points. 
};


//------------------------------------------------------------------------------
/** \brief \ru Расположение полюсов.
           \en Location of the poles. \~
  \details \ru Расположение полюсов поверхности в параметрической области. \n
           \en The location of surface poles in the parametric region. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbePoleLocation { 
  pln_None  = -1,  ///< \ru Нет полюса. \en No pole. 
  pln_MinU  = 0,   ///< \ru Полюс при u = umin. \en Pole at u = umin. 
  pln_MaxU  = 1,   ///< \ru Полюс при u = umax. \en Pole at u = umax. 
  pln_MinV  = 2,   ///< \ru Полюс при v = vmin. \en Pole at v = vmin. 
  pln_MaxV  = 3,   ///< \ru Полюс при v = vmax. \en Pole at v = vmax. 
};


//------------------------------------------------------------------------------
/** \brief \ru Тип границы поверхности.
           \en Surface border type. \~
  \details \ru Тип границы поверхности. \n
           \en Surface border type. \n \~
  \ingroup Data_Structures
*/
// ---
enum MbeSurfacePoleType {
  spt_Undefined = 0, ///< \ru Тип не определен. \en A type is undefined. 
  spt_Point,         ///< \ru Точка. \en A point. 
  spt_Curve,         ///< \ru Кривая. \en A curve. 
};


//------------------------------------------------------------------------------
/** \brief \ru Типы элементарных тел.
           \en Types of elementary solids. \~
  \details \ru Типы элементарных тел, которые можно построить по нескольким точкам. \n
           \en Types of elementary solids which can be constructed by several points. \n \~
  \ingroup Build_Parameters
*/
//---
enum ElementaryShellType {
  et_Sphere      =  0, ///< \ru Шар (3 точки). \en Sphere (3 points).
  et_Torus       =  1, ///< \ru Тор (3 точки). \en Torus (3 points).
  et_Cylinder    =  2, ///< \ru Цилиндр (3 точки). \en Cylinder (3 points).
  et_Cone        =  3, ///< \ru Конус (3 точки). \en Cone (3 points).
  et_Block       =  4, ///< \ru Блок (4 точки). \en Block (4 points).
  et_Wedge       =  5, ///< \ru Клин (4 точки). \en Wedge (4 points).
  et_Prism       =  6, ///< \ru Призма (n + 1 точек, n > 2). \en Prism (n + 1 points, n > 2).
  et_Pyramid     =  7, ///< \ru Пирамида (n + 1 точек, n > 2). \en Pyramid (n + 1 points, n > 2).
  et_Plate       =  8, ///< \ru Плита (4 точки). \en Plate (4 points).
  et_Icosahedron =  9, ///< \ru Икосаэдр (3 точки). \en Icosahedron (3 points).
  et_Polyhedron  = 10, ///< \ru Многогранник (3 точки). \en Polyhedron (3 points).
  et_Tetrapipe   = 11, ///< \ru Тетратруба (3 точки). \en Tetrapipe (3 points).
  et_Octapipe    = 12, ///< \ru Октатруба (3 точки). \en Octapipe (3 points).
};


//------------------------------------------------------------------------------
/** \brief \ru Типы изменения смещения точек эквидистантных кривых и поверхностей.
           \en Types of points offset displacement for offset curves and offset surfaces from base objects. \~
  \details \ru Смещение точек эквидистантных кривых и поверхностей может быть константным, или выполняться по линейному закону, или выполняться по кубическому закону.
               Смещение является функцией параметров кривых и поверхностей. Кубическая функция смещения на краях имеет нулевые производные.
           \en The points displacement of offset curves and offset surfaces can be constant, or can be linear, or can be cubic.
               The offset is a function of the parameters of curves and surfaces. The cubic function has zero derivatives at the beginning and at the end. \~
  \ingroup Data_Structures
*/
// ---
enum MbeOffsetType {
  off_Empty = 0, ///< \ru Смещение отсутствует (нулевое). \en The offset is absent (null).
  off_Const = 1, ///< \ru Постоянное значение смещения. \en Constant value of offset.
  off_Linea = 2, ///< \ru Линейная функция смещения. \en Linear function of offset.
  off_Cubic = 3, ///< \ru Кубическая функция смещения. \en Cubic function of offset.
};


//------------------------------------------------------------------------------
/** \brief \ru Идентификаторы сообщений индикатора прогресса выполнения. 
           \en Identifiers of the execution progress indicator messages. \~
  \ingroup Data_Structures
*/
//---
enum MbeProgBarId_Common
{
  pbarId_Common_Beg = 0,

  pbarId_Read_Data,    ///< \ru Чтение данных. \en Data reading. 
  pbarId_Prepare_Data, ///< \ru Подготовка данных. \en Data preparing. 
  pbarId_Process_Data, ///< \ru Обработка данных. \en Data processing. 
  pbarId_Finish_Data,  ///< \ru Завершение обработки данных. \en Completion of data processing. 
  pbarId_Draw_Data,    ///< \ru Отображение данных. \en Data mapping. 
  pbarId_Write_Data,   ///< \ru Запись данных. \en Data writing. 

  pbarId_Common_End,
};


//------------------------------------------------------------------------------
/** \brief \ru Идентификаторы сообщений индикатора прогресса выполнения. Поверхность по пласту(сети) точек.
           \en Identifiers of the execution progress indicator messages. Surface by points layer(grid). \~
  \ingroup Data_Structures
*/
//---
enum MbeProgBarId_PointsSurface
{
  pbarId_PointsSurface_Beg = pbarId_Common_End + 1,

  pbarId_Solve_LinearEquationsSystem, ///< \ru Решение системы линейных уравнений. \en System of linear equations solving.
  pbarId_Remove_RedundantPoints,      ///< \ru Удаление избыточных точек. \en Removal of redundant points.
  pbarId_Build_ShellByPointsMesh,     ///< \ru Построение оболочки по сети точек. \en Construction of shell by points grid. 
  pbarId_Build_PointsCloudMesh,       ///< \ru Построение сети точек по пласту точек. \en Construction of points grid by points layer. 
  pbarId_Build_TriangleFaces,         ///< \ru Построение треугольных граней. \en Construction of triangular faces. 
  pbarId_Find_AdjacentEdges,          ///< \ru Поиск смежных ребер. \en Search adjacent edges.
  pbarId_Build_TrianglesShell,        ///< \ru Построение поверхности из треугольных граней. \en Construction of surface from triangular faces. 
  pbarId_Prepare_SurfaceData,         ///< \ru Подготовка данных для построения поверхности. \en Preparing data for surface construction. 
  pbarId_Check_Surface,               ///< \ru Проверка правильности построения поверхности. \en Check correctness of surface construction. 

  pbarId_PointsSurface_End,
};


#endif // __MB_ENUM_H
