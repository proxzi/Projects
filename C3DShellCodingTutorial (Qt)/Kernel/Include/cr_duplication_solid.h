////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель размноженого набора граней.
         \en Constructor of duplication face sets . \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef CR_ELEMENTARY_SOLID_H
#define CR_ELEMENTARY_SOLID_H


#include <creator.h>
#include <op_duplication_parameter.h>


class  MATH_CLASS  MbFaceShell;
class              MbRegTransform;
class              MbRegDuplicate;


//------------------------------------------------------------------------------
/** \brief \ru Строитель размноженого набора граней.
           \en Constructor of duplication face sets . \~
  \details \ru Строитель выполняет размножение тела согласно параметрам и объединяет копии в одно тело\n
           \en Creator makes duplication of face sets accordind to parameters and unite its into a single face set\~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbDuplicationSolid : public MbCreator {
protected:
  DuplicationValues * parameters; ///< \ru Параметры размножения. \en Parameters of duplication.

public:
  /// \ru Конструктор по параметрам. \en Constructor by parameters. 
  MbDuplicationSolid( const DuplicationValues & p, const MbSNameMaker & n );
private:
  MbDuplicationSolid( const MbDuplicationSolid & init, MbRegDuplicate *ireg  );
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbDuplicationSolid( const MbDuplicationSolid & init );
public:
  virtual~MbDuplicationSolid();

  /** \ru \name Общие функции строителя оболочки.
      \en \name Common functions of the shell creator.
      \{ */
  /// \ru Получить регистрационный тип (для копирования, дублирования). \en Get the registration type (for copying, duplication). 
  virtual MbeCreatorType IsA() const;
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru сделать копию \en create a copy 
  virtual void        Transform( const MbMatrix3D & matr, MbRegTransform * = NULL );          // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D & to, MbRegTransform * = NULL );                 // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D & axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual void        GetProperties( MbProperties & properties ); // \ru выдать свойства объекта \en get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru записать свойства объекта \en set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru выдать заголовок свойства объекта \en get a name of object property 

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru являются ли объекты подобными \en whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );       // \ru сделать равным \en make equal 

  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction 
  /** \} */

private :
// \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
  void         operator = ( const MbDuplicationSolid & );

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbDuplicationSolid )
}; // MbDuplicationSolid

IMPL_PERSISTENT_OPS( MbDuplicationSolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку размножения исходной оболочки.
           \en Create a shell of duplication of original shell. \~ 
  \details \ru По данной оболочке и параметрам размножения построить оболочку как результат объединения копий.\n
    Одновременно с построением оболочки функция создаёт её строитель. \n
           \en For a given shell and duplication parameters construct a shell as a result of a union of copies. \n
    The function simultaneously constructs the shell and creates its constructor.\~
  \param[in]  solid          - \ru Исходная оболочка.
                               \en Original face set. \~
  \param[in]  params         - \ru Параметры размножения.
                               \en Parameters of duplication. \~
  \param[in]  operNames      - \ru Именователь операции.
                               \en An object defining names generation in the operation. \~
  \param[out] duplSolid      - \ru Построенный набор граней.
                               \en Constructed set of faces. \~  
  \param[out] res            - \ru Код результата операции.
                               \en Operation result code. \~
  \result \ru Возвращает строитель, если операция была выполнена успешно.
          \en Returns the constructor if the operation has been successfully performed. \~
  \ingroup Solid_Modeling
*/
MATH_FUNC (MbCreator *) CreateDuplication( const MbFaceShell & solid, 
                                           const DuplicationValues & params, 
                                           const MbSNameMaker & operNames,
                                           MbResultType & res,
                                           MbFaceShell *& shell );


#endif // CR_ELEMENTARY_SOLID_H