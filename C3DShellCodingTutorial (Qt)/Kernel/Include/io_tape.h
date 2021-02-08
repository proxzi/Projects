////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Сериализация: чтение и запись потоковых классов.
         \en Serialization: reading and writing of stream classes. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __IO_TAPE_H
#define __IO_TAPE_H


/// \ru Для контроля чтения/записи char* и TCHAR* только через ReadTCHAR/WriteTCHAR() скомпилировать с данным дефайном и увидим все места, где незаконно пишутся/читаются данные через operator << и >>.
/// \en Compile with the given preprocessor define for control of reading/writing char* and TCHAR* only via ReadTCHAR/WriteTCHAR(), not via illegally operator << and >>. 
//#define DISABLE_RWTCHAR  


////////////////////////////////////////////////////////////////////////////////
//
// \ru Классы, для которых при записи и чтении точно известен тип, \en Classes for which the type is exactly known while reading and writing 
// \ru могут записываться в поток и читаться из потока с помощью \en can be written to the stream and read from the stream using 
// \ru операторов << и >>, \en << and >> operators. 
// \ru Это, например, классы лежащие в массиве SArray \en They are, for instance, classes contained in array SArray 
//
// \ru Для таких объектов необходимо в описании класса установить : \en For such objects one should set in the class definition: 
// \ru KNOWN_OBJECTS_RW_REF_OPERATORS( Class ) - для работы со ссылками и объектами класса \en KNOWN_OBJECTS_RW_REF_OPERATORS( Class ) - for work with references and class objects 
// \ru KNOWN_OBJECTS_RW_PTR_OPERATORS( Class ) - для работы с указателями на объекты класса \en KNOWN_OBJECTS_RW_PTR_OPERATORS( Class ) - for work with pointers to class objects 
//
// \ru и определить тела самих операторов : \en and define the solids of operators: 
//
// \ru -- для ссылок \en -- for references 
//  inline reader& operator >> ( reader& in, Class& ref ) {
//    return in >> ref. >> ref.... ;
//  }
//
//  writer& operator << ( writer& out, const Class& ref ) {
//    return out << ref. << ref. ... ;
//  }
//
// \ru -- для указателей \en -- for pointers 
//  inline reader& operator >> ( reader& in, Class*& ptr ) {
//    ptr = new Class(...);
//    return in >> ptr-> >> ptr->.... ;
//  }
//
//  writer& operator << ( writer& out, const Class* ptr ) {
//    return out << ptr-> << ptr-> ... ;
//  }
//
// \ru Классы, для которых при записи и чтении тип не известен. \en Classes for which the type is unknown while writing and reading. 
// \ru Для описания такого класса Class как поточного в общем случае требуется : \en There are the following requirements for description of such class Class as a stream class: 
// \ru -- Наследовать класс от TapeBase напрямую или через своих предков \en -- Inherit the class from TapeBase directly or via ancestors 
// \ru Примечание : \en Note: 
// \ru Если класс наследует более чем от одного поточного класса, \en If the class is inherited from more than one stream class, 
// \ru то его предки !!!обязательно!!! должны наследовать от TapeBase \en then its parents MUST be inherited from TapeBase 
// \ru виртуально, т.е. \en virtually, i.e. 
//           class A : public virtual TapeBase {
//             ...
//           };
//
//           class B : public virtual TapeBase {
//             ...
//           };
//
//           class C : public A, public B {
//             ...
//           };
//
// \ru При этом классы A,B равно как и C нельзя укладывать в SArray, \en At the same time classes A,B cannot be put to array SArray, as well as class C, 
// \ru поскольку они неявно содержат указатель на виртуальную базу \en since they implicitly contain a pointer to the virtual base 
//
// \ru -- В декларации класса установить : \en -- Set in declaration of the class: 
// \ru DECLARE_PERSISTENT_CLASS( Class ) - если Class не имеет поточных предков \en DECLARE_PERSISTENT_CLASS( Class ) - if Class does not have stream ancestors 
//
// \ru -- В любом *.cpp файле установить : \en -- Set in any *.cpp file: 
// \ru IMP_PERSISTENT_CLASS( AppID, Class ); - требуется написание конструктора \en IMP_PERSISTENT_CLASS( AppID, Class ); - the constructor implementation is required 
//
// \ru -- Описать тела функций : \en -- Describe the solids of functions: 
//        void Class::Read( reader& in, Class* obj );
//        void Class::Write( writer& out, const Class* obj );
//
// \ru Если Class не содержит своих полей данных, которые необходимо \en If Class does not contain its own data fields which should 
// \ru писать в поток и читать оттуда, то вместо \en be written to stream and be read from stream, then instead of 
// \ru IMP_PERSISTENT_CLASS следует применять \en IMP_PERSISTENT_CLASS one should use 
//    IMP_PERSISTENT_CLASS_FROM_BASE( Class, Base ),
// \ru при этом не надо определять функции Class::Read и Class::Write \en at that the functions Class::Read and Class::Write don't have to be defined 
//
// \ru Если Class абстрактный -- применять \en If Class is abstract - apply 
//    IMP_A_PERSISTENT_CLASS( Class );
//
// \ru Если Class не наследует ни от кого кроме TapeBase и плюс к этому \en If Class does not inherit from any class except TapeBase and, in addition, 
// \ru не имеет полей данных для записи, применять : \en does not have data fields for writing, apply: 
// \ru в cpp-файле \en in cpp-file 
// \ru для абстрактного -- IMP_AWD_PERSISTENT_CLASS( Class ); \en for the abstract one -- IMP_AWD_PERSISTENT_CLASS( Class ); 
// \ru для обычного     -- IMP_WD_PERSISTENT_CLASS( Class ); \en for the ordinary one    -- MP_WD_PERSISTENT_CLASS( Class ); 
// \ru примечание : WD - Without Data \en note: WD - Without Data 
//
// \ru Если Class наследует более чем от одного TapeBase'а \en If Class inherit from more than one TaperBase class, 
// \ru наследование от него должно быть virtual'ным, например : \en the inheritance from it should be virtual, for instance: 
//    class first : virtual public TapeBase {
//      ...
//      DECLARE_PERSISTENT_CLASS( AppID, first );
//    };
//
//    class second : virtual public TapeBase {
//      ...
//      DECLARE_PERSISTENT_CLASS( AppID, second );
//    };
//
//    class third : public first, public second {
//      ...
//      DECLARE_PERSISTENT_CLASS( AppID, third );
//    };
//    IMP_PERSISTENT_CLASS( AppID, first )
//    IMP_PERSISTENT_CLASS( AppID, second )
//    IMP_PERSISTENT_CLASS( AppID, third )
// \ru + функции чтения - записи \en + functions of reading-writing 
// \ru + соответствующие конструкторы чтения \en + the corresponding reading constructors   
//
// \ru Если Class template'ный, то для описания класса поточным требуется : \en If Class is a template class, then the following is required for definition the class as a stream class: 
// \ru -- Наследовать template от TapeBase \en -- Inherit template from TapeBase 
//
// \ru -- В декларации template'а установить : \en -- Set in the declaration of template : 
//        DECLARE_T_PERSISTENT_CLASS( Templ, Arg );
// \ru где Templ - имя самого template'а \en where Templ is the name of template 
// \ru Arg   - имя формального template'ного аргумента \en Arg   - the name of formal argument of template 
//
// \ru -- В этом же h-файле вне декларации template'а установить \en -- Set in the same h-file outside the template declaration 
//        IMP_T_PERSISTENT_OPS( Templ );
//
// \ru -- В этом же h-файле вне декларации template'а  описать тела функций : \en -- In the same h-file outside the template declaration describe solids of functions: 
//        template <class Arg>
//          void Templ<Agr>::Read( reader& in, Templ<Agr>* obj );
//        template <class Arg>
//          void Templ<Agr>::Write( writer& out, const Templ<Agr>* obj );
// \ru где \en where 
// \ru Arg - формальный аргумент \en Arg - formal argument 
//
// \ru -- В любом(ых) cpp-файле(ах) установить для каждого применения template'а : \en -- In any cpp-files set for each use of template: 
//        IMP_T_PERSISTENT_CLASS( Templ, Class );
// \ru где \en where 
// \ru Class - имя класса с которым применяется template ( фактический аргумент ) \en Class - name of the class the template is used with (the actual argument) 
//
// \ru Примечание : для классов List, DList, SArray, PArray, Array2 все действия \en Note: for classes List, DList, SArray, PArray, Array2 all the instructions 
// \ru уже выполнены, кроме последнего пункта. \en already applied except the last one. 
//
//
// \ru По поводу функции Class::Read( reader& in, Class* obj ) рекомендуется \en Regarding function Class::Read( reader& in, Class* obj ) it is recommended 
// \ru обратить внимание на : \en to pay attention to: 
//
// \ru 1.Поля данных базового класса самостоятельно читать не нужно, вместо этого \en 1.Data fields of the base class don't require any special code to be read, instead of it 
// \ru нужно вызвать функцию ReadBase( out, (Base*)obj ). \en one should call function ReadBase( out, (Base*)obj ). 
// \ru Вызывать ее желательно в голове функции Class::Read \en It is desirable to call it in the head of function Class::Read 
// \ru Обратите внимание на преобразование типа (Base*)obj ! \en Pay attention to the conversion like (Base*)obj ! 
//
// \ru 2.Функция Class::Read декларирована статической (static), поэтому она не имеет \en 2. Function Class::Read is declared as static so it has no 
// \ru указателя this ==> не пытайтесь делать что-нибудь типа : \en 'this' pointer ==> don't try to do something like: 
//        in >> field
// \ru правильно : \en the correct variant is: 
//        in >> obj->field;
//
// \ru По поводу функции Class::Write( writer& out, const Class* obj ) рекомендуется \en As for function Class::Write( writer& out, const Class* obj ), it is recommended 
// \ru обратить внимание на : \en to pay attention to: 
//
// \ru 1.Поля данных базового класса самостоятельно писать не нужно, вместо этого \en 1.Data fields of the base class don't require any special code to be written, instead of it 
// \ru нужно вызвать функцию WriteBase( out, (const Base*)obj ). \en one should call function WriteBase( out, (const Base*)obj ). 
// \ru Вызывать ее желательно в голове функции Class::Write \en It is desirable to call it in the head of function Class::Write 
// \ru Обратите внимание на преобразование типа (const Base*)obj ! \en Pay attention to the conversion like (const Base*)obj ! 
//
// \ru 2.Функция Write декларирована статической (static), поэтому она не имеет \en 2.Function Class::Write is declared as static so it has no 
// \ru указателя this ==> не пытайтесь делать что-нибудь типа : \en 'this' pointer ==> don't try to do something like: 
//        out << field
// \ru правильно : \en the correct variant is: 
//        out << obj->field;
//
//
// \ru По поводу поддержки версий : \en As for versions support: 
// \ru 1. При записи - \en 1. While reading - 
// \ru iobuf имеет статическое поле данных iobuf_defaultVersionCont - контейнер версии \en iobuf has static data field iobuf_defaultVersionCont - the version container 
// \ru и статическую функцию void iobuf::SetDefaultVersion( VERSION ); \en and the static function void iobuf::SetDefaultVersion( VERSION); 
// \ru которую можно вызывать в любом месте программы, например : \en which can be called in any place of the program, for instance: 
//          iobuf::SetDefaultVersion( 192 );
// \ru все потоки, которые будут записываться после этого, будут записывать этот \en all the streams which will be written after this will write this 
// \ru номер в качестве версии \en number as a version 
// \ru 2. При чтении - \en 2. While reading - 
// \ru номер версии, записанный в поток возвращается функцией \en the version number written to the stream is returned by function 
//        VERSION in.MathVersion(),
// \ru где in - экземпляр потока \en where in - is the stream instance 
//
////////////////////////////////////////////////////////////////////////////////

#include <math_x.h>
#include <map>
#include <memory>
#include <float.h>
#include <io_buffer.h>
#include <io_memory_buffer.h>
#include <templ_pointer.h>
#include <templ_sptr.h>
#include <templ_ss_array.h>
#include <templ_sfdp_array.h>
#include <alg_indicator.h>
#include <tool_cstring.h>
#include <tool_uuid.h>
#include <hash32.h>
#include <system_cpp_standard.h>
#include <system_dependency.h>
#include <math_version.h>
#include <math_define.h>
#include <io_tree.h>
#include <tool_mutex.h>
#include <tool_memory_leaks_check.h>

#ifdef _MSC_VER // LF-Linux: incomplete type reader/writer errors
#include <templ_s_array_rw.h> // R/W
#endif // _MSC_VER
#ifdef __DEBUG_MEMORY_ALLOCATE_FREE_
#include <tool_memory_debug.h>
#endif

#include <typeinfo>
#include <system_types.h>

//----------------------------------------------------------------------------------------
// \ru Предварительное объявление классов чтения/записи.
// \en The forward declaration of the read/write classes. \~
// ---
class TapeManager;
class reader;
class writer;

//----------------------------------------------------------------------------------------
/** \brief \ru Типы регистрации объектов.
           \en Types of objects registration. \~
  \details \ru Типы регистрации потоковых объектов. \n
           \en Types of stream objects registration. \n \~
  \ingroup Base_Tools_IO
*/
//---
enum RegistrableRec { 
  noRegistrable, ///< \ru Нерегистрируемый объект. \en Unregistrable object. 
  registrable    ///< \ru Регистрируемый объект. \en Registrable object. 
};


//----------------------------------------------------------------------------------------
/** \brief \ru Типы инициализации объектов.
           \en The objects initialization types. \~
  \details \ru Типы регистрации потоковых объектов. \n
           \en Types of stream objects registration. \n \~
  \ingroup Base_Tools_IO
*/
//---
enum TapeInit {
  tapeInit ///< \ru По умолчанию. \en By default. 
};


//----------------------------------------------------------------------------------------
/** \brief \ru Упакованное имя класса.
           \en Packed class name. \~
  \details \ru Упакованное имя одного класса - для набора массива потоковых классов в TapeClass. \n
           \en Packed name of one class - for array of stream classes in TapeClass. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS ClassDescriptor
{
protected:
  uint16 val;     ///< \ru Хэш имени класса. \en The class name hash.
  MbUuid appID_;  ///< \ru Дополнительный идентификатор приложения. \en Additional application identifier.

private:
  /// Признак записи appID
  static const uint16 rwIdFlag;

public:
  /// \ru Конструктор. \en Constructor. 
  ClassDescriptor();
  /// \ru Конструктор по хэшу. \en Constructor by hash. 
  ClassDescriptor( uint16 v );
  /// \ru Конструктор по имени. \en Constructor by name. 
  ClassDescriptor( const char * name );
  /// \ru Конструктор по хэшу. \en Constructor by hash. 
  ClassDescriptor( uint16 v, const MbUuid & appID  );
  /// \ru Конструктор по имени. \en Constructor by name. 
  ClassDescriptor( const char * name, const MbUuid & appID );
  /// \ru Конструктор по хэшу. \en Constructor by hash. 
  ClassDescriptor( const ClassDescriptor & other );

  /// \ru Оператор присваивания. \en An assignment operator. 
  ClassDescriptor & operator = ( const ClassDescriptor & other );

  /// \ru Оператор равенства. \en The equality operator. 
  bool  operator == ( const ClassDescriptor & other ) const;

  /// \ru Оператор неравенства. \en The inequality operator. 
  bool  operator!=( const ClassDescriptor & other ) const;

  /// \ru Оператор сравнения. \en Comparison operator. 
  bool operator < (const ClassDescriptor & other ) const;

  /// \ru Оператор сравнения. \en Comparison operator. 
  bool operator > ( const ClassDescriptor & other ) const;

#ifdef C3D_DEBUG
  /// \ru Оператор доступа. \en An access operator. 
  operator uint16() const                     { return val; }
#endif

  /// \ru Оператор записи. \en Write operator.
  void Write( writer & out );

  /// \ru Оператор чтения. \en Read operator.
  bool Read( reader & in );
};


//------------------------------------------------------------------------------
/** \brief \ru Базовый класс для потоковых классов.
           \en Base class for stream classes. \~
  \details \ru Базовый класс для потоковых классов. \n
           \en Base class for stream classes. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS TapeBase {
private:
  mutable use_count_type  m_countRegistrable; ///< \ru Счетчик ссылок регистрируемого объекта. \en Number of usages of the registrable object. 

public:
  /// \ru Конструктор. \en Constructor. 
  TapeBase( RegistrableRec regs = noRegistrable );
  /// \ru Конструктор копирования \en Copy-constructor. 
  TapeBase( const TapeBase & );
  /// \ru Деструктор. \en Destructor. 
  virtual ~TapeBase();

  /// \ru Является ли потоковый класс регистрируемым. \en Whether the stream class is registrable. 
  RegistrableRec GetRegistrable() const;
  /// \ru Установить состояние регистрации потокового класса. \en Set the state of registration of the stream class. 
  void           SetRegistrable( RegistrableRec regs = registrable ) const;
  /// \ru Получить дескриптор класса
  //virtual ClassDescriptor GetClassDescriptor( const VersionContainer & ) const { return ClassDescriptor( ::pureName(typeid(*this).name()) ); }
  virtual ClassDescriptor GetClassDescriptor( const VersionContainer & ) const = 0;

  /// \ru Получить имя класса. \en Get the class name.
  virtual const char * GetPureName( const VersionContainer & ) const;

  /// \ru Принадлежит ли объект к регистрируемому семейству. \en Whether the object belongs to a registrable family.
  virtual bool IsFamilyRegistrable() const;

private:
  /// \ru Функция-пустышка для обеспечения полиморфизма данного класса и его наследников. \en Dummy function for providing polymorphism of the given class and its descendants. 
  virtual void   dummy();   // I need this to make class polymorphic
  /// \ru Оператор присваивания \en Assignment operator 
  void operator = ( const TapeBase & other );
};


//----------------------------------------------------------------------------------------
/// \ru Шаблон функции создания нового экземпляра. \en Template of function of a new instance creation. \~ \ingroup Base_Tools_IO
//---
typedef TapeBase * (CALL_DECLARATION * BUILD_FUNC) ( void );

//----------------------------------------------------------------------------------------
/** \brief \ru Шаблон функции преобразования.
           \en Template of conversion function. \~
  \details \ru Шаблон функции преобразования из указателя на TapeBase к указателю на класс. \n
           \en Template of function of conversion from a pointer to TapeBase to a pointer to the class. \n \~
  \ingroup Base_Tools_IO
*/
//---
typedef void * (CALL_DECLARATION * CAST_FUNC) ( const TapeBase * );

//----------------------------------------------------------------------------------------
/**\ru Шаблон функции чтения экземпляра.
   \en Template of instance reading function. \~ 
   \ingroup Base_Tools_IO
*/
//---
typedef void (CALL_DECLARATION * READ_FUNC) ( reader & in, void * /*obj*/ );

//----------------------------------------------------------------------------------------
/// \ru Шаблон функции записи экземпляра. \en Template of instance writing function. \~ \ingroup Base_Tools_IO
//---
typedef void (CALL_DECLARATION * WRITE_FUNC) ( writer & out, void * /*obj*/ );

//----------------------------------------------------------------------------------------
/** \brief \ru "Обертка" для одного потокового класса.
           \en "Wrapper" for one stream class. \~
  \details \ru "Обертка" для одного потокового класса ( не экземпляра! ).
    Xранит упакованное имя класса и адреса функций, необходимых при чтении/записи. \n
           \en "Wrapper" for one stream class ( not instance! ).
    Stores packed class name and addresses of functions necessary while reading/writing. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS TapeClass {
protected:
  ClassDescriptor hashValue; ///< \ru Упакованное имя класса. \en Packed class name. 
  BUILD_FUNC     _builder;   ///< \ru Функция создания нового экземпляра. \en Functions of a new instance creation. 
  CAST_FUNC      _caster;    ///< \ru Функция преобразования от TapeBase к указателю на класс. \en Function of conversion from TapeBase to a pointer to a class. 
  READ_FUNC      _reader;    ///< \ru Функция чтения. \en Read function. 
  WRITE_FUNC     _writer;    ///< \ru Функция записи. \en Write function. 

public:
  /// \ru Конструктор. \en Constructor.
  /// \ru Конструктор. \en Constructor. 
  TapeClass( const char * name, BUILD_FUNC b, CAST_FUNC c, READ_FUNC r, WRITE_FUNC w );
  TapeClass( const char * name, MbUuid appID, BUILD_FUNC b, CAST_FUNC c, READ_FUNC r, WRITE_FUNC w );
  /// \ru Деструктор. \en Destructor. 
  virtual ~TapeClass();
  /// \ru Получить упакованное имя класса. \en Get the packed class name. 
          ClassDescriptor GetPackedClassName() const;
  /// \ru Получить упакованное имя класса для записи с учетом версии. \en Get the packed class name for writing subject to the version. 
  virtual ClassDescriptor GetPackedClassNameForWrite( VERSION ) const;
  
  friend class  TapeManager;
  friend struct TapeClassContainer;

OBVIOUS_PRIVATE_COPY( TapeClass )
};


//----------------------------------------------------------------------------------------
/** \brief \ru Массив для регистрации объектов при чтении/записи.
           \en Array for object registration while reading/writing. \~
  \details \ru Массив для регистрации объектов при чтении/записи. \n
           \en Array for object registration while reading/writing. \n \~
  \ingroup Base_Tools_IO
*/
//---
class MATH_CLASS TapeRegistrator 
{
public:
  typedef std::map<const TapeBase *, size_t> TapeIndexMap;
  typedef std::map<size_t, TapeBase *>       IndexTapeMap;
protected:
  TapeIndexMap tapeIndexPairs; /// \ru Ассоциативный массив связок [указатель на объект]-[номер в массиве]. \en Map of [object]-[index] pairs.
  size_t       maxCount;       /// \ru Максимальное количество зарегистрированных объектов. \en Maximal number of registered objects.
  IndexTapeMap indexesAndObjs; /// \ru Ассоциативный массив связок [номер в массиве]-[указатель на объект]. \en Map of [index]-[object] pairs.

public:
  /// \ru Конструктор. \en Constructor. 
  TapeRegistrator();
  /// \ru Деструктор. \en Destructor. 
  virtual ~TapeRegistrator();

  /// \ru Получить количество зарегистрированных объектов. \en Get a number of registered objects. 
  size_t      Count() const;
  /// \ru Зарезервировать место под данное количество элементов. \en Reserve space for a given number of elements.
  bool        Reserve ( size_t n );
  
  /// \ru Найти объект в массиве. \en Find the object in array. 
  size_t      FindIt( const TapeBase * e ) const;
  /// \ru Существует ли объект в массиве. \en Whether the object is in the array. 
  bool        IsExist( const TapeBase * e ) const;
  /// \ru Узнать максимально возможное количество регистрируемых объектов. \en Get the maximal possible number of registered objects. 
  size_t      GetMaxCount() const;
  /// \ru Выдать из массива зарегистрированных объектов указатель по заданному индексу. \en Get the pointer from the registered object array by the given index. 
  TapeBase *  operator[]( size_t ind ) const ;

  ///< \ru Вставить элемент с определенным индексом. \en Insert an element with defined index. 
  void        AddAt( const TapeBase * e, size_t ind );

  /// \ru Добавить объект в массив. \en Add the object to the array. 
  size_t      Add( const TapeBase * e );

  /// \ru Выдать указатель на зарегистрированный объект по заданной позиции в кластере. \en Get the pointer of the registered object by the position in the cluster. 
  virtual TapeBase *        Get( const ClusterReference & ) const { return NULL; } // unsupported
  /// \ru Выдать позицию в кластере по заданному индексу. \en Get position in the cluster by given index. 
  virtual ClusterReference  GetClusterRef( size_t )   const { return ClusterReference(); } // unsupported
  /// \ru Добавить позицию объекта в кластере. \en Add the object position in the cluster. 
  virtual void              AddClusterRef( size_t, const ClusterReference & ) {} // unsupported
  /// \ru Очистить массив зарегистрированных объектов. \en Flush the array of registered objects. 
  virtual void              FlushRegistered();
  /// \ru Очистить зарегистрированный объект \en Flush the registered object 
  virtual void              FlushObj( const TapeBase * );

  /// \ru Поменять местами массивы для регистрации
  void Swap ( TapeRegistrator & swapReg );

protected:
  /// \ru Очистить зарегистрированный объект \en Flush the registered object 
  void         FlushObjInd( size_t );

#ifdef __DEBUG_MEMORY_ALLOCATE_FREE_
public:
  void * operator new    ( size_t size ) {
    return ::Allocate( size, typeid(TapeRegistrator).name() );
  }
  void   operator delete ( void * ptr, size_t size ) {
    ::Free( ptr, size, typeid(TapeRegistrator).name() );
  }
#endif // __DEBUG_MEMORY_ALLOCATE_FREE_

OBVIOUS_PRIVATE_COPY( TapeRegistrator )
};

//----------------------------------------------------------------------------------------
/** \brief \ru Массив для регистрации объектов с сохраненим информации о позиции чтения/записи.
           \en Array for registration of objects with information about reading/writing position. \~
  \details \ru Массив для регистрации объектов с сохраненим информации о позиции чтения/записи. \n
           \en Array for registration of objects with information about reading/writing position. \n \~
  \ingroup Base_Tools_IO
*/
//---
class MATH_CLASS TapeRegistratorEx : public TapeRegistrator {
public:
  typedef std::map<ClusterReference, size_t>        ClusterIndexMap;
  typedef std::map<size_t, const ClusterReference*> IndexClusterMap;
private:
  /// \ru Ассоциативный массив [cluster position] -> [object index]. Основное хранилище для значений ClusterReference.
  /// \en Map: [cluster position] -> [object index]. The primary container for ClusterReference values.
  ClusterIndexMap  refIndex;
  /// \ru Ассоциативный массив [object index] -> [pointer to cluster position]. Содержит указатели на объекты ClusterReference из массива refIndex.
  /// \en Map: [object index] -> [pointer to cluster position]. Contains pointers to object ClusterReference from refIndex map.
  IndexClusterMap  objReferences;

public:
  /// \ru Конструктор. \en Constructor. 
  TapeRegistratorEx();

  /// \ru Выдать указатель на зарегистрированный объект по заданной позиции в кластере.
  /// \en Get the pointer ещ the registered object by the position in the cluster. 
  virtual TapeBase *        Get ( const ClusterReference & ref ) const;

  /// \ru Выдать позицию в кластере по заданному индексу. \en Get position in the cluster by given index. 
  virtual ClusterReference  GetClusterRef ( size_t ind ) const;

  /// \ru Добавить позицию объекта в кластере. \en Add the object position in the cluster. 
  virtual void              AddClusterRef( size_t ind, const ClusterReference & ref );

  /// \ru Очистить массив зарегистрированных объектов. \en Flush the array of registered objects. 
  virtual void              FlushRegistered();
  /// \ru Очистить зарегистрированный объект \en Flush the registered object 
  virtual void              FlushObj ( const TapeBase * );

OBVIOUS_PRIVATE_COPY( TapeRegistratorEx )
};


//----------------------------------------------------------------------------------------
/** \brief \ru Cпособы записи указателей.
           \en Methods of writing pointers. \~
  \details \ru Cпособы записи указателей. \n
           \en Methods of writing pointers. \n \~
  \ingroup Base_Tools_IO
*/
//---
enum TapePointerType { 
  tpt_Null              = 0x00, ///< \ru Нулевой указатель. \en Null pointer. 
  tpt_Indexed16         = 0x01, ///< \ru Индекс указателя в массиве регистрации (2 байта). \en Pointer index in the registration array (2 bytes). 
  tpt_Object            = 0x02, ///< \ru Тело объекта. \en The object solid. 
  tpt_Indexed8          = 0x03, ///< \ru Индекс указателя в массиве регистрации (1 байт). \en Index of pointer in the registration array (1 byte). 
  tpt_Indexed32         = 0x04, ///< \ru Индекс указателя в массиве регистрации (4 байта). \en Pointer index in the registration array (4 bytes). 
  tpt_Indexed64         = 0x05, ///< \ru Индекс указателя в массиве регистрации (8 байт). \en Index of pointer in the registration array (8 byte). 
  tpt_DetachedObject    = 0x06, ///< \ru Тело объекта в отдельном FileSpace. \en The object solid in separated FileSpace. 
  tpt_ObjectCatalog     = 0x07, ///< \ru Каталог объектов в отдельном FileSpace. \en The object catalog in separated FileSpace. 
};


#pragma pack( push, 1 )
//----------------------------------------------------------------------------------------
/** \brief \ru Базовый класс потока для реализации чтения и записи.
           \en The base class of the stream for implementation of reading and writing. \~
  \details \ru Базовый класс потока для реализации чтения и записи. \n
           \en The base class of the stream for implementation of reading and writing. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS tape {
protected:
  iobuf_Seq   &                 buf;         ///< \ru Буфер для данных. \en Buffer for data. 
  TapeManager &                 manager;     ///< \ru Менеджер потоков. \en Stream manager. 
  uint8                         level;       ///< \ru Уровень вложенности при чтении/записи. \en Nesting level while reading/writing. 
  TapeRegistrator &             registrator; ///< \ru Структура для регистрации записанных/прочитанных адресов. \en Structure for registration of written/read addresses. 
  mutable ProgressBarWrapper *  progress;    ///< \ru Индикатор прогресса. \en Progress indicator.

private:
  uint8  ownBuf;      ///< \ru Владеет ли буфером. \en Whether it owns the buffer. 
  bool   ownReg;      ///< \ru Признак владения регистратором.

public:
  /// \ru Тип объекта. \en An object type. 
  enum objectType { 
    otNull,    
    otIndexed, 
    otObject
  };
  /// \ru Деструктор. \en Destructor. 
  virtual ~tape();
  
  /// \ru Получить доступ к буферу. \en Get access to the buffer.
  DEPRECATE_DECLARE iobuf & buffer()     const;
  /// \ru Получить доступ к буферу. \en Get access to the buffer. 
  DEPRECATE_DECLARE iobuf & operator()() const;

  /// \ru Получить доступ к буферу. \en Get access to the buffer. 
  const iobuf_Seq & GetIOBuffer() const;

  /// \ru Получить доступ к буферу. \en Get access to the buffer. 
  iobuf_Seq & GetIOBuffer();

  /// \ru Узнать режим работы буфера. \en Get the buffer mode. 
  uint8             mode()               const; //AR getMode
  /// \ru Установить режим работы буфера. \en Set the buffer mode. 
  void              setMode( uint8 m );
  /// \ru Убрать состояние буфера. \en Remove the buffer state. 
  void              clearState( io::state sub );
  /// \ru Добавить состояние буфера. \en Add the buffer state. 
  void              setState  ( io::state add );

  /// \ru Установить текущую версию равной версии хранилища. \en Set the current version to be equal to the storage version. 
  void              SetVersionsByStorage();
  /// \ru Вернуть главную версию (математического ядра). \en Return the main version (of the mathematical kernel). 
  VERSION           MathVersion()        const;
  /// \ru Вернуть дополнительную версию (конечного приложения). \en Return the additional version (of the target application). 
  VERSION           AppVersion( size_t ind = -1 ) const;

  /// \ru Получить доступ к контейнеру версий. \en Get access to the version container. 
  const VersionContainer & GetVersionsContainer() const;
  /// \ru Установить версию открытого файла. \en Set the version of open file. 
  void              SetVersionsContainer( const VersionContainer & vers ) const;
  /// \ru Установить версию хранилища. \en Set the storage version. 
  VERSION           SetStorageVersion( VERSION v );

  /// \ru Свежий ли буфер? \en Is the buffer fresh? 
  int               fresh() const;
  /// \ru Корректно ли состояние буфера.. \en Whether the buffer state is correct. 
  bool              good()  const;
  /// \ru Достигнут ли конец файла? \en Is the end of file reached? 
  virtual uint8     eof()   const;
  /// \ru Получить флаг состояния буфера. \en Get the flag of the buffer state. 
  virtual uint32    state() const;
  /// \ru Получить текущую позицию в потоке. \en Get current position in stream
  virtual io::pos   tell();
  ///< \ru Зарегистрировать указатель. \en Register the pointer. 
  void              registrate( const TapeBase * e );
  ///< \ru Отменить регистрацию указателя. \en Unregister the pointer. 
  void              unregistrate( const TapeBase * e );
  ///< \ru Есть ли зарегистрированный объект? \en Does a registered object exist? 
  bool              exist ( const TapeBase * e ) const;
  ///< \ru Очистить массив регистрации. \en Flush the registration array. 
  void              flushRegister  ();
  ///< \ru Получить количество зарегистрированных объектов. \en Get the number of registered objects. 
  size_t            RegisteredCount() const;
  ///< \ru Получить максимально возможное количество объектов для регистрации. \en Get the maximal possible number of objects for registration. 
  size_t            GetMaxRegisteredCount() const;
  ///< \ru Зарезервировать память под n объектов. \en Reserve memory for n objects. 
  void              ReserveRegistered( size_t n );
  /// \ru Владеем ли буфером? \en Do we own the buffer? 
  bool              IsOwnBuffer() const;
  /// \ru Установить флаг владения буфером. \en Set the flag of buffer ownership. 
  void              SetOwnBuffer( bool own );

  /// \ru Получить тип индекса. \en Get index type.
  uint8             GetIndexType( size_t index ) const;

  /// \ru Работа с индикатором прогресса. \en Work with progress indicator.

  /// Инициализировать индикатор прогресса. \en Initialize progress indicator.
  void                  InitProgress( IProgressIndicator * pr );
  void                  InitProgress( ProgressBarWrapper & pr );
  /// \ru Освободить текущий индикатор прогресса. Установить родительский индикатор прогресса, если он есть.
  /// \en Release current progress indicator. Set parent progress indicator if it exists.
  void                  ResetProgress(); 
  /// \ru Получить индикатор прогресса. \en Get progress indicator.
  ProgressBarWrapper *  GetProgress();
  /// \ru Завершить индикатор прогресса. \en End the progress indicator.
  void                  FinishProgress();

protected:
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE tape( membuf &, bool openSys, uint8 om, TapeRegistrator * , bool ownReg = false);
  
  /// \ru Конструктор. \en Constructor. 
  tape( iobuf_Seq & buf, bool ownBuf, bool openSys, uint16 om, TapeRegistrator * , bool ownReg = false); //AR(DP)

private:
  /// \ru Открыть системный файл в соответствующем режиме (чтение или запись). \en Open the system file in the appropriate mode (reading or writing). 
  void init( uint8 om );

private:
  tape            ( const tape & ); // \ru запрещено \en forbidden 
  void operator = ( const tape & ); // \ru запрещено \en forbidden 
};
#pragma pack( pop )

//----------------------------------------------------------------------------------------
/** \brief \ru Поток для чтения.
           \en Stream for reading. \~
  \details \ru Поток для чтения. \n
           \en Stream for reading. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS reader : public virtual tape {
public:
  typedef std_unique_ptr<reader>     reader_ptr;
protected:
  /// \ru Конструктор. \en Constructor. 
  reader( iobuf_Seq & buf, bool ownbuf, bool openSys, uint16 om, TapeRegistrator * reg );

  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE reader( iobuf_Seq & buf, bool ownbuf, bool openSys, uint16 om, TapeRegistrator & reg );

  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE reader( membuf & sb, bool openSys, uint8 om, TapeRegistrator & reg );

public:
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE reader( membuf & sb, uint8 om );

  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE reader( iobuf_Seq & buf, uint16 om );
  
  virtual ~reader() {}

public:
  /// \ru Создать читатель для последовательного буфера. \en Create reader for iobuf_Seq.
  static reader_ptr   CreateReader ( std_unique_ptr<iobuf_Seq> buf, uint16 om );

  /// \ru Создать читатель для буфера в памяти. \en Create reader for membuf.
  static reader_ptr   CreateMemReader ( membuf & sb, uint8 om );

public:
  /// \ru Прочитать объект. \en Read the object. 
          TapeBase *  readObject ( TapeBase * mem = 0 );
  /// \ru Прочитать указатель на объект. \en Read a pointer to the object. 
          TapeBase *  readObjectPointer();

  /// \ru Читать каталог объектов. \en Read the object catalog. 
  virtual void        ReadObjectCatalog();
  /// \ru Читать объект по позиции в кластере. \en Read an object by position in cluster. 
  virtual TapeBase *  ReadObjectByPosition ( const ClusterReference & ) { return NULL; }
  /// \ru Установить позицию чтения. \en Set reading position. 
  virtual bool        SetReadPosition ( ClusterReference & ) { return false; } // not supported

  /// \ru Прочитать последовательность байт из буфера. \en Read a sequence of bytes from the buffer. 
  DEPRECATE_DECLARE size_t readSBytes ( void * bf, size_t len );
  
  /// \ru Прочитать беззнаковое 64-разрядное целое \en Read unsigned 64-bit integer. 
          bool        readUInt64( uint64 & );
  /// \ru Прочитать 64-разрядное целое \en Read 64-bit integer.  
          bool        readInt64( int64 & );
  
  /// \ru Прочитать байт из буфера. \en Read a byte from the buffer. 
  virtual int         readByte();
  /// \ru Прочитать последовательность байт из буфера. \en Read a sequence of bytes from the buffer. 
  virtual bool        readBytes( void * bf, size_t len );

  /// \ru Получить указатель на дерево модели. \en Get pointer to the model tree. 
  virtual const c3d::IModelTree * GetModelTree() const { return NULL; } // not supported

  /// \ru Получить признак полного чтения текущего объекта. \en Get indicator of full reading of the current object. 
  /// \ru Установить признак полного чтения текущего объекта. \en Set indicator of full reading of the current object. 
  virtual bool        IsFullRead() { return true; } // not supported
  virtual void        SetFullRead( bool ) {} // not supported

  /// \ru Получить ошибки чтения. \en Get reading errors. 
  virtual uint32      GetLastError();

  // \ru Работа с индикатором прогресса.
  // \en Work with progress indicator.
  void                InitProgress( IProgressIndicator * pr );
  void                InitProgress( ProgressBarWrapper & pr );

protected:
  /// \ru Читаем объект по заданной позиции. \en Read object on defined position. 
  virtual TapeBase *  ReadDetachedObject ();
  /// \ru Регистрируем объект. \en Register the object. 
  virtual void        RegisterObject( TapeBase * obj, uint8 regId, ClusterReference ref = ClusterReference() );
  /// \ru Читаем индекс объекта. \en Read object index. 
          size_t      ReadObjectIndex();

private:
  reader              ( const reader & ); // \ru запрещено \en forbidden 
  reader & operator = ( const reader & ); // \ru запрещено \en forbidden 
};

//----------------------------------------------------------------------------------------
/** \brief \ru Индикатор прогресса в области видимости для reader.
           \en Scoped progress indicator for reader. \~
  \details \ru Индикатор прогресса в области видимости для чтения модели с помощью reader.
               Создается дочерний индикатор прогресса для reader. При выходе из области видимости 
               освобождается текущий индикатор прогресса и устанавливается родительский индикатор прогресса. \n
           \en Scoped progress indicator for reader.
               A scoped child progress indicator for reader is created.
               When exiting the scope, the current progress indicator is released and 
               the parent progress indicator is set. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS ScopedReadProgress
{
  SPtr<ProgressBarWrapper>  _progress;
  reader &                  _reader;
public:
  ScopedReadProgress( reader & in );
  ~ScopedReadProgress();
  // \ru Доступ к индикатору прогресса. \en Access to progress indicator.
  ProgressBarWrapper * operator()();

private:
  ScopedReadProgress();
  void operator = ( const ScopedReadProgress& );
};

//----------------------------------------------------------------------------------------
/** \brief \ru Поток для чтения с возможностью чтения из нескольких FileSpaces по заданным позициям.
           \en Stream for reading from several FileSpaces by given positions in clusters. \~
  \details \ru Поток для чтения с возможностью чтения из разных FileSpaces по заданным позициям. \n
            \en Stream for reading from several FileSpace by given positions in clusters. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS reader_ex : public reader
{
  std_unique_ptr<c3d::IModelTree> m_tree;
  uint32                          m_lastError;
  bool                            m_fullRead;
protected:
  /// \ru Конструктор. \en Constructor. 
  reader_ex( iobuf_Seq & buf, bool ownbuf, bool openSys, uint16 om );

public:
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE reader_ex( membuf & sb, uint8 om );

  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE reader_ex( iobuf_Seq & buf, uint16 om );

  virtual ~reader_ex() {}

public:
  /// \ru Создать экземпляр reader_ex для последовательного буфера. \en Create reader_ex instance for sequential buffer. 
  static std_unique_ptr<reader_ex> CreateReaderEx( std_unique_ptr<iobuf_Seq> buf, uint16 om );

  /// \ru Создать читатель для буфера в памяти. \en Create reader for membuf.
  static std_unique_ptr<reader_ex> CreateMemReaderEx ( membuf & sb, uint8 om );


public:
  /// \ru Читаем каталог объектов. \en Read the object catalog. 
  virtual void        ReadObjectCatalog();
  /// \ru Читать объект по позиции в кластере. \en Read an object by position in cluster. 
  virtual TapeBase *  ReadObjectByPosition ( const ClusterReference& position );
  /// \ru Установить позицию чтения. \en Set reading position. 
  virtual bool        SetReadPosition ( ClusterReference & );

  /// \ru Получить указатель на дерево модели. \en Get pointer to the model tree. 
  virtual const c3d::IModelTree * GetModelTree() const;

  /// \ru Признак полного чтения текущего объекта.
  ///     При чтении произвольного объекта может возникнуть необходимость чтения некоторых данных его родителя.
  ///     В этом случае объект родителя читается не полностью и имеет флаг FullRead = false.
  /// \en Indicator of full reading of the current object.
  ///     While reading an arbitrary object there can be a need to read some data from its parent.
  ///     In this case the parent object is read partially and has the flag FullRead = false.

  /// \ru Получить признак полного чтения текущего объекта. \en Get indicator of full reading of the current object. 
  virtual bool        IsFullRead();
  /// \ru Установить признак полного чтения текущего объекта. \en Set indicator of full reading of the current object. 
  virtual void        SetFullRead( bool full );

  /// \ru Получить ошибки чтения. \en Get reading errors. 
  virtual uint32      GetLastError();

protected:
  /// \ru Читать объект по заданной позиции. \en Read object on defined position. 
  virtual TapeBase *  ReadDetachedObject();
  /// \ru Зарегистрировать объект. \en Register the object. 
  virtual void        RegisterObject( TapeBase * obj, uint8 regId, ClusterReference ref = ClusterReference() );

private:
  reader_ex              ( const reader_ex & ); // \ru запрещено \en forbidden 
  reader_ex & operator = ( const reader_ex & ); // \ru запрещено \en forbidden 
};

//----------------------------------------------------------------------------------------
/** \brief \ru Поток для записи.
           \en Stream for writing. \~
  \details \ru Поток для записи. \n
           \en Stream for writing. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS writer : public virtual tape {
public:
  typedef std_unique_ptr<writer>     writer_ptr;
protected:
  /// \ru Конструктор. \en Constructor. 
  writer ( iobuf_Seq  & buf, bool ownBuf, bool openSys, uint16 om, TapeRegistrator * reg );
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE writer( iobuf_Seq  & buf, bool ownBuf, bool openSys, uint16 om, TapeRegistrator & reg );
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE writer ( membuf & sb, bool openSys, uint8 om, TapeRegistrator & reg );

public:
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE writer ( membuf & sb, uint8  om );
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE writer ( iobuf_Seq & buf, uint16 om );

  virtual ~writer() {}

public:
  /// \ru Создать писатель для последовательного буфера. \en Create writer for iobuf_Seq.
  static writer_ptr   CreateWriter( std_unique_ptr<iobuf_Seq> buf, uint16 om );
  /// \ru Создать писатель для буфера в памяти. \en Create writer for membuf.
  static writer_ptr   CreateMemWriter( membuf & sb, uint8  om );

public:
  /// \ru Записать объект. \en Write the object. 
          void        writeObject( const TapeBase * );
  /// \ru Записать указатель на объект. \en Write the pointer to the object. 
          void        writeObjectPointer( const TapeBase * );

  /// \ru Записать дерево модели. \en Write the model tree. 
  virtual void        WriteModelCatalog();
  /// \ru Выдать следующую позицию записи. \en Get next writing position. 
  virtual ClusterReference GetNextWritePosition () { return ClusterReference(); } // not supported

  /// \ru Записать байт в буфер. \en Write the byte to the buffer. 
  virtual void        writeByte  ( uint8 ch );
  /// \ru Записать последовательность байт в буфер. \en Write the sequence of bytes to the buffer. 
  virtual void        writeBytes ( const void * bf, size_t len );
  /// \ru Записать последовательность байт в буфер. \en Write the sequence of bytes to the buffer. 
  DEPRECATE_DECLARE size_t  writeSBytes( const void * bf, size_t len );
  /// \ru Записать беззнаковое 64-разрядное целое. \en Write unsigned 64-bit integer. \~ \return \ru Возвращает количество записанных байт. \en Returns the number of written bytes. \~
          void        writeUInt64( const uint64 & val );
  /// \ru Записать 64-разрядное целое. \en Write 64-bit integer. \~ \return \ru Возвращает количество записанных байт. \en Returns the number of written bytes. \~
          void        writeInt64 ( const int64 & val );

          // \ru Запись CHAR строки в поток (кодировка ANSI, русская локаль). \en Writing CHAR string to the stream. (ANSI coding, Russian locale).
          writer &  __writeChar ( const char * s );
          // \ru Запись WCHAR строки в поток (в потоке хранится как UTF-16). \en Writing WCHAR string to the stream (stored in the stream as UTF-16).
          writer &  __writeWchar( const TCHAR * s );
          // \ru Запись WCHAR строки в поток (в потоке хранится как UTF-16). \en Writing WCHAR string to the stream (stored in the stream as UTF-16). 
          writer &  __writeWcharT( const wchar_t * s );
          // \ru Длина записи WCHAR строки в поток (в потоке хранится как UTF-16). \en Length of WCHAR string in the stream (stored in the stream as UTF-16).
          size_t    __lenWchar( const TCHAR * s );

  /// \ru Получить указатель на дерево модели. \en Get pointer to the model tree. 
  virtual const c3d::IModelTree * GetModelTree() const { return NULL; } // not supported

protected:
  /// \ru Записать объект и тип. \en Write the object and type. 
  virtual void        WriteObjectAndType  ( const TapeBase * );
  /// \ru Зарегистрировать объект. \en Register the object. 
  virtual void        RegisterObject      ( const TapeBase * );
  /// \ru Завершить запись объекта. \en Finish writing the object. 
  virtual void        EndWriteObject      ( const TapeBase * );
  /// \ru Добавить ссылку на объект в каталог. \en Add reference to the object to the object catalog. 
  virtual void        UpdateObjectCatalog ( const TapeBase * , const ClusterReference & );
  /// \ru Является ли объект регистрируемым. \en Whether the object is registrable.
  virtual bool        IsRegistrable( const TapeBase * mem );
  /// Записать индекс объекта
          void        WriteObjectIndex    ( size_t index );

private:
  writer              ( const writer & ); // \ru запрещено \en forbidden 
  writer & operator = ( const writer & ); // \ru запрещено \en forbidden 
};

//----------------------------------------------------------------------------------------
/** \brief \ru Поток для записи в разные FileSpaces.
\en Stream for writing to several FileSpaces. \~
\details \ru Поток для записи в разные FileSpaces. \n
\en Stream for writing to several FileSpaces. \n \~
\ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS writer_ex : public writer
{
  std_unique_ptr<c3d::IModelTree> m_tree;
  ClusterReference                m_catalogRef;
protected:
  /// \ru Конструктор. \en Constructor. 
  writer_ex ( iobuf_Seq  & buf, bool ownBuf, bool openSys, uint16 om );

public:
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE writer_ex ( membuf & sb, uint8  om );

  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE writer_ex ( iobuf_Seq & buf, uint16 om );

  virtual ~writer_ex() {}

public:
  /// \ru Создать писатель для последовательного буфера. \en Create writer for iobuf_Seq.
  static std_unique_ptr<writer_ex> CreateWriterEx( std_unique_ptr<iobuf_Seq> buf, uint16 om );

  /// \ru Создать писатель для буфера в памяти. \en Create writer for membuf.
  static std_unique_ptr<writer_ex> CreateMemWriterEx( membuf & sb, uint8  om );

public:
  /// \ru Записать дерево модели. \en Write the model tree. 
  virtual void        WriteModelCatalog();
  /// \ru Выдать следующую позицию записи. \en Get next writing position. 
  virtual ClusterReference GetNextWritePosition ();

  /// \ru Получить указатель на дерево модели. \en Get pointer to the model tree. 
  virtual const c3d::IModelTree * GetModelTree () const;

protected:
  /// \ru Записать объект и тип. \en Write the object and type. 
  virtual void        WriteObjectAndType  ( const TapeBase * );
  /// \ru Зарегистрировать объект. \en Register the object. 
  virtual void        RegisterObject      ( const TapeBase * );
  /// \ru Завершить запись объекта. \en Finish writing the object. 
  virtual void        EndWriteObject      ( const TapeBase * );
  /// \ru Добавить ссылку на объект в каталог. \en Add reference to the object to the object catalog. 
  virtual void        UpdateObjectCatalog ( const TapeBase *mem, const ClusterReference& ref );
  /// \ru Является ли объект регистрируемым. \en Whether the object is registrable.
  virtual bool        IsRegistrable( const TapeBase * mem );

private:
  writer_ex              ( const writer_ex & ); // \ru запрещено \en forbidden 
  writer_ex & operator = ( const writer_ex & ); // \ru запрещено \en forbidden 
};

//----------------------------------------------------------------------------------------
/** \brief \ru Поток для чтения и записи.
           \en Stream for reading and writing. \~
  \details \ru Поток для чтения и записи. \n
           \en Stream for reading and writing. \n \~
  \ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS rw : public writer, public reader {
public:
  typedef std_unique_ptr<rw> rw_ptr;
public:
  /// \ru Конструктор. \en Constructor. 
  DEPRECATE_DECLARE rw( membuf & sb, uint8 om );

  /// \ru Создать читатель/писатель для буфера в памяти. \en Create reader/writer for membuf.
  static rw_ptr CreateMemWriter( membuf & sb, uint8  om );
  
  /// \ru Конструктор. \en Constructor. 
  rw( iobuf & buf, uint16 om );

  virtual ~rw() {}

private:
  /// \ru Конструктор. \en Constructor. 
  rw( iobuf_Seq & sb, bool ownBuf, bool openSys, uint16 om, TapeRegistrator * reg );

  rw              ( const rw & ); // \ru запрещено \en forbidden 
  rw & operator = ( const rw & ); // \ru запрещено \en forbidden 
};


//----------------------------------------------------------------------------------------
/** \brief \ru Менеджер потоков.
\en Stream manager. \~
\details \ru Менеджер потоков чтения и записи. \n
\en Reading and writing streams manager. \n \~
\ingroup Base_Tools_IO
*/
// ---
class MATH_CLASS TapeManager {
private:
  //static TPointer<TapeManager> &  StaticTapeManager();
protected :
  TapeClass * currentClass; ///< \ru Указатель на объект потокового класса. \en A pointer to the object of stream class. 
protected :
  /// \ru Конструктор. \en Constructor. 
  TapeManager();
  /// \ru Конструктор копирования. \en Copy constructor. 
  TapeManager( const TapeManager & );
public :
  /// \ru Деструктор. \en Destructor. 
  virtual ~TapeManager() {}
public:
  /// \ru Чтение экземпляра. \en Reading of the instance. 
  bool            SpecimenReading             ( reader & r,       TapeBase & o ) const;
  /// \ru Запись экземпляра. \en Writing of the instance. 
  bool            SpecimenWriting             ( writer & w, const TapeBase & o ) const;
  /// \ru Установить текущим класс по упакованному имени класса. \en Set class as default one by packed class name. 
  bool            SetCurrentClassByDescriptor     ( const ClassDescriptor & descr );
  /// \ru Установить текущим класс по упакованному имени класса. \en Set class as default one by packed class name. 
  bool            SetCurrentClassByDescriptor ( const ClassDescriptor & descr, const VersionContainer & ver );
  /// \ru Установить текущим класс по имени класса. \en Set class to be current by class name. 
  //bool            SetCurrentClassByName       ( const char * name );
  /// \ru Создать объект потокового класса. \en Create an object of a stream class. 
  TapeBase *      BuildObject                 () const;   
  /// \ru Есть ли функция записи у класса? \en Is there the writing function in the class? 
  bool            HasWriter                   () const;
  /// \ru Получить упакованное имя класс для записи в версию. \en Get packed class name for writing to the version. 
  ClassDescriptor GetPackedClassNameForWrite  ( VERSION version ) const;

  /// \ru Отпустить менеджер потоков после использования. \en Release the stream manager after using. 
  virtual void    FreeTapeManager();

  /// \ru Получить ссылку на менеджер потоков. \en Get a reference to the stream manager. 
  static TapeManager & GetTapeManager();

private:
  TapeManager & operator = ( const TapeManager & );
};


//----------------------------------------------------------------------------------------
/** \brief \ru Массив регистрации потоковых классов.
\en Array of stream classes registration. \~
\details \ru Массив регистрации потоковых классов TapeClass. \n
\en Array of stream TapeClass classes registration. \n \~
\ingroup Base_Tools_IO
*/
// ---
struct TapeClassContainer 
{
  /// \ru Создать массив регистрации потоковых классов. \en Create an array of stream classes registration. 
  static EXPORT_DECLARATION TPointer< SFDPArray<TapeClass> > & CALL_DECLARATION StaticTapeClassContainer();

  /// \ru Добавить потоковый класс. \en Add a stream class. 
  static bool Add( TapeClass & tapeClass )
  {
    if ( !StaticTapeClassContainer() )
      StaticTapeClassContainer() = new SFDPArray<TapeClass>( 430, 1, TapeClass_Compare, NULL ); // \ru не владеет \en doesn't own 

    return StaticTapeClassContainer()->AddExact( tapeClass );
  }
  /// \ru Функция сравнения двух TapeClass для поиска. \en Function of two TapeClass comparison for a search. 
  static int  TapeClass_Search( const TapeClass & t1, size_t d ) 
  {
    return ( ( t1.hashValue == *(ClassDescriptor*)d ) ? 0 : (( t1.hashValue > *(ClassDescriptor*)d ) ? 1 : -1 ) );
  }
  /// \ru Функция сравнения двух TapeClass для сортировки при вставке. \en Function of two TapeClass comparison for sorting while inserting. 
  static int  TapeClass_Compare( const TapeClass & t1, const TapeClass & t2 ) 
  {
    return ( ( t1.hashValue == t2.hashValue ) ? 0 : (( t1.hashValue > t2.hashValue ) ? 1 : -1 ) );
  }
};


//----------------------------------------------------------------------------------------
/// \ru Функция чтения базового класса. \en Function of reading the base class. \~ \ingroup Base_Tools_IO
// ---
template <class Base>
inline void ReadBase( reader & in, Base * base ) {
  Base::Read( in, base );
}

//----------------------------------------------------------------------------------------
/// \ru Функция записи базового класса. \en Function of writing the base class. \~ \ingroup Base_Tools_IO
// ---
template <class Base>
inline void WriteBase( writer & out, const Base * base ) {
  Base::Write( out, base );
}


//----------------------------------------------------------------------------------------
/// \ru Функция чтения виртуального базового класса. \en Function of reading of a virtual base class. \~ \ingroup Base_Tools_IO
// ---
template <class Base>
void ReadVBase( reader & in, Base * base )
{
  switch( in.readByte() ) {
    case tape::otIndexed:
      break;
    case tape::otObject :
      in.registrate( dynamic_cast<TapeBase*>(base) );
      Base::Read( in, base );
      break;
  }
}


//----------------------------------------------------------------------------------------
/// \ru Функция записи виртуального базового класса. \en Function of writing of a virtual base class. \~ \ingroup Base_Tools_IO
// ---
template <class Base>
void WriteVBase( writer & out, const Base * base )
{
  if ( !out.good() )
    return;
  if ( out.exist( dynamic_cast<TapeBase*>(base) ) )
    out.writeByte( tape::otIndexed );
  else {
    out.registrate( dynamic_cast<TapeBase*>(base) );
    out.writeByte( tape::otObject );
    Base::Write( out, base );
  }
}


//----------------------------------------------------------------------------------------
/**
  \brief  \ru Дружественные операторы чтения и записи указателей и ссылок. 
          \en Friend operators of reading and writing of pointers and references. \~ 
  \ingroup Base_Tools_IO
*/
// ---
#define DECLARE_PERSISTENT_OPS( Class )                                                     \
  friend inline reader & CALL_DECLARATION operator >> ( reader & in, Class & ref ) {        \
    in.readObject( dynamic_cast<TapeBase *>(&ref) );                                        \
    return in;                                                                              \
  }                                                                                         \
  friend inline reader & CALL_DECLARATION operator >> ( reader & in, Class *& ptr ) {       \
    ptr = dynamic_cast<Class *>( in.readObjectPointer() );                                  \
    return in;                                                                              \
  }                                                                                         \
  friend inline reader & CALL_DECLARATION operator >> ( reader & in, const Class *& ptr )   \
  {                                                                                         \
    ptr = dynamic_cast<Class *>( in.readObjectPointer() );                                  \
    return in;                                                                              \
  }                                                                                         \
  friend inline writer & CALL_DECLARATION operator << ( writer & out, const Class & ref ) { \
    out.writeObject( dynamic_cast<const TapeBase *>(&ref) );                                \
    return out;                                                                             \
  }                                                                                         \
  friend inline writer & CALL_DECLARATION operator << ( writer & out, const Class * ptr ) { \
    out.writeObjectPointer( dynamic_cast<const TapeBase*>(ptr) );                           \
    return out;                                                                             \
  }                                                                                         \
  friend inline writer & CALL_DECLARATION operator << ( writer & out, Class & ref ) {       \
    out.writeObject( dynamic_cast<TapeBase *>(&ref) );                                      \
    return out;                                                                             \
  }                                                                                         \
  friend inline writer & CALL_DECLARATION operator << ( writer& out, Class * ptr ) {        \
    out.writeObjectPointer( dynamic_cast<TapeBase *>(ptr) );                                \
    return out;                                                                             \
  }

/**
  \brief  \ru Объявление операторов чтения и записи указателей и ссылок.
          \en Declaration of operators of reading and writing of pointers and references. \~
  \ingroup Base_Tools_IO
*/
// ---
#define DECLARE_PERSISTENT_OPS_B( Class )                                                     \
  friend inline reader & CALL_DECLARATION operator >> ( reader & in, Class & ref );         \
  friend inline reader & CALL_DECLARATION operator >> ( reader & in, Class *& ptr );        \
  friend inline reader & CALL_DECLARATION operator >> ( reader & in, const Class *& ptr );  \
  friend inline writer & CALL_DECLARATION operator << ( writer & out, const Class & ref );  \
  friend inline writer & CALL_DECLARATION operator << ( writer & out, const Class * ptr );  \
  friend inline writer & CALL_DECLARATION operator << ( writer & out, Class & ref );        \
  friend inline writer & CALL_DECLARATION operator << ( writer& out, Class * ptr );

//----------------------------------------------------------------------------------------
/**
  \brief \ru Операторы чтения и записи указателей и ссылок.
         \en  Operators of reading and writing of pointers and references. \~
  \ingroup Base_Tools_IO
*/
// ---
#ifdef __BORLANDC__
#define IMPL_PERSISTENT_OPS( Class )                                                     \
  inline reader & CALL_DECLARATION operator >> ( reader & in, Class & ref ) {        \
    in.readObject( dynamic_cast<TapeBase *>(&ref) );                                        \
    return in;                                                                              \
  }                                                                                         \
  inline reader & CALL_DECLARATION operator >> ( reader & in, Class *& ptr ) {       \
    ptr = dynamic_cast<Class *>( in.readObjectPointer() );                                  \
    return in;                                                                              \
  }                                                                                         \
  inline reader & CALL_DECLARATION operator >> ( reader & in, const Class *& ptr )   \
  {                                                                                         \
    ptr = dynamic_cast<Class *>( in.readObjectPointer() );                                  \
    return in;                                                                              \
  }                                                                                         \
  inline writer & CALL_DECLARATION operator << ( writer & out, const Class & ref ) { \
    out.writeObject( dynamic_cast<const TapeBase *>(&ref) );                                \
    return out;                                                                             \
  }                                                                                         \
  inline writer & CALL_DECLARATION operator << ( writer & out, const Class * ptr ) { \
    out.writeObjectPointer( dynamic_cast<const TapeBase*>(ptr) );                           \
    return out;                                                                             \
  }                                                                                         \
  inline writer & CALL_DECLARATION operator << ( writer & out, Class & ref ) {       \
    out.writeObject( dynamic_cast<TapeBase *>(&ref) );                                      \
    return out;                                                                             \
  }                                                                                         \
  inline writer & CALL_DECLARATION operator << ( writer& out, Class * ptr ) {        \
    out.writeObjectPointer( dynamic_cast<TapeBase *>(ptr) );                                \
    return out;                                                                             \
  }
#else
#define IMPL_PERSISTENT_OPS( Class )
#endif

//----------------------------------------------------------------------------------------
/**
  \brief  \ru Операторы чтения указателей и ссылок для класса без записи. 
          \en Operators of reading pointers and references for a class without writing. \~ 
  \ingroup Base_Tools_IO
*/
// ---
#define DECLARE_PERSISTENT_RO_OPS( Class )                                            \
  friend inline reader & CALL_DECLARATION operator >> ( reader & in, Class & ref ) {  \
    in.readObject( dynamic_cast<TapeBase *>(&ref) );                                  \
    return in;                                                                        \
  }                                                                                   \
  friend inline reader & CALL_DECLARATION operator >> ( reader & in, Class *& ptr ) { \
    ptr = dynamic_cast<Class *>( in.readObjectPointer() );                            \
    return in;                                                                        \
  }

//----------------------------------------------------------------------------------------
/// \ru Функции чтения и записи. \en Functions of reading and writing. \~ \ingroup Base_Tools_IO
// ---
#define DECLARE_PERSISTENT_FUNCS( Class )                 \
  public:                                                 \
    static void Read ( reader & in,  Class * obj );       \
    static void Write( writer & out, const Class * obj )

//----------------------------------------------------------------------------------------
/// \ru Функции чтения для класса без записи. \en Function of reading for class without writing. \~ \ingroup Base_Tools_IO
// ---
#define DECLARE_PERSISTENT_RO_FUNCS( Class )      \
  public:                                         \
    static void Read( reader & in, Class * obj )

//------------------------------------------------------------------------------
/// \ru Функции получения дескриптора класса. \~ \ingroup Base_Tools_IO
// ---
#define DECLARE_CLASS_DESC_FUNC( Class )      \
  public:                                     \
    virtual ClassDescriptor GetClassDescriptor( const VersionContainer & ) const;

//------------------------------------------------------------------------------
/// \ru Функции получения дескриптора (хэш + APP UID) класса. \~ \ingroup Base_Tools_IO
// ---
#define IMP_CLASS_DESC_FUNC( AppID, Class )                                   \
  ClassDescriptor Class::GetClassDescriptor( const VersionContainer & v) const \
    { return ClassDescriptor( GetPureName(v), AppID ); }

//----------------------------------------------------------------------------------------
/// \ru Конструктор для потокового класса. \en Constructor for a stream class. \~ \ingroup Base_Tools_IO
// ---
#define DECLARE_PERSISTENT_CTOR( Class )  \
  public:                                 \
    Class( TapeInit )

//----------------------------------------------------------------------------------------
/// \ru Конструктор для потокового класса. \en Constructor for a stream class. \~ \ingroup Base_Tools_IO
// ---
#define IMP_PERSISTENT_CTOR( Class )  \
  Class::Class( TapeInit ) {}

//----------------------------------------------------------------------------------------
/// \ru Конструктор для класса с одной потоковой базой. \en Constructor for a class with one stream base. \~ \ingroup Base_Tools_IO
// ---
#define IMP_PERSISTENT_CTOR1( Class, Base )       \
  Class::Class( TapeInit ) : Base( tapeInit ) {}

//----------------------------------------------------------------------------------------
/// \ru Конструктор для класса с двумя потоковыми базами. \en Constructor for a class with two stream bases. \~ \ingroup Base_Tools_IO
// ---
#define IMP_PERSISTENT_CTOR2( Class, Base1, Base2 )                   \
  Class::Class( TapeInit ) : Base1( tapeInit ), Base2( tapeInit ) {}

//----------------------------------------------------------------------------------------
/** \brief \ru Конструирование нового экземпляра класса.
           \en Construction of a new instance of the class. \~
  \details \ru Конструирование нового экземпляра класса. \n
    Определяются функция конструирования нового экземпляра класса,
    функция преобразования от указателя на TapeBase к указателю на класс
    и класс (не экземпляр!) добавляется в массив потоковых 
    путем создания переменной r ## Class типа TapeClass 
    (а в конструкторе TapeClass производится 
    добавление в массив потоковых классов).
    Символ ## - это указание препроцессору о необходимости "склейки" 
    текущего идентификатора с последующим.
           \en Construction of a new instance of the class. \n
    Definition of functions of construction a new instance of the class,
    function of conversion from a pointer to TapeBase to a pointer to the class
    and addition of the class (not an instance) to the array of stream classes 
    by creating variable r ## Class of type TapeClass 
    (and in constructor of TapeClass 
    addition to array of stream classes is performed).
    Symbol ## is a directive for preprocessor about the necessity of "glueing" 
    of the current identifier with the next one. \~
  \ingroup Base_Tools_IO
*/
// ---
#define IMP_PERSISTENT_REGISTRATION( AppID, Class )                     \
  TapeBase * CALL_DECLARATION make ## _ ## Class () {                   \
    return new Class(tapeInit);                                         \
  }                                                                     \
  void * CALL_DECLARATION cast ## _ ## Class ( const TapeBase * obj ) { \
    return dynamic_cast<Class *>(const_cast<TapeBase *>(obj) );         \
  }                                                                     \
                                                                        \
  TapeClass  r ## Class(                                                \
    typeid(Class).name(),                                               \
    AppID,                                                              \
    (BUILD_FUNC) make ## _ ## Class,                                    \
    (CAST_FUNC ) cast ## _ ## Class,                                    \
    (READ_FUNC ) Class::Read,                                           \
    (WRITE_FUNC) Class::Write                                           \
  )

//------------------------------------------------------------------------------
// \ru Как записать переименованный класс в старую версию (с) Столяров А.Г. \en How to write the renamed class to the old version (c) Stolyarov A.G. 
/* #define IMP_PERSISTENT_REGISTRATION_OLDCLASS( Class, OldClass )         \
  TapeBase * CALL_DECLARATION make ## _ ## Class () {                   \
    return dynamic_cast<TapeBase *>( new Class(tapeInit) );             \
  }                                                                     \
  void * CALL_DECLARATION cast ## _ ## Class ( const TapeBase * obj ) { \
    return dynamic_cast<Class *>(const_cast<TapeBase *>(obj) );         \
  }                                                                     \
  TapeClass  r ## Class(                                                \
    typeid(Class).name(),                                               \
    typeid(OldClass).name(),                                            \
    (BUILD_FUNC) make ## _ ## Class,                                    \
    (CAST_FUNC ) cast ## _ ## Class,                                    \
    (READ_FUNC ) Class::Read,                                           \
    (WRITE_FUNC) Class::Write                                           \
  )

#define IMP_PERSISTENT_OLDCLASS( Class, OldClass )         \
  IMP_PERSISTENT_REGISTRATION_OLDCLASS( Class, OldClass ); \
  IMP_PERSISTENT_NEW_DELETE_CLASS( Class )

IMP_PERSISTENT_OLDCLASS( Class, OldClass );

class TapeClassForNewObjects : public TapeClass {
protected :
  ClassDescriptor hashValueOld;  // \ru упакованное имя класса для старой версии файла \en packed class name for the old version of file
public :
  TapeClassForNewObjects( const char * name, const char * oldName, BUILD_FUNC b, CAST_FUNC c, READ_FUNC r, WRITE_FUNC w );
  virtual ~TapeClassForNewObjects();
  virtual ClassDescriptor GetPackedClassNameForWrite( long version ) const; 
  OBVIOUS_PRIVATE_COPY(TapeClassForNewObjects);
};

TapeClassForNewObjects::TapeClassForNewObjects( const char * name, const char * oldName, 
                                                BUILD_FUNC b, CAST_FUNC c, READ_FUNC r, WRITE_FUNC w ) 
  : TapeClass( name, b, c, r, w )
  , hashValueOld( ::hash(::pureName( oldName ) ) )
{
}

ClassDescriptor TapeClassForNewObjects::GetPackedClassNameForWrite( long version ) const { 
  uint16 res = version > CHANGE_VERSION ? TapeClass::GetPackedClassName() : uint16(hashValueOld);
  return res;
}
*/

//----------------------------------------------------------------------------------------
/// \ru Конструирование нового экземпляра класса для класса без записи. \en Construction of a new instance of the class for a class without writing. \~ \ingroup Base_Tools_IO
// ---
#define IMP_PERSISTENT_RO_REGISTRATION( AppID, Class )                    \
  TapeBase * CALL_DECLARATION make ## _ ## Class () {                     \
    return new Class(tapeInit);                                           \
  }                                                                       \
  void * CALL_DECLARATION cast ## _ ## Class ( const TapeBase * obj ) {   \
    return dynamic_cast<Class*>(const_cast<TapeBase *>(obj) );            \
  }                                                                       \
  TapeClass  r ## Class(                                                  \
    typeid(Class).name(),                                                 \
    AppID,                                                                \
    (BUILD_FUNC) make ## _ ## Class,                                      \
    (CAST_FUNC ) cast ## _ ## Class,                                      \
    (READ_FUNC ) Class::Read,                                             \
    (WRITE_FUNC) 0                                                        \
  )

/** \brief \ru Переменная включает перегрузку операторов new/delete,
           обеспечивающую последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков.
           \en The variable enables overloading of new/delete operators
           which provides sequential access to the allocation/deallocation functions
           from different threads. \~
  \details \ru Переменная включает перегрузку операторов new/delete,
           обеспечивающую последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков.
           \en The variable enables overloading of new/delete operators
           which provides sequential access to the allocation/deallocation functions
           from different threads. \~
\ingroup Base_Tools_IO
*/
// ---
#define __OVERLOAD_MEMORY_ALLOCATE_FREE_

#ifdef __DEBUG_MEMORY_ALLOCATE_FREE_
  //----------------------------------------------------------------------------------------
  /// \ru Объявление функций new, delete и операторов доступа. \en Declaration of functions new, delete and access operators.  \~ \ingroup Base_Tools_IO
  // \ru операторы * и -> автоматически не перегружаются, \en operators * and -> are not overloaded automatically,  
  // \ru для их использования нужно писать примерно так: \n \en one should write like this to use them: \n 
  // \ru вместо ptr->F();   ptr->operator ->()->F();     \n \en instead of ptr->F();   ptr->operator ->()->F();     \n 
  // \ru или                ptr->operator *().F();       \n \en or                ptr->operator *().F();       \n 
  // \ru или                ptr->operator Class*()->F(); \n \en or                ptr->operator Class*()->F(); \n 
  // \ru Для ссылок так же. \en Similarly for references. 
  // ---
  #define DECLARE_NEW_DELETE_CLASS( Class )        \
    public:                                        \
    void  * operator new       ( size_t );         \
    void    operator delete    ( void *, size_t ); \
    void  * operator new    [] ( size_t );         \
    void    operator delete [] ( void * );         

  //--------------------------------------------------------------------------------------
  /// \ru Реализация функций new, delete и операторов доступа. \en Implementation of functions new, delete and access operators.  \~ \ingroup Base_Tools_IO
  // ---
  #define IMP_PERSISTENT_NEW_DELETE_CLASS( Class )               \
    void * Class::operator new( size_t size ) {                  \
      return ::Allocate( size, typeid(Class).name() ); }         \
    void Class::operator delete ( void *ptr, size_t size ) {     \
      ::Free( ptr, size, typeid(Class).name() ); }               \
                                                                 \
    void * Class::operator new[] ( size_t size ) {               \
      return ::AllocateArray( size, typeid(Class[]).name()); }   \
    void Class::operator delete[] ( void *ptr ) {                \
      ::FreeArray( ptr, typeid(Class[]).name() ); }              

  //--------------------------------------------------------------------------------------
  /// \ru Объявление операторов new и delete, обеспечивающих последовательное обращение
  /// к функциям выделения/освобождения памяти из разных потоков.
  /// \en Declaration of new and delete operators which provide sequential access
  /// to the allocation/deallocation functions from different threads.  \~
  /// \ingroup Base_Tools_IO
  // ---
  #define DECLARE_NEW_DELETE_CLASS_EX( Class )

  //--------------------------------------------------------------------------------------
  /// \ru Реализация операторов new и delete, обеспечивающих последовательное обращение
  ///  к функциям выделения/освобождения памяти из разных потоков.
  /// \en Implementation of new and delete operators which provide sequential access
  /// to the allocation/deallocation functions from different threads.  \~
  /// \ingroup Base_Tools_IO
  // ---
  #define IMP_PERSISTENT_NEW_DELETE_CLASS_EX( Class )

#else // __DEBUG_MEMORY_ALLOCATE_FREE_
  //--------------------------------------------------------------------------------------
  /// \ru Объявление функций new, delete и операторов доступа. \en Declaration of functions new, delete and access operators.  \~ \ingroup Base_Tools_IO
  // ---
  #define DECLARE_NEW_DELETE_CLASS( Class )
  //--------------------------------------------------------------------------------------
  /// \ru Реализация функций new, delete и операторов доступа. \en Implementation of functions new, delete and access operators.  \~ \ingroup Base_Tools_IO
  // ---
  #define IMP_PERSISTENT_NEW_DELETE_CLASS( Class )

#if defined(__OVERLOAD_MEMORY_ALLOCATE_FREE_) && !defined(C3D_DEBUG)

  //--------------------------------------------------------------------------------------
  /// \ru Объявление операторов new и delete, обеспечивающих последовательное обращение
  /// к функциям выделения/освобождения памяти из разных потоков.
  /// Перегружаются все стандартные операторы new и delete.
  /// \en Declaration of new and delete operators which provide sequential access
  /// to the allocation/deallocation functions from different threads.
  /// All standard new and delete operators are overloaded. \~
  /// \ingroup Base_Tools_IO
  // ---
  #define DECLARE_NEW_DELETE_CLASS_EX( Class )                            \
    public:                                                               \
    void * operator new       ( size_t );                                 \
    void * operator new       ( size_t, const std::nothrow_t & ) throw(); \
    void * operator new       ( size_t, void * );                         \
    void * operator new []    ( size_t );                                 \
    void * operator new []    ( size_t, const std::nothrow_t & ) throw(); \
    void * operator new []    ( size_t, void * );                         \
    void   operator delete    ( void * );                                 \
    void   operator delete    ( void *, const std::nothrow_t & ) throw(); \
    void   operator delete    ( void *, void* );                          \
    void   operator delete [] ( void * );                                 \
    void   operator delete [] ( void *, const std::nothrow_t & ) throw(); \
    void   operator delete [] ( void *, void * );

  //--------------------------------------------------------------------------------------
  /// \ru Реализация операторов new и delete, обеспечивающая последовательное обращение
  ///  к функциям выделения/освобождения памяти из разных потоков.
  /// Перегружаются все стандартные операторы new и delete.
  /// \en Implementation of new and delete operators which provides sequential access
  /// to the allocation/deallocation functions from different threads.
  /// All standard new and delete operators are overloaded. \~
  /// \ingroup Base_Tools_IO
  // ---
  #define IMP_PERSISTENT_NEW_DELETE_CLASS_EX( Class )          \
    void* Class::operator new( size_t size ) {                 \
      SET_MEMORY_SCOPED_LOCK;                                  \
      return ::operator new( size ); }                         \
    void Class::operator delete( void *ptr ) {                 \
      SET_MEMORY_SCOPED_LOCK;                                  \
      ::operator delete( ptr ); }                              \
                                                               \
    void* Class::operator new( size_t size, void *ptr ) {      \
      SET_MEMORY_SCOPED_LOCK;                                  \
      return ::operator new( size, ptr ); }                    \
    void Class::operator delete( void *ptr, void *ptr2 ) {     \
      SET_MEMORY_SCOPED_LOCK;                                  \
      ::operator delete( ptr, ptr2 ); }                        \
                                                               \
    void* Class::operator new[]( size_t size ) {               \
      SET_MEMORY_SCOPED_LOCK;                                  \
      return ::operator new[]( size ); }                       \
    void Class::operator delete[]( void *ptr ) {               \
      SET_MEMORY_SCOPED_LOCK;                                  \
      ::operator delete[]( ptr ); }                            \
                                                               \
    void* Class::operator new []( size_t size, void *ptr ) {   \
      SET_MEMORY_SCOPED_LOCK;                                  \
      return ::operator new[]( size, ptr ); }                  \
    void Class::operator delete []( void *ptr, void *ptr2 ) {  \
      SET_MEMORY_SCOPED_LOCK;                                  \
      ::operator delete[]( ptr, ptr2 ); }                      \
                                                               \
    void* Class::operator new( size_t size, const std::nothrow_t &nt ) throw() {    \
      SET_MEMORY_SCOPED_LOCK;                                                       \
      return ::operator new( size, nt ); }                                          \
    void Class::operator delete( void *ptr, const std::nothrow_t &nt ) throw() {    \
      SET_MEMORY_SCOPED_LOCK;                                                       \
      ::operator delete( ptr, nt ); }                                               \
                                                                                    \
    void* Class::operator new []( size_t size, const std::nothrow_t &nt ) throw() { \
      SET_MEMORY_SCOPED_LOCK;                                                       \
      return ::operator new[]( size, nt ); }                                        \
    void Class::operator delete []( void *ptr, const std::nothrow_t &nt ) throw() { \
      SET_MEMORY_SCOPED_LOCK;                                                       \
      ::operator delete[]( ptr, nt ); }
                                                      
#else // __OVERLOAD_MEMORY_ALLOCATE_FREE_

  //--------------------------------------------------------------------------------------
  /// \ru Объявление операторов new и delete, обеспечивающих последовательное обращение
  /// к функциям выделения/освобождения памяти из разных потоков.
  /// \en Declaration of new and delete operators which provide sequential access
  /// to the allocation/deallocation functions from different threads.  \~
  /// \ingroup Base_Tools_IO
  // ---
  #define DECLARE_NEW_DELETE_CLASS_EX( Class )
  
  //--------------------------------------------------------------------------------------
  /// \ru Реализация операторов new и delete, обеспечивающая последовательное обращение
  ///  к функциям выделения/освобождения памяти из разных потоков.
  /// \en Implementation of new and delete operators which provides sequential access
  /// to the allocation/deallocation functions from different threads.  \~
  /// \ingroup Base_Tools_IO
  // ---
  #define IMP_PERSISTENT_NEW_DELETE_CLASS_EX( Class )

#endif // __OVERLOAD_MEMORY_ALLOCATE_FREE_

#endif // __DEBUG_MEMORY_ALLOCATE_FREE_

//------------------------------------------------------------------------------
/** \brief \ru Объявление класса Class поточным.
           \en Declaration of class Class as a stream one. \~
  \details \ru Объявление класс Class поточным.
    Устанавливается в декларации класса в файле *.h.
    Декларирует операторы <<, >>, а также функции Read и Write,
    которые должны быть определены в любом файле *.cpp
    Class должен наследовать от TapeBase.
    Для этого класса должен быть определен конструктор чтения,
    а его тело должно быть в .cpp файле. \n
           \en Declaration of class Class as a stream one.
    It is set in the declaration of class in file *.h.
    Declares operators <<, >> and also functions Read and Write
    which must be defined in any file *.cpp
    Class must be inherited from TapeBase.
    The read constructor must be defined for the class
    and its solid should be in .cpp file. \n \~
  \ingroup Base_Tools_IO
*/
// ---
#ifndef __BORLANDC__

#define DECLARE_PERSISTENT_CLASS( Class )    \
  DECLARE_PERSISTENT_FUNCS( Class );         \
  DECLARE_PERSISTENT_OPS( Class );           \
  DECLARE_PERSISTENT_CTOR( Class );          \
  DECLARE_NEW_DELETE_CLASS( Class );         \
  DECLARE_CLASS_DESC_FUNC(Class)

#else  // __BORLAND__

#define DECLARE_PERSISTENT_CLASS( Class )    \
  DECLARE_PERSISTENT_FUNCS( Class );         \
  DECLARE_PERSISTENT_OPS_B( Class );         \
  DECLARE_PERSISTENT_CTOR( Class );          \
  DECLARE_NEW_DELETE_CLASS( Class );         \
  DECLARE_CLASS_DESC_FUNC(Class)

#endif // __BORLAND__

/** \brief \ru Аналог макроса DECLARE_PERSISTENT_CLASS
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков.
           \en Analog of DECLARE_PERSISTENT_CLASS macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads. \~
\details \ru Аналог макроса DECLARE_PERSISTENT_CLASS
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков
           (включается переменной __OVERLOAD_MEMORY_ALLOCATE_FREE_).
           \en Analog of DECLARE_PERSISTENT_CLASS macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads
           (enabled by defining __OVERLOAD_MEMORY_ALLOCATE_FREE_). \~
\ingroup Base_Tools_IO
*/
// ---
#define DECLARE_PERSISTENT_CLASS_NEW_DEL( Class ) \
  DECLARE_PERSISTENT_CLASS( Class )               \
  DECLARE_NEW_DELETE_CLASS_EX( Class )

//------------------------------------------------------------------------------
/** \brief \ru Реализация объявления DECLARE_PERSISTENT_CLASS.
           \en Implementation of DECLARE_PERSISTENT_CLASS declaration. \~
  \details \ru Реализация объявления DECLARE_PERSISTENT_CLASS.
    Описывает необходимые действия для поточного класса.
    Устанавливается в любой .cpp файл.
    Class должен наследовать от TapeBase.
    Должны быть реализованы функции чтения Read и записи Write. \n
           \en Implementation of DECLARE_PERSISTENT_CLASS declaration.
    Describes the necessary operations for a stream class.
    It is set into any .cpp file.
    Class must be inherited from TapeBase.
    Function Read of reading and function Write of writing should be implemented. \n \~
  \ingroup Base_Tools_IO
*/
// ---
#define IMP_PERSISTENT_CLASS( AppID, Class )   \
  IMP_PERSISTENT_REGISTRATION( AppID, Class ); \
  IMP_PERSISTENT_NEW_DELETE_CLASS( Class );    \
  IMP_CLASS_DESC_FUNC( AppID, Class )

/** \brief \ru Аналог макроса IMP_PERSISTENT_CLASS
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков.
           \en Analog of IMP_PERSISTENT_CLASS macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads. \~
  \details \ru Аналог макроса IMP_PERSISTENT_CLASS
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков
           (включается переменной __OVERLOAD_MEMORY_ALLOCATE_FREE_).
           \en Analog of IMP_PERSISTENT_CLASS macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads
           (enabled by defining __OVERLOAD_MEMORY_ALLOCATE_FREE_). \~
  \ingroup Base_Tools_IO
*/
// ---
#define IMP_PERSISTENT_CLASS_NEW_DEL( AppID, Class ) \
  IMP_PERSISTENT_CLASS( AppID, Class );              \
  IMP_PERSISTENT_NEW_DELETE_CLASS_EX( Class );

//----------------------------------------------------------------------------------------
// \ru Описывает необходимые действия для поточного класса без записи \en Describes the necessary operations for a stream class without writing. 
// \ru Устанавливается в любой .cpp файл \en It is set to any .cpp file 
// \ru Примечание : \en Note: 
// \ru 1. Class должен наследовать от TapeBase \en 1. Class must be inherited from TapeBase 
// \ru 2. Требуется наличие функций \en 2. There must be the following functions 
//      - void Class:Read( reader& in, Class* obj );
//      - void Class::Write( writer& out, const Class* obj );
// \ru где Class - имя класса \en where Class is a class name 
// ---
#define IMP_PERSISTENT_RO_CLASS( AppID, Class )      \
  IMP_PERSISTENT_RO_REGISTRATION( AppID, Class );    \
  IMP_PERSISTENT_NEW_DELETE_CLASS( Class )

//------------------------------------------------------------------------------
/** \brief \ru Аналог макроса IMP_PERSISTENT_RO_CLASS
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков.
           \en Analog of IMP_PERSISTENT_RO_CLASS macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads. \~
  \details \ru Аналог макроса IMP_PERSISTENT_RO_CLASS
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков
           (включается переменной __OVERLOAD_MEMORY_ALLOCATE_FREE_).
           \en Analog of IMP_PERSISTENT_RO_CLASS macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads
           (enabled by defining __OVERLOAD_MEMORY_ALLOCATE_FREE_). \~
  \ingroup Base_Tools_IO
*/
// ---
#define IMP_PERSISTENT_RO_CLASS_NEW_DEL( AppID, Class ) \
  IMP_PERSISTENT_RO_CLASS( AppID, Class );              \
  IMP_PERSISTENT_NEW_DELETE_CLASS_EX( Class )

//----------------------------------------------------------------------------------------
// \ru Описывает необходимые операции для абстрактного \en Describes the necessary operations for abstract 
// \ru поточного класса \en stream class 
// \ru Устанавливается в любой .cpp файл \en It is set to any .cpp file 
// \ru Примечание : \en Note: 
// \ru 1. Class должен наследовать от TapeBase \en 1. Class must be inherited from TapeBase 
// \ru 2. Требуется наличие функций \en 2. There must be the following functions 
//      - void Class::Read( reader& in, Class* obj );
//      - void Class::Write( writer& out, const Class* obj );
// \ru где Class - имя класса \en where Class is a class name 
// ---
#define IMP_A_PERSISTENT_CLASS( AppID, Class ) \
  IMP_PERSISTENT_NEW_DELETE_CLASS( Class )     \
  IMP_CLASS_DESC_FUNC( AppID, Class )

//----------------------------------------------------------------------------------------
// \ru Описывает необходимые операции абстрактного поточного класса, \en Describes the necessary operations for the abstract stream class 
// \ru наследующего от другого такого же, и у которого \en inherited from another class which is the same and which 
// \ru нет своих полей данных для записи в поток \en has no its own data fields for writing to stream 
// \ru Устанавливается в любой .cpp файл \en It is set to any .cpp file 
// \ru Примечание : \en Note: 
// \ru 1. Class должен наследовать от TapeBase \en 1. Class must be inherited from TapeBase 
// \ru 2. Требуется (!!!) отсутствие (!!!) функций \en 2. The following functions must be (!!!) absent (!!!) 
//      - void Class::Read( reader& in, Class* obj );
//      - void Class::Write( writer& out, const Class* obj );
// \ru где Class - имя класса \en where Class is a class name 
// \ru эти функции генерируются автоматически \en these functions are generated automatically 
// ---
#define IMP_A_PERSISTENT_CLASS_FROM_BASE( AppID, Class, Base )   \
  void Class::Read( reader & in, Class * obj ) {                 \
    Base::Read( in, obj );                                       \
  }                                                              \
  void Class::Write( writer & out, const Class * obj ) {         \
    Base::Write( out, obj );                                     \
  }                                                              \
  IMP_PERSISTENT_NEW_DELETE_CLASS( Class )                       \
  IMP_CLASS_DESC_FUNC( AppID, Class )

//----------------------------------------------------------------------------------------
// \ru Описывает необходимые операции поточного класса, \en Describes the necessary operations of the stream class 
// \ru наследующего от другого такого же, и у которого \en inherited from another class which is the same and which 
// \ru нет своих полей данных для записи в поток \en has no its own data fields for writing to stream 
// \ru Устанавливается в любой .cpp файл \en It is set to any .cpp file 
// \ru Примечание : \en Note: 
// \ru 1. Class должен наследовать от TapeBase \en 1. Class must be inherited from TapeBase 
// \ru 2. Требуется (!!!) отсутствие (!!!) функций \en 2. The following functions must be (!!!) absent (!!!) 
//      - void Class::Read( reader& in, Class* obj );
//      - void Class::Write( writer& out, const Class* obj );
// \ru где Class - имя класса \en where Class is a class name 
// \ru эти функции генерируются автоматически \en these functions are generated automatically 
// ---
#define IMP_PERSISTENT_CLASS_FROM_BASE( AppID, Class, Base ) \
  IMP_PERSISTENT_REGISTRATION( AppID, Class );               \
  IMP_A_PERSISTENT_CLASS_FROM_BASE( AppID, Class, Base )

//------------------------------------------------------------------------------
/** \brief \ru Аналог макроса IMP_PERSISTENT_CLASS_FROM_BASE
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков.
           \en Analog of IMP_PERSISTENT_CLASS_FROM_BASE macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads. \~
  \details \ru Аналог макроса IMP_PERSISTENT_CLASS_FROM_BASE
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков
           (включается переменной __OVERLOAD_MEMORY_ALLOCATE_FREE_).
           \en Analog of IMP_PERSISTENT_CLASS_FROM_BASE macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads
           (enabled by defining __OVERLOAD_MEMORY_ALLOCATE_FREE_). \~
  \ingroup Base_Tools_IO
*/
// ---
#define IMP_PERSISTENT_CLASS_FROM_BASE_NEW_DEL( AppID, Class, Base ) \
  IMP_PERSISTENT_CLASS_FROM_BASE( AppID, Class, Base )             \
  IMP_PERSISTENT_NEW_DELETE_CLASS_EX( Class )

//----------------------------------------------------------------------------------------
// \ru Описывает необходимые операции для поточного класса, \en Describes the necessary operations for the stream class 
// \ru не наследующего ни от кого кроме TapeBase, и у которого \en which is not inherited from any class except TapeBase and which 
// \ru нет своих полей данных для записи в поток \en has no its own data fields for writing to stream 
// \ru Устанавливается в любой .cpp файл \en It is set to any .cpp file 
// \ru Примечание : \en Note: 
// \ru 1. Class должен наследовать от TapeBase \en 1. Class must be inherited from TapeBase 
// \ru 2. Требуется (!!!) отсутствие (!!!) функций \en 2. The following functions must be (!!!) absent (!!!) 
//      - void Class::Read( reader& in, Class* obj );
//      - void Class::Write( writer& out, const Class* obj );
// \ru где Class - имя класса \en where Class is a class name 
// ---
#define IMP_PERSISTENT_CLASS_WD( AppID, Class )     \
  IMP_PERSISTENT_REGISTRATION( AppID, Class );      \
  void Class::Read( reader &, Class * )         {}  \
  void Class::Write( writer &, const Class * )  {}  \
  IMP_PERSISTENT_NEW_DELETE_CLASS( Class )          \
  IMP_CLASS_DESC_FUNC( AppID, Class )

//----------------------------------------------------------------------------------------
/** \brief \ru Аналог макроса IMP_PERSISTENT_CLASS_WD
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков.
           \en Analog of IMP_PERSISTENT_CLASS_WD macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads. \~
  \details \ru Аналог макроса IMP_PERSISTENT_CLASS_WD
           с возможностью перегрузки операторов new/delete,
           обеспечивающий последовательное обращение к функциям
           выделения/освобождения памяти из разных потоков
           (включается переменной __OVERLOAD_MEMORY_ALLOCATE_FREE_).
           \en Analog of IMP_PERSISTENT_CLASS_WD macro
           with support of new/delete operators overloading which provides
           sequential access to the allocation/deallocation functions
           from different threads
           (enabled by defining __OVERLOAD_MEMORY_ALLOCATE_FREE_). \~
  \ingroup Base_Tools_IO
*/
// ---
#define IMP_PERSISTENT_CLASS_WD_NEW_DEL( AppID, Class ) \
  IMP_PERSISTENT_CLASS_WD( AppID, Class );              \
  IMP_PERSISTENT_NEW_DELETE_CLASS_EX( Class )

//----------------------------------------------------------------------------------------
// \ru Описывает необходимые операции для абстрактного поточного класса, \en Describes the necessary operations for the abstract stream class 
// \ru не наследующего ни от кого кроме TapeBase, и у которого \en which is not inherited from any class except TapeBase and which 
// \ru нет своих полей данных для записи в поток \en has no its own data fields for writing to stream 
// \ru Устанавливается в любой .cpp файл \en It is set to any .cpp file 
// \ru Примечание : \en Note: 
// \ru 1. Class должен наследовать от TapeBase \en 1. Class must be inherited from TapeBase 
// \ru 2. Требуется (!!!) отсутствие (!!!) функций \en 2. The following functions must be (!!!) absent (!!!) 
//      - void Class::Read( reader& in, Class* obj );
//      - void Class::Write( writer& out, const Class* obj );
// \ru где Class - имя класса \en where Class is a class name 
// ---
#define IMP_A_PERSISTENT_CLASS_WD( AppID, Class )   \
  void Class::Read( reader &, Class * )         {}  \
  void Class::Write( writer &, const Class * )  {}  \
  IMP_PERSISTENT_NEW_DELETE_CLASS( Class )          \
  IMP_CLASS_DESC_FUNC( AppID, Class )


//----------------------------------------------------------------------------------------
/// \ru Удаление пробелов и записей перед пробелами. \en Deleting of spaces and records before spaces.  \~ \ingroup Base_Tools_IO
// \ru Для совместимости с предыдущими компиляторами по именам возвращаемым typeid(a).name() \en For compatibility with the previous compilers by names returned by typeid(a).name() 
// \ru Для определения того, что надо делать, скомпилируйте и запустите из консоли код \en Compile and run the following code from console to define what is to do  
// #include <typeinfo>
// #include <iostream>
// class CLASS_A {
//   public: virtual ~CLASS_A() {} 
// };
//
// int main(int argc, char **argv) {
//   CLASS_A a;
//   std::cout << typeid(a).name() << '\n';
//   return 0;
// }
//
// \ru Выдаваемые значения \en Returned values  
// MS Visual C++ 6.0 ... 2010:     "class CLASS_A"
// gcc (Linux):                    "7CLASS_A"
// BORLAND C++ 5.0:                "CLASS_A"
// Embarcadero C++ 7.20 for Win32  "$CLASS_A"
// \ru Интересующая нас функция должна выдавать "CLASS_A" \en The desired function must write "CLASS_A" 
// ---
inline const char * pureName( const char * name )
{
  if ( name && *name ) 
  {
#ifdef _MSC_VER    
    // \ru убираем ключевые слова "class", "struct" и т.д. в начале строки \en remove the keywords "class", "struct" and so on at the beginning of the string 
    ptrdiff_t i = strlen(name) - 1;
    for ( ; i >= 0 && name[i] != ' '; i-- );
    return ((i >= 0) && (name[i] == ' ')) ? &(name[i+1]) : name;
#elif __BORLANDC__
    // \ru убираем "$" в начале строки \en remove "$" at the beginning of the string 
    for ( size_t i = 0, c = strlen(name); i < c; i++ )
      if ( name[i] != '$' )
        return &(name[i]);
#else // _MSC_VER
    // \ru убираем длину имени в начале строки \en remove the name length at the beginning of the string 
    for ( size_t i = 0, c = strlen(name); i < c; i++ )
      if ( !(name[i] >= '0' && name[i] <= '9') )
        return &(name[i]);
#endif // _MSC_VER   
  }
  return name;
}


//----------------------------------------------------------------------------------------
/// \ru Упаковать строку(имя класса) в uint16. \en Pack the string (class name) into uint16. \~ \ingroup Base_Tools_IO
// ---
inline uint16 hash( const char * name )
{
  const uint16 * c = (const uint16 *)name;

  uint16 h = uint16(strlen(name));    // Mix in the string length.
  uint16 l = h;
  uint16 i = uint16(h / sizeof(uint16));  // Could do "<<" here, but less portable.

  while ( i-- )
    h ^= *c++;  // XOR in the characters.

                // If there are any remaining characters,
                // then XOR in the rest, using a mask:
  if ( (i = uint16(l % sizeof(uint16))) != 0 )
    h ^= uint16(*c & 0xff);

  return h;
}

//----------------------------------------------------------------------------------------
// \ru Чтение CHAR строки из потока. (в кодировке ANSI, с русской локалью) \en Reading of CHAR string from the stream. (in ANSI coding, with Russian locale) 
// \ru И нулевой указатель и пустая строка возвращаются как нулевой указатель! \en Both null pointer and an empty string are returned as null pointer!  
// \ru Длина строки не может превышать SYS_MAX_UINT16 - 1 \en The string length cannot exceed SYS_MAX_UINT16 - 1 
// \ru Созданную строку кто-то потом должен уничтожить (через delete[]) \en Created string must be deleted by someone then (using delete[]) 
// ---
inline reader & __readChar( reader & ps, char *& s )
{
  s = NULL;

  if ( ps.good() )
  {
    uint16 len = 0;
    ps.readBytes( &len, sizeof(len) );  // \ru длина строки - uint16 \en string length - uint16 

    if ( len == 0              ||
         len == SYS_MAX_UINT16 ||
         (len > 0 && ps.eof()) ||
         !ps.good() )
    {
      s = NULL;
    }
    else // good
    {
      s = new char[len + 1];
      if ( s )
      {
        if ( ps.readBytes(s, len) )
        {
          // \ru прочли сколько нужно - добавить ограничивающий 0 \en have read as much as necessary - the terminating 0 is to be added 
          s[len] = 0;
        }
        else
        {
          // \ru прочли не все, скорее всего ошибка - очистить строку \en not everything has been read, must be an error - clear the string 
          delete [] s;
          s = NULL;
        }
      }
      else 
        ps.setState( io::outOfMemory );
    }
  }

  return ps;
}


//----------------------------------------------------------------------------------------
// \ru Чтение WCHAR строки из потока. (в потоке хранится как UTF-16) \en Reading of WCHAR string from the stream. (stored in the stream as UTF-16) 
// \ru И нулевой указатель и пустая строка возвращаются как нулевой указатель! \en Both null pointer and an empty string are returned as null pointer!  
// \ru Длина строки не может превышать SYS_MAX_UINT32 - 1 \en The string length cannot exceed SYS_MAX_UINT32 - 1 
// \ru Созданную строку кто-то потом должен уничтожить \en Created string should be deleted by someone then 
// ---
inline reader & __readWchar( reader & ps, TCHAR * & s )
{
  s = NULL; // \ru на случай, если ничего не прочитаем \en for case if nothing will be read 
  if ( ps.good() )
  {
    uint32 len = 0; 
    if ( ps.readBytes(&len, sizeof(len)) &&  // \ru длина строки в символах без терминального нуля - uint32 \en the string length in symbols without the termination zero - uint32 
         len != 0               &&
         len != SYS_MAX_UINT32  &&
         !ps.eof() )
    {
      uint16 * readBuf = new uint16[(size_t)len + 1]; // \ru длина (количество символов) вычитываемой строки с терминальным нулем \en length (number of symbols) of string being read with terminating 0 
      size_t size = sizeof(uint16) * (size_t)len;     // \ru длина (в байтах) вычитываемой строки без терминального нуля \en length (in bytes) of string being read without terminating null 

      if ( ps.readBytes(readBuf, size) ) 
        // \ru прочли сколько нужно - добавить ограничивающий 0 \en have read as much as necessary - the terminating 0 is to be added 
        readBuf[(size_t)len] = 0; 
      else {
        // \ru прочли не все, скорее всего ошибка - очистить строку \en not everything has been read, must be an error - clear the string 
        delete [] readBuf;
        readBuf = NULL;
      }

      if ( readBuf ) { // is OK
#ifdef _UNICODE  // TCHAR == wchar_t
 #if __SIZEOF_WCHAR_T__ == 2  // sizeof(wchar_t) == sizeof(uint16)
        s = (TCHAR *)readBuf; // \ru собственно ничего конвертировать не нужно \en nothing to convert 
 #else // sizeof(wchar_t) == sizeof(uint32)
        s = (TCHAR *)Utf16ToUcs4(readBuf); // \ru Конвертировать UTF-16 в WCHAR \en Convert from UTF-16 to WCHAR 
        delete [] readBuf;
 #endif
#else // _UNICODE 
 #if __SIZEOF_WCHAR_T__ == 2  // sizeof(wchar_t) == sizeof(uint16)
        s = wcsnewmbs( (const wchar_t*)readBuf );  // \ru Конвертировать WCHAR в CHAR строку. \en Convert WCHAR-string to CHAR-string. 
 #else // sizeof(wchar_t) == sizeof(uint32)
	uint32* readBuf32 = Utf16ToUcs4(readBuf); // \ru Конвертировать UTF-16 в WCHAR \en Convert from UTF-16 to WCHAR 
	s = wcsnewmbs( (const wchar_t*)readBuf32 );  // \ru Конвертировать WCHAR в CHAR строку. \en Convert WCHAR-string to CHAR-string. 
	delete [] readBuf32;
 #endif
        delete [] readBuf;
#endif // _UNICODE 
      }
    }
  }

  return ps;
}


//----------------------------------------------------------------------------------------
// \ru Чтение WCHAR строки из потока. (в потоке хранится как UTF-16) \en Reading of WCHAR string from the stream. (stored in the stream as UTF-16) 
// \ru И нулевой указатель и пустая строка возвращаются как нулевой указатель! \en Both null pointer and an empty string are returned as null pointer!  
// \ru Длина строки не может превышать SYS_MAX_UINT32 - 1 \en The string length cannot exceed SYS_MAX_UINT32 - 1 
// \ru Созданную строку кто-то потом должен уничтожить \en Created string should be deleted by someone then 
// ---
inline reader & __readWcharT( reader & ps, wchar_t * & s )
{
  s = NULL; // \ru на случай, если ничего не прочитаем \en for case if nothing will be read 
  if ( ps.good() )
  {
    uint32 len = 0; 
    if ( ps.readBytes(&len, sizeof(len)) &&  // \ru длина строки в символах без терминального нуля - uint32 \en the string length in symbols without the termination zero - uint32 
         len != 0               &&
         len != SYS_MAX_UINT32  &&
         !ps.eof() )
    {
      uint16 * readBuf = new uint16[(size_t)len + 1]; // \ru длина (количество символов) вычитываемой строки с терминальным нулем \en length (number of symbols) of string being read with terminating 0 
      size_t size = sizeof(uint16) * (size_t)len;     // \ru длина (в байтах) вычитываемой строки без терминального нуля \en length (in bytes) of string being read without terminating null 

      if ( ps.readBytes(readBuf, size) ) 
        // \ru прочли сколько нужно - добавить ограничивающий 0 \en have read as much as necessary - the terminating 0 is to be added 
        readBuf[(size_t)len] = 0; 
      else {
        // \ru прочли не все, скорее всего ошибка - очистить строку \en not everything has been read, must be an error - clear the string 
        delete [] readBuf;
        readBuf = NULL;
      }

      if ( readBuf ) { // is OK
#if __SIZEOF_WCHAR_T__ == 2  // sizeof(wchar_t) == sizeof(uint16)
        s = (wchar_t *)readBuf; // \ru собственно ничего конвертировать не нужно \en nothing to convert 
#else // sizeof(wchar_t) == sizeof(uint32)
        s = (wchar_t *)Utf16ToUcs4(readBuf); // \ru Конвертировать UTF-16 в WCHAR \en Convert from UTF-16 to WCHAR 
        delete [] readBuf;
#endif
      }
    }
  }

  return ps;
}


#ifdef C3D_WINDOWS //_MSC_VER // \ru Код для поддержки КОМПАС \en Code for KOMPAS support 
//----------------------------------------------------------------------------------------
/// \ru Чтение CHAR строки из потока. \en Reading of CHAR string from the stream. \~ \ingroup Base_Tools_IO
// \ru И нулевой указатель и пустая строка возвращаются как нулевой указатель! \en Both null pointer and an empty string are returned as null pointer!  
// ---
#ifndef DISABLE_RWTCHAR
#ifdef _UNICODE
inline reader & operator >> ( reader & ps, char *& s )
{
  return __readChar( ps, s );
}
#endif // _UNICODE
#endif // DISABLE_RWTCHAR


//----------------------------------------------------------------------------------------
/// \ru Запись CHAR строки в поток. \en Writing CHAR string to the stream. \~ \ingroup Base_Tools_IO
// ---
#ifndef DISABLE_RWTCHAR
#ifdef _UNICODE
inline writer & operator << ( writer & ps, const char * s )
{
  return ps.__writeChar( s );
}
#endif // _UNICODE
#endif // DISABLE_RWTCHAR

//----------------------------------------------------------------------------------------
/// \ru Чтение WCHAR строки из потока. \en Reading of WCHAR string from the stream. \~ \ingroup Base_Tools_IO
// \ru И нулевой указатель и пустая строка возвращаются как нулевой указатель! \en Both null pointer and an empty string are returned as null pointer!  
// \ru OV длина строки не может превышать SYS_MAX_UINT32 - 1 \en OV length of string can't exceed SYS_MAX_UINT32 - 1 
// ---
#ifndef DISABLE_RWTCHAR
inline reader & operator >> ( reader & ps, TCHAR *& s )
{
  return __readWchar( ps, s );
}
#endif // DISABLE_RWTCHAR


//----------------------------------------------------------------------------------------
/// \ru Запись WCHAR строки в поток. \en Writing WCHAR string to the stream. \~ \ingroup Base_Tools_IO
// \ru длина строки не может превышать SYS_MAX_UINT32 - 1 \en string length can't exceed SYS_MAX_UINT32 - 1 
// ---
#ifndef DISABLE_RWTCHAR
inline writer & operator << ( writer & ps, const TCHAR * s )
{
  return ps.__writeWchar( s );
}
#endif // DISABLE_RWTCHAR

#endif // C3D_WINDOWS

#ifdef __MOBILE_VERSION__
#ifdef _UNICODE
inline reader & operator >> ( reader & ps, char *& s ){  return __readChar( ps, s );}
inline writer & operator << ( writer & ps, const char * s ){  return ps.__writeChar( s );}
inline reader & operator >> ( reader & ps, TCHAR *& s ){  return __readWchar( ps, s );}
inline writer & operator << ( writer & ps, const TCHAR * s ){  return ps.__writeWchar( s );}
#endif // _UNICODE
#endif // __MOBILE_VERSION__

//----------------------------------------------------------------------------------------
/// \ru Запись bool в поток. \en Writing bool to the stream. \~ \ingroup Base_Tools_IO
// ---
inline writer & operator << ( writer & ps, bool i )
{
  //unsigned char val = i;
  uint8 val = i ? 1 : 0;
  ps.writeByte( val );
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение bool в поток. \en Reading of bool to the stream. \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, bool & i )
{
  if ( IsVersion16bit( ps.MathVersion() ) )
  {
    unsigned short tmp = 0;
    ps.readBytes( &tmp, sizeof(unsigned short) );
    i = !!tmp;
  }
  else 
    i = !!ps.readByte();
  
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись signed int в поток. \en Writing signed int to the stream. \~ \ingroup Base_Tools_IO
// \ru оператор записи для типов: int (не поддерживает int32, long, LONG - для них есть своя реализация) \en write operator for types: int (doesn't support int32, long, LONG - there is a separate implementation for them)  
// \ru поддерживает запись в 32 и 16-битный формат файла \en supports writing to 32- and 16-bit format of file 
// ---
inline writer & operator << ( writer & ps, signed int i )
{
#ifdef C3D_WINDOWS //_MSC_VER 
  if ( IsVersion16bit( ps.MathVersion() ) )
  {
    // \ru чтение из 16-битной версии файла \en reading from 16-bit version of file 
    // \ru ради этого куска чтение/запись int отделено от чтения/записи long \en reading/writing of int is separated from reading/writing of long for the sake of this fragment 
    int16 val = (int16)i;
    ps.writeBytes( &val, sizeof(val) );
  }
  else {
    int32 val = (int32)i;
    ps.writeBytes( &val, sizeof(val) );
  }
  return ps;
#else // C3D_WINDOWS
  if ( IsVersion16bit( ps.MathVersion() ) )
    ps.setState( io::fail );  // \ru в Linux-версии 16-битные файлы не поддерживаются \en 16-bit files are not supported in Linux 
  else {
    int32 val = (int32)i;
    ps.writeBytes( &val, sizeof(val) );
  }
  return ps;
#endif // C3D_WINDOWS 
}


//----------------------------------------------------------------------------------------
/// \ru Запись unsigned int в поток. \en Writing unsigned int to the stream.  \~ \ingroup Base_Tools_IO
// \ru оператор записи для типов: uint (не поддерживает uint32, ulong - для них есть своя реализация) \en write operator for types: uint (doesn't support uint32, ulong - there is a separate implementation for them)  
// \ru поддерживает запись в 32 и 16-битный формат файла \en supports writing to 32- and 16-bit format of file 
// ---
inline writer & operator << ( writer & ps, unsigned int i ) {
#ifdef C3D_WINDOWS //_MSC_VER 
  if ( IsVersion16bit( ps.MathVersion() ) ) { 
    // \ru чтение из 16-битной версии файла \en reading from 16-bit version of file 
    // \ru ради этого куска чтение/запись int отделено от чтения/записи long \en reading/writing of int is separated from reading/writing of long for the sake of this fragment 
    uint16 val = (uint16)i;
    ps.writeBytes( &val, sizeof(val) );
  }
  else {
    uint32 val = i;
    ps.writeBytes( &val, sizeof(val) );
  }
  return ps;
#else // C3D_WINDOWS 
  if ( IsVersion16bit( ps.MathVersion() ) ) 
    ps.setState( io::fail );  // \ru в Linux-версии 16-битные файлы не поддерживаются \en 16-bit files are not supported in Linux 
  else {
    uint32 val = i;
    ps.writeBytes( &val, sizeof(val) );
  }
  return ps;
#endif // C3D_WINDOWS 
}


//----------------------------------------------------------------------------------------
/// \ru Чтение signed int в поток. \en Reading signed int to the stream. \~ \ingroup Base_Tools_IO
// \ru оператор чтения для типов: int (не поддерживает int32, long, LONG - для них есть своя реализация) \en read operator for types: int (doesn't support int32, long, LONG - there is a separate implementation for them)  
// \ru поддерживает чтение из 32 и 16-битного формата файла \en supports reading from 32- and 16-bit format of file 
// ---
inline reader & operator >> ( reader & ps, signed int & i )
{
#ifdef C3D_WINDOWS //_MSC_VER // Linux identical int/uint and int32/uint32
  if ( IsVersion16bit( ps.MathVersion() ) ) { 
    // \ru чтение из 16-битной версии файла \en reading from 16-bit version of file 
    // \ru ради этого куска чтение/запись int отделено от чтения/записи long \en reading/writing of int is separated from reading/writing of long for the sake of this fragment 
    int16 val = 0;
    ps.readBytes( &val, sizeof(val) );
    i = val;
  }
  else {
    int32 val = 0;
    ps.readBytes( &val, sizeof(val) );
    i = (signed int)val;
  }
  return ps;
#else // C3D_WINDOWS
  if ( IsVersion16bit( ps.MathVersion() ) ) 
    ps.setState( io::fail );  // \ru в Linux-версии 16-битные файлы не поддерживаются \en 16-bit files are not supported in Linux 
  else {
    int32 val = 0;
    ps.readBytes( &val, sizeof(val) );
    i = (signed int)val;
  }
  return ps;
#endif // C3D_WINDOWS
}


//----------------------------------------------------------------------------------------
/// \ru Чтение unsigned int в поток. \en Reading unsigned int to the stream. \~ \ingroup Base_Tools_IO
// \ru оператор чтения для типов: uint (не поддерживает uint32, ulong - для них есть своя реализация) \en read operator for types: uint (doesn't support uint32, ulong - there is a separate implementation for them)  
// \ru поддерживает чтение из 32 и 16-битного формата файла \en supports reading from 32- and 16-bit format of file 
// ---
inline reader & operator >> ( reader & ps, unsigned int & i )
{
#ifdef C3D_WINDOWS //_MSC_VER // Linux identical int/uint and int32/uint32
  if ( IsVersion16bit( ps.MathVersion() ) )
  {
    // \ru чтение из 16-битной версии файла \en reading from 16-bit version of file 
    // \ru ради этого куска чтение/запись int отделено от чтения/записи long \en reading/writing of int is separated from reading/writing of long for the sake of this fragment 
    uint16 val = 0;
    ps.readBytes( &val, sizeof(val) );
    i = val;
  }
  else {
    uint32 val = 0;
    ps.readBytes( &val, sizeof(val) );
    i = (unsigned int)val;
  }
  return ps;
#else // C3D_WINDOWS
  if ( IsVersion16bit( ps.MathVersion() ) ) 
    ps.setState( io::fail );  // \ru в Linux-версии 16-битные файлы не поддерживаются \en 16-bit files are not supported in Linux 
  else {
    uint32 val = 0;
    ps.readBytes( &val, sizeof(val) );
    i = (unsigned int)val;
  }
  return ps;
#endif // C3D_WINDOWS
}


//----------------------------------------------------------------------------------------
/// \ru Запись int32 в поток. \en Writing int32 to the stream. \~ \ingroup Base_Tools_IO
// \ru оператор записи для типов: long, int32, LONG (не поддерживает int - для него есть своя реализация) \en write operator for types: long, int32, LONG (does not support int - there is a separate implementation for it)  
// \ru данные всегда пишутся в 32-разрядном формате \en data are always written in 32-bit format 
// ---
#ifdef C3D_WINDOWS //_MSC_VER // Linux identical int/uint and int32/uint32
// \ru ВНИМАНИЕ!!! В целях совместимости данных для задач скомпилированных под Windows и Linux \en NOTE!!! To provide data compatibility for tasks compiled for Windows and Linux  
// \ru ЗАПРЕЩАЕТСЯ использовать тип данных long и unsigned long. Используйте int32 и uint32 \en IT IS FORBIDDEN to use long and unsigned long data types. Use int32 and uint32 
inline writer & operator << ( writer & ps, int32 l )
{
  ps.writeBytes( &l, sizeof(l) );
  return ps;
}
#endif // C3D_WINDOWS


//----------------------------------------------------------------------------------------
/// \ru Запись uint32 в поток. \en Writing uint32 to the stream. \~ \ingroup Base_Tools_IO
// \ru оператор записи для типов: ulong, uint32 (не поддерживает uint - для него есть своя реализация) \en write operator for types: ulong, uint32 (does not support uint - there is a separate implementation for it)  
// \ru данные всегда пишутся в 32-разрядном формате \en data are always written in 32-bit format 
// ---
#ifdef C3D_WINDOWS // Linux identical int/uint and int32/uint32
// \ru ВНИМАНИЕ!!! В целях совместимости данных для задач скомпилированных под Windows и Linux \en NOTE!!! To provide data compatibility for tasks compiled for Windows and Linux  
// \ru ЗАПРЕЩАЕТСЯ использовать тип данных long и unsigned long. Используйте int32 и uint32 \en IT IS FORBIDDEN to use long and unsigned long data types. Use int32 and uint32 
inline writer& operator << ( writer& ps, uint32 l )
{
  ps.writeBytes( &l, sizeof(l) );
  return ps;
}
#endif // C3D_WINDOWS


//----------------------------------------------------------------------------------------
/// \ru Чтение int32 в поток. \en Reading int32 to the stream. \~ \ingroup Base_Tools_IO
// \ru оператор чтения для типов: long, int32, LONG  (не поддерживает int - для него есть своя реализация) \en read operator for types: long, int32, LONG (does not support int - there is a separate implementation for it)  
// \ru данные всегда читаются в 32-разрядном формате \en data are always read in 32-bit format 
// ---
#ifdef C3D_WINDOWS //_MSC_VER // Linux identical int/uint and int32/uint32
// \ru ВНИМАНИЕ!!! В целях совместимости данных для задач скомпилированных под Windows и Linux \en NOTE!!! To provide data compatibility for tasks compiled for Windows and Linux  
// \ru ЗАПРЕЩАЕТСЯ использовать тип данных long и unsigned long. Используйте int32 и uint32 \en IT IS FORBIDDEN to use long and unsigned long data types. Use int32 and uint32 
inline reader& operator >> ( reader& ps, int32 & l )
{
  size_t size = sizeof(int32);
  if ( !ps.readBytes(&l, size) )
    l = 0;

  return ps;
}
#endif // C3D_WINDOWS


//----------------------------------------------------------------------------------------
/// \ru Чтение uint32 в поток. \en Reading uint32 to the stream. \~ \ingroup Base_Tools_IO
// \ru оператор чтения для типов: ulong, uint32 (не поддерживает uint - для него есть своя реализация) \en read operator for types: ulong, uint32 (does not support uint - there is a separate implementation for it)  
// \ru данные всегда читаются в 32-разрядном формате \en data are always read in 32-bit format 
// ---
#ifdef C3D_WINDOWS //_MSC_VER // Linux identical int/uint and int32/uint32
// \ru ВНИМАНИЕ!!! В целях совместимости данных для задач скомпилированных под Windows и Linux \en NOTE!!! To provide data compatibility for tasks compiled for Windows and Linux  
// \ru ЗАПРЕЩАЕТСЯ использовать тип данных long и unsigned long. Используйте int32 и uint32 \en IT IS FORBIDDEN to use long and unsigned long data types. Use int32 and uint32 
inline reader& operator >> ( reader& ps, uint32 & l )
{
  size_t size = sizeof(uint32);
  if ( !ps.readBytes(&l, size) )
    l = 0;

  return ps;
}
#endif // C3D_WINDOWS


//----------------------------------------------------------------------------------------
/// \ru Запись int64 в поток. \en Writing int64 to the stream. \~ \ingroup Base_Tools_IO
// ---
inline writer & operator << ( writer & ps, int64 val )
{
  ps.writeInt64( val );
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение int64 в поток. \en Reading int64 to the stream. \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, int64 & val )
{
  ps.readInt64( val );
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение signed char в поток. \en Reading signed char to the stream. \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, signed char & ch )
{
  ch = (signed char)ps.readByte();
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение unsigned char в поток. \en Reading unsigned char to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, unsigned char & ch )
{
  ch = (unsigned char)ps.readByte();
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение char в поток. \en Reading char to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, char & ch ) {
  ch = (char)ps.readByte();
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение signed short в поток. \en Reading signed short to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, signed short & sh ) {
  const size_t size = sizeof(sh);
  
  if ( !ps.readBytes(&sh, size) )
    sh = 0;

  return ps;
}

//----------------------------------------------------------------------------------------
/// \ru Чтение unsigned short в поток. \en Reading unsigned short to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, unsigned short & sh ) 
{
  const size_t size = sizeof(sh);
  
  if ( !ps.readBytes(&sh, size) )
    sh = 0;

  return ps;
}

#ifdef __MOBILE_VERSION__
//----------------------------------------------------------------------------------------
/// \ru Чтение wchar_t в поток. \en Reading wchar_t to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, wchar_t & sh )
{
  sh = 0; //Обнулить, т.к. размер 4 байта, а читаются только 2
  //size_t size = sizeof(sh);
  size_t size = 2; //В windows sizeof(wchar_t) = 2, в Android  sizeof(wchar_t) = 4

  if ( !ps.readBytes(&sh, size) )

  sh = 0;

  return ps;
}
#endif // __MOBILE_VERSION__


//----------------------------------------------------------------------------------------
/// \ru Чтение float в поток. \en Reading float to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, float & f ) {
  size_t size = sizeof(f);
  
  if ( !ps.readBytes(&f, size) )
    f = 0;

  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение double в поток. \en Reading double to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, double & d )
{
  size_t size = sizeof(d);

  if ( !ps.readBytes(&d, size) )
    d = 0;

  // \ru Проверка числа на определенность \en Check if the number is defined
  if ( c3d_isnan(d) )
    d = 0;

  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение long double из потока. \en Reading long double from the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, long double & l ) {
  size_t size = sizeof(l);

  if ( !ps.readBytes(&l, size) )
    l = 0;

  return ps;
}

//----------------------------------------------------------------------------------------
/// \ru Чтение smart-указателя из потока. \en Reading a smart pointer from the stream. \~ \ingroup Base_Tools_IO
// ---
template<class _Class>
inline reader & operator >> ( reader & ps, SPtr<_Class> & sPtr )
{
  _Class * ptr = NULL;
  ps >> ptr;
  sPtr.assign( ptr );
  return ps;
}

//----------------------------------------------------------------------------------------
/// \ru Запись smart-указателя в поток. \en Writing a smart pointer to the stream. \~ \ingroup Base_Tools_IO
// ---
template<class _Class>
inline writer & operator << ( writer & ps, const SPtr<_Class> & sPtr )
{
  ps << sPtr.get();
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись signed char в поток. \en Write signed char to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer& operator << ( writer & ps, signed char ch )
{
  ps.writeByte( ch ); // \ru байт \en byte 
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись unsigned char в поток. \en Write unsigned char to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer& operator << ( writer & ps, unsigned char ch )
{
  ps.writeByte( ch ); // \ru байт \en byte 
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись char в поток. \en Write char to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer& operator << ( writer & ps, char ch )
{
  ps.writeByte( ch ); // \ru байт \en byte 
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись signed short в поток. \en Write signed short to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer& operator << ( writer & ps, signed short sh )
{
  ps.writeBytes( &sh, sizeof(sh) );
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись unsigned short в поток. \en Write unsigned short to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer& operator << ( writer& ps, unsigned short sh )
{
  ps.writeBytes( &sh, sizeof(sh) );
  return ps;
}

#ifdef __MOBILE_VERSION__
//----------------------------------------------------------------------------------------
/// \ru Запись wchar_t в поток. \en Write wchar_t to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer & operator << ( writer & ps, wchar_t sh )
{
  size_t size = 2; //В windows sizeof(wchar_t) = 2, в Android  sizeof(wchar_t) = 4
  ps.writeBytes( &sh, size );
  return ps;
}
#endif // __MOBILE_VERSION__


//----------------------------------------------------------------------------------------
/// \ru Запись float в поток. \en Write float to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer & operator << ( writer & ps, float f )
{
  ps.writeBytes( &f, sizeof(f) );
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись double в поток. \en Write double to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer& operator << ( writer & ps, const double & d )
{
  ps.writeBytes( &d, sizeof(d) );
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись long double в поток. \en Write long double to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer & operator << ( writer & ps, const long double & l )
{
  ps.writeBytes( &l, sizeof(l) );
  return ps;
}

//----------------------------------------------------------------------------------------
/// \ru Записать TCHAR строку в поток. \en Write TCHAR string to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline void WriteTCHAR( writer & out, const TCHAR * ts, bool directSingleByte = false ) 
{
  if ( directSingleByte || out.MathVersion() < UNICODE_VERSION ) 
  {
    // \ru пишем WCHAR* как CHAR* \en write WCHAR* as CHAR* 
    char * s = _tcsNstr( ts );  // \ru создаем ANSI из TCHAR (если TCHAR == char, то просто дублируем) \en create ANSI from TCHAR (if TCHAR == char, then simply duplicate) 
    out.__writeChar( s );      // \ru пишем строку в формате ANSI \en write string in ANSI format 
    delete [] s;
  }
  else 
  {
    // \ru пишем WCHAR* \en write WCHAR* 
    out.__writeWchar( ts ); 
  }
}

//----------------------------------------------------------------------------------------
/// \ru Прочитать TCHAR строку из потока. \en Read TCHAR string from the stream.  \~ \ingroup Base_Tools_IO
//---
inline void ReadTCHAR( reader & in, TCHAR *& ts, bool directSingleByte = false ) 
{
  if ( directSingleByte || in.MathVersion() < UNICODE_VERSION ) 
  {
    // \ru читаем WCHAR* из CHAR* \en read WCHAR* from CHAR* 
    char * s = NULL;
    __readChar( in, s );   // \ru читаем строку в формате ANSI \en read string in ANSI format 
    ts = _strNtcs( s );   // \ru создаем TCHAR из ANSI (если TCHAR == char, то просто дублируем) \en create TCHAR from ANSI (if TCHAR == char, then simply duplicate) 
    delete [] s;
  }
  else 
  {
    // \ru читаем WCHAR* \en read WCHAR* 
    __readWchar( in, ts ); 
  }
}


//----------------------------------------------------------------------------------------
/// \ru Записать wchar_t строку в поток. \en Write wchar_t string to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline void WriteWcharT( writer & out, const wchar_t* ts ) 
{
  out.__writeWcharT( ts ); 
}

//----------------------------------------------------------------------------------------
/// \ru Прочитать TCHAR строку из потока. \en Read TCHAR string from the stream.  \~ \ingroup Base_Tools_IO
//---
inline void ReadWcharT( reader& in, wchar_t* & ts ) 
{
  __readWcharT( in, ts ); 
}


//----------------------------------------------------------------------------------------
/// \ru Запись size_t в зависимости от версии потока. \en Write size_t subject to the stream version.  \~ \ingroup Base_Tools_IO
// ---
inline void WriteCOUNT( writer & out, size_t count )
{
  if ( IsVersion64bit( out.MathVersion() ) )
  {
    uint64 count64 = count;

    if ( out.MathVersion() >= 0x0F001001L ) {
      if ( count64 == SYS_MAX_T )
        count64 = SYS_MAX_UINT64;
    }

    out.writeUInt64( count64 );
  }
  else
  {
    // \ru OV_x64 проверить переполнение при записи 64-битных данных в 32-битный поток \en OV_x64 check for overflow while writing 64-bit data to 32-bit stream 
    if ( HiUint32( count ) != 0 )
      out.setState( io::underflow64to32 );

    uint32 _count = (uint32)LoUint32(count);
    out << _count;
  }
}

//----------------------------------------------------------------------------------------
/// \ru Запись ptrdiff_t в зависимости от версии потока. \en Writing ptrdiff_t subject to the stream version.  \~ \ingroup Base_Tools_IO
// ---
inline void WriteINT_T( writer & out, ptrdiff_t count )
{
  if ( IsVersion64bit( out.MathVersion() ) )
  {
    out.writeInt64( count );
  }
  else
  {
    // \ru OV_x64 проверить переполнение при записи 64-битных данных в 32-битный поток \en OV_x64 check for overflow while writing 64-bit data to 32-bit stream 
    if ( (int64)count > (int64)SYS_MAX_INT32 || (int64)count < (int64)SYS_MIN_INT32 )
      out.setState( io::underflow64to32 );

    int32 _count = (int32)LoUint32(count);
    out << _count;
  }
}

//----------------------------------------------------------------------------------------
/// \ru Чтение size_t в зависимости от версии потока. \en Reading size_t subject to the stream version.  \~ \ingroup Base_Tools_IO
//
// \ru Т.к. операторы чтения/записи для uint и uint32 разные нужно \en Since reading/writing operators are different for uint and uint32,  
// \ru уметь читать оба, в зависимости от места где вызывается. \en there should be capability for reading both of them subject to the place where it is called. 
// \ru Решено запись не менять, т.к. в 16 битовую задачу не записываем. \en Decided not to modify writing since we do not write to 16-bit task. 
// ---
inline size_t ReadCOUNT ( reader & in, bool uint_val = true )
{
  size_t count = 0;
  if ( IsVersion64bit( in.MathVersion() ) )
  {
    uint64  _count = 0;
    in.readUInt64( _count );

    if ( in.MathVersion() >= 0x0F001001L ) {
      if ( _count == SYS_MAX_UINT64 )
        _count = SYS_MAX_T;
    }
    else {
      // \Mapping\a_17356\17356_Телега.c3d PRECONDITION( _count != SYS_MAX_UINT32 ); // неоднозначность интерпретации значения // Primery_Set/Models_8/_58720. 
      if ( _count == SYS_MAX_UINT32 || _count == SYS_MAX_UINT64 )
        _count = SYS_MAX_T;
    }

    count = (size_t)_count; 

    // \ru OV_x64 проверить переполнение при чтении 64-битных данных в 32-битной задаче \en OV_x64 check for overflow while reading 64-bit data in 32-bit task 
    if ( HiUint32(count) != HiUint32(_count) )
      in.setState( io::underflow64to32 );
  }
  else
  {
    // \ru оператор чтения в uint (в отличии от uint32) поддерживает чтение 16-битных версий файла \en operator of reading to uint (in contrast to uint32) supports reading 16-bit versions of file 
    if ( uint_val )
    {
      uint _count = 0;
      in >> _count;

      count = (size_t)_count; 
    }
    else
    {
      uint32 _count = 0;
      in >> _count;
      count = (size_t)_count; 
    }

    if ( count == SYS_MAX_UINT32 )
      count = SYS_MAX_T;
  }

  return count;
}

//----------------------------------------------------------------------------------------
/// \ru Чтение ptrdiff_t в зависимости от версии потока. \en Reading ptrdiff_t subject to the stream version.  \~ \ingroup Base_Tools_IO
//
// \ru Т.к. операторы чтения/записи для uint и uint32 разные нужно \en Since reading/writing operators are different for uint and uint32,  
// \ru уметь читать оба, в зависимости от места где вызывается. \en there should be capability for reading both of them subject to the place where it is called. 
// \ru Решено запись не менять, т.к. в 16 битовую задачу не записываем. \en Decided not to modify writing since we do not write to 16-bit task. 
// ---
// \ru САА K13 31.8.2010 Исправление BUG 52091 \en CAA K13 31.8.2010 Fix for BUG 52091 
// \ru 77 вызовов и из них только 2 с false!!! - поэтому по умолчанию для всех \en 77 calls and only 2 of them with false!!! - so it is default for all 
inline ptrdiff_t ReadINT_T( reader & in, bool uint_val = true )
{
  ptrdiff_t count = 0;
  if ( IsVersion64bit( in.MathVersion() ) )
  {
    int64  _count = 0;
    in.readInt64( _count );
    count = (ptrdiff_t)_count; 

    // \ru OV_x64 проверить переполнение при чтении 64-битных данных в 32-битной задаче \en OV_x64 check for overflow while reading 64-bit data in 32-bit task 
    if ( HiInt32(count) != HiInt32(_count) )
      in.setState( io::underflow64to32 );
  }
  else
  {
    // \ru оператор чтения в uint (в отличии от uint32) поддерживает чтение 16-битных версий файла \en operator of reading to uint (in contrast to uint32) supports reading 16-bit versions of file 
    if ( uint_val )
    {
      int _count = 0;
      in >> _count;
      count = (ptrdiff_t)_count;
    }
    else
    {
      int32 _count = 0;
      in >> _count;
      count = (ptrdiff_t)_count; 
    }
  }

  return count;
}

//OV_LNX \ru Перенесено в Asset\Tape\io_buffer.h \en Moved to Asset\Tape\io_buffer.h 
//OV_LNX //----------------------------------------------------------------------------------------
//OV_LNX /// \ru Длина данных size_t в потоке. \en Length of size_t data in the stream.  \~ \ingroup Base_Tools_IO
//OV_LNX // ---
//OV_LNX inline size_t LenCOUNT( VERSION version )
//OV_LNX {
//OV_LNX   if ( IsVersion64bit(version) )
//OV_LNX     return sizeof(uint64);
//OV_LNX   else
//OV_LNX     return sizeof(uint32);
//OV_LNX }

//----------------------------------------------------------------------------------------
/// \ru Запись size_t в память в зависимости от версии потока. \en Writing size_t to the memory subject to the stream version.  \~ \ingroup Base_Tools_IO
// ---
inline void WriteCOUNT( void * out, VERSION version, size_t count )
{
  if ( IsVersion64bit(version) )
  {
    const uint64 count64 = (uint64)count;
    ::memcpy( out, &count64, sizeof(count64) );
  }
  else
  {
    // \ru OV_x64 проверить переполнение при записи 64-битных данных в 32-битный поток \en OV_x64 check for overflow while writing 64-bit data to 32-bit stream 
    //OV_x64 if ( count > (int64)_I32_MAX || count < (int64)_I32_MIN )
    //OV_x64   out.setState( io::underflow64to32 );

    PRECONDITION( count <= (size_t)SYS_MAX_UINT32/*_UI32_MAX*/ );
    const uint32 count32 = (uint32)LoUint32(count);

    ::memcpy( out, &count32, sizeof(count32) );
  }
}

//----------------------------------------------------------------------------------------
/// \ru Запись ptrdiff_t в память в зависимости от версии потока. \en Writing ptrdiff_t to the memory subject to the stream version.  \~ \ingroup Base_Tools_IO
// ---
inline void WriteCOUNT( void * out, VERSION version, ptrdiff_t count )
{
  if ( IsVersion64bit(version) )
  {
    const int64 count64 = (int64)count;
    ::memcpy( out, &count64, sizeof(count64) );
  }
  else
  {
    // \ru OV_x64 проверить переполнение при записи 64-битных данных в 32-битный поток \en OV_x64 check for overflow while writing 64-bit data to 32-bit stream 
    //OV_x64 if ( count > (int64)_I32_MAX || count < (int64)_I32_MIN )
    //OV_x64   out.setState( io::underflow64to32 );

    PRECONDITION( count <= (ptrdiff_t)SYS_MAX_INT32/*_I32_MAX*/ && count >= (ptrdiff_t)SYS_MIN_INT32/*_I32_MIN*/ );
    const int32 count32 = (int32)LoUint32(count);

    ::memcpy( out, &count32, sizeof(count32) );
  }
}

//----------------------------------------------------------------------------------------
/// \ru Чтение size_t в память в зависимости от версии потока. \en Reading of size_t to the memory subject to the stream version.  \~ \ingroup Base_Tools_IO
// ---
inline size_t ReadCOUNT ( void * in, VERSION version )
{
  size_t count = 0;

  if ( IsVersion64bit(version) )
  {
    uint64 count64 = 0;
    ::memcpy( &count64, in, sizeof(count64) );
    PRECONDITION( count64 <= SYS_MAX_T/*SIZE_MAX*/ );
    count = (size_t)count64; 

    // \ru OV_x64 проверить переполнение при чтении 64-битных данных в 32-битной задаче \en OV_x64 check for overflow while reading 64-bit data in 32-bit task 
    //OV_x64 if ( HiUint32( count ) != HiUint32( _count ) )
    //OV_x64   in.setState( io::underflow64to32 );
  }
  else
  {
    uint32 count32 = 0;
    ::memcpy( &count32, in, sizeof(count32) );
    PRECONDITION( sizeof(count32) <= sizeof(count)); // Cannot readCOUNT because sizof(uint32) > sizeof(size_t)
    count = /*AR (size_t)*/count32;   //-V101
  }

  return count;
}


//----------------------------------------------------------------------------------------
/** Получить упакованное имя класса по значению хэша записанному в поток
           
  \param[in]  hash       - Значение хэша.
  \param[in]  ver        - Версия потока в котором записан хэш.

  \result Возвращает упакованное имя класса.
*/
// ---
MATH_FUNC (ClassDescriptor) GetPackedClassName( const ClassDescriptor &, const VersionContainer & ver ); 


#ifdef STANDARD_C11
//----------------------------------------------------------------------------------------
/** Добавить новое соответствие значения хэша записанного в поток упакованному имени класса
           
  \param[in]  сlassName   - Упакованное имя класса.
  \param[in]  hash        - Значение хэша.
  \param[in]  appIndex    - Индекс приложения, которому принадлежит класс.
  \param[in]  lowVersion  - Нижняя граница верссии.
  \param[in]  highVersion - Верхняя граница верссии.
*/
// ---
MATH_FUNC (void) AddPackedClassNameForVersion( const ClassDescriptor & newClassName, const ClassDescriptor & oldClassName, uint appIndex, VERSION lowVersion, VERSION highVersion );
#endif //STANDARD_C11


////////////////////////////////////////////////////////////////////////////////
//
// \ru для получения дампа значений Hash Value в файле hash_GRP.txt(hash_VIE.txt) \en for getting dump of Hash Value values in file hash_GRP.txt(hash_VIE.txt) 
// \ru необходимо раскоментарить этот комментарий \en this comment should be uncommented 
//
////////////////////////////////////////////////////////////////////////////////
#ifdef C3D_DEBUG
//#define HASH_DOCUMENTATION
#endif

#ifdef HASH_DOCUMENTATION

#include <string>

inline void HashDocumentationOut( uint16 hashValue, const char * name, bool unique )
{
  static uint st_calls = 0;

  const char * outName = "C:\\Logs\\hash_GRP.txt";
  std::ofstream out( outName, st_calls ? (std::ios::out|std::ios::app) : std::ios::out );

  std::string sname( name );

  out << _T("\t") << uint16(hashValue) << _T("\t\t") << sname.c_str();
  if ( !unique )
    out << _T("\tNOT UNIQUE!!!");
  out << _T("\n");

  st_calls++;
}

#endif // HASH_DOCUMENTATION

#undef HASH_DOCUMENTATION



#ifndef SIMPLENAME_AS_CLASS

//----------------------------------------------------------------------------------------
/// \ru Запись простого имени. \en Writing of a simple name.  \~ \ingroup Base_Tools_IO
// ---
inline void WriteSimpleName( writer & out, const SimpleName & s ) { out << s; }

//----------------------------------------------------------------------------------------
/// \ru Чтение простого имени. \en Reading of a simple name.  \~ \ingroup Base_Tools_IO
// ---
inline SimpleName ReadSimpleName( reader & in ) { SimpleName s = 0; in >> s; return s; }

#else // SIMPLENAME_AS_CLASS

//----------------------------------------------------------------------------------------
/// \ru Запись простого имени. \en Writing of a simple name.  \~ \ingroup Base_Tools_IO
// ---
inline void WriteSimpleName( writer & out, const SimpleName & s )
{
  size_t sn = s;
  WriteCOUNT( out, sn );
}

//----------------------------------------------------------------------------------------
/// \ru Чтение простого имени. \en Reading of a simple name.  \~ \ingroup Base_Tools_IO
// ---
inline SimpleName ReadSimpleName( reader & in )
{
  size_t sn = ReadCOUNT( in );
  return SimpleName(sn);
}

#endif // SIMPLENAME_AS_CLASS


//----------------------------------------------------------------------------------------
/// \ru Оператор записи хэша. \en Operator of writing hash.  \~ \ingroup Base_Tools_IO
//---
inline writer & operator << ( writer & out, const StrHash & strHash )
{
  // \ru Нельзя допускать хеш с неопределенным типом и с определенным значением \en Hash with undefined type and with specified value cannot be allowed 
  PRECONDITION( !(IsGoodSimpleName(strHash.m_val) && strHash.m_type == StrHash::htp_undef) );

  WriteSimpleName( out, strHash.m_val );

  if ( out.MathVersion() >= 0x0A001005L )
    out << strHash.m_type;
  return out;
}


//----------------------------------------------------------------------------------------
/// \ru Оператор чтения хэша. \en Operator of hash reading.  \~ \ingroup Base_Tools_IO
//---
inline reader & operator >> ( reader& in, StrHash & strHash )
{
  strHash.m_val = ReadSimpleName( in );

  if ( in.MathVersion() >= UNICODE_VERSION )
    if ( in.MathVersion() >= 0x0A001005L /*\ru введена запись типа хеша \en record of hash type is set */)
      in >> strHash.m_type;
    else
      strHash.m_type = StrHash::htp_wchar; // \ru !!! Переходный период, могут быть разные \en !!! Period of transition, may be different 
  else
    strHash.m_type = StrHash::htp_char;

  // \ru Нельзя допускать хеш с неопределенным типом и с определенным значением \en Hash with undefined type and with specified value cannot be allowed 
  PRECONDITION( !(IsGoodSimpleName(strHash.m_val) && strHash.m_type == StrHash::htp_undef) );

  return in;
}


//----------------------------------------------------------------------------------------
/// \ru Запись строки в поток. \en Writing a string to the stream.  \~ \ingroup Base_Tools_IO
//---
inline writer & operator << ( writer & ps, const std::string & s )
{
  if ( ps.MathVersion() < UNICODE_VERSION ) 
  {
    // \ru пишем WCHAR* как CHAR* \en write WCHAR* as CHAR* 
    ps.__writeChar( s.c_str() );      // \ru пишем строку в формате ANSI \en write string in ANSI format 
  } else {
    wchar_t* buf = mbsnewwcs( s.c_str() );
    WriteWcharT( ps, buf );
    delete[] buf;
  }
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение строки из потока. \en Reading a string from the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, std::string & s )
{
  if ( ps.MathVersion() < UNICODE_VERSION ) 
  {
    char * str( NULL );
    __readChar( ps, str );   // \ru читаем строку в формате ANSI \en read string in ANSI format 
    if ( str )
      s = str;
    else
      s.clear();
    delete [] str;
  } else {
    wchar_t * p (NULL);
    ReadWcharT( ps, p ); // \ru в зависимости от версии потока \en subject to the stream version 
    if ( p ) {
      char* str = wcsnewmbs(p);    
      if ( str )
        s = str;
      else
        s.clear();
      delete[] str;
    }
    else
      s.clear();
    delete [] p;
  }
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись строки в поток. \en Writing a string to the stream.  \~ \ingroup Base_Tools_IO
// ---
inline writer & operator << ( writer & ps, const std::wstring & s )
{
  if ( ps.MathVersion() < UNICODE_VERSION ) 
  {
    // \ru пишем WCHAR* как CHAR* \en write WCHAR* as CHAR* 
    char * str = wcsnewmbs( s.c_str() );  // \ru создаем ANSI из TCHAR (если TCHAR == char, то просто дублируем) \en create ANSI from TCHAR (if TCHAR == char, then simply duplicate) 
    ps.__writeChar( str );      // \ru пишем строку в формате ANSI \en write string in ANSI format 
    delete [] str;
  }
  else
    WriteWcharT( ps, s.c_str() ); // \ru в зависимости от версии потока \en subject to the stream version 
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Чтение строки из потока. \en Reading a string from the stream.  \~ \ingroup Base_Tools_IO
// ---
inline reader & operator >> ( reader & ps, std::wstring & s )
{
  if ( ps.MathVersion() < UNICODE_VERSION ) 
  {
    char * str( NULL );
    __readChar( ps, str );   // \ru читаем строку в формате ANSI \en read string in ANSI format 
    wchar_t* p = mbsnewwcs( str );
    if ( p )
      s = p;
    else
      s.clear();
    delete [] p;
    delete [] str;
  } else {
    wchar_t * p = NULL;
    ReadWcharT( ps, p ); // \ru в зависимости от версии потока \en subject to the stream version 
    if ( p )
      s = p;
    else
      s.clear();
    delete [] p;
  }
  return ps;
}


//----------------------------------------------------------------------------------------
/// \ru Запись строки в поток. \en Writing a string to the stream.  \~ \ingroup Base_Tools_IO
//---
inline writer & operator << ( writer & ps, const std::wstring * s )
{
  WriteWcharT( ps, (s ? s->c_str() : NULL) ); // \ru в зависимости от версии потока \en subject to the stream version 
  return ps;
}

//----------------------------------------------------------------------------------------
/// \ru Прочитать кластер. \en Read the cluster.  \~ \ingroup Base_Tools_IO
// ---
inline void ReadCluster( reader & in, uint16 clusterSize, Cluster & cl ) 
{
  // \ru очистить поле указателя, т.к. в AllocMem есть проверка на 0 \en clear the pointer field since there is a check for 0 in AllocMem 
  cl.SetClusterOffset( 0 ); 
  // \ru распределяем кластер стандартной длины ... \en allocate a cluster of a standard length ... 
  cl.AllocMem( clusterSize );

  uint16 length = 0;
  in >> length;
  PRECONDITION( length <= clusterSize );
  cl.m_l = length;

  // \ru ...а читаем - сколько было занято \en ...but read as much as has been occupied 
  in.readBytes( (uint8*)cl.m_f, length );
}

//----------------------------------------------------------------------------------------
/// \ru Записать кластер, параметр clusterSize используется для проверки корректности длины кластера.
/// \en Write the cluster, the clusterSize parameter is used to checking the cluster length.
//  \~ \ingroup Base_Tools_IO
// ---
#ifdef C3D_DEBUG
inline void WriteCluster( writer & out, const Cluster & cl, uint16 clusterSize )
#else
inline void WriteCluster( writer & out, const Cluster & cl, uint16 /*clusterSize*/ )
#endif
{
  uint16 len = cl.m_l;
  PRECONDITION( len <= clusterSize );
  out << len;
  out.writeBytes( (const uint8*)cl.m_f, len );
}

//----------------------------------------------------------------------------------------
/// \ru Записать информацию о кластере. \en Write the information about the cluster.  \~ \ingroup Base_Tools_IO
// ---
inline size_t WriteClusterInfo( void * out, VERSION version, const Cluster & obj )
{
  WriteCOUNT( out, version, obj.m_f );

  uint16 len = obj.m_l; 
  ::memcpy( (uint8*)out + LenCOUNT(version), &len, sizeof( len ) );

  return Cluster::SizeOf( version );
}

//----------------------------------------------------------------------------------------
/// \ru Прочитать информацию о кластере. \en Read the information about the cluster.  \~ \ingroup Base_Tools_IO
// ---
inline size_t ReadClusterInfo( void * in, VERSION version, Cluster & obj )
{
  size_t off = ReadCOUNT( in, version );

  uint16 len = 0; 
  ::memcpy( &len, (uint8*)in + LenCOUNT(version), sizeof( len ) );

  obj.AllocFile( off, len ); // \ru запомнить смещение в файле и кол-во байт \en memorize the shift in file and the number of bytes 

  return Cluster::SizeOf( version );
}

//------------------------------------------------------------------------------
// \ru Записать содержимое кластера. Возвращает размер данных кластера или -1, если длина кластера больше заявленной.
// \en Write the cluster's contents. Return size of cluster's data or -1, if the cluster length is greater than the defined one.
// ---
inline size_t WriteClusterBody( void * out, VERSION version, const Cluster & obj, uint16 clusterSize )
{
  uint8 * m = (uint8 *)out;

  // \ru кол-во заполненных байт в кластере \en the number of filled bytes in the cluster 
  uint16 l = obj._len();
  PRECONDITION( l <= clusterSize );
  *(uint16*)m = l;
  m += sizeof(uint16);

  if ( l > clusterSize )
    return (size_t)-1;

  if ( l ) {
    memcpy( m, obj._ptr(), l ); // \ru теперь данные кластера \en the cluster data now 
                                // не используется далее m += l;
  }

  return getMemLen( obj, version ) ;
}

//------------------------------------------------------------------------------
// \ru Прочитать содержимое кластера. Возвращает размер данных кластера или -1, если длина кластера больше заявленной.
// \en Read the cluster's contents. Return size of cluster's data or -1, if the cluster length is greater than the defined one.
// ---
inline size_t ReadClusterBody( void * in, VERSION version, Cluster & obj, uint16 clusterSize )
{
  uint8 * m = (uint8 *)in;

  // \ru прочитать кол-во заполненных байт кластера и заполнить соответствующее поле в нем \en read the number of filled bytes in the cluster and fill its corresponding field 
  uint16 l = *(uint16*)m;
  PRECONDITION( l <= clusterSize );
  obj.SetClusterLength( l );
  m += sizeof(uint16);

  if ( l > clusterSize )
    return (size_t)-1;

  if ( l ) {
    memcpy( obj._getMemPointer(), m, l ); // \ru теперь данные кластера \en the cluster data now 
                                          // не используется далее m += l;
  }

  return getMemLen( obj, version );
}

//------------------------------------------------------------------------------
/**
  \brief \ru Стартовать try-catch регион для I/O операций. \en Start try-catch region for I/O operations. \~
  \ingroup Base_Tools
*/
//---
#define C3D_IO_CATCH_START  \
  try {

//------------------------------------------------------------------------------
/**
  \brief \ru Завершить try-catch регион для I/O операций (аргумент iostrm - поток чтения или записи).
         \en Complete try-catch region for I/O operations (argument iostrm - reading or writing stream). \~
  \ingroup Base_Tools
*/
//---
#define C3D_IO_CATCH_END(iostrm)        \
  }                                     \
  catch ( const std::bad_alloc & ) {    \
    iostrm.setState( io::outOfMemory ); \
  }                                     \
  catch ( ... ) {                       \
    iostrm.setState( io::fail );        \
  }

#endif // __IO_TAPE_H
