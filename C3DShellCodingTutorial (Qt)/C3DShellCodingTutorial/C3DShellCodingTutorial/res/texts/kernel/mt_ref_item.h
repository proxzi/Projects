//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file 
  \brief  \ru Надкласс для объектов, время жизни которых автоматически регулируется счетчиком ссылок.
          \en Superclass for objects their lifetime is automatically regulated by reference counter.
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __MT_REF_ITEM_H
#define __MT_REF_ITEM_H

#include <system_types.h>


//////////////////////////////////////////////////////////////////////////////////////////
/**
  \brief  \ru Базовый класс для объектов с подсчетом ссылок.
          \en Base class for objects with reference counting. \~
  \ingroup Base_Items
  \sa #MbRefItem, #SPtr
*/
//////////////////////////////////////////////////////////////////////////////////////////

class MtRefItem
{
  mutable refcount_t useCount;

protected:
           MtRefItem() : useCount(0) {}
  virtual ~MtRefItem() {}

public: 
  /// \ru Добавить одну ссылку на объект. \en Adds a reference to this object. 
  refcount_t  AddRef()  const { return ++useCount; }
  /// \ru Освободить одну ссылку на объект. \en Releases a reference to this object.
  refcount_t  Release() const;

public:
  /// \ru Вернуть количество объектов, ссылающихся на данный. \en Returns a number of objects referring to this.
  refcount_t  GetUseCount() const { return useCount; }

private:
  MtRefItem( const MtRefItem & );
  MtRefItem & operator = ( const MtRefItem & );
};

//----------------------------------------------------------------------------------------
//
//---
inline refcount_t MtRefItem::Release() const 
{          
  if ( !useCount || (--useCount == 0) )
  {
    delete this; // \ru Вызов виртуального деструктора \en Call of virtual destructor 
    return 0;                            
  }

  return useCount;
}                                        

#endif // __MT_REF_ITEM_H

// eof