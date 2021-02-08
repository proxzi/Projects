////////////////////////////////////////////////////////////////////////////////
//
//  Создание оболочки из нурбс-поверхностей
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __NURBS_SURFACES_SHELL_H
#define __NURBS_SURFACES_SHELL_H

#include <templ_rp_array.h>
#include <math_define.h>
#include <mb_operation_result.h>


class  MATH_CLASS MbCreator;
class  MATH_CLASS MbSNameMaker;
class  MATH_CLASS MbFaceShell;
struct            NurbsSurfaceValues;
class             IProgressIndicator;


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку из NURBS-поверхностей.
           \en Construct a shell from NURBS-surfaces. \~
  \details \ru Построить оболочку из NURBS-поверхностей MbSplineSurface по заданному множеству точек условно расположенных в узлах четырехугольной сетки. \n
           \en Construct a shell from NURBS-surfaces MbSplineSurface by a given set of points conventionally located at the nodes of a quadrangle grid. \n \~ 
  \param[in]  parameters - \ru Параметры построения.
                           \en Parameters of a shell creation. \~
  \param[in]  operNames - \ru Именователь граней.
                          \en An object for naming faces. \~
  \param[in]  isPhantom - \ru Режим создания фантома.
                          \en Create in the phantom mode. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \param[out] indicator - \ru Индикатор хода построения позволяющий прервать построение.
                          \en Construction process indicator which allow to interrupt the construction. \~
  \result \ru Возвращает оболочку.
          \en Returns the constructуed shell. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbFaceShell *) CreateNurbsSurfacesShell( NurbsSurfaceValues & params,
                                                    const MbSNameMaker & operNames, 
                                                    bool isPhantom,
                                                    MbResultType & res,
                                                    IProgressIndicator * = NULL );


//------------------------------------------------------------------------------
// проверить оболочку из нурбс-поверхностей
/** \brief \ru Построить оболочку из NURBS-поверхностей.
           \en Construct a shell from NURBS-surfaces. \~
  \details \ru Построить оболочку из NURBS-поверхностей MbSplineSurface по заданному множеству точек условно расположенных в узлах четырехугольной сетки. \n
           \en Construct a shell from NURBS-surfaces MbSplineSurface by a given set of points conventionally located at the nodes of a quadrangle grid. \n \~ 
  \param[in]  parameters - \ru Параметры построения.
                           \en Parameters of a shell creation. \~
  \param[in]  shell - \ru Оболочка, построенная по заданным параметрам.
                      \en The shell constructed by given parameters. \~
  \param[out] indicator - \ru Индикатор хода построения позволяющий прервать построение.
                          \en Construction process indicator which allow to interrupt the construction. \~
  \result \ru Возвращает код результата операции.
          \en Returns operation result code. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbResultType) CheckNurbsSurfacesShell( const NurbsSurfaceValues & params,
                                                  const MbFaceShell & shell,
                                                  IProgressIndicator * = NULL );


#endif // __NURBS_SURFACES_SHELL_H
