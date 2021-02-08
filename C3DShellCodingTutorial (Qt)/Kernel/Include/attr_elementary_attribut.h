////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Подтип элементарные атрибуты.
         \en Elementary attributes subtype. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_ELEMENTARY_ATTRIBUTE_H
#define __ATTR_ELEMENTARY_ATTRIBUTE_H


#include <attribute.h>


//------------------------------------------------------------------------------
/** \brief \ru Элементарный атрибут - базовый класс.
           \en Elementary attribute - the base class. \~
  \details \ru Элементарный атрибут - базовый класс. \n
           \en Elementary attribute - the base class. \n \~
  \ingroup Model_Attributes
 */
class MATH_CLASS MbElementaryAttribute : public MbAttribute {
protected:
  MbElementaryAttribute();
public:
  virtual ~MbElementaryAttribute();

public :
  virtual MbeAttributeType AttributeFamily() const;    // \ru Тип атрибута \en Type of an attribute 
  virtual MbeAttributeType AttributeType() const = 0; // \ru Выдать подтип атрибута \en Get subtype of an attribute.  
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const = 0; // \ru Сделать копию элемента \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const = 0; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ) = 0; // \ru Инициализировать данные по присланным \en Initialize data. 

  // \ru Действия при изменении владельца, не связанное с другими действиями. \en Actions which are not associated with other actions when changing the owner. 
  virtual void    OnChangeOwner( const MbAttributeContainer & owner );
  // \ru Действия при конвертации владельца. \en Actions when converting the owner. 
  virtual void    OnConvertOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  /// \ru Действия при трансформировании владельца. \en Actions when transforming the owner. 
  virtual void    OnTransformOwner( const MbAttributeContainer & owner, const MbMatrix3D & matr, MbRegTransform * iReg = NULL ); 
  // \ru Действия при перемещении владельца. \en Actions when moving the owner. 
  virtual void    OnMoveOwner( const MbAttributeContainer & owner, const MbVector3D & to, MbRegTransform * iReg = NULL ); 
  // \ru Действия при вращении владельца. \en Actions when rotating the owner. 
  virtual void    OnRotateOwner( const MbAttributeContainer & owner, const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL ); 
  // \ru Действия при копировании владельца. \en Actions when copying the owner. 
  virtual void    OnCopyOwner( const MbAttributeContainer & owner, MbAttributeContainer & other, MbRegDuplicate * iReg = NULL ); 
  // \ru Действия при объединении владельца. \en Actions when merging the owner. 
  virtual void    OnMergeOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  // \ru Действия при замене владельца. \en Actions when replacing the owner. 
  virtual void    OnReplaceOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  // \ru Действия при разделении владельца. \en Actions when splitting the owner. 
  virtual void    OnSplitOwner( const MbAttributeContainer & owner, const std::vector<MbAttributeContainer*> & others ); 
  // \ru Действия при удалении владельца. \en Actions when merging the owner. 
  virtual void    OnDeleteOwner( const MbAttributeContainer & owner ); 

  virtual void    GetProperties( MbProperties & ) = 0; // \ru Выдать свойства объекта \en Get properties of the object 
  virtual size_t  SetProperties( const MbProperties & ) = 0; // \ru Установить свойства объекта \en Set properties of object 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 

DECLARE_PERSISTENT_CLASS( MbElementaryAttribute )
OBVIOUS_PRIVATE_COPY( MbElementaryAttribute )
}; 

IMPL_PERSISTENT_OPS( MbElementaryAttribute )

#endif // __ATTR_ELEMENTARY_ATTRIBUTE_H
