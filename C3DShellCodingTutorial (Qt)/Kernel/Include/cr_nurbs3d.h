////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель пространственного сплайна с сопряжениями.
         \en Constructor of the spatial spline with tangents.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_NURBS3D_H
#define __CR_NURBS3D_H


#include <creator.h>
#include <cur_nurbs3d.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель пространственного сплайна.
           \en Spatial spline constructor. \~
  \details \ru Строитель пространственного сплайна.\n
           \en Spatial spline constructor.\n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbNurbs3DCreator : public MbCreator {
private:
  SArray<MbCartPoint3D>                  points;        // \ru Точки, через которые проходит сплайн \en Points which the spline passes through  
  SArray<double>                         weights;       // \ru Веса \en Weights 
  SArray<double>                         knots;         // \ru Узлы \en Knots 
  RPArray< MbPntMatingData<MbVector3D> > matingData;    // \ru Данные сопряжения в точках \en Data about mating in the points    
  MbeSplineParamType                     paramType;     // \ru Тип параметризации \en Parametrization type 
  size_t                                 degree;        // \ru Степень сплайна \en Spline degree 
  bool                                   closed;        // \ru Замкнутость сплайна \en Spline closedness 
  bool                                   throughPnts;   // \ru через точки \en Through points 

protected:
  MbNurbs3DCreator( const MbNurbs3DCreator &, MbRegDuplicate * iReg ); // \ru Конструктор копирования \en Copy-constructor 
  MbNurbs3DCreator( const MbNurbs3DCreator & ); // \ru Не реализовано \en Not implemented 
  MbNurbs3DCreator(); // \ru Не реализовано \en Not implemented 
public:
  MbNurbs3DCreator( const SArray<MbCartPoint3D> & spacePnts, bool throughPnts,
                    MbeSplineParamType paramType, size_t degree, bool closed,
                    const SArray<double> * weights,
                    const SArray<double> * knots,
                    const RPArray< MbPntMatingData<MbVector3D> > & matingData,
                    const MbSNameMaker & snMaker );
public:
  virtual ~MbNurbs3DCreator();

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
          void        operator = ( const MbNurbs3DCreator & ); // \ru Не реализовано!!! \en Not implemented!!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbNurbs3DCreator )
};

IMPL_PERSISTENT_OPS( MbNurbs3DCreator )

//------------------------------------------------------------------------------
/** \brief \ru Создать пространственный сплайн через точки и с сопряжениями.
           \en Create a spatial spline through points and with the given tangents. \~
  \details \ru Создать пространственный сплайн через точки и с сопряжениями
    Если есть сопряжения, то количество сопряжений д.б. равно количеству точек.
    Отсутствующие сопряжения должны быть представлены нулевыми указателями в массиве.
           \en Create a spatial spline through points with tangents
    If the tangents are specified, then the number of tangents should be equal to the number of points.
    The missing tangents should be represented as the null pointers in the array. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Curve3D_Modeling
*/
//---
MATH_FUNC (MbCreator *) CreateSplineThrough( const SArray<MbCartPoint3D> & points,    // \ru Точки \en Points 
                                             MbeSplineParamType            paramType, // \ru Тип параметризации \en Parametrization type 
                                             size_t                        degree,    // \ru Порядок сплайна \en Spline degree 
                                             bool                          closed,    // \ru Замкнуть \en Make close 
                                             RPArray< MbPntMatingData<MbVector3D> > & transitions, // \ru Сопряжения \en Tangents 
                                             const MbSNameMaker &          snMaker,   // \ru Именователь \en An object for naming the new objects 
                                             MbResultType &                resType,
                                             MbCurve3D *&                  resCurve );


//------------------------------------------------------------------------------
/** \brief \ru Создать пространственный сплайн по точкам и сопряжениями.
           \en Create a spatial spline from points and tangents. \~
  \details \ru Создать пространственный сплайн по точкам и сопряжениями.\n
           \en Create a spatial spline from points and tangents.\n \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Curve3D_Modeling
*/
//---
MATH_FUNC (MbCreator *) CreateSplineBy( const SArray<MbCartPoint3D> & points,    // \ru Точки \en Points 
                                        size_t                        degree,    // \ru Порядок сплайна \en Spline degree 
                                        bool                          closed,    // \ru Замкнуть \en Make close 
                                        const SArray<double> *        weights,   // \ru Веса \en Weights 
                                        const SArray<double> *        knots,     // \ru Узлы \en Knots 
                                        MbPntMatingData<MbVector3D> * begData,   // \ru Сопряжение в начале \en Tangent at the start point 
                                        MbPntMatingData<MbVector3D> * endData,   // \ru Сопряжение в конце \en Tangent at the end point 
                                        const MbSNameMaker &          snMaker,   // \ru Именователь \en An object for naming the new objects 
                                        MbResultType &                resType,
                                        MbCurve3D *&                  resCurve );


#endif // __CR_NURBS3D_H
