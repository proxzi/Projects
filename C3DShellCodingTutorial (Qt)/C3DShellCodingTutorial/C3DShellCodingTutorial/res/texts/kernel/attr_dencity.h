////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Атрибуты. Плотность.
         \en Attributes. Density. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_DENCITY_H
#define __ATTR_DENCITY_H


#include <attr_elementary_attribut.h>


//------------------------------------------------------------------------------
/** \brief \ru Плотность.
           \en Density. \~
  \details \ru Плотность. \n
           \en Density. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbDencity : public MbElementaryAttribute {
protected :
  double dencity; ///< \ru Плотность. \en Density. 

protected :
  /// \ru Конструктор. \en Constructor. 
  MbDencity( const MbDencity & init ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbDencity( double init );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbDencity();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Установить плотность. \en Set a density. 
          void    Init( double init ) { dencity = init; }
          /// \ru Дать плотность. \en Get a density. 
          double  Dencity() const  { return dencity; }

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
          void        operator = ( const MbDencity & ); // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbDencity ) 

}; // MbDencity

IMPL_PERSISTENT_OPS( MbDencity )


//------------------------------------------------------------------------------
/** \brief \ru Жесткость.
           \en The stiffness. \~
  \details \ru Механические характеристики материала: модуль Юнга и коэффициент Пуассана. \n
           \en Mechanical properties of the material: Young's modulus and Poisson's ratio. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbElasticity : public MbElementaryAttribute {
protected :
  double young;   ///< \ru Модуль Юнга. \en The Young's modulus of material. 
  double poisson; ///< \ru Коэффициент Пуассона. \en The Poisson's ratio of material.

protected :
  /// \ru Конструктор. \en Constructor. 
  MbElasticity( const MbElasticity & init ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbElasticity( double e, double v );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbElasticity();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Установить свойства. \en Set a density. 
          void    Init( double e_, double v_ ) { young = e_; poisson = v_; }
          /// \ru Дать Модуль Юнга. \en Get an Young's modulus. 
          double  YoungModulus() const  { return young; }
          /// \ru Дать Коэффициент Пуассона. \en Get a Poisson's ratio. 
          double  PoissonRatio() const  { return poisson; }

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
          void        operator = ( const MbElasticity & ); // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbElasticity ) 

}; // MbElasticity

IMPL_PERSISTENT_OPS( MbElasticity )


//------------------------------------------------------------------------------
/** \brief \ru Деформации / Напряжения.
           \en The strains / The tensions. \~
  \details \ru Напряжённо деформированное состояние объекта - три деформации или три напряжения. \n
           \en Tension strain state of an object. \n \~
  \ingroup Model_Attributes
*/
// ---
class MATH_CLASS MbStrains : public MbElementaryAttribute {
protected :
  double strain1; ///< \ru Деформация 1 / Напряжение 1. \en The strain 1 / The tension 1. 
  double strain2; ///< \ru Деформация 2 / Напряжение 2. \en The strain 2 / The tension 2. 
  double strain3; ///< \ru Деформация 3 / Напряжение 3. \en The strain 3 / The tension 3. 

protected :
  /// \ru Конструктор. \en Constructor. 
  MbStrains( const MbStrains & init ); 
public :
  /// \ru Конструктор. \en Constructor. 
  MbStrains( double e1, double e2, double e3 );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbStrains();

  // \ru Общие функции объекта \en Common functions of object. 

  virtual MbeAttributeType AttributeType() const; // \ru Дать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const; // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    Init( const MbAttribute & ); // \ru Инициализировать данные по присланным. \en Initialize data. 

          /// \ru Установить свойства. \en Set a density. 
          void    Init( double e1, double e2, double e3 ) { strain1 = e1; strain2 = e2; strain3 = e3; }
          /// \ru Дать деформированное состояние объекта. \en Get a deformed state. 
          double  Strain( size_t i ) const  { if ( i <= 1 ) return strain1; else if ( i == 2 ) return strain1; else return strain3; }

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

private:
          void        operator = ( const MbStrains & ); // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbStrains ) 

}; // MbStrains

IMPL_PERSISTENT_OPS( MbStrains )


#endif // __ATTR_DENCITY_H
