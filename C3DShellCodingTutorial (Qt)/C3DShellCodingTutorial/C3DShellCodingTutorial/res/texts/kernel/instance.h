//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Вставка объекта.
         \en Instance of object. \~
  \details \ru Вставка объекта геометрической модели MbItem в локальной системе координат MbPlacement3D
  позволяет накладывать геометрические ограничения на объект в сборке и позиционоровать объект. 
  Вставка не может содержать другую вставку. \n
           \en The instance of geometric model MbItem object in local coordinate system MbPlacement3D
  allows to define constraints for an object in the assembly and to locate the object. 
  The instance cannot contain another instance. \n \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __INSTANCE_H
#define __INSTANCE_H

#include <model_item.h>
#include <mb_placement3d.h>


class  MATH_CLASS MbSolid;
class  MATH_CLASS MbInstance;
class  MATH_CLASS MbAssembly;

namespace c3d // namespace C3D
{
typedef SPtr<MbInstance>                InstanceSPtr;
typedef SPtr<const MbInstance>          ConstInstanceSPtr;

typedef std::vector<MbInstance *>       InstancesVector;
typedef std::vector<const MbInstance *> ConstInstancesVector;

typedef std::vector<InstanceSPtr>       InstancesSPtrVector;
typedef std::vector<ConstInstanceSPtr>  ConstInstancesSPtrVector;
}


//----------------------------------------------------------------------------------------
/** \brief \ru Вставка объекта.
           \en Instance of object. \~
  \details \ru Вставка объекта геометрической модели MbItem в локальной системе координат MbPlacement3D
    позволяет накладывать геометрические ограничения на объект в сборке и позиционоровать объект. 
    Вставка не может содержать другую вставку. \n
           \en The instance of geometric model MbItem object in local coordinate system MbPlacement3D
    allows to define constraints for an object in the assembly and to locate the object. 
    The instance cannot contain another instance. \n \~
  \ingroup Model_Items
*/
// ---
class MATH_CLASS MbInstance : public MbItem 
{
  MbPlacement3D place; ///< \ru Локальная система координат объекта. \en Local coordinate system of the object.   
  SPtr<MbItem>  item;  ///< \ru Геометрический объект. \en A geometric object.

protected :
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  explicit MbInstance( const MbInstance &, MbRegDuplicate * );

public :
  /// \ru Конструктор по объекту и его системе координат. \en The constructor by an object and its coordinate system.  
  MbInstance( MbItem &, const MbPlacement3D & );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbInstance();

public :
  VISITING_CLASS( MbInstance ); 

  // \ru Общие функции геометрического объекта. \en Common functions of a geometric object.  
  virtual MbeSpaceType  IsA()  const; // \ru Тип объекта. \en An object type. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Создать копию. \en Create a copy. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * iReg = NULL ); // \ru Преобразовать согласно матрице. \en Transform according to the matrix.  
  virtual void    Move     ( const MbVector3D &, MbRegTransform * iReg = NULL ); // \ru Сдвинуть вдоль вектора. \en Move along a vector. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * iReg = NULL ); // \ru Повернуть вокруг оси. \en Rotate about an axis. 
  virtual	bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными? \en Whether the objects are equal? 
  virtual bool    IsSimilar( const MbSpaceItem & init ) const; // \ru Являются ли объекты подобными? \en Whether the objects are similar? 
  virtual bool    SetEqual ( const MbSpaceItem & init ); // \ru Сделать объекты равными. \en Make the objects equal. 
  virtual double  DistanceToPoint ( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate distance to point. 
  virtual void    AddYourGabaritTo( MbCube & r ) const; // \ru Добавь свой габарит в куб. \en Add own bounding box to the bounding box. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D & into, MbCube & cube ) const; // \ru Рассчитать габарит в локальной системы координат. \en Calculate the bounding box in a local coordinate system. 
  virtual void    CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; // \ru Построить полигональную копию mesh. \en Build polygonal copy mesh.

  virtual MbProperty & CreateProperty( MbePrompt n ) const;     // \ru Создать собственное свойство. \en Create own property. 
  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Установить свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Получить систему координат объекта. \en Get the coordinate system of an item. 
  virtual bool    GetPlacement( MbPlacement3D & ) const; 
  // \ru Установить систему координат объекта. \en Set the coordinate system of an item. 
  virtual bool    SetPlacement( const MbPlacement3D & );

  // \ru Перестроить объект по журналу построения. \en Reconstruct object according to the history tree. 
  virtual bool    RebuildItem( MbeCopyMode sameShell, RPArray<MbSpaceItem> * items, IProgressIndicator * progInd );

  // \ru Создать полигональный объект - упрощенную копию данного объекта. \en Create a polygonal object - a simplified copy of the given object. 
  virtual MbItem * CreateMesh( const MbStepData & stepData, const MbFormNote & note, MbRegDuplicate * iReg ) const; 
  // \ru Добавить полигонную сетку объекта. \en Add a polygon mesh of the object. 
  virtual bool    AddYourMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; 
  // \ru Разрезать полигональный объект одной или двумя параллельными плоскостями. \en Cut the polygonal object by one or two parallel planes. 
  virtual MbItem * CutMesh( const MbPlacement3D & cutPlace, double distance ) const; 
  // \ru Найти ближайший объект или имя ближайшего объекта. \en Find the closest object or its name. 
  virtual bool    NearestMesh( MbeSpaceType sType, MbeTopologyType tType, MbePlaneType pType, 
                               const MbAxis3D & axis, double maxDistance, bool gridPriority, double & t, double & dMin, 
                               MbItem *& find, SimpleName & findName,
                               MbRefItem *& element, SimpleName & elementName,
                               MbPath & path, MbMatrix3D & from ) const; 
  // \ru Дать все объекты указанного типа. \en Get all objects by type. \~
  virtual bool    GetItems( MbeSpaceType type, const MbMatrix3D & from, 
                            RPArray<MbItem> & items, SArray<MbMatrix3D> & matrs ); 
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

  // \ru Преобразовать согласно матрице c использованием регистратора содержимый объект, если он селектирован. \en Transform the contained object according to the matrix using the registrator if the object selected.  
  virtual void    TransformSelected( const MbMatrix3D & matr, MbRegTransform * iReg = NULL ); 
  // \ru Сдвинуть вдоль вектора с использованием регистратора содержимый объект, если он селектирован. \en Translate the contained object along the vector according to the matrix using the registrator if the object selected. 
  virtual void    MoveSelected( const MbVector3D & to, MbRegTransform * iReg = NULL );
  // \ru Повернуть вокруг оси на заданный угол с использованием регистратора содержимый объект, если он селектирован. \en Translate the contained object about the axis according to the matrix using the registrator if the object selected.  
  virtual void    RotateSelected( const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL );

  /// \ru Дать матрицу преобразования из локальной системы объекта. \en Get transform matrix from local coordinate system of object.
  virtual bool    GetMatrixFrom( MbMatrix3D & from ) const;
  /// \ru Дать матрицу преобразования в  локальную систему объекта. \en Get transform matrix into local coordinate system of object.
  virtual bool    GetMatrixInto( MbMatrix3D & into ) const;

  /** \ru \name Функции вставки объекта.
      \en \name Functions of the object instance.
      \{ */
          /// \ru Выдать геометрический объект. \en Get the geometric object. 
  const   MbItem * GetItem() const { return item; }
          /// \ru Выдать геометрический объект для модификации. \en Get the geometric object for modification. 
          MbItem * SetItem()       { return item; }
          /// \ru Установить другой геометрический объект. \en Set another geometric object. 
          void    SetItem( MbItem * init ); 

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

          /// \ru Выдать количество граней. \en Get the number of faces. 
          size_t  GetFacesCount() const;
          /// \ru Заполнить контейнер гранями тела. \en Fill container by solid faces. 
          template <class FacesVector>
          void    GetFacesSet( FacesVector & faces ) const;
          /// \ru Выдать систему координат объекта. \en Get the coordinate system of an item. 
  const   MbPlacement3D & GetPlacement() const { return place; }
          /// \ru Выдать систему координат объекта для редактирования. \en Get the coordinate system of an assembly item for editing. 
          MbPlacement3D & SetPlacement()       { return place; } 

  /** \} */

private:
  // Найти объект по геометрическому объекту
  template<class _ItemType>
  const MbItem * _FindItem( const _ItemType * s, MbPath & path, MbMatrix3D & from ) const;

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbInstance ) ;
  OBVIOUS_PRIVATE_COPY( MbInstance );
};

IMPL_PERSISTENT_OPS( MbInstance )


#endif
