////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель кривой сопряжения двух кривых.
         \en Constructor of curve connecting two curves.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_CONNECTING_CURVE_H
#define __CR_CONNECTING_CURVE_H


#include <creator.h>


class  MATH_CLASS MbCartPoint;
class  MATH_CLASS MbCurve3D;
class  MATH_CLASS MbSurface;
class  MATH_CLASS MbElementarySurface;
class  MATH_CLASS MbEdge;


//------------------------------------------------------------------------------
/** \brief \ru Строитель кривой сопряжения двух кривых.
           \en Constructor of curve connecting two curves. \~
  \details \ru Строитель кривой сопряжения двух кривых.\n
           \en Constructor of curve connecting two curves.\n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbConnectingCurveCreator : public MbCreator {
private:
  MbCurve3D *   curve1;   ///< \ru Первая скругляемая кривая \en The first curve to connect  
  MbCurve3D *   curve2;   ///< \ru Вторая скругляемая кривая \en The second curve to connect  
  double        init1;    ///< \ru Исходное приближение параметра первой скругляемой кривой (для ft_Fillet и ft_OnSurface) \en The initial approximation of parameter of the first curve to be connected (for ft_Fillet and ft_OnSurface) 
  double        init2;    ///< \ru Исходное приближение параметра второй скругляемой кривой (для ft_Fillet и ft_OnSurface) \en The initial approximation of parameter of the second curve to be connected (for ft_Fillet and ft_OnSurface) 
  double        param1;   ///< \ru Параметр точки стыковки первой скругляемой кривой (кроме ft_Double) \en Connection point parameter of the first curve (except ft_Double) 
  double        param2;   ///< \ru Параметр точки стыковки второй скругляемой кривой (кроме ft_Double) \en Connection point parameter of the second curve (except ft_Double) 
  double        radius1;  ///< \ru Исходное приближение радиуса (кроме ft_Bridge, для ft_Double - радиус скругления первого участка, для ft_Spline - tension) \en The initial approximation of radius (except ft_Bridge, for ft_Double - the first segment fillet radius, for ft_Spline - tension) 
  double        radius2;  ///< \ru Результат расчета радиуса    (кроме ft_Bridge, для ft_Double - радиус скругления второго участка, для ft_Spline - tension) \en The radius calculation result (except ft_Bridge, for ft_Double - the second segment fillet radius, for ft_Spline - tension) 
  bool          sense1;   ///< \ru Совпадение направления кривой скругления и первой кривой (кроме ft_Spline, для ft_Double - начало/конец кривой) \en Coincidence of the connecting curve direction and the first curve (except ft_Spline, for ft_Double - start/end point of the curve) 
  bool          sense2;   ///< \ru Совпадение направления кривой скругления и второй кривой (кроме ft_Spline, для ft_Double - начало/конец кривой) \en Coincidence of the connecting curve direction and the second curve (except ft_Spline, for ft_Double - start/end point of the curve) 
  MbeMatingType mating1;  ///< \ru Тип сопряжения с первой кривой  (для ft_Spline) \en Type of mating with the first curve (for ft_Spline) 
  MbeMatingType mating2;  ///< \ru Тип сопряжения со второй кривой (для ft_Spline) \en Type of mating with the second curve (for ft_Spline) 
  MbeConnectingType type; ///< \ru Тип скругления (обычное или на поверхности) \en Connection type (ordinary or on a surface) 

protected:
  MbConnectingCurveCreator( const MbConnectingCurveCreator & , MbRegDuplicate * iReg ); // \ru Конструктор копирования \en Copy-constructor 
  MbConnectingCurveCreator( const MbConnectingCurveCreator & ); // \ru Не реализовано \en Not implemented 
  MbConnectingCurveCreator(); // \ru Не реализовано \en Not implemented 

public:
  MbConnectingCurveCreator( const MbSNameMaker & n, 
                            const MbCurve3D & c1, double t1, double p1, double r1, bool s1, MbeMatingType m1,
                            const MbCurve3D & c2, double t2, double p2, double r2, bool s2, MbeMatingType m2, MbeConnectingType t ); 

public :
  virtual ~MbConnectingCurveCreator();

  // \ru Общие функции строителя \en The common functions of the creator 
  virtual MbeCreatorType IsA() const; // \ru Тип элемента \en A type of element 
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

  // \ru Построить кривую по журналу построения \en Create a curve from the history tree 
  virtual bool        CreateSpaceCurve( MbWireFrame *&, MbeCopyMode, RPArray<MbSpaceItem> * items = NULL );

  /** \} */

private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation, to prevent an assignment by default. 
          void        operator = ( const MbConnectingCurveCreator & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbConnectingCurveCreator )
};

IMPL_PERSISTENT_OPS( MbConnectingCurveCreator )

//------------------------------------------------------------------------------
/** \brief \ru Создание строителя скругления двух кривых.
           \en Create two curves fillet constructor. \~
  \details \ru Создание строителя скругления двух кривых.\n
           \en Create two curves fillet constructor.\n \~
  \param[in] curve1 - \ru Кривая 1.
                      \en Curve 1. \~
  \param[in] curve2 - \ru Кривая 2.
                      \en Curve 2. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Curve3D_Modeling
*/
// ---
MATH_FUNC (MbCreator *) CreateFilletEdge( const MbCurve3D & curve1, double & t1, 
                                          const MbCurve3D & curve2, double & t2, 
                                          double & radius, bool sense, 
                                          MbeConnectingType type, 
                                          const MbSNameMaker & names,  
                                          MbResultType & res, 
                                          bool & unchanged,               // \ru Для ft_Fillet и ft_OnSurface \en For ft_Fillet and ft_OnSurface 
                                          MbElementarySurface *& surface, // \ru Для ft_Fillet и ft_OnSurface \en For ft_Fillet and ft_OnSurface 
                                          MbEdge *& edge ); 


//------------------------------------------------------------------------------
/** \brief \ru Создание строителя сопряжения двух кривых сплайном.
           \en Create constructor of two curves connection by a spline. \~
  \details \ru Создание строителя сопряжения двух кривых сплайном.\n
           \en Create constructor of two curves connection by a spline.\n \~
  \param[in] curve1 - \ru Кривая 1.
                      \en Curve 1. \~
  \param[in] curve2 - \ru Кривая 2.
                      \en Curve 2. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Curve3D_Modeling
*/
// ---
MATH_FUNC (MbCreator *) CreateSplineEdge( const MbCurve3D & curve1, double t1, MbeMatingType mating1,
                                          const MbCurve3D & curve2, double t2, MbeMatingType mating2,
                                          double tension1, double tension2,
                                          const MbSNameMaker & names,  
                                          MbResultType & res, 
                                          MbEdge *& edge ); 


//------------------------------------------------------------------------------
/** \brief \ru Создание строителя сопряжения концов двух кривых составной кривой плавного соединения.
           \en Create a constructor of conjugation of two curves end points by a composite curve of smooth connection. \~
  \details \ru Создание строителя сопряжения концов двух кривых составной кривой плавного соединения.\n
           \en Create a constructor of conjugation of two curves end points by a composite curve of smooth connection.\n \~
  \param[in] curve1 - \ru Кривая 1.
                      \en Curve 1. \~
  \param[in] curve2 - \ru Кривая 2.
                      \en Curve 2. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Curve3D_Modeling
*/
// ---
MATH_FUNC (MbCreator *) CreateConnectingEdge( const MbCurve3D & curve1, bool isBegin1, double radius1, 
                                              const MbCurve3D & curve2, bool isBegin2, double radius2, 
                                              const MbSNameMaker & names,  
                                              MbResultType & res, 
                                              MbEdge *& edge ); 


//------------------------------------------------------------------------------
/** \brief \ru Cоздание строителя сопряжения двух кривых кубическим сплайном Эрмита (кривой-мостиком).
           \en Create a constructor of two curves conjugation by a cubic Hermite spline (transition curve). \~
  \details \ru Cоздание строителя сопряжения двух кривых кубическим сплайном Эрмита (кривой-мостиком).\n
           \en Create a constructor of two curves conjugation by a cubic Hermite spline (transition curve).\n \~
  \param[in] curve1 - \ru Кривая 1.
                      \en Curve 1. \~
  \param[in] curve2 - \ru Кривая 2.
                      \en Curve 2. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Curve3D_Modeling
*/
// ---
MATH_FUNC (MbCreator *) CreateBridgeEdge( const MbCurve3D & curve1, double t1, bool sense1, 
                                          const MbCurve3D & curve2, double t2, bool sense2, 
                                          const MbSNameMaker & names,  
                                          MbResultType & res, 
                                          MbEdge *& edge ); 


#endif  // __CR_CONNECTING_CURVE_H