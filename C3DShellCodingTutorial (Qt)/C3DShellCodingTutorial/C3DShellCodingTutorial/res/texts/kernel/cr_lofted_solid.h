////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель оболочки тела по плоским сечениям.
         \en Constructor of a lofted shell. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_LOFTED_SOLID_H
#define __CR_LOFTED_SOLID_H


#include <cur_contour_on_plane.h>
#include <cr_swept_solid.h>
#include <templ_sptr.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки тела по сечениям.
           \en Constructor of a lofted shell. \~
  \details \ru Строитель оболочки тела, проходящей по заданным сечениям и вдоль заданной осевой линии и направляющих. \n
           \en Constructor of solid's shell passing through the given sections along the specified spine curve and guide curves. \n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbCurveLoftedSolid : public MbCurveSweptSolid {
protected :
  RPArray<MbContourOnSurface> curves;      ///< \ru Плоские сечения. \en Plane sections.
  SPtr<MbCurve3D>             spine;       ///< \ru Осевая линия (может отсутствовать). \en Spine curve (can be absent).
  LoftedValues                parameters;  ///< \ru Параметры. \en Parameters.
  RPArray<MbCurve3D> *        guideCurves; ///< \ru Массив направляющих кривых (может быть NULL). \en An array of guide curves (can be NULL).
  SArray<MbCartPoint3D> *     userPnts;    ///< \ru Пользовательские точки на сечениях. \en Custom points on the sections.

public:
  /// \ru Конструктор. \en Constructor. 
  MbCurveLoftedSolid( const RPArray<MbSurface> &    surfs, 
                      const RPArray<MbContour> &    cntrs,
                      const LoftedValues &          p,
                            OperationType           op,
                      const MbSNameMaker &          n,
                            RPArray<MbSNameMaker> & ns,
                            RPArray<MbCurve3D> *    guideCrvs,
                            SArray<MbCartPoint3D> * userPnts );
  /// \ru Конструктор. \en Constructor. 
  MbCurveLoftedSolid( const MbCurve3D &             s,
                      const RPArray<MbSurface> &    surfs, 
                      const RPArray<MbContour> &    cntrs,
                      const LoftedValues &          p,
                            OperationType           op,
                      const MbSNameMaker &          n,
                            RPArray<MbSNameMaker> & ns,
                            RPArray<MbCurve3D> *    guideCrvs,
                            SArray<MbCartPoint3D> * userPnts );

private :
  MbCurveLoftedSolid( const MbCurveLoftedSolid & init, MbRegDuplicate * ireg );
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbCurveLoftedSolid( const MbCurveLoftedSolid & init );

public :
  virtual ~MbCurveLoftedSolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию \en Create a copy 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );             // \ru Преобразовать \en Transform 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL );             // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );       // \ru Сделать равным \en Make equal 

  // \ru Общие функции твердого тела \en Common functions of solid  

  virtual MbFaceShell * InitShell( bool /*in*/ ); 
  virtual void        InitBasis( RPArray<MbSpaceItem> & items ); 
  virtual bool        GetPlacement( MbPlacement3D & ) const;

          /// \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       LoftedValues & params ) const { params = parameters; }
          /// \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const LoftedValues & params )       { parameters = params; }
          /// \ru Направляющая кривая. \en The spine curve. 
  const   MbCurve3D * GetSpine() const { return spine.get(); }

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbCurveLoftedSolid & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCurveLoftedSolid )
};

IMPL_PERSISTENT_OPS( MbCurveLoftedSolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать тело по плоским сечениям.
           \en Create a solid from a planar sections. \~
  \details \ru Построить оболочку тела, проходящую по заданным сечениям
               и выполнить булеву операцию с оболочкой, если последняя задана. \n
               Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Create a solid's shell passing through the given sections
               and perform the Boolean operation with the shell if it is specified. \n
               The function simultaneously creates the shell and its constructor.\n \~ 
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateCurveLofted(       MbFaceShell *           solid,
                                                 MbeCopyMode             sameShell,
                                                 SArray<MbPlacement3D> & pl,
                                                 RPArray<MbContour> &    c,
                                           const LoftedValues &          p,
                                                 OperationType           oType,
                                           const MbSNameMaker &          operNames,
                                                 RPArray<MbSNameMaker> & ns,
                                                 SArray<MbCartPoint3D> * ps,
                                                 MbResultType &          res,
                                                 MbFaceShell *&          shell );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по пространственным сечениям.
           \en Create a solid from sections on surfaces. \~
  \details \ru Построить оболочку тела, проходящую по заданным сечениям
               и выполнить булеву операцию с оболочкой, если последняя задана. \n
               Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Create a solid's shell passing through the given sections
               and perform the Boolean operation with the shell if it is specified. \n
               The function simultaneously creates the shell and its constructor.\n \~ 
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateCurveLofted(       MbFaceShell *           solid,
                                                 MbeCopyMode             sameShell,
                                                 RPArray<MbSurface> &    surfs,
                                                 RPArray<MbContour> &    c,
                                           const LoftedValues &          p,
                                                 OperationType           oType,
                                           const MbSNameMaker &          operNames,
                                                 RPArray<MbSNameMaker> & ns,
                                                 RPArray<MbCurve3D> *    guideCurves,
                                                 SArray<MbCartPoint3D> * ps,
                                                 MbResultType &          res,
                                                 MbFaceShell *&          shell );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по плоским сечениям.
           \en Create a solid from a planar sections. \~
  \details \ru Построить оболочку тела, проходящую по заданным сечениям вдоль заданной направляющей
               и выполнить булеву операцию с оболочкой, если последняя задана. \n
               Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Create a solid's shell passing through the given sections along the specified spine curve
               and perform the Boolean operation with the shell if it is specified. \n
               The function simultaneously creates the shell and its constructor.\n \~ 
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateCurveLofted(       MbFaceShell *           solid,
                                                 MbeCopyMode             _sameShell,
                                                 SArray<MbPlacement3D> & pl,
                                                 RPArray<MbContour> &    c,
                                           const MbCurve3D &             centre_line,
                                           const LoftedValues &          p,
                                                 OperationType           oType,
                                           const MbSNameMaker &          operNames,
                                                 RPArray<MbSNameMaker> & ns,
                                                 SArray<MbCartPoint3D> * ps,
                                                 MbResultType &          res,
                                                 MbFaceShell *&          shell );


//------------------------------------------------------------------------------
/** \brief \ru Создать тело по пространственным сечениям.
           \en Create a solid from a space sections. \~
  \details \ru Построить оболочку тела, проходящую по заданным сечениям вдоль заданной осевой линии и направляющих
               и выполнить булеву операцию с оболочкой, если последняя задана. \n
               Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Create a solid's shell passing through the given sections along the specified spine curve and guide curves
               and perform the Boolean operation with the shell if it is specified. \n
               The function simultaneously creates the shell and its constructor.\n \~ 
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateCurveLofted(       MbFaceShell *           solid,
                                                 MbeCopyMode             _sameShell,
                                                 RPArray<MbSurface> &    surfs,
                                                 RPArray<MbContour> &    c,
                                           const MbCurve3D &             centre_line,
                                           const LoftedValues &          p,
                                                 OperationType           oType,
                                           const MbSNameMaker &          operNames,
                                                 RPArray<MbSNameMaker> & ns,
                                                 RPArray<MbCurve3D> *    guideCurves,
                                                 SArray<MbCartPoint3D> * ps,
                                                 MbResultType &          res,
                                                 MbFaceShell *&          shell );


#endif // __CR_LOFTED_SOLID_H
