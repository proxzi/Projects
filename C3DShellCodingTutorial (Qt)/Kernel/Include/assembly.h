//////////////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Сборочная единица.
         \en Assembly unit. \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ASSEMBLY_H
#define __ASSEMBLY_H

#include <generic_utility.h>
#include <gcm_manager.h>
#include <model_item.h>
#include <solid.h>
#include <instance.h>


class             MbConstraintSystem;
class  MATH_CLASS MtGeomArgument;
class  MATH_CLASS MtGeomConstraint;
class  MATH_CLASS MtConstraintIter;
struct            ItAssemblyReactor;
struct            ItAssemblyImportData;
class            _ItemVisitor;
class             MbModelTreeReader;
class  MATH_CLASS MbAssembly;

namespace c3d // namespace C3D
{
typedef SPtr<MbAssembly>                AssemblySPtr;
typedef SPtr<const MbAssembly>          ConstAssemblySPtr;

typedef std::vector<MbAssembly *>       AssembliesVector;
typedef std::vector<const MbAssembly *> ConstAssembliesVector;

typedef std::vector<AssemblySPtr>       AssembliesSPtrVector;
typedef std::vector<ConstAssemblySPtr>  ConstAssembliesSPtrVector;
}


//----------------------------------------------------------------------------------------
/** \brief \ru Сборочная единица.
           \en Assembly unit. \~
  \details \ru Сборка состоит из множества объектов геометрической модели MbItem.
    Сборка может содержать объекты любого подкласса MbItem, в том числе и сборочные 
    единицы (тип MbAssembly).
           \en The assembly consists of a set of objects of geometric model MbItem.
    The assembly may contain objects of any sub-class of MbItem, including 
    assembly units (of type MbAssembly).
  \par  \ru Отношение "часть-целое". 
        \en Relationship "is a part of".
  \ru Сборочная единица - это объект модели объединяющий в себе набор других объектов. 
      Такое объединение рассматривается как агрегация, устанавливающая отношение 
      владения между сборкой и её собственными суб-объектами. Это предполагает что любой
      объект модели типа MbItem может принадлежать только одной сборке.
  \en Assembly unit is object of model aggregating a collection of other objects.
      Such an association is regarded as an aggregation establishing an ownership 
      between the assembly and its proper sub-objects. This implies that any
      model object of type MbItem can belong to only assembly.
  \~
  \ingroup Model_Items
*/
//---
class MATH_CLASS MbAssembly : public MbItem
{
private:
  typedef sorting_array<MbItem*,LessName> ItemContainer;  
  typedef ItemContainer::iterator         item_iterator;

private:  
  ItemContainer               assemblyItems;    ///< \ru Множество объектов сборки. \en A set of assembly objects.
  MbConstraintSystem *        constraintSystem; ///< \ru Система ограничений сборки. \en Constraint system of assembly unit.
  mutable ItAssemblyReactor * m_reactor;        ///< \ru Обработчик события, связанные с решением сборки. \en The event handles related to solving the assembly.

protected:
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator.
  explicit MbAssembly( const MbAssembly & init, MbRegDuplicate * iReg );

public:
  /// \ru Конструктор пустой сборки. \en Construct an empty assembly.
           MbAssembly();
  /// \ru Конструктор по объекту. \en The constructor by an object.
  explicit MbAssembly( MbItem & );
  /// \ru Конструктор по объектам в локальной системе координат. \en The constructor by objects in a local coordinate system.
           template <class ItemsVector>
           MbAssembly( const ItemsVector & items );
  // \ru Деструктор. \en Destructor.
  virtual ~MbAssembly();

public:
  VISITING_CLASS( MbAssembly ); 

  // \ru Общие функции геометрического объекта \en Common functions of a geometric object

  virtual MbeSpaceType  IsA()  const; // \ru Тип объекта. \en An object type.
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Создать копию. \en Create a copy.
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * iReg = NULL ); // \ru Преобразовать согласно матрице. \en Transform according to the matrix.
  virtual void    Move( const MbVector3D &, MbRegTransform * iReg = NULL ); // \ru Сдвинуть вдоль вектора. \en Move along a vector.
  virtual void    Rotate( const MbAxis3D   &, double angle, MbRegTransform * iReg = NULL ); // \ru Повернуть вокруг оси. \en Rotate about an axis.
  virtual bool    IsSame( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными? \en Are the objects equal?
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными? \en Are the objects similar?
  virtual bool    SetEqual ( const MbSpaceItem & );   // \ru Сделать объекты равным \en Make the objects equal
  virtual double  DistanceToPoint ( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate distance to point.
  virtual void    AddYourGabaritTo( MbCube & r ) const; // \ru Добавь свой габарит в куб. \en Add own bounding box to the bounding box.
  virtual void    CalculateLocalGabarit( const MbMatrix3D & into, MbCube & cube ) const; // \ru Рассчитать габарит в локальной системы координат. \en Calculate the bounding box in a local coordinate system.
  virtual void    CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; // \ru Построить полигональную копию mesh. \en Build polygonal copy mesh.

  virtual MbProperty & CreateProperty( MbePrompt n ) const;   // \ru Создать собственное свойство. \en Create own property.
  virtual void    GetProperties( MbProperties & );        // \ru Выдать свойства объекта. \en Get properties of the object.
  virtual void    SetProperties( const MbProperties & );  // \ru Установить свойства объекта. \en Set properties of the object.
  virtual void    GetBasisItems( RPArray<MbSpaceItem>   & ); // \ru Дать базовые объекты. \en Get the basis objects.
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Выдать локальную систему координат объектов сборки. \en Get the local coordinate system of assembly items.
  virtual bool    GetPlacement( MbPlacement3D & ) const;
  // \ru Установить локальную систему координат объектов сборки. \en Set coordinate system of assembly items.
  virtual bool    SetPlacement( const MbPlacement3D & );
  // \ru Перестроить объект по журналу построения. \en Rebuild object according to the history tree.
  virtual bool    RebuildItem( MbeCopyMode sameShell, RPArray<MbSpaceItem> * items, IProgressIndicator * progInd );
  // \ru Создать полигональный объект - упрощенную копию данного объекта. \en Create a polygonal object - a simplified copy of the given object.
  // \note \ru В многопоточном режиме выполняется параллельно. \en In multithreaded mode runs in parallel.
  virtual MbItem * CreateMesh( const MbStepData & stepData, const MbFormNote & note, MbRegDuplicate * iReg ) const;
  // \ru Добавить полигональную сетку объекта. \en Add a polygonal mesh of the object.
  virtual bool     AddYourMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const;
  // \ru Разрезать полигональный объект одной или двумя параллельными плоскостями. \en Cut the polygonal object by one or two parallel planes.
  virtual MbItem * CutMesh( const MbPlacement3D & cutPlace, double distance ) const;
  // \ru Найти ближайший объект или имя ближайшего объекта. \en Find the closest object or its name.
  virtual bool     NearestMesh( MbeSpaceType sType, MbeTopologyType tType, MbePlaneType pType,
                                const MbAxis3D & axis, double maxDistance, bool gridPriority, double & t, double & dMin,
                                MbItem *& find, SimpleName & findName,
                                MbRefItem *& element, SimpleName & elementName,
                                MbPath & path, MbMatrix3D & from ) const;
  // \ru Дать все объекты указанного типа. \en Get all objects by type. \~
  virtual bool    GetItems( MbeSpaceType type, const MbMatrix3D & from,
                            RPArray<MbItem> & items, SArray<MbMatrix3D> & matrs );
  // \ru Дать все полигональные объекты, отображающие геометрические элементы, участвующие в геометрических огриничениях.\en Get all polygonal objects for drawing the elements participated in geometric constraints. \~
          bool    GetConstraintMesh( std::vector<const MbMesh *> & meshes ) const;
  // \ru Дать все уникальные объекты указанного типа. \en Get all unique objects by type . \~
  virtual bool    GetUniqItems( MbeSpaceType type, CSSArray<const MbItem *> & items ) const;
  // \ru Дать объект по его пути положения в модели и матрицу преобразования объекта в глобальную систему координат. \en Get the object by its path in the model and get the matrix of transformation of the object to the global coordinate system.
  virtual const MbItem * GetItemByPath( const MbPath & path, size_t ind, MbMatrix3D & from, size_t currInd = 0 ) const;
  // \ru Найти объект по геометрическому объекту (MbSpaceItem). \en Find the object by a geometric object (MbSpaceItem).
  virtual const MbItem * FindItem( const MbSpaceItem * s, MbPath & path, MbMatrix3D & from ) const;
  // \ru Найти объект по геометрическому объекту (MbPlaneItem). \en Find the object by a geometric object (MbSpaceItem).
  virtual const MbItem * FindItem( const MbPlaneItem * s, MbPath & path, MbMatrix3D & from ) const;
  // \ru Найти объект и матрицу его преобразования в глобальную систему координат. \en Find the object and the matrix of its transformation to the global coordinate system.
  virtual const MbItem * FindItem( const MbItem * s, MbPath & path, MbMatrix3D & from ) const;
  // \ru Дать объект с заданным именем и матрицу его преобразования в глобальную систему координат. \en Get the object with the specified name and the matrix of its transformation to the global coordinate system.
  virtual const MbItem * GetItemByName( SimpleName n, MbPath & path, MbMatrix3D & from ) const;

  // \ru Преобразовать согласно матрице c использованием регистратора селектированные содержимые объекты. \en Transform selected objects according to the matrix using the registrator.
  virtual void    TransformSelected( const MbMatrix3D & matr, MbRegTransform * iReg = NULL );
  // \ru Сдвинуть вдоль вектора с использованием регистратора селектированные содержимые объекты. \en Move selected objects along the vector using the registrator.
  virtual void    MoveSelected( const MbVector3D & to, MbRegTransform * iReg = NULL );
  // \ru Повернуть вокруг оси на заданный угол с использованием регистратора селектированные содержимые объекты. \en Rotate selected objects about the axis by the given angle using the registrator.
  virtual void    RotateSelected( const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL );
          /// \ru Отдать селектированные содержимые объекты. \en Get selected objects.
          bool    DetachSelected( RPArray<MbItem> & items, SArray<MbMatrix3D> & matrs, bool selected = true );
          /// \ru Отцепить все видимые или невидимые объекты. \en Detach all visible or invisible objects. \~
          bool    DetachInvisible( RPArray<MbItem> & items, SArray<MbMatrix3D> & matrs, bool invisible = true );
          /// \ru Отцепить все объекты с указанным свойством. \en Detach all objects with pointed attribute. \~
          bool    DetachByAttribute( RPArray<MbItem> & items, SArray<MbMatrix3D> & matrs, int attribute );

public:
  /** \ru \name Функции сборочной единицы.
      \en \name The assembly unit functions.
      \{ */
          /// \ru Выдать непосредственный объект сборки по идентификатору. \en Get the immediate item of assembly by identifier.
          const  MbItem * SubItem( SimpleName n ) const { return _ItemByName(n); }
          /// \ru Добавить объект в сборку. \en Add an item to the assembly.
          MbItem *        AddItem( MbItem & item );        
        /**
          \brief \ru Добавить вставку геометрического объекта. 
                 \en Add an instance of the geometric object. \~
          \param item - \ru Источник, на котором основан экземпляр вставки.
                        \en A source item on which the instance is based.                      
          \param lcs - \ru Локальная система координат экземпляра вставляемого объекта.
                       \en Local coordinate system of the instanced object. \~
          \return \ru Экземпляр класса MbInstance, размещающего объект в пространстве сборки.
                  \en An Instance of class MbInstance placing the item in the space of the assembly.
        */
          MbItem *  AddInstance( MbItem & item, const MbPlacement3D & lcs );
        /** \brief \ru Заменить объект.
                    \en Replace an item. \~
          \details \ru Заменить объект новым.
                    \en Replace an item by a new one. \~
          \param[in] item - \ru Заменяемый объект.
                            \en An item to be replaced. \~
          \param[in] newItem - \ru Новый объект.
                                \en A new item. \~
          \return \ru Возвращает true, если замена была выполнена.
                  \en Returns true if the replacement has been performed. \~
        */
          bool    ReplaceItem( const MbItem & item, MbItem & newItem, bool saveName = false );

          /// \ru Выдать все объекты. \en Get all the items.
          void    GetItems( RPArray<const MbItem> & items ) const;
          /// \ru Выдать все объекты. \en Get all the items.
          void    GetItems( RPArray<MbItem> & items );

          /// \ru Отцепить объект по индексу. \en Detach the item by index.
          MbItem* DetachItem ( size_t ind );
          /// \ru Отцепить объект, если такой есть в сборке. \en Detach the item if it belongs to the assembly.
          bool    DetachItem ( MbItem * obj );
          /// \ru Удалить объект, если такой есть в сборке или в подсборках. \en Delete the item if it belongs to the assembly or its sub-assemblies.
          bool    DeleteItem ( MbItem * obj );
          /// \ru Удалить все объекты сборки. \en Delete all the assembly items.
          void    DeleteItems();
          /// \ru Выдать количество объектов сборки. \en Get the assembly item count.
          size_t  ItemsCount() const { return assemblyItems.size(); }
          /// \ru Вернуть true, если сборка не содержит геометрических объекты. \en Return true, if the assembly has no geometric objects.
          bool    IsEmpty() const { return assemblyItems.empty(); }
          /// \ru Выдать объект по индексу. \en Get the item by index.
    const MbItem * GetItem( size_t i ) const;
          /// \ru Выдать объект по индексу для модификации. \en Get the item by index for modification.
          MbItem * SetItem( size_t i );
          /// \ru Содержит ли сборка присланный объект? \en Does the assembly contain the given item?
          bool    ContainsItem( const MbItem * obj ) const;
          /// \ru Вычислить габарит сборки. \en Calculate the bounding box of the assembly.
          void    CalculateGabarit( MbCube & cube ) const;
          /// \ru Выдать количество граней. \en Get the number of faces. 
          size_t  GetFacesCount() const;
          /// \ru Заполнить контейнер гранями тела. \en Fill container by solid faces. 
          template <class FacesVector>
          void    GetFacesSet( FacesVector & faces ) const;
public:
  /** \}
      \ru \name Функции системы ограничений.
      \en \name The constraint system functions.
      \{ */
          /// \ru Добавить ограничение для пары геометрических объектов. \en Add geometric constraint.
          MtGeomConstraint AddConstraint( MtMateType, const MtGeomArgument &, const MtGeomArgument &, MtParVariant = MtParVariant::undef );
          /// \ru Изменить значение управляющего размера. \en Change the value of driving dimension.
          MtResultCode3D   ChangeDimension( MtGeomConstraint & dimCon, double newVal );
          /// \ru Решить ограничения сборки. \en Evaluate constraints.
          MtResultCode3D   EvaluateConstraints();
          /// \ru Выдать диапазон итераторов для обхода всех ограничений сборки. \en Get a range of iterators to traverse all assembly constraints.
          void    GetConstraints( MtConstraintIter & begIter, MtConstraintIter & endIter ) const;
          /// \ru Задать или сбросить обработчик событий решателя. \en Set or reset an handler of constraint solving events.
          void    SetReactor( ItAssemblyReactor * ) const;
          /// \ru Импортировать систему ограничений из приложения САПР. \ru Import the constraint system from CAD application.
          bool    Import( ItAssemblyImportData & );

public:
  /** \} */
  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbAssembly );

  static const MbPlacement3D & GetPlacement() { return MbPlacement3D::global; } // This function is deprecated. Use MbInstanse to give the assembly its own placement.

  friend class MbModelTreeReader;

private:
        // \ru Инициализатор по массиву составляющих объектов. // \en Initializer to aggregate items in the assembly.
          template <class ItemsVector>
          void   _Init( const ItemsVector & );
          // Найти объект по геометрическому объекту
          template <class ItemType>
    const MbItem * _FindItem( const ItemType * s, MbPath & path, MbMatrix3D & from ) const;
          // Поиск в глубину среди подчиненных
          template<class ItemType>
    const MbItem * _FindRecursively( const ItemType * s, MbPath & path, MbMatrix3D & from ) const;
          // \ru Выдать объект по идентификатору. \en Get the item by identifier.
    const MbItem * _ItemByName( SimpleName ) const;
          // \ru Генерация имени для нового элемента сборки. \en Generate identifier for new assembly item.
          SimpleName _NewItemName() const;
          /// \ru Добавить в сборку объекты сборки без трансформации. \en Add assembly items to the assembly without transformation.
          bool   _AddAssemblyItems( MbAssembly & );
          // Обход дерева модели в глубину
          void   _Traverse( _ItemVisitor & );

  OBVIOUS_PRIVATE_COPY( MbAssembly );
}; // MbAssembly

IMPL_PERSISTENT_OPS( MbAssembly )


//----------------------------------------------------------------------------------------
// \ru Конструктор по объектам. \en The constructor by objects.
//---
template <class ItemsVector>
MbAssembly::MbAssembly( const ItemsVector & items )
  : MbItem()
  , assemblyItems()
  , constraintSystem( NULL )
  , m_reactor( NULL )
{
#ifdef C3D_DEBUG
  // Check a condition of the single owner.
  for ( size_t i = 0, iCount = items.size(); i < iCount; ++i ) 
  {
    if ( items[i]->GetItemName() != UNDEFINED_SNAME ) 
    {
      C3D_ASSERT_UNCONDITIONAL( false ); // The item has already a name. It's probably means that the item is owned another assembly.
      break;
    }
  }
#endif // C3D_DEBUG

  _Init( items );
}


//----------------------------------------------------------------------------------------
// \ru Инициализатор по массиву составляющих объектов.
// \en Initializer to aggregate items in the assembly.
//---
template <class ItemsVector>
void MbAssembly::_Init( const ItemsVector & items )
{
  C3D_ASSERT( assemblyItems.empty() && (constraintSystem == NULL) );
  SimpleName idCounter = 0;

  for ( size_t i = 0, iCount = items.size(); i < iCount; ++i ) 
  {
    if ( MbItem * item = items[i] ) {
      if ( item->GetItemName() == UNDEFINED_SNAME ) {
        item->SetItemName( idCounter );
      }
      else {
        C3D_ASSERT( idCounter <= item->GetItemName() );
        idCounter = max_of( idCounter, item->GetItemName() );
      }
      ++idCounter;
      item->AddRef();
      assemblyItems.push_back( item );
    }
  }
}


//----------------------------------------------------------------------------------------
// \ru Заполнить контейнер гранями тела. \en Fill container by solid faces. 
//---
template <class FacesVector>
void MbAssembly::GetFacesSet( FacesVector & faces ) const
{
  for ( size_t i = assemblyItems.size(); i--; ) {
    const MbItem * assemblyItem = assemblyItems[i];
    if ( assemblyItem != NULL ) {
      if ( assemblyItem->IsA() == st_Solid )
        static_cast<const MbSolid &>(*assemblyItem).GetFacesSet( faces );
      else if ( assemblyItem->IsA() == st_Instance )
        static_cast<const MbInstance &>(*assemblyItem).GetFacesSet( faces );
      else if ( assemblyItem->IsA() == st_Assembly )
        static_cast<const MbAssembly &>(*assemblyItem).GetFacesSet( faces );
    }
  }
}

//----------------------------------------------------------------------------------------
// \ru Заполнить контейнер гранями тела. \en Fill container by solid faces. 
//---
template <class FacesVector>
void MbInstance::GetFacesSet( FacesVector & faces ) const
{
  if ( item != NULL ) {
    if ( item->IsA() == st_Solid )
      static_cast<const MbSolid &>( *item ).GetFacesSet( faces );
    else if ( item->IsA() == st_Assembly )
      static_cast<const MbAssembly &>( *item ).GetFacesSet( faces );
    else if ( item->IsA() == st_Instance )
      static_cast<const MbInstance &>( *item ).GetFacesSet( faces );
  }
}


#endif // __ASSEMBLY_H
