﻿////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение оболочки в форме заплатки.
         \en Construction of a patch-shaped shell. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_PATCH_CREATOR_H
#define __CR_PATCH_CREATOR_H


#include <templ_rp_array.h>
#include <mb_operation_result.h>
#include <creator.h>
#include <op_shell_parameter.h>


class  MATH_CLASS  MbCurve3D;
class  MATH_CLASS  MbCurveEdge;
class  MATH_CLASS  MbFaceShell;


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки в форме заплатки.
           \en Constructor of a patch-shaped shell. \~
  \details \ru Строитель оболочки в форме заплатки на заданных ребрах или кривых. \n
           \en Constructor of a patch-shaped shell from the given edges or curves. \n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbPatchCreator : public MbCreator {
protected:
  RPArray<MbCurve3D> initCurves;   ///< \ru Кривые, определяющие края заплатки. \en Curves determining the boundaries of a patch. 
  PatchValues        parameters;   ///< \ru Параметры построения заплатки. \en Parameters of patch construction. 
  /// \ru Cледующие данные имеются только, если обрабатываются ребра. \en The following data are defined only when edges are being processed. 
  SArray<bool>       orientations; ///< \ru Ориентация кривых для замыкания в цепь. \en Orientation of curves for enclosing into a chain.  
  SArray<double>     tolerances;   ///< \ru Толерантности стыков кривых для замыкания в цепь. \en Tolerances of joints of curves for enclosing into a chain. 
  SArray<ptrdiff_t>  surfInds;     ///< \ru Номер поверхности кривой пересечения, отвечающей существующей грани. \en Number of surface of the intersection curve corresponding to the existent face. 

private :
  MbPatchCreator( const MbPatchCreator &, MbRegDuplicate * ireg );

public :
  MbPatchCreator( const RPArray<MbCurve3D>  & curves,
                  const PatchValues         & params,
                  const MbSNameMaker        & n,
                  const SArray<ptrdiff_t>   * surfInds,
                  const SArray<bool>        * orientations,
                  const SArray<double>      * tolerances );
  virtual ~MbPatchCreator();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );             
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL );             
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL );

  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems( RPArray<MbSpaceItem> & );  // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const;      
  virtual bool        SetEqual ( const MbCreator & );      

  // \ru Построение оболочки по исходным данным \en Construction of a shell from the given data 
  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); 

          // \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       PatchValues & params ) const { params = parameters; }
          // \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const PatchValues & params )       { parameters = params; }

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbPatchCreator )
OBVIOUS_PRIVATE_COPY( MbPatchCreator )
};

IMPL_PERSISTENT_OPS( MbPatchCreator )

//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку в форме заплатки.
           \en Construct a patch-shaped shell. \~
  \details \ru Построить оболочку в форме заплатки на заданных кривых.
           \en Construct a patch-shaped shell from the given curves. \~
  \param[in]  initEdges - \ru Кривые, определяющие края заплатки.
                          \en Curves determining the bounds of the patch. \~
  \param[in]  parameters - \ru Параметры операции.
                           \en The operation parameters. \~
  \param[in]  operNames - \ru Именователь.
                          \en An object for naming the new objects. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \result \ru Возвращает построенную оболочку.
          \en Returns the constructed shell. \~
  \ingroup Model_Creators
*/
// ---
MbFaceShell * CreatePatchShell( const RPArray<MbCurve3D> & initCurves,
                                const PatchValues &        parameters,
                                const MbSNameMaker &       operNames,
                                MbResultType &             res );


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку в форме заплатки.
           \en Construct a patch-shaped shell. \~
  \details \ru Построить оболочку в форме заплатки на заданных ребрах.
    Одновременно с построением оболочки функция создает её строитель.\n
           \en Construct a patch-shaped shell from the given edges.
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  initEdges - \ru Рёбра, определяющие края заплатки.
                          \en Edges determining the bounds of the patch. \~
  \param[in]  parameters - \ru Параметры операции.
                           \en The operation parameters. \~
  \param[in]  operNames - \ru Именователь.
                          \en An object for naming the new objects. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreatePatchSet( const RPArray<MbPatchCurve> & initEdges, 
                                        const PatchValues           & parameters, 
                                        const MbSNameMaker          & operNames, 
                                        MbResultType                & res,
                                        MbFaceShell                *& shell ); 


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку в форме заплатки.
           \en Construct a patch-shaped shell. \~
  \details \ru Построить оболочку в форме заплатки на заданных кривых.
    Одновременно с построением оболочки функция создает её строитель.\n
           \en Construct a patch-shaped shell from the given curves.
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  initEdges - \ru Кривые, определяющие края заплатки.
                          \en Curves determining the bounds of the patch. \~
  \param[in]  parameters - \ru Параметры построения.
                           \en Parameters of shell creation. \~
  \param[in]  operNames - \ru Именователь граней.
                          \en An object for naming faces. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *)CreatePatchSet( const RPArray<MbCurve3D> & initCurves, 
                                       const PatchValues        & parameters, 
                                       const MbSNameMaker       & operNames, 
                                       MbResultType             & res,
                                       MbFaceShell             *& shell );


#endif // __CR_PATCH_CREATOR_H
