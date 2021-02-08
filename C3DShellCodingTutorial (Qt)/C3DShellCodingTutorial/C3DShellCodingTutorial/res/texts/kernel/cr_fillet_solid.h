////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель cкругления ребeр.
         \en Edges fillet constructor.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_FILLET_SOLID_H
#define __CR_FILLET_SOLID_H


#include <cr_smooth_solid.h>
#include <function.h>


struct MATH_CLASS MbEdgeFunction; 


//------------------------------------------------------------------------------
/** \brief \ru Строитель cкругления ребeр.
           \en Edges fillet constructor. \~
  \details \ru Строитель cкругления ребeр содержит параметры для выполнения операции, функции изменения радиуса, 
    идентификаторы граней остановки скруглений, идентификаторы скругляемых вершин. \n
    Скругление ребра заключается в его замене на грань, гладко сопрягающую соединяемые ребром грани.
    Построенная грань в сечении может иметь форму дуги окружности, эллипса, параболы и гиперболу.
    Дуга окружности может иметь постоянный или переменный радиус, а также постоянную хорду. \n
           \en Edges fillet constructor contains parameters for performing the operation, radius law, 
    identifiers of faces terminating fillets, fillet vertices identifiers. \n
    Edge fillet consists in its replacement with a face smoothly connecting the faces incident at the edge.
    The section of the constructed face can be an arc of circle, ellipse, parabola or hyperbola.
    A circular arc can have a constant or variable radius and also a constant chord. \n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbFilletSolid : public MbSmoothSolid {
public :
  RPArray<MbFunction> functions;  ///< \ru Функции изменения радиусов сопряжения. \en Functions of changing conjugation radii. 
  SArray<MbItemIndex> boundaries; ///< \ru Номера граней для обрезки краёв скругления / фаски. \en Indices of faces for trimming the fillet / chamfer boundaries. 
  SArray<MbItemIndex> vertices;   ///< \ru Номера скругляемых вершин. \en Indices of vertices to fillet. 
  CornerValues        cornerData; ///< \ru Параметры скругления вершин. \en Parameters of vertices fillet.  

public :
  MbFilletSolid( SArray<MbEdgeFacesIndexes> & inds, 
                 RPArray<MbFunction> & funcs, 
                 SArray<MbItemIndex> & bounds, 
                 SArray<MbItemIndex> & verts,
                 const SmoothValues  & params, 
                 const CornerValues  & data, 
                 const MbSNameMaker  & n );
private :
  MbFilletSolid( const MbFilletSolid & init, MbRegDuplicate * iReg ); // \ru Конструктор копирования \en Copy-constructor 
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbFilletSolid( const MbFilletSolid & init ); 
public :
  virtual ~MbFilletSolid();

  // \ru Общие функции математического объекта. \en Common functions of the mathematical object. 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию \en Create a copy 
  virtual void        Transform( const MbMatrix3D &matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D &to, MbRegTransform * = NULL );        // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D &axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void        GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void        SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта. \en Set properties of the object.
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property. 

  virtual bool        IsSame( const MbCreator & other, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  virtual bool        SetEqual( const MbCreator & init ); // \ru Сделать равным. \en Make equal. 

  // \ru Общие функции твердого тела \en Common functions of solid  

  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction 

private :
  virtual void        ReadDistances ( reader &in );
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbFilletSolid & ); // \ru НЕЛЬЗЯ!!! \en NOT ALLOWED!!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbFilletSolid )
}; // MbFilletSolid

IMPL_PERSISTENT_OPS( MbFilletSolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку со cкруглением ребeр.
           \en Create a shell with edges fillet. \~
  \details \ru Для указанной оболочки построить оболочку, в которой выполнено cкругление или фаска рёбер с постоянными параметрами.\n 
    Одновременно с построением оболочки функция создаёт её строитель. \n
           \en For a given shell create a shell with edges fillet or chamfer with constant parameters.\n 
    The function simultaneously constructs the shell and creates its constructor. \n \~
  \param[in]  solid          - \ru Исходная оболочка.
                               \en The source shell. \~
  \param[in]  sameShell      - \ru Способ копирования граней исходной оболочки.
                               \en Method of copying the source shell faces. \~
  \param[in]  initCurves     - \ru Скругляемые рёбра исходной оболочки.
                               \en The source shell's edges to fillet. \~
  \param[in]  initBounds     - \ru Грани исходной оболочки для обрезки cкругления или фаски.
                               \en The source shell faces to trim the fillet of chamfer. \~
  \param[in]  initVertices   - \ru Скругляемые вершины "чемоданных углов".
                               \en Vertices for blending of three surfaces. \~
  \param[in]  parameters     - \ru Параметры обработки рёбер.
                               \en Parameters of edges processing. \~
  \param[in]  cornerData     - \ru Параметры скругления вершин "чемоданных углов".
                               \en Parameters of blending three surfaces. \~
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
MATH_FUNC (MbCreator *) CreateFillet( MbFaceShell * solid, 
                                      MbeCopyMode sameShell, 
                                      RPArray<MbCurveEdge> & initCurves, 
                                      RPArray<MbFace> & initBounds, 
                                      RPArray<MbVertex> & initVertices, 
                                      const SmoothValues & parameters, 
                                      const CornerValues & cornerData,
                                      const MbSNameMaker & names,
                                      MbResultType & res, 
                                      MbFaceShell *& shell );


//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку со cкруглением ребeр.
           \en Create a shell with edges fillet. \~
  \details \ru Для указанной оболочки построить оболочку, в которой выполнено cкругление рёбер переменным радиусом.\n 
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en For a given shell create a shell with edges fillet with a variable radius.\n 
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  solid          - \ru Исходная оболочка.
                               \en The source shell. \~
  \param[in]  sameShell      - \ru Способ копирования граней исходной оболочки.
                               \en Method of copying the source shell faces. \~
  \param[in]  initCurves     - \ru Обрабатываемые рёбра исходной оболочки и значения переменного радиуса.
                               \en The source shell edges to process and values of variable radius. \~
  \param[in]  initBounds     - \ru Грани исходной оболочки для обрезки cкругления или фаски.
                               \en The source shell faces to trim the fillet or chamfer. \~
  \param[in]  parameters     - \ru Параметры обработки рёбер.
                               \en Parameters of edges processing. \~
  \param[in]  names          - \ru Именователь операции.
                               \en An object defining names generation in the operation. \~
  \param[out] res            - \ru Код результата операции.
                               \en Operation result code. \~
  \param[out] shell          - \ru Построенный набор граней.
                               \en Constructed set of faces. \~  
  \result \ru Возвращает строитель, если операция была выполнена успешно.
          \en Returns the constructor if the operation has been successfully performed. \~
  \ingroup Curve3D_Modeling
*/
// ---
MATH_FUNC (MbCreator *) CreateFillet( MbFaceShell * solid, MbeCopyMode sameShell, 
                                      SArray<MbEdgeFunction> & initCurves, 
                                      RPArray<MbFace> & initBounds, 
                                      const SmoothValues & parameters, 
                                      const MbSNameMaker & names, 
                                      MbResultType & res, 
                                      MbFaceShell *& shell );


#endif // __CR_FILLET_SOLID_H
