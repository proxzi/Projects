////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Идентификатор объекта.
         \en Object identifier. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_IDENTIFIER_H
#define __ATTR_IDENTIFIER_H


#include <attr_elementary_attribut.h>
#include <name_item.h>


//------------------------------------------------------------------------------
/** \brief \ru Идентификатор объекта.
           \en Object identifier. \~
  \details \ru Идентификатор объекта. \n
           \en Object identifier. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbIdentifier : public MbElementaryAttribute {
protected :
  int32 identifier; ///< \ru Идентификатор объекта. \en Object identifier. 

protected :
  /// \ru Конструктор. \en Constructor. 
  MbIdentifier( const MbIdentifier & ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbIdentifier( int32 init );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbIdentifier();

  // \ru Общие функции объекта. \en Common functions of object. 

  virtual MbeAttributeType  AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool      IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool      Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual void      GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t    SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

  // \ru Специфические свойства объекта. \en Specific functions of object.

  /// \ru Установить идентификатор. \en Set identifier. 
          void      Init( int32 init ) { identifier = init; }
  /// \ru Дать идентификатор объекта. \en Get identifier of object. 
          int32     Identifier() const { return identifier; }

private:
  MbIdentifier & operator = ( const MbIdentifier & );

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbIdentifier ) 
}; // MbIdentifier

IMPL_PERSISTENT_OPS( MbIdentifier )


//------------------------------------------------------------------------------
/** \brief \ru Топологическое имя.
           \en Topological name. \~
  \details \ru Топологическое имя. \n
           \en Topological name. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbNameAttribute : public MbElementaryAttribute {
  typedef std::vector<MbNameAttribute *> NameAttributesVector;
protected :
  MbName                tName;       ///< \ru Топологическое имя объекта. \en A name of a topological object 
private:
  NameAttributesVector  parentNames; ///< \ru Топологические имена родителей объекта. \en Topological names of object parents. 
  mutable bool          isTemporal;  ///< \ru Атрибут временный, на время операции (Этот признак не пишется и не читается). \en Attribute is temporary, for the duration of the operation only (This tag is not read or written). 

protected :
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbNameAttribute( const MbNameAttribute & ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbNameAttribute( bool isTemporal = false ); 
  /// \ru Конструктор. \en Constructor. 
  MbNameAttribute( const MbName &, bool isTemporal = false );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbNameAttribute();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

  // \ru Выполнить действия при объединении владельца. \en Perform actions when merging the owner. 
  virtual void    OnMergeOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 

          /// \ru Выдать имя. \en Get name. 
  const   MbName &  GetName() const { return tName; }
          /// \ru Выдать имя. \en Get name. 
          MbName &  SetName()       { return tName; }
          /// \ru Установить имя. \en Set name. 
          void      SetName( const MbName &, bool deleteParentNames = true );

          /// \ru Определить, есть ли хоть одно имя родительского объекта. \en Determine whether at least one name of parent object exists. 
          bool      IsAnyParentName() const { return (parentNames.size() > 0); }
          /// \ru Выдать количество родительских имен первого уровня. \en Get the number of parent names of the first level. 
          size_t    GetParentNamesCount() const { return parentNames.size(); }
          /// \ru Удалить имена родительских объектов. \en Delete names of parent objects. 
          void      DeleteParentNames();
          /// \ru Добавить имя родительского объекта. \en Add a name of parent object. 
          bool      AddParentName( const MbName &, bool isTemporal = false );
          /// \ru Добавить имена родительских объектов. \en Add names of parent objects. 
          bool      AddParentNames( const MbNameAttribute &, double accuracy );
          /// \ru Получить имена родительских объектов. \en Get names of parent objects. 
          void      GetParentNames( std::vector<const MbName *> & ) const;
          ///< \ru Является ли атрибут временным. \en Whether this attribute is temporary. 
          bool      IsTemporal() const { return isTemporal; }

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
  MbNameAttribute & operator = ( const MbNameAttribute & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbNameAttribute ) 
}; 

IMPL_PERSISTENT_OPS( MbNameAttribute )

//------------------------------------------------------------------------------
/** \brief \ru Метка времени обновления.
           \en Stamp of update time. \~
  \details \ru Метка времени обновления. \n
           \en Stamp of update time. \n \~
  \ingroup Model_Attributes
*/
class MATH_CLASS MbUpdateStamp : public MbElementaryAttribute 
{
protected :
  uint32 updStamp; ///< \ru Значение метки. \en The value of stamp. 

protected :
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbUpdateStamp( const MbUpdateStamp & ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbUpdateStamp();
  /// \ru Конструктор. \en Constructor. 
  MbUpdateStamp( uint32 stampVal ); 
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbUpdateStamp();

  // \ru Общие функции объекта \en Common functions of object 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Сбросить значение метки времени обновления. \en Reset a value of a stamp of update time. 
          void    ResetStamp()             { updStamp = 0; }
          /// \ru Проверить, равно ли значение метки нулю. \en Check whether the value of a stamp is null. 
          bool    IsNull    () const       { return updStamp == 0; }
          /// \ru Дать значение метки времени обновления. \en Get the value of a stamp of update time. 
          uint32  GetStamp  () const       { return updStamp; }

          /// \ru Увеличить значение метки на единицу. \en Increase the value of stamp by one. 
          void    Increment ()             { updStamp++; }
          /// \ru Установить значение метки максимальным из присланного и действующего. \en Set the value of stamp to the maximum from the given value and the current value. 
          void    Maximize  ( uint32 val ) { if (val > updStamp) updStamp = val; }


  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
  MbUpdateStamp & operator = ( const MbUpdateStamp & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbUpdateStamp ) 
}; 

IMPL_PERSISTENT_OPS( MbUpdateStamp )

//------------------------------------------------------------------------------
/** \brief \ru Атрибут "якорь".
           \en Attribute "anchor". \~
  \details \ru Атрибут "якорь". \n
           \en Attribute "anchor". \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbAnchorAttribute : public MbAttribute {
public:
  enum AnchorType {
    ant_Undefined = 0,  ///< \ru Неопределенный тип. \en An undefined type. 
    ant_TopoName,       ///< \ru Для топологического имени. \en For a topological name. 
  };

protected :
  uint8 aType; ///< \ru Тип якорного атрибута. \en Type of an anchor attribute. 

protected :
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbAnchorAttribute( const MbAnchorAttribute & ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbAnchorAttribute(); 
  /// \ru Конструктор. \en Constructor. 
  MbAnchorAttribute( AnchorType type ); 
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbAnchorAttribute();

  // \ru Общие функции объекта. \en Common functions of object. 

  virtual MbeAttributeType AttributeFamily() const; // \ru Дать тип атрибута. \en Get type of an attribute. 
  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Дать тип якорного атрибута. \en Get type of an anchor attribute. 
          AnchorType GetAnchorType() { return static_cast<AnchorType>(aType); }

  // \ru Выполнить действия при изменении владельца, не связанное с другими действиями. \en Perform actions which are not associated with other actions when changing the owner. 
  virtual void    OnChangeOwner( const MbAttributeContainer & owner );  
  // \ru Выполнить действия при конвертации владельца \en Perform actions when converting the owner.  
  virtual void    OnConvertOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  // \ru Выполнить действия при трансформировании владельца. \en Perform actions when transforming the owner. 
  virtual void    OnTransformOwner( const MbAttributeContainer & owner, const MbMatrix3D & matr, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при перемещении владельца. \en Perform actions when moving the owner. 
  virtual void    OnMoveOwner( const MbAttributeContainer & owner, const MbVector3D & to, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при вращении владельца. \en Perform actions when rotating the owner. 
  virtual void    OnRotateOwner( const MbAttributeContainer & owner, const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при копировании владельца. \en Perform actions when copying the owner. 
  virtual void    OnCopyOwner( const MbAttributeContainer & owner, MbAttributeContainer & other, MbRegDuplicate * iReg = NULL ); 
  // \ru Выполнить действия при объединении владельца. \en Perform actions when merging the owner. 
  virtual void    OnMergeOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  // \ru Выполнить действия при замене владельца. \en Perform actions when replacing the owner. 
  virtual void    OnReplaceOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 
  // \ru Выполнить действия при разделении владельца. \en Perform actions when splitting the owner. 
  virtual void    OnSplitOwner( const MbAttributeContainer & owner, const std::vector<MbAttributeContainer*> & others ); 
  // \ru Выполнить действия при удалении владельца. \en Perform actions when deleting the owner. 
  virtual void    OnDeleteOwner( const MbAttributeContainer & owner ); 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
  MbAnchorAttribute & operator = ( const MbAnchorAttribute & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbAnchorAttribute ) 
}; 

IMPL_PERSISTENT_OPS( MbAnchorAttribute )

//------------------------------------------------------------------------------
/** \brief \ru Признак исполнения (варианта реализации модели).
           \en Indication of embodiment (variant of model implementation). \~
  \details \ru Признак исполнения (варианта реализации модели). \n
           \en Indication of embodiment (variant of model implementation). \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbEmbodimentAttribute : public MbElementaryAttribute {
protected:
  SimpleName m_name;    ///< \ru Имя исполнения. \en Name of embodiment.
  SimpleName m_parent;  ///< \ru Имя родительского исполнения. \en Name of parent embodiment.
  bool       m_current; ///< \ru Признак, является ли исполнение текущим. \en Flag, whether the embodiment is current.

protected:
  // \ru Конструктор. \en Constructor. 
  MbEmbodimentAttribute( const MbEmbodimentAttribute & );
public:
  // \ru Конструктор. \en Constructor. 
  MbEmbodimentAttribute();
  // \ru Конструктор. \en Constructor. 
  MbEmbodimentAttribute( const SimpleName & name1, const SimpleName & name2, bool curr = false );
  // \ru Деструктор. \en Destructor. 
  virtual ~MbEmbodimentAttribute();

  // \ru Общие функции объекта. \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const;                       // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute &    Duplicate( MbRegDuplicate * = NULL ) const;  // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool             IsSame( const MbAttribute &, double ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool             Init( const MbAttribute & );                 // \ru Инициализировать данные по атрибуту. \en Initialize by attribute. 
  virtual void             GetProperties( MbProperties & );             // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t           SetProperties( const MbProperties & );       // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt        GetPropertyName();                           // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

  // \ru Специфические функции объекта. \en Specific functions of object. 

  // \ru Установить родительское исполнение. \en Set a parent embodiment. 
  void    Init( const SimpleName & name1, const SimpleName & name2, bool curr = false ) {
    m_name = name1; m_parent = name2; m_current = curr; 
  }
  // \ru Выдать имя исполнения. \en Get a name of embodiment. 
  SimpleName  Name() const { return m_name; }
  // \ru Выдать имя родительского исполнения. \en Get a name of parent embodiment. 
  SimpleName  ParentName() const { return m_parent; }
  // \ru Является ли исполнение текущим. \en Whether the embodiment is current. 
  bool        IsCurrent() const { return m_current; }

private:
  void    operator = ( const MbEmbodimentAttribute & ); // \ru Не реализовано. \en Not implemented.

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbEmbodimentAttribute )

}; // MbEmbodimentAttribute

IMPL_PERSISTENT_OPS( MbEmbodimentAttribute )


#endif // __ATTR_IDENTIFIER_H
