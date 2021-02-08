////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Топологический объект в трехмерном пространстве.
         \en Topological object in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __TOPOLOGY_ITEM_H
#define __TOPOLOGY_ITEM_H


#include <io_tape.h>
#include <name_item.h>
#include <mb_enum.h>
#include <reference_item.h>
#include <attribute_container.h>
#include <templ_visitor.h>
#include <tool_mutex.h>


class  MATH_CLASS MbVector3D; 
class  MATH_CLASS MbCartPoint3D; 
class  MATH_CLASS MbMatrix3D;
class  MATH_CLASS MbAxis3D;
class  MATH_CLASS MbCube;
class  MATH_CLASS MbMesh; 
class  MATH_CLASS MbStepData; 
struct MATH_CLASS MbFormNote; 
class             MbRegTransform;
class             MbRegDuplicate;


//------------------------------------------------------------------------------
/** \brief \ru Типы топологических объектов.
           \en Types of topological objects. \~
  \ingroup Topology_Items
*/
// ---
enum MbeTopologyType {

  tt_Undefined    =   0,  ///< \ru Неизвестный объект. \en Unknown object. 
  tt_TopItem      =   1,  ///< \ru Топологический объект. \en A topological object. \n

  tt_Vertex       = 101,  ///< \ru Вершина. \en A vertex. 

  tt_Edge         = 201,  ///< \ru Ребро, проходящее по кривой. \en An edge passing along a curve. 
  tt_CurveEdge    = 202,  ///< \ru Ребро, проходящее по кривой пересечения поверхностей. \en An edge passing along a surface intersection curve. 
  tt_OrientedEdge = 203,  ///< \ru Ориентированное ребро. \en Oriented edge. 

  tt_Loop         = 301,  ///< \ru Цикл. \en A loop. 

  tt_Face         = 401,  ///< \ru Грань. \en A face. \n

  tt_FaceShell    = 501,  ///< \ru Множество граней. \en A set of faces. \n

  tt_FreeItem     = 600,  ///< \ru Тип для объектов, созданных пользователем. \en Type for the user-defined objects.

};


//------------------------------------------------------------------------------
/** \brief \ru Типы состояний модификации топологического объекта.
           \en The types of modification states of a topological object. \~
  \ingroup Topology_Items
*/
// ---
enum MbeChangedType {
  tct_Unchanged   = 0x0000, ///< \ru Без изменений. \en Unchanged. 
  tct_Modified    = 0x0001, ///< \ru Изменен. \en Modified. 
  tct_Created     = 0x0002, ///< \ru Создан новый. \en Created (new). 
  tct_Transformed = 0x0004, ///< \ru Трансформирован. \en Transformed. 
  tct_Reoriented  = 0x0008, ///< \ru Переориентирован. \en Reoriented. 
  tct_Deleted     = 0x0010, ///< \ru Удален (элемент объекта или связь). \en Deleted (object's element or link). 
  tct_Truncated   = 0x0020, ///< \ru Разрезан, усечен, продлен. \en Cut, truncated or extended.
  tct_Merged      = 0x0040, ///< \ru Объединен или сшито. \en Merged or sewn (stitched).
  tct_Replaced    = 0x0080, ///< \ru Заменен. \en Replaced. 
  tct_Added       = 0x0100, ///< \ru Добавлен или вставлен (элемент объекта). \en Added or inserted (object's element). 
  tct_Renamed     = 0x0200, ///< \ru Переименован. \en Renamed.
};


//------------------------------------------------------------------------------
/** \brief \ru Метка для выполнения операция.
           \en A label for performing of operations. \~
  \ingroup Topology_Items
*/
// ---
class MATH_CLASS MbLabel : public MbSyncItem {
  typedef std::map<void *, int8> LabelMap;
private:
  int8       own;     ///< \ru Собственная временная метка для выполнения операций. \en Own label for performing of operations. 
  LabelMap   privates;///< \ru Частные временные метки для выполнения операций. \en Private labels for performing of operations.
public:
  /// \ru Конструктор без параметров. \en Constructor without parameters. 
  MbLabel();
  /// \ru Конструктор по собственное метке. \en Constructor by own label. 
  MbLabel( const MbeLabelState );
  /// \ru Конструктор по Label. \en Constructor by Label. 
  MbLabel( const MbLabel & );
  /// \ru Деструктор. \en Destructor without parameters. 
  ~MbLabel();
  /// \ru Установить частную или собственную метку (соответствующую ключу). \en Set own or private label (according to the key). 
  void SetLabel( const MbeLabelState, void * key = NULL );
  /// \ru Установить частную или собственную метку (соответствующую ключу). \en Set own or private label (according to the key). 
  void SetLabel( const MbeLabelState, void * key, bool setLock );
  /// \ru Получить частную или собственную метку (соответствующую ключу). \en Get own or private label (according to thew key). 
  int8 GetLabel( void * key = NULL );
  /// \ru Удалить частные метки(освободить память) соответствующие ключу. \en Remove private labels (free memory) according to the key. 
  void DeletePrivate( void * key );
  /// \ru Присвоить значение собственной метке. \en Assign values to own label. 
  void operator = ( const MbeLabelState lbl ) { own = (int8)lbl; }
  /// \ru Присвоить значение собственной метке и скопировать частные. \en Assign values to own label and cope private labels. 
  void operator = ( const MbLabel & );
  /// \ru Проверить собственную метку на равенство. \en Check own label for equality. 
  bool operator == ( const MbeLabelState lbl ) const { return (own == (int8)lbl);  }
private:
  bool operator == ( const MbLabel & ); // \ru Не реализовано!!! \en Not implemented!!! 
};


//------------------------------------------------------------------------------
/** \brief \ru Топологический объект в трехмерном пространстве.
           \en Topological object in three-dimensional space. \~
  \details \ru Родительский класс топологических объектов в трехмерном пространстве.\n
    Топологическими называют геометрические свойства, 
    которые не зависят от количественных характеристик (длин и углов), 
    а отражают непрерывную связь объекта с его окружением. \n
    Топологические объекты описывают и геометрические свойства объекта, 
    зависящие от количественных характеристик, и геометрические свойства, 
    отражающие непрерывную связь объекта с соседними элементами. 
    Топологические объекты строятся на основе точек, кривых и поверхностей путём добавления к их данным, 
    свойствам и методам новых данных, свойств и методов.
           \en A parent class of topological objects in three-dimensional space.\n
    Geometric properties are called topological if they 
    are not depend on the quantitative characteristics (lengths and angles), 
    but reflect continuous connection between an object and its environment. \n
    topological objects also describe the object geometric properties 
    which depend on quantitative characteristics and geometric properties, 
    which reflect continuous connection between an object and neighboring elements. 
    topological objects are constructed on the base of points, curves and surfaces by adding to their data, 
    properties and methods a new data, properties and methods. \~ 
  \ingroup Topology_Items
*/
// ---
class MATH_CLASS MbTopItem : public MbRefItem, public TapeBase {
protected:
  /// \ru Конструктор. \en Constructor. 
  MbTopItem(); 
public:
  virtual ~MbTopItem();
public:
  /// \ru Регистрационный тип (для копирования, дублирования). \en Registration type (for copying, duplication). 
  virtual MbeRefType  RefType() const; 
  /// \ru Тип элемента. \en A type of element. 
  virtual MbeTopologyType IsA() const = 0; 

          /// \ru Подготовить объект к записи. \en Prepare an object for writing. 
          void        PrepareWrite() { SetRegistrable( GetUseCount() > 1 ? registrable : noRegistrable ); }
          
          bool        IsAVertex()   const { return (IsA() == tt_Vertex);       } ///< \ru Это вершина? \en Is it a vertex? 
          bool        IsAWireEdge() const { return (IsA() == tt_Edge);         } ///< \ru Это ребро каркаса? \en Is it an edge of wireframe? 
          bool        IsAnEdge()    const { return (IsA() == tt_CurveEdge);    } ///< \ru Это ребро? \en Is it an edge? 
          bool        IsAFace()     const { return (IsA() == tt_Face);         } ///< \ru Это грань? \en Is it a face? 
          bool        IsAShell()    const { return (IsA() == tt_FaceShell);    } ///< \ru Это оболочка? \en Is it a shell? 

DECLARE_PERSISTENT_CLASS( MbTopItem )
OBVIOUS_PRIVATE_COPY( MbTopItem )
};

IMPL_PERSISTENT_OPS( MbTopItem )

//------------------------------------------------------------------------------
/** \brief \ru Топологический объект с именем.
           \en Topological object with name. \~
  \details \ru Родительский класс именованных топологических объектов. \n
    Наследниками являются объекты, которые можно идентифицировать по имени, это 
    вершины, ребра, грани.
    Наследники также имеют флаг изменённости и временную метку для использования в операция.
           \en A parent class of named topological objects. \n
    Inheritors are objects which may be identified by name, there are 
    vertices, edges, faces.
    Also inheritors have a flag of being changed and temporary label for using in operations. \~
  \ingroup Topology_Items
*/
// ---
class MATH_CLASS MbTopologyItem : public MbTopItem, public MbAttributeContainer {
private:
  MbName          name;    ///< \ru Имя объекта. \en A name of an object. 
  uint16          changed; ///< \ru Флаг изменений объекта после выполнения операций: false - для не измененных, true - для измененных. \en A flag of object changes after performing of operations: false - for unchanged, true - for changed. 
protected:
  mutable MbLabel label;   ///< \ru Временная метка для выполнения операций. \en Temporary label for performing of operations. 

protected:
  /// \ru Конструктор без параметров. \en Constructor without parameters. 
  MbTopologyItem(); 
  /// \ru Конструктор дублирования. \en Constructor of duplicating. 
  MbTopologyItem( const MbTopologyItem &, MbRegDuplicate * ); 
public:
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbTopologyItem();

public :
  VISITING_CLASS( MbTopologyItem ); 

  /// \ru Тип элемента. \en A type of element. 
  virtual MbeTopologyType  IsA() const = 0; 
  /// \ru Тип контейнера атрибутов. \en Type of attribute container. 
  virtual MbeImplicationType  ImplicationType() const; 

  /** \brief \ru Преобразовать согласно матрице.
             \en Transform according to the matrix. \~
  \details \ru Преобразование объекта согласно матрице. 
    Данный объект может содержаться указателем в нескольких других объектах, подлежащих преобразованию.
    Для предотвращения многократного преобразования данного объекта используется регистратор.
    При преобразовании объекта с использованием регистратора проверяется наличие объекта в регистраторе.
    Если такой объект отсутствует, то он заносится в регистратор и выполняется его преобразование,
    в противном случае преобразование данного объекта не выполняется.
           \en Transformation of an object according to the matrix. 
    This object can be contained as pointer in several other objects for transformations.
    Registrar is used to prevent multiple transformation of this object.
    When transforming the object with registrator, the existence of the object inside the registrator is verified.
    If such object is absent, it is stored to the registrator and transformed,
    otherwise, a transformation of the object is not performed. \~
  \param[in] matr - \ru Матрица преобразования.
                    \en A transformation matrix. \~
  \param[in] iReg - \ru Регистратор.
                    \en Registrator. \~
  \ingroup Topology_Items
  */
  virtual void        Transform( const MbMatrix3D & matr, MbRegTransform * iReg = NULL ) = 0;

  /** \brief \ru Сдвинуть вдоль вектора.
             \en Move along a vector. \~
  \details \ru Сдвинуть объект вдоль вектора. 
    При преобразовании объекта с использованием регистратора проверяется наличие объекта в регистраторе.
    Если такой объект отсутствует, то он заносится в регистратор и выполняется его преобразование,
    в противном случае преобразование данного объекта не выполняется.
           \en Move an object along a vector. 
    When transforming the object with registrator, the existence of the object inside the registrator is verified.
    If such object is absent, it is stored to the registrator and transformed,
    otherwise, a transformation of the object is not performed. \~
  \param[in] to   - \ru Вектор сдвига.
                    \en Translation vector. \~
  \param[in] iReg - \ru Регистратор.
                    \en Registrator. \~
  \ingroup Topology_Items
  */
  virtual void        Move     ( const MbVector3D & to, MbRegTransform * iReg = NULL ) = 0;

  /** \brief \ru Повернуть вокруг оси.
             \en Rotate around an axis. \~
  \details \ru Повернуть объект вокруг оси на заданный угол. 
    При преобразовании объекта с использованием регистратора проверяется наличие объекта в регистраторе.
    Если такой объект отсутствует, то он заносится в регистратор и выполняется его преобразование,
    в противном случае преобразование данного объекта не выполняется.
           \en Rotate an object at a given angle around an axis. 
    When transforming the object with registrator, the existence of the object inside the registrator is verified.
    If such object is absent, it is stored to the registrator and transformed,
    otherwise, a transformation of the object is not performed. \~
  \param[in] axis  - \ru Ось вращения.
                     \en Rotation axis. \~
  \param[in] angle - \ru Угол поворота.
                     \en The rotation angle. \~
  \param[in] iReg  - \ru Регистратор.
                     \en Registrator. \~
  \ingroup Topology_Items
  */
  virtual void        Rotate   ( const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL ) = 0;
  
  /// \ru Вычислить расстояние до точки. \en Calculate the distance to a point. 
  virtual double      DistanceToPoint( const MbCartPoint3D & ) const = 0; 
  /// \ru Добавить свой габарит в присланный габарит. \en Add your own bounding box into the sent bounding box. 
  virtual void        AddYourGabaritTo( MbCube & ) const = 0; 
  /// \ru Рассчитать габарит в локальной системы координат, заданной матрицей преобразования в эту систему. \en Calculate bounding box in the local coordinate system which is given by the matrix of transformation to this system. 
  virtual void        CalculateLocalGabarit( const MbMatrix3D & into, MbCube & cube ) const = 0; 
  /// \ru Являются ли объекты равными? \en Determine whether objects are equal. 
  virtual bool        IsSame( const MbTopologyItem &, double accuracy ) const = 0; 
  /// \ru Построить полигональную копию объекта mesh. \en Construct a polygonal copy of an object mesh). 
  virtual void        CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const = 0; 

  /// \ru Выдать имя объекта. \en Get name of object. 
  const   MbName    & GetName()     const { return name; } 
  /// \ru Выдать имя объекта для модификации. \en Get name of object for modification. 
          MbName    & SetName()           { return name; } 

          /// \ru Выдать главное имя. \en Get main name. 
          SimpleName  GetMainName() const { return name.GetMainName(); }
          /// \ru Установить главное имя. \en Set main name. 
          void        SetMainName( SimpleName n ) { name.SetMainName( n ); }
           /// \ru Получить первое имя. \en Get first name. 
          SimpleName  GetFirstName() const { return ( name.CountBase() > (size_t)MbName::i_First ) ? name.GetFirstNameDirect() : 0; }
          /// \ru Выдать hash имени. \en Get hash of name. 
          SimpleName  GetNameHash() const { return name.Hash(); } 
          /// \ru Установить имя. \en Set name. 
          void        SetName( const MbName & n ) { name.SetName( n ); }  

          /// \ru Получить флаг, свидетельствующий о том, что объект был (не был) изменен. \en Get flag which indicates that an object has (not) been changed. 
          bool        GetOwnChanged() const { return (changed != tct_Unchanged); } 
          /// \ru Получить флаг, свидетельствующий о том, что объект был (не был) изменен. \en Get flag which indicates that an object has (not) been changed. 
          bool        GetOwnChanged( MbeChangedType n ) const { return !!(changed & n); }
          /// \ru Установить флаг, свидетельствующий о том, что объект был (не был) изменен. \en Set flag which indicates that an object has (not) been changed. 
          void        SetOwnChanged( MbeChangedType );
          /// \ru Копировать флаг, свидетельствующий о том, что объект был (не был) изменен. \en Copy flag which indicates that an object has (not) been changed. 
          void        CopyOwnChanged( const MbTopologyItem & ti ) { changed = ti.changed; }

          /// \ru Получить флаг, свидетельствующий о том, что объект был (не был) изменен. \en Get flag which indicates that an object has (not) been changed. 
          uint16      GetOwnChangedFlag() const { return changed; } 
          /// \ru Установить флаг, свидетельствующий о том, что объект был (не был) изменен. \en Set flag which indicates that an object has (not) been changed. 
          template<class Uint>
          void        SetOwnChangedFlag( Uint n ) { changed = (uint16)n; }

          /// \ru Получить флаг, свидетельствующий о том, что объект был только переименован. \en Get flag which indicates that an object has been renamed only. 
          bool        IsOwnRenamedOnly()     const { return ( changed == ( tct_Renamed | tct_Modified ) ); }
          /// \ru Получить флаг, свидетельствующий о том, что объект был только трансформирован. \en Get flag which indicates that an object has been transformed only. 
          bool        IsOwnTransformedOnly() const { return ( changed == ( tct_Transformed | tct_Modified ) ); }
          /// \ru Получить флаг, свидетельствующий о том, что объект был только переориентирован. \en Get flag which indicates that an object has been reoriented only. 
          bool        IsOwnReorientedOnly()  const { return ( changed == ( tct_Reoriented  | tct_Modified ) ); }
          /// \ru Получить флаг, свидетельствующий о том, что объект был создан, переименован, трансформирован или переориентирован. \en Get flag which indicates that an object has been only created, renamed, transformed or reoriented. 
          bool        IsOwnChangedWeakly() const;

          /// \ru Получить метку. \en Get label. 
          MbeLabelState GetLabel( void * key = NULL ) const { return (MbeLabelState)label.GetLabel(key); } 
          /// \ru Установить метку. \en Set a label of the loop. 
          void        SetOwnLabel( MbeLabelState l, void * key = NULL ) const { label.SetLabel( l, key ); } 
          /// \ru Установить метку. \en Set a label of the loop. 
          void        SetOwnLabel( MbeLabelState l, void * key, bool setLock ) const { if ( setLock || GetUseCount() > 1 ) return SetOwnLabel( l, key ); label.SetLabel( l, key ); }
          /// \ru Предназначен ли объект для удаления? Определяется по меткам. \en Is this object intended for deletion? This is defined by labels. 
          bool        ToDelete() const { return( (MbeLabelState)label.GetLabel(NULL) == ls_Delete || (MbeLabelState)label.GetLabel(NULL) == ls_Error ); }
          /// \ru Удалить частную метку. \en Remove private label. 
          void        RemovePrivateLabel ( void * key = NULL ) const { label.DeletePrivate(key); } 

          /// \ru Копирование данных объекта. \en Copying of the object data. 
          void        Assign( const MbTopologyItem & );
          /// \ru Удалить атрибут типа имя с родительскими именами. \en Delete an attribute of name type with parent names. 
          void        RemoveParentNamesAttribute();

DECLARE_PERSISTENT_CLASS( MbTopologyItem )
OBVIOUS_PRIVATE_COPY( MbTopologyItem )
};

IMPL_PERSISTENT_OPS( MbTopologyItem )

//------------------------------------------------------------------------------
// \ru Установить флаг, свидетельствующий о том, что объект был (не был) изменен. \en Set flag which indicates that an object has (not) been changed. 
// ---
inline void MbTopologyItem::SetOwnChanged( MbeChangedType n )
{
  if ( n != tct_Unchanged ) {
    changed |= n;
    changed |= tct_Modified;
  }
  else {
    changed = tct_Unchanged;
  }
}

//------------------------------------------------------------------------------
// \ru Получить флаг, свидетельствующий о том, что объект был создан, переименован, трансформирован или переориентирован. \en Get flag which indicates that an object has been only created, renamed, transformed or reoriented. 
// ---
inline bool MbTopologyItem::IsOwnChangedWeakly() const
{
  uint16 wrkFlag = (tct_Created | tct_Renamed | tct_Transformed | tct_Reoriented | tct_Modified);
  wrkFlag = ~wrkFlag;
  wrkFlag = (changed & wrkFlag);
  if ( !wrkFlag )
    return true;
  return false;
}

//------------------------------------------------------------------------------
// \ru Копирование данных. \en Data copying. 
// ---
inline void MbTopologyItem::Assign( const MbTopologyItem & other )
{
  AttributesAssign( other );
  name.SetName( other.GetName() );
  label = other.label;
  changed = other.changed;
}


#endif // __TOPOLOGY_ITEM_H
