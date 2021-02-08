////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Подтип обобщенные атрибуты.
         \en Common attributes subtype. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_COMMON_ATTRIBUE_H
#define __ATTR_COMMON_ATTRIBUE_H


#include <attribute.h>


//------------------------------------------------------------------------------
/** \brief \ru Обобщенный атрибут - базовый класс.
           \en Common attribute - the base class. \~
  \details \ru Обобщенный атрибут - базовый класс. \n
           \en Common attribute - the base class. \n \~
  \ingroup Model_Attributes
 */
class MATH_CLASS MbCommonAttribute : public MbAttribute {
protected :
  c3d::string_t prompt_;    ///< \ru Строка описания. \en String of description. 
  bool          changeable; ///< \ru Признак редактируемости. \en Attribute of editability. 

protected :
  /// \ru Конструктор. \en Constructor. 
  MbCommonAttribute( const c3d::string_t & prompt, bool change );
  /// \ru Конструктор. \en Constructor. 
  explicit MbCommonAttribute( bool change );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbCommonAttribute();

public :
  virtual MbeAttributeType AttributeFamily() const;    // \ru Выдать тип атрибута. \en Get attribute type. 
  virtual MbeAttributeType AttributeType() const = 0; // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const = 0; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ) = 0; // \ru Инициализировать данные по присланным. \en Initialize data. 

  // \ru Выполнить действия при изменении владельца, не связанное с другими действиями. \en Perform actions which are not associated with other actions when changing the owner. 
  virtual void    OnChangeOwner( const MbAttributeContainer & owner );  
  // \ru Выполнить действия при конвертации владельца. \en Perform actions when converting the owner. 
  virtual void    OnConvertOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  // \ru Выполнить действия при трансформировании владельца. \en Perform actions when transforming the owner. 
  virtual void    OnTransformOwner( const MbAttributeContainer & owner, const MbMatrix3D & matr, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при перемещении владельца. \en Perform actions when moving the owner. 
  virtual void    OnMoveOwner( const MbAttributeContainer & owner, const MbVector3D & to, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при вращении владельца. \en Perform actions when rotating the owner. 
  virtual void    OnRotateOwner( const MbAttributeContainer & owner, const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при копировании владельца. \en Perform actions when copying the owner. 
  virtual void    OnCopyOwner( const MbAttributeContainer & owner, MbAttributeContainer & other, MbRegDuplicate * iReg = NULL ); 
  // \ru Выполнить действия при объединении владельца. \en Perform actions when merging he owner. 
  virtual void    OnMergeOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  // \ru Выполнить действия при замене владельца. \en Perform actions when replacing the owner. 
  virtual void    OnReplaceOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  // \ru Выполнить действия при разделении владельца. \en Perform actions when splitting the owner. 
  virtual void    OnSplitOwner( const MbAttributeContainer & owner, const std::vector<MbAttributeContainer*> & others ); 
  // \ru Выполнить действия при удалении владельца. \en Perform actions when deleting the owner. 
  virtual void    OnDeleteOwner( const MbAttributeContainer & owner ); 

  virtual void    GetCharValue( TCHAR * v ) const = 0; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual void    GetProperties( MbProperties & ) = 0; // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ) = 0; // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

  /** \brief \ru Выдать подсказку атрибута. \en Get a prompt of attribute.
      \details \ru Строковое значение, которое может быть использовано, как совего рода тэг, имя или пометка атрибута.
               \en String value which can be used as some kind of tag, name or label of an attribute.
  */
  const c3d::string_t & GetPrompt() const;
  /// \ru Выдать признак изменяемости. \en Get an attribute of changeability. 
  bool IsChangeable() const;

DECLARE_PERSISTENT_CLASS( MbCommonAttribute ) 
OBVIOUS_PRIVATE_COPY( MbCommonAttribute )
}; 

IMPL_PERSISTENT_OPS( MbCommonAttribute )

//------------------------------------------------------------------------------
/** \brief \ru bool атрибут.
           \en Bool attribute. \~
  \details \ru bool атрибут. \n
           \en Bool attribute. \n \~
  \ingroup Model_Attributes
 */
class MATH_CLASS MbBoolAttribute : public MbCommonAttribute {
private:
  bool value_; ///< \ru Значение. \en The value. 

public:
  /// \ru Конструктор. \en Constructor. 
  explicit MbBoolAttribute( const c3d::string_t & prompt, bool change, bool initValue );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbBoolAttribute();

public:
  virtual MbeAttributeType AttributeType() const; // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual void    GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

          bool    GetValue() const; // \ru Выдать значение свойства. \en Get a value of the property. 
          bool    SetValue( bool val ); // \ru Установить новое значение свойства. \en Set new value of the property. 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbBoolAttribute )
OBVIOUS_PRIVATE_COPY( MbBoolAttribute )
};

IMPL_PERSISTENT_OPS( MbBoolAttribute )

//------------------------------------------------------------------------------
/** \brief \ru int атрибут.
           \en Int attribute. \~
  \details \ru int атрибут. \n
           \en Int attribute. \n \~
  \ingroup Model_Attributes
*/
class MATH_CLASS MbIntAttribute : public MbCommonAttribute {
private:
  int value_; ///< \ru Значение. \en The value. 

public:
  /// \ru Конструктор. \en Constructor. 
  explicit MbIntAttribute( const c3d::string_t & prompt, bool change, int initValue );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbIntAttribute();

public:
  virtual MbeAttributeType AttributeType() const; // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual void    GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

          int     GetValue() const; // \ru Выдать значение свойства. \en Get a value of the property. 
          bool    SetValue( int val ); // \ru Установить новое значение свойства. \en Set new value of the property. 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbIntAttribute ) 
OBVIOUS_PRIVATE_COPY( MbIntAttribute )
};

IMPL_PERSISTENT_OPS( MbIntAttribute )

//------------------------------------------------------------------------------
/** \brief \ru int64 атрибут.
           \en Int64 attribute. \~
  \details \ru int64 атрибут. \n
           \en Int64 attribute. \n \~
  \ingroup Model_Attributes
*/
class MATH_CLASS MbInt64Attribute : public MbCommonAttribute {
private:
  int64 value_; ///< \ru Значение. \en The value. 

public:
  /// \ru Конструктор. \en Constructor. 
  explicit MbInt64Attribute( const c3d::string_t & prompt, bool change, int64 initValue );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbInt64Attribute();

public:
  virtual MbeAttributeType AttributeType() const; // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual void    GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

  int64   GetValue() const; // \ru Выдать значение свойства. \en Get a value of the property. 
  bool    SetValue( int64 val ); // \ru Установить новое значение свойства. \en Set new value of the property. 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbInt64Attribute ) 
OBVIOUS_PRIVATE_COPY( MbInt64Attribute )
};

IMPL_PERSISTENT_OPS( MbInt64Attribute )

//------------------------------------------------------------------------------
/** \brief \ru double атрибут.
           \en Double attribute. \~
  \details \ru double атрибут. \n
           \en Double attribute. \n \~
  \ingroup Model_Attributes
 */
class MATH_CLASS MbDoubleAttribute : public MbCommonAttribute {
private:
  double value_; ///< \ru Значение. \en The value. 

public:
  /// \ru Конструктор. \en Constructor. 
  explicit MbDoubleAttribute( const c3d::string_t & prompt, bool change, double initValue );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbDoubleAttribute();

public:
  virtual MbeAttributeType AttributeType() const; // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual void    GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

          double  GetValue() const; // \ru Выдать значение свойства. \en Get a value of the property. 
          bool    SetValue( double val ); // \ru Установить новое значение свойства. \en Set new value of the property. 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbDoubleAttribute ) 
OBVIOUS_PRIVATE_COPY( MbDoubleAttribute )
};

IMPL_PERSISTENT_OPS( MbDoubleAttribute )

//------------------------------------------------------------------------------
/** \brief \ru String атрибут.
           \en String attribute. \~
  \details \ru String атрибут. \n
           \en String attribute. \n \~
  \ingroup Model_Attributes
 */
class MATH_CLASS MbStringAttribute : public MbCommonAttribute {
private:
  c3d::string_t value_; ///< \ru Значение. \en The value. 

public:
  /// \ru Конструктор. \en Constructor. 
  explicit MbStringAttribute( const c3d::string_t & prompt, bool change, const c3d::string_t & string );

public:
  virtual MbeAttributeType AttributeType() const; // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual void    GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

  c3d::string_t GetValue() const; // \ru Выдать значение свойства. \en Get a value of the property. 
  bool          SetValue( c3d::string_t & val ); // \ru Установить новое значение свойства. \en Set new value of the property. 

protected:
  virtual ~MbStringAttribute();  // Use AddRef/Release or smart pointer SPtr<MbAttribute> to destruct it correctly.

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbStringAttribute ) 
OBVIOUS_PRIVATE_COPY( MbStringAttribute )
};

IMPL_PERSISTENT_OPS( MbStringAttribute )

//------------------------------------------------------------------------------
/** \brief \ru Бинарный атрибут.
    \en Binary attribute. \~
  \details \ru Бинарный атрибут. \n
           \en Binary attribute. \n \~
  \ingroup Model_Attributes
*/
class MATH_CLASS MbBinaryAttribute : public MbCommonAttribute {
private:
  std::vector<unsigned char> value_; ///< \ru Значение. \en The value. 

public:
  /// \ru Конструктор. \en Constructor. 
  explicit MbBinaryAttribute( const c3d::string_t & prompt, bool change, const std::vector<unsigned char> & value );

public:
  virtual MbeAttributeType AttributeType() const; // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual void    GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

  std::vector<unsigned char> GetValue() const; // \ru Выдать значение свойства. \en Get a value of the property. 
  bool                       SetValue( std::vector<unsigned char> & val ); // \ru Установить новое значение свойства. \en Set new value of the property. 

protected:
  virtual ~MbBinaryAttribute();  // Use AddRef/Release or smart pointer SPtr<MbAttribute> to destruct it correctly.

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbBinaryAttribute ) 
OBVIOUS_PRIVATE_COPY( MbBinaryAttribute )
};

IMPL_PERSISTENT_OPS( MbBinaryAttribute )

#endif // __ATTR_COMMON_ATTRIBUE_H
