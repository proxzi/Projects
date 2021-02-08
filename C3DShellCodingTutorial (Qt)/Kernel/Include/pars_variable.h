////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Переменная.
         \en Variable. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MBVARIABLE_H
#define __MBVARIABLE_H

#include <pars_tree_variable.h>
#include <math_define.h>


//-----------------------------------------------------------------------------
/** \brief \ru Координата.
           \en Coordinate. \~
  \details \ru Координата. \n
           \en Coordinate. \n \~
  \ingroup Parser
*/
// ---
class MbCoord : public ItCoord
{
private:
  double m_coord; // \ru Значение координаты. \en A value of coordinate. 
public:
  /// \ru Конструктор по значению. \en Constructor by the value. 
  MbCoord( double v ) : m_coord(v) {}
  /// \ru Установить значение. \en Set value. 
  virtual void   SetValue( double v ){ m_coord = v; }
  /// \ru Получить значение. \en Get the value. 
  virtual double GetValue() const    { return m_coord; }
  /// \ru Вычислить размер координаты в байтах. \en Get size of coordinate in bytes. 
  size_t SizeOf() const      { return sizeof(double);}

  /// \ru Операторы чтения, записи. \en Reading and writing operators. 
  KNOWN_OBJECTS_RW_REF_OPERATORS( MbCoord );
};


//-----------------------------------------------------------------------------
/** \brief \ru Переменная.
           \en Variable. \~
  \details \ru Переменная. \n
           \en Variable. \n \~
  \ingroup Parser
*/
// ---
class MATH_CLASS MbTreeVariable : public TapeBase, public ItTreeVariable
{
private:
  MbCoord         m_coord;   ///< \ru Координата. \en Coordinate. 
  c3d::string_t     m_name;    ///< \ru Имя переменной. \en A name of variable. 
  mutable size_t  useCount;  ///< \ru Количество использований. \en The number of uses. 

public:
  /// \ru Конструктор по имени и значению. \en Constructor by the name and the value. 
  MbTreeVariable( const c3d::string_t & name, double v );
  virtual ~MbTreeVariable();

public:
  /// \ru Получить имя. \en Get name. 
  virtual const  c3d::string_t &   GetName  () const                { return m_name; }
  /// \ru Установить имя. \en Set name. 
  virtual        void       SetName  ( const c3d::string_t & name ) { m_name = name; }
  /// \ru Установить имя. Обработка нулевого указателяю \en Set name. Null pointer processing.
  virtual       void        SetName( const TCHAR* s ) { m_name.assign( s ? s : _T("") ); }; 
  /// \ru Получение значение. \en Get value. 
  virtual        double     GetValue () const     { return m_coord.GetValue(); }
  /// \ru Установить значение. \en Set value. 
  virtual        void       SetValue ( double v ) { m_coord.SetValue( v ); }
  /// \ru Получить координату. \en Get coordinate. 
  virtual const  MbCoord &  GetCoord () const { return m_coord; } 
  /// \ru Вычислить размер переменной в байтах. \en Get size of variable in bytes. 
  virtual        size_t     SizeOf   () const { 
#ifdef C3D_WINDOWS //_MSC_VER // method SizeOf()
    return /*m_name.*/sizeof( m_name ) + sizeof( TCHAR ) * (m_name.length()) + m_coord.SizeOf(); 
#else // C3D_WINDOWS 
    // \ru необходимо корректное вычилсение размера занимаемой памяти std::string \en there must be a correct calculation of size of memory allocated for std::string 
    return sizeof(m_name) + m_coord.SizeOf(); // \ru если данный SizeOf требуется для выделения памяти \en if the given SizeOf is required for the memory allocation 
    // \ru то все Ок, поскольку std::string сам разберется с выделением памяти себе. \en then everything is OK because std::string controls the memory allocation for itself. 
#endif // C3D_WINDOWS
  }
  /// \ru Создать копию переменной. \en Create a copy of variable. 
          MbTreeVariable &  Duplicate() const { return *new MbTreeVariable( GetName(), GetValue() ); }
  /// \ru Увеличить счетчик использований. \en Increase a counter of uses. 
  virtual refcount_t            AddRef () const { return ++useCount; }
  /// \ru Уменьшить счетчик использований и удалить объект, если он никому уже не нужен. \en Decrease a counter of uses and delete an object if it is not used any more. 
  virtual refcount_t            Release() const;

  /// \ru Операторы чтения, записи. \en Reading and writing operators. 
  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbTreeVariable );
}; 

IMPL_PERSISTENT_OPS( MbTreeVariable )

#endif // __MBVARIABLE_H