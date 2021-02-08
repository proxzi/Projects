////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение оболочки соединения.
         \en Construction of a join shell. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_JOIN_SHELL_H
#define __CR_JOIN_SHELL_H


#include <op_shell_parameter.h>
#include <creator.h>
#include <math_define.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки соединения.
           \en Constructor of a join shell. \~
  \details \ru Строитель оболочки, соединяющей две грани по двум кривым на них. \n
           \en Constructor of a shell joining two faces by two curves on them. \n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbJoinShell : public MbCreator {
protected:
  MbCurve3D *       curve1;     ///< \ru Первая образующая кривая. \en The first generating curve.  
  MbCurve3D *       curve2;     ///< \ru Вторая образующая кривая. \en The second generating curve. 
  JoinSurfaceValues parameters; ///< \ru Параметры поверхности соединения. \en Parameters of a join surface. 
public :
  MbJoinShell( MbCurve3D & c1, MbCurve3D & c2, const JoinSurfaceValues & p, const MbSNameMaker & n ); 
private :
  MbJoinShell( const MbJoinShell & init, MbRegDuplicate * ireg );
public :
  virtual ~MbJoinShell();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA  () const;                                                    ///< \ru Тип элемента \en Element type 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const;                           ///< \ru Сделать копию \en Make a copy 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );             ///< \ru Преобразовать элемент согласно матрице \en Transform an element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL );             ///< \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); ///< \ru Поворот вокруг оси \en Rotation about an axis 

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Являются ли объекты подобными. \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );       // \ru Сделать равным \en Make equal 

  virtual MbePrompt   GetPropertyName ();                           // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetProperties ( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties ( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & );   // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции твердого тела \en Common functions of solid solid 

  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL );    ///< \ru Построение \en Construction 

  
          // \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       JoinSurfaceValues & params ) const { params = parameters; }
          // \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const JoinSurfaceValues & params )       { parameters = params; }

  const   MbCurve3D & GetCurve( ptrdiff_t num ) const;

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbJoinShell )
OBVIOUS_PRIVATE_COPY( MbJoinShell )
};

IMPL_PERSISTENT_OPS( MbJoinShell )

//------------------------------------------------------------------------------
/*  \brief \ru Проверить необходимость модификации второй кривой.
           \en Check if a modification of the second curve is necessary. \~
  \details \ru Проверить необходимость модификации второй кривой для построения оболочки соединения на этих кривых. \n
           \en Check whether a modification of the second curve is necessary for construction of a join shell on these curves. \n \~ 
  \param[in]  curve1 - \ru Первая кривая.
                       \en The first curve. \~
  \param[in]  curve2 - \ru Вторая кривая.
                       \en The second curve. \~
  \param[out] isInverted1 - \ru Была ли первая кривая инвертирована.
                            \en Whether the first curve was inverted. \~
  \param[out] isShifted1 - \ru Было ли смещено начало второй кривой.
                           \en Whether the beginning of the first curve was shifted. \~
  \param[in]  version - \ru Версия построения.
                        \en The version of construction. \~
  \result \ru Возвращает построенную оболочку.
          \en Returns the constructed shell. \~
  \ingroup Model_Creators
*/
//---
void CheckJoinedShellCurve( const MbCurve3D & curve1,
                            const MbCurve3D & curve2,
                            bool &      isInverted1,
                            bool &      isShifted1,
                            VERSION     version );


//------------------------------------------------------------------------------
/*  \brief \ru Построить кривую по набору рёбер.
           \en Construct a curve given a set of edges. \~
  \details \ru Построить кривую по набору рёбер для поверхности соединения.
           \en Construct a curve given a set of edges for a join surface. \~
  \param[in]  edges - \ru Набор ребер.
                      \en A set of edges. \~
  \param[in]  orients - \ru Ориентация рёбер набора.
                        \en Orientation of edges from the set. \~
  \param[in]  matr - \ru Матрица преобразования рёбер набора.
                     \en Transformation matrix of edges from the set. \~
  \param[out] res - \ru Код результата построения.
                    \en Construction result code. \~
  \result \ru Возвращает построенную кривую.
          \en Returns the constructed curve. \~
  \ingroup Model_Creators
*/
//---
MbCurve3D * CreateJoinedShellCurve( const RPArray<MbCurveEdge> & edges, 
                                    const SArray<bool> & orients,
                                    const MbMatrix3D & matr,
                                    MbResultType & res );


//------------------------------------------------------------------------------
/*  \brief \ru Построить оболочку соединения.
           \en Construct a join shell. \~
  \details \ru Построить оболочку, соединяющую две грани по двум кривым на них. \n
           \en Construct a shell joining two faces by two curves on them. \n \~ 
  \param[in]  curve1 - \ru Кривая на первой соединяемой поверхности.
                       \en A curve on the first surface to join. \~
  \param[in]  curve2 - \ru Кривая на второй соединяемой поверхности.
                       \en A curve on the second surface to join. \~
  \param[in]  parameters - \ru Параметры построения.
                           \en Parameters of a shell creation. \~
  \param[in]  names - \ru Именователь граней.
                      \en An object for naming faces. \~
  \param[in]  isPhantom - \ru Режим создания фантома.
                          \en Create in the phantom mode. \~
  \param[out] res - \ru Код результата построения.
                    \en Construction result code. \~
  \result \ru Возвращает построенную оболочку.
          \en Returns the constructed shell. \~
  \ingroup Model_Creators
*/
// ---
MbFaceShell * MakeJoinShell( MbSurfaceCurve & curve1,
                             MbSurfaceCurve & curve2, 
                             JoinSurfaceValues & parameters,
                             const MbSNameMaker & names,
                             bool isPhantom, 
                             MbResultType & res );


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку соединения.
           \en Construct a join shell. \~
  \details \ru Построить оболочку, соединяющую две грани по двум кривым на них. 
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct a shell joining two faces by two curves on them. 
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  curve1 - \ru Кривая на первой соединяемой поверхности.
                       \en A curve on the first surface to join. \~
  \param[in]  curve2 - \ru Кривая на второй соединяемой поверхности.
                       \en A curve on the second surface to join. \~
  \param[in]  parameters - \ru Параметры построения.
                           \en Parameters of a shell creation. \~
  \param[in]  names - \ru Именователь граней.
                      \en An object for naming faces. \~
  \param[out] res - \ru Код результата построения.
                    \en Construction result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateJoinShell( MbSurfaceCurve & curve1, 
                                         MbSurfaceCurve & curve2, 
                                         JoinSurfaceValues & parameters,
                                         const MbSNameMaker & names,
                                         MbResultType & res, 
                                         MbFaceShell *& shell );


//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку соединения.
           \en Construct a join shell. \~
  \details \ru Построить оболочку соединения по двум наборам ребер. 
    Рёбра двух наборов определяют набор граней соединения, каждая из которых побстроена по двум кривым. 
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct a shell of join given two sets of edges. 
    Edges of two sets define a set of join faces each of which is constructed by two curves. 
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  edges1 - \ru Первый набор ребер.
                       \en The first set of edges. \~
  \param[in]  orients1 - \ru Ориентация рёбер первого набора.
                         \en Orientation of edges from the first set. \~
  \param[in]  edges2 - \ru Второй набор ребер.
                       \en The second set of edges. \~
  \param[in]  orients2 - \ru Ориентация рёбер второго набора.
                         \en Orientation of edges of the second set. \~
  \param[in]  matr1 - \ru Матрица преобразования рёбер первого набора.
                      \en Transformation matrix of edges from the first set. \~
  \param[in]  matr2 - \ru Матрица преобразования рёбер второго набора.
                      \en Transformation matrix of edges from the second set. \~
  \param[in]  parameters - \ru Параметры построения.
                           \en Parameters of a shell creation. \~
  \param[in]  names - \ru Именователь граней.
                      \en An object for naming faces. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \param[in]  isPhantom - \ru Режим создания фантома.
                          \en Create in the phantom mode. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateJoinShell( const RPArray<MbCurveEdge> & edges1, 
                                         const SArray<bool> & orients1,
                                         const RPArray<MbCurveEdge> & edges2, 
                                         const SArray<bool> & orients2,
                                         const MbMatrix3D & matr1,
                                         const MbMatrix3D & matr2,
                                         JoinSurfaceValues & parameters,
                                         const MbSNameMaker & names,
                                         MbResultType & res, 
                                         MbFaceShell *& shell,
                                         bool isPhantom );


#endif // __CR_JOIN_SHELL_H
