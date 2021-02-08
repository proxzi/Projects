////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Тело, матрица его преобразования и идентификаторы владельцев.
         \en Solid, matrix of its transformation and identifiers of owners. \~ 

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __LUMP_H
#define __LUMP_H


#include <mb_matrix3d.h>
#include <mb_cube.h>
#include <math_define.h>
#include <reference_item.h>
#include <templ_sptr.h>
#include <solid.h>


class             MbRegDuplicate;
struct MATH_CLASS MbLump;

namespace c3d // namespace C3D
{
typedef SPtr<MbLump>                                LumpSPtr;
typedef SPtr<const MbLump>                          ConstLumpSPtr;

typedef std::vector<MbLump *>                       LumpsVector;
typedef std::vector<const MbLump *>                 ConstLumpsVector;

typedef std::vector<LumpSPtr>                       LumpsSPtrVector;
typedef std::vector<ConstLumpSPtr>                  ConstLumpsSPtrVector;

typedef std::set<MbLump *>                          LumpsSet;
typedef LumpsSet::iterator                          LumpsSetIt;
typedef LumpsSet::const_iterator                    LumpsSetConstIt;
typedef std::pair<LumpsSetConstIt, bool>            LumpsSetRet;

typedef std::set<LumpSPtr>                          LumpsSPtrSet;
typedef LumpsSPtrSet::iterator                      LumpsSPtrSetIt;
typedef LumpsSPtrSet::const_iterator                LumpsSPtrSetConstIt;
typedef std::pair<LumpsSetConstIt, bool>            LumpsSPtrSetRet;

typedef std::set<const MbLump *>                    ConstLumpsSet;
typedef ConstLumpsSet::iterator                     ConstLumpsSetIt;
typedef ConstLumpsSet::const_iterator               ConstLumpsSetConstIt;
typedef std::pair<ConstLumpsSetConstIt, bool>       ConstLumpsSetRet;

typedef std::set<ConstLumpSPtr>                     ConstLumpsSPtrSet;
typedef ConstLumpsSPtrSet::iterator                 ConstLumpsSPtrSetIt;
typedef ConstLumpsSPtrSet::const_iterator           ConstLumpsSPtrSetConstIt;
typedef std::pair<ConstLumpsSPtrSetConstIt, bool>   ConstLumpsSPtrSetRet;
} // namespace C3D


//------------------------------------------------------------------------------
/** \brief \ru Тело, матрица его преобразования и идентификаторы владельцев.
           \en Solid, matrix of its transformation and identifiers of owners. \~
  \details \ru Тело, матрица его преобразования из локальной системы координат и
    идентификаторы владельцев тела. \n
           \en Solid, matrix of its transformation from local coordinate system and
    identifiers of solid owners. \n \~
  \ingroup Data_Structures
*/
// ---
struct MATH_CLASS MbLump: public MbRefItem {
protected:
  c3d::ConstSolidSPtr solid;      ///< \ru Тело (всегда не NULL). \en Solid (always not NULL). 
  uint                component;  ///< \ru Идентификатор компонента, в котором определено тело. \en An identifier of a component which a solid is defined in. 
  size_t              identifier; ///< \ru Идентификатор нити. \en A thread identifier. 
  MbMatrix3D          from;       ///< \ru Матрица преобразования из локальной системы координат. \en A transformation matrix from the local coordinate system. 
private:
  bool                changed;    ///< \ru Флаг необходимости обработки компонента. \en Component processing flag. 

private:
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  MbLump( const MbLump & other, MbRegDuplicate * iReg );
public:
  /// \ru Пустой конструктор. \en Empty constructor. 
  MbLump() : solid( NULL ), component( 0 ), identifier( SYS_MAX_T ), from(), changed( true ) {} 
  /// \ru Конструктор по данным. \en Constructor by data. 
  MbLump( const MbSolid & _solid, const MbMatrix3D & _from, uint _comp = 0, size_t _ident = SYS_MAX_T, bool _changed = true );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbLump();

public:

  /// \ru Базовое тело? \en Whether the solid is basic. 
  virtual bool      IsBaseLump() const { return true; } 
  /// \ru Тело с признаком резки на производном виде? \en Solid with cutting type on derive view?
  virtual bool      IsCutLump() const { return false; } 
  /// \ru Тело с признаком резки? \en Solid with cutting type?
  virtual bool      IsMappingLump() const { return false; } 
  /// \ru Разрезать тело в производном виде. \en Cut solid on derive view.
  virtual bool      WillCutOnDeriveView() const { return true; }
  /// \ru Дублирование объекта. \en Duplication of an object. 
  virtual MbLump &  Duplicate( MbRegDuplicate * iReg = NULL ) const; 
          /// \ru Получить имя компонента. \en Get the name of a component. 
          uint      GetComponent()  const { return component; } 
          /// \ru Установить имя компонента. \en Set the name of a component. 
          void      SetComponent( uint comp ) { component = comp; } 
          /// \ru Получить идентификатор. \en Get the thread identifier. 
          size_t    GetIdentifier() const { return identifier; } 
          /// \ru Есть идентификатор? \en Is an thread identifier. 
          bool      IsIdentifier() const { return (identifier != SYS_MAX_T); } 
          /// \ru Установить идентификатор. \en Set the thread identifier. 
          void      SetIdentifier( size_t id ) { identifier = id; } 
  /// \ru Получить матрицу преобразования в мир. \en Get the matrix of transformation to the world coordinate system. 
  const MbMatrix3D & GetMatrixFrom() const { return from; } 
        /// \ru Получить матрицу преобразования в мир. \en Get the matrix of transformation to the world coordinate system. 
        MbMatrix3D & SetMatrixFrom() { return from; } 
        /// \ru Инициализировать тело и матрицу. \en Initialize solid and matrix. 
        void        SetSolid( const MbSolid & _solid, const MbMatrix3D & _from, bool _changed = true );
        /// \ru Получить тело. \en Get solid. 
  const MbSolid &   GetSolid() const { return *solid; } 

        /// \ru Получить флаг необходимости обработки компонента. \en Get component processing flag. 
        bool        GetChanged() const { return changed; }
        /// \ru Установить флаг необходимости обработки компонента. \en Set component processing flag.
        void        SetChanged( bool c ) { changed = c; }

/// \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class. 
KNOWN_OBJECTS_RW_REF_OPERATORS_EX( MbLump, MATH_FUNC_EX ) 
/// \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
OBVIOUS_PRIVATE_COPY( MbLump ) 
};


namespace c3d // namespace C3D
{

//-----------------------------------------------------------------------------
/**
Сравнение компонентов MbLump
*/
//---
struct LumpCompLess
{
  bool operator()(const MbLump * lhs, const MbLump * rhs) const
  {
    _ASSERT( lhs && rhs );
    return lhs->GetComponent() < rhs->GetComponent();
  }
};

typedef std::multiset<const MbLump *, LumpCompLess> ConstLumpsMultiSet; 

} // namespace C3D


//------------------------------------------------------------------------------
/** \brief \ru Габарит тела, матрица его преобразования и идентификаторы владельцев.
           \en Solid bounding box, matrix of its transformation and identifiers of owners. \~
  \details \ru Габарит тела, матрица его преобразования из локальной системы координат и
    идентификаторы владельцев тела. \n
           \en Solid bounding box, matrix of its transformation from local coordinate system and
    identifiers of solid owners. \n \~
  \ingroup Data_Structures
*/
// ---
struct MATH_CLASS MbLumpCube: public MbRefItem {
protected:
  MbCube              cube;       ///< \ru Габарита тела. \en Solid bounding box. 
  MbMatrix3D          from;       ///< \ru Матрица преобразования из локальной системы координат. \en A transformation matrix from the local coordinate system. 
  uint                component;  ///< \ru Идентификатор компонента, в котором определено тело. \en An identifier of a component which a solid is defined in. 
  size_t              identifier; ///< \ru Идентификатор нити. \en A thread identifier. 

public:
  /// \ru Пустой конструктор. \en Empty constructor. 
  MbLumpCube()
    : cube()
    , from()
    , component( 0 )
    , identifier( SYS_MAX_T )
  {} 
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  MbLumpCube( const MbLumpCube & other )
    : cube( other.cube )
    , from( other.from )
    , component( other.component )
    , identifier( other.identifier )
  {}
  /// \ru Конструктор по данным. \en Constructor by data. 
  MbLumpCube( const MbCube & _cube, const MbMatrix3D & _from, uint _comp, size_t _ident )
    : cube      ( _cube  )
    , from      ( _from  )
    , component ( _comp  )
    , identifier( _ident )
  {}
  /// \ru Деструктор. \en Destructor. 
  ~MbLumpCube() {}

public:
        /// \ru Получить габарит тела. \en Get solid bounding box. 
  const MbCube &      GetCube() const { return cube; } 
        /// \ru Инициализировать тело и матрицу. \en Initialize solid and matrix. 
        void          SetCube( const MbCube & _cube, const MbMatrix3D & _from ) { cube.Init( _cube ); from.Init( _from ); }
        /// \ru Получить матрицу преобразования в мир. \en Get the matrix of transformation to the world coordinate system. 
        MbMatrix3D &  SetMatrixFrom() { return from; } 
        /// \ru Получить матрицу преобразования в мир. \en Get the matrix of transformation to the world coordinate system. 
  const MbMatrix3D &  GetMatrixFrom() const { return from; } 

        /// \ru Получить имя компонента. \en Get the name of a component. 
        uint      GetComponent()  const { return component; } 
        /// \ru Установить имя компонента. \en Set the name of a component. 
        void      SetComponent( uint comp ) { component = comp; } 
        /// \ru Получить идентификатор. \en Get the thread identifier. 
        size_t    GetIdentifier() const { return identifier; } 
        /// \ru Установить идентификатор. \en Set the thread identifier. 
        void      SetIdentifier( size_t id ) { identifier = id; } 

public:
  const MbLumpCube & operator = ( const MbLumpCube & other )
  {
    cube.Init( other.cube );
    from.Init( other.from );
    component = other.component;
    identifier = other.identifier;
    return *this;
  }
};


#endif // __LUMP_H
