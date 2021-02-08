////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение оболочки элементарного тела.
         \en Construction of shell for elementary solid. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_ELEMENTARY_SOLID_H
#define __CR_ELEMENTARY_SOLID_H


#include <creator.h>
#include <mb_enum.h>


class  MATH_CLASS  MbElementarySurface;


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки элементарного тела.
           \en Constructor of shell for elementary solid. \~
  \details \ru Строитель оболочки элементарного тела по набору опорных точек и типу: \n
    solidType = et_Sphere   - шар      (3 точки), \n
    solidType = et_Torus    - тор      (3 точки), \n
    solidType = et_Cylinder - цилиндр  (3 точки), \n
    solidType = et_Cone     - конус    (3 точки), \n
    solidType = et_Block    - блок     (4 точки), \n
    solidType = et_Wedge    - клин     (4 точки), \n
    solidType = et_Prism    - призма   (количество вершин основания+1 точка), \n
    solidType = et_Pyramid  - пирамида (количество вершин основания+1 точка), \n
    solidType = et_Plate    - плита    (4 точки). \n
           \en Constructor of shell for elementary solid by a set of support points and a type: \n
    solidType = et_Sphere   - a sphere     (3 points), \n
    solidType = et_Torus    - a torus      (3 points), \n
    solidType = et_Cylinder - a cylinder  (3 points), \n
    solidType = et_Cone     - a cone    (3 points), \n
    solidType = et_Block    - a block     (4 points), \n
    solidType = et_Wedge    - a wedge     (4 points), \n
    solidType = et_Prism    - a prism  (points count is equal to the base vertices count + 1), \n
    solidType = et_Pyramid  - a pyramid (points count is equal to the base vertices count + 1), \n
    solidType = et_Plate    - a plate   (4 points). \n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbElementarySolid : public MbCreator {
protected :
  SArray<MbCartPoint3D> points; ///< \ru Опорные точки оболочки тела. \en Support points of a solid shell. 
  ElementaryShellType type;     ///< \ru Тип тела. \en Type of a solid. 

public :
  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по точкам и типу тела.
             \en Constructor by points and a type of a solid. \~

    \param[in] pnts - \ru Опорные точки. \n
               pnts[0] определяет начало локальной системы координат. \n
               Для сферы, тора, цилиндра и конуса: \n
               pnts[1] определяет направление оси Z локальной системы. \n
               pnts[2] определяет направление оси X локальной системы. \n
               Для блока, клина и плиты: \n
               pnts[1] определяет направление оси X локальной системы. \n
               pnts[2] определяет направление оси Y локальной системы. \n
               Кроме того, \n
               pnts[1] определяет высоту цилиндра, высоту конуса,
               большой радиус тора, длину блока, длину клина. \n
               pnts[2] определяет радиус цилиндра, радиус конуса, радиус сферы,
               малый радиус тора, ширину блока, ширину клина. \n
               Последняя точка определяет высоту блока, клина, плиты, вершину пирамиды.
               \en Support points. \n
               pnts[0] determines a local coordinate system origin. \n
               For a sphere, a torus, a cylinder or a cone: \n
               pnts[1] determines the direction of Z-axis of a local coordinate system. \n
               pnts[2] determines the direction of X-axis of a local coordinate system. \n
               For a block, a plate or a wedge: \n
               pnts[1] determines the direction of X-axis of a local coordinate system. \n
               pnts[2] determines the direction of Y-axis of a local coordinate system. \n
               Also, \n
               pnts[1] determines the height of a cylinder or a cone,
               the major radius of a torus, the length of a block or a wedge. \n
               pnts[2] determines the radius of a cylinder or a cone, radius of a sphere,
               the minor radius of a torus, the width of a block or a wedge. \n
               The last point determines the height of a block, a wedge or a plate, the vertex of a pyramid. \~
    \param[in] t - \ru Тип элементарного тела.
                   \en Elementary solid type. \~
    \param[in] n - \ru Именователь операции.
                   \en An object defining names generation in the operation. \~
  */
  template<class Points>
  MbElementarySolid( const Points & pnts, ElementaryShellType t, const MbSNameMaker & n )
    : MbCreator( n    )
    , points   (      )
    , type     ( t    )
  {
    size_t cnt = pnts.size();
    points.reserve( cnt );
    for ( size_t k = 0; k < cnt; ++k ) {
      points.push_back( pnts[k] );
    }
  }

private :
  MbElementarySolid( const MbElementarySolid &, MbRegDuplicate * iReg ); // \ru Конструктор копирования с регистратором \en Copy-constructor with the registrator 
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbElementarySolid( const MbElementarySolid & ); 
public :
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbElementarySolid();

  /** \ru \name Общие функции строителя оболочки.
      \en \name Common functions of the shell creator.
      \{ */
  virtual MbeCreatorType IsA() const; // \ru Тип элемента \en Type of element 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D &, MbRegTransform * = NULL );                 // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 

  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems( RPArray<MbSpaceItem> & s );   // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar ( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual( const MbCreator & );       // \ru Сделать равным \en Make equal 

  virtual bool        CreateShell( MbFaceShell *&, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * = NULL ); // \ru Построение \en Construction 
  /** \} */

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbElementarySolid & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbElementarySolid )
}; // MbElementarySolid

IMPL_PERSISTENT_OPS( MbElementarySolid )

//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку элементарного тела.
           \en Create a shell of an elementary solid. \~
  \details \ru Создать оболочку элементарного тела по набору опорных точек и типу:\n
    solidType = et_Sphere   - шар      (3 точки), \n
    solidType = et_Torus    - тор      (3 точки), \n
    solidType = et_Cylinder - цилиндр  (3 точки), \n
    solidType = et_Cone     - конус    (3 точки), \n
    solidType = et_Block    - блок     (4 точки), \n
    solidType = et_Wedge    - клин     (4 точки), \n
    solidType = et_Prism    - призма   (количество вершин основания+1 точка), \n
    solidType = et_Pyramid  - пирамида (количество вершин основания+1 точка), \n
    solidType = et_Plate    - плита    (4 точки). \n
    Одновременно с построением оболочки функция создаёт её строитель. \n
           \en Create an elementary solid shell by a set of support points and type:\n
    solidType = et_Sphere   - a sphere     (3 points), \n
    solidType = et_Torus    - a torus      (3 points), \n
    solidType = et_Cylinder - a cylinder  (3 points), \n
    solidType = et_Cone     - a cone    (3 points), \n
    solidType = et_Block    - a block     (4 points), \n
    solidType = et_Wedge    - a wedge     (4 points), \n
    solidType = et_Prism    - a prism  (points count is equal to the base vertices count + 1), \n
    solidType = et_Pyramid  - a pyramid (points count is equal to the base vertices count + 1), \n
    solidType = et_Plate    - a plate   (4 points). \n
    The function simultaneously constructs the shell and creates its constructor. \n \~
  \param[in]  points - \ru Набор опорных точек.
                       \en Set of support points. \~
  \param[in]  t      - \ru Тип элементарного тела.
                       \en Elementary solid type. \~
  \param[in]  n      - \ru Именователь операции.
                       \en An object defining names generation in the operation. \~
  \param[out] res    - \ru Код результата операции.
                       \en Operation result code. \~
  \param[out] shell  - \ru Оболочка - результат построения.
                       \en Shell - the result of construction. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbCreator *) CreateElementary( const SArray<MbCartPoint3D> & points, 
                                                ElementaryShellType     t,
                                          const MbSNameMaker &          n, 
                                                MbResultType &          res, 
                                                MbFaceShell *&          shell );


//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку элементарного тела.
           \en Create a shell of an elementary solid. \~
  \details \ru Создать оболочку элементарного тела по элементарной поверхности.\n
    Одновременно с построением оболочки функция создаёт её строитель. \n
           \en Create an elementary solid shell by an elementary surface.\n
    The function simultaneously constructs the shell and creates its constructor. \n \~
  \param[in]  surface - \ru Элементарная поверхность.\n
                        Допускается тип поверхности - шар, тор, цилиндр, конус.
                        \en Elementary surface.\n
                        The acceptable surface types are sphere, torus, cylinder, cone. \~
  \param[in]  n       - \ru Именователь операции.
                        \en An object defining names generation in the operation. \~
  \param[out] res     - \ru Код результата операции.
                        \en Operation result code. \~
  \param[out] shell   - \ru Оболочка - результат операции.
                        \en Shell - the result of operation. \~
  \result \ru Возвращает строитель.
          \en Returns the constructor. \~
  \ingroup Solid_Modeling
*/
// ---
MATH_FUNC (MbCreator *) CreateElementary( const MbElementarySurface & surface, 
                                          const MbSNameMaker &        n, 
                                                MbResultType &        res, 
                                                MbFaceShell *&        shell );


#endif // __CR_ELEMENTARY_SOLID_H
