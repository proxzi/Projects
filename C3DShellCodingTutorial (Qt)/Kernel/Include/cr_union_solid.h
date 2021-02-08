﻿////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель объединения наборов граней в один набор граней.
         \en Constructor of union of two face sets to one face set.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_UNION_SOLID_H
#define __CR_UNION_SOLID_H

#include <math_define.h>
#include <templ_sptr.h>
#include <creator.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель объединения наборов граней в один набор граней.
           \en Constructor of union of two face sets to one face set. \~
  \details \ru Строитель объединения выполняет объединение наборов граней в один набор граней,
    при этом может быть выполнена обработка пересечений граней. \n
           \en Constructor of union performs union of face sets into a single face set,
    meanwhile the treatment of faces intersection can be performed. \n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbUnionSolid : public MbCreator {
protected :
  c3d::CreatorsSPtrVector creators;          ///< \ru Набор данных для построения исходных оболочек. \en Data set for construction of the source shells. 
  c3d::IndicesVector      countNumbers;      ///< \ru Индекс начального строителя для следующей оболочки. \en Index of the source creator for the next shell. 
  c3d::IndicesVector      sharedLinks;       ///< \ru Номера общих наборов строителей для оболочек. \en Numbers of common creators sets for shells. 
  size_t                  sharedCount;       ///< \ru Количество общих набор строителей. \en The number of common creators sets. 
  OperationType           operation;         ///< \ru Тип булевой операции над оболочками. \en Type of Boolean operation on shells. 
  bool                    checkIntersection; ///< \ru Проверять ли на пересечение тела. \en Whether to check the solids for intersection. 
  bool                    mergeFaces;        ///< \ru Объединять подобные грани (true). \en Whether to union similar faces (true).  
  double                  buildSag;          ///< \ru Угловое отклонение при движении по кривым и поверхностям. \en Angular deviation while moving along curves and surfaces. 

public :
  MbUnionSolid( const c3d::CreatorsSPtrVector & creators, 
                      bool                      sameCreators, 
                const c3d::IndicesVector &      countNumbers, 
                      size_t                    sharedCnt,
                const c3d::IndicesVector &      sharedLinks,
                      OperationType             operType, 
                      bool                      checkIntersection, 
                      bool                      mergeFaces,
                const MbSNameMaker &            nameMaker );
private :
  MbUnionSolid( const MbUnionSolid &, MbRegDuplicate * );
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbUnionSolid( const MbUnionSolid & ); 
public :
  virtual ~MbUnionSolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию \en Create a copy 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );          // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D &, MbRegTransform * = NULL );                 // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual size_t      GetCreatorsCount   ( MbeCreatorType ) const; // \ru Посчитать внутренние построители по типу. \en Count internal creators by type.
  virtual bool        GetInternalCreators( MbeCreatorType, c3d::ConstCreatorsSPtrVector & ) const; // \ru Получить внутренние построители по типу. \en Get internal creators by type.
  virtual bool        SetInternalCreators( MbeCreatorType, c3d::CreatorsSPtrVector & );            // \ru Получить внутренние построители по типу. \en Get internal creators by type.

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );       // \ru Сделать равным \en Make equal 

  // \ru Общие функции твердого тела \en Common functions of solid 

  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction 

  virtual void        SetYourVersion( VERSION version, bool forAll );

public:
          /// \ru Тип булевой операции над телами. \en Type of Boolean operation on solids. 
          OperationType GetOperationType() const { return operation; }
          /// \ru Угловое отклонение при движении по кривым и поверхностям. \en Angular deviation while moving along curves and surfaces. 
          double        GetBuildSag()      const { return buildSag; }

          /// \ru Общее количество строителей. \en Total count of creators. 
          size_t        GetCreatorsCount() const { return creators.size(); }
          /// \ru Дать строитель. \en Get the creator. 
  const   MbCreator *   GetCreator( size_t k ) const { return ((k < creators.size()) ? &(*creators[k]) : NULL); }

public:
          /// \ru Собрать группы общих строителей тел. \en Collect groups of shared creators. 
  static  size_t          CollectSharedCreators( c3d::CreatorsSPtrVector & creators, c3d::IndicesVector & countNumbers, c3d::IndicesVector & sharedLinks );
private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
         void           operator = ( const MbUnionSolid & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbUnionSolid )
}; // MbUnionSolid

IMPL_PERSISTENT_OPS( MbUnionSolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку булевой операции множества оболочек.
           \en Create a shell of Boolean operation of shell set. \~ 
  \details \ru Для указанной оболочки и множества оболочек построить оболочку как результат булевой операции над оболочкой и множеством оболочек.
    Перед операцией множество оболочек объединяется в одну оболочку, в которой содержатся все грани множества оболочек.
    При необходимости выполняется объединение пересекающихся оболочек.\n
    Одновременно с построением оболочки функция создаёт её строитель. \n
           \en For a given shell and a shell set construct a shell as a result of Boolean operation on the shell and a shell set.
    Before the operation a shell set is united into a single shell which contains all the faces of shell set.
    Union of the intersected shells is performed if necessary.
    The function simultaneously constructs the shell and creates its constructor. \n \~
  \param[in]  solid          - \ru Оболочка, с которой выполняется булева операция объединённого множества оболочек (может быть NULL).
                               \en The shell the Boolean operation of the united shell set is performed with (can be NULL). \~
  \param[in]  sameShell      - \ru Способ копирования граней оболочки.
                               \en Method of shell faces copying. \~
  \param[in]  creators       - \ru Строители набора оболочек.
                               \en Shell set creators. \~
  \param[in]  countNumbers   - \ru Номера крайних строителей для набора оболочек.
                               \en Indices of the last creators for a shell set. \~
  \param[in]  shells         - \ru Набор оболочек, подлежащих объединению.
                               \en Shell set to unite. \~
  \param[in]  sameShells     - \ru Способ копирования граней.
                               \en The method of copying faces. \~
  \param[in]  oType          - \ru Тип булевой операции.
                               \en A Boolean operation type. \~
  \param[in]  checkIntersect - \ru Проверять ли пересечение оболочек.
                               \en Whether to check shells intersection. \~
  \param[in]  mergeFaces     - \ru Сливать подобные грани.
                               \en Whether to merge similar faces. \~
  \param[in]  operNames      - \ru Именователь операции.
                               \en An object defining names generation in the operation. \~
  \param[in]  isArray        - \ru Являются ли оболочки размноженными по прямоугольной сетке копиями?
                               \en Are the shells copies duplicated over the rectangular mesh? \~
  \param[out] res            - \ru Код результата операции.
                               \en Operation result code. \~
  \param[out] shell          - \ru Построенный набор граней.
                               \en Constructed set of faces. \~  
  \param[out] notGluedShells - \ru Множество оболочек, которые не получилось приклеить.
                               \en An array of shells which were not glued. \~
  \result \ru Возвращает строитель, если операция была выполнена успешно.
          \en Returns the constructor if the operation has been successfully performed. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateUnion(       MbFaceShell *             solid, 
                                           MbeCopyMode               sameShell,
                                     const c3d::CreatorsSPtrVector & creators,
                                     const c3d::IndicesVector &      countNumbers,
                                     const RPArray<MbFaceShell> &    shells, 
                                           MbeCopyMode               sameShells, 
                                           OperationType             oType, 
                                           bool                      checkIntersect, 
                                           bool                      mergeFaces, 
                                     const MbSNameMaker &            operNames, 
                                           bool                      isArray, // \ru Флаг массива \en Flag of array 
                                           MbResultType &            res, 
                                           MbFaceShell *&            shell,
                                           RPArray<MbFaceShell> *    notGluedShells = NULL ); 


//------------------------------------------------------------------------------
/** \brief \ru Объединить множества граней оболочек в одну оболочку.
           \en Unite a set of shells' faces into a single shell. \~ 
  \details \ru Множества граней указанных оболочек положить в одну оболочку. \n
    Одновременно с построением оболочки функция создаёт её строитель. \n
           \en Put sets of faces of the specified shells to a single shell.+ \n
    The function simultaneously constructs the shell and creates its constructor. \n \~
  \param[in]  creators       - \ru Строители набора оболочек.
                               \en Shell set creators. \~
  \param[in]  countNumbers   - \ru Номера крайних строителей для набора оболочек.
                               \en Indices of the last creators for a shell set. \~
  \param[in]  shells         - \ru Набор оболочек, подлежащих объединению.
                               \en Shell set to unite. \~
  \param[in]  operNames      - \ru Именователь операции.
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
MATH_FUNC (MbCreator *) CreateUnion( const c3d::CreatorsSPtrVector & creators,
                                     const c3d::IndicesVector &      countNumbers, 
                                     const RPArray<MbFaceShell> &    shells, 
                                     const MbSNameMaker &            operNames,
                                           MbResultType &            res, 
                                           MbFaceShell *&            shell );


#endif // __CR_UNION_SOLID_H
