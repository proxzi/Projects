﻿////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель блока из nurbs-поверхностей.
         \en Constructor of a block from NURBS-surfaces.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_NURBS_BLOCK_SOLID_H
#define __CR_NURBS_BLOCK_SOLID_H


#include <creator.h>
#include <op_shell_parameter.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки в форме блока.
           \en Constructor of a shell in the form of block. \~
  \details \ru Строитель оболочки в форме блока, имеющего шесть четырёхугольных граней на базе Nurbs-поверхностей. \n
           \en Constructor of a shell in the form of a block with six quadrangular faces on the base of NURBS-surfaces. \n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbNurbsBlockSolid : public MbCreator {
protected: 
  RPArray<MbSurface> surfaces; ///< \ru Множество поверхностей граней nurbs-блока. \en A set of surfaces of NURBS-block faces. 
  bool               out;      ///< \ru Направление нормалей граней (out = true - нормали направлены наружу блока). \en The faces normals direction (out = true - normals are directed outside the block). 
  SimpleName         name;     ///< \ru Имя объекта. \en A name of an object. 

public: // \ru Конструктор по параметрам \en Constructor by parameters 
  MbNurbsBlockSolid( RPArray<MbSurface> & surf, bool bOutDir, const MbSNameMaker & names, SimpleName name );
private: // \ru Конструктор дублирующий \en Duplication constructor 
  MbNurbsBlockSolid( const MbNurbsBlockSolid &, MbRegDuplicate *ireg );
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbNurbsBlockSolid( const MbNurbsBlockSolid & );
public: // \ru Деструктор \en Destructor 
  virtual ~MbNurbsBlockSolid();

public: // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 
  virtual bool        IsSame( const MbCreator & other, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  virtual bool        SetEqual ( const MbCreator & ); // \ru Сделать равным \en Make equal 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать по матрице \en Transform according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг по вектору \en Translation by a vector 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & s ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

public: 
  /// \ru Построение оболочки \en Creation of a shell 
  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL );
  virtual void        Refresh( MbFaceShell & outer ); ///< \ru Обновить форму оболочки \en Update shape of the shell 

private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbNurbsBlockSolid & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbNurbsBlockSolid )
};

IMPL_PERSISTENT_OPS( MbNurbsBlockSolid )

//------------------------------------------------------------------------------
/** \brief \ru Построить модифицированную оболочку.
           \en Construct the modified shell. \~
  \details \ru Построить оболочку в форме блока, имеющего шесть четырёхугольных граней на базе Nurbs-поверхностей. 
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Create a shell in the form of a block with six quadrangular faces on the base of NURBS-surfaces. 
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  place      - \ru Локальная система координат, вдоль осей которой будут стороиться ребра оболочки.
                           \en The local coordinate system along axes of which the shell's edges will be constructed. \~
  \param[in]  ax         - \ru Размер блока вдоль первой оси локальной системы координат.
                           \en The block size along the first axis of the local coordinate system. \~
  \param[in]  ay         - \ru Размер блока вдоль второй оси локальной системы координат.
                           \en The block size along the second axis of the local coordinate system. \~
  \param[in]  az         - \ru Размер блока вдоль третьей оси локальной системы координат.
                           \en The block size along the third axis of the local coordinate system. \~
  \param[in]  out        - \ru Направление нормалей граней (out = true - нормали наравлены наружу блока).
                           \en The faces normals direction (out = true - the normals are directed outside the block). \~
  \param[in]  names      - \ru Именователь операции.
                           \en An object defining names generation in the operation. \~
  \param[in]  name       - \ru Имя объекта.
                           \en A name of an object. \~
  \param[out] parameters - \ru Параметры построения оболочки.
                           \en The shell construction parameters. \~
  \param[out] shell      - \ru Построенная оболочка.
                           \en The resultant shell. \~  
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateNurbsBlock( const MbPlacement3D & place,
                                          double ax, double ay, double az, 
                                          bool out,
                                          const MbSNameMaker & names, 
                                          SimpleName name,
                                          NurbsBlockValues & parameters,
                                          MbFaceShell *& shell );


#endif // __CR_NURBS_BLOCK_SOLID_H
