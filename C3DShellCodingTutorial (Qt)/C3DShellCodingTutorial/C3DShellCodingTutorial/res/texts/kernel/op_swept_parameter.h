////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Параметры операций над телами.
         \en Parameters of operations on the solids. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __OP_SWEPT_PARAMETERS_H
#define __OP_SWEPT_PARAMETERS_H


#include <templ_rp_array.h>
#include <templ_sptr.h>
#include <math_version.h>
#include <math_define.h>
#include <mb_enum.h>
#include <mb_vector3d.h>
#include <mb_axis3d.h>
#include <cur_contour.h>
#include <cur_contour3d.h>
#include <surface.h>
#include <solid.h>
#include <function.h>
#include <vector>


class  MATH_CLASS  MbPlacement3D;
class  MATH_CLASS  MbMatrix3D;
class  MATH_CLASS  MbAxis3D;
class  MATH_CLASS  MbCurve3D;
class              MbRegTransform;
class              MbRegDuplicate;


//------------------------------------------------------------------------------
/** \brief \ru Данные об образующей.
           \en The generating data. \~
  \details \ru Данные об образующей операции движения. \n
    Образующая операции выдавливания, вращения или кинематической операции
    может включать в себя набор двумерных контуров, набор трехмерных контуров, тело. \n
    Для набора двумерных контуров на поверхности существуют следующие ограничения:\n
    – может быть один или несколько контуров;\n
    – если контуров несколько, они должны быть либо все замкнуты, либо все разомкнуты;\n
    - если контуры замкнуты, они могут быть вложенными друг в друга, уровень вложенности не ограничивается;\n
    – контуры не должны пересекаться между собой или самопересекаться.\n
    Для двумерных контуров на не плоской поверхности есть дополнительное ограничение:
      все контуры должны быть замкнуты.\n
    Построение операции по двумерным контурам на не плоской поверхности рассчитано на указание пользователем
      грани тела в качестве образующей. В этом случае данные для образующей можно получить
      с помощью метода грани MbFace::GetSurfaceCurvesData.\n
    Ограничения для трехмерных контуров:\n
    – контуры не должны пересекаться между собой или самопересекаться.\n
           \en Data about generating of movement operation. \n
    Generating of extrusion operation, rotation or sweeping operation
    can include a set of two-dimensional contours, a set of three-dimensional contours, solid. \n
    For a set of two-dimensional contours on the surface, the following restrictions:\n
    - can be one or multiple contours;\n
    - If there are multiple contours, all of them must be either closed or open;\n
    - if contours are closed, then they can be nested into each other, the level of nesting is not limited;\n
    - contours can't overlap each other or self-intersect.\n
    For two-dimensional contour on the non-planar surface is additional constraint:
      all the contours must be closed.\n
    Constructing operation by two-dimensional contours on non-planar surface  it is necessary to specify the by the user
      face of solid as generating. In this case, the generating data can be obtained
      by the method of face MbFace::GetSurfaceCurvesData.\n
    Constraints for three-dimensional contour:\n
    - contours can't overlap each other or self-intersect.\n \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS MbSweptData {

private:
  // \ru Данные о двумерных контурах на поверхности. \en Data about two-dimensional contours on the surface.
  c3d::SurfaceSPtr              surface;    ///< \ru Поверхность. \en The surface.
  c3d::PlaneContoursSPtrVector  contours;   ///< \ru Множество двумерных контуров. \en Set of two-dimensional contours.
  // \ru Трехмерные контуры. \en Three-dimensional contours.
  c3d::SpaceContoursSPtrVector  contours3D; ///< \ru Множество трёхмерных контуров. \en Set of three-dimensional contours.
  // \ru Тело. \en Solid.
  c3d::SolidSPtr                solid;      ///< \ru Тело. \en A solid.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  MbSweptData();
  /// \ru Конструктор копирования. \en Copy-constructor.
  MbSweptData( const MbSweptData &, MbRegDuplicate * ireg = NULL );

public:

  /** \brief \ru Конструктор плоской образующей.
             \en Constructor of planar swept. \~
    \details \ru Конструктор плоской образующей из одного контура.
             \en Constructor of planar swept from one contour. \~
    \param[in] place   - \ru Локальная система координат.
                         \en A local coordinate system. \~
    \param[in] contour - \ru Контур в параметрах заданной системы координат. Используется оригинал.
                         \en Contour in parameters of the given coordinate system. Used original. \~
  */
  MbSweptData( const MbPlacement3D & place, MbContour & contour );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по набору контуров на поверхности.
             \en Constructor by a set of contours on a surface. \~
    \param[in] _surface  - \ru Поверхность. Используется оригинал.
                           \en The surface. Used original. \~
    \param[in] _contours - \ru Набор контуров. Используются оригиналы.
                           \en A set of contours. Used originals. \~
  */
  MbSweptData( MbSurface & _surface, RPArray<MbContour> & _contours );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по набору контуров на поверхности.
             \en Constructor by a set of contours on a surface. \~
    \param[in] _surface  - \ru Поверхность. Используется оригинал.
                           \en The surface. Used original. \~
    \param[in] _contours - \ru Набор контуров. Используются оригиналы.
                           \en A set of contours. Used originals. \~
  */
  MbSweptData( MbSurface & _surface, c3d::PlaneContoursSPtrVector & _contours );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по кривой.
             \en Constructor by a contour. \~
    \param[in] _contour3d - \ru Кривая. Используются оригиналы.
                             \en A curve. Used originals. \~
  */
  MbSweptData( MbCurve3D & _curve3d );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по контуру.
             \en Constructor by a contour. \~
    \param[in] _contour3d - \ru Контур. Используются оригиналы.
                             \en A contour. Used originals. \~
  */
  MbSweptData( MbContour3D & _contour3d );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по набору пространственных контуров.
             \en Constructor by a set of spatial contours. \~
    \param[in] _contours3d - \ru Набор контуров. Используются оригиналы.
                             \en A set of contours. Used originals. \~
  */
  MbSweptData( RPArray<MbContour3D> & _contours3d );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по набору пространственных контуров.
             \en Constructor by a set of spatial contours. \~
    \param[in] _contours3d - \ru Набор контуров. Используются оригиналы.
                             \en A set of contours. Used originals. \~
  */
  MbSweptData( c3d::SpaceContoursSPtrVector & _contours3d );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по телу.
             \en Constructor by a solid. \~
    \param[in] _solid - \ru Тело. Используется оригинал объекта.
                        \en A solid. Used original of object. \~
  */
  MbSweptData( MbSolid & _solid );

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор смешанной образующей.
             \en Constructor of mixed swept. \~
    \param[in] _surface    - \ru Поверхность. Используется оригинал.
                             \en The surface. Used original. \~
    \param[in] _contours   - \ru Набор двумерных контуров в параметрах заданной поверхности. Используются оригиналы.
                             \en Set of two-dimensional contours in the parameters of the given surface. Used originals. \~
    \param[in] _contours3d - \ru Набор трехмерных контуров. Используются оригиналы.
                             \en A set of three-dimensional contours. Used originals. \~
    \param[in] _solid      - \ru Тело. Используется оригинал объекта.
                             \en A solid. Used original of object. \~
  */
  MbSweptData( MbSurface * _surface, RPArray<MbContour> & _contours,
               RPArray<MbContour3D> & _contours3d, MbSolid * _solid );

  /// \ru Деструктор. \en Destructor.
  ~MbSweptData();

public:
  /** \brief \ru Добавить данные.
             \en Add data. \~
    \details \ru Добавить данные о контурах на поверхности.
             \en Add data about contours to the surface. \~
    \param[in] _surface  - \ru Поверхность. Добавляется оригинал объекта.
                           \en The surface. Added original of the object. \~
    \param[in] _contours - \ru Набор контуров. Добавляются оригиналы.
                           \en A set of contours. Originals are added. \~
  */
  bool              AddData( MbSurface & _surface, const RPArray<MbContour> & _contours );

  /** \brief \ru Добавить данные.
             \en Add data. \~
    \details \ru Добавить данные о контурах на поверхности.
             \en Add data about contours to the surface. \~
    \param[in] _surface  - \ru Поверхность. Добавляется оригинал объекта.
                           \en The surface. Added original of the object. \~
    \param[in] _contours - \ru Набор контуров. Добавляются оригиналы.
                           \en A set of contours. Originals are added. \~
  */
  bool              AddData( MbSurface & _surface, c3d::PlaneContoursSPtrVector & _contours );

  /** \brief \ru Количество всех кривых.
             \en The count of all the curves. \~
    \details \ru Общее количество двумерных и трехмерных кривых.
             \en The total count of two and three-dimensional curves. \~
  */
  size_t            CurvesCount()              const;

  /** \brief \ru Получить кривую по индексу.
             \en Get the curve by the index. \~
    \details \ru Получить кривую из множества кривых на поверхности
      и трехмерных кривых.
             \en Get the curve from set of curves on the surface
      and three-dimensional curves. \~
    \param[in] i - \ru Номер кривой в пределах от 0 до CurvesCount().
                   \en The index of curve from 0 to CurvesCount(). \~
    \return \ru Кривую на поверхности или трехмерную кривую.
            \en Curve on the surface or three-dimensional curve. \~
  */
  SPtr<MbCurve3D>   GetCurve3D( size_t i )     const;

  /// \ru Есть данные о двумерных кривых на поверхности? \en Is there data of two-dimensional curves on the surface?
  bool              IsSurfaceCurvesData()      const;
  /// \ru Есть данные о пространственных кривых? \en Is there data of spatial curves?
  bool              IsSpaceCurvesData()        const;
  /// \ru Есть данные о теле? \en Is there data about the solid?
  bool              IsSolidData()              const;

  /// \ru Выдать поверхность. \en Get the surface.
  const MbSurface *                     GetSurface()    const { return surface; }
  /// \ru Выдать поверхность для изменения. \en Get the surface for editing.
        MbSurface *                     SetSurface()          { return surface; }
  /// \ru Выдать набор двумерных контуров. \en Get the set of two-dimensional contours.
  const c3d::PlaneContoursSPtrVector &  GetContours()   const { return contours;   }
  /// \ru Выдать набор трехмерных контуров. \en Get the set of three-dimensional contours.
  const c3d::SpaceContoursSPtrVector &  GetContours3D() const { return contours3D; }
  /// \ru Выдать тело. \en Get the solid.
  const MbSolid *                       GetSolid()      const { return solid; }
  /// \ru Выдать тело для изменения. \en Get the solid for editing.
        MbSolid *                       SetSolid()      const { return solid; }

  /** \brief \ru Преобразовать объект.
             \en Transform the object. \~
    \details \ru Преобразовать исходный объект согласно матрице c использованием регистратора.
             \en Transform the initial object according to the matrix using the registrator. \~
    \param[in] matr - \ru Матрица преобразования.
                      \en A transformation matrix. \~
    \param[in] iReg - \ru Регистратор.
                      \en Registrator. \~
  */
  void              Transform( const MbMatrix3D & matr, MbRegTransform * iReg = NULL );
  /** \brief \ru Сдвинуть объект.
             \en Move the object. \~
    \details \ru Сдвинуть геометрический объект вдоль вектора с использованием регистратора.
             \en Move a geometric object along the vector using the registrator. \~
    \param[in] to   - \ru Вектор сдвига.
                      \en Translation vector. \~
    \param[in] iReg - \ru Регистратор.
                      \en Registrator. \~
  */
  void              Move     ( const MbVector3D & to, MbRegTransform * iReg = NULL );
  /** \brief \ru Повернуть объект.
             \en Rotate the object. \~
    \details \ru Повернуть объект вокруг оси на заданный угол с использованием регистратора.
             \en Rotate an object about the axis by the given angle using the registrator. \~
    \param[in] axis  - \ru Ось поворота.
                       \en The rotation axis. \~
    \param[in] angle - \ru Угол поворота.
                       \en The rotation angle. \~
    \param[in] iReg  - \ru Регистратор.
                       \en Registrator. \~
  */
  void              Rotate   ( const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL );

  /** \brief \ru Определить, являются ли объекты равными.
             \en Determine whether the objects are equal. \~
    \details \ru Определить, являются ли объекты равными с заданной точностью.
             \en Determine whether the objects are equal with defined accuracy. \~
    \param[in] other - \ru Объект для сравнения.
                       \en Object for comparison. \~
    \return \ru Подобны ли объекты.
            \en Whether the objects are similar. \~
  */
  bool              IsSame( const MbSweptData & other, double accuracy ) const;
  /** \brief \ru Определить, являются ли объекты подобными.
             \en Determine whether the objects are similar. \~
    \details \ru Подобный объект можно инициализировать по данным подобного ему объекта.
             \en Similar object can be initialized by data of object which is similar to it. \~
    \param[in] other - \ru Объект для сравнения.
                       \en Object for comparison. \~
    \return \ru Подобны ли объекты.
            \en Whether the objects are similar. \~
  */
  bool              IsSimilar( const MbSweptData & other ) const;
  /** \brief \ru Сделать объекты равным.
             \en Make objects equal. \~
    \details \ru Равными можно сделать только подобные объекты.
             \en It is possible to make equal only similar objects. \~
    \param[in] init - \ru Объект для инициализации.
                      \en Object for initialization. \~
    \return \ru Сделан ли объект равным присланному.
            \en Whether the object is made equal to the given one. \~
  */
  bool              SetEqual ( const MbSweptData & other );

  /** \brief \ru Замкнуты ли все контуры.
             \en Whether all contours are closed. \~
    \details \ru Замкнуты ли все контуры. \n
             \en Whether all contours are closed. \n \~
    \return \ru Возвращает true, если все контуры замкнуты.
            \en Returns true if all contours are closed. \~
  */
  bool              IsContoursClosed() const;

  /// \ru Проверить, что нет разрывов между сегментами поверхностных контуров. \en Check that there are no gaps between the segments of the surface contours.
  bool              CheckSurfaceContourConnection( double eps ) const;
  /// \ru Проверить, что нет разрывов между сегментами пространственных контуров. \en Check that there are no gaps between the segments of the spatial contours.
  bool              CheckSpaceContourConnection( double eps ) const;

private:
  // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default.
  MbSweptData &     operator = ( const MbSweptData & );

KNOWN_OBJECTS_RW_REF_OPERATORS( MbSweptData ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Cпособ выдавливания/вращения.
           \en Method of extrusion/rotation. \~
  \details \ru Cпособ построения выдавливания/вращения. \n
           \en Method of extrusion/rotation constructing. \n \~
  \ingroup Build_Parameters
*/
// ---
enum MbSweptWay {
  sw_scalarValue = -2, ///< \ru Выдавить на заданную глубину / вращать на заданный угол. \en Extrude to a given depth / rotate by a given angle.
  sw_shell       = -1, ///< \ru До ближайшего объекта (тела). \en To the nearest object (solid).
  sw_surface     =  0, ///< \ru До поверхности. \en To the surface.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры вращения и выдавливания.
           \en Parameters of rotation and extrusion. \~
  \details \ru Данные о построении операции вращения или выдавливания
    в одном из направлений: прямом или обратном.
           \en Data about construction of rotation and extrusion
    in one of directions: forward or backward. \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS MbSweptSide {
public:
  MbSweptWay    way;          ///< \ru Способ выдавливания/вращения. \en Method of extrusion/rotation.
  double        scalarValue;  ///< \ru Угол вращения/глубина выдавливания. \en Angle of rotation/depth of extrusion.

  /** \brief \ru Расстояние от поверхности.
             \en Distance from the surface. \~
    \details \ru Расстояние от поверхности, до которой строим операцию.
      Задавать при построении операции до поверхности (way = sw_surface).
      distance < 0.0 при построении операции за поверхность,
      distance > 0.0 при построении операции до поверхности.
             \en Distance from the surface to construct up to.
      Set when constructing operation to the surface (way = sw_surface).
      distance < 0.0 when constructing operation back of surface,
      distance > 0.0 when constructing operation front of surface. \~
  */
  double        distance;

  /** \brief \ru Угол уклона.
             \en Draft angle. \~
    \details \ru Угол уклона при выдавливании.\n
      Операцию выдавливания с уклоном можно построить только в случае плоской образующей.
             \en Draft angle when extruding.\n
      Extrusion operation with draft can be constructed in the case of planar swept. \~
  */
  double        rake;

protected:
  /** \brief \ru Поверхность, до которой строим операцию.
             \en The surface to construct up to. \~
    \details \ru Поверхность, до которой строим операцию.\n
      Задавать при построении операции до поверхности (way = sw_surface).
             \en The surface to construct up to.\n
      Set when constructing operation to the surface (way = sw_surface). \~
  */
  MbSurface *   surface;

  /** \brief \ru Признак совпадения нормали поверхности с нормалью грани.
             \en An attribute of coincidence between the surface normal and the face normal. \~
    \details \ru Признак совпадения нормали поверхности, до которой строим операцию, с нормалью грани.\n
      Задавать при построении операции до поверхности (way = sw_surface).\n
      Указывает положение оболочки-результата относительно поверхности.
      Используется при построении массива операций до поверхности.
      Если у всех элементов массива признак должен быть одинаковым,
      то при построении исходной операции нужно задать признак равным orient_BOTH (направление не определено).
      При построении признак будет определен, и его значение нужно использовать для построения остальных элементов массива.
             \en An attribute of coincidence between the face normal and the normal of surface to which to create operation.\n
      Set when constructing operation to the surface (way = sw_surface).\n
      Specifies the position of shell-result relative to the surface.
      Used when constructing the array of operations to the surface.
      If attributes of all the elements of array must be the same,
      then when constructing of the original operation need to set attribute which is equal to orient_BOTH (the direction is not determined).
      When constructing the attribute is determined and its value should be used for the construction of other elements of the array. \~
 */
  MbeSenseValue sameSense;


public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Задает параметры операции со способом "на заданную глубину".
      Для построения операции параметры нужно изменить,
      например, указать глубину выдавливания (угол вращения).
             \en Sets parameters of the operation with the method "to a given depth".
      For construction of operation the parameters need to change,
      for example: specify the depth of extrusion (angle of rotation). \~
  */
  MbSweptSide()
    : way        ( sw_scalarValue )
    , scalarValue( 0.0 )
    , distance   ( 0.0 )
    , rake       ( 0.0 )
    , surface    ( NULL )
    , sameSense  ( orient_BOTH )
  {}

  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор на угол вращения\глубину выдавливания.
             \en Constructor by angle of rotation\depth of extrusion. \~
    \param[in] sVal - \ru Угол вращения\глубина выдавливания.
                      \en Angle of rotation\depth of extrusion. \~
  */
  MbSweptSide( double sVal )
    : way        ( sw_scalarValue )
    , scalarValue( sVal )
    , distance   ( 0.0  )
    , rake       ( 0.0  )
    , surface    ( NULL )
    , sameSense  ( orient_BOTH )
  {}

  /** \brief \ru Конструктор до поверхности.
             \en Constructor to the surface. \~
    \details \ru Конструктор до поверхности. Расстояние от поверхности задается равным 0.0.
             \en Constructor to the surface. Distance from the surface is set to 0.0. \~
    \param[in] surf - \ru Поверхность, до которой строится операция.
                      \en The surface to construct up to. \~
  */
  MbSweptSide( MbSurface * surf );

  /** \brief \ru Конструктор до поверхности.
             \en Constructor to the surface. \~
    \details \ru Конструктор до поверхности. Для элемента массива.
             \en Constructor to the surface. For array element. \~
    \param[in] surf - \ru Поверхность, до которой строится операция.
                      \en The surface to construct up to. \~
    \param[in] sense - \ru Признак совпадения нормали заданной поверхности с нормалью грани.
      Указывает, по какую сторону от поверхности должна находиться построенная оболочка.
                       \en An attribute of coincidence between the normal of given surface and the face normal.
      Indicates at which side of the surface the must be located constructed shell. \~
  */
  MbSweptSide( MbSurface * surf, MbeSenseValue sense );

  /** \brief \ru Конструктор копирования.
             \en Copy-constructor. \~
    \details \ru Конструктор копирования данных с использованием той же поверхности.
             \en Copy-constructor of data with using of the same surface. \~
    \param[in] other - \ru Исходные параметры.
                       \en Initial parameters. \~
  */
  MbSweptSide( const MbSweptSide & other );

  /** \brief \ru Конструктор копирования с регистратором.
             \en Copy-constructor with the registrator. \~
    \details \ru Конструктор копирования с регистратором. Поверхность копируется.
             \en Copy-constructor with the registrator. Surface is copying. \~
    \param[in] other - \ru Исходные параметры.
                       \en Initial parameters. \~
  */
  MbSweptSide( const MbSweptSide & other, MbRegDuplicate * ireg );

  /// \ru Деструктор. \en Destructor.
  virtual ~MbSweptSide();

  /// \ru Оператор присваивания данных с использованием той же поверхности. \en Assignment operator of data with using of the same surface.
  MbSweptSide & operator = ( const MbSweptSide & other );

  /// \ru Получить поверхность. \en Get the surface.
  MbSurface * GetSurface() const { return surface; }
  /// \ru Заменить поверхность. \en Replace surface.
  void        SetSurface( MbSurface * s );

  /// \ru Получить признак совпадения нормали поверхности с нормалью грани. \en Get the attribute of coincidence between the surface normal and the face normal.
  MbeSenseValue   GetSameSense() const { return sameSense; }
  /// \ru Установить признак совпадения нормали поверхности с нормалью грани. \en Set the attribute of coincidence between the surface normal and the face normal.
  void            SetSameSense( MbeSenseValue sense ) { sameSense = sense; }
  /// \ru Доступ к признаку совпадения нормали поверхности с нормалью грани. \en Access to the attribute of coincidence between the surface normal and the face normal.
  MbeSenseValue & SetSameSense() { return sameSense; }

  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool            IsSame( const MbSweptSide & other, double accuracy ) const
  {
    if ( (other.way == way) && (other.sameSense == sameSense) ) {
      if ( (::fabs(other.scalarValue - scalarValue) < accuracy) &&
           (::fabs(other.distance - distance) < accuracy) &&
           (::fabs(other.rake - rake) < accuracy) )
      {
        bool isSurf1 = (surface != NULL);
        bool isSurf2 = (other.surface != NULL);

        if ( isSurf1 == isSurf2 ) {
          if ( isSurf1 && isSurf2 ) {
            if ( !other.surface->IsSame( *surface, accuracy ) )
              return false;
          }
          return true;
        }
      }
    }

    return false;
  }
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры формообразующей операции.
           \en The parameters of form-generating operation. \~
  \details \ru Параметры построения формообразующей операции
    (например, выдавливания, вращения, кинематической, по сечениям). \n
           \en The construction parameters of form-generating operation.
    (for example: extrusion, rotation, sweeping, loft). \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS SweptValues {
public:

  /** \brief \ru Толщина стенки (величина эквидистанты) в прямом направлении.
             \en Wall thickness (offset distance) along the forward direction. \~
    \details \ru Толщина стенки (величина эквидистанты) в положительном направлении нормали объекта
     (грани, поверхности, плоскости кривой).
             \en Wall thickness (offset distance) along the positive direction of the normal of an object
     (face, surface, plane of the curve). \~
  */
  double thickness1;

  /** \brief \ru Толщина стенки (величина эквидистанты) в обратном направлении.
             \en Wall thickness (offset distance) along the backward direction. \~
    \details \ru Толщина стенки (величина эквидистанты) в отрицательном направлении нормали объекта
     (грани, поверхности, плоскости кривой).
             \en Wall thickness (offset distance) along the negative direction of the normal of an object
     (face, surface, plane of the curve). \~
  */
  double thickness2;

  bool   shellClosed;   ///< \ru Замкнутость оболочки. \en Closedness of shell.

private:
  bool   checkSelfInt;  ///< \ru Флаг проверки самопересечений (вычислительно "тяжелыми" методами). \en Flag for checking of self-intersection (computationally by "heavy" methods).
  bool   mergeFaces;    ///< \ru Сливать подобные грани (true). \en Whether to merge similar faces (true). 

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  SweptValues()
    : thickness1  ( 0.0  )
    , thickness2  ( 0.0  )
    , shellClosed ( true )
    , checkSelfInt( true )
    , mergeFaces  ( true )
  {}
  /// \ru Конструктор по толщинам и замкнутости. \en Constructor by thicknesses and closedness.
  SweptValues( double t1, double t2, bool c = true )
    : thickness1  ( t1   )
    , thickness2  ( t2   )
    , shellClosed ( c    )
    , checkSelfInt( true )
    , mergeFaces  ( true )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  SweptValues( const SweptValues & other )
    : thickness1  ( other.thickness1   )
    , thickness2  ( other.thickness2   )
    , shellClosed ( other.shellClosed  )
    , checkSelfInt( other.checkSelfInt )
    , mergeFaces  ( other.mergeFaces   )
  {}
  /// \ru Деструктор. \en Destructor.
  virtual ~SweptValues() {}

public:
  /// \ru Это параметры выдавливания? \en This is extrusion parameters?
  virtual bool IsExtrusionValues()  const { return false; }
  /// \ru Это параметры вращения? \en This is rotation parameters?
  virtual bool IsRevolutionValues() const { return false; }
  /// \ru Это параметры кинематики? \en This is "evolution" parameters?
  virtual bool IsEvolutionValues()  const { return false; }
  /// \ru Это параметры операции по сечениям? \en This is "lofted" parameters?
  virtual bool IsLoftedValues()     const { return false; }
  /// \ru Это параметры операции ребра жесткости? \en This is "rib" parameters?
  virtual bool IsRibValues()        const { return false; }

  /// \ru Определить, являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool IsSame( const SweptValues & other, double accuracy ) const;
  /// \ru Определить, являются ли объекты подобными. \en Determine whether the objects are similar. \~
  virtual bool IsSimilar( const MbSweptData & other ) const;
  /// \ru Сделать объекты равным. \en Make objects equal. \~
  virtual bool SetEqual ( const MbSweptData & other );

public:
  /// \ru Функция копирования данных. \en Function of copying data.
  void  Init( const SweptValues & other ) {
    thickness1   = other.thickness1;
    thickness2   = other.thickness2;
    shellClosed  = other.shellClosed;
    checkSelfInt = other.checkSelfInt;
    mergeFaces   = other.mergeFaces;
  }

  /// \ru Получить состояние замкнутости. \en Get the closedness state.
  bool        IsShellClosed() const { return shellClosed; }
  /// \ru Установит состояние замкнутости. \en Set the closedness state.
  void        SetShellClosed( bool cl ) { shellClosed = cl; }
  /// \ru Получить состояние флага проверки самопересечений. \en Get the state of flag of checking self-intersection.
  bool        CheckSelfInt() const { return checkSelfInt; }
  /// \ru Установить состояние флага проверки самопересечений. \en Set the state of flag of checking self-intersection.
  void        SetCheckSelfInt( bool c ) { checkSelfInt = c; }
  /// \ru Сливать подобные грани (true). \en Whether to merge similar faces (true). 
  bool        MergeFaces() const { return mergeFaces; }
  /// \ru Сливать подобные грани (true). \en Whether to merge similar faces (true). 
  void        SetMergeFaces( bool mf ) { mergeFaces = mf; }

  /// \ru Оператор присваивания. \en Assignment operator.
  void       operator = ( const SweptValues & other ) { Init( other ); }

  KNOWN_OBJECTS_RW_REF_OPERATORS( SweptValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры выдавливания или вращения.
           \en The parameters of extrusion or rotation. \~
  \details \ru Параметры выдавливания или вращения кривых с опциями по направлениям. \n
     В операции выдавливания прямым направлением считается направление, сонаправленное
     с вектором выдавливания, а обратным - противоположное направление.
     В операции вращения прямое направлением определяется по оси вращения с помощью правила правой руки.
           \en The parameters of extrusion or rotation of curves with options along the directions. \n
     In the extrusion operations the forward direction is the direction collinear
     with the vector of extrusion and back - the opposite direction.
     In the rotation operation the forward direction is determined by the axis of rotation using the right hand rule. \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS SweptValuesAndSides: public SweptValues {
public:
  MbSweptSide side1; ///< \ru Параметры выдавливания/вращения в прямом направлении. \en The parameters of extrusion/rotation along the forward direction.
  MbSweptSide side2; ///< \ru Параметры выдавливания/вращения в обратном направлении. \en The parameters of extrusion/rotation along the backward direction.

public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров для построения замкнутой оболочки без тонкой стенки.
      Способ построение в обоих направлениях - на заданную глубину, равную 0.0.
             \en Constructor of parameters for construction of closed shell without the thin wall.
      Method of construction in both directions - to a given depth equal to 0.0. \~
  */
  SweptValuesAndSides()
    : SweptValues()
    , side1      ()
    , side2      ()
  {}
  /** \brief \ru Конструктор по углам вращения или глубинам выдавливания.
             \en Constructor by rotation angles and extrusion depths. \~
    \details \ru Конструктор параметров для построения замкнутой оболочки без тонкой стенки.
      Способ построение в обоих направлениях - на заданную глубину.
             \en Constructor of parameters for construction of closed shell without the thin wall.
      Method of construction in both directions - to a given depth. \~
    \param[in] scalarValue1 - \ru Угол вращения\глубина выдавливания в прямом направлении.
                              \en Angle of rotation\depth of extrusion along the forward direction. \~
    \param[in] scalarValue2 - \ru Угол вращения\глубина выдавливания в обратном направлении.
                              \en Angle of rotation\depth of extrusion along the backward direction. \~
  */
  SweptValuesAndSides( double scalarValue1, double scalarValue2 )
    : SweptValues(              )
    , side1      ( scalarValue1 )
    , side2      ( scalarValue2 )
  {}
  /// \ru Конструктор копирования данных на тех же поверхностях. \en Copy-constructor of data on the same surfaces.
  SweptValuesAndSides( const SweptValuesAndSides & other )
    : SweptValues( other       )
    , side1      ( other.side1 )
    , side2      ( other.side2 )
  {}
  /// \ru Конструктор полного копирования данных. \en Constructor of complete copying of data.
  SweptValuesAndSides( const SweptValuesAndSides & other, MbRegDuplicate * ireg )
    : SweptValues( other             )
    , side1      ( other.side1, ireg )
    , side2      ( other.side2, ireg )
  {}
  /// \ru Деструктор. \en Destructor.
  virtual ~SweptValuesAndSides();

public:
  // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool IsSame( const SweptValues & other, double accuracy ) const
  {
    const SweptValuesAndSides * obj = dynamic_cast<const SweptValuesAndSides *>( &other );
    if ( obj != NULL ) {
      if ( side1.IsSame( obj->side1, accuracy ) && side2.IsSame( obj->side2, accuracy ) ) {
        if ( obj->SweptValues::IsSame( *this, accuracy ) ) {
          return true;
        }
      }
    }
    return false;
  }

public:
  /// \ru Оператор присваивания данных на тех же поверхностях. \en Assignment operator of data copying on the same surfaces.
  void        operator = ( const SweptValuesAndSides & other ) {
    SweptValues::Init( other );
    side1 = other.side1;
    side2 = other.side2;
  }

  /** \brief \ru Преобразовать согласно матрице.
             \en Transform according to the matrix. \~
    \details \ru Преобразовать согласно матрице поверхности в прямом и обратном направлении.
             \en Transform according to the matrix of surface in the forward and backward direction. \~
    \param[in] matr - \ru Матрица преобразования.
                      \en A transformation matrix. \~
    \param[in] iReg - \ru Регистратор.
                      \en Registrator. \~
  */
  void        Transform( const MbMatrix3D & matr, MbRegTransform * iReg = NULL );
  /** \brief \ru Сдвинуть вдоль вектора.
             \en Move along a vector. \~
    \details \ru Сдвинуть вдоль вектора поверхности в прямом и обратном направлении.
             \en Move along the vector of the surface along the forward and backward direction. \~
    \param[in] to   - \ru Вектор сдвига.
                      \en Translation vector. \~
    \param[in] iReg - \ru Регистратор.
                      \en Registrator. \~
  */
  void        Move     ( const MbVector3D & to, MbRegTransform * iReg = NULL );
  /** \brief \ru Повернуть вокруг оси.
             \en Rotate around an axis. \~
    \details \ru Повернуть вокруг оси поверхности в прямом и обратном направлении.
             \en Rotate around the axis of the surface along the forward and backward direction. \~
    \param[in] axis  - \ru Ось поворота.
                       \en The rotation axis. \~
    \param[in] angle - \ru Угол поворота.
                       \en The rotation angle. \~
    \param[in] iReg  - \ru Регистратор.
                       \en Registrator. \~
  */
  void        Rotate   ( const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL );

  /** \brief \ru Сделать копии поверхностей.
             \en Make copies of surfaces. \~
    \details \ru Если в каком-либо направлении задана поверхность, заменить эту поверхность на ее копию.
             \en If the surface is given in any direction, then replace the surface with its copy. \~
    \param[in] ireg - \ru Регистратор копий.
                      \en Registrator of copies. \~
    \return \ru true, если хотя бы одна поверхность имелась и сдублирована.
            \en True if at least one surface is had and copied. \~
  */
  bool        DuplicateSurfaces( MbRegDuplicate * ireg = NULL );

  /// \ru Получить поверхность в положительном направлении. \en Get the surface along the positive direction.
  MbSurface * GetSurface1() const { return side1.GetSurface(); }
  /// \ru Получить поверхность в отрицательном направлении. \en Get the surface along the negative direction.
  MbSurface * GetSurface2() const { return side2.GetSurface(); }
  /// \ru Установить поверхность в положительном направлении. \en Set the surface along the positive direction.
  void        SetSurface1( MbSurface * s ) { side1.SetSurface( s ); }
  /// \ru Установить поверхность в отрицательном направлении. \en Set the surface along the negative direction.
  void        SetSurface2( MbSurface * s ) { side2.SetSurface( s ); }
  /// \ru Поменять поверхности местами. \en Swap surfaces.
  void        ExchangeSurfaces();
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры операции выдавливания.
           \en The parameters of extrusion operation. \~
  \details \ru Параметры операции выдавливания кривых с опциями по направлениям. \n
           \en The parameters of extrusion operation of curves with options along directions. \n \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS ExtrusionValues : public SweptValuesAndSides {
public:

  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров выдавливания для построения замкнутой оболочки без тонкой стенки
      в прямом направлении на величину, равную 10.0.
             \en Constructor of extrusion parameters for construction of closed shell without the thin wall.
      along the forward direction by value 10.0. \~
  */
  ExtrusionValues()
    : SweptValuesAndSides( 10., 0. ) {}
  /** \brief \ru Конструктор по глубинам выдавливания.
             \en Constructor by extrusion depths. \~
    \details \ru Конструктор параметров выдавливания для построения замкнутой оболочки без тонкой стенки.
      Способ построение в обоих направлениях - на заданную глубину.
             \en Constructor of extrusion parameters for construction of closed shell without the thin wall.
      Method of construction in both directions - to a given depth. \~
    \param[in] scalarValue1 - \ru Глубина выдавливания в прямом направлении.
                              \en Depth of extrusion along the forward direction. \~
    \param[in] scalarValue2 - \ru Глубина выдавливания в обратном направлении.
                              \en Depth of extrusion along the backward direction. \~
  */
  ExtrusionValues( double scalarValue1, double scalarValue2 ) 
    : SweptValuesAndSides( scalarValue1, scalarValue2 ) {}
  /// \ru Конструктор копирования, на тех же поверхностях. \en Copy-constructor on the same surfaces.
  ExtrusionValues( const ExtrusionValues & other ) 
    : SweptValuesAndSides( other ) {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  ExtrusionValues( const ExtrusionValues & other, MbRegDuplicate * ireg ) 
    : SweptValuesAndSides( other, ireg ) {}
  /// \ru Деструктор. \en Destructor.
  virtual ~ExtrusionValues();

public:
  // \ru Это параметры выдавливания? \en This is extrusion parameters?
  virtual bool IsExtrusionValues() const { return true; }

  // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool IsSame( const SweptValues & other, double accuracy ) const
  {
    const ExtrusionValues * obj = dynamic_cast<const ExtrusionValues *>( &other );
    if ( obj != NULL ) {
      if ( obj->SweptValuesAndSides::IsSame( *this, accuracy ) )
        return true;
    }
    return false;
  }

public:
  /// \ru Оператор присваивания, на тех же поверхностях. \en Assignment operator on the same surfaces.
  ExtrusionValues & operator = ( const ExtrusionValues & other ) {
    *static_cast<SweptValuesAndSides*>(this) = *static_cast<const SweptValuesAndSides*>(&other);
    return *this;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( ExtrusionValues ) // \ru Для работы со ссылками и объектами класса \en For treatment of references and objects of the class
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры операции вращения.
           \en The parameters of revolution operation. \~
  \details \ru Параметры операции вращения кривых с опциями по направлениям. \n
           \en The parameters of revolution operation of curves with options along directions. \n \~
  \ingroup Build_Parameters
*/
// ---
class MATH_CLASS RevolutionValues : public SweptValuesAndSides {
public:
  /** \brief \ru Форма топологии.
             \en Topology shape. \~
    \details \ru Форма топологии: 0 - тело типа сферы, 1 - тело типа тора.\n
      Если образующая - не замкнутая плоская кривая, и ось вращения лежит в плоскости кривой,
      то возможно построение тела вращения с топологией типа сферы. В этом случае образующая достраивается до оси вращения.
             \en Topology shape: 0 - sphere, 1 - torus.\n
      If swept is non-closed planar curve and axis of rotation lies on the curve plane,
      then is possible to construct revolution solids with the topology of sphere type. In this case the swept is being updated to the rotation axis.
I \~  */
  int  shape;

public:
   /** \brief \ru Конструктор по умолчанию.
              \en Default constructor. \~
    \details \ru Конструктор параметров вращения для построения замкнутой оболочки типа тора
      без тонкой стенки в прямом направлении на полный оборот.
             \en Constructor of revolution parameters for construction of closed shell of torus type
      without thin wall along the forward direction at full turn. \~
  */
  RevolutionValues()
    : SweptValuesAndSides( M_PI, 0. )
    , shape( 1 )
  {}
  /** \brief \ru Конструктор по углам вращения.
             \en Constructor by revolution angles. \~
    \details \ru Конструктор параметров вращения для построения замкнутой оболочки без тонкой стенки.
      Способ построение в обоих направлениях - на заданную глубину (заданный угол).
             \en Constructor of revolution parameters for construction of closed shell without the thin wall.
      Method of construction in both directions - to a given depth (given angle). \~
    \param[in] scalarValue1 - \ru Угол вращение в прямом направлении.
                              \en Revolution angle along the forward direction. \~
    \param[in] scalarValue2 - \ru Угол вращения в обратном направлении.
                              \en Revolution angle along the backward direction. \~
    \param[in] s            - \ru Форма топологии.
                              \en Topology shape. \~
  */
  RevolutionValues( double scalarValue1, double scalarValue2, int s )
    : SweptValuesAndSides( scalarValue1, scalarValue2 )
    , shape( s )
  {}
  /// \ru Конструктор копирования, на тех же поверхностях. \en Copy-constructor on the same surfaces.
  RevolutionValues( const RevolutionValues & other )
    : SweptValuesAndSides( other )
    , shape( other.shape )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  RevolutionValues( const RevolutionValues & other, MbRegDuplicate * ireg )
    : SweptValuesAndSides( other, ireg )
    , shape( other.shape )
  {}
  /// \ru Деструктор. \en Destructor.
  virtual ~RevolutionValues();

public:
  // \ru Это параметры вращения? \en This is rotation parameters?
  virtual bool IsRevolutionValues() const { return true; }

  // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool IsSame( const SweptValues & other, double accuracy ) const
  {
    const RevolutionValues * obj = dynamic_cast<const RevolutionValues *>( &other );
    if ( obj != NULL ) {
      if ( obj->shape == shape ) {
        if ( obj->SweptValuesAndSides::IsSame( *this, accuracy ) )
          return true;
      }
    }
    return false;
  }

public:
  /// \ru Оператор присваивания, на тех же поверхностях. \en Assignment operator on the same surfaces.
  RevolutionValues & operator = ( const RevolutionValues & other ) {
    *static_cast<SweptValuesAndSides*>(this) = *static_cast<const SweptValuesAndSides*>(&other);
    shape = other.shape;
    return *this;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( RevolutionValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры кинематической операции.
           \en Parameters of the sweeping operation. \~
  \details \ru Параметры операции движения образующей по направляющей кривой. \n
           \en The operation parameters of moving the generating curve along the spine curve. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS EvolutionValues : public SweptValues {
public:
  /** \brief \ru Способ переноса образующего контура вдоль направляющей.
             \en Moving method of generating contour along the spine curve. \~
    \details \ru Способ переноса образующего контура вдоль направляющей: \n
             parallel <= 0  - образующая переносится параллельно самой себе; \n
             parallel == 1  - образующая при переносе сохраняет исходный угол с направляющей; \n
             parallel >= 2  - плоскость образующей выставляется и сохраняется ортогональной направляющей. \n
             \en Moving method of generating contour along the spine curve: \n
             parallel <= 0  - generating curve is moved parallel to itself; \n
             parallel == 1  - generating curve when moving preserves initial angle with spine; \n
             parallel >= 2  - plane of generating curve is set and saved as orthogonal to spine. \n \~
  */
  int              parallel;
  // \ru Данные о функциях изменения образующих кривых вдоль напрвлябшей кривой (могут быть NULL). \en Data about changes of generating curves along the guide curve (can be NULL).
  double           range;   ///< \ru Эквидистантное смещение точек образующей кривой в конце траектории. \en The offset range of generating curve on the end of spine curve. 
  SPtr<MbFunction> scaling; ///< \ru Функция масштабирования образующей кривой. \en The fanction of curve scale. 
  SPtr<MbFunction> winding; ///< \ru Функция вращения образующей кривой. \en The fanction of curve rotation. 

public:

  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров кинематической операции для построения замкнутой оболочки
      без тонкой стенки с сохранением угла наклона.
             \en Constructor of sweeping operation parameters for construction of closed shell
      without the thin wall with keeping the angle inclination. \~
  */
  EvolutionValues()
    : SweptValues(      )
    , parallel   ( 1    )
    , range      ( 0.0  )
    , scaling    ( NULL )
    , winding    ( NULL )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  EvolutionValues( const EvolutionValues & other );
  /// \ru Деструктор. \en Destructor.
  virtual ~EvolutionValues();

public:
  // \ru Это параметры кинематики? \en This is "evolution" parameters?
  virtual bool      IsEvolutionValues() const { return true; }

  // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool      IsSame( const SweptValues & other, double accuracy ) const;
  // \ru Определить, являются ли объекты подобными. \en Determine whether the objects are similar. \~
  virtual bool      IsSimilar( const SweptValues & other ) const;
  // \ru Сделать объекты равным. \en Make objects equal. \~
  virtual bool      SetEqual ( const SweptValues & other );

  /// \ru Выдать функцию масштабирования образующей кривой. \en Get the fanction of curve scale. 
  double            GetRange() const { return range; }
  double &          SetRange() { return range; }
  void              SetRange( double r ) { range = r; }

  /** \brief \ru Добавить данные.
             \en Add data. \~
    \details \ru Добавить данные об изменении образующих контурах на поверхности вдоль образующей кривой.
             \en Add data about changes of generatig contours on the surface along the guide curve. \~
    \param[in] _scaling - \ru Масштабирование.
                          \en The scaling. \~
    \param[in] _winding - \ru Поворот.
                          \en The winding. \~
  */
  bool              AddData( MbFunction & _scaling, MbFunction & _winding );

  /// \ru Выдать функцию масштабирования образующей кривой. \en Get the fanction of curve scale. 
  const MbFunction* GetScaling() const { return scaling; }
  MbFunction *      SetScaling()       { return scaling; }

  /// \ru Выдать функцию вращения образующей кривой. \en Get the fanction of curve rotation. 
  const MbFunction* GetWinding() const { return winding; }
  MbFunction *      SetWinding()       { return winding; }

public:
  /// \ru Оператор присваивания. \en Assignment operator.
  EvolutionValues & operator = ( const EvolutionValues & other );

  KNOWN_OBJECTS_RW_REF_OPERATORS( EvolutionValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры операции построения тела по плоским сечениям.
           \en The operation parameters of constructing solid by lofted. \~
  \details \ru Параметры операции построения тела по плоским сечениям, заданных контурами. \n
           \en The parameters of constructing operation by lofted which are given by contours. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS LoftedValues : public SweptValues {
public:
  bool       closed;     ///< \ru Замкнутость трубки сечений. \en Closedness of tube.
  MbVector3D vector1;    ///< \ru Производная в начале. \en The derivative at the start.
  MbVector3D vector2;    ///< \ru Производная в конце. \en The derivative at the end.
  bool       setNormal1; ///< \ru Установлена нормаль в начале. \en The normal is set at the start.
  bool       setNormal2; ///< \ru Установлена нормаль в конце. \en The normal is set at the end.

public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор параметров операции по сечениям для построения замкнутой оболочки без тонкой стенки.
             \en Constructor of lofted operation parameters for construction of closed shell without the thin wall. \~
  */
  LoftedValues()
    : SweptValues (               )
    , closed      ( false         )
    , vector1     ( 0.0, 0.0, 0.0 )
    , vector2     ( 0.0, 0.0, 0.0 )
    , setNormal1  ( false         )
    , setNormal2  ( false         )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  LoftedValues( const LoftedValues & other )
    : SweptValues ( other            )
    , closed      ( other.closed     )
    , vector1     ( other.vector1    )
    , vector2     ( other.vector2    )
    , setNormal1  ( other.setNormal1 )
    , setNormal2  ( other.setNormal2 )
  {}
  /// \ru Оператор присваивания. \en Assignment operator.
  LoftedValues & operator = ( const LoftedValues & other )
  {
    SweptValues::Init( other );
    closed     = other.closed;
    vector1    = other.vector1;
    vector2    = other.vector2;
    setNormal1 = other.setNormal1;
    setNormal2 = other.setNormal2;
    return *this;
  }
  /// \ru Деструктор. \en Destructor.
  virtual ~LoftedValues();

public:
  // \ru Это параметры операции по сечениям? \en This is "lofted" parameters?
  virtual bool IsLoftedValues() const { return true; }

  // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool IsSame( const SweptValues & other, double accuracy ) const
  {
    const LoftedValues * obj = dynamic_cast<const LoftedValues *>( &other );
    if ( obj != NULL ) {
      if ( obj->closed == closed ) {
        if ( c3d::EqualVectors(vector1, obj->vector1, accuracy) && c3d::EqualVectors(vector2, obj->vector2, accuracy) ) {
          if ( obj->setNormal1 == setNormal1 && obj->setNormal2 == setNormal2 ) {
            if ( obj->SweptValues::IsSame(*this, accuracy) ) {
              return true;
            }
          }
        }
      }
    }
    return false;
  }

public:
  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D & matr );
  /// \ru Сдвинуть объект вдоль вектора. \en Move an object along a vector.
  void        Move     ( const MbVector3D & to );
  /// \ru Повернуть объект вокруг оси на заданный угол. \en Rotate an object at a given angle around an axis.
  void        Rotate   ( const MbAxis3D & axis, double ang );

  KNOWN_OBJECTS_RW_REF_OPERATORS( LoftedValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры ребра жёсткости.
           \en Parameters of a rib. \~
  \details \ru Параметры построения ребра жёсткости по кривой, задающей его форму. \n
           \en The construction parameters of rib by curve gives its shape. \n \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS RibValues : public SweptValues {
public:
  /** \brief \ru Сторона заполнения пространства телом ребра.
             \en The side to place the rib on. \~
    \details \ru С какой стороны от кривой располагается ребро. \n
             \en With which side of the curve is rib. \n \~
    \ingroup Build_Parameters
  */
  enum ExtrudeSide {
    es_Left  = 0,     ///< \ru Ребро выдавливается в левую сторону от кривой вдоль плоскости. \en Rib is extruded to the left side of the curve along the plane.
    es_Right,         ///< \ru Ребро выдавливается в правую сторону от кривой вдоль плоскости. \en Rib is extruded to the right side of the curve along the plane.
    es_Up,            ///< \ru Ребро выдавливается в сторону нормали плоскости. \en Rib is extruded to the side of the surface normal.
    es_Down,          ///< \ru Ребро выдавливается в сторону против нормали плоскости. \en Rib is extruded to the side opposite to the surface normal.
  };

public:
  double      angle1; ///< \ru Угол уклона плоскости в прямом направлении. \en Draft angle of the plane along the forward direction.
  double      angle2; ///< \ru Угол уклона плоскости в обратном направлении. \en Draft angle of the plane along the backward direction.
  ExtrudeSide side;   ///< \ru Сторона заполнения пространства телом ребра. \en The side to place the rib on.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  RibValues()
    : SweptValues(          )
    , angle1     ( 0.0      )
    , angle2     ( 0.0      )
    , side       ( es_Right )
  {}
  /// \ru Конструктор по толщинам, углам и стороне заполнения пространства. \en Constructor by thickness, angles and filling space.
  RibValues( double t1, double t2, double a1, double a2, int s )
    : SweptValues( t1, t2          )
    , angle1     ( a1              )
    , angle2     ( a2              )
    , side       ( (ExtrudeSide)s  )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  RibValues( const RibValues & other )
    : SweptValues( other        )
    , angle1     ( other.angle1 )
    , angle2     ( other.angle2 )
    , side       ( other.side   )
  {}
  /// \ru Деструктор. \en Destructor.
  virtual ~RibValues();

public:
  // \ru Это параметры операции ребра жесткости? \en This is "rib" parameters?
  virtual bool IsRibValues() const { return true; }

  // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool  IsSame( const SweptValues & other, double accuracy ) const
  {
    const RibValues * obj = dynamic_cast<const RibValues *>( &other );

    if ( obj != NULL ) {
      if ( obj->side == side ) {
        if ( ::fabs(obj->angle1 - angle1) < accuracy && ::fabs(obj->angle2 - angle2) < accuracy )
          return SweptValues::IsSame( *obj, accuracy );
      }
    }
    return false;
  }

public:
  /// \ru Функция копирования. \en Copy function.
  void          Init( const RibValues & other )
  {
    SweptValues::Init( other );
    angle1      = other.angle1;
    angle2      = other.angle2;
    side        = other.side;
  }
  /// \ru Оператор присваивания. \en Assignment operator.
  RibValues &   operator = ( const RibValues & other )
  {
    Init( other );
    return *this;
  }

  KNOWN_OBJECTS_RW_REF_OPERATORS( RibValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры ребра жёсткости листового тела.
           \en Parameters of a sheet metal rib. \~
  \details \ru Параметры построения ребра жёсткости листового тела по кривой, задающей его форму. \n
           \en The construction parameters of a sheet metal rib by curve gives its shape. \n \~
\ingroup Build_Parameters
*/
// ---
struct MATH_CLASS SheetRibValues: public RibValues {
public:
  double radRibConvex;   ///< \ru Радиус скругления выпуклой части ребра жесткости. \en Fillet radius of convex part of rib.
  double radSideConcave; ///< \ru Радиус скругления примыкания вогнутой части ребра жесткости к листовому телу. \en Fillet radius of connection of concave part of rib and metal sheet.

public:
  /// \ru Конструктор по умолчанию. \en Default constructor.
  SheetRibValues()
    : RibValues     (     )
    , radRibConvex  ( 0.0 )
    , radSideConcave( 0.0 )
  {}
  /// \ru Конструктор по параметрам. \en Constructor by parameters.
  SheetRibValues( double t1, double t2, double a1, double a2, int s, double rFilletRib, const double & rFilletSide )
    : RibValues     ( t1, t2, a1, a2, s   )
    , radRibConvex  ( ::fabs(rFilletRib)  )
    , radSideConcave( ::fabs(rFilletSide) )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  SheetRibValues( const SheetRibValues & other )
    : RibValues     ( other                )
    , radRibConvex  ( other.radRibConvex   )
    , radSideConcave( other.radSideConcave )
  {}
  /// \ru Деструктор. \en Destructor.
  virtual ~SheetRibValues();

public:
  // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool  IsSame( const SweptValues & other, double accuracy ) const
  {
    const SheetRibValues * obj = dynamic_cast<const SheetRibValues *>( &other );

    if ( obj != NULL ) {
      if ( (::fabs(radRibConvex - obj->radRibConvex) < accuracy) && (::fabs(radSideConcave - obj->radSideConcave) < accuracy) )
        return RibValues::IsSame( *obj, accuracy );
    }
    return false;
  }

public:
  /// \ru Функция копирования. \en Copy function.
  void        Init( const SheetRibValues & other )
  {
    RibValues::Init( other );
    radRibConvex = other.radRibConvex;
    radSideConcave = other.radSideConcave;
  }

  /// \ru Оператор присваивания. \en Assignment operator.
  SheetRibValues & operator = ( const SheetRibValues & other ) {
    Init( other );
    return *this;
  }

  /// \ru Преобразовать объект согласно матрице. \en Transform an object according to the matrix.
  void        Transform( const MbMatrix3D & matr );

  KNOWN_OBJECTS_RW_REF_OPERATORS( SheetRibValues ) // \ru Для работы со ссылками и объектами класса. \en For working with references and objects of the class.
};

//------------------------------------------------------------------------------
/** \brief \ru Параметры булевой операции выдавливания или вращения до объекта.
           \en The parameters of Boolean operation of extrusion or revolution to object. \~
  \details \ru Параметры булевой операции выдавливания или вращения до объекта. \n
    Используется при булевой операции исходного тела
    и построенной операции выдавливания или вращения двумерных контуров на поверхности.
           \en The parameters of Boolean operation of extrusion or revolution to object. \n
    Used in Boolean operation of initial solid
    and constructed operation of extrusion or revolution of two-dimensional contours on the surface. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbSweptLayout {
  /** \brief \ru Направление выдавливания (вращения).
             \en A direction of extrusion (revolution). \~
    \details \ru Направление выдавливания (вращения) по отношению к вектору выдавливания (оси вращения).
             \en The direction of extrusion relative to the extrusion vector. \~
  */
  enum Direction {
    ed_minus_minus = -2, ///< \ru В обратном направлении, для обеих строн. \en Along the backward direction, for both sides.
    ed_minus       = -1, ///< \ru В обратном направлении, для одной стороны. \en Along the backward direction, for one sides.
    ed_both        = 0,  ///< \ru В обоих направлениях. \en Along both directions.
    ed_plus        = 1,  ///< \ru В прямом направлении, для одной стороны. \en Along the forward direction, for one sides.
    ed_plus_plus   = 2,  ///< \ru В прямом направлении, для обеих сторон. \en Along the forward direction, for both sides.
  };
  Direction   direction; ///< \ru Направление выдавливания относительно вектора. \en The direction of extrusion relative to the vector.
  bool        skipUnion; ///< \ru Создавать новое тело (Не приклеивать к телу). \en Create a new solid.

protected:
  SPtr<const MbSurface> surface;  ///< \ru Поверхность, на которой размещена образующая. \en The surface, which contains the generating curve.

protected:
  /// \ru Конструктор. \en Constructor.
  MbSweptLayout( const MbSurface & surf, Direction dir ) : surface( &surf ), direction( dir ), skipUnion( false ) {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  MbSweptLayout( const MbSweptLayout & other ) : surface( other.surface ), direction( other.direction ), skipUnion( other.skipUnion ) {}
  /// \ru Деструктор. \en Destructor.
  virtual ~MbSweptLayout();
public:
  /// \ru Получить поверхность. \en Get the surface.
  const MbSurface & GetSurface() const { return *surface; }

  /// \ru Создавать новое тело (Не приклеивать к телу). \en Create a new solid.
  bool SkipUnion() const { return skipUnion; }
  /// \ru Создавать новое тело (Не приклеивать к телу). \en Create a new solid.
  void SkipUnion( bool su ) { skipUnion = su; }
public:
  /// \ru Это параметры выдавливания? \en This is extrusion parameters?  
  virtual bool IsExtrusionLayout() const { return false; }
  /// \ru Это параметры вращения? \en This is rotation parameters?
  virtual bool IsRevolutionLayout() const { return false; }
public:
  /// \ru Классификация точки относительно несущей поверхности. \en Classification point relative to the surface.
  MbeItemLocation PointRelative( const MbCartPoint3D & p ) const;
private:
  // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default.
  MbSweptLayout &        operator = ( const MbSweptLayout & );
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры булевой операции выдавливания до объекта.
           \en The parameters of Boolean operation of extrusion to object. \~
  \details \ru Параметры булевой операции выдавливания до объекта. \n
    Используется при булевой операции исходного тела
    и построенной операции выдавливания двумерных контуров на поверхности.
           \en The parameters of Boolean operation of extrusion to object. \n
    Used in Boolean operation of initial solid
    and constructed operation of extrusion of two-dimensional contours on the surface. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbExtrusionLayout : public MbSweptLayout {
  MbVector3D dirVector; ///< \ru Вектор выдавливания. \en An extrusion vector.
public:
  /// \ru Конструктор. \en Constructor.
  MbExtrusionLayout( const MbSurface & surf, Direction dir, const MbVector3D & dirVec ) : MbSweptLayout( surf, dir ), dirVector( dirVec ) {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  MbExtrusionLayout( const MbExtrusionLayout & other ) : MbSweptLayout( other ), dirVector( other.dirVector ) {}
  /// \ru Деструктор. \en Destructor.
  virtual ~MbExtrusionLayout();
public:
  /// \ru Это параметры выдавливания? \en This is extrusion parameters?  
  virtual bool IsExtrusionLayout() const { return true; }
private:
  // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default.
  void        operator = ( const MbExtrusionLayout & );
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры булевой операции вращения до объекта.
           \en The parameters of Boolean operation of revolution to object. \~
  \details \ru Параметры булевой операции вращения до объекта. \n
    Используется при булевой операции исходного тела
    и построенной операции вращения двумерных контуров на поверхности.
           \en The parameters of Boolean operation of revolution to object. \n
    Used in Boolean operation of initial solid
    and constructed operation of revolution of two-dimensional contours on the surface. \~
  \ingroup Build_Parameters
*/
// ---
struct MATH_CLASS MbRevolutionLayout : public MbSweptLayout {
  MbAxis3D revAxis; ///< \ru Ось вращения. \en An revolution axis.
public:
  /// \ru Конструктор. \en Constructor.
  MbRevolutionLayout( const MbSurface & surf, Direction dir, const MbAxis3D & rotAxis ) : MbSweptLayout( surf, dir ), revAxis( rotAxis ) {}
  /// \ru Конструктор копирования. \en Copy-constructor.
  MbRevolutionLayout( const MbRevolutionLayout & other ) : MbSweptLayout( other ), revAxis( other.revAxis ) {}
  /// \ru Деструктор. \en Destructor.
  virtual ~MbRevolutionLayout();
public:
  /// \ru Это параметры вращения? \en This is rotation parameters?
  virtual bool IsRevolutionLayout() const { return true; }
private:
  // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default.
  void        operator = ( const MbRevolutionLayout & );
};


#endif // __OP_SHELL_PARAMETERS_H
