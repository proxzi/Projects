////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение удлинённой грани оболочки.
         \en Construction of an extended face of a shell. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_EXTENSION_SHELL_H
#define __CR_EXTENSION_SHELL_H


#include <creator.h>
#include <op_shell_parameter.h>
#include <math_define.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель удлинённой грани оболочки.
           \en Constructor of an extended face of a shell. \~
  \details \ru Строитель удлинённой грани оболочки. Удлинение может быть выполнено следующими способами.
    Может быть ублинена на заданное расстояние указанная грань.
    К указанной грани может быть добавлена гладко стыкующаяся с ней грань.
    К указанной грани может быть добавлена грань, полученная выдавливанием крайнего ребра в заданном направлении.
           \en Constructor of an extended face of a shell. Extension can be performed in the following ways:
    The specified faces can be extended on the given distance.
    A smoothly connected face can be added to the given face.
    A face obtained by extrusion of boundary edge in the given direction can be added to the specified face. \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbExtensionShell : public MbCreator {
protected :
  MbItemIndex         faceIndex;   ///< \ru Идентификатор удлиняемой грани в оболочке. \en Identifier of a shell face to extend. 
  SArray<MbItemIndex> edgeIndexes; ///< \ru Идентификаторы ребер в грани. \en Identifier of edges in the face. 
  ExtensionValues     parameters;  ///< \ru Параметры построения удлинённой оболочки. \en Parameters of the extended shell construction. 

public :
  MbExtensionShell( const MbItemIndex & fInd, const SArray<MbItemIndex> & inds, 
                    const ExtensionValues & p, const MbSNameMaker & n );
private :
  MbExtensionShell( const MbExtensionShell &, MbRegDuplicate * ireg ); 
public :
  virtual ~MbExtensionShell();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 
  virtual void        Transform( const MbMatrix3D & matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D & to, MbRegTransform * = NULL );                 // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D & axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual void        GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  
  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );       // \ru Сделать равным \en Make equal 

  // \ru Общие функции твердого тела \en Common functions of solid solid 

  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction 

          // \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       ExtensionValues & params ) const { params = parameters; }
          // \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const ExtensionValues & params )       { parameters = params; }

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbExtensionShell )
OBVIOUS_PRIVATE_COPY( MbExtensionShell )
}; // MbExtensionShell

IMPL_PERSISTENT_OPS( MbExtensionShell )

//------------------------------------------------------------------------------
/** \brief \ru Построить удлинённую грань оболочки.
           \en Construct the extended face of a shell. \~
  \details \ru Построить удлинённую грань оболочки. Удлинение может быть выполнено следующими способами.
    Может быть ублинена на заданное расстояние указанная грань.
    К указанной грани может быть добавлена гладко стыкующаяся с ней грань.
    К указанной грани может быть добавлена грань, полученная выдавливанием крайнего ребра в заданном направлении.
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct the extended face of a shell. Extension can be performed in the following ways:
    The specified faces can be extended on the given distance.
    A smoothly connected face can be added to the given face.
    A face obtained by extrusion of a boundary edge in the given direction can be added to the specified face.
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  solid - \ru Исходная оболочка.
                      \en The initial shell. \~
  \param[in]  sameShell  - \ru Режим копирования исходной оболочки.
                           \en Mode of copying the initial shell. \~
  \param[in]  face - \ru Удлиняемая грагнь.
                     \en Face to extend. \~
  \param[in]  edges - \ru Крайние рёбра удлиняемой грани.
                      \en Boundary edges of a face to extend. \~
  \param[in]  parameters - \ru Параметры построения.
                           \en Parameters of a shell creation. \~
  \param[in]  operNames - \ru Именователь граней.
                          \en An object for naming faces. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateExtensionShell( MbFaceShell * solid, 
                                              MbeCopyMode sameShell, 
                                              MbFace & face, 
                                              const RPArray<MbCurveEdge> & edges, 
                                              const ExtensionValues & parameters, 
                                              const MbSNameMaker & operNames, 
                                              MbResultType & res, 
                                              MbFaceShell *& shell );


#endif // __CR_EXTENSION_SHELL_H
