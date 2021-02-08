////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Полигоны.
         \en Polygons. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MESH_POLYGON_H
#define __MESH_POLYGON_H


#include <templ_s_array.h>
#include <io_tape.h>
#include <mesh_primitive.h>
#include <mesh_float_point3d.h>
#include <mesh_float_point.h>
#include <mb_rect.h>


class  MATH_CLASS  MbPolyline;


////////////////////////////////////////////////////////////////////////////////
/** \brief \ru Полигон на числах double. 
           \en Polygon on double data. \~
  \details \ru Полигон представляет собой упорядоченное множество точек в пространстве, 
    последовательное соединение которых даёт ломаную линию, аппроксимирующую некоторый объект или часть объекта. \n
           \en Polygon is an ordered set of points in space, 
    sequential connection of these points produces polyline that approximates an object or part of an object. \n \~ 
  \ingroup Polygonal_Objects
*/
////////////////////////////////////////////////////////////////////////////////
class MATH_CLASS MbExactPolygon3D : public MbPolygon3D {
private :
  std::vector<MbCartPoint3D> points; ///< \ru Множество точек полигона. \en Array of points of a polygon. 

protected:
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию \en Declaration without implementation of the copy-constructor to prevent copying by default 
  MbExactPolygon3D( const MbExactPolygon3D & );
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  explicit MbExactPolygon3D( const MbExactPolygon3D &, MbRegDuplicate * ); 
public :
  /// \ru Конструктор без параметров. \en Constructor without parameters. 
  MbExactPolygon3D();
  /// \ru Деструктор \en Destructor 
  virtual ~MbExactPolygon3D();

public:

  // \ru Общие функции примитива. \en Common functions of the primitive. 
  virtual MbePrimitiveType IsA() const; // \ru Вернуть тип объекта \en Get the object type. 
  virtual MbExactPolygon3D &    Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Создать копию объекта \en Create a copy of the object 
  virtual void    Transform( const MbMatrix3D & );             // \ru Преобразовать полигон согласно матрице \en Transform polygon according to the matrix 
  virtual void    Move     ( const MbVector3D & );             // \ru Сдвиг полигона \en Translation of the polygon. 
  virtual void    Rotate   ( const MbAxis3D &, double angle ); // \ru Поворот полигона вокруг оси \en Rotation of the polygon around an axis 
  virtual void    AddYourGabaritTo( MbCube & ) const;        // \ru Расширить присланный габаритный куб так, чтобы он включал в себя данный объект. \en Extend given bounding box so that it encloses the given object.  
  virtual double  DistanceToPoint( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate distance to the point.  
  virtual double  DistanceToLine( const MbAxis3D &, double maxDistance, double & t ) const;  // \ru Вычислить расстояние до оси. \en Calculate the distance to the axis.  
  virtual void    GetProperties( MbProperties & );   // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & );   // \ru Записать свойства объекта. \en Set properties of the object. 

  // \ru \name Функции полигона. \en \name Functions of polygon.

  // \ru Выдать размер занимаемой памяти. \en Get the size of taken memory. 
  virtual size_t  SizeOf() const; 
  // \ru Зарезервировать место для полигона. \en Reserve memory for polygon. 
  virtual void    Reserve( size_t cnt )     { points.reserve( points.size() + cnt ); }
  // \ru Удалить лишнюю память. \en Free the unnecessary memory. 
  virtual void    Adjust()                  { 
                                              #ifdef STANDARD_C11
                                              points.shrink_to_fit(); 
                                              #endif
                                            } 
  // \ru Очистить полигон удалив все точки. \en Clear the polygon by deleting all the points. 
  virtual void    Flush();
  // \ru Выдать количество точек. \en Get count of points. 
  virtual size_t  Count() const { return points.size(); } 
  // \ru Добавить точку в конец полигона. \en Add point to the end of the polygon. 
  virtual void    AddPoint( const MbCartPoint3D  & dpnt );
  // \ru Добавить точку в конец полигона. \en Add point to the end of the polygon. 
  virtual void    AddPoint( const MbFloatPoint3D & fpnt );

  /// \ru Выдать точку по её номеру. \en Get point by its index. 
  virtual void    GetPoint( size_t i, MbCartPoint3D & dp ) const;
  /// \ru Выдать точку по её номеру. \en Get point by its index. 
  virtual void    GetPoint( size_t i, MbFloatPoint3D & fp ) const;

  /// \ru Установить точку с номером. \en Set point by index. 
  virtual void    SetPoint( size_t i, MbCartPoint3D & pnt ) { points[i] = pnt; }

          /// \ru Установить точку с номером. \en Set point by index. 
          template <class Point>
          void    SetPoint( size_t i, Point & pnt ) { points[i].x = (float)pnt.x; points[i].y = (float)pnt.y; points[i].z = (float)pnt.z; cube.SetEmpty(); }
          /// \ru Выдать точку по её номеру. \en Get point by its index. 
          template <class Point>
          void    GetPoint( size_t i, Point & pnt ) const { pnt.x = points[i].x; pnt.y = points[i].y; pnt.z = points[i].z; }

          /// \ru Выдать точку по её номеру. \en Get point by its index. 
  const   MbCartPoint3D & GetPoint( size_t i ) const { return points[i]; }

          /// \ru Выдать все точки полигона. \en Get all the points of the polygon. 
          template<class PointsVector>
          void    GetPoints( PointsVector & pnts ) const
          {
            size_t cnt = points.size();
            pnts.clear();
            pnts.reserve( cnt );
            for ( size_t k = 0; k < cnt; k++ ) {
              pnts.push_back( points[k] );
            }
          }
  // \ru Проверить, лежат ли точки полигона в одной плоскости c заданной точностью metricAccuracy. Если да, то инициализировать плоскость plane.
  // \en Check whether all points of polygon lie on the same plane with the given metricAccuracy accuracy. If so, then initialize 'plane' plane. \~
  virtual bool    IsPlanar( MbPlacement3D & plane, double metricAccuracy = Math::metricRegion ) const;
  /// \ru Если точки полигона лежат в одной плоскости, то инициализировать plane и заполнить полигон poly. \en If points of polygon lie on the same plane, then initialize 'plane' and fill the 'poly' polygon. 
  virtual bool    GetPlanePolygon( MbPlacement3D & plane, MbPolygon & poly ) const;

  // \ru Проверить наличие точек в объекте. \en Check existence of points in object. 
  virtual bool    IsComplete() const { return (points.size() > 0); }

  /// \ru Добавить к полигону полигон с удалением совпадающих точек стыка. \en Add a polygon to the polygon with removing the coincident points of joint. 
  virtual void    AddPolygon( const MbPolygon3D & other );
  /// \ru Добавить к полигону полигон с удалением совпадающих точек стыка. \en Add a polygon to the polygon with removing the coincident points of joint. 
  virtual void    operator += ( const MbPolygon3D & other );
  /// \ru Являются ли объекты равными? \en Determine whether objects are equal. 
  virtual bool    IsSame( const MbPolygon3D & other, double eps ) const;
  // \ru Инициировать по другому полигону. \en Init by other polygon. 
  virtual void    Init( const MbPolygon3D & other );

  /// \ru Создать ломаную по полигону. \en Create a polyline on the base of the polygon. 
  virtual MbPolyline3D * CreatePolyline() const;

  /** \} */

          // \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
          const   MbCartPoint3D * GetAddr() const { return &(points[0]); }

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation, to prevent an assignment by default. 
          void    operator = ( const MbExactPolygon3D & );

  DECLARE_NEW_DELETE_CLASS( MbExactPolygon3D )
  DECLARE_NEW_DELETE_CLASS_EX( MbExactPolygon3D )
  KNOWN_OBJECTS_RW_REF_OPERATORS_EX( MbExactPolygon3D, MATH_FUNC_EX );
  KNOWN_OBJECTS_RW_PTR_OPERATORS_EX( MbExactPolygon3D, MATH_FUNC_EX );
}; // MbExactPolygon3D


////////////////////////////////////////////////////////////////////////////////
/** \brief \ru Полигон на числах float. 
           \en Polygon on float data. \~
  \details \ru Полигон представляет собой упорядоченное множество точек в пространстве, 
    последовательное соединение которых даёт ломаную линию, аппроксимирующую некоторый объект или часть объекта. \n
           \en Polygon is an ordered set of points in space, 
    sequential connection of these points produces polyline that approximates an object or part of an object. \n \~ 
  \ingroup Polygonal_Objects
*/
////////////////////////////////////////////////////////////////////////////////
class MATH_CLASS MbFloatPolygon3D : public MbPolygon3D {
private :
  std::vector<MbFloatPoint3D> points; ///< \ru Множество точек полигона. \en Array of points of a polygon. 

protected:
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию \en Declaration without implementation of the copy-constructor to prevent copying by default 
  MbFloatPolygon3D( const MbFloatPolygon3D & );
  /// \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  explicit MbFloatPolygon3D( const MbFloatPolygon3D &, MbRegDuplicate * ); 
public :
  /// \ru Конструктор без параметров. \en Constructor without parameters. 
  MbFloatPolygon3D();
  /// \ru Деструктор \en Destructor 
  virtual ~MbFloatPolygon3D();

public:

  // \ru Общие функции примитива. \en Common functions of the primitive. 
  virtual MbePrimitiveType IsA() const; // \ru Вернуть тип объекта \en Get the object type. 
  virtual MbFloatPolygon3D &    Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Создать копию объекта \en Create a copy of the object 
  virtual void    Transform( const MbMatrix3D & );             // \ru Преобразовать полигон согласно матрице \en Transform polygon according to the matrix 
  virtual void    Move     ( const MbVector3D & );             // \ru Сдвиг полигона \en Translation of the polygon. 
  virtual void    Rotate   ( const MbAxis3D &, double angle ); // \ru Поворот полигона вокруг оси \en Rotation of the polygon around an axis 
  virtual void    AddYourGabaritTo( MbCube & ) const;        // \ru Расширить присланный габаритный куб так, чтобы он включал в себя данный объект. \en Extend given bounding box so that it encloses the given object.  
  virtual double  DistanceToPoint( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate distance to the point.  
  virtual double  DistanceToLine( const MbAxis3D &, double maxDistance, double & t ) const;  // \ru Вычислить расстояние до оси. \en Calculate the distance to the axis.  
  virtual void    GetProperties( MbProperties & );   // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & );   // \ru Записать свойства объекта. \en Set properties of the object. 

  // \ru \name Функции полигона. \en \name Functions of polygon.

  // \ru Выдать размер занимаемой памяти. \en Get the size of taken memory. 
  virtual size_t  SizeOf() const; 
  // \ru Зарезервировать место для полигона. \en Reserve memory for polygon. 
  virtual void    Reserve( size_t cnt )     { points.reserve( points.size() + cnt ); }
  // \ru Удалить лишнюю память. \en Free the unnecessary memory. 
  virtual void    Adjust()                  {
                                              #ifdef STANDARD_C11  
                                              points.shrink_to_fit(); 
                                              #endif
                                            } 
  // \ru Очистить полигон удалив все точки. \en Clear the polygon by deleting all the points. 
  virtual void    Flush();
  // \ru Выдать количество точек. \en Get count of points. 
  virtual size_t  Count() const { return points.size(); } 
  // \ru Добавить точку в конец полигона. \en Add point to the end of the polygon. 
  virtual void    AddPoint( const MbCartPoint3D  & dpnt );
  // \ru Добавить точку в конец полигона. \en Add point to the end of the polygon. 
  virtual void    AddPoint( const MbFloatPoint3D & fpnt );

  /// \ru Выдать точку по её номеру. \en Get point by its index. 
  virtual void    GetPoint( size_t i, MbCartPoint3D & dp ) const;
  /// \ru Выдать точку по её номеру. \en Get point by its index. 
  virtual void    GetPoint( size_t i, MbFloatPoint3D & fp ) const;

  /// \ru Установить точку с номером. \en Set point by index. 
  virtual void    SetPoint( size_t i, MbCartPoint3D & pnt ) { points[i].x = (float)pnt.x; points[i].y = (float)pnt.y; points[i].z = (float)pnt.z; cube.SetEmpty(); }

          /// \ru Установить точку с номером. \en Set point by index. 
          template <class Point>
          void    SetPoint( size_t i, Point & pnt ) { points[i].x = (float)pnt.x; points[i].y = (float)pnt.y; points[i].z = (float)pnt.z; cube.SetEmpty(); }
          /// \ru Выдать точку по её номеру. \en Get point by its index. 
          template <class Point>
          void    GetPoint( size_t i, Point & pnt ) const { pnt.x = points[i].x; pnt.y = points[i].y; pnt.z = points[i].z; }

          /// \ru Выдать точку по её номеру. \en Get point by its index. 
  const   MbFloatPoint3D & GetPoint( size_t i ) const { return points[i]; }

          /// \ru Выдать все точки полигона. \en Get all the points of the polygon. 
          template<class PointsVector>
          void    GetPoints( PointsVector & pnts ) const
          {
            size_t cnt = points.size();
            pnts.clear();
            pnts.reserve( cnt );
            for ( size_t k = 0; k < cnt; k++ ) {
              pnts.push_back( points[k] );
            }
          }
  // \ru Проверить, лежат ли точки полигона в одной плоскости c заданной точностью metricAccuracy. Если да, то инициализировать плоскость plane.
  // \en Check whether all points of polygon lie on the same plane with the given metricAccuracy accuracy. If so, then initialize 'plane' plane. \~
  virtual bool    IsPlanar( MbPlacement3D & plane, double metricAccuracy = Math::metricRegion ) const;
  /// \ru Если точки полигона лежат в одной плоскости, то инициализировать plane и заполнить полигон poly. \en If points of polygon lie on the same plane, then initialize 'plane' and fill the 'poly' polygon. 
  virtual bool    GetPlanePolygon( MbPlacement3D & plane, MbPolygon & poly ) const;

  // \ru Проверить наличие точек в объекте. \en Check existence of points in object. 
  virtual bool    IsComplete() const { return (points.size() > 0); }

  /// \ru Добавить к полигону полигон с удалением совпадающих точек стыка. \en Add a polygon to the polygon with removing the coincident points of joint. 
  virtual void    AddPolygon( const MbPolygon3D & other );
  /// \ru Добавить к полигону полигон с удалением совпадающих точек стыка. \en Add a polygon to the polygon with removing the coincident points of joint. 
  virtual void    operator += ( const MbPolygon3D & other );
  /// \ru Являются ли объекты равными? \en Determine whether objects are equal. 
  virtual bool    IsSame( const MbPolygon3D & other, double eps ) const;
  // \ru Инициировать по другому полигону. \en Init by other polygon. 
  virtual void    Init( const MbPolygon3D & other );

  /// \ru Создать ломаную по полигону. \en Create a polyline on the base of the polygon. 
  virtual MbPolyline3D * CreatePolyline() const;

  /** \} */

          // \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
          const   MbFloatPoint3D * GetAddr() const { return &(points[0]); }

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation, to prevent an assignment by default. 
          void    operator = ( const MbFloatPolygon3D & );

  DECLARE_NEW_DELETE_CLASS( MbFloatPolygon3D )
  DECLARE_NEW_DELETE_CLASS_EX( MbFloatPolygon3D )
  KNOWN_OBJECTS_RW_REF_OPERATORS_EX( MbFloatPolygon3D, MATH_FUNC_EX );
  KNOWN_OBJECTS_RW_PTR_OPERATORS_EX( MbFloatPolygon3D, MATH_FUNC_EX );
}; // MbFloatPolygon3D


////////////////////////////////////////////////////////////////////////////////
/** \brief \ru Двумерный полигон.
           \en Two-dimensional polygon. \~
  \details \ru Двумерный полигон представляет собой упорядоченное множество точек в 
  двумерном пространстве, последовательное соединение которых даёт ломаную линию, 
  аппроксимирующую некоторый двумерный объект. \n
           \en Two-dimensional polygon is an ordered set of points in 
  two-dimensional space, sequential connection of them produces a polyline 
  that approximate a two-dimensional object. \n \~
  \ingroup Polygonal_Objects
*/
////////////////////////////////////////////////////////////////////////////////
class MATH_CLASS MbPolygon : public MbRefItem {
private:
  SArray<MbFloatPoint> points;  ///< \ru Множество точек полигона. \en Array of points of a polygon. 
  double               sag;     ///< \ru Стрелка прогиба, с которой рассчитан полигон. \en Sag used for calculation of a polygon. 
  mutable MbRect       rect;    ///< \ru Габарит полигона (не записывается в поток и не читаeтся). \en Bounding box of polygon (not read from stream and not written to stream). 
  mutable double       length;  ///< \ru Длина полигона   (не записывается в поток и не читаeтся). \en Length of a polygon (not read from stream and not written to stream). 

public :
  /// \ru Конструктор без параметров. \en Constructor without parameters. 
  MbPolygon();
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbPolygon( const MbPolygon & );
  /// \ru Деструктор. \en Destructor. 
  ~MbPolygon();

public:
  /// \ru Обеспечить резерв памяти под additionalSpace элементов. \en Reserve memory for additionalSpace elements. 
  void    Reserve( size_t additionalSpace ); 
  /// \ru Установить максимальное из приращений. \en Set the maximum increment. 
  void    SetMaxDelta( uint16 delta ); 
  /// \ru Удалить лишнюю память. \en Free the unnecessary memory. 
  void    Adjust(); 
  /// \ru Вернуть количество точек. \en Get count of points. 
  size_t  Count() const { return points.size(); } 

  /// \ru HardFlush очистить полигон (освободить всю память). \en HardFlush clear the polygon (free all the memory). 
  void    HardFlushPoints();   
  /// \ru Flush очистить полигон \en Flush clear polygon 
  void    SimpleFlushPoints(); 

  /// \ru Добавить новую точку. \en Add a new point. 
  void    AddPoint   ( double x, double y );  
  /// \ru Добавить новую точку. \en Add a new point. 
  void    AddPoint   ( const MbCartPoint & ); 
  /// \ru Добавить полигон. \en Add a polygon. 
  void    AddPolygon ( const MbPolygon & );
  /// \ru Удалить точку. \en Remove the point. 
  bool    RemovePoint( size_t index );

  /// \ru Выдать очередную точку. \en Get the next point. 
  bool    GetPoint ( size_t i, MbCartPoint &  ) const;
  /// \ru Выдать очередную точку. \en Get the next point. 
  bool    GetPoint ( size_t i, MbFloatPoint & ) const;
  /// \ru Изменить точку. \en Change a point. 
  bool    SetPoint ( size_t i, const MbCartPoint & );
  /// \ru Изменить точку. \en Change a point. 
  bool    SetPoint ( size_t i, const MbFloatPoint & );
  /// \ru Выдать очередную точку. \en Get the next point. 
  bool    GetCoords( size_t i, double & x, double & y ) const;
  /// \ru Заполнить контейнер. \en Fill the container. 
  void    GetPoints( SArray<MbCartPoint>  & ) const;
  /// \ru Заполнить контейнер. \en Fill the container. 
  void    GetPoints( SArray<MbFloatPoint> & ) const;
  /// \ru Выдать точку. \en Get point. 
  const MbFloatPoint & GetPoint( size_t i ) const { return points[i]; } 

  /// \ru Сдвинyть полигон. \en Move the polygon. 
  void    Move  ( const MbVector & ); 
  /// \ru Повернуть полигон вокруг точки. \en Rotate a polygon about a point. 
  void    Rotate( const MbCartPoint &, const MbDirection & ); 
  /// \ru Преобразовать полигон согласно матрице. \en Transform a polygon according to the matrix. 
  void    Transform( const MbMatrix & ); 
  /// \ru Инверсия направления. \en Inverse the direction. 
  void    Inverse();

  /// \ru Вернуть габарит. \en Get bounding box. 
  const MbRect & GetRect() const;
  /// \ru Вернуть длину полигона. \en Get length of the polygon. 
  double  GetLength() const;
  /// \ru Получить стрелку прогиба. \en Get sag. 
  double  GetSag() const     { return sag; }
  /// \ru Установить стрелку прогиба. \en Set sag. 
  void    SetSag( double s ) { sag = s;    }
  /// \ru Является ли полигон выпуклым. \en Whether the polygon is convex. 
  bool    IsConvex() const;
  /// \ru Площадь полигона. \en Area of the polygon. 
  double  Area() const;

  void    operator = ( const MbPolygon & );

  /// \ru Создать ломаную на основе полигона. \en Create a polyline from the polygon. 
  MbPolyline *    ConvertToPolyline() const; 

  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  const MbFloatPoint * GetAddr() const { return points.GetAddr(); }

private:
  // \ru Рассчитать габарит. \en Calculate bounding box. 
  void    CalculateRect() const;
  // \ru Рассчитать длину полигона. \en Calculate length of the polygon. 
  void    CalculateLength() const;
  // \ru Сбросить временные данные. \en Reset temporary data. 
  void    ResetMutable() const;

  KNOWN_OBJECTS_RW_PTR_OPERATORS_EX( MbPolygon, MATH_FUNC_EX )
  DECLARE_NEW_DELETE_CLASS( MbPolygon )
  DECLARE_NEW_DELETE_CLASS_EX( MbPolygon )
};


#endif // __MESH_POLYGON_H
