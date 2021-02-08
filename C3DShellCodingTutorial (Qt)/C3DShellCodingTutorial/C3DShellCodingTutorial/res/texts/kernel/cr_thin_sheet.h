﻿////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение оболочки по поверхности.
         \en Construction of a shell from a surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_THIN_SHEET_H
#define __CR_THIN_SHEET_H


#include <creator.h>
#include <op_swept_parameter.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки по поверхности.
           \en Constructor of a shell from a surface. \~
  \details \ru Строитель создаёт оболочку по заданной поверхности приданием ей толщины. \n
           \en The constructor creates a shell from a given surface by supplying it with a thickness. \n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbThinShellCreator : public MbCreator {
protected :
  MbSurface * surface;    ///< \ru Поверхность. \en Surfaces. 
  bool        sameSense;  ///< \ru Совпадение нормали основной ргани оболочки и поверхности. \en Coincidence of the normal to the basic face of a shell and the normal to the surface. 
  SweptValues parameters; ///< \ru Параметры построения. \en Construction parameters. 
  SimpleName  name;       ///< \ru Имя операции. \en Operation name. 

public :
  MbThinShellCreator( const MbSurface & surf, bool sense, SweptValues p, 
                      bool same, const MbSNameMaker & n, SimpleName & m );
private :
  MbThinShellCreator( const MbThinShellCreator &, MbRegDuplicate *ireg ); 
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbThinShellCreator( const MbThinShellCreator & ); 
public :
  virtual ~MbThinShellCreator();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 
  virtual void        Transform( const MbMatrix3D &matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D &to, MbRegTransform * = NULL );                 // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D &axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual void        GetProperties( MbProperties &properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties &properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & s );   // \ru Дать базовые объекты \en Get the base objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );       // \ru Сделать равным \en Make equal 

  // \ru Общие функции твердого тела \en Common functions of solid solid 

  virtual bool        CreateShell( MbFaceShell *&shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction 

          // \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       SweptValues & params ) const { params = parameters; }
          // \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const SweptValues & params )       { parameters = params; }

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbThinShellCreator & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbThinShellCreator )
}; // MbThinShellCreator

IMPL_PERSISTENT_OPS( MbThinShellCreator )

//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку по поверхности.
           \en Construct a shell from a surface. \~
  \details \ru Построить оболочку по заданной поверхности приданием ей толщины. \n
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct a shell from a given surface by thickening. \n
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  surface - \ru Исходная поверхность.
                        \en The initial surface. \~
  \param[in]  sense   - \ru Признак совпадения нормали основной ргани оболочки и поверхности.
                        \en Flag of coincidence of the normal to the basic face of the shell and to the surface. \~
  \param[in]  parameters - \ru Параметры построения оболочки.
                           \en The shell construction parameters. \~
  \param[in]  same - \ru Признак не копировать поверхность.
                     \en Not to copy the surface. \~
  \param[in]  operNames - \ru Именователь граней.
                          \en An object for naming faces. \~
  \param[in]  name - \ru Имя операции.
                     \en Operation name. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateThinShell( const MbSurface & surface, 
                                         bool sense, 
                                         const SweptValues & parameters, 
                                         bool same,
                                         const MbSNameMaker & operNames, 
                                         SimpleName & name, 
                                         MbResultType & res, 
                                         MbFaceShell *& shell );


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку по наборам точек.
           \en Construct a shell from point sets. \~
  \details \ru Построить оболочку по заданным наборам точек. По заданным наборам точек строятся кривые, по кривым создаётся 
    поверхность MbLoftedSurface, которой придаётся толщина. 
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct a shell from given point sets. The curves are created from the given sets of points, from these curves the surface 
    MbLoftedSurface with a certain thickness is created. 
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  points - \ru Исходные наборы точек.
                       \en Initial point sets. \~
  \param[in]  operNames - \ru Именователь граней.
                          \en An object for naming faces. \~
  \param[in]  name - \ru Имя операции.
                     \en Operation name. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateLoftedShell( const RPArray< SArray<MbCartPoint3D> > & points, 
                                           const MbSNameMaker & operNames, 
                                           SimpleName & name, 
                                           MbResultType & res, 
                                           MbFaceShell *& shell );


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку по кривым.
           \en Construct a shell from curves. \~
  \details \ru Построить оболочку по заданным кривым. По заданным кривым создаётся 
    поверхность MbLoftedSurface, которой придаётся толщина. 
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct a shell from given curves. A surface MbLoftedSurface is created from the given curves, 
    and it is supplied with a thickness. 
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  curves - \ru Исходные кривые.
                       \en Initial curves. \~
  \param[in]  operNames - \ru Именователь граней.
                          \en An object for naming faces. \~
  \param[in]  name - \ru Имя операции.
                     \en Operation name. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateLoftedShell( const RPArray<MbCurve3D> & curves, 
                                           const MbSNameMaker & operNames, 
                                           SimpleName & name, 
                                           MbResultType & res, 
                                           MbFaceShell *& shell );


#endif // __CR_THIN_SHEET_H
