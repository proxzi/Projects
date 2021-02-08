////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение оболочки из NURBS-поверхностей.
         \en Construction of a sell from NURBS-surfaces. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_NURBS_SURFACES_SOLID_H
#define __CR_NURBS_SURFACES_SOLID_H


#include <math_define.h>
#include <mb_operation_result.h>
#include <creator.h>
#include <op_shell_parameter.h>


class  MATH_CLASS  MbCreator;
class  MATH_CLASS  MbSNameMaker;
class  MATH_CLASS  MbFaceShell;
struct MATH_CLASS  NurbsSurfaceValues;
class              IProgressIndicator;


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки из NURBS-поверхностей.
           \en Constructor of a shell from NURBS-surfaces. \~
  \details \ru Строитель оболочки из NURBS-поверхностей MbSplineSurface. 
    Аббревиатура NURBS получена из первых букв словосочетания Non-Uniform Rational B-Spline.
           \en Constructor of a shell from NURBS-surfaces MbSplineSurface. 
    Abbreviation of NURBS is obtained from the first letters of "Non-Uniform Rational B-Spline" phrase. \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbNurbsSurfacesSolid : public MbCreator {
protected:
  NurbsSurfaceValues parameters; ///< \ru Параметры построения. \en Construction parameters. 
  mutable bool       changed;    ///< \ru Флаг изменения параметров. \en Flag of parameters modification. 

public:
  // \ru конструктор, копирующий параметры \en constructor copying the parameters 
  MbNurbsSurfacesSolid( const NurbsSurfaceValues & params, const MbSNameMaker & names );
private:
  MbNurbsSurfacesSolid( const MbNurbsSurfacesSolid &, MbRegDuplicate * ireg );
public: 
  // \ru деструктор \en destructor 
  ~MbNurbsSurfacesSolid();

public: // \ru Общие функции математического объекта \en Common functions of the mathematical object 
  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru сделать копию \en create a copy 
  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        SetEqual ( const MbCreator & ); // \ru сделать равным \en make equal 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать по матрице \en Transform according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru сдвиг по вектору \en translation by a vector 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual MbePrompt   GetPropertyName(); // \ru выдать заголовок свойства объекта \en get a name of object property 
  virtual void        GetProperties( MbProperties & properties ); // \ru выдать свойства объекта \en get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru записать свойства объекта \en set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & s ); // \ru дать базовые объекты \en get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

public: 
  /// \ru построение оболочки \en creation of a shell 
  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL );
  virtual void        Refresh( MbFaceShell & outer ); ///< \ru обновить форму оболочки \en update shape of the shell 

          // \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       NurbsSurfaceValues & params ) const { params = parameters; }
          // \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const NurbsSurfaceValues & params )       { parameters = params; }

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbNurbsSurfacesSolid )
OBVIOUS_PRIVATE_COPY( MbNurbsSurfacesSolid )
};

IMPL_PERSISTENT_OPS( MbNurbsSurfacesSolid )

//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку из NURBS-поверхностей.
           \en Construct a shell from NURBS-surfaces. \~
  \details \ru Построить оболочку из NURBS-поверхностей MbSplineSurface. 
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct a shell from NURBS-surfaces MbSplineSurface. 
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  parameters - \ru Параметры построения.
                           \en Parameters of a shell creation. \~
  \param[in]  operNames - \ru Именователь граней.
                          \en An object for naming faces. \~
  \param[in]  isPhantom - \ru Режим создания фантома.
                          \en Create in the phantom mode. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] shell - \ru Построенная оболочка.
                      \en The resultant shell. \~
  \param[out] indicator - \ru Индикатор хода построения.
                          \en Construction process indicator. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateNurbsShell( NurbsSurfaceValues & parameters, 
                                          const MbSNameMaker & operNames, 
                                          bool isPhantom,
                                          MbResultType & res, 
                                          MbFaceShell *& shell,
                                          IProgressIndicator * indicator = NULL );


#endif // __CR_NURBS_SURFACES_SOLID_H
