////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Геометрический атрибут.
         \en Geometric attribute. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_GEOMETRIC_ATTRIBUTE_H
#define __ATTR_GEOMETRIC_ATTRIBUTE_H


#include <attr_common_attribut.h>
#include <attr_registry.h>
#include <math_define.h>
#include <creator.h>


class  MATH_CLASS MbSpaceItem;
class  MATH_CLASS MbProperty;
class  MATH_CLASS MbProperties;
class             MbRegTransform;
class             MbRegDuplicate;


//------------------------------------------------------------------------------
/** \brief \ru Геометрический атрибут.
           \en Geometric attribute. \~
  \details \ru Геометрический атрибут. \n
           \en Geometric attribute. \n \~
  \ingroup Model_Attributes
 */
class MATH_CLASS MbGeomAttribute : public MbCommonAttribute {
protected :
  MbSpaceItem *  spaceItem; ///< \ru Геометрический объект. \en A geometric object. 
  MbeCreatorType type;      ///< \ru Тип операции. \en Operation type. 
  bool           keepItem;  ///< \ru Сохранять исходный объект при копировании. \en Save the initial object when copying. 

private:
  // \ru Конструктор копирования. \en Copy constructor. 
  MbGeomAttribute( const MbGeomAttribute & init, MbRegDuplicate * iReg );
public :
  /// \ru Конструктор. \en Constructor. 
  MbGeomAttribute( const MbSpaceItem & item, MbeCreatorType t, bool keepItem ); 
  /// \ru Конструктор. \en Constructor. 
  MbGeomAttribute( const MbSpaceItem & item, MbeCreatorType t, bool keepItem, const c3d::string_t & itemPrompt ); 
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbGeomAttribute();

public:
  // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbeAttributeType AttributeType() const;
  // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; 
  // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const;
  // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual bool    Init( const MbAttribute & ); 
  // \ru Выполнить действия при трансформировании владельца. \en Perform actions when transforming the owner. 
  virtual void    OnTransformOwner( const MbAttributeContainer & owner, const MbMatrix3D & matr, MbRegTransform * iReg ); 
  // \ru Выполнить действия при перемещении владельца. \en Perform actions when moving the owner. 
  virtual void    OnMoveOwner( const MbAttributeContainer & owner, const MbVector3D & to, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при вращении владельца. \en Perform actions when rotating the owner. 
  virtual void    OnRotateOwner( const MbAttributeContainer & owner, const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при копировании владельца. \en Perform actions when copying the owner. 
  virtual void    OnCopyOwner( const MbAttributeContainer & owner, MbAttributeContainer & other, MbRegDuplicate * iReg ); 
  // \ru Выполнить действия при объединении владельца. \en Perform actions when merging the owner. 
  virtual void    OnMergeOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 

  virtual void    GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 
          /// \ru Дать геометрический объект. \en Get geometric object. 
  const   MbSpaceItem * GetSpaceItem() const { return spaceItem; } 
          MbSpaceItem * SetSpaceItem() { return spaceItem; } 
          /// \ru Заменить геометрический объект. \en Replace geometric object. 
          void    ChangeSpaceItem( MbSpaceItem & init );
          /// \ru Дать тип операции. \en Get operation type. 
          MbeCreatorType GetOperationType() const { return type; }

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbGeomAttribute ) 
OBVIOUS_PRIVATE_COPY( MbGeomAttribute )
}; 

IMPL_PERSISTENT_OPS( MbGeomAttribute )

#endif // __ATTR_GEOMETRIC_ATTRIBUTE_H
