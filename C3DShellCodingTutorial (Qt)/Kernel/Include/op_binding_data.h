////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Классы привязки объектов.
         \en Items binding classes. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __OP_BINDING_DATA_H
#define __OP_BINDING_DATA_H

#include <math_define.h>
#include <mb_variables.h>
#include <mb_cart_point3d.h>


class  MATH_CLASS  MbMatrix3D;
class  MATH_CLASS  MbAxis3D;
class  MATH_CLASS  MbCurveEdge;
class  MATH_CLASS  MbFace;
class  MATH_CLASS  MbFaceShell;


//------------------------------------------------------------------------------
/** \brief \ru Индекс идентификации объекта.
           \en Index of object identification. \~
  \details \ru Индекс содержит имя, номер в теле и контрольную точку и
    служит для поиска объекта (грани, ребра, вершины) в оболочке.
    Поиск объекта производится по имени, в случае неудаче - по номеру,
    и проверяется по контрольной точке \n
           \en Index contains the name, the index in the solid and the control point, it
    is used to search for object (face, edge, vertex) in the shell.
    Object searching is performed by name. In failure case - by index,
    and checked by the control point \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbItemIndex {
protected:
  size_t        itemIndex; ///< \ru Номер объекта в оболочке. \en The index of object in the shell.
  MbCartPoint3D point;     ///< \ru Контрольная точка объекта. \en Control point of the object.
  SimpleName    itemName;  ///< \ru Имя объекта. \en A name of an object.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MbItemIndex()
    : itemIndex( SYS_MAX_T )
    , point    ( -DETERMINANT_MAX, -DETERMINANT_MAX, -DETERMINANT_MAX )
    , itemName ( SIMPLENAME_MAX )
  {}

  /// \ru Конструктор по индексу без точки привязки. \en Constructor by the index without anchor point.
  explicit MbItemIndex( size_t i )
    : itemIndex( i )
    , point    ( -DETERMINANT_MAX, -DETERMINANT_MAX, -DETERMINANT_MAX )
    , itemName ( SIMPLENAME_MAX )
  {}

  /// \ru Конструктор по индексу с точкой привязки. \en Constructor by the index with anchor point.
  MbItemIndex( size_t i, const MbCartPoint3D & p, SimpleName n )
    : itemIndex( i )
    , point    ( p )
    , itemName ( n )
  {}

  /// \ru Конструктор по индексу с точкой привязки. \en Constructor by the index with anchor point.
  MbItemIndex( size_t i, const MbFace & face ) : itemIndex( i ), point(), itemName() { Init( face, i ); }
  /// \ru Конструктор по индексу с точкой привязки. \en Constructor by the index with anchor point.
  MbItemIndex( size_t i, const MbCurveEdge & edge ) : itemIndex( i ), point(), itemName() { Init( edge, i ); }

  /// \ru Конструктор копирования. \en Copy-constructor.
  MbItemIndex( const MbItemIndex & other )
    : itemIndex( other.itemIndex )
    , point    ( other.point     )
    , itemName ( other.itemName  )
  {}
  /// \ru Деструктор. \en Destructor.
  ~MbItemIndex();

public:
  /// \ru Функция инициализации. \en Initialization function.
  void        Init( const MbItemIndex & other )
  {
    itemIndex = other.itemIndex;
    point     = other.point;
    itemName  = other.itemName;
  }
  /// \ru Функция инициализации. \en Initialization function.
  void        Init( size_t ind, bool reset = true )
  {
    itemIndex = ind;
    if ( reset ) {
      point.Init( -DETERMINANT_MAX, -DETERMINANT_MAX, -DETERMINANT_MAX );
      itemName = SIMPLENAME_MAX;
    }
  }
  /// \ru Функция инициализации. \en Initialization function.
  void        Init( size_t i, const MbCartPoint3D & p, SimpleName n )
  {
    itemIndex = i;
    point     = p;
    itemName  = n;
  }
  /// \ru Функция инициализации. \en Initialization function.
  bool        Init( const MbFaceShell &, size_t faceIndex );
  /// \ru Функция инициализации. \en Initialization function.
  void        Init( const MbFace      &, size_t faceIndex );
  /// \ru Функция инициализации. \en Initialization function.
  void        Init( const MbCurveEdge &, size_t edgeIndex );

  /// \ru Оператор присваивания. \en Assignment operator.
  MbItemIndex & operator = ( const MbItemIndex & other )
  {
    Init( other );
    return *this;
  }

  /// \ru Получить индекс. \en Get index.
  size_t      GetIndex() const { return itemIndex; }
  /// \ru Получить имя. \en Get name.
  SimpleName  GetName()  const { return itemName; }
  /// \ru Получить точку привязки. \en Get anchoring point.
  const MbCartPoint3D &  GetPoint()  const { return point; }

  /// \ru Установить индекс. \en Set index.
  void        SetIndex( size_t index ) { itemIndex = index; }
  /// \ru Установить имя. \en Set name.
  void        SetName( SimpleName name ) { itemName = name; }
  /// \ru Установить точку привязки. \en Set anchoring point.
  void        SetPoint( const MbFace & );
  /// \ru Установить точку привязки. \en Set anchoring point.
  void        SetPoint( const MbCurveEdge & );

  /// \ru Изменить индекс и точку привязки. \en Change index and anchoring point.
  void        ChangeIndexPoint( size_t index, const MbCartPoint3D & pnt ) { itemIndex = index; point = pnt; }
  /// \ru Изменить индекс и точку привязки. \en Change index and anchoring point.
  void        ChangeIndexName( size_t index, const SimpleName & name ) { itemIndex = index; itemName = name; }

  /// \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix.
  void        Transform( const MbMatrix3D & matr );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D & to );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D & axis, double ang );
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const MbItemIndex & other, double accuracy ) const; 

  /// \ru Статический оператор меньше. \en Static operator "less".
  static bool LessByItemIndex( const MbItemIndex & ind1, const MbItemIndex & ind2 )
  {
    if ( ind1.GetIndex() < ind2.GetIndex() )
      return true;
    return false;
  }
  /// \ru Статический оператор меньше. \en Static operator "less".
  static bool LessByItemName( const MbItemIndex & ind1, const MbItemIndex & ind2 )
  {
    if ( ind1.GetName() < ind2.GetName() )
      return true;
    return false;
  }
  /// \ru Статический оператор отсутствия индекса. \en Static operator "no item index".
  static bool NoItemIndex( const MbItemIndex & ind )
  {
    if ( ind.itemIndex == SYS_MAX_T )
      return true;
    return false;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbItemIndex ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
  DECLARE_NEW_DELETE_CLASS( MbItemIndex )
  DECLARE_NEW_DELETE_CLASS_EX( MbItemIndex )
};

namespace c3d // namespace C3D
{
typedef std::pair<MbItemIndex, MbItemIndex> ItemIndexPair;
typedef std::vector<MbItemIndex>            ItemIndices;
}


//------------------------------------------------------------------------------
/** \brief \ru Расширенный индекс идентификации объекта.
           \en Extended index of object identification. \~
  \details \ru Расширенный индекс содержит имя, номер в теле и контрольную точку и служит для поиска объекта
    (например, грани а теле для построения тонкой стенки).
    Поиск объекта производится по имени, в случае неудаче - по номеру, и проверяется по контрольной точке \n
           \en Extended index contains the name, the index in the solid and the control point and is used to search object
    (or example: face in the solid, for construction of thin wall).
    Object searching is performed by name. In failure case - by index, and checked by the control point \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbItemThinValues : public MbItemIndex {
public:
  double  value1; ///< \ru Первое значение параметра объекта (толщина наружу). \en The first parameter value of the object (thickness of the outside).
  double  value2; ///< \ru Второе значение параметра объекта (толщина внутрь). \en The second parameter value of the object (thickness of the outside).

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MbItemThinValues()
    : MbItemIndex(     )
    , value1     ( 0.0 )
    , value2     ( 0.0 )
  {}

  /// \ru Конструктор по индексу и толщинам наружу и внутрь. \en Constructor by the index and thickness to outside and inside.
  MbItemThinValues( ptrdiff_t i, double d1, double d2 )
    : MbItemIndex( i  )
    , value1     ( ::fabs(d1) )
    , value2     ( ::fabs(d2) )
  {}

  /// \ru Конструктор по индексу, точке привязки и толщинам наружу и внутрь. \en Constructor by the index, anchor point and thickness to outside and inside.
  MbItemThinValues( ptrdiff_t i, const MbCartPoint3D & p, double d1, double d2, SimpleName n )
    : MbItemIndex( i, p, n    )
    , value1     ( ::fabs(d1) )
    , value2     ( ::fabs(d2) )
  {}

  /// \ru Конструктор по индексу, точке привязки и толщинам наружу и внутрь. \en Constructor by the index, anchor point and thickness to outside and inside.
  MbItemThinValues( const MbItemIndex & itemInd, double d1, double d2 )
    : MbItemIndex( itemInd    )
    , value1     ( ::fabs(d1) )
    , value2     ( ::fabs(d2) )
  {}

  /// \ru Конструктор копирования. \en Copy-constructor.
  MbItemThinValues( const MbItemThinValues & other )
    : MbItemIndex( other.itemIndex, other.point, other.itemName )
    , value1     ( other.value1                 )
    , value2     ( other.value2                 )
  {}

  /// \ru Оператор присваивания. \en Assignment operator.
  MbItemThinValues & operator = ( const MbItemThinValues & other ) {
    MbItemIndex::Init( (const MbItemIndex &)other );
    value1 = other.value1;
    value2 = other.value2;
    return *this;
  }

  /** \brief \ru Инициализировать по индексу идентификации.
             \en Initialize by identification index. \~
    \details \ru Инициализировать по индексу идентификации и толщине наружу и внутрь.
             \en Initialize by the identification index and thickness to outside and inside. \~
    \param[in] itemInd - \ru Индекс идентификации.
                         \en Identification index. \~
    \param[in] d1      - \ru Толщина наружу.
                         \en Thickness to outside. \~
    \param[in] d2      - \ru Толщина внутрь.
                         \en Thickness to inside. \~
  */
  void        Init( const MbItemIndex & itemInd, double d1, double d2 )
  {
    MbItemIndex::Init( itemInd );
    value1 = ::fabs(d1);
    value2 = ::fabs(d2);
  }
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const MbItemThinValues & other, double accuracy ) const; 

  KNOWN_OBJECTS_RW_REF_OPERATORS( MbItemThinValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
  DECLARE_NEW_DELETE_CLASS( MbItemThinValues )
  DECLARE_NEW_DELETE_CLASS_EX( MbItemThinValues )
};


//------------------------------------------------------------------------------
/** \brief \ru Индекс идентификации ребра.
           \en Index of edge identification. \~
  \details \ru Индекс содержит имя, номер ребра, номера соединяемых ребром граней в теле
    и контрольную точку и служит для поиска ребра для скругления или фаски.
    Поиск ребра производится по имени, в случае неудаче - по номерам, и проверяется по контрольной точке \n
           \en Index contains the name, the index of the edge, indices of faces in the solid connected by edge
    and control point and is used to search the edge for fillet or chamfer.
    Edge searching is performed by name. In failure case - by indices, and checked by the control point \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbEdgeFacesIndexes {
public:
  size_t        edgeIndex;  ///< \ru Номер ребра в множестве рёбер тела. \en The index of the edge in the set of solid edges.
  size_t        facePIndex; ///< \ru Номер грани слева в множестве граней тела. \en The index of the face on the left in the set of solid faces.
  size_t        faceMIndex; ///< \ru Номер грани справа в множестве граней тела. \en The index of the face on the right in the set of solid faces.
  MbCartPoint3D point;      ///< \ru Контрольная точка ребра. \en Control point of the edge.
  SimpleName    itemName;   ///< \ru Имя объекта. \en A name of an object.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MbEdgeFacesIndexes()
    : edgeIndex ( SYS_MAX_T )
    , facePIndex( SYS_MAX_T )
    , faceMIndex( SYS_MAX_T )
    , point     ( -DETERMINANT_MAX, -DETERMINANT_MAX, -DETERMINANT_MAX )
    , itemName  ( SIMPLENAME_MAX )
  {}

  /// \ru Конструктор копирования. \en Copy-constructor.
  MbEdgeFacesIndexes( const MbEdgeFacesIndexes & other )
    : edgeIndex ( other.edgeIndex  )
    , facePIndex( other.facePIndex )
    , faceMIndex( other.faceMIndex )
    , point     ( other.point      )
    , itemName  ( other.itemName   )
  {}

  /// \ru Оператор присваивания. \en Assignment operator.
  MbEdgeFacesIndexes & operator = ( const MbEdgeFacesIndexes & other ) {
    edgeIndex  = other.edgeIndex;
    facePIndex = other.facePIndex;
    faceMIndex = other.faceMIndex;
    point      = other.point;
    itemName   = other.itemName;
    return *this;
  }

  /// \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix.
  void        Transform( const MbMatrix3D & matr );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D & to );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D & axis, double ang );
  /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  bool        IsSame( const MbEdgeFacesIndexes & other, double accuracy ) const; 

  /// \ru Установить индекс. \en Set index.
  void        SetIndex( size_t index, size_t indexP, size_t indexM ) { edgeIndex = index; facePIndex = indexP; faceMIndex = indexM; }
  /// \ru Установить имя. \en Set name.
  void        SetName( SimpleName name ) { itemName = name; }

  /// \ru Статический оператор меньше. \en Static operator "less".
  static bool LessByEdgeIndex( const MbEdgeFacesIndexes & ind1, const MbEdgeFacesIndexes & ind2 )
  {
    if ( ind1.edgeIndex < ind2.edgeIndex )
      return true;
    return false;
  }

  /// \ru Функция чтения. \en Read function.
  friend MATH_FUNC (reader &) operator >> ( reader & in,        MbEdgeFacesIndexes & ref );
  /// \ru Функция записи. \en Write function.
  friend MATH_FUNC (writer &) operator << ( writer & out, const MbEdgeFacesIndexes & ref );
  /// \ru Функция записи. \en Write function.
  friend MATH_FUNC (writer &) operator << ( writer & out,       MbEdgeFacesIndexes & ref ) {
    return operator << ( out,(const MbEdgeFacesIndexes &)ref );
  }

  DECLARE_NEW_DELETE_CLASS( MbEdgeFacesIndexes )
  DECLARE_NEW_DELETE_CLASS_EX( MbEdgeFacesIndexes )
};


////////////////////////////////////////////////////////////////////////////////
//
// \ru Неклассные функции. \en Out-of-class functions.
//
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
/// \ru Сортировка по возрастанию номера. \en Sorting in ascending order of index.
// ---
template <class Indices> // Indices - MbItemIndex vector
void SortItemIndices( Indices & indices )
{
  if ( indices.size() > 1 ) {
    std::sort( indices.begin(), indices.end(), MbItemIndex::LessByItemIndex );
  }
}


//------------------------------------------------------------------------------
/// \ru Сортировка по возрастанию номера. \en Sorting in ascending order of index.
// ---
template <class Indices> // Indices - MbEdgeFacesIndexes vector
void SortEdgeFacesIndices( Indices & indices )
{
  if ( indices.size() > 1 ) {
    std::sort( indices.begin(), indices.end(), MbEdgeFacesIndexes::LessByEdgeIndex );
  }
}



#endif // __OP_BINDING_DATA_H
