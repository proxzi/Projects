////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Методы построения незамкнутых тел.
         \en Functions for open solids construction. \~
  \details \ru Геометрическое ядро C3D поддерживает поверхностное моделирование. 
    Результатом поверхностного моделирования являются элементы геометрической модели, 
    которые будем называть незамкнутыми телами. Незамкнутые тела характерны тем,
    что они описывают не всю поверхность моделируемого объекта, а только часть её.
    Часто незамкнутое тело состоит из одной грани. В незамкнутом теле всегда присутствуют 
    краевые рёбра. Незамкнутое тело описывает множество точек, принадлежащих только граням
    этого тела, тогда как замкнутое тело описывает множество точек, располагающихся
    на поверхности моделируемого объекта и внутри него.
           \en The geometric kernel C3D supports the surface modeling. 
    The result of surface modeling are elements of geometric model 
    which are called open solids here. Open solids
    describe not the whole surface of an object of modeling but only a part of it.
    An open solid often consists of one face. An open solid always contains 
    boundary edges. An open solid describes a point set that belong to faces of the solid only,
    whereas a closed solid describes a point set
    on the surface of the modeled object and inside it. \~ 
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SHELL_H
#define __ACTION_SHELL_H


#include <templ_rp_array.h>
#include <templ_s_array.h>
#include <mb_cart_point3d.h>
#include <space_item.h>
#include <op_boolean_flags.h>
#include <op_shell_parameter.h>
#include <op_swept_parameter.h>
#include <topology_faceset.h>
#include <mb_operation_result.h>


class  MATH_CLASS  MbCurve;
class  MATH_CLASS  MbCurve3D;
class  MATH_CLASS  MbSurface;
class  MATH_CLASS  MbCurveEdge;
class  MATH_CLASS  MbFace;
class  MATH_CLASS  MbSolid;
class  MATH_CLASS  MbSNameMaker;
class  MATH_CLASS  MbPatchCurve;
class              IProgressIndicator;


//------------------------------------------------------------------------------
/** \brief \ru Построить заплатку.
           \en Create a patch. \~
  \details \ru Построить заплатку по выбранным ребрам. \n
           \en Create a patch from the specified edges. \n \~
  \param[in] initEdges - \ru Набор ребер.
                         \en A set of edges. \~ 
  \param[in] p - \ru Параметры операции.
                 \en The operation parameters. \~
  \param[in] n - \ru Именователь.
                 \en An object for naming the new objects. \~ 
  \param[out] result - \ru Построенная заплатка.
                       \en The required patch. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) PatchShell( const RPArray<MbPatchCurve> & initEdges, 
                                     const PatchValues &           p, 
                                     const MbSNameMaker &          n, 
                                           MbSolid *&              result );


//------------------------------------------------------------------------------
/** \brief \ru Построить заплатку.
           \en Create a patch. \~
  \details \ru Построить заплатку по выбранным кривым. \n
           \en Create a patch from the specified curves. \n \~
  \param[in] initCurves - \ru Набор кривых.
                          \en A set of curves. \~ 
  \param[in] p - \ru Параметры операции.
                 \en The operation parameters. \~
  \param[in] n - \ru Именователь.
                 \en An object for naming the new objects. \~ 
  \param[out] result - \ru Построенная заплатка.
                       \en The required patch. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) PatchShell( const RPArray<MbCurve3D> & initCurves, 
                                     const PatchValues &        p, 
                                     const MbSNameMaker &       n, 
                                           MbSolid *&           result );


//------------------------------------------------------------------------------
/** \brief \ru Построить незамкнутое тело по множеству групп точек.
           \en Create an open solid given a set of point groups. \~
  \details \ru Построить незамкнутое тело по сечениям, образованным сплайнами, построенными по группе контрольных точек. \n
           \en Create an open lofted solid whose profiles are defined by splines created from the specified groups of points. \n \~
  \param[in] points - \ru Набор точек.
                      \en A point set. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] name - \ru Идентификатор.
                    \en An identifier. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) LoftedShell( const RPArray< SArray<MbCartPoint3D> > & points,
                                      const MbSNameMaker &                     names, 
                                            SimpleName                         name, 
                                            MbSolid *&                         result );


//------------------------------------------------------------------------------
/** \brief \ru Построить незамкнутое тело по множеству кривых.
           \en Create an open solid from a set of curves. \~
  \details \ru Построить незамкнутое тело по сечениям, образованным кривыми. \n
           \en Create an open lofted solids whose profiles are defined by the curves. \n \~
  \param[in] curves - \ru Набор кривых.
                      \en A set of curves. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[in] name - \ru Идентификатор.
                    \en An identifier. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) LoftedShell( const RPArray<MbCurve3D> & curves, 
                                      const MbSNameMaker &       names, 
                                            SimpleName           name, 
                                            MbSolid *&           result );


//------------------------------------------------------------------------------
/** \brief \ru Построить незамкнутое эквидистантное тело.
           \en Create an open offset solid. \~
  \details \ru Построить незамкнутое эквидистантное тело на базе указанных в initFaces граней. \n
           \en Create an open offset solid on the basis of the faces 'initFaces'. \n \~
  \param[in] solid - \ru Исходное тело.
                     \en The initial solid. \~
  \param[in] sameShell - \ru Режим копирования тела.
                         \en Whether to copy the solid. \~
  \param[in] initFaces - \ru Грани исходного тела для построения.
                         \en Faces of the initial solid for construction. \~
  \param[in] checkFacesConnection - \ru Необходимость проверки связности выбранных граней.
                                    \en Whether to check connectivity of the specified faces. \~
  \param[in] p - \ru Параметры операции.
                 \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[in]  copyFaceAttrs - \ru Копировать атрибуты из исходных граней в эквидистантные.
                              \en Copy attributes of initial faces to offset faces. \~
  \param[out] result - \ru Эквидистантная оболочка.
                       \en The offset shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) OffsetShell(       MbSolid &         solid, 
                                            MbeCopyMode       sameShell, 
                                            RPArray<MbFace> & initFaces, 
                                            bool              checkFacesConnection, 
                                            SweptValues &     p, 
                                      const MbSNameMaker &    operNames,
                                            bool              copyFaceAttrs,
                                            MbSolid *&        result );


//------------------------------------------------------------------------------
/** \brief \ru Построить незамкнутое тело по множеству точек.
           \en Create an open solid from a point set. \~
  \details \ru Построить незамкнутое тело по множеству точек, заданных в параметрах построения. \n
           \en Create an open solid from a point set specified in parameters. \n \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[in] isPhantom - \ru Режим создания фантома.
                         \en Create in the phantom mode. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \param[in,out] progBar - \ru Индикатор прогресса выполнения операции.
                           \en A progress indicator of the operation. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) NurbsSurfacesShell(       NurbsSurfaceValues & params,
                                             const MbSNameMaker &       operNames,
                                                   bool                 isPhantom,
                                                   MbSolid *&           result,
                                                   IProgressIndicator * progBar );


//------------------------------------------------------------------------------
/** \brief \ru Построить незамкнутое тело по сети кривых.
           \en Create an open solid from a set of curves. \~
  \details \ru Построить незамкнутое тело по сети кривых, заданных в параметрах построения. \n
           \en Create an open solid from a set of curves specified in the parameters. \n \~
  \param[in] pars - \ru Параметры операции.
                    \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[in] isPhantom - \ru Режим создания фантома.
                         \en Create in the phantom mode. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) MeshShell(       MeshSurfaceValues & pars, 
                                    const MbSNameMaker &      operNames, 
                                          bool                isPhantom,  
                                          MbSolid *&          result );


//------------------------------------------------------------------------------
/** \brief \ru Усечь (обрезать) незамкнутое тело.
           \en Truncate an open solid. \~
  \details \ru Выполнить построение незамкнутого тела путём усечения исходного тела. \n
           \en Create an open solid by truncation the initial solid. \n \~
  \param[in] initSolid - \ru Исходная оболочка.
                         \en The initial shell. \~
  \param[in] selIndices - \ru Номера выбранных граней (если массив пуст, то вся оболочка).
                          \en The numbers of selected faces (if the array is empty, the whole shell is selected). \~
  \param[in] initCopyMode - \ru Режим копирования исходных оболочек.
                            \en Whether to copy the initial shells. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[in] truncatingItems - \ru Усекающие объекты.
                               \en Truncating objects. \~
  \param[in] truncatingOrients - \ru Ориентация усекающих объектов.
                                 \en The truncating objects orientation. \~
  \param[in] truncatingSplitMode - \ru Кривые используются как линии разъема.
                                   \en The curves are used as parting lines. \~
  \param[in] truncatingCopyMode - \ru Режим копирования усекающих оболочек.
                                  \en Whether to copy the truncating shells. \~
  \param[in] mergeFlags - \ru Флаги слияния элементов оболочки.
                          \en Control flags of shell items merging. \~
  \param[out] result - \ru Усеченная оболочка.
                       \en The truncated shell. \~
  \param[out] resultPlace - \ru Фантомное направление усечения.
                            \en A phantom direction of truncation. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) TruncateShell(       MbSolid              & initSolid,
                                              SArray<size_t>       & selIndices,
                                              MbeCopyMode            initCopyMode,
                                        const MbSNameMaker         & operNames,
                                              RPArray<MbSpaceItem> & truncatingItems,
                                              SArray<bool>         & truncatingOrients,
                                              bool                   truncatingSplitMode,
                                              MbeCopyMode            truncatingCopyMode,
                                        const MbMergingFlags       & mergeFlags,
                                              MbSolid             *& result,
                                              MbPlacement3D       *& resultPlace );


//------------------------------------------------------------------------------
/** \brief \ru Построить линейчатое незамкнутое тело.
           \en Create an open ruled solid. \~
  \details \ru Построить линейчатое незамкнутое тело по двум кривым, заданным в параметрах. \n
           \en Create an open ruled solid from two curves specified in parameters. \n \~
  \param[in] pars - \ru Параметры операции.
                    \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[in] isPhantom - \ru Режим создания фантома.
                         \en Create in the phantom mode. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) RuledShell(       RuledSurfaceValues & pars, 
                                     const MbSNameMaker &       operNames, 
                                           bool                 isPhantom,  
                                           MbSolid *&           result );


//------------------------------------------------------------------------------
/** \brief \ru Проверить кривую для построения линейчатого тела.
           \en Check the curve for a ruled solid creation. \~
  \details \ru Проверить вторую кривую на согласованность с первой кривой для построения
    линейчатого незамкнутого тела и выполнить необходимую модификацию второй кривой. \n
           \en Check the second curve for consistency with the first curve for creation
    of the open ruled solid and make the necessary modification of the second curve. \n \~
  \param[in] curve0 - \ru Первая кривая.
                      \en The first curve. \~
  \param[in] curve1 - \ru Вторая кривая.
                      \en The second curve. \~
  \param[out] isInverted1 - \ru Была ли вторая кривая инвертирована.
                            \en Whether the second curve was inverted. \~
  \param[out] isShifted1 - \ru Было ли смещено начало второй кривой.
                           \en Whether the beginning of the first curve was shifted. \~
  \param[in] version - \ru Версия операции.
                       \en The version of the operation. \~
  \warning \ru Вспомогательная функция операции RuledShell.
           \en An auxiliary function of operation 'RuledShell'. \~
  \ingroup Shell_Modeling
*/
//---
MATH_FUNC (void) CheckRuledCurve( const MbCurve3D & curve0,
                                  const MbCurve3D & curve1,
                                        bool &      isInverted1,
                                        bool &      isShifted1,
                                        VERSION     version );


//------------------------------------------------------------------------------
/** \brief \ru Проверить параметры кривой для построения линейчатого тела.
           \en Check the curve parameters for creation of a ruled solid. \~
  \details \ru Проверить параметры кривой и выполнить нормализацию параметров замкнутой кривой. \n
           \en Check the curve parameters and perform the normalization of a closed curve parameters. \n \~
  \param[in] curve - \ru Кривая.
                     \en The curve. \~
  \param[in,out] params - \ru Множество параметров кривой.
                          \en An array of the curve parameters. \~
  \param[in] isAscending - \ru Будет ли порядок параметров возрастающим.
                           \en Whether the parameters are specified in the ascending order. \~
  \return \ru Возвращает true, если удалось нормализовать массив параметров.
          \en Returns true if the parameter array has been successfully normalized. \~
  \warning \ru Вспомогательная функция операции RuledShell.
           \en An auxiliary function of operation 'RuledShell'. \~
  \ingroup Shell_Modeling
*/
//---
MATH_FUNC (bool) CheckRuledParams( const MbCurve3D &      curve, 
                                         SArray<double> & params, 
                                         bool             isAscending );


//------------------------------------------------------------------------------
/** \brief \ru Построить продолжение незамкнутого тела выдавливанием.
           \en Create an extension of an open solid by extrusion. \~
  \details \ru Построить продолжение незамкнутого тела путём выдавливания указанных краевых рёбер заданной грани тела. \n
           \en Create an extension of an open solid by extrusion of specified boundary edges of the given face of the solid. \n \~
  \param[in] solid - \ru Исходная оболочка.
                     \en The initial shell. \~
  \param[in] sameShell - \ru Режим копирования оболочки.
                         \en Whether to copy the shell. \~
  \param[in] face - \ru Продляемая грань в исходной оболочке.
                    \en A face of the initial shell to be extended. \~
  \param[in] edges - \ru Множество ребер продляемой грани, через которые выполняется продление.
                     \en An array of edges through which to extend the face. \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) ExtensionShell(       MbSolid &              solid, 
                                               MbeCopyMode            sameShell,
                                               MbFace &               face, 
                                         const RPArray<MbCurveEdge> & edges, 
                                         const ExtensionValues &      params, 
                                         const MbSNameMaker &         operNames, 
                                               MbSolid *&             result );


//------------------------------------------------------------------------------
/** \brief \ru Построить тело соединения по двум кривым.
           \en Create a joint solid from two curves. \~
  \details \ru Построить незамкнутое тело соединения по двум кривым на поверхности. \n
           \en Create an open joint solid from two curves on a surface. \n \~
  \param[in] curve1 - \ru Первая поверхностная кривая.
                      \en The first curve on a surface. \~
  \param[in] curve2 - \ru Вторая поверхностная кривая.
                      \en The second curve on a surface. \~
  \param[in] parameters - \ru Параметры операции.
                          \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
//---
MATH_FUNC (MbResultType) JoinShell(       MbSurfaceCurve &    curve1, 
                                          MbSurfaceCurve &    curve2, 
                                          JoinSurfaceValues & parameters,
                                    const MbSNameMaker &      operNames, 
                                          MbSolid *&          result );


//------------------------------------------------------------------------------
/** \brief \ru Построить тело соединения по двум множествам рёбер.
           \en Create a joint solid from two sets of edges. \~
  \details \ru Построить незамкнутое тело соединения по двум множествам ребер. \n
           \en Create an open joint solid from two sets of edges. \n \~
  \param[in] edges1 - \ru Первая группа ребер.
                      \en The first group of edges. \~
  \param[in] orients1 - \ru Ориентации ребер в первой группе.
                        \en The edges senses in the first group. \~
  \param[in] edges2 - \ru Вторая группа ребер.
                      \en The second group of edges. \~
  \param[in] orients2 - \ru Ориентация ребер во второй группе.
                        \en The edges senses in the second group. \~
  \param[in] matr1 - \ru Матрица преобразования первой группы ребер в единую систему координат.
                     \en The matrix of transformation of the first group of edges to the common coordinate system. \~
  \param[in] matr2 - \ru Матрица преобразования второй группы ребер в единую систему координат.
                     \en The matrix of transformation of the second group of edges to the common coordinate system. \~
  \param[in] parameters - \ru Параметры операции.
                          \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \param[in] isPhantom - \ru Режим фантома операции.
                         \en The operation phantom mode. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
//---
MATH_FUNC (MbResultType) JoinShell( const RPArray<MbCurveEdge> & edges1, 
                                    const SArray<bool> &         orients1,
                                    const RPArray<MbCurveEdge> & edges2, 
                                    const SArray<bool> &         orients2,
                                    const MbMatrix3D &           matr1,
                                    const MbMatrix3D &           matr2,
                                          JoinSurfaceValues &    parameters,
                                    const MbSNameMaker &         operNames, 
                                          MbSolid *&             result,
                                          bool                   isPhantom = false );


//------------------------------------------------------------------------------
/** \brief \ru Разделить оболочку на части по заданному набору ребер.
           \en Divide a shell into parts using a given set of edges. \~
  \details \ru Разделить оболочку на части по заданному набору ребер. \n
           \en Divide shell into parts using a given set of edges. \n \~
  \param[in] solid - \ru Оболочка.
                     \en A shell. \~
  \param[in] sameShell - \ru Режим копирования оболочки.
                         \en Whether to copy the shell. \~
  \param[in] edges - \ru Набор ребер.
                     \en Set of edges. \~
  \param[in] operNames - \ru Именователь.
                          \en An object for naming the new objects. \~
  \param[out] result - \ru Результирующая оболочка.
                       \en The required shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
\ingroup Shell_Modeling
*/
//---
MATH_FUNC (MbResultType) DivideShell(       MbSolid              & solid,
                                            MbeCopyMode            sameShell,
                                      const RPArray<MbCurveEdge> & edges, 
                                      const MbSNameMaker &         operNames, 
                                            MbSolid *&             result );


//------------------------------------------------------------------------------
/** \brief \ru Проверить кривую для построения тела соединения.
           \en Check a curve for creation a joint solid. \~
  \details \ru Проверить вторую кривую на согласованность с первой кривой для построения
    незамкнутого тела соединения и выполнить необходимую модификацию второй кривой. \n
           \en Check the second curve for consistency with the first curve for creation
    of the open joint solid and make the necessary modification of the second curve. \n \~
  \param[in] curve1 - \ru Первая кривая.
                      \en The first curve. \~
  \param[in] curve2 - \ru Вторая кривая.
                      \en The second curve. \~
  \param[out] isInverted1 - \ru Была ли вторая кривая инвертирована.
                            \en Whether the second curve was inverted. \~
  \param[out] isShifted1 - \ru Было ли смещено начало второй кривой.
                           \en Whether the beginning of the first curve was shifted. \~
  \param[in] version - \ru Версия операции.
                       \en The version of the operation. \~
  \warning \ru Вспомогательная функция операции JoinShell.
           \en An auxiliary function of operation JoinShell. \~
  \ingroup Shell_Modeling
*/
//---
MATH_FUNC (void) CheckJoinedCurve( const MbCurve3D & curve1,
                                   const MbCurve3D & curve2,
                                         bool &      isInverted1,
                                         bool &      isShifted1,
                                         VERSION     version );


//------------------------------------------------------------------------------
/** \brief \ru Проверить параметры кривой для построения тела соединения.
           \en Check the curve parameters for creation of a joint solid. \~
  \details \ru Проверить параметры кривой и нормализовать параметры замкнутой кривой. \n
           \en Check the curve parameters and normalize a closed curve parameters. \n \~
  \param[in] curve - \ru Кривая.
                     \en The curve. \~
  \param[in,out] params - \ru Множество параметров кривой.
                          \en An array of the curve parameters. \~
  \param[in] isAscending - \ru Будет ли порядок параметров возрастающим.
                           \en Whether the parameters are specified in the ascending order. \~
  \return \ru Возвращает true, если удалось нормализовать массив параметров.
          \en Returns true if the parameter array has been successfully normalized. \~
  \warning \ru Вспомогательная функция операции JoinShell.
           \en An auxiliary function of operation JoinShell. \~
  \ingroup Curve3D_Modeling
*/
//---
MATH_FUNC (bool) CheckJoinedParams( const MbCurve3D &      curve, 
                                          SArray<double> & params, 
                                          bool             isAscending );


//------------------------------------------------------------------------------
/** \brief \ru Построить кривую по множеству рёбер.
           \en Create a curve from a set of edges. \~
  \details \ru Создать кривую для поверхности соединения по списку ребер. \n
           \en Create a curve for a surface of the joint from a list of edges. \n \~
  \param[in] edges - \ru Набор ребер.
                     \en A set of edges. \~
  \param[in] orients - \ru Ориентации ребер.
                       \en Edges senses. \~
  \param[in] matr - \ru Матрица преобразования ребер.
                    \en Edges transformation matrix. \~
  \param[out] res - \ru Результат операции.
                    \en The operation result. \~
  \return \ru Возвращает указатель на кривую, если ее получилось создать,
    иначе возвращает ноль.
          \en Returns a pointer to the curve if it has been successfully created,
    otherwise it returns null. \~
  \warning \ru Вспомогательная функция операции JoinShell.
           \en An auxiliary function of operation JoinShell. \~
  \ingroup Curve3D_Modeling
*/
//---
MATH_FUNC (MbCurve3D *) CreateJoinedCurve( const RPArray<MbCurveEdge> & edges, 
                                           const SArray<bool> &         orients,
                                           const MbMatrix3D &           matr,
                                                 MbResultType &         res );


//------------------------------------------------------------------------------
/** \brief \ru Построить тело сопряжения несвязанных граней.
           \en Create a solid of two non-connected faces. \~
  \details \ru Построить незамкнутое тело, состоящее из грани скругления между двумя несвязанными гранями. \n
           \en Create an open solid that consists of a fillet face between two non-connected faces. \n \~
  \param[in] solid1 - \ru Первое тело.
                      \en The first solid. \~
  \param[in] face1 - \ru Сопрягаемая грань первого тела.
                     \en The first solid face to fillet. \~
  \param[in] solid2 - \ru Второе тело.
                      \en The second solid. \~
  \param[in] face2 - \ru Сопрягаемая грань второго тела.
                     \en The second solid face to fillet. \~
  \param[in] params - \ru Параметры операции.
                      \en The operation parameters. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка (тело).
                       \en The resultant shell (solid). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) FacesFillet( const MbSolid &      solid1,
                                      const MbFace &       face1,
                                      const MbSolid &      solid2,
                                      const MbFace &       face2,
                                      const SmoothValues & params,
                                      const MbSNameMaker & names,
                                            MbSolid *&     result );


//------------------------------------------------------------------------------
/** \brief \ru Построить тело на базе элементарной поверхности.
           \en Create a solid given an elementary surface. \~
  \details \ru Построить тело, состоящее из одной грани, на базе исходной элементарной поверхности. \n
           \en Create a solid which consists of a face with the specified underlying elementary surface. \n \~
  \param[in] surface - \ru Поверхность.
                       \en The surface. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка.
                       \en The resultant shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) ElementaryShell( const MbSurface &    surface,
                                          const MbSNameMaker & names, 
                                                MbSolid *&     result );


//------------------------------------------------------------------------------
/** \brief \ru Построить тело на базе поверхности.
           \en Create a solid given a surface. \~
  \details \ru Построить тело, состоящее из одной грани, на базе исходной поверхности.
  Поверхность должна быть без самопересечений, с корректной ориентацией
  ограничивающих кривых в случае поверхности MbCurveBoundedSurface. \n
           \en Create a solid which consists of a face with the specified underlying surface.
  The surface should have no self-intersections,
  the bounding curves should be correctly oriented in case of surface MbCurveBoundedSurface. \n \~
  \param[in] surface - \ru Поверхность.
                       \en The surface. \~
  \param[in] names - \ru Именователь.
                     \en An object for naming the new objects. \~
  \param[out] result - \ru Построенная оболочка.
                       \en The resultant shell. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) SurfaceShell( const MbSurface &    surface,
                                       const MbSNameMaker & names, 
                                             MbSolid *&     result );


//------------------------------------------------------------------------------
/** \brief \ru Разрезать тело силуэтным контуром. 
           \en Cut a solid by a silhouette contour. \~
  \details \ru Построить оболочки, полученные в результате разрезания тела его силуэтным контуром. \n 
           \en Create solids as a result of cutting a solids by its silhouette contour.\n\~
  \param[in] shell          - \ru Исходное тело. 
                              \en The solid\~
  \param[in] sameShell      - \ru Способ передачи данных при копировании оболочек. 
                              \en Methods of transferring data while copying shells \~
  \param[in] eye            - \ru Направление взгляда.
                              \en Eye's direction. \~
  \param[out] outlineCurves - \ru Кривые, входящие в силуэтный контур.
                            - \en Curves of the silhouette contour. \~
  \param[out] result        - \ru Тела, полученные в результате применения операции. 
                            - \en The resultant solids.\~
  \return \ru Возвращает код результата операции.\~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) CutShellSilhouetteContour(       MbSolid &            solid, 
                                                          MbeCopyMode          sameShell, 
                                                    const MbVector3D &         eye,
                                                    const VERSION              version,
                                                          RPArray<MbCurve3D> & outlineCurves,
                                                          RPArray<MbSolid> &   result );


//------------------------------------------------------------------------------
/** \brief \ru Сшить грани нескольких тел в одно тело.
           \en Stitch faces of several solids into single solid. \~
  \details \ru Сшить стыкующиеся друг с другом грани нескольких тел в одно тело. Ориентация граней может быть изменена. \n
           \en Stitch faces of several solids with coincident edges into single solid. The faces orientation can be changed. \n \~
  \param[in] initialSolids - \ru Множество тел для сшивки.
                             \en An array of solids for stitching. \~
  \param[in] operNames - \ru Именователь операции.
                         \en An object defining names generation in the operation. \~
  \param[in] formSolidBody - \ru Флаг формирования твердого тела из результирующей оболочки.
                             \en Whether to form a solid solid from the resultant shell. \~
  \param[in] stitchPrecision - \ru Точность сшивки.
                               \en Stitching accuracy. \~
  \param[out] resultSolid - \ru Результирующая оболочка или тело (в зависимости от флага).
                            \en The resultant shell or solid (depends on the flag). \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbeStitchResType) StitchToOneSheetSolid( const RPArray<const MbSolid> & initialSolids, 
                                                    const MbSNameMaker &           operNames,               
                                                          bool                     formSolidBody,
                                                          double                   stitchPrecision,
                                                          MbSolid *&               resultSolid );


//------------------------------------------------------------------------------
/** \brief \ru Определение оси токарного сечения и построение кривых сечения для тела.
           \en Search for lathe axis and construction of lathe elements for the solid. \~
  \details \ru Функция выполняет поиск токарной оси граней вращения и строит токарное сечение в некоторой плоскости. \n 
           \en The function searches for lathe axis of rotation faces and builds the curves of lathe-section in a plane. \n \~
  \param[in]  solid    - \ru Тело. \en Solid. \~ 
  \param[in]  axis     - \ru Ось токарного сечения может быть нуль). \en Lathe axis, may be null. \~ 
  \param[in]  angle    - \ru Угол, управляющий построением перпендикулярных оси сечения отрезками, рекомендуется M_PI_4-M_PI. \en The angle, managing the construction of segments which perpendicular to the axis, recomended M_PI_4-M_PI. \~ 
  \param[out] position - \ru Плоскость, в плоскости XY которой лежат кривые сечения, а ось X является осью токарного сечения. \en Plane position of section, axis X is a axis of section. \~  
  \param[out] curves   - \ru Кривые токарного сечения располагаются в плоскости XY position. \en The curves of section located on plane XY of position. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) LatheCurves( const MbSolid &          solid, 
                                      const MbAxis3D *         axis,
                                            double             angle, 
                                            MbPlacement3D &    position,
                                            RPArray<MbCurve> & curves );


//------------------------------------------------------------------------------
/** \brief \ru Построение следа кривой при её вращении вокруг оси токарного сечения.
           \en Building of curves for lathe section for given curve. \~
  \details \ru Функция выполняет построение следа ребра в плоскости XY локальной системы координат при его вращении вокруг оси X. \n 
           \en The function builds the generatrix track in the XY plane of the local coordinate system as it rotates around the axis X. \n \~
  \param[in]  generatrix - \ru Кривая. \en Curve \~ 
  \param[in]  position   - \ru Плоскость, ось X которой является осью токарного сечения. \en Plane position of section, axis X is a axis of section. \~  
  \param[out] curves     - \ru Контейр кривых, в который будет добавлен след в плоскости XY position от вращения кривой generatrix вокруг оси X. \en The curve on plane XY of position will be added to contaner curves. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC (MbResultType) LatheCurve( const MbCurve3D &        generatrix, 
                                     const MbPlacement3D &    position,
                                           RPArray<MbCurve> & curves ); 


//------------------------------------------------------------------------------
/** \brief \ru Построить срединную оболочку по граням тела, основанным на
  эквидистантных поверхностях.
  \en Create a median shell by solid faces, based on equidistant
  surfaces. \~
  \details \ru Построить срединную оболочку по парам граней тела, основанным на
  эквидистантных поверхностях. Пары граней либо выбираются пользователем,
  либо находятся автоматически по заданному расстоянию между гранями.
  Грани должны принадлежать одному и тому же телу.\n
  \en Construct a median shell between pair of faces, based on equidistant
  surfaces. Pair of faces are selected by user or are found by given distance
  between faces. The faces must belong to the same body. \n \~
  \param[in] solid -     \ru Исходное тело.
  \en The initial solid. \~
  \param[in] sameShell - \ru Режим копирования тела.
  \en Whether to copy the solid. \~
  \param[in] faceIndexes - \ru Выбранные пары граней.
  \en Selected face pairs. \~
  \param[in] params - \ru Параметры операции.
  \en The operation parameters. \~
  \param[in] operNames - \ru Именователь.
  \en An object for naming the new objects. \~
  \param[out] result - \ru Результирующая оболочка.
  \en The required shell. \~
  \return \ru Возвращает код результата операции.
  \en Returns operation result code. \~
  \return \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Shell_Modeling
*/
// ---
MATH_FUNC( MbResultType ) MedianShell(       MbSolid &                 solid,
                                             MbeCopyMode               sameShell,
                                       const c3d::IndicesPairsVector & faceIndexes,
                                       const MedianShellValues &       params,
                                       const MbSNameMaker &            operNames,
                                             MbSolid *&                result );


//------------------------------------------------------------------------------
/** \brief \ru Построение развёртки грани на плоскость.
           \en Construction of a face sweep on a plane. \~
  \details \ru Построение развёртки грани на плоскость.\n
           \en Construction of a face sweep on a plane.\n \~
  \param[in] face -     \ru Исходная грань.
                        \en The initial face. \~
  \param[in] values -   \ru Параметры построения: локальная система координат развернутой поверхности грани, данные для вычисления шага при триангуляции, коэффициент Пуассона материала грани.
                        \en The parameters: Local coordinate system for result surface, Data for step calculation during triangulation, the Poisson's ratio of face material. \~
  \param[out] result -  \ru Тело - плоская развертка исходной грани.
                        \en The built solid unbend face on plane. \~
  \result \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \warning \ru В разработке.
           \en Under development. \~
  \ingroup Surface_Modeling
*/
// ---
MATH_FUNC (MbResultType) RectifyFace( const MbFace &      face, 
                                      const RectifyValues values,
                                            MbSolid *&    result );


//------------------------------------------------------------------------------
/** \brief \ru Создать решетчатую оболочку.
           \en Create a lattice shell. \~
  \details \ru Создать решетчатую оболочку по трем управляющим точкам, параметрам решетки и количеству элементов. \n
           \en Create a lattice shell on the three control points of the lattice parameters and the number of elements. \~
  \param[in] point0  - \ru Точка, определяющая начало локальной системы координат поверхности.
                       \en The origin of the surface local coordinate system. \~
  \param[in] point1  - \ru Точка, определяющая направление оси X локальной системы и размер элемента.
                       \en A point specifying the direction of X-axis of the local system and the size of element. \~
  \param[in] point2  - \ru Точка, определяющая направление оси Y локальной системы.
                       \en A point specifying the direction of Y-axis of the local system. \~
  \param[in] xRadius - \ru Шаг вдоль первой оси локальной системы координат.
                       \en The step along the first axis of the local coordinate system. \~
  \param[in] yRadius - \ru Шаг вдоль второй оси локальной системы координат.
                       \en The step along the second axis of the local coordinate system. \~
  \param[in] zRadius - \ru Шаг вдоль третьей оси локальной системы координат.
                       \en The step along the third axis of the local coordinate system. \~
  \param[in] xCount  - \ru Количество ячеек вдоль первой оси локальной системы координат.
                       \en The number of cells along a first axis of the local coordinate system. \~
  \param[in] yCount  - \ru Количество ячеек вдоль второй оси локальной системы координат.
                       \en The number of cells along a second axis of the local coordinate system. \~
  \param[in] zCount  - \ru Количество ячеек вдоль третьей оси локальной системы координат.
                       \en The number of cells along a third axis of the local coordinate system. \~
  \param[out] result - \ru Построенная тело.
                       \en The constructed solid. \~
  \result \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Surface_Modeling
*/
// ---
MATH_FUNC (MbResultType) OctaLattice( const MbCartPoint3D & point_0, 
                                      const MbCartPoint3D & point_1, 
                                      const MbCartPoint3D & point_2, 
                                            double          xRadius, 
                                            double          yRadius, 
                                            double          zRadius,
                                            size_t          xCount, 
                                            size_t          yCount, 
                                            size_t          zCount, 
                                      const MbSNameMaker &  names,
                                            MbSolid *&      result );


#endif // __ACTION_SHELL_H
