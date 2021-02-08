////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение фантомов операций.
         \en Creation of phantom operations. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_PHANTOM_H
#define __ACTION_PHANTOM_H


#include <templ_s_array.h>
#include <mb_cart_point3d.h>
#include <space_item.h>
#include <op_shell_parameter.h>
#include <op_swept_parameter.h>
#include <position_data.h>
#include <topology_faceset.h>
#include <mb_operation_result.h>


class  MATH_CLASS MbCurve;
class  MATH_CLASS MbCurve3D;
class  MATH_CLASS MbSurface;
class  MATH_CLASS MbCurveEdge;
class  MATH_CLASS MbFace;
class  MATH_CLASS MbSolid;
class  MATH_CLASS MbSNameMaker;


//------------------------------------------------------------------------------
/** \brief \ru Построить фантомные поверхности скругления/фаски.
           \en Create phantom surfaces of fillet/chamfer. \~
  \details \ru Построить фантомные поверхности скругления/фаски и сложить в контейнер surfaces. \n
    По окончании работ поверхности можно и нужно удалить. \n
           \en Create phantom surfaces of fillet/chamfer and store them in the container 'surfaces'. \n
    After finish working with the surfaces they should be deleted. \n \~
  \param[in]  solid - \ru Исходное тело.
                      \en The initial solid. \~
  \param[in]  edges - \ru Множество выбранных ребер для скругления/фаски.
                      \en An array of edges for fillet/chamfer. \~
  \param[in]  params - \ru Параметры операции скругления/фаски.
                       \en Parameters of the fillet/chamfer operation. \~
  \param[out] result - \ru Поверхности скругления/фаски.
                       \en The fillet/chamfer surfaces. \~
  \return \ru Возвращает код результата построения.
          \en Returns the creation result code. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (MbResultType) SmoothPhantom( const MbSolid &              solid, 
                                              RPArray<MbCurveEdge> & edges, 
                                        const SmoothValues &         params, 
                                              RPArray<MbSurface> &   result );


//------------------------------------------------------------------------------
/** \brief \ru Построить фантомные поверхности скругления/фаски. 
           \en Create phantom surfaces of fillet/chamfer.\~
  \details \ru Построить фантомные поверхности скругления/фаски и сложить в контейнер surfaces. \n
    По окончании работ поверхности можно и нужно удалить.
           \en Create phantom surfaces of fillet/chamfer and store them in the container 'surfaces'. \n
    After finish working with the surfaces they should be deleted. \~
  \param[in]  solid - \ru Исходное тело.
                      \en The initial solid. \~
  \param[in]  edges - \ru Множество выбранных ребер и функций изменения радиуса для скругления/фаски.
                      \en An array of edges and radius laws for fillet/chamfer. \~
  \param[in]  params - \ru Параметры операции скругления/фаски.
                       \en Parameters of the fillet/chamfer operation. \~
  \param[out] result - \ru Поверхности скругления/фаски.
                       \en The fillet/chamfer surfaces. \~
  \return \ru Возвращает код результата построения.
          \en Returns the creation result code. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (MbResultType) SmoothPhantom( const MbSolid &                solid, 
                                              SArray<MbEdgeFunction> & edges, 
                                        const SmoothValues &           params, 
                                              RPArray<MbSurface> &     result );


//------------------------------------------------------------------------------
/** \brief \ru Построить последовательности гладко стыкующихся рёбер.
           \en \~
  \details \ru Построить последовательности гладко стыкующихся рёбер, скругляемых одновременно,
    а также поверхности скругления/фаски (массив surfaces). \n
    По окончании работ поверхности можно и нужно удалить.
           \en \~
  \param[in]  solid - \ru Исходное тело.
                      \en The initial solid. \~
  \param[in]  edges - \ru Множество выбранных ребер для скругления/фаски.
                      \en An array of edges for fillet/chamfer. \~
  \param[in]  params - \ru Параметры операции скругления/фаски.
                       \en Parameters of the fillet/chamfer operation. \~
  \param[in]  createSurfaces - \ru Создавать ли поверхности скругления/фаски для фантома?
                        \en Create a fillet/chamfer surfaces for phantom. \~
  \param[out] sequences - \ru Последовательность гладко стыкующихся рёбер.
                          \en Sequence of smooth mating edges. \~
  \param[out] result - \ru Поверхности скругления/фаски.
                       \en The fillet/chamfer surfaces. \~
  \return \ru Возвращает код результата построения.
          \en \~
  \ingroup Algorithms_3D
*/

// ---
MATH_FUNC (MbResultType) SmoothSequence( const MbSolid &                 solid, 
                                               RPArray<MbCurveEdge> &    edges, 
                                         const SmoothValues &            params, 
                                               bool                      createSurfaces,
                                               RPArray<MbEdgeSequence> & sequences,
                                               RPArray<MbSurface> &      result );


//------------------------------------------------------------------------------
/** \brief \ru Построить последовательности гладко стыкующихся рёбер.
           \en \~
  \details \ru Построить последовательности гладко стыкующихся рёбер, скругляемых одновременно,
    а также поверхности скругления/фаски (массив surfaces). \n
    По окончании работ поверхности можно и нужно удалить.
           \en \~
  \param[in]  solid - \ru Исходное тело.
                      \en The initial solid. \~
  \param[in]  edges - \ru Множество выбранных ребер и функций изменения радиуса для скругления/фаски.
                      \en An array of edges and radius laws for fillet/chamfer. \~
  \param[in]  params - \ru Параметры операции скругления/фаски.
                       \en Parameters of the fillet/chamfer operation. \~
  \param[in]  createSurfaces - \ru Создавать ли поверхности скругления/фаски для фантома?
                               \en Create a fillet/chamfer surfaces for phantom. \~
  \param[out] sequences - \ru Последовательность гладко стыкующихся рёбер.
                          \en Sequence of smooth mating edges. \~
  \param[out] result - \ru Поверхности скругления/фаски.
                       \en The fillet/chamfer surfaces. \~
  \return \ru Возвращает код результата построения.
          \en \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (MbResultType) SmoothSequence( const MbSolid &                 solid, 
                                               SArray<MbEdgeFunction> &  edges, 
                                         const SmoothValues &            params, 
                                               bool                      createSurfaces,
                                               RPArray<MbEdgeSequence> & sequences,
                                               RPArray<MbSurface> &      result );


//------------------------------------------------------------------------------
/** \brief \ru Построить фантомные эквидистантные поверхности для граней оболочки.
           \en Create phantom offset surfaces for faces of a shell. \~
  \details \ru Построить фантомные эквидистантные поверхности для граней оболочки, \n
    кроме имеющих перечислены  кроме имеющих перечисленные индексы, и сложить в массив surfaces. \n
    По окончании работ поверхности можно и нужно удалить.
           \en Create phantom offset surfaces for faces of a shell, \n 
    except the faces with specified indices and store them in array 'surfaces'. \n
    After finish working with the surfaces they should be deleted. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The initial solid. \~
  \param[in] outFaces - \ru Множество вскрываемых граней тела.
                        \en An array of shelling faces of the solid. \~
  \param[in] offFaces - \ru Множество граней, для которых заданы индивидуальные значения толщин.
                        \en An array of faces for which the individual values of thickness are specified. \~
  \param[in] offDists - \ru Множество индивидуальных значений толщин (должен быть синхронизирован с массивом offFaces).
                        \en An array of individual values of thickness (must be synchronized with the array 'offFaces'). \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[out] result - \ru Результат операции.
                       \en The operation result. \~
  \param[out] hpShellFaceInd - \ru Номер грани в исходной оболочки для построения хот-точки.
                               \en The face number in the initial shell for a hot-point creation. \~
  \return \ru Возвращает код результата построения.
          \en Returns the creation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) OffsetPhantom( const MbSolid &         solid, 
                                              RPArray<MbFace> & outFaces, 
                                              RPArray<MbFace> & offFaces,
                                              SArray<double> &  offDists,
                                        const SweptValues &     params, 
                                        const MbSNameMaker &    operNames,
                                              MbFaceShell *&    result,
                                              size_t *          hpShellFaceInd = NULL ); // \ru Номер грани в исходной оболочки для построения хот-точки); \en The face number in the initial shell for a hot-point creation); 


//------------------------------------------------------------------------------
/** \brief \ru Построить фантом габаритного куба в локальной системе координат.
           \en Create a phantom of a bounding box in local coordinate system. \~
  \details \ru Построить фантом габаритного куба в локальной системе координат. \n
           \en Create a phantom of a bounding box in local coordinate system. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The initial solid. \~
  \param[in] place - \ru Локальная система координат (ЛСК).
                     \en A local coordinate system (LCS). \~
  \param[in] bScale - \ru Является ли ЛСК масштабирующей.
                      \en Whether the LCS is scaling. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[out] result - \ru Фантом локального куба.
                        \en The phantom of the local bounding box. \~
  \return \ru Возвращает код результата построения.
          \en Returns the creation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) LocalCubePhantom( const MbSolid &       solid,
                                           const MbPlacement3D & place,
                                                 bool            bScale,
                                           const MbSNameMaker &  operNames,
                                                 MbSolid *&      result );


//------------------------------------------------------------------------------
/** \brief \ru Определить фантомное направление усечения.
           \en Determine a phantom direction of truncation. \~
  \details \ru Определить фантомное направление усечения по усеченной грани исходного тела. \n
           \en Determine a phantom direction of truncation given the truncated face of the initial solid. \n \~
  \param[in] truncatingEdge - \ru Ребро усеченной грани исходного тела.
                              \en An edge of truncated face of the initial solid. \~
  \param[in] dirPlace - \ru Система координат направления усечения (Ось Z - направление усечения).
                        \en A coordinate system of truncation direction (Z-axis is a truncation direction). \~
  \return \ru Возвращает true, если получилось определить направление.
          \en Returns true if the direction has been successfully determined. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) TruncatDirection( const MbCurveEdge &   truncatingEdge, 
                                         MbPlacement3D & dirPlace );


//------------------------------------------------------------------------------
/** \brief \ru Построить опорные точки размеров операции скругления/фаски.
           \en Create support points of fillet/chamfer operation sizes. \~
  \details \ru Построить опорные точки размеров операции скругления/фаски и сложить в контейнер data. \n
    Первые две точки лежат на краях поверхности скругления/фаски.
           \en Create support points of fillet/chamfer operation sizes and store them in container 'data'. \n
    The first two points lie on the fillet/chamfer surface boundary. \~
  \param[in]  solid - \ru Исходное тело.
                      \en The initial solid. \~
  \param[in]  edges - \ru Множество выбранных ребер для скругления/фаски.
                      \en An array of edges for fillet/chamfer. \~
  \param[in]  params - \ru Параметры операции скругления/фаски.
                       \en Parameters of the fillet/chamfer operation. \~
  \param[out] result - \ru Опорные точки размеров операции скругления/фаски.
                       \en Support points of the fillet/chamfer operation sizes. \~
  \param[in]  edgeParam - \ru Параметр точки на ребре (0 <= edgeParam <= 1).
                          \en The parameter of a point on the edge (0 <= edgeParam <= 1). \~
  \param[in]  dimensionEdge - \ru Ребро, на котором дать опорные точки.
                              \en The edge on which the support points are to be created. \~
  \return \ru Возвращает код результата построения.
          \en Returns the creation result code. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (MbResultType) SmoothPositionData( const MbSolid &                 solid, 
                                                   RPArray<MbCurveEdge> &    edges, 
                                             const SmoothValues &            params, 
                                                   RPArray<MbPositionData> & result,
                                                   double                    edgeParam = 0.5,
                                             const MbCurveEdge *             dimensionEdge = NULL );


//------------------------------------------------------------------------------
/** \brief \ru Построить опорные точки размеров операции скругления/фаски.
           \en Create support points of fillet/chamfer operation sizes. \~
  \details \ru Построить опорные точки размеров операции скругления/фаски и сложить в контейнер data. \n
    Первые две точки лежат на краях поверхности скругления/фаски.
           \en Create support points of fillet/chamfer operation sizes and store them in container 'data'. \n
    The first two points lie on the fillet/chamfer surface boundary. \~
  \param[in]  solid - \ru Исходное тело.
                      \en The initial solid. \~
  \param[in]  edges - \ru Множество выбранных ребер для скругления/фаски и функций изменения радиуса для скругления/фаски.
                      \en The array of specified edges for fillet/chamfer and radius laws for fillet/chamfer. \~
  \param[in]  params - \ru Параметры операции скругления/фаски.
                       \en Parameters of the fillet/chamfer operation. \~ 
  \param[out] result - \ru Опорные точки размеров операции скругления/фаски.
                       \en Support points of the fillet/chamfer operation sizes. \~
  \param[in]  edgeParam - \ru Параметр точки на ребре (0 <= edgeParam <= 1).
                          \en The parameter of a point on the edge (0 <= edgeParam <= 1). \~
  \param[in]  dimensionEdge - \ru Ребро, на котором дать опорные точки.
                              \en The edge on which the support points are to be created. \~
  \return \ru Возвращает код результата построения.
          \en Returns the creation result code. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (MbResultType) SmoothPositionData( const MbSolid &                 solid, 
                                                   SArray<MbEdgeFunction> &  edges, 
                                             const SmoothValues &            params, 
                                                   RPArray<MbPositionData> & result,
                                                   double                    edgeParam = 0.5,
                                             const MbCurveEdge *             dimensionEdge = NULL );


#endif // __ACTION_PHANTOM_H
