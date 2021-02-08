////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поставщик атрибутов для топологических объектов.
         \en Topological objects attributes provider. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_ATTRIBURE_PROVIDER_H
#define __CR_ATTRIBURE_PROVIDER_H


#include <creator.h>
#include <attribute.h>
#include <name_item.h>
#include <topology_faceset.h>


class MATH_CLASS MbNamedAttributeContainer;


//------------------------------------------------------------------------------
/** \brief \ru Поставщик атрибутов для топологических объектов.
           \en Topological objects attributes provider. \~
  \details \ru Поставщик атрибутов для топологических объектов создаёт атрибуты для журнала построений. \n
           \en Topological objects attributes provider creates attributes for history tree. \n \~
  \ingroup Model_Creators
 */
class MATH_CLASS MbAttributeProvider : public MbCreator 
{
private:
  struct NamedAttrCondDuplicator
  {
    public:
      MbAttributeProvider & target_;
      NamedAttrCondDuplicator( MbAttributeProvider & target ) : target_(target) {}
      void operator () ( MbNamedAttributeContainer * source );
    private:
      void operator = ( const NamedAttrCondDuplicator & );
  };

  struct NamedAttrCondComparer 
  {
    public:
      MbName target_;
      NamedAttrCondComparer( const MbName & target ) : target_(target) {}
      bool operator () ( MbNamedAttributeContainer * source );
    private:
      void operator = ( const NamedAttrCondComparer & );
  };

  struct NamedAttrCondSetter 
  {
    public:
      MbFaceShell & target_;
      NamedAttrCondSetter( MbFaceShell & target ) : target_(target) {}
      void operator () ( MbNamedAttributeContainer * source );
    private:
      void operator = ( const NamedAttrCondSetter & );
  };

  typedef std::vector<MbNamedAttributeContainer *>::iterator ContIter;

private:
  std::vector<MbNamedAttributeContainer *> attrConts;  // \ru Передаваемые атрибуты \en Attributes to pass 

public:  
  MbAttributeProvider( const MbSNameMaker & n );
  ~MbAttributeProvider();

  virtual MbeCreatorType  IsA() const; // \ru Выдать тип элемента. \en Get an element type. 
  virtual void        Transform( const MbMatrix3D & matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void        Move( const MbVector3D & to, MbRegTransform * = NULL ); // \ru Сдвинуть вдоль вектора. \en Move along a vector. 
  virtual void        Rotate( const MbAxis3D & axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate about an axis. 
  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Определить, являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual bool        SetEqual( const MbCreator & );       // \ru Сделать равным. \en Make equal. 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию. \en Create a copy. 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction. 

          // \ru Добавить отдельный атрибут (забрать во владение) \en Add a separate attribute. 
          void        AddAttribute( const MbName & name, MbAttribute * attr );
          // \ru Добавить контейнер атрибутов (забрать во владение) \en Add an attribute container. 
          void        AddNamedCont( MbNamedAttributeContainer * attr );
          // \ru Добавить контейнер атрибутов (сделать себе копию) \en Add an attribute container (make a copy). 
          void        AddNamedCont( MbNamedAttributeContainer & attr );

protected:
  MbAttributeProvider( const MbAttributeProvider & );
          void        operator = ( const MbAttributeProvider & ); // \ru Не реализовано \en Not implemented 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbAttributeProvider )
};

IMPL_PERSISTENT_OPS( MbAttributeProvider )


//------------------------------------------------------------------------------
/** \brief \ru Контейнер атрибутов.
           \en Attribute container. \~ 
  \details \ru Контейнер атрибутов для одного топологического объекта. \n
           \en An attribute container for a topological object. \n \~
  \ingroup Model_Attributes
 */
class MATH_CLASS MbNamedAttributeContainer
{
  typedef c3d::AttrVector::iterator AttrIter;

private:
  MbName          target;     // \ru Имя топологического объекта, которому будут отданы хранимые атрибуты. \en Name of the topological object the stored attributes will be passed to. 
  c3d::AttrVector attributes; // \ru Передаваемые атрибуты. \en Attributes to pass. 

public:
  MbNamedAttributeContainer( const MbName & );
  virtual ~MbNamedAttributeContainer();

public:
          /// \ru Записать полученные атрибуты. \en Save the received attributes. 
          void            ReceiveAttributes  ( c3d::AttrVector & attrs );
          /// \ru Скопировать атрибуты. \en Copy attributes. 
          void            DuplicateAttributes( c3d::AttrVector & attrs, MbRegDuplicate * iReg = NULL ) const;
          /// \ru Дать количество атрибутов. \en Get the attributes count. 
          size_t          AttributesCount() const { return attributes.size(); }
          /// \ru Добавить атрибут. \en Add an attribute. 
          void            AddAttribute( MbAttribute & ) ;
  const   MbAttribute *  _GetAttribute( size_t k ) const { return attributes[k]; }

public:
  /// \ru Дать имя топологического объекта. \en Get the topological object name. 
  const   MbName &        GetName() const { return target; }

          /// \ru Читать из потока. \en Read from stream. 
          void            ReadAttrCont ( reader & );
          /// \ru Записать в поток. \en Write to stream. 
          void            WriteAttrCont( writer & ) const;

  virtual void            GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void            SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of the object. 

protected:
  MbNamedAttributeContainer( const MbNamedAttributeContainer & );
          void            operator = ( const MbNamedAttributeContainer & ); // \ru Не реализовано \en Not implemented 
};


#endif // __CR_ATTRIBURE_PROVIDER_H
