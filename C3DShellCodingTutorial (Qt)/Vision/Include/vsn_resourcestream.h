////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс ResourceStream - поток, предназначенный для чтения данных из ресурса (памяти).
         \en ResourceStream class is a stream intended for reading data from resource (memory). \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_IRSTREAM_H
#define __VSN_IRSTREAM_H

#include "vsn_string.h"
#include "vsn_global.h"

#include <iostream>

VSN_BEGIN_NAMESPACE
class ResourceStreamPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс ResourceStream - поток, предназначенный для чтения данных из ресурса(памяти)
            \en ResourceStream class is a stream intended for reading data from resource (memory). \~
    \details \ru Есть возможность менять источник данных потока, используя функции Init. \n
             \en There is a capability to change the stream data source using Init functions. \n \~
    \ingroup Vision_Image
*/
// ---
class VSN_CLASS ResourceStream : public std::istream
{
public:
    /** \brief \ru Конструктор по умолчанию.
               \en Default constructor. \~
    */
    ResourceStream();
    /** \brief \ru Создать поток, используя имя ресурса.
               \en Creates stream using resource name. \~
    */
    ResourceStream(const String& path);
    /** \brief \ru Создать поток, используя указатель на данные и размер.
               \en Creates stream using pointer to data and size. \~
    */
    ResourceStream(const void* buffer, size_t length);
    /** \brief \ru Деструктор.
               \en Destructor. \~
    */
    virtual ~ResourceStream();
    /** \brief \ru Инициализировать поток, используя имя ресурса.
               \en Initializes stream using resource name. \~
    */
public:
    void Init(const String& path);
    /** \brief \ru Инициализировать поток, используя указатель на данные и размер.
               \en Initializes stream using pointer to data and size. \~
    */
    void Init(const void* buffer, size_t length);
private:
    VSN_DECLARE_PRIVATE(ResourceStream)
};

VSN_END_NAMESPACE

#endif // __VSN_IRSTREAM_H
