////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Автоматические указатель и ссылка на объекты с подсчетом ссылок.
         \en Smart pointer and reference to objects with reference counter. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __TEMPL_SPTR_H
#define __TEMPL_SPTR_H

#include <system_cpp_standard.h>
#include <math_define.h>


//------------------------------------------------------------------------------
/** \brief \ru Отладочная проверка на NULL.
           \en Debug check for NULL. \~
  \details \ru Отладочная проверка на NULL. \n
           \en Debug check for NULL. \n \~
  \ingroup Base_Tools_SmartPointers
*/
// ---
#define NULL_CHECK PRECONDITION( m_pI != NULL );


//------------------------------------------------------------------------------
/** \brief \ru Автоматический указатель на объекты с подсчетом ссылок.
           \en Smart pointer to objects with reference counter. \~
  \details \ru Автоматический указатель (smart pointer) на объекты с подсчетом ссылок.
           Требует от параметра шаблона реализации функций AddRef() и Release(). \n
           \en Smart pointer to objects with reference counter.
           It requires Implementation of functions AddRef() and Release() from the template parameter. \n \~
  \ingroup Base_Tools_SmartPointers
*/
// ---
template <class T>
class SPtr 
{
  T * m_pI;   // \ru Указатель на объект. \en A pointer to an object.

public:  
  /// \ru Конструктор. \en Constructor. 
  SPtr () : m_pI( NULL ) {}
  /// \ru Конструктор по указателю. \en Constructor by pointer. 
  explicit SPtr ( T * elem )
  {
    if ( (m_pI = elem) != NULL )
      m_pI->AddRef();
  }
  /// \ru Конструктор копирования. \en Copy constructor.   
  SPtr( const SPtr<T> & ptr ) : m_pI( NULL ) { assign(ptr.m_pI); }
  /// \ru Конструктор по совместимому указателю \en Constructor by compatible pointer 
  template<class _T>
  SPtr( const SPtr<_T> & ptr ) : m_pI( ptr.get() ) { if ( m_pI != NULL ) { m_pI->AddRef();} }
  /// \ru Деструктор. \en Destructor. 
 ~SPtr() { if( m_pI != NULL ) m_pI->Release(); }

public: // \ru Перегрузка операторов \en Operators overloading 
  /// \ru Оператор преобразования к типу T* . \en An operator for conversion to the type T*. 
  operator T* ( void ) const { return m_pI; }
  /// \ru Оператор преобразования к совместимому указателю. \en An operator for conversion to a compatible pointer. 
  /*
  template<class _T>
  operator SPtr<_T> () const { return SPtr<_T>( m_pI ); }  
  */
  /// \ru Оператор доступа. \en An access operator. 
  T &       operator * () const { NULL_CHECK return *m_pI; }
  /// \ru Оператор доступа. \en An access operator. 
  T       * operator -> () const { NULL_CHECK return m_pI; }
  /// \ru Оператор присваивания. \en The assignment operator. 
  SPtr<T> & operator = ( T * elem ) { return assign( elem ); }
  /// \ru Оператор присваивания. \en The assignment operator. 
  SPtr<T> & operator = ( const SPtr<T> & ptr ) { return assign( ptr.get() ); }
  /// \ru Оператор присваивания для совместимого указателя. \en An assignment operator for a compatible pointer. 
  template<class _T>
  SPtr<T> & operator = ( const SPtr<_T> & ptr ) { return assign( ptr.get() ); }  
  /// \ru Оператор проверки на равенство. \en An operator for equality check. 
  template<class _T>
  bool      operator == ( const SPtr<_T> & ptr ) const { return ( m_pI == ptr.get() ); }
  /// \ru Оператор проверки на равенство. \en An operator for equality check. 
  template<class _T>
  bool      operator == ( const _T * elem ) const { return ( m_pI == elem ); }
  /// \ru Оператор проверки на равенство. \en An operator for equality check. 
  bool      operator == ( T * elem ) const { return ( m_pI == elem ); }
  /// \ru Оператор проверки на неравенство. \en An operator for inequality check. 
  template<class _T>
  bool      operator != ( const SPtr<_T> & ptr ) const { return ( !(operator == (ptr)) ); }
  /// \ru Оператор проверки на неравенство. \en An operator for inequality check. 
  template<class _T>
  bool      operator != ( const _T * elem ) const { return ( !(operator == (elem)) ); }
  /// \ru Оператор проверки на неравенство. \en An operator for inequality check.   
  bool      operator != ( T * elem ) const { return ( !(operator == (elem)) ); }
  /// \ru Отношение порядка. \en Order relation. 
  template<class _T>
  bool      operator < ( const _T * elem ) const { return ( m_pI < elem ); }
  /// \ru Отношение порядка. \en Order relation. 
  template<class _T>
  bool      operator < ( const SPtr<_T> & elem ) const { return ( m_pI < elem.get() ); }

public:
  /// \ru Функция присваивания указателем. \en A function of assignment by pointer. 
  SPtr<T> & assign( T * elem );
  /// \ru Фунция освобождения объекта. \en A function of release an object. 
  SPtr<T> & reset( void ) { if( m_pI != NULL )	{ m_pI->Release(); m_pI = NULL; } return *this; }
  /// \ru Функция доступа к элементу данных. \en A function of access to data element. 
  T *       get() const { return m_pI; }
  /// \ru Функция отсоединяет объект. \en A function detaches an object. 
  T *       detach() { T * obj = m_pI; m_pI = NULL; if ( obj != NULL ) obj->DecRef(); return obj; }
  /// \ru Нулевой указатель? \en Is null pointer? 
  bool      is_null() const { return (( NULL == m_pI ) ? true : false ); }

#ifdef STANDARD_CPP11_RVALUE_REFERENCES
public:
  /// \ru Конструктор перемещения. \en Moving constructor.
  SPtr( SPtr<T> && src ) : m_pI ( src.m_pI )
  {
    src.m_pI = 0;
  }
  /// \ru Оператор перемещения. \en Moving operator.
  SPtr<T> & operator = ( SPtr<T> && src )
  {
    T * tmp = m_pI;
    m_pI = src.m_pI;
    src.m_pI = tmp;
    return *this;
  }
#endif // STANDARD_CPP11_RVALUE_REFERENCES
};


//------------------------------------------------------------------------------
// \ru Функция присваивания указателем \en A function of assignment by pointer. 
// ---
template <class T>
inline SPtr<T> & SPtr<T>::assign( T * elem )
{
  if ( m_pI != elem ) 
  {
    if ( elem != NULL )	{	elem->AddRef();	}
    if ( m_pI != NULL )	{	m_pI->Release(); }
    m_pI = elem;
  }
  return *this;
}


//------------------------------------------------------------------------------
/** \brief \ru Автоматическая ссылка на объекты с подсчетом ссылок.
           \en Smart reference to objects with reference counter. \~
  \details \ru Автоматическая ссылка (smart reference) на объекты с подсчетом ссылок.
           Фактически тоже самое, что и SPtr, но без возможности равенства NULL.\n
           Требует от параметра шаблона реализации функций AddRef() и Release(). \n
           \en Smart reference to objects with reference counter.
           Actually it is the same as SPtr but without the possibility of equality to NULL \n
           It requires Implementation of functions AddRef() and Release() from the template parameter. \n \~
  \ingroup Base_Tools_SmartPointers
*/
// ---
template <class T>
class SRef 
{
  T * m_pI; ///< \ru Указатель на значение \en A pointer to the value 

public:
  /// \ru Конструктор по ссылке. \en Constructor by reference. 
  SRef ( T & ref ) : m_pI( & ref )
  {
    m_pI->AddRef();
  }
  /// \ru Конструктор копирования. \en Copy constructor. 
  SRef( const SRef & src ): m_pI( src.m_pI )	
  {
    m_pI->AddRef();
  }
  /// \ru Деструктор. \en Destructor. 
 ~SRef( void )
  {
    m_pI->Release();
  }
public:
  /// \ru Функция доступа. \en An access function. 
  T &       get() const { return *m_pI; }
  /// \ru Оператор доступа. \en An access operator. 
            operator T & ( void ) const { return *m_pI; }
  /// \ru Оператор доступа. \en An access operator. 
  T &       operator()() const { return *m_pI; }
  /// \ru Оператор проверки на равенство. \en An operator for equality check. 
  bool      operator == ( const SRef & src ) const { return ( m_pI == src.m_pI );	 }
  /// \ru Оператор проверки на равенство. \en An operator for equality check. 
  bool      operator == ( T & pObj ) const { return ( m_pI == &pObj ); }
  /// \ru Оператор проверки на неравенство. \en An operator for inequality check. 
  bool      operator != ( const SRef & src ) const { return ( !(operator == (src)) );  }
  /// \ru Оператор проверки на неравенство. \en An operator for inequality check. 
  bool      operator != ( T & pObj ) const { return ( !(operator == (pObj)) ); }
  /// \ru Оператор присваивания. \en The assignment operator. 
  SRef<T> & operator = ( const SRef & ref ) { return operator =( *ref.m_pI ); }
  /// \ru Оператор присваивания. \en The assignment operator. 
  SRef<T> & operator =  ( T & obj )
  {
    obj.AddRef();
    m_pI->Release();
    m_pI = &obj;
    return *this;
  }
};


//------------------------------------------------------------------------------
/** \brief \ru Пара автоматических указателей.
           \en A pair of smart pointers. \~
  \details \ru Пара автоматических указателей. \n
    Удобно применять там, где требуется передавать в качестве аргумента 
    функции или результата пару указателей на объекты со счетчиком ссылок.
    Все данные и методы класса намеренно сделаны открытыми.
           \en A pair of smart pointers. \n
    It is comfortable to use this when it is required to pass as an argument 
    of a function or a result, a pair of smart pointers to objects with reference counters.
    All data and methods of the class are purposely made public. \~
  \ingroup Base_Tools_SmartPointers
*/
// ---
template <class RefItem >
struct SPtrPair
{
  SPtr<RefItem> first;  ///< \ru Автоматический указатель на первый объект. \en A smart pointer to the first object. 
  SPtr<RefItem> second; ///< \ru Автоматический указатель на второй объект. \en A smart pointer to the second object. 
  /// \ru Конструктор. \en Constructor. 
  SPtrPair(): first(), second() {}
  /// \ru Конструктор копирования. \en Copy constructor. 
  SPtrPair( const SPtrPair & sPair ) : first(sPair.first), second(sPair.second) {} 
  /// \ru Оператор присваивания. \en The assignment operator. 
  SPtrPair  & operator = ( const SPtrPair & sPair ) { first = sPair.first; second = sPair.second; }
};


#endif // __TEMPL_SPTR_H
