////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель оболочки из листового материала штамповкой телом-инструментом.
         \en Constructor of a shell from the sheet material with stamping by a tool solid.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_USERSTAMP_SOLID_H
#define __CR_USERSTAMP_SOLID_H


#include <creator.h>
#include <sheet_metal_param.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки из листового материала штамповкой телом-инструментом.
           \en Constructor of a shell from the sheet material with stamping by tool solid. \~
  \details \ru Строитель оболочки из листового материала закрытой или открытой штамповкой телом-инструментом.
    Тело-инструмент может являться пуансоном или матрицей.\n 
    Строятся штамповки двух типов: \n 
    закрытая - не указаны вскрываемые грани тела-инструмента, \n 
    открытая - когда лист пробит штамповкой насквозь, указаны вскрываемые грани. \n
           \en Constructor of a shell from the sheet material by open or closed stamping by tool solid. 
    The tool solid may be a punch or a die. \n 
    Stamping of two types are constructed: \n 
    closed - pierce faces of tool solid are not specified, \n 
    open - when a sheet is punched through by stamping, pierce faces of tool solid are specified. \n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbUserStampSolid : public MbCreator {
private:
  MbItemIndex          faceIndex;     ///< \ru Индекс грани, на которой строится штамповка. \en Index of the face the stamping is constructed on. 
  MbItemIndex          pairFaceIndex; ///< \ru Индекс грани парной к грани штамповки. \en Index of the face which is pair to the stamp face.
  RPArray<MbCreator>   creators;      ///< \ru Журнал построения оболочки тела-инструмента. \en History tree of the shell of the tool solid.
  size_t               countOne;      ///< \ru Разделитель строителей тел-операндов. \en Separator of operand solids creators. 
  MbUserStampingValues parameters;    ///< \ru Параметры штамповки. \en Stamping parameters. 
  double               thickness;     ///< \ru Толщина листа. \en The thickness of the sheet metal.
  bool                 punch;         ///< \ru Является тело-инструмент пуансоном или матрицей? \en Is tool body a punch or a die.

public :
  MbUserStampSolid( const RPArray<MbCreator> &    creatorsTool,
                    const bool                    sameTool,
                    const MbItemIndex &           faceIndex,
                    const MbItemIndex &           pairFaceIndex,
                    const MbUserStampingValues &  params,
                    const double                  thickness,
                    const bool                    isPunch,
                    const MbSNameMaker &          names );
private:
  MbUserStampSolid( const MbUserStampSolid &, MbRegDuplicate * iReg );

public:
  virtual ~MbUserStampSolid();

  // \ru Общие функции математического объекта. \en Common functions of the mathematical object.

  virtual MbeCreatorType  IsA()  const; // \ru Тип элемента. \en A type of element.
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию. \en Create a copy.

  virtual bool        IsSame   ( const MbCreator & other, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & item ) const; // \ru Являются ли объекты подобными? \en Determine whether an object is similar?
  virtual bool        SetEqual ( const MbCreator & ); // \ru Сделать равным. \en Make equal.

  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix.
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг. \en Translation.
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis.

  virtual void        GetProperties  ( MbProperties &properties ); // \ru Выдать свойства объекта. \en Get properties of the object.
  virtual void        SetProperties  ( const MbProperties &properties ); // \ru Записать свойства объекта. \en Set properties of the object.
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property.

  // \ru Общие функции твердого тела. \en Common functions of solid.

  virtual bool        CreateShell( MbFaceShell *&shell, MbeCopyMode sameShell, 
                                   RPArray <MbSpaceItem> *items = NULL ); // \ru Построение оболочки штамповки. \en Construction of a stamping shell.

          // \ru Получить параметры. \en Get the parameters. 
          void        GetParameters( MbUserStampingValues & params ) const { params = parameters; }
          // \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const MbUserStampingValues & params ) { parameters = params; }

private:
  OBVIOUS_PRIVATE_COPY( MbUserStampSolid )
  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbUserStampSolid )
};

IMPL_PERSISTENT_OPS( MbUserStampSolid )


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку из листового материала штамповкой телом-инструментом.
           \en Construct a shell form sheet material by tool body stamping. \~
  \details \ru На базе исходной оболочки из листового материала построить оболочку методом закрытой или открытой штамповки. \n
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en A shell is to be constructed on the basis of the source shell by the method of closed or open stamping. \n
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  solid        - \ru Исходная оболочка.
                             \en The source shell. \~
  \param[in]  sameShell    - \ru Режим копирования исходной оболочки.
                             \en Mode of copying the source shell. \~
  \param[in]  face         - \ru Грань штамповки.
                             \en The face for stamping. \~
  \param[in] toolSolid     - \ru Оболочка тела-инструмента.
                             \en A shell of tool solid. \~
  \param[in] sameShellTool - \ru Режим копирования оболочки тела-инструмента.
                             \en Mode of copying the tool shell. \~
  \param[in] punch         - \ru Является тело-инструмент пуансоном или матрицей.
                             \en Is tool body a punch or a die. \~
  \param[in] pierceFaces   - \ru Вскрываемые для вырубки грани инструмента,
                             \en Pierce faces of tool body. \~
  \param[in] params        - \ru Параметры штамповки.
                             \en The parameters of stamping. \~
  \param[in] nameMaker     - \ru Именователь.
                             \en An object for naming the new objects. \~
  \param[out] result       - \ru Результирующее тело.
                             \en The resultant solid. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateUserStamp(       MbFaceShell &          initialShell,  // Исходная оболочка,
                                         const MbeCopyMode            sameShell,     // флаг способа использования исходной оболочки,
                                         const MbFace &               targetFace,    // грань штамповки,
                                         const RPArray<MbCreator> &   creatorsTool,  // журнал построения инструмента,
                                               MbFaceShell &          toolShell,     // оболочка тела-инструмента,
                                         const MbeCopyMode            sameShellTool, // флаг способа использования оболочки инструмента,
                                               bool                   isPunch,       // является инструмент пуансоном или матрицей,
                                         const RPArray<MbFace> &      pierceFaces,   // вскрываемые для вырубки грани инструмента,
                                         const MbUserStampingValues & params,        // параметры штамповки,
                                         const MbSNameMaker &         nameMaker,     // именователь,
                                               MbResultType &         res,           // флаг успешности операции,
                                               SPtr<MbFaceShell> &    resultShell ); // результирующая оболочка.


#endif // __CR_USERSTAMP_SOLID_H
