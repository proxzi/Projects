////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель оболочки из листового материала штамповкой.
         \en Constructor of a shell from the sheet material with stamping.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_STAMP_SOLID_H
#define __CR_STAMP_SOLID_H


#include <cur_contour.h>
#include <mb_placement3d.h>
#include <creator.h>
#include <sheet_metal_param.h>


class  MATH_CLASS  MbCurveBoundedSurface;


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки из листового материала штамповкой.
           \en Constructor of a shell from the sheet material with stamping. \~
  \details \ru Строитель оболочки из листового материала закрытой или открытой штамповкой. \n 
    Строятся штамповки двух типов: \n 
    закрытая - донышко штамповки закрыто листовым материалом, \n 
    открытая - когда лист пробит штамповкой насквозь. \n
           \en Constructor of a shell from the sheet material by open or closed stamping. \n 
    Stamping of two types are constructed: \n 
    closed - bottom of stamping is closed by a sheet material, \n 
    open - when a sheet is punched through by stamping. \n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbStampSolid : public MbCreator {
private:
  MbItemIndex             faceIndex;     ///< \ru Индекс грани, на которой строится штамповка. \en Index of the face the stamping is constructed on. 
  MbItemIndex             pairFaceIndex; ///< \ru Индекс грани парной к грани штамповки. \en Index of the face which is pair to the stamp face.
  MbCurveBoundedSurface * boundSurface;  ///< \ru Поверхность, границами которой надо подрезать штамповку. \en Surface, by which bounds the stamp is cutted.
  MbPlacement3D           placement;     ///< \ru Локальная система координат контура штамповки. \en The local coordinate system of contour of stamping. 
  MbContour               contour;       ///< \ru Контур донышка штамповки. \en Stamping bottom contour. 
  MbStampingValues        parameters;    ///< \ru Параметры штамповки. \en Stamping parameters. 
  double                  thickness;     ///< \ru Толщина листа. \en The thickness of the sheet metal.
  bool                    add;           ///< \ru Создавать добавляемую или вычитаемую часть штамповки. \en Create additional or subtructional part of a stamp.

public :
  MbStampSolid( const MbItemIndex &           faceIndex,
                const MbItemIndex &           pairFaceIndex,
                const MbCurveBoundedSurface * boundSurface,
                const MbPlacement3D &         placement,
                const MbContour &             contour,
                const MbStampingValues &      params,
                const double                  thickness,
                const bool                    add,
                const MbSNameMaker &          names );
private:
  MbStampSolid( const MbStampSolid &, MbRegDuplicate * iReg );
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbStampSolid( const MbStampSolid & );

public:
  virtual ~MbStampSolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA()  const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 

  virtual bool        IsSame   ( const MbCreator & other, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & item ) const; // \ru Являются ли объекты подобными? \en Determine whether an object is similar?
  virtual bool        SetEqual ( const MbCreator & ); // \ru Сделать равным \en Make equal 

  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void        GetProperties  ( MbProperties &properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties  ( const MbProperties &properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem>   & ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции твердого тела \en Common functions of solid  

  virtual bool        CreateShell( MbFaceShell *&shell, MbeCopyMode sameShell, 
                                   RPArray <MbSpaceItem> *items = NULL ); // \ru Построение \en Construction 

          // \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       MbStampingValues & params ) const { params = parameters; }
          // \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const MbStampingValues & params )       { parameters = params; }

private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
  MbStampSolid  &     operator = ( const MbStampSolid & ); // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbStampSolid )
};

IMPL_PERSISTENT_OPS( MbStampSolid )

//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку из листового материала штамповкой.
           \en Construct a shell form sheet material by stamping. \~
  \details \ru На базе исходной оболочки из листового материала построить оболочку методом закрытой или открытой штамповкой. \n
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en A shell is to be constructed on the basis of the source shell by the method of closed or open stamping. \n
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  solid      - \ru Исходная оболочка.
                           \en The source shell. \~
  \param[in]  sameShell  - \ru Режим копирования исходной оболочки.
                           \en Mode of copying the source shell. \~
  \param[in]  face       - \ru Грань штамповки.
                           \en The face for stamping. \~
  \param[in]  placement  - \ru Локальная система координат, в плоскости XY которй расположен контур штамповки.
                           \en The local coordinate system in the XY plane of which the stamping contour is located. \~
  \param[in]  contour    - \ru Контур штамповки.
                           \en The stamping contour. \~
  \param[in]  parameters - \ru Параметры штамповки.
                           \en The parameters of stamping. \~
  \param[in]  operNames  - \ru Именователь операции.
                           \en An object defining names generation in the operation. \~
  \param[out] res        - \ru Код результата операции выдавливания.
                           \en The extrusion operation result code. \~
  \param[out] shell      - \ru Построенная оболочка.
                           \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateStamp(       MbFaceShell *       initialShell,   // исходная оболочка
                                     const MbeCopyMode         sameShell,      // флаг способа использования исходной оболочки
                                     const MbFace *            face,           // грань штамповки
                                     const MbPlacement3D &     placement,      // локальная система координат контура
                                     const MbContour &         contour,        // контур штамповки
                                     const MbStampingValues &  params,         // параметры штамповки
                                     const double              thickness,      // толщина листа
                                     const bool                add,            // создать добавляемую часть
                                           MbSNameMaker &      nameMaker,      // именователь
                                           MbResultType &      res,            // флаг успешности операции
                                           SPtr<MbFaceShell> & resultShell );  // результирующая оболочка


#endif // __CR_STAMP_SOLID_H
