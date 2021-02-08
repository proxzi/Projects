////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение срединной оболочки между гранями тела.
         \en Construction of a median shell between faces of solid. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_MEDIAN_SHELL_H
#define __CR_MEDIAN_SHELL_H


#include <creator.h>
#include <math_define.h>
#include <mb_operation_result.h>
#include <op_shell_parameter.h>


class  MATH_CLASS  MbSNameMaker;
class  MATH_CLASS  MedianShellFaces;


//------------------------------------------------------------------------------
/** \brief \ru Строитель срединной оболочки тела.
           \en Constructor of a median shell of solid. \~
  \details \ru Строитель осуществляет построение срединной оболочки между выбранными парами граней тела.
               Поверхности выбранные граней должны быть эквидистантны по отношению друг к другу. \n
           \en Constructor performs the building of a median shell between suitable selected face pairs of solid.
               Suitable face pairs should be equidistant from each other. \n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbMedianShell : public MbCreator {
private :
  MedianShellFaces  faces;       ///< \ru Выбранные грани. \en Selected faces . 
  MedianShellValues parameters;  ///< \ru Параметры срединной оболочки. \en Parameters of median shell. 

public:
  /// \ru Конструктор по выбранным граням и параметрам срединной оболочки. \en Constructor by selected faces and parameters of median shell. 
  MbMedianShell( const MedianShellFaces & faces, const MedianShellValues & params, const MbSNameMaker & snMaker );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbMedianShell();

private:
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  MbMedianShell( const MbMedianShell &, MbRegDuplicate * );

public:
  virtual MbeCreatorType  IsA()  const; // \ru Тип элемента \en Type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 
  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const;  // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );        // \ru Сделать равным \en Make equal 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual void        GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 

  // \ru Построение оболочки по исходным данным \en Construction of a shell from the given data 
  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL );

  /// \ru Дать параметры. \en Get the parameters. 
  void        GetParameters( MedianShellValues & params ) const { params = parameters; }
  /// \ru Установить параметры. \en Set the parameters. 
  void        SetParameters( const MedianShellValues & params ) { parameters = params; }


DECLARE_PERSISTENT_CLASS_NEW_DEL( MbMedianShell )
OBVIOUS_PRIVATE_COPY( MbMedianShell )
};

IMPL_PERSISTENT_OPS( MbMedianShell )

//------------------------------------------------------------------------------
/** \brief \ru Построить срединную оболочку между выбранными парами граней тела.
           \en Build a median shell between selected faces of solid. \~
  \details \ru Построить срединную оболочку между выбранными парами граней тела.
               Выбранные грани должны быть эквидистантны по отношению друг к другу. 
               Грани должны принадлежать одному и тому же телу.
               Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Build a median shell between suitable selected face pairs of solid.
               Suitable face pairs should be offset from each other. 
               The faces must belong to the same body.
               The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  solid       - \ru Исходное тело.
                            \en The initial solid. \~
  \param[in]  faces       - \ru Выбранные пары граней.
                            \en Selected face pairs. \~
  \param[in]  parameters  - \ru Параметры операции.
                            \en Parameters of operation. \~
  \param[in]  operNames   - \ru Именователь операции.
                            \en An object defining names generation in the operation \~
  \param[out] res         - \ru Код результата операции.
                            \en Operation result code. \~
  \param[out] shell       - \ru Построенная срединная оболочка.
                            \en Constructed median shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateMedianShell( const MbFaceShell &                   solid,
                                           const std::vector<c3d::IndicesPair> & faceIndexes,
                                           const MedianShellValues &             parameters, 
                                           const MbSNameMaker &                  operNames, 
                                                 MbResultType &                  res, 
                                                 MbFaceShell *&                  shell );


#endif // __CR_MEDIAN_SHELL_H