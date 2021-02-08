////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель эквидистантной кривой.
         \en Offset curve constructor.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_OFFSET_CURVE_H
#define __CR_OFFSET_CURVE_H


#include <creator.h>
#include <templ_sptr.h>
#include <vector>


class MATH_CLASS  MbCurve3D;


//------------------------------------------------------------------------------
/** \brief \ru Строитель эквидистантной кривой.
           \en Offset curve constructor. \~
  \details \ru Строитель эквидистантной кривой.\n
           \en Offset curve constructor.\n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbOffsetCurveCreator : public MbCreator {
private:
  // \ru Основные параметры \en The basic parameters 
  SPtr<MbCurve3D>     curve;          // \ru Исходная кривая. \en The initial curve. 
  MbVector3D          dir;            // \ru Направление смещения. \en The offset direction. 
  double              dist;           // \ru Величина смещения. \en The offset distance. 
  bool                fromBeg;        // \ru Вектор смещения привязан к началу кривой (иначе к концу). \en The translation vector is associated with the beginning (with the end otherwise). 

  // \ru Дополнительные параметры (эквидистанта в пространстве) \en Auxiliary parameters (spatial offset) 
  bool                useFillet;      // \ru Заполнять ли разрывы скруглениями (иначе продлять сегменты). \en Whether to fill the gaps with fillets (extend segments otherwise). 
  bool                keepRadius;     // \ru Сохранять ли радиусы в скруглениях. \en Whether to keep the radii at fillets. 
  bool                bluntAngle;     // \ru Притуплять острые углы стыков сегментов \en Whether to blunt the sharp edges of segments joints. 

  // \ru Дополнительные параметры (эквидистанта на поверхности грани оболочки) \en Auxiliary parameters (offset on the shell face surface) 
  c3d::CreatorsSPtrVector  shellCreators;  // \ru Журнал построения оболочки. \en The shell history tree. 

protected:
  MbOffsetCurveCreator( const MbOffsetCurveCreator &, MbRegDuplicate * iReg ); // \ru Конструктор копирования \en Copy-constructor 
  MbOffsetCurveCreator( const MbOffsetCurveCreator & ); // \ru Не реализовано \en Not implemented 
  MbOffsetCurveCreator(); // \ru Не реализовано \en Not implemented 
public:
  // \ru Конструктор эквидистанты в пространстве \en Constructor of offset in the space 
  MbOffsetCurveCreator( const MbCurve3D &, bool fromBeg, const MbVector3D & dir, double dist,
                        bool useFillet, bool keepRadius, bool bluntAngle,
                        const MbSNameMaker & snMaker );
  // \ru Конструктор эквидистанты на поверхности грани оболочки \en Constructor of offset on the shell face surface 
  MbOffsetCurveCreator( const MbCurve3D &, bool fromBeg, const MbVector3D & dir, double dist,
                        const RPArray<MbCreator> & shellCreators, bool sameCreators,
                        const MbSNameMaker & snMaker );
public :
  virtual ~MbOffsetCurveCreator();

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
          void        operator = ( const MbOffsetCurveCreator & ); // \ru Не реализовано!!! \en Not implemented!!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbOffsetCurveCreator )
};

IMPL_PERSISTENT_OPS( MbOffsetCurveCreator )

//------------------------------------------------------------------------------
/** \brief \ru Создать офсетную кривую по трехмерной кривой и вектору направления.
           \en Create an offset curve from three-dimensional curve and direction. \~
  \details \ru Создать офсетную кривую по трехмерной кривой и вектору направления. \n
           \en Create an offset curve from three-dimensional curve and direction. \n \~
  \param[in] initCurve - \ru Постранственная кривая, к которой строится эквидистантная.
                         \en A space curve for which to construct the offset curve. \~
  \param[in] offsetVect - \ru Вектор, задающий смещение в точке кривой.
                          \en The displacement vector at a point of the curve. \~
  \param[in] useFillet - \ru Если true, то разрывы заполнять скруглением, иначе продолженными кривыми.
                         \en If 'true', the gaps are to be filled with fillet, otherwise with the extended curves. \~
  \param[in] keepRadius - \ru Если true, то в существующих скруглениях сохранять радиусы.
                          \en If 'true', the existent fillet radii are to be kept. \~
  \param[in] fromBeg - \ru Вектор смещения привязан к началу.
                       \en The translation vector is associated with the beginning. \~
  \param[in] snMaker  - \ru Именователь кривых каркаса.
                        \en An object defining the frame curves names. \~
  \param[out] resType - \ru Код результата операции
                        \en Operation result code \~
  \param[out] resCurve - \ru Эквидистантная кривая.
                         \en The offset curve. \~
  \return \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Curve3D_Modeling
*/
//---
MATH_FUNC (MbCreator *) CreateOffsetCurve( const MbCurve3D &    initCurve, 
                                           const MbVector3D &   offsetVect,
                                           const bool           useFillet,
                                           const bool           keepRadius,
                                           const bool           bluntAngle,
                                           const bool           fromBeg, 
                                           const MbSNameMaker & snMaker,
                                                 MbResultType & resType,
                                                 MbCurve3D *&   resCurve );


//------------------------------------------------------------------------------
/** \brief \ru Создать офсетную кривую по поверхностной кривой и значению смещения.
           \en Create an offset curve from a spatial curve and offset value. \~
  \details \ru Создать офсетную кривую по поверхностной кривой и значению смещения. \n
           \en Create an offset curve from a spatial curve and offset value. \n \~
  \param[in] curve - \ru Кривая на поверхности грани face.
                     \en A curve on face 'face' surface. \~
  \param[in] face - \ru Грань, на которой строится эквидистанта.
                    \en The edge on which to build the offset curve. \~
  \param[in] dirAxis - \ru Направление смещения с точкой приложения.
                       \en The offset direction with a point of application. \~
  \param[in] dist - \ru Величина смещения.
                    \en The offset distance. \~
  \param[in] snMaker  - \ru Именователь кривых каркаса.
                        \en An object defining the frame curves names. \~
  \param[out] resType - \ru Код результата операции
                        \en Operation result code \~
  \param[out] resCurves - \ru Множество эквидистантных кривых.
                          \en Offset curve array. \~
  \return \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Curve3D_Modeling
*/
//---
MATH_FUNC (MbCreator *) CreateOffsetCurve( const MbCurve3D &          curve, 
                                           const MbFace &             face,
                                           const MbAxis3D &           dirAxis,
                                                 double               dist,
                                           const MbSNameMaker &       snMaker,
                                                 MbResultType &       resType,
                                                 RPArray<MbCurve3D> & resCurves );


#endif // __CR_OFFSET_CURVE_H
