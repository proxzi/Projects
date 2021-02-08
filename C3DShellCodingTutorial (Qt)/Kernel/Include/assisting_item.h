////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Вспомогательный объект геометрической модели.
         \en Assisting item of the geometric model. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ASSISTING_ITEM_H
#define __ASSISTING_ITEM_H


#include <space_item.h>
#include <model_item.h>
#include <mb_placement3d.h>
#include <math_define.h>


class  MATH_CLASS  MbCube;
class  MATH_CLASS  MbProperties;
class  MATH_CLASS  MbMesh;


//------------------------------------------------------------------------------
/** \brief \ru Вспомогательный объект геометрической модели.
           \en Assisting item of the geometric model. \~
  \details \ru Вспомогательный объект позволяет использовать в геометрической модели такие объекты, 
    как локальная система координат, ось, матрица преобразования для позиционирования других объектов.\n
           \en The assisting item allows to use such an objects in a geometric model 
    as a local coordinate system, axis, transformation matrix for the other objects location.\n \~
  \ingroup Model_Items
*/
// ---
class MATH_CLASS MbAssistingItem : public MbItem {
protected :
  MbPlacement3D place; ///< \ru Локальная система координат. \en Local coordinate system. 

protected :
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  explicit MbAssistingItem( const MbAssistingItem &, MbRegDuplicate * );
public :
  /// \ru Конструктор по локальной системе координат. \en Constructor by a local coordinate system. 
  MbAssistingItem( const MbPlacement3D & );
public :
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbAssistingItem();

public :
  VISITING_CLASS( MbAssistingItem ); 

  // \ru Общие функции геометрического объекта. \en Common functions of a geometric object.  
  virtual MbeSpaceType  IsA()  const; // \ru Тип объекта. \en An object type. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Создать копию. \en Create a copy. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать согласно матрице. \en Transform according to the matrix.  
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвинуть вдоль вектора. \en Move along a vector. 
  virtual void    Rotate   ( const MbAxis3D   &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate about an axis. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными? \en Whether the objects are equal? 
  virtual bool    IsSimilar( const MbSpaceItem & init ) const; // \ru Являются ли объекты подобными? \en Whether the objects are similar? 
  virtual bool    SetEqual ( const MbSpaceItem & init );   // \ru Сделать объекты равным. \en Make the objects equal. 
  virtual double  DistanceToPoint ( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate distance to point. 
  virtual void    AddYourGabaritTo( MbCube & r ) const; // \ru Добавь свой габарит в куб. \en Add own bounding box to the bounding box. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D & into, MbCube & cube ) const; // \ru Рассчитать габарит в локальной системы координат. \en Calculate the bounding box in a local coordinate system. 
  virtual void    CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; // \ru Построить полигональную копию mesh. \en Build polygonal copy mesh.

  virtual MbProperty & CreateProperty( MbePrompt name ) const; // \ru Создать собственное свойство. \en Create own property. 
  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Установить свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  /// \ru Получить систему координат объекта. \en Get the coordinate system of an item. 
  virtual bool    GetPlacement( MbPlacement3D & ) const; 
  /// \ru Установить систему координат объекта. \en Set the coordinate system of an item. 
  virtual bool    SetPlacement( const MbPlacement3D & p );

  // \ru Создать полигональный объект - упрощенную копию данного объекта. \en Create a polygonal object - a simplified copy of the given object. 
  virtual MbItem * CreateMesh( const MbStepData & stepData, const MbFormNote & note, MbRegDuplicate * iReg ) const; 

  /// \ru Дать матрицу преобразования из локальной системы объекта. \en Get transform matrix from local coordinate system of object.
  virtual bool    GetMatrixFrom( MbMatrix3D & from ) const;
  /// \ru Дать матрицу преобразования в  локальную систему объекта. \en Get transform matrix into local coordinate system of object.
  virtual bool    GetMatrixInto( MbMatrix3D & into ) const;

  /** \ru \name Функции вспомогательного объекта.
      \en \name Functions of assisting item.
      \{ */
          /// \ru Выдать систему координат объекта. \en Get the coordinate system of an item. 
  const   MbPlacement3D & GetPlacement() const { return place; }
          /// \ru Выдать систему координат объекта для редактирования. \en Get the coordinate system of an item for editing. 
          MbPlacement3D & SetPlacement()       { return place; } 
  /** \} */

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbAssistingItem ) 
OBVIOUS_PRIVATE_COPY( MbAssistingItem )
};

IMPL_PERSISTENT_OPS( MbAssistingItem )

#endif // __ASSISTING_ITEM_H
