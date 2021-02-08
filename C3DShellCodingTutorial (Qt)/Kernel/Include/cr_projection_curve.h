////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель проволочного каркаса из проекционных кривых.
         \en Projection wireframe constructor.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_PROJECTION_CURVE_H
#define __CR_PROJECTION_CURVE_H


#include <creator.h>
#include <wire_frame.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель проволочного каркаса из проекционных кривых.
           \en Projection wireframe constructor. \~
  \details \ru Строитель проволочного каркаса из проекционных кривых.\n
           \en Projection wireframe constructor.\n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbProjCurveCreator : public MbCreator {
private:
  MbWireFrame *      wireFrame;        // \ru Проецируемый проволочный каркас. \en Wireframe to project.
  RPArray<MbCreator> shellCreators;    // \ru Протокол построения оболочки, на которую выполняется проецирование \en History tree of the shell the projection is performed onto 
  MbVector3D         dir;              // \ru Вектор направления (если нулевой, то проекция по нормали) \en Direction vector (if zero, the normal projection) 
  bool               createExact;      // \ru Создавать проекционную кривую при необходимости \en Create the projection curve if necessary 
  bool               truncateByBounds; // \ru Усечь границами \en Truncate by bounds

protected:
  MbProjCurveCreator( const MbProjCurveCreator &, MbRegDuplicate * iReg ); // \ru Конструктор копирования \en Copy-constructor 
  MbProjCurveCreator( const MbProjCurveCreator & ); // \ru Не реализовано \en Not implemented 
  MbProjCurveCreator(); // \ru Не реализовано \en Not implemented 
public:
  MbProjCurveCreator( const MbCurve3D & curve,
                      const RPArray<MbCreator> & shellCreators, bool sameCreators,
                      const MbVector3D * dir, bool exact, bool truncate,
                      const MbSNameMaker & snMaker );

  MbProjCurveCreator( const MbWireFrame &wf, const bool sameWire,
                      const RPArray<MbCreator> & shellCreators, bool sameCreators,
                      const MbVector3D * dir, bool exact, bool truncate,
                      const MbSNameMaker & snMaker );
public:
  virtual ~MbProjCurveCreator();

  // \ru Общие функции строителя. \en The common functions of the creator. 
  virtual MbeCreatorType  IsA()  const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Сделать копию \en Create a copy 

  virtual bool        IsSame   ( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const;            // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );                  // \ru Сделать равным \en Make equal 

  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual MbePrompt   GetPropertyName(); // \ru Дать имя свойства объекта \en Get the object property name  
  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & );  // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  virtual size_t      GetCreatorsCount( MbeCreatorType ct ) const; // \ru Посчитать внутренние построители по типу. \en Count internal creators by type.
  virtual bool        GetInternalCreators( MbeCreatorType, c3d::ConstCreatorsSPtrVector & ) const; // \ru Получить внутренние построители по типу. \en Get internal creators by type.
  virtual bool        SetInternalCreators( MbeCreatorType, c3d::CreatorsSPtrVector & );            // \ru Получить внутренние построители по типу. \en Get internal creators by type.

  // \ru Построить кривую по журналу построения \en Create a curve from the history tree 
  virtual bool        CreateWireFrame( MbWireFrame *&, MbeCopyMode, RPArray<MbSpaceItem> * items = NULL );

  /** \} */

private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation, to prevent an assignment by default. 
          void        operator = ( const MbProjCurveCreator & ); // \ru Не реализовано!!! \en Not implemented!!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbProjCurveCreator )
};

IMPL_PERSISTENT_OPS( MbProjCurveCreator )

#endif // __CR_PROJECTION_CURVE_H
