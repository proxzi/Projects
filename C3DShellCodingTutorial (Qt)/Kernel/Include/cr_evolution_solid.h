////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель оболочки кинематическо тела.
         \en Constructor of shell of evolution solid. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_EVOLUTION_SOLID_H
#define __CR_EVOLUTION_SOLID_H


#include <surf_spine.h>
#include <cr_swept_solid.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки кинематическо тела.
           \en Constructor of shell of evolution solid. \~
  \details \ru Строитель оболочки тела путём движения образующей кривой по направляющей кривой. \n
           \en Constructor of solid shell by moving generating curve along a spine curve.  \n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbCurveEvolutionSolid : public MbCurveSweptSolid {
protected :
  MbSweptData       sweptData;      ///< \ru Данные об образующей. \en Generating curve data. 
  SPtr<MbCurve3D>   spineCurve;     ///< \ru Направляющая кривая. \en Spine curve. 
  SPtr<MbCurve3D>   directionCurve; ///< \ru Кривая векторa ориентации матрицы преобразования (может быть NULL для простой траектории). \en A curve of the transformation matrix orientation (it may be NULL for a simple trajectory). 
  MbVector3D        direction;      ///< \ru Вектор ориентации матрицы преобразования (может быть нулевой, в случае автопределения). \en Vector of transformation matrix orientation (it's equal zero in the mode of automatic direction calculation). 
  MbSNameMaker      spineNames;     ///< \ru Именователь направляющей. \en An object defining the name of the spine curve. 
  EvolutionValues   parameters;     ///< \ru Параметры. \en Parameters. 

public :
  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по одному контуру на поверхности.
             \en Constructor by one contour on a surface. \~
    \param[in] surface_     - \ru Поверхность образующей.
                              \en Surface of a generating curve. \~
    \param[in] contour_     - \ru Контур в параметрах поверхности.
                              \en Contour in surface parameters domain. \~
    \param[in] spine_       - \ru Направляющая кривая.
                              \en The spine curve. \~
    \param[in] params       - \ru Параметры кинематической операции.
                              \en Parameters of the sweeping operation. \~
    \param[in] oType        - \ru Тип булевой операции с предыдущим результатом.
                              \en Type of Boolean operation with the previous result. \~
    \param[in] operNames    - \ru Именователь операции.
                              \en An object defining names generation in the operation. \~
    \param[in] contourNames - \ru Имена контуров образующей для именования граней.
                              \en Generatix contours' names for naming faces. \~
    \param[in] spineNames   - \ru Имена направляющей.
                              \en Generating curve names. \~
  */
  MbCurveEvolutionSolid( const MbSurface &       surface_,
                         const MbContour &       contour_,
                         const MbCurve3D &       spine_,
                         const EvolutionValues & params,
                               OperationType     oType,
                         const MbSNameMaker &    operNames,
                         const MbSNameMaker &    contourNames,
                         const MbSNameMaker &    spineNames_ );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по смешанной образующей.
             \en Constructor by combined generating curve. \~
    \param[in] sweptData_   - \ru Образующая.
                              \en Generating curve. \~
    \param[in] spine_       - \ru Направляющая кривая.
                              \en The spine curve. \~
    \param[in] params       - \ru Параметры кинематической операции.
                              \en Parameters of the sweeping operation. \~
    \param[in] oType        - \ru Тип булевой операции с предыдущим результатом.
                              \en Type of Boolean operation with the previous result. \~
    \param[in] operNames    - \ru Именователь операции.
                              \en An object defining names generation in the operation. \~
    \param[in] contourNames - \ru Имена контуров образующей для именования граней.
                              \en Generatix contours' names for naming faces. \~
    \param[in] spineNames   - \ru Имена направляющей.
                              \en Generating curve names. \~
  */
  MbCurveEvolutionSolid( const MbSweptData &           sweptData_,
                         const MbCurve3D &             spine_,
                         const EvolutionValues &       params,
                               OperationType           oType,
                         const MbSNameMaker &          operNames,
                         const RPArray<MbSNameMaker> & contoursNames,
                         const MbSNameMaker &          spineNames_ );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по смешанной образующей.
             \en Constructor by combined generating curve. \~
    \param[in] sweptData_   - \ru Образующая.
                              \en Generating curve. \~
    \param[in] spine_       - \ru Направляющая кривая.
                              \en The spine curve. \~
    \param[in] params       - \ru Параметры кинематической операции.
                              \en Parameters of the sweeping operation. \~
    \param[in] oType        - \ru Тип булевой операции с предыдущим результатом.
                              \en Type of Boolean operation with the previous result. \~
    \param[in] operNames    - \ru Именователь операции.
                              \en An object defining names generation in the operation. \~
    \param[in] contourNames - \ru Имена контуров образующей для именования граней.
                              \en Generatix contours' names for naming faces. \~
    \param[in] spineNames   - \ru Имена направляющей.
                              \en Generating curve names. \~
  */
  MbCurveEvolutionSolid( const MbSweptData &           sweptData_,
                         const MbSpine &               spine_,
                         const EvolutionValues &       params,
                               OperationType           oType,
                         const MbSNameMaker &          operNames,
                         const RPArray<MbSNameMaker> & contoursNames,
                         const MbSNameMaker &          spineNames_ );

private :
  MbCurveEvolutionSolid( const MbCurveEvolutionSolid & init, MbRegDuplicate * ireg );
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbCurveEvolutionSolid( const MbCurveEvolutionSolid & ); 
public :
  virtual ~MbCurveEvolutionSolid();

  /** \ru \name Общие функции математического объекта.
      \en \name Common functions of the mathematical object.
      \{ */
  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию \en Create a copy 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );             // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL );             // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem>   & s ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );       // \ru Сделать равным \en Make equal 
  
  /** \} */
  /** \ru \name Общие функции твердого тела (формообразующей операции).
      \en \name Common functions of the rigid solid (forming operations).
      \{ */
  virtual MbFaceShell * InitShell( bool in ); 
  virtual void        InitBasis( RPArray<MbSpaceItem> & items ); 
  virtual bool        GetPlacement( MbPlacement3D & p ) const;
  virtual void        SetYourVersion( VERSION version, bool forAll );
  /** \} */
  /** \ru \name Функции строителя оболочки кинематического тела.
      \en \name Functions of creator of evolution solid shell.
      \{ */
          /// \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       EvolutionValues & params ) const { params = parameters; }
          /// \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const EvolutionValues & params )       { parameters = params; }
  /** \} */

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbCurveEvolutionSolid & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCurveEvolutionSolid )
}; // MbCurveEvolutionSolid

IMPL_PERSISTENT_OPS( MbCurveEvolutionSolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку кинематического тела.
           \en Create a shell of evolution solid. \~
  \details \ru Построить оболочку путём движения образующей кривой по направляющей кривой
    и выполнить булуву операцию с оболочкой, если последняя задана. \n
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Create a shell by moving the generating curve along the spine curve
    and perform the Boolean operation with the shell if it is specified. \n
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  solid         - \ru Набор граней, к которым дополняется построение.
                              \en Face set the construction is complemented with respect to. \~
  \param[in]  sameShell     - \ru Способ копирования граней.
                              \en The method of copying faces. \~
  \param[in]  sweptData     - \ru Данные об образующей.
                              \en The generating curve data. \~
  \param[in]  spine         - \ru Направляющая кривая.
                              \en The spine curve. \~
  \param[in]  params        - \ru Параметры кинематической операции.
                              \en Parameters of the sweeping operation. \~
  \param[in]  oType         - \ru Тип операции дополнения построения.
                              \en Type of operation of construction complement. \~
  \param[in]  operNames     - \ru Именователь с версией для булевой с исходным телом.
                              \en Name-maker with version for a Boolean operation with the source solid. \~
  \param[in]  contoursNames - \ru Имена образующей.
                              \en Names of the generating curve. \~
  \param[in]  spineNames    - \ru Имена пути.
                              \en Names of the path. \~
  \param[out] res           - \ru Код результата операции.
                              \en Operation result code. \~
  \param[out] shell         - \ru Построенный набор граней.
                              \en Constructed set of faces. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateCurveEvolution(       MbFaceShell *           solid,
                                                    MbeCopyMode             sameShell,
                                              const MbSweptData &           sweptData,
                                              const MbCurve3D &             spine,
                                              const EvolutionValues &       params,
                                                    OperationType           oType,
                                              const MbSNameMaker &          operNames,
                                              const RPArray<MbSNameMaker> & contoursNames, 
                                              const MbSNameMaker &          spineNames,
                                                    MbResultType &          res,
                                                    MbFaceShell *&          shell );

//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку кинематического тела.
           \en Create a shell of evolution solid. \~
  \details \ru Построить оболочку путём движения образующей кривой по направляющей кривой
    и выполнить булуву операцию с оболочкой, если последняя задана. \n
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Create a shell by moving the generating curve along the spine curve
    and perform the Boolean operation with the shell if it is specified. \n
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  solid         - \ru Набор граней, к которым дополняется построение.
                              \en Face set the construction is complemented with respect to. \~
  \param[in]  sameShell     - \ru Способ копирования граней.
                              \en The method of copying faces. \~
  \param[in]  sweptData     - \ru Данные об образующей.
                              \en The generating curve data. \~
  \param[in]  spine         - \ru Направляющая кривая c дополнительной информацией.
                              \en The spine curve with additional data. \~
  \param[in]  params        - \ru Параметры кинематической операции.
                              \en Parameters of the sweeping operation. \~
  \param[in]  oType         - \ru Тип операции дополнения построения.
                              \en Type of operation of construction complement. \~
  \param[in]  operNames     - \ru Именователь с версией для булевой с исходным телом.
                              \en Name-maker with version for a Boolean operation with the source solid. \~
  \param[in]  contoursNames - \ru Имена образующей.
                              \en Names of the generating curve. \~
  \param[in]  spineNames    - \ru Имена пути.
                              \en Names of the path. \~
  \param[out] res           - \ru Код результата операции.
                              \en Operation result code. \~
  \param[out] shell         - \ru Построенный набор граней.
                              \en Constructed set of faces. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateCurveEvolution(       MbFaceShell *           solid,
                                                    MbeCopyMode             sameShell,
                                              const MbSweptData &           sweptData,
                                              const MbSpine &               spine,
                                              const EvolutionValues &       params,
                                                    OperationType           oType,
                                              const MbSNameMaker &          operNames,
                                              const RPArray<MbSNameMaker> & contoursNames, 
                                              const MbSNameMaker &          spineNames,
                                                    MbResultType &          res,
                                                    MbFaceShell *&          shell );


#endif // __CR_EVOLUTION_SOLID_H
