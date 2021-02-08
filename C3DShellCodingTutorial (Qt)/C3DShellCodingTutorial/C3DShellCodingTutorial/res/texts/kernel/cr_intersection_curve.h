////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель кривой пересечения.
         \en Intersection curve constructor.
*/
////////////////////////////////////////////////////////////////////////////////
  
#ifndef __CR_INTERSECTION_CURVE_H
#define __CR_INTERSECTION_CURVE_H


#include <creator.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель кривой пересечения.
           \en Intersection curve constructor. \~
  \details \ru Строитель кривой пересечения.\n
           \en Intersection curve constructor.\n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbIntCurveCreator : public MbCreator {
private:
  RPArray<MbCreator> creators1; // \ru Журнал построения первой оболочки. \en The first shell history tree. 
  RPArray<MbCreator> creators2; // \ru Журнал построения второй оболочки. \en The second shell history tree. 

protected:
  MbIntCurveCreator( const MbIntCurveCreator &, MbRegDuplicate * iReg ); // \ru Конструктор копирования \en Copy-constructor 
  MbIntCurveCreator( const MbIntCurveCreator & ); // \ru Не реализовано \en Not implemented 
  MbIntCurveCreator(); // \ru Не реализовано \en Not implemented 
public:
  MbIntCurveCreator( const RPArray<MbCreator> & creators1, bool same1,
                     const RPArray<MbCreator> & creators2, bool same2,
                     const MbSNameMaker & snMaker );
public:
  virtual ~MbIntCurveCreator();

  // \ru Общие функции строителя. \en The common functions of the creator.
  virtual MbeCreatorType  IsA()  const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Сделать копию \en Create a copy 

  virtual bool        IsSame   ( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const;            // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );                  // \ru Сделать равным \en Make equal

  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual MbePrompt GetPropertyName(); // \ru Дать имя свойства объекта \en Get the object property name  
  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & );  // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Построить кривую по журналу построения \en Create a curve from the history tree 
  virtual bool        CreateWireFrame( MbWireFrame *&, MbeCopyMode, RPArray<MbSpaceItem> * items = NULL );

  /** \} */

private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation, to prevent an assignment by default. 
          void        operator = ( const MbIntCurveCreator & ); // \ru Не реализовано!!! \en Not implemented!!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbIntCurveCreator )
};

IMPL_PERSISTENT_OPS( MbIntCurveCreator )

#endif // __CR_INTERSECTION_CURVE_H
