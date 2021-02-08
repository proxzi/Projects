﻿//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Имя топологического объекта.
         \en A name of a topological object. \~

*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __NAME_ITEM_H
#define __NAME_ITEM_H


#include <templ_s_array.h>
#include <templ_s_array_rw.h>
#include <templ_css_array.h>
#include <io_tape.h>
#include <hash32.h>
#include <mb_enum.h>
#include <name_version.h>
#include <name_flags.h>
#include <templ_lis_array.h>
#include <system_atomic.h>
#include <memory>


class  MATH_CLASS MbProperties;
class  MATH_CLASS MbName;

//----------------------------------------------------------------------------------------
/** \brief \ru Поменять местами.
           \en Swap. \~
  \details \ru Поменять местами. \n
           \en Swap. \n \~
  \ingroup Names
*/
// ---
template <class IntegralType>
inline void SwapIT( IntegralType & a, IntegralType & b ) { a^=b; b^=a; a^=b; }


//----------------------------------------------------------------------------------------
/** \brief \ru Размер SimpleName.
           \en Size of SimpleName. \~
  \details \ru Размер SimpleName. \n
           \en Size of SimpleName. \n \~
  \ingroup Names
*/
// ---
const size_t sizeofSimpleName = sizeof( SimpleName );


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Множество простых имен. \en Set of simple names. 
//
//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------
/** \brief \ru Множество простых имен.
           \en Set of simple names. \~
  \details \ru Множество содержит контейнер простых имен. \n
           \en The set contains the container of simple names. \n \~
  \ingroup Names
*/
// ---
class SimpleNameArray {
private:
  SArray<SimpleName> m_array; ///< \ru Множество простых имен. \en Array of simple names. 

public:
  /// \ru Конструктор. \en Constructor. 
  SimpleNameArray( size_t i_max = 0, uint16 i_delta = 1 ) : m_array( i_max, i_delta ) {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  SimpleNameArray( const SimpleNameArray & other )        : m_array( other.m_array )  {}

public:
  /// \ru Установить приращение по количеству элементов при выделении дополнительной памяти (1 - автоприращение). \en Set an increment by the number of elements while allocating additional memory (1 - autoincrement). 
  void          Delta( uint16 newDelta )                          { m_array.Delta( newDelta ); }
  /// \ru Установить максимальное из приращений. \en Set maximum of increments. 
  void          SetMaxDelta( uint16 newDelta )                    { m_array.SetMaxDelta( newDelta ); }
  /// \ru Количество элементов в массиве. \en Count of elements in array. 
  size_t        Count()    const                                  { return m_array.Count(); }
  /// \ru Индекс последнего элемента. \en The last element index. 
  ptrdiff_t     MaxIndex() const                                  { return m_array.MaxIndex(); } 

  /// \ru Зарезервировать память под указанное количество элементов. \en Reserve memory for the specified number of elements. 
  void          Reserve( size_t additionalSpace )                 { m_array.Reserve( additionalSpace ); }
  /// \ru Удалить все элементы в массиве без освобождения памяти. \en Delete all elements from the array without freeing memory. 
  void          Flush()                                           { m_array.Flush(); }
  /// \ru Освободить неиспользуемую память. \en Free unused memory. 
  void          Adjust()                                          { m_array.Adjust(); } 

  /// \ru Получить адрес начала массива. \en Get address of the beginning of the array. 
  const SimpleName *  GetAddr() const                                   { return (SimpleName *)m_array.GetAddr(); }

  /// \ru Получить элемент по индексу. \en Get element by an index. 
  SimpleName &  operator []( size_t loc ) const                   { return m_array[loc]; }

  /// \ru Вставить элемент по индексу. \en Insert element by an index. 
  SimpleName *  AddAt( const SimpleName & ent, size_t index ) { return m_array.AddAt( ent, index ); }
  /// \ru Вставить хэш имени по индексу. \en Insert name hash by an index. 
  SimpleName *  AddAt( const MbName & ent, size_t index );
  /// \ru Добавить элемент в конец массива. \en Add an element to the end of the array.
  SimpleName *  Add  ( const SimpleName & ent ) { return m_array.Add( ent ); }
  /// \ru Добавить элемент в конец массива. \en Add an element to the end of the array.
  SimpleName *  Add  ( const MbName & ent );

  /// \ru Удалить элемент по индексу. \en Delete element by an index. 
  void          RemoveInd( size_t delIndex )                      { m_array.RemoveInd(delIndex); }
  /// \ru Удалить элементы начиная с индекса firstIdx до lastIdx-1 включительно. \en Delete elements in range from firstIdx to lastIdx-1 inclusive. 
  void          RemoveInd( size_t firstIdx, size_t lastIdx )      { m_array.RemoveInd(firstIdx, lastIdx); }

  /// \ru Вставить элемент по индексу. \en Insert element by an index. 
  SimpleName *  InsertInd( size_t index, const SimpleName & ent ) { return m_array.InsertInd( index, ent ); }
  /// \ru Вставить хэш имени по индексу. \en Insert name hash by an index. 
  SimpleName *  InsertInd( size_t index, const MbName & ent );

  /// \ru Найти объект среди элементов массива. \en Find object among elements of the array. 
  size_t        FindIt( const SimpleName & ent ) const            { return m_array.FindIt( ent ); }

  /// \ru Оператор добавления. \en Operator for adding. 
  SimpleNameArray &           operator += ( const SimpleNameArray & other ) { m_array += other.m_array; return *this; }
  /// \ru Оператор добавления. \en Operator for adding. 
  friend SArray<SimpleName> & operator += ( SArray<SimpleName> &, const SimpleNameArray & ); 

  /// \ru Оператор чтения. \en Read operator. 
  friend reader &             operator >> ( reader &, SimpleNameArray *& );
  /// \ru Оператор чтения. \en Read operator. 
  friend reader &             operator >> ( reader &, SimpleNameArray & );
  /// \ru Оператор записи. \en Write operator. 
  friend writer &             operator << ( writer &, const SimpleNameArray & );
};

//----------------------------------------------------------------------------------------
/// \ru Чтение с выделением памяти: nArr = new SimpleNameArray(); \en Reading with memory allocation: nArr = new SimpleNameArray();  
// ---
reader & operator >> ( reader & in, SimpleNameArray *& nArr );

//----------------------------------------------------------------------------------------
/// \ru Чтение. \en Reading. 
// ---
inline reader & operator >> ( reader & in, SimpleNameArray & ref )
{ 
  size_t count = ReadCOUNT( in, true/*uint_val*/ );
  if ( in.good() && count ) {
    ref.m_array.SetSize( count, true/*clear*/ );
    for ( size_t i = 0; i < count && in.good(); ++i ) {
      SimpleName item( ReadSimpleName( in ) );
      ref.Add( item ); 
    }
  }
  return in; 
}

//----------------------------------------------------------------------------------------
/// \ru Запись. \en Writing. 
// ---
inline writer & operator << ( writer & out, const SimpleNameArray & ref )
{ 
  size_t count = ref.Count();
  ::WriteCOUNT( out, count );
  for ( size_t i = 0; i < count && out.good(); ++i )
    ::WriteSimpleName( out, ref.m_array[i] );
  return out; 
}

//----------------------------------------------------------------------------------------
/// Hash32
// ---
inline SimpleName Hash32( const SimpleNameArray & snArr ) { 
  return (SimpleName)::Hash32( (uint8 *)snArr.GetAddr(), snArr.Count() * sizeofSimpleName );
}

//----------------------------------------------------------------------------------------
/// \ru Оператор конкатенации. \en Concatenation operator. 
// ---
inline SArray<SimpleName> & operator += ( SArray<SimpleName> & array, const SimpleNameArray & other ) 
{ 
  array += other.m_array; 
  return array; 
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Укороченное множество простых имен. \en Truncated set of simple names. 
//
//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------
/** \brief \ru Укороченное множество простых имен.
           \en Truncated set of simple names. \~
  \details \ru Укороченное множество простых имен состоит из базовых и обычных элементов. \n
           \en Truncated set of simple names consists of basic and ordinary elements. \n \~
  \ingroup Names
*/
// ---
struct MATH_CLASS MbIdArr : private LiSArray<SimpleName> 
{
  friend class MbName;
private:
  uint16              countBase; ///< \ru Количество элементов в базовой части. \en The count of elements in base part. 
  mutable SimpleName  hash;      ///< \ru Хэш множества простых имен. \en The hash of simple names` set. 
protected://public:
  MbFlags             flags; ///< \ru Флаги. \en Flags.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbIdArr()                    : LiSArray<SimpleName>(), countBase(0), hash(SIMPLENAME_MAX), flags() {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbIdArr( const MbIdArr & o ) : LiSArray<SimpleName>(o), countBase(o.countBase), hash( o.hash ), flags(o.flags) {}

public:
        SimpleName    Hash() const; ///< \ru Вычислить хэш себя. \en Calculate hash of itself. 
        void          FlashHash()  { hash = SIMPLENAME_MAX; } ///< \ru Сбросить свой хэш. \en Reset hash value.

        size_t        CountAll()    const { return Count();   } ///< \ru Дать количество элементов массива. \en Get the number of elements in the array. 
        size_t        CountBase()   const { return countBase; } ///< \ru Дать количество элементов массива в базовой части. \en Get the number of elements in base part. 

        /// \ru Обнулить количество элементов \en Set the number of elements to null 
        void          Flush       () { LiSArray<SimpleName>::Flush(); countBase = 0; hash = SIMPLENAME_MAX; }

        bool          IsEmpty     ()                        const;  ///< \ru Множество пуст? \en Is the array empty? 
        bool          GetCut      ( SimpleName & cutIndex ) const;  ///< \ru Получение индекса разрезки. \en Get an index of a cutaway. 
        void          SetCopyIndex( SimpleName ci );                ///< \ru Установка индекса копирования. \en Set an index of copying. 
        bool          GetCopyIndex( SimpleName & ci )       const;  ///< \ru Получение индекса копирования. \en Get an index of copying. 
        size_t        SizeOf() const; ///< \ru Размер в памяти. \en Size in memory. 

        /// \ru Добавить основной элемент в конец массива. \en Add main element to the end of the array. 
        SimpleName *  AddBase      ( const SimpleName & ent ) { FlashHash(); return InsertInd( countBase++, ent ); }
        /// \ru Добавить дополнительный элемент в конец массива. \en Add additional element to the end of the array. 
        SimpleName *  AddExtra     ( const SimpleName & ent ) { FlashHash(); return Add( ent ); }
        /// \ru Удалить основное элемент из массива. \en Delete main element from the array. 
        void          RemoveIndBase ( size_t delIndex ) { C3D_ASSERT(delIndex <  countBase); RemoveInd( delIndex ); countBase--; FlashHash(); }
        /// \ru Удалить дополнительный элемент из массива. \en Delete additional element from the array. 
        void          RemoveIndExtra( size_t delIndex ) { C3D_ASSERT(delIndex >= countBase); RemoveInd( delIndex ); FlashHash(); }
        /// \ru Получить основное простое имя по индексу. \en Get main simple name by an index. 
  const SimpleName &  GetValueBase( size_t index ) const   { C3D_ASSERT(index<countBase); return parr[index]; }
        /// \ru Установить основное простое имя по индексу. \en Set main simple name by an index. 
        void          SetValueBase( SimpleName v, size_t index  ) { C3D_ASSERT(index<countBase); parr[index] = v; FlashHash(); }
        /// \ru Получить дополнительное простое имя по индексу. \en Get additional simple name by an index. 
  const SimpleName &  GetValueExtra( size_t index ) const  { C3D_ASSERT(index>=countBase && index<count); return parr[index]; }
        /// \ru Установить дополнительное простое имя по индексу. \en Set additional simple name by an index. 
        void          SetValueExtra( SimpleName v, size_t index ) { C3D_ASSERT(index>=countBase && index<count); parr[index] = v; FlashHash(); }
public:
        /// \ru Оператор добавления. \en Operator for adding. 
        void          operator += ( const MbIdArr & other );
        /// \ru Оператор присваивания. \en An assignment operator. 
        void          operator =  ( const MbIdArr & other ) { LiSArray<SimpleName>::operator = ( other ); countBase = other.countBase; hash = other.hash; flags = other.flags; }
        /// \ru Функция присваивания (без копирования флагов). \en Assignment function (without copying of flags). 
        void          Assign( const MbIdArr & other ) { LiSArray<SimpleName>::operator = ( other ); countBase = other.countBase; hash = other.hash; }

  /// \ru Получить адрес массива. \en Get address of the array. 
  using LiSArray<SimpleName>::GetAddr;

KNOWN_OBJECTS_RW_REF_OPERATORS( MbIdArr )
};

//----------------------------------------------------------------------------------------
// \ru Вычислить хэш себя. \en Calculate hash of itself. 
// ---
inline SimpleName MbIdArr::Hash() const
{ 
  if ( hash == SIMPLENAME_MAX )
    hash = ::Hash32( (uint8*)parr, count * sizeofSimpleName/*4*/ );
  return hash;
} 

//----------------------------------------------------------------------------------------
// \ru Размер в памяти \en Size in memory 
// ---
inline size_t MbIdArr::SizeOf() const
{
  size_t size = sizeof(MbFlags);
  size += sizeof(LiSArray<SimpleName>) + Count() * sizeofSimpleName; //-V119
  size += sizeofSimpleName;
  return size;
}

//----------------------------------------------------------------------------------------
//
// ---
inline void MbIdArr::operator += ( const MbIdArr & other ) 
{ 
  C3D_ASSERT( CountAll() == CountBase() );
  if ( CountAll() == CountBase() ) {
    LiSArray<SimpleName>::operator += ( other );
    flags   = other.flags;

    C3D_ASSERT( (countBase + other.countBase) <= SYS_MAX_UINT16 ); // \ru Превышение размерности uint16 \en Exceeding of size of uint16 
    countBase = (uint16)(countBase + other.countBase);
    FlashHash();
  }
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Имя объекта. \en A name of an object. 
//
//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------
/** \brief \ru Имя объекта.
           \en A name of an object. \~
  \details \ru Имя топологического объекта (автоматически генерируемый атрибут). \n
               Не используйте главные имена из диапазона MbName::ReservedMainNames (исключение - MbName::ReservedMainNames::rmn_DefaultName). \n
           \en A name of a topological object (automatically generated attribute).  \n
               Do not use the main names from the range MbName::ReservedMainNames (exception - MbName::ReservedMainNames::rmn_DefaultName). \n \~
  \ingroup Names
*/ // ---
class MATH_CLASS MbName {
public:
    typedef std_unique_ptr<MbName> UniqueNamePtr;

public :
  /// \ru Индекс имени. \en A name index. 
  enum EIndexes
  {             // v e f
    // i_Main,  // * * *
    // i_First, // * * *
    // i_Cut,   // - + +
    // i_Copy,  // - - +
    // i_Extra, // - - +
    i_Main,     ///< \ru Индекс главного имени. \en Main name index. 
    i_First,    ///< \ru Индекс уникального имени, содержащего в себе hash, построенный по жестким правилам. \en Index of unique name which includes hash constructed by strict rules. 
    i_Cut,      ///< \ru Индекс индекса разрезанности. \en Index of index of cutaway. 
    i_Copy,     ///< \ru Индекс индекса копирования. \en Index of index of copying. 
    i_Extra,    ///< \ru Индекс предыдущего hash'a копирования. \en Index of previous hash of copying. 
    i_PseudoCopy = -1, ///< \ru Индекс псевдо копирования. \en Index of pseudo copying. 
  };
  /// \ru Основной индекс имени. \en Main index of name. 
  enum BaseNameIndex
  {               // v e f
    // bni_Main,  // * * *
    // bni_First, // * * *
    // bni_Cut,   // - + +
    bni_Main,     ///< \ru Индекс главного имени. \en Main name index. 
    bni_First,    ///< \ru Индекс уникального имени, содержащего в себе hash, построенный по жестким правилам. \en Index of unique name which includes hash constructed by strict rules. 
    bni_Cut,      ///< \ru Индекс индекса разрезанности (может нести признак разрезанности). \en Index of index of cutaway (can indicate to cutaway). 
    bni_Total,    ///< \ru Максимальное размер базовой части имени. \en Maximum size of base part of name. 
  };
  /// \ru Дополнительный индекс имени. \en Additional index of name. 
  enum ExtraNameIndex
  {               // v e f
    // eni_Copy,  // - - +
    // eni_Extra, // - - +
    eni_Copy,     ///< \ru Индекс индекса копирования. \en Index of index of copying. 
    eni_Extra,    ///< \ru Индекс предыдущего hash'a копирования. \en Index of previous hash of copying. 
    eni_Total,    ///< \ru Периодичность структуры индексов. \en Periodicity of structure of indices. 
  };
  /// \ru Зарезервированные главные имена. \en Reserved main names. 
  enum ReservedMainNames
  {
    rmn_EmergencyName      = -5, ///< \ru Системное аварийное имя для замены. \en Emergency name for replacing. 
    rmn_DummyFaceName      = -4, ///< \ru Системное имя фиктивной грани. \en Default name of dummy face. 
    rmn_ReservedName       = -3, ///< \ru Системное имя резервное. \en Reserved name.
    rmn_SectionItemName    = -2, ///< \ru Системное имя секущего объекта. \en Section item name.
    rmn_DefaultName        = -1, ///< \ru Системное имя по умолчанию (= SIMPLENAME_MAX). \en Default name (= SIMPLENAME_MAX).
  };
  // The name -2 is also reserved for system names in the Kompas CAD.

protected:
  /// \ru Флаги. \en Flags. 
  enum EFlags {
    f_Cut       = 0x01, ///< \ru Примитив разрезан. \en Primitive is cut. 
    f_Sheet     = 0x02, ///< \ru Примитив является листовым. (Действителен только для граней) \en Primitive is sheet. (Valid only for faces) 
    f_InnerBend = 0x04, ///< \ru Примитив является внутренней гранью сгиба. (Действителен только для граней) //-V112 \en Primitive is an internal face of bend. (Valid only for faces) //-V112 
    f_OuterBend = 0x08, ///< \ru Примитив является внешней гранью сгиба. (Действителен только для граней) \en Primitive is an external face of bend. (Valid only for faces) 
    f_SideBend  = 0x10, ///< \ru Примитив является боковой гранью сгиба. (Действителен только для граней) \en Primitive is a side face of bend. (Valid only for faces)
    f_RibBend   = 0x20, ///< \ru Примитив является гранью ребра жесткости листового тела. (Действителен только для граней) \en Primitive is a face of reinforcement rib of sheet solid. (Valid only for faces)
  };

protected:
  MbIdArr   defNames; ///< \ru Множество идентификаторов. \en An array of identifiers. 

public:
  static const  UniqueNamePtr uniqueFaceName; ///< \ru Уникальное имя фиктивной грани. \en Unique name of dummy face.

public :
  /// \ru Конструктор по умолчанию \en Default constructor 
  MbName() : defNames() {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbName( const MbName & other ) : defNames( other.defNames ) {}
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbName();
public:

  /// \ru Получить главное имя. \en Get main name. 
  SimpleName  GetMainName() const;        
  /// \ru Установить главное имя. \en Set main name. 
  bool        SetMainName( SimpleName n );
  /// \ru Установить имя. \en Set name. 
  void        SetName    ( const MbName &, bool setFlags = true ); 

  /// \ru Пуст ли массив идентификаторов имени. \en Whether the array of name identifiers is empty. 
  bool        IsEmpty    ()  const { return defNames.IsEmpty(); } 
  ///< \ru Очистить массив идентификаторов имени. \en Clear array of name identifiers. 
  void        SetEmpty   () { defNames.Flush(); }

  /// \ru Дать количество элементов массива. \en Get the number of elements in array. 
  size_t      CountAll   ()  const { return defNames.CountAll();  } 
  /// \ru Дать количество элементов массива в базовой части. \en Get the number of array elements in base part. 
  size_t      CountBase  ()  const { return defNames.CountBase(); } 

  /// \ru Извлечь имена в массив. \en Extract names into array. 
  void        AddNamesBase( SimpleNameArray & to ) const; 

  /// \ru Дать или сгенерировать основное имя. \en Get or generate the main name. 
  SimpleName  GetNameBase ( size_t i ) const;
  /// \ru Дать или сгенерировать дополнительное имя. \en Get or generate the additional name. 
  SimpleName  GetNameExtra( size_t i ) const;

  ///< \ru Получение индекса разрезки. \en Get an index of a cutaway. 
  bool        IsCutIndex() const;
  /// \ru Получение индекса разрезки. \en Get an index of a cutaway. 
  bool        GetCutIndex( SimpleName & cutIndex ) const { return defNames.GetCut( cutIndex );  }
  /// \ru Установка индекса разрезки. \en Set an index of cutaway. 
  void        SetCutIndex( SimpleName cutIndex );
  /// \ru Удаление индекса разрезки. \en Delete an index of cutaway. 
  bool        RemoveCutIndex();

  /// \ru Получить первое имя. \en Get first name. 
  SimpleName  GetFirstName()                    const { return (defNames.CountBase() > (size_t)i_First) ? defNames.GetValueBase((size_t)i_First) : -1; }
  /// \ru Прямой доступ к первому имени. \en Direct access to the first name. 
  SimpleName  GetFirstNameDirect()              const { C3D_ASSERT(defNames.CountBase() > (size_t)i_First); return defNames.GetValueBase((size_t)i_First);     }
  /// \ru Прямой доступ к первому имени. \en Direct access to the first name. 
  void        SetFirstNameDirect( SimpleName fi )     { C3D_ASSERT(defNames.CountBase() > (size_t)i_First);        defNames.SetValueBase(fi, (size_t)i_First); } 

  /// \ru Получение значения флага порезанности. \en Get flag of cutaway. 
  bool        IsCutFlag() const;  
  /// \ru Установление значения флага порезанности. \en Set flag of cutaway. 
  void        SetCutFlag( bool s = true );

  /// \ru Установление значения флага листового примитива. \en Set flag of sheet primitive. 
  void        SetSheet( bool s );
  /// \ru Установка значения флага внутренней части сгиба. \en Set flag of internal part of bend. 
  void        SetInnerBend( bool s );
  /// \ru Установка значения флага внешней части сгиба. \en Set flag of external part of bend. 
  void        SetOuterBend( bool s );
  /// \ru Установка значения флага боковой грани сгиба. \en Set flag of side part of bend.
  void        SetSideBend( bool s );
  /// \ru Установка значения флага грани ребра жесткости листового тела. \en Set flag of reinforcement rib part of sheet solid.
  void        SetStampRibBend( bool s );
  /// \ru Получение значения флага листового примитива. \en Get flag of sheet primitive. 
  bool        IsSheet() const;
  /// \ru Получение значения флага внутренней части сгиба. \en Get flag of internal part of bend. 
  bool        IsInnerBend() const;
  /// \ru Получение значения флага внешней части сгиба. \en Get flag of external part of bend. 
  bool        IsOuterBend() const;
  /// \ru Получение значения флага боковой грани сгиба. \en Get flag of side part of bend.
  bool        IsSideBend() const;
  /// \ru Получение значения флага грани ребра жесткости листового тела. \en Get flag of reinforcement rib part of sheet solid.
  bool        IsStampRibBend() const;

  /// \ru Установка индекса копирования. \en Set an index of copying. 
  void        SetCopyIndex( SimpleName ci ) { defNames.SetCopyIndex( ci ); }
  /// \ru Получение индекса копирования. \en Get an index of copying. 
  bool        GetCopyIndex( SimpleName & ci ) const { return defNames.GetCopyIndex( ci ); }

  /** \brief \ru Установить положение в сетке копирования.
             \en Set a position in grid of copying. \~
    \details \ru Установить положение копии в сетке копирования при размножении объекта по прямоугольной или концентрической сетке. \n
             \en Set a copy position in the copy grid when the object is reproduced on a rectangular or concentric grid. \n \~
    \param[in] row - \ru Индекс ряда.
                     \en Index of row. \~
    \param[in] col - \ru Индекс солонки.
                     \en Index of column. \~
    \return \ru true - если индекс установлен, иначе - false.
            \en true, if the copy position was set, otherwise false. \~  */
  bool        SetCopyPosition( size_t row, size_t col );

  /** \brief \ru Выдать положение в сетке копирования.
             \en Get position in grid of copying. \~
    \details \ru Выдать положение копии в сетке копирования при размножении объекта по прямоугольной или концентрической сетке. \n
             \en Get a copy position in the copy grid when the object is reproduced on a rectangular or concentric grid. \n \~
    \param[out] row - \ru Индекс ряда.
                     \en Index of row. \~
    \param[out] col - \ru Индекс солонки.
                     \en Index of column. \~
    \return \ru true - если положение копии было найдено, иначе - false.
            \en true, if the copy position was find, otherwise false. \~  */
  bool        GetCopyPosition( ptrdiff_t & row, ptrdiff_t & col );

  /// \ru Можно ли получить индексы копирования. \en Whether the indices of copying can be obtained.  
  bool        IsCopied() const { return defNames.CountAll() > defNames.CountBase(); }

  /// \ru Выдать главное имя источника для копирования, вызывать только после проверки - IsCopied(); \en Get the main name of source for copying, to be called only after check by IsCopied(); 
  SimpleName  GetCopySourceName() const { return defNames.GetValueExtra( CountAll() - 1 ); }
  /** \brief \ru Получить массив индексов копирования.
             \en Get array of copying indices. \~
    \details \ru Получить заданное количество индексов копирования в обратном порядке. 
             Если запросить больше чем есть - не даст ничего. \n
             \en Get the given count of copying indices in reverse order. 
             If requested more than exist, then nothing will be returned. \n \~
    \param[out] indexes - \ru Множество индексов копирования.
                          \en Array of copying indices. \~
    \param[in,out] count - \ru Количество запрашиваемых индексов [in], количество полученных индексов [out].
                           \en Count of the requested indices [in], count of the obtained indices [out]. \~
  */
  void        GetCopyIndices( SArray<SimpleName> & indexes , size_t & count ) const; 

  /// \ru Вычислить хэш себя. \en Calculate hash of itself. 
  SimpleName  Hash()                            const { return defNames.Hash(); }
  /// \ru Оператор равенства. \en An equality operator. 
  bool        operator == ( const MbName &   )  const; 
  /// \ru Оператор сравнения. \en Comparison operator. 
  bool        operator <  ( const MbName &   )  const; 
  /// \ru Оператор неравенства. \en Inequality operator. 
  bool        operator != ( const MbName & n )  const { return !( operator == (n) ); } 

  /// \ru Выдать свойства объекта. \en Get properties of the object. 
  void        GetProperties( MbProperties & ); 
  /// \ru Записать свойства объекта. \en Set properties of the object. 
  void        SetProperties( const MbProperties & ); 
  /// \ru Преобразовать имя в строку. \en Convert name to string. 
  void        ToString( c3d::string_t & strName ) const; 
  /// \ru Преобразовать в имя из строки. \en Convert name from string. 
  void        FromString( const c3d::string_t & strName ); 
  /// \ru Размер в памяти. \en Size in memory. 
  size_t      SizeOf() const { return defNames.SizeOf(); } 

//private:
  /// \ru Оператор присваивания. \en An assignment operator. 
  void        operator = ( const MbName & other ) { defNames = other.defNames; }

public:
  /// \ru Функция присваивания (без копирования флагов). \en Assignment function (without copying of flags). 
  void        Assign( const MbName & other ) { defNames.Assign( other.defNames ); }

  /// \ru Сделать из имени шаблон. \en Create template from name. 
  void        MakeTemplate() { 
    C3D_ASSERT( defNames.CountBase() );
    if ( defNames.CountBase() > (size_t)i_First ) {
      SetFirstNameDirect( 0 );
      if ( defNames.CountBase() > (size_t)i_Cut ) SetCutIndex( 0 );
    }
    else
      defNames.AddBase( 0 );
    C3D_ASSERT( *this != *uniqueFaceName );
  }

  /// \ru Уникальное имя фиктивной грани. \en Unique name of dummy face.
  static UniqueNamePtr UniqueFaceName()
  {
    UniqueNamePtr name( new MbName );
    name->defNames.AddBase( static_cast<SimpleName>(rmn_DummyFaceName) ); // i_Main
    name->defNames.AddBase( 0 );                                          // i_First
    return name;
  }

  friend class MATH_CLASS MbNameMaker;
  friend class MATH_CLASS MbSNameMaker;
  friend MATH_FUNC (int) MbDefNameCompare   ( const MbName & n1, const MbName & n2 );
  friend MATH_FUNC (int) MbMemDefNameCompare( const MbName & n1, const MbName & n2 );

KNOWN_OBJECTS_RW_REF_OPERATORS_EX( MbName, MATH_FUNC_EX ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class 
};


//----------------------------------------------------------------------------------------
//
// ---
inline bool MbIdArr::IsEmpty() const {
  // \ru IsEmpty проверять parr[MbName::i_Main] только для count == 1 \en IsEmpty check parr[MbName::i_Main] only for count == 1 
  // \ru Если count > 1 - считать не пустым \en If count > 1, then it is considered as non-empty 
  return ( Count() > (size_t)MbName::i_Main ) ? ( (Count() - 1) == (size_t)MbName::i_Main ? !parr[(size_t)MbName::i_Main]  : false ) : true;
}


//----------------------------------------------------------------------------------------
// \ru Получение индекса разрезки \en Get an index of a cutaway 
// ---
inline bool MbIdArr::GetCut( SimpleName & cutIndex ) const
{
  if ( Count() > (size_t)MbName::i_Cut )  {
    cutIndex = parr[(size_t)MbName::i_Cut];
    return true;
  }
  return false;
}


//----------------------------------------------------------------------------------------
// \ru Получение индекса копирования \en Get an index of copying 
// ---
inline bool MbIdArr::GetCopyIndex( SimpleName & ci ) const
{
  if ( Count() > (size_t)MbName::i_Copy ) {
    ci = parr[(size_t)MbName::i_Copy];
    return true;
  }
  return false;
}


//------------------------------------------------------------------------------
// \ru Получить главное имя. \en Get main name. 
// ---
inline SimpleName MbName::GetMainName() const
{
  if ( defNames.CountBase() > (size_t)i_Main )
    return defNames.GetValueBase( (size_t)i_Main );
  return 0;
}


//------------------------------------------------------------------------------
// \ru Установить главное имя. \en Set main name. 
// ---
inline bool MbName::SetMainName( SimpleName n )
{
  bool res = true;
  if ( static_cast<SimpleName>(rmn_DummyFaceName) == n  ) { // Reserved for unique name of dummy face (-1 = SIMPLENAME_MAX, -2 is already used for Kompas CAD and It's the error on their side)
    n = static_cast<SimpleName>(rmn_EmergencyName);
    C3D_ASSERT_UNCONDITIONAL( false );
    res = false;
  }

  if ( defNames.CountBase() > 0 )
    defNames.SetValueBase( n, 0 );
  else
    defNames.AddBase( n );

  return res;
}


//----------------------------------------------------------------------------------------
// \ru Проверка на равенство. \en Check for equality. 
// ---
inline bool MbName::operator == ( const MbName & n ) const
{
  if ( defNames.CountAll() == n.defNames.CountAll() ) {
    if ( defNames.CountAll() ) {
      // C3D-510 return (::memcmp( defNames.GetAddr(), n.defNames.GetAddr(), defNames.CountAll() * sizeofSimpleName ) == 0);
      return (defNames.Hash() == n.defNames.Hash());
    }
    return true;
  }
  return false;
}


//----------------------------------------------------------------------------------------
// \ru Проверка не неравенство. \en Check for inequality. 
// ---
inline bool MbName::operator < ( const MbName & n ) const
{
  if ( defNames.CountAll() == n.defNames.CountAll() ) {
    if ( defNames.CountAll() ) {
      if ( defNames.Hash() != n.defNames.Hash() ) // C3D-510
        return (::memcmp( defNames.GetAddr(), n.defNames.GetAddr(), defNames.CountAll() * sizeofSimpleName ) < 0);
    }
    return false;
  }
  else if ( defNames.CountAll() < n.defNames.CountAll() )
    return true;

  return false;
}


//----------------------------------------------------------------------------------------
// \ru Получение индекса разрезки. \en Get an index of a cutaway. 
// ---
inline bool MbName::IsCutIndex() const
{
  SimpleName cutIndex = 0;
  if ( GetCutIndex( cutIndex ) )
    return ::IsGoodSimpleName( cutIndex );
  return false;
}


//----------------------------------------------------------------------------------------
// \ru Получение значения флага порезанности. \en Get flag of cutaway. 
// ---
inline bool MbName::IsCutFlag() const {
  return !!defNames.flags.GetFlagValue( f_Cut );
}


//----------------------------------------------------------------------------------------
// \ru Установление значения флага порезанности. \en Set flag of cutaway. 
// ---
inline void MbName::SetCutFlag( bool s ) {
  defNames.flags.SetFlagValue( f_Cut, s );
}


//----------------------------------------------------------------------------------------
// \ru Установление значения флага листового примитива. \en Set flag of sheet primitive. 
// ---
inline void MbName::SetSheet( bool s ) {
  defNames.flags.SetFlagValue( f_Sheet, s );
}


//----------------------------------------------------------------------------------------
// \ru Получение значения флага листового примитива. \en Get flag of sheet primitive. 
// ---
inline bool MbName::IsSheet() const {
  return !!defNames.flags.GetFlagValue( f_Sheet );
}


//----------------------------------------------------------------------------------------
// \ru Установление значения флага внутренней части сгиба. \en Set flag of internal part of bend. 
// ---
inline void MbName::SetInnerBend( bool s ) {
  defNames.flags.SetFlagValue( f_InnerBend, s );
}


//----------------------------------------------------------------------------------------
// \ru Получение значения флага внутренней части сгиба. \en Get flag of internal part of bend. 
// ---
inline bool MbName::IsInnerBend() const {
  return !!defNames.flags.GetFlagValue( f_InnerBend );
}


//----------------------------------------------------------------------------------------
// \ru Установление значения флага внешней части сгиба. \en Set flag of external part of bend. 
// ---
inline void MbName::SetOuterBend( bool s ) {
  defNames.flags.SetFlagValue( f_OuterBend, s );
}


//----------------------------------------------------------------------------------------
// \ru Получение значения флага внешней части сгиба. \en Get flag of external part of bend. 
// ---
inline bool MbName::IsOuterBend() const {
  return !!defNames.flags.GetFlagValue( f_OuterBend );
}


//----------------------------------------------------------------------------------------
// \ru Установление значения флага боковой грани сгиба. \en Set flag of side part of bend.
// ---
inline void MbName::SetSideBend( bool s ) {
  defNames.flags.SetFlagValue( f_SideBend, s );
}


//----------------------------------------------------------------------------------------
// \ru Получение значения флага боковой грани сгиба. \en Get flag of side part of bend.
// ---
inline bool MbName::IsSideBend() const {
  return !!defNames.flags.GetFlagValue( f_SideBend );
}


//----------------------------------------------------------------------------------------
// \ru Установление значения флага грани ребра жесткости листового тела. \en Set flag of reinforcement rib part of sheet solid.
// ---
inline void MbName::SetStampRibBend( bool s ) {
  defNames.flags.SetFlagValue( f_RibBend, s ); 
}


//----------------------------------------------------------------------------------------
// \ru Получение значения флага грани ребра жесткости листового тела. \en Get flag of reinforcement rib part of sheet solid.
// ---
inline bool MbName::IsStampRibBend() const {
  return !!defNames.flags.GetFlagValue( f_RibBend );
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Имя объекта и его копии. \en Name of object and its duplicate. 
//
//////////////////////////////////////////////////////////////////////////////////////////


#define ORIGINAL_MAIN_NAME    // \ru Используется для работы с массивами. \en Used for arrays treatment. 


#ifdef ORIGINAL_MAIN_NAME
//----------------------------------------------------------------------------------------
/** \brief \ru Имя объекта и его копии.
           \en Name of object and its duplicate. \~
  \details \ru Имя топологического объекта и его копии. \n
           \en Name of topological object and its duplicate. \n \~
  \ingroup Names
*/
// ---
class MATH_CLASS MbNamePair {
private:
  MbName * gageName; // \ru Имя оригинала. \en A name of original. 
  MbName * copyName; // \ru Имя копии. \en A name of duplicate.

  // могут использоваться для самостоятельного поиска
  mutable SimpleName copyHash; // \ru Кэш хеша имени оригинала. \en 

public:
  /// \ru Конструктор. \en Constructor. 
  MbNamePair( MbName * orig, MbName * copy ) : gageName( orig ), copyName( copy ), copyHash( SIMPLENAME_MAX )  {}
  /// \ru Конструктор для поиска по имени копии. \en Constructor for find by copy name. 
  MbNamePair( MbName * copy ) : gageName( NULL ), copyName( copy ), copyHash( SIMPLENAME_MAX ) {}
  /// \ru Конструктор для поиска по хешу копии. \en Constructor for find by copy hash. 
  MbNamePair( SimpleName copy ) : gageName( NULL ), copyName( NULL ), copyHash( copy ) {}
  /// \ru Деструктор. \en Destructor. 
  ~MbNamePair() {}

public:
  /// \ru Обнулить имя оригинала и имя копии. \en Set name of original and of its duplicate to null. 
  void        SetNull() { gageName = NULL; copyName = NULL; copyHash = SIMPLENAME_MAX; }
  /// \ru Оператор сравнения. \en Comparison operator. 
  bool        operator == ( const MbNamePair & other ) const;
  /// \ru Оператор меньше. \en "Less than" operator. 
  bool        operator <  ( const MbNamePair & other ) const;
  /// \ru Расчет хеша имени оригинала для сравнения. \en Original hash calculation
  SimpleName  CopyNameHash() const
  {
    if ( copyName )
      copyHash = Prepare(*copyName).Hash();
    return copyHash;
  }
  /// \ru Правило приготовления имен. \en Names prepare rules.
  static MbName Prepare( const MbName & name );

  friend class MATH_CLASS MbNamePairList;
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Таблица соответствия имён размноженных объектов. \en Table of names correspondence of duplicated objects. 
//
//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------
/** \brief \ru Таблица соответствия имён.
           \en Table of names correspondence. \~
  \details \ru Таблица соответствия имён оригиналов и их размноженных копий в массивах. \n
           \en Table of names correspondence of originals and its duplicates in arrays. \n \~
  \ingroup Names
*/
// ---
class MATH_CLASS MbNamePairList {
private:
  CSSArray<MbNamePair> checkList;  ///< \ru Имена объектов и их копий. \en Names of objects and of its duplicates. 

public:
  /// \ru Конструктор. \en Constructor. 
  MbNamePairList( size_t count = 0 ) : checkList( count, 1 ) {}
  /// \ru Деструктор. \en Destructor. 
  ~MbNamePairList() { DeleteNames(); }

public:
  /// \ru Добавить имя объекта и имя его копии, имя оригинала и копии должно быть создано по new. \en Store names of object and its duplicate, which are created by new. 
  void        AddNameData( MbName * orig, MbName * copy )
  {
    C3D_ASSERT( (orig != NULL) && (copy != NULL) );
    if ( (orig != NULL) && (copy != NULL) ) {
      checkList.Add( MbNamePair( orig, copy ) );
    }
  }
  /// \ru Выделить память под элементы. \en Allocate memory for elements. 
  void        Reserve( size_t count ) { checkList.Reserve( count ); }
  /// \ru Очистить массив не удаляя память под элементы. \en Erase array without deleting memory for elements. 
  void        Erase() { DeleteNames(); checkList.Flush(); }
  /// \ru Удалить память под элементы. \en Delete memory for elements. 
  void        Free() { DeleteNames(); checkList.HardFlush(); }
  /// \ru Удалить ненужные элементы по именам копий. \en Clean up unnecessary pairs by name copies. 
  bool        Clean( const std::vector<const MbName *> & delNamesCopies );
  /// \ru Заменить имена копий. \en Replace names copies. 
  bool        Replace( const MbName & newNameCopies, const std::vector<const MbName *> & oldNamesCopies );

  /// \ru Найти имя объекта по имени его копии. \en Find name of object by name of its duplicate. 
  const MbName * FindOriginalByCopy( const MbName * copy );
  /// \ru Найти имя копии объекта по имени его оригинала. \en Find name of duplicate object by name of its original. 
  const MbName * FindCopyByOriginal( const MbName & original ) const;
  /// \ru Найти имя объекта по хешу его копии. \en Find name of object by hash of its duplicate. 
  const MbName * FindOriginalByCopy( const SimpleName & originalHash );

  const CSSArray<MbNamePair> & GetCheckList() const { return checkList; }

  friend class MATH_CLASS MbNameMaker;
  friend class MATH_CLASS MbSNameMaker;

private:
  /// \ru Удалить имена в каждом элементе. \en Delete names in each element. 
  void        DeleteNames();
  /// \ru Обнулить имя оригинала и имя копии в каждом элементе. \en Set name of original and of its duplicate to null in each element. 
  void        SetNull();
};
#endif //  ORIGINAL_MAIN_NAME


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Генератор имен. \en Name generator. 
//
//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------
/** \brief \ru Генератор имен.
           \en Name generator. \~
  \details \ru Генератор имен топологических объектов по заданному шаблону. \n
               Не используйте главные имена из диапазона MbName::ReservedMainNames (исключение - MbName::ReservedMainNames::rmn_DefaultName). \n
           \en Generator of names of topological objects by the given template. \n
               Do not use the main names from the range MbName::ReservedMainNames (exception - MbName::ReservedMainNames::rmn_DefaultName). \n \~
  \internal
\ru Надо добиться того, чтобы имена не могли создаваться в обход определенных правил
  и одновременно предусмотреть возможность создания новых правил!!!
  Задача противоречивая - попробуем вот так.
  Если надо создать новое правило генерации имени, то сделайте наследника от этого класса
  напишите новое правило создающее MbIdArr (LiSArray<SimpleName>) (или просто SimpleName)
  и отдайте на вход MakeName
\en It is necessary to achieve that names can't be created passing over certain rules
  and at the same time to provide possibility for creating new rules!!!
  Task is inconsistent - try so.
  If it is necessary to create a new rule for generating name, then inherit from this class,
  write a new rule that creates MbIdArr (LiSArray<SimpleName>) (or simply SimpleName)
  and set it as input to MakeName \~
  \endinternal
  \ingroup Names 
*/ 
//---
class MATH_CLASS MbNameMaker {

protected:
  MbName                    defName;  ///< \ru Шаблон имени. \en Name template. 
  MbNameVersion             version;  ///< \ru Версия изготовления. \en Version of manufacture. 
#ifdef ORIGINAL_MAIN_NAME
  SimpleName                original; ///< \ru Исходное главное имя. \en Source main name. 
  mutable MbNamePairList *  nameList; ///< \ru Таблица соответствия имён оригиналов и их копий. \en Table of correspondence of names of originals and its duplicates. 
#endif //  ORIGINAL_MAIN_NAME

public:
  /// \ru Конструктор по главному имени. \en Constructor by main name. 
  MbNameMaker( SimpleName mn  );
  /// \ru Конструктор по имени. \en Constructor by name. 
  MbNameMaker( const MbName & _name );
  /// \ru Конструктор другому генератору имен. \en Constructor by another generator of names. 
  MbNameMaker ( const MbNameMaker & o );
  /// \ru Деструктор. \en Destructor. 
  ~MbNameMaker() {}

public:
  /// \ru Доступ к главному имени. \en Access to main name. 
  SimpleName  GetMainName () const         { return defName.GetMainName(); } 
  /// \ru Установка главного имени. \en Set main name. 
  void        SetMainName ( SimpleName n ) { defName.SetMainName( n ); } 
  /// \ru Версия изготовления. \en Version of manufacture. 
  const VersionContainer & GetVersionContainer() const { return version.GetVersionContainer(); } 
  /// \ru Версия изготовления. \en Version of manufacture. 
  const MbNameVersion    & GetMbNameVersion() const    { return version; } 
  /// \ru Версия изготовления. \en Version of manufacture. 
  void        SetVersion( const MbNameVersion & v ) { version = v; }   

  /// \ru Получить версию математического ядра. \en Get version of the mathematical kernel. 
  VERSION     GetMathVersion() const { return version.GetVersionContainer().GetMathVersion(); } 
  /// \ru Установить версию математического ребра. \en Set version of the mathematical kernel. 
  void        SetMathVersion( VERSION v ) { version.SetVersion( 0, v ); } 

protected:
  /// \ru Генерация имени name по шаблону и двум простым именам. \en Generate 'name' name by template and two simple names. 
  void        MakeNameBy( SimpleName snFirst, SimpleName snCut, MbName & name ) const;
  /// \ru Генерация имени name шаблону и источнику для грани скругления. \en Generate 'name' name by template and by source for fillet face. 
  void        MakeNameBy( const MbName & source, MbName & name ) const; 
public:
  /// \ru Генерация имени name по шаблону и простому имени. \en Generate 'name' name by template and by simple name. 
  void        MakeNameBy( SimpleName sn, MbName & name ) const;
  /// \ru Генерация имени name по двум простым именам SimpleName. \en Generate 'name' name by two SimpleName simple names. 
  void        MakeName( SimpleName sn1, SimpleName sn2, MbName & name ) const; 
  /// \ru Генерация имени name по простому имени SimpleName. \en Generate 'name' name by SimpleName simple name. 
  void        MakeName( SimpleName sn, MbName & name ) const; 
  /// \ru Генерация имени name для грани скругления. \en Generate 'name' name for fillet face. 
  void        MakeFilletFaceName( const MbName &, MbName & name ) const; 

#ifdef ORIGINAL_MAIN_NAME
  /// \ru Установить исходное главное имя и таблицу соответствия имён. \en Set original main name and table of name correspondence. 
  void        SetOriginalMainName( SimpleName orig, MbNamePairList * list ) { original = orig; nameList = list; }
  /// \ru Исходное главное имя. \en Source main name. 
  SimpleName  GetOriginalMainName() const { return original; }
  /// \ru Таблица соответствия имён оригиналов и их копий. \en Table of correspondence of names of originals and of its duplicates. 
  MbNamePairList * GetNameList() const { return nameList; } 
  /// \ru Получить генератор имен оригинала, считая, что это именователь копии. \en Get original name maker. 
  MbNameMaker GetOriginalNameMaker() const;
  /// \ru Удалить ненужные элементы по именам копий. \en Clean up unnecessary pairs by name copies. 
  bool        CleanNameList( std::vector<const MbName *> & delNamesCopies ) const;
  /// \ru Заменить имена копий. \en Replace names copies. 
  bool        ReplaceNameList( const MbName & newNameCopies, const std::vector<const MbName *> & oldNamesCopies ) const;
#endif //  ORIGINAL_MAIN_NAME

  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool        IsSame( const MbNameMaker & ) const;

protected:
  /// \ru Оператор чтения. \en Read operator. 
  friend MATH_FUNC (reader &) operator >> ( reader & in,        MbNameMaker & ref );
  /// \ru Оператор записи. \en Write operator. 
  friend MATH_FUNC (writer &) operator << ( writer & out, const MbNameMaker & ref );
  /// \ru Оператор записи. \en Write operator. 
  friend MATH_FUNC (writer &) operator << ( writer & out,       MbNameMaker & ref ) { return operator << ( out, static_cast<const MbNameMaker &>(ref) ); }

private:
  void operator = ( const MbNameMaker & ); // \ru Не реализовано. \en Not implemented. 
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Генератор имен c добавлением информации об источниках. \en Generator of names with addition of information about sources. 
//
//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------
/** \brief \ru Генератор имен c добавками к имени.
           \en Generator of names with additions to name. \~
  \details \ru Генератор имен (именователь) топологических объектов c добавлением информации об источниках. \n
    Делает имена граням. Не используйте главные имена из диапазона MbName::ReservedMainNames (исключение - MbName::ReservedMainNames::rmn_DefaultName).
           \en Generator of names (name-maker) of topological objects with addition of information about sources. \n
    Makes names for faces. Do not use the main names from the range MbName::ReservedMainNames (exception - MbName::ReservedMainNames::rmn_DefaultName). \~
  \ingroup Names
*/ //---
class MATH_CLASS MbSNameMaker : public SimpleNameArray, public MbNameMaker {

public:
  /// \ru Типы добавок к имени. \en Types of additions to name. 
  enum ESides {
    i_SideNone  =  0, ///< \ru Никакое. \en None. 
    i_SidePlus  =  1, ///< \ru Положительное. \en Positive. 
    i_SideMinus = -1, ///< \ru Отрицательное. \en Negative. 
  };

protected:
  ESides     sideAdd; ///< \ru Добавка к имени боковой грани. \en Addition to name of a side face. 
  SimpleName buttAdd; ///< \ru Добавка к имени торцевой грани. \en Addition to name of a butt face. 
  bool       cpyHist; ///< \ru Добавлять индексы копирования и старые имена в конец (не записываем). \en Whether to add indices of copying and old names to the end (don't write). 
private:
  bool       addParentNamesAttributes; ///< \ru Добавлять атрибуты типа имя в объединенные грани. \en Whether to add name attributes to united faces. 

public:
  /// \ru Конструктор. \en Constructor. 
  explicit MbSNameMaker ( SimpleName _mainName = UNDEFINED_SNAME, ESides _sideAdd = MbSNameMaker::i_SideNone, SimpleName _buttAdd = 0 );
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbSNameMaker ( const MbSNameMaker & other );

  /// \ru Инициализировать по другому именователю. \en Initialize by another name-maker. 
  void        SetName( const MbSNameMaker & other, bool setVersion = false );
  /// \ru Получить простое имя из массива с контролем выхода за границы \en Get simple name from array with control of overruning 
  SimpleName  GetName( size_t i ) const; 
  /// \ru Инверсия. \en Inversion. 
  void        Inverse(); 

  /// \ru Выдать имя в виде условного положения в сетке копирования (для массивов). \en Get name in form of conditional position in grid of copying (for arrays). 
  bool        GetNameAsPosition( size_t i, ptrdiff_t & row, ptrdiff_t & col ) const;

  /// \ru Добавка к имени боковой грани. \en Addition to name of a side face. 
  void        SetSideAdd ( ESides     s ) { sideAdd = s; } 
  /// \ru Добавка к имени торцевой грани. \en Addition to name of a butt face. 
  void        SetButtAdd ( SimpleName b ) { buttAdd = b; } 
  /// \ru Установить состояние флага работы с индексами копирования. \en Set flag state of working with indices of copying. 
  void        SetCopyHist( bool setHist ) { cpyHist = setHist; }  
  /// \ru Получить состояние флага работы с индексами копирования. \en Get flag state of working with indices of copying. 
  bool        GetCopyHist() const         { return cpyHist; }
  /// \ru Установить состояние флага добавки атрибутов типа имя в объединенные грани и ребра. \en Set flag state of addition of name attributes to united faces and edges. 
  void        SetParentNamesAttributes( bool addPNA ) { addParentNamesAttributes = addPNA; }
  /// \ru Получить состояние флага добавки атрибутов типа имя в объединенные грани и ребра. \en Get flag state of addition of name attributes to united faces and edges. 
  bool        GetParentNamesAttributes() const { return addParentNamesAttributes; }
  /// \ru Установить количество имен. \en Set count of names. 
  void        SetNamesCount( size_t newCount );

  /// \ru Генерация имени name торцевой грани: mainName, +/-defName, знак определяется направлением. \en Generate 'name' name for butt face: mainName, +/-defName, sign is defined by direction. 
  void        SetButtFaceName( MbName & name, MbSNameMaker::ESides side ) const;
  /// \ru Генерация имени name грани: mainName, hash( sideName, add ). \en Generate 'name' name for face: mainName, hash( sideName, add ). 
  void        SetFaceName( MbName & name, size_t i, SimpleName add ) const;
  /// \ru Генерация имени name каркаса. \en Generate 'name' name for frame. 
  void        SetWireName( MbName & name, size_t i ) const;
  /// \ru Генерация имени name ребра из имен граней (sense - направление ребра по отношению к подлежащей кривой). \en Generate 'name' name for edge from names of faces ('sense' is a direction of edge relative to underlined curve). 
  void        CompileEdgeName(       MbName & name,
                               const MbName * f1,
                               const MbName * f2,
                               size_t ind,
                               bool   sameSense ) const;
  /// \ru Генерация имени name по другому имени, полное совпадение. \en Generate 'name' name by other name, full coincidence. 
  void        CompileEdgeName( MbName & name, const MbName & other ) const;

  /// \ru Добавить генератор имен. \en Add name generator. 
  void        AddSNameMaker( const MbSNameMaker & other );
  /// \ru Создать с именем индекса iFrom. \en Create with name of iForm index. 
  MbSNameMaker * GetSNameMakerFrom( size_t iFrom, size_t iTo ); 
#ifdef ORIGINAL_MAIN_NAME
  /// \ru Получить генератор имен оригинала, считая, что это именователь копии. \en Get original name maker. 
  MbSNameMaker GetOriginalSNameMaker() const;
#endif // ORIGINAL_MAIN_NAME

  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool         IsSame( const MbSNameMaker & ) const;

protected:
  /// \ru Оператор чтения. \en Read operator. 
  friend MATH_FUNC (reader &) operator >> ( reader & in,        MbSNameMaker & ref );
  /// \ru Оператор записи. \en Write operator. 
  friend MATH_FUNC (writer &) operator << ( writer & out, const MbSNameMaker & ref );
  /// \ru Оператор записи. \en Write operator. 
  friend MATH_FUNC (writer &) operator << ( writer & out,       MbSNameMaker & ref ) { return operator << ( out, static_cast<const MbSNameMaker &>(ref) ); }

private:
  /// \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation, to prevent an assignment by default. 
  void operator = ( const MbSNameMaker & ); 
};


//----------------------------------------------------------------------------------------
// \ru Конструктор. \en Constructor. 
//---
inline MbSNameMaker::MbSNameMaker ( SimpleName           _mainName, // =-1
                                    MbSNameMaker::ESides _sideAdd,  // = 0
                                    SimpleName           _buttAdd ) // = 0 
  : SimpleNameArray( 0, 2      )
  , MbNameMaker    ( _mainName )
  , sideAdd        ( _sideAdd  )
  , buttAdd        ( _buttAdd  )
  , cpyHist        ( true      )
  , addParentNamesAttributes( false )
{}


//----------------------------------------------------------------------------------------
// \ru Конструктор по другому именователю. \en Constructor by other name-maker. 
// ---
inline MbSNameMaker::MbSNameMaker ( const MbSNameMaker & other )
  : SimpleNameArray( other.Count(), 2 )
  , MbNameMaker    ( other            )
  , sideAdd        ( i_SideNone       )
  , buttAdd        ( 0                )
  , cpyHist        ( true             )
  , addParentNamesAttributes( false   )
{
  SetName( other, true );
}


//----------------------------------------------------------------------------------------
// \ru Установить имя \en Set name 
// ---
inline void MbSNameMaker::SetName( const MbSNameMaker & other, bool setVersion ) 
{
  SetMainName( other.GetMainName() );
  SimpleNameArray::operator = ( (SimpleNameArray&)other );
  sideAdd = other.sideAdd;
  buttAdd = other.buttAdd;
  cpyHist = other.cpyHist;
  addParentNamesAttributes = other.addParentNamesAttributes;
  if ( setVersion )
    SetVersion( other.GetMbNameVersion() );
#ifdef ORIGINAL_MAIN_NAME
  original = other.original; 
  nameList = other.nameList; 
#endif //  ORIGINAL_MAIN_NAME
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Неклассные функция имён. \en Out-of-class functions for names.  
//
//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------
/** \brief \ru Функция сравнения имён.
           \en Name comparison function. \~ 
  \details \ru Функция сравнения имён возвращает: \n
           -1, если n1 <  n2; \n
            0, если n1 == n2; \n
           +1, если n1 >  n2; \n
           \en Name comparison function returns: \n
           -1, if n1 <  n2; \n
            0, if n1 == n2; \n
           +1, if n1 >  n2; \n \~
  \ingroup Names
*/
inline MATH_FUNC (int) MbMemDefNameCompare( const MbName & n1, const MbName & n2 )
{
  int res = -1;
  size_t count1 = n1.defNames.CountAll();
  size_t count2 = n2.defNames.CountAll();

  if ( count1 == count2 ) {
    if ( count1 )
      res = ::memcmp( n1.defNames.GetAddr(), n2.defNames.GetAddr(), count1 * sizeofSimpleName ); 
    else
      res = 0;
  }
  else if ( count1 > count2 )
    res = 1;

  return res;
}


//----------------------------------------------------------------------------------------
/** \brief \ru Функция сравнения имён.
           \en Name comparison function. \~
  \details \ru Функция сравнения имён для работы в сортированных структурах. \n
           \en Name comparison function for work with sorted structures. \n \~
  \ingroup Names
*/
// ---
inline MATH_FUNC (int) MbDefNameCompare( const MbName & n1, const MbName & n2 ) 
{
  SimpleName hash1 = n1.defNames.Hash();
  SimpleName hash2 = n2.defNames.Hash();
  return ::SimpleNameCompare( hash1, hash2 );
}


//----------------------------------------------------------------------------------------
// \ru часто встречающаяся комбинация - hash от SArray'a \en Frequently occurring combination - hash of SArray 
// ---
inline SimpleName Hash32( const SArray<SimpleName> & arr )  {
  return Hash32( (uint8*)arr.GetAddr(), arr.Count() * sizeofSimpleName );
}


//----------------------------------------------------------------------------------------
// \ru Расчет модификатора имени примитива \en Calculate of modifier of name of primitive 
// ---
inline SimpleName CalcNameModifier( const MbName & name, const SArray<SimpleName> & path ) 
{
  return ( (path.Count()) ? ::Hash32SN(name.Hash(), Hash32(path)) : name.Hash() );
}


//----------------------------------------------------------------------------------------
/** \brief \ru Сравнить пути в виде массива идентификаторов.
           \en Compare paths as array of identifiers. \~
  \details \ru Сравнить пути в виде массива идентификаторов. \n
           \en Compare paths as array of identifiers. \n \~
  \return \ru Возвращает true, если пути совпадают.
          \en Returns true if paths is coincident. \~
  \ingroup Names
*/
// ---
MATH_FUNC (bool) IsEqualPaths( const SArray<SimpleName> & path1, 
                               const SArray<SimpleName> & path2 );


//////////////////////////////////////////////////////////////////////////////////////////
//
// \ru Путь к компоненту. \en Path to component. 
//
//////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------
/** \brief \ru Путь к компоненту.
           \en Path to component. \~
  \details \ru Путь в виде массива идентификаторов (путь к компоненту от верхнего компонента). \n
           \en Path as array of identifiers (path to component from upper component). \n \~
  \ingroup Names
*/ // ---
class MbPath : public SArray<SimpleName> 
{
public:
  /// \ru Конструктор. \en Constructor. 
  MbPath()                       : SArray<SimpleName> ( 0, 1 )  {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbPath( const MbPath & other ) : SArray<SimpleName> ( other ) {}
  /// \ru Вычислить хэш себя. \en Calculate hash of itself. 
  SimpleName      Hash() const;
  /// \ru Оператор равенства. \en An equality operator. 
  bool operator == ( const MbPath & ) const;
  /// \ru Оператор присваивания. \en An assignment operator. 
  MbPath & operator =  ( const MbPath & o ) { SArray<SimpleName>::operator = (o); return *this; }
  /// \ru Оператор чтения. \en Read operator. 
  friend reader & operator >> ( reader & in,        MbPath & ref );
  /// \ru Оператор записи. \en Write operator. 
  friend writer & operator << ( writer & out, const MbPath & ref );
  /// \ru Оператор записи. \en Write operator. 
  friend writer & operator << ( writer & out,       MbPath & ref ) { return operator << ( out, (const MbPath &)ref ); }
};


//----------------------------------------------------------------------------------------
// \ru чтение \en Reading 
// ---
inline reader & operator >> ( reader & in, MbPath & ref )       
{ 
  size_t count = ReadCOUNT( in, true/*uint_val*/ );
  if ( in.good() && count ) {
    ref.SetSize( count, true/*clear*/ );

    if ( (ref.GetAddr() == NULL) && (count >= SYS_MAX_UINT32) ) // We could not allocate the required amount of memory
      in.setState( io::outOfMemory );
    else {
      for ( size_t i = 0; i < count && in.good(); i++ ) {
        SimpleName item = ReadSimpleName( in );
        ref.Add( item ); 
      }
    }
  }
  return in; 
}


//----------------------------------------------------------------------------------------
// \ru Запись \en Writing 
// ---
inline writer & operator << ( writer & out, const MbPath & ref ) 
{ 
  size_t count = ref.Count();
  WriteCOUNT( out, count );
  for( size_t i = 0; i < count && out.good(); i++ )
    WriteSimpleName( out, (SimpleName&)ref[i] );
  
  return out; 
}


//----------------------------------------------------------------------------------------
//
// ---
inline SimpleName MbPath::Hash() const 
{
  return ::Hash32( *this );
}


//----------------------------------------------------------------------------------------
// \ru Сравнить пути в виде массива идентификаторов \en Compare paths as array of identifiers 
// ---
inline bool MbPath::operator == ( const MbPath & other ) const 
{
  return ::IsEqualPaths( *this, other );
}


#endif // __NAME_ITEM_H
