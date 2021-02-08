////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель фаски или скругления ребeр тела.
         \en Constructor of chamfer or fillet of solid's edges.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_SMOOTH_SOLID_H
#define __CR_SMOOTH_SOLID_H


#include <op_shell_parameter.h>
#include <creator.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель фаски или скругления ребeр тела.
           \en Constructor of chamfer or fillet of solid's edges. \~
  \details \ru Строитель фаски или скругления ребeр тела содержит идентификаторы обрабатываемых рёбер и параметры для выполнения операции. \n
           \en Constructor of solid's edges chamfer or fillet contains identifiers of edges being processed and parameters for performing operation. \n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbSmoothSolid : public MbCreator {
protected :
  SArray<MbEdgeFacesIndexes> indexes; ///< \ru Номера ребер и номера смежных (сопрягаемых) граней. \en Indices of edges and indices of adjacent (conjugated) faces. 
  SmoothValues parameters;            ///< \ru Параметры скругления или фаски. \en Parameters of fillet or chamfer. 
  double buildSag;                    ///< \ru Шаг построения. \en Build step. 

private:
  MbSmoothSolid( const MbSmoothSolid & bres ); // \ru Не реализовано. \en No realize.
protected :
  MbSmoothSolid( const MbSNameMaker & n, SArray<MbEdgeFacesIndexes> & _indexes,
                 const SmoothValues & params );
  // \ru Конструктор копирования. \en Copy-constructor. 
  MbSmoothSolid( const MbSmoothSolid & bres, MbRegDuplicate * iReg ); 
public :
  virtual ~MbSmoothSolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA()  const = 0; // \ru Тип элемента \en A type of element 
  virtual MbeCreatorType  Type() const;     // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate *iReg = NULL ) const = 0;  // \ru Сделать копию \en Create a copy 
  virtual void        Transform( const MbMatrix3D &matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D &to, MbRegTransform * = NULL );        // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D &axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void        GetProperties( MbProperties & ) = 0; // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ) = 0; // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName() = 0; // \ru Выдать заголовок свойства объекта \en Get a name of object property 

  virtual bool        IsSame( const MbCreator & other, double accuracy ) const = 0; // \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  virtual bool        SetEqual( const MbCreator & ) = 0;     // \ru Сделать равным \en Make equal 
  virtual bool        IsSimilar ( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 

  // \ru Общие функции твердого тела \en Common functions of solid  

  virtual bool        CreateShell( MbFaceShell *&shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ) = 0; // \ru Построение \en Construction 

          /// \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       SmoothValues & params ) const { params = parameters; }
          /// \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const SmoothValues & params )       { parameters = params; }

private :
  virtual void        ReadDistances ( reader &in ) = 0;
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbSmoothSolid & );

  DECLARE_PERSISTENT_CLASS( MbSmoothSolid )
}; // MbSmoothSolid

IMPL_PERSISTENT_OPS( MbSmoothSolid )

#endif // __CR_SMOOTH_SOLID_H
