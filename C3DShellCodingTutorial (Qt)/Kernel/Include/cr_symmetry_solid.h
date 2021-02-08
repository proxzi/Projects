////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель симметричного тела.
         \en Constructor of a symmetric solid.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_SYMMETRY_SOLID_H
#define __CR_SYMMETRY_SOLID_H


#include <creator.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель симметричного тела.
           \en Constructor of a symmetric solid. \~
  \details \ru Строитель симметричного тела разрезает тело плоскостью на две части, удаляет одну из них, 
    для оставшейся части строит симметричную относительно плоскости копию и склеивает её с оставшейся частью.
           \en Constructor of a symmetric solid cuts a solid by a plane onto to parts, deletes one of them, 
    for the remained part it builds a copy symmetric relative to the plane and glues it with the remained part. \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbSymmetrySolid : public MbCreator {
protected :
  MbCartPoint3D origin;   ///< \ru Начало плоскости симметрии. \en Symmetry plane origin. 
  MbVector3D    axisX;    ///< \ru Ось плоскости симметрии. \en Symmetry plane axis. 
  MbVector3D    axisY;    ///< \ru Ось плоскости симметрии. \en Symmetry plane axis. 
  int           side;     ///< \ru Оставляемая часть (если side>0, то оставляем часть тела со стороны нормали плоскости симметрии). \en Remained part (if side>0, then a part of solid from the side of symmetric plane's normal is to be remained). 
  double        buildSag; ///< \ru Угловое отклонение при движении по кривым и поверхностям. \en Angular deviation while moving along curves and surfaces.  

public :
  MbSymmetrySolid( const MbCartPoint3D & p, const MbVector3D & ax, const MbVector3D & ay, 
                   int s, const MbSNameMaker & n );
private :
  MbSymmetrySolid( const MbSymmetrySolid & init, MbRegDuplicate * iReg );
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbSymmetrySolid( const MbSymmetrySolid & init );
public :
  virtual ~MbSymmetrySolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию \en Create a copy 
  virtual void        Transform( const MbMatrix3D &matr, MbRegTransform * = NULL );          // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D &to, MbRegTransform * = NULL );                 // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D &axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual ( const MbCreator & );       // \ru Сделать равным \en Make equal 

  // \ru Общие функции твердого тела \en Common functions of solid 

  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL ); // \ru Построение \en Construction 

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void    operator = ( const MbSymmetrySolid & );

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbSymmetrySolid )
}; // MbSymmetrySolid

IMPL_PERSISTENT_OPS( MbSymmetrySolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать симметричную оболочку.
           \en Create a symmetric shell. \~
  \details \ru Для указанной оболочки построить симметричную относительно указанной плоскости оболочку.
    функция разрезает оболочку плоскостью на две части, удаляет одну из них, 
    для оставшейся части строит симметричную относительно плоскости копию и склеивает её с оставшейся частью. \n 
    Одновременно с построением оболочки функция создаёт её строитель. \n
           \en For a given shell build a shell symmetric relative to the specified plane.
    the function cuts the shell by the plane onto two parts, deletes one of them, 
    for the remained part it builds a copy symmetric relative to the plane and glues it with the remained part. \n 
    The function simultaneously constructs the shell and creates its constructor. \n \~
  \param[in]  solid          - \ru Исходная оболочка.
                               \en The source shell. \~
  \param[in]  sameShell      - \ru Способ копирования граней исходной оболочки.
                               \en Method of copying the source shell faces. \~
  \param[in]  origin         - \ru Точка плоскости симметрии.
                               \en A point of plane of symmetry. \~
  \param[in]  axisX          - \ru Первая ось плоскости симметрии.
                               \en The first axis of symmetry. \~
  \param[in]  axisY          - \ru Вторая ось плоскости симметрии.
                               \en The second axis of symmetry. \~
  \param[in]  side           - \ru Сохраняемая часть исходной оболочки (+1, -1).
                               \en A part of the source shell to be kept (+1, -1). \~
  \param[in]  operNames      - \ru Именователь операции.
                               \en An object defining names generation in the operation. \~
  \param[out] res            - \ru Код результата операции выдавливания.
                               \en The extrusion operation result code. \~
  \param[out] shell          - \ru Построенный набор граней.
                               \en Constructed set of faces. \~  
  \result \ru Возвращает строитель, если операция была выполнена успешно.
          \en Returns the constructor if the operation has been successfully performed. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateSymmetry( MbFaceShell * solid, 
                                        MbeCopyMode sameShell, 
                                        const MbCartPoint3D & origin, 
                                        const MbVector3D & axisX, 
                                        const MbVector3D & axisY,
                                        int side, 
                                        const MbSNameMaker & operNames, 
                                        MbResultType & res,
                                        MbFaceShell *& shell );


#endif // __CR_SYMMETRY_SOLID_H
