////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Автоматический указатель на объекты, не имеющие счетчиков ссылок.
         \en Smart pointer to objects without reference counters. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef  __TEMPL_DPTR_H
#define  __TEMPL_DPTR_H


#ifndef NULL
 #define NULL 0
#endif


#include <math_define.h>
#include <system_types.h>


//------------------------------------------------------------------------------
/** \brief \ru Автоматический указатель.
           \en Smart pointer. \~
  \details \ru Автоматический указатель на объекты, не имеющие счетчиков ссылок. \n
           \en Smart pointer to objects without reference counters. \n \~
  \ingroup Base_Tools_SmartPointers
*/
// ---
template <class dtype>
class DPtr {
public:
  /// \ru Конструктор. \en Constructor. 
  DPtr();
  /// \ru Конструктор по указателю на объект. \en Constructor by pointer to an object. 
  DPtr( dtype * obj );
  /// \ru Конструктор по автоматическому указателю на объект. \en Constructor by smart pointer to an object. 
  DPtr( const DPtr<dtype> & dptr );
  /// \ru Деструктор. \en Destructor. 
 ~DPtr();

public:
  /// \ru Оператор доступа. \en An access operator. 
                operator dtype* ( void ) const { return m_Ptr; }
  /// \ru Оператор доступа. \en An access operator. 
  dtype       & operator *  ( void ) const { return *m_Ptr; }
  /// \ru Оператор доступа. \en An access operator. 
  dtype       * operator -> ( void ) const { return  m_Ptr; }
  /// \ru Оператор присваивания. \en The assignment operator. 
  DPtr<dtype> & operator =  ( dtype * pObj );
  /// \ru Оператор присваивания. \en The assignment operator. 
  DPtr<dtype> & operator =  ( const DPtr<dtype> & src );
  /// \ru Оператор равенства. \en The equality operator. 
  bool          operator == ( const DPtr<dtype> & src ) const { return ( m_Ptr == src.m_Ptr );	 }
  /// \ru Оператор равенства. \en The equality operator. 
  bool          operator == ( dtype * pObj ) const { return ( m_Ptr == pObj ); }
  /// \ru Оператор неравенства. \en The inequality operator. 
  bool          operator != ( const DPtr<dtype> & src ) const { return ( !(operator == (src )) ); }
  /// \ru Оператор неравенства. \en The inequality operator. 
  bool          operator != ( dtype * pObj ) const { return ( !(operator == (pObj)) ); }

private:
  /// \ru Счетчик ссылок на объект. \en A counter of references to an object. 
  template <class dtype1>
  struct Owner {  
    dtype1 * m_Ptr;
    uint     m_RefCounter;

    Owner( dtype1 * obj )
      : m_Ptr( obj )
      , m_RefCounter(0)
    {}
    ~Owner() 
    {
      PRECONDITION( m_RefCounter == 0 );
      delete m_Ptr;
    }
    void Release()
    {
      if ( m_RefCounter-- == 1 )
        delete this;
    }
  };

private:
  dtype        * m_Ptr;    ///< \ru Указатель на объект. \en A pointer to an object. 
  Owner<dtype> * m_Owner;  ///< \ru Счетчик ссылок на объект. \en A counter of references to an object. 
};


//-------------------------------------------------------------------------------
/// \ru Конструктор. \en Constructor. 
// ---
template <class dtype>
DPtr<dtype>::DPtr()
  : m_Ptr  ( NULL )
  , m_Owner( NULL )
{
}


//-------------------------------------------------------------------------------
// \ru Конструктор по указателю на объект. \en Constructor by pointer to an object. 
// ---
template <class dtype>
DPtr<dtype>::DPtr( dtype * obj )
  : m_Ptr  ( obj  )
  , m_Owner( NULL )
{
  if ( obj != NULL ) {
    m_Owner = new Owner<dtype>( obj );
    m_Owner->m_RefCounter++;
  }
}


//-------------------------------------------------------------------------------
// \ru Конструктор копирования. \en Copy constructor. 
// ---
template <class dtype>
DPtr<dtype>::DPtr( const DPtr<dtype> & dptr )
  : m_Ptr( dptr.m_Ptr )
  , m_Owner( dptr.m_Owner )
{
  if ( m_Owner != NULL )
    m_Owner->m_RefCounter++;
}


//-------------------------------------------------------------------------------
// \ru Оператор присваивания. \en Assignment operator. 
// ---
template <class dtype>
DPtr<dtype> & DPtr<dtype>::operator = ( dtype * pObj )
{
  if ( m_Ptr != pObj ) {
    m_Ptr = pObj;
    if ( m_Owner != NULL ) {
      m_Owner->Release();
      m_Owner = NULL;
    }
    if ( pObj != NULL ) {
      m_Owner = new Owner<dtype>( pObj );
      m_Owner->m_RefCounter++;    
    }
  }  

  return *this;
}


//-------------------------------------------------------------------------------
// \ru Оператор присваивания. \en Assignment operator. 
// ---
template <class dtype>
DPtr<dtype> & DPtr<dtype>::operator = ( const DPtr<dtype> & dptr )
{
  if ( m_Ptr != dptr.m_Ptr ) {
    m_Ptr = dptr.m_Ptr;
    if ( m_Owner != NULL ) {
      m_Owner->Release();
      m_Owner = NULL;
    }
    if ( dptr.m_Ptr != NULL ) {
      m_Owner = dptr.m_Owner;
      m_Owner->m_RefCounter++;
    }
  }
  
  return *this;
}


//-------------------------------------------------------------------------------
// \ru Деструктор. \en Destructor. 
// ---
template <class dtype>
DPtr<dtype>::~DPtr()
{
  if ( m_Owner )
    m_Owner->Release();
}


#endif // __TEMPL_DPTR_H
