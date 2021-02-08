////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель операции объединения листовых тел по торцу.
         \en Constructor of operation of union of sheet solids by butt. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_SHEET_UNION_SOLID_H
#define __CR_SHEET_UNION_SOLID_H


#include <creator.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель операции объединения листовых тел по торцу.
           \en Constructor of operation of union of sheet solids by butt. \~
  \details \ru Строитель операции объединения листовых тел по торцу объединяет тела
           только по указанному с помощью ориентированных рёбер торцу,
           независимо от возможных пересечений тел в других местах.\n.
           \en Constructor of operation of union of sheet solids by butt unites solids
           only by the bound specified using oriented edges
           independently of possible intersections of solids in other places.\n. \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbSheetUnionSolid : public MbCreator {
protected :
  RPArray<MbCreator> creators;  ///< \ru Журнал построения: 0<=i<countOne -  оболочки первого тела-операнда; countOne<=i<creators.Count() - оболочки второго тела-операнда. \en History tree: 0<=i<countOne -  shells of the first operand-solid; countOne<=i<creators.Count() - shells of the second operand-solid. 
  size_t             countOne;  ///< \ru Разделитель строителей тел-операндов. \en Separator of operand solids creators. 

public :
  MbSheetUnionSolid( MbCreator & solid2, const bool same2, const MbSNameMaker & n );
  MbSheetUnionSolid( const RPArray<MbCreator> & solid2, const bool same2, const MbSNameMaker & n );
private :
  MbSheetUnionSolid( const MbSheetUnionSolid & init, MbRegDuplicate *ireg );

public :
  virtual ~MbSheetUnionSolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * ireg = NULL );              // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * ireg = NULL );              // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * ireg = NULL );  // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию \en Create a copy 

  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & ); // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsSame   ( const MbCreator & other, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & item ) const; // \ru Являются ли объекты подобными? \en Determine whether an object is similar?
  virtual bool        SetEqual ( const MbCreator & );         // \ru Сделать равным \en Make equal 

  // \ru Общие функции твердого тела \en Common functions of solid 

  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction 

  virtual void        SetYourVersion( VERSION version, bool forAll );

          /// \ru Количество строителей первого тела. \en Count of creators of the first solid. 
          size_t      GetCountOne()      const { return countOne;         } 
          /// \ru Общее количество строителей. \en Total count of creators. 
          size_t      GetCreatorsCount() const { return creators.Count(); } 
          /// \ru Добавить в журнал. \en Add to the history tree. 
          void        AddCreator   ( MbCreator & creator ); 
          /// \ru Дать строитель. \en Get the constructor. 
          MbCreator * GetCreator   ( const size_t ind ) const;
          void        DeleteCreator( const size_t ind ); 

private :
          // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
          MbSheetUnionSolid( const MbSheetUnionSolid & init ); 
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          MbSheetUnionSolid & operator = ( const MbSheetUnionSolid & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbSheetUnionSolid )
};

IMPL_PERSISTENT_OPS( MbSheetUnionSolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку объединённых по торцу листовых тел.
           \en Create a shell of sheet solids united by a butt. \~
  \details \ru Для указанных оболочек построить оболочку как результат операции объединения над множествами граней двух тел.
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en For the specified shells create a shell using operation of union of face sets of two solids.
    The function simultaneously creates the shell and its constructor.\n \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateSheetUnion(       MbFaceShell &        faceShell1,
                                          const MbeCopyMode          sameShell1,
                                          const RPArray<MbCreator> & creators2,
                                                MbFaceShell &        faceShell2,
                                          const MbeCopyMode          sameShell2,
                                          const MbSNameMaker &       operNames,
                                                MbResultType &       res,
                                                MbFaceShell *&       shell );


#endif // __CR_SHEET_UNION_SOLID_H
