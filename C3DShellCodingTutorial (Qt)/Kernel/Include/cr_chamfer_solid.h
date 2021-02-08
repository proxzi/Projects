////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель тела с фасками рёбер.
         \en Constructor of solid with edges' chamfers.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_CHAMFER_SOLID_H
#define __CR_CHAMFER_SOLID_H


#include <cr_smooth_solid.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель тела с фасками рёбер.
           \en Constructor of solid with edges' chamfers. \~
  \details \ru Строитель тела с фасками рёбер, выполняющий замену указанных рёбер линейчатыми гранями,
    стыкующимися со смежными гранями обрабатываемых ребер.
           \en Constructor of solid with edges' chamfers performing the replacement of the specified edges by ruled faces
    connected with the adjacent faces of the edges being processed. \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbChamferSolid : public MbSmoothSolid {
public :

public :
  MbChamferSolid( SArray<MbEdgeFacesIndexes> & _indexes,
                  const SmoothValues & params, const MbSNameMaker & n );
private :
  MbChamferSolid( const MbChamferSolid & init, MbRegDuplicate * iReg ); // \ru Конструктор копирования \en Copy-constructor 
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbChamferSolid( const MbChamferSolid & init ); 
public :
  virtual ~MbChamferSolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию \en Create a copy 

  virtual void        GetProperties( MbProperties &properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties &properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 

  virtual bool        IsSame( const MbCreator & other, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  virtual bool        SetEqual( const MbCreator &init );    // \ru Сделать равным \en Make equal 

  // \ru Общие функции твердого тела \en Common functions of solid  

  virtual bool        CreateShell( MbFaceShell *&shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction 

private :
  virtual void        ReadDistances ( reader &in );
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbChamferSolid & );

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbChamferSolid )
}; // MbChamferSolid

IMPL_PERSISTENT_OPS( MbChamferSolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку с фасками ребeр.
           \en Create a shell with edges' chamfers. \~
  \details \ru Для указанной оболочки построить оболочку, в которой выполнены фаски указанных рёбер.\n
           \en For the given shell create a shell with chamfers of the specified edges.\n \~ 
  \param[in]  solid          - \ru Исходная оболочка.
                               \en The source shell. \~
  \param[in]  sameShell      - \ru Способ копирования граней исходной оболочки.
                               \en Method of copying the source shell faces. \~
  \param[in]  initCurves     - \ru Обрабатываемые рёбра исходной оболочки.
                               \en The source shell edges to be processed. \~
  \param[in]  parameters     - \ru Правметры обработки рёбер.
                               \en Parameters of edges processing. \~
  \param[in]  names          - \ru Именователь операции.
                               \en An object defining names generation in the operation. \~
  \param[out] res            - \ru Код результата операции.
                               \en Operation result code. \~
  \param[out] shell          - \ru Построенный набор граней.
                               \en Constructed set of faces. \~  
  \result \ru Возвращает строитель, если операция была выполнена успешно.
          \en Returns the constructor if the operation has been successfully performed. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateChamfer( MbFaceShell * solid, 
                                       MbeCopyMode sameShell, 
                                       RPArray<MbCurveEdge> & initCurves, 
                                       const SmoothValues & parameters, 
                                       const MbSNameMaker & names, 
                                       MbResultType & res, 
                                       MbFaceShell *& shell );


#endif // __CR_CHAMFER_SOLID_H
