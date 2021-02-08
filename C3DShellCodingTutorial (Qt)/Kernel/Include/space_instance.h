//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Вставка трёхмерного объекта.
         \en Instance of three-dimensional object. \~

*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SPACE_INSTANCE_H
#define __SPACE_INSTANCE_H


#include <space_item.h>
#include <model_item.h>
#include <mb_placement3d.h>
#include <math_define.h>


class  MATH_CLASS  MbLegend;
class  MATH_CLASS  MbPoint3D;
class  MATH_CLASS  MbCurve3D;
class  MATH_CLASS  MbSurface;


class  MATH_CLASS MbSpaceInstance;
namespace c3d // namespace C3D
{
typedef SPtr<MbSpaceInstance>                 SInstanceSPtr;
typedef SPtr<const MbSpaceInstance>           ConstSInstanceSPtr;

typedef std::vector<MbSpaceInstance *>        SInstancesVector;
typedef std::vector<const MbSpaceInstance *>  ConstSInstancesVector;

typedef std::vector<SInstanceSPtr>            SInstancesSPtrVector;
typedef std::vector<ConstSInstanceSPtr>       ConstSInstancesSPtrVector;
}


//----------------------------------------------------------------------------------------
/** \brief  \ru Вставка трёхмерного объекта.
            \en Instance of three-dimensional object. \~
  \details  \ru Вставка позволяет работать с трёхмерным геометрическим объектом, как  с 
            объектом геометричекой модели. Вставка позволяет использовать в геометричекой 
            модели любые другие объекты MbSpaceItem, например, резьбу и условные обозначения.
            \en Instance allows to deal with three-dimensional object as with object of 
            geometric model. Instance allows to use any objects inherited from MbSpaceItem
            such as thread and conventional notations in geometric model. \~
  \ingroup Model_Items
*/
// ---
class MATH_CLASS MbSpaceInstance : public MbItem {
protected :
  MbSpaceItem * spaceItem; ///< \ru Трёхмерный геометрический объект. \en Three-dimensional geometric object. 

protected :
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  explicit MbSpaceInstance( const MbSpaceInstance &, MbRegDuplicate * );
public :
  /// \ru Конструктор по вспомогательному объекту. \en Constructor by auxiliary item. 
  MbSpaceInstance( MbLegend & );
  /// \ru Конструктор по точке. \en Constructor by point. 
  MbSpaceInstance( MbPoint3D & );
  /// \ru Конструктор по кривой. \en Constructor by curve. 
  MbSpaceInstance( MbCurve3D & );
  /// \ru Конструктор по поверхности. \en Constructor by surface. 
  MbSpaceInstance( MbSurface & );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbSpaceInstance();

public :
  VISITING_CLASS( MbSpaceInstance ); 

  // \ru Общие функции геометрического объекта. \en Common functions of a geometric object.  
  virtual MbeSpaceType  IsA()  const; // \ru Тип объекта. \en A type of an object. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Создать копию. \en Create a copy. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * iReg = NULL ); // \ru Преобразовать согласно матрице. \en Transform according to the matrix.  
  virtual void    Move     ( const MbVector3D &, MbRegTransform * iReg = NULL ); // \ru Сдвинуть вдоль вектора. \en Translate along a vector. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * iReg = NULL ); // \ru Повернуть вокруг оси. \en Rotate about an axis. 
  virtual	bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными? \en Are the objects equal? 
  virtual bool    IsSimilar( const MbSpaceItem & init ) const; // \ru Являются ли объекты подобными? \en Are the objects similar? 
  virtual bool    SetEqual ( const MbSpaceItem & init ); // \ru Сделать объекты равными. \en Make the objects equal. 
  virtual double  DistanceToPoint ( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate the distance to a point. 
  virtual void    AddYourGabaritTo( MbCube & r ) const; // \ru Добавь свой габарит в куб. \en Add bounding box into a cube. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D & into, MbCube & cube ) const; // \ru Рассчитать габарит в локальной системы координат. \en Calculate bounding box in the local coordinate system. 
  virtual void    CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; // \ru Построить полигональную копию mesh. \en Build polygonal copy mesh.

  virtual MbProperty & CreateProperty( MbePrompt n ) const; // \ru Создать собственное свойство. \en Create a custom property. 
  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Установить свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Создать полигональный объект - упрощенную копию данного объекта. \en Create a polygonal object - a simplified copy of the given object. 
  virtual MbItem *        CreateMesh( const MbStepData & stepData, const MbFormNote & note, MbRegDuplicate * iReg ) const; 
  // \ru Найти объект по геометрическому объекту (MbSpaceItem). \en Find the object by a geometric object (MbSpaceItem). 
  virtual const MbItem *  FindItem( const MbSpaceItem * s, MbPath & path, MbMatrix3D & from ) const;
  // \ru Дать все объекты указанного типа. \en Get all objects by type. \~
  virtual bool            GetItems( MbeSpaceType type, const MbMatrix3D & from, 
                                    RPArray<MbItem> & items, SArray<MbMatrix3D> & matrs ); 
  // \ru Дать все уникальные объекты указанного типа. \en Get all unique objects by type . \~
  virtual bool            GetUniqItems( MbeSpaceType type, CSSArray<const MbItem *> & items ) const; 

  /** \ru \name Общие функции вставки трёхмерного объекта.
      \en \name Common functions of instance of three-dimensional object.
      \{ */
          /// \ru Выдать трёхмерный геометрический объект. \en Get three-dimensional geometric object. 
  const MbSpaceItem * GetSpaceItem() const; 
          /// \ru Выдать трёхмерный геометрический объект для модификации. \en Get three-dimensional geometric object for modification. 
        MbSpaceItem * SetSpaceItem();       
          /// \ru Заменить геометрический объект. \en Replace geometric object. 
        void          SetSpaceItem( MbSpaceItem * init ); 
  /** \} */

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbSpaceInstance ) 
OBVIOUS_PRIVATE_COPY( MbSpaceInstance )
};

IMPL_PERSISTENT_OPS( MbSpaceInstance )

#endif // __SPACE_INSTANCE_H
