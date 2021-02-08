////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Tриангуляция.
         \en Triangulation. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MESH_GRID_H
#define __MESH_GRID_H


#include <mesh_primitive.h>
#include <templ_s_array.h>
#include <mesh_float_point3d.h>
#include <mesh_float_point.h>
#include <mesh_triangle.h>
#include <mb_data.h>


class  MATH_CLASS MbRect;


////////////////////////////////////////////////////////////////////////////////
/** \brief \ru Триангуляция на числах double.
           \en Triangulation on double data. \~
  \details \ru Триангуляция представляет собой набор треугольных и четырёхугольных пластин, стыкующихся друг с другом по общим сторонам.\n
      Триангуляция состоит из согласованных наборов точек, нормалей, параметров триангулируемой поверхности и наборов треугольников и четырехугольников.
    Каждый треугольник - это три номера из набора точек, определяющих вершины треугольника, каждый четырехугольник - это четыре номера из набора точек, определяющих вершины четырехугольника. \n
           \en Triangulation represents a set of triangular and quadrangular plates which are joined to each other by their common sides.\n
      The triangulation consists of a sets of points, normals, surface parameters and a sets of triangles and quadrangles.
    The triangle is represented as three indices from the set of points defining vertices of triangle, the quadrangle is represented as four indices from the set of points defining vertices of quadrangle.\n \~
  \ingroup Polygonal_Objects
*/
////////////////////////////////////////////////////////////////////////////////
class MATH_CLASS MbExactGrid : public MbGrid {
private:
  std::vector<MbCartPoint3D>   points;      ///< \ru Множество контрольных точек триангуляции (согласовано с множеством параметров, если последнее не пустое, или пусто, если не пусто множество параметров). \en Set of control points of triangulation (synchronized with set of parameters if the last is not empty, or empty if the set of parameters isn't empty). 
  std::vector<MbVector3D>      normals;     ///< \ru Множество нормалей в контрольных точках согласовано с множеством контрольных точек. \en Set of normals at control points is synchronized with the set of control points. 
  std::vector<MbCartPoint>     params;      ///< \ru Множество параметров - двумерных точек на параметрической области триангулируемой поверхности (может быть пустым). \en Set of parameters of two-dimensional points in parametric domain of surface being triangulated(can be empty). 
  std::vector<uint32>          escorts;     ///< \ru Множество значений для дополнительной информации в точках. \en The set of values for additional information of points. 

protected:
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en The copy constructor without implementation prevents from copying by default. 
  MbExactGrid( const MbExactGrid & init );
  // \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  explicit MbExactGrid( const MbExactGrid & init, MbRegDuplicate * iReg ); 
public:
  // \ru Конструктор без параметров. \en Constructor without parameters. 
  MbExactGrid();
  // \ru Деструктор. \en Destructor. 
  virtual ~MbExactGrid();

public:

  // \ru \name Общие функции примитива. \en \name Common functions of primitive.

  virtual MbePrimitiveType IsA() const; // \ru Тип объекта. \en A type of an object. 
  virtual MbExactGrid & Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Создать копию объекта. \en Create a copy of the object. 
  virtual void    Transform( const MbMatrix3D & matr );             // \ru Преобразовать сетку согласно матрице. \en Transform mesh according to the matrix. 
  virtual void    Move     ( const MbVector3D & to );               // \ru Сдвиг сетки. \en Move mesh. 
  virtual void    Rotate   ( const MbAxis3D & axis, double angle ); // \ru Поворот сетки вокруг оси. \en Rotation of mesh about an axis. 
  virtual void    AddYourGabaritTo( MbCube & r ) const;             // \ru Расширить присланный габаритный куб так, чтобы он включал в себя данный объект. \en Extend given bounding box so that it encloses the given object.  
  virtual double  DistanceToPoint( const MbCartPoint3D & pnt ) const; // \ru Вычислить расстояние до точки. \en Calculate distance to point.  
  virtual double  DistanceToLine( const MbAxis3D & axis, double maxDistance, double & t ) const;  // \ru Вычислить расстояние до оси. \en Calculate the distance to an axis.  
  virtual void    GetProperties( MbProperties & );        // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & );  // \ru Записать свойства объекта. \en Set properties of the object. 

  // \ru Выдать количество точек. \en Get the number of points. 
  virtual size_t  PointsCount()  const { return points.size();  }
  // \ru Выдать количество нормалей. \en Get the number of normals. 
  virtual size_t  NormalsCount() const { return normals.size(); }
  // \ru Выдать количество параметров. \en Get the number of parameters. 
  virtual size_t  ParamsCount()  const { return params.size();  } 
  // \ru Выдать количество значений. \en Get count of values. 
  virtual size_t  EscortsCount() const { return escorts.size(); } 
  // \ru Выдать количество точек минус 1 (максимальный индекс). \en Get the number of points minus one (maximal index). 
  virtual ptrdiff_t PointsMaxIndex()  const { ptrdiff_t n = points.size(); return ( n - 1 ); }
  // \ru Выдать количество нормалей минус 1 (максимальный индекс). \en Get the number of normals minus one (maximal index). 
  virtual ptrdiff_t NormalsMaxIndex() const { ptrdiff_t n = normals.size(); return ( n - 1 ); }
  // \ru Выдать количество параметров минус 1 (максимальный индекс). \en Get the number of parameters minus one (maximal index). 
  virtual ptrdiff_t ParamsMaxIndex()  const { ptrdiff_t n = params.size(); return ( n - 1 ); }

  // \ru Добавить в триангуляцию параметры, точку и нормаль триангулируемой поверхности в точке. \en Add parameters, point and normal of triangulated surface at point to triangulation. 
  virtual void    AddPoint ( const MbCartPoint   & p2D, const MbCartPoint3D & p3D, const MbVector3D & n3D );
  // \ru Добавить в триангуляцию параметры и точку. \en Add parameters and a point to triangulation. 
  virtual void    AddPoint ( const MbCartPoint   & p2D, const MbCartPoint3D & p3D );
  // \ru Добавить в триангуляцию точку и нормаль в точке. \en Add a point and normal at the point to triangulation. 
  virtual void    AddPoint ( const MbCartPoint3D & p3D, const MbVector3D & n3D );
  // \ru Добавить в триангуляцию точку. \en Add a point to triangulation. 
  virtual void    AddPoint ( const MbCartPoint3D & p3D );
  // \ru Добавить в триангуляцию нормаль. \en Add a normal to triangulation. 
  virtual void    AddNormal( const MbVector3D    & n3D );
  // \ru Добавить в триангуляцию параметры триангулируемой поверхности. \en Add parameters of triangulated surface to triangulation. 
  virtual void    AddParam ( const MbCartPoint   & p2D );

  // \ru Добавить в триангуляцию параметры, точку и нормаль триангулируемой поверхности в точке. \en Add parameters, point and normal of triangulated surface at point to triangulation. 
  virtual void    AddPoint ( const MbFloatPoint  & p2D, const MbFloatPoint3D & p3D, const MbFloatVector3D & n3D );
  // \ru Добавить в триангуляцию параметры и точку. \en Add parameters and a point to triangulation. 
  virtual void    AddPoint ( const MbFloatPoint  & p2D, const MbFloatPoint3D & p3D );
  // \ru Добавить в триангуляцию точку и нормаль в точке. \en Add a point and normal at the point to triangulation. 
  virtual void    AddPoint ( const MbFloatPoint3D & p3D, const MbFloatVector3D & n3D );
  // \ru Добавить в триангуляцию точку. \en Add a point to triangulation. 
  virtual void    AddPoint( const MbFloatPoint3D & p3D );
  // \ru Добавить в триангуляцию нормаль. \en Add a normal to triangulation. 
  virtual void    AddNormal( const MbFloatVector3D & n3D );
  // \ru Добавить в триангуляцию параметры триангулируемой поверхности. \en Add parameters of triangulated surface to triangulation. 
  virtual void    AddParam( const MbFloatPoint   & p2D );

          // \ru Добавить в триангуляцию точки. \en Add points to triangulation. 
          template <class PointsVector>
          void    AddPoints ( const PointsVector & pnts ) {
            size_t addCnt = pnts.size();
            points.reserve( points.size() + addCnt );
            for ( size_t k = 0; k < addCnt; k++ )
              points.push_back( pnts[k] );
          }
          // \ru Добавить в триангуляцию нормали. \en Add normals to triangulation. 
          template <class NormalsVector>
          void    AddNormals( const NormalsVector & nrms ) {
            size_t addCnt = nrms.size();
            normals.reserve( normals.size() + addCnt );
            for ( size_t k = 0; k < addCnt; k++ )
              normals.push_back( nrms[k] );
          }
          // \ru Добавить в триангуляцию параметры триангулируемой поверхности. \en Add parameters of triangulated surface to triangulation.
          template <class ParamsVector>
          void    AddParams( const ParamsVector & prms ) {
            size_t addCnt = prms.size();
            params.reserve( params.size() + addCnt );
            for ( size_t k = 0; k < addCnt; k++ )
              params.push_back( prms[k] );
          }

  // \ru Добавить в коллекцию данных. \en Add scores to collection. 
  virtual void    AddEscorts( const std::vector<uint32> & scores )  { escorts.insert(escorts.end(), scores.begin(), scores.end()); }

  // \ru Выдать точку по её номеру. \en Get point by its index. 
  virtual void    GetPoint ( size_t i, MbCartPoint3D  & p ) const;
  // \ru Выдать нормаль по её номеру. \en Get normal by its index. 
  virtual void    GetNormal( size_t i, MbVector3D     & n ) const;
  // \ru Выдать параметр по его номеру. \en Get parameter by its index. 
  virtual void    GetParam ( size_t i, MbCartPoint    & p ) const;
  // \ru Выдать дополнительную информацию по её номеру. \en Get additional information by its index. 
  virtual const   uint32 & GetEscort( size_t i ) const;

  /// \ru Выдать точку по её номеру. \en Get point by its index. 
  virtual void    GetPoint ( size_t i, MbFloatPoint3D  & p ) const;
  /// \ru Выдать нормаль по её номеру. \en Get normal by its index. 
  virtual void    GetNormal( size_t i, MbFloatVector3D & n ) const;
  /// \ru Выдать параметр по его номеру. \en Get parameter by its index. 
  virtual void    GetParam ( size_t i, MbFloatPoint    & p ) const;

          // \ru Выдать точку с заданным номером. \en Get point by the given index. 
          const   MbCartPoint3D  & GetPoint ( size_t i ) const;
          // \ru Выдать нормаль с заданным номером. \en Get normal by the given index. 
          const   MbVector3D & GetNormal( size_t i ) const;
          // \ru Выдать параметр с заданным номером. \en Get parameter by the given index. 
          const   MbCartPoint    & GetParam ( size_t i ) const;

  // \ru Установить точку с заданным номером. \en Set point by the given index. 
  virtual void    SetPoint ( size_t i, const MbCartPoint3D & p );
  // \ru Установить нормаль с заданным номером. \en Set normal by the given index. 
  virtual void    SetNormal( size_t i, const MbVector3D    & n );
  // \ru Установить параметр с заданным номером. \en Set parameter by the given index. 
  virtual void    SetParam ( size_t i, const MbCartPoint   & p );
  // \ru Установить дополнительную информацию по её номеру. \en Set additional information by its index. 
  virtual void    SetEscort( size_t i, const uint32 & e );

  // \ru Удалить точку с заданным номером. \en Delete point by the given index. 
  virtual void    PointRemove ( size_t i );
  // \ru Удалить нормаль с заданным номером. \en Delete normal by the given index. 
  virtual void    NormalRemove( size_t i );
  // \ru Удалить параметры поверхности с заданным номером. \en Delete parameters of surface by the given index. 
  virtual void    ParamRemove ( size_t i );

  // \ru Удалить точки. \en Delete points. 
  virtual void    PointsDelete();
  // \ru Удалить нормали. \en Delete normal. 
  virtual void    NormalsDelete();
  // \ru Удалить параметры. \en Delete papams. 
  virtual void    PapamsDelete();
  // \ru Удалить дополнительную информацию. \en Delete additional information. 
  virtual void    EscortsDelete();

  /// \ru Инвертировать нормали. \en Invert normals. 
  virtual void    NormalsInvert();

  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) параметры поверхности. \en Get parameters of surface for i-th triangle in general numbering (with strips). 
  virtual bool    GetTriangleParams   ( size_t i, MbCartPoint & r0, MbCartPoint & r1, MbCartPoint & r2 ) const;
  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) точки вершин. \en Get points of vertices for i-th triangle in general numbering (with strips). 
  virtual bool    GetTrianglePoints   ( size_t i, MbCartPoint3D & p0, MbCartPoint3D & p1, MbCartPoint3D & p2 ) const;
  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) точки вершин. \en Get points of vertices for i-th triangle in general numbering (with strips). 
  virtual bool    GetTrianglePoints   ( size_t i, MbFloatPoint3D & p0, MbFloatPoint3D & p1, MbFloatPoint3D & p2 ) const;
  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) нормали в вершинах. \en Get normals at vertices for i-th triangle in general numbering (with strips). 
  virtual bool    GetTriangleNormals  ( size_t i, MbVector3D & n0, MbVector3D & n1, MbVector3D & n2 ) const;
  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) нормали в вершинах. \en Get normals at vertices for i-th triangle in general numbering (with strips). 
  virtual bool    GetTriangleNormals  ( size_t i, MbFloatVector3D & n0, MbFloatVector3D & n1, MbFloatVector3D & n2 ) const;

  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) параметры поверхности. \en Get parameters of surface for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadrangleParams ( size_t i, MbCartPoint & r0, MbCartPoint & r1, MbCartPoint & r2, MbCartPoint & r3 ) const;
  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) точки вершин. \en Get points of vertices for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadranglePoints ( size_t i, MbCartPoint3D & p0, MbCartPoint3D & p1, MbCartPoint3D & p2, MbCartPoint3D & p3 ) const;
  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) точки вершин. \en Get points of vertices for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadranglePoints ( size_t i, MbFloatPoint3D & p0, MbFloatPoint3D & p1, MbFloatPoint3D & p2, MbFloatPoint3D & n3 ) const;
  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) нормали в вершинах. \en Get normals at vertices for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadrangleNormals( size_t i, MbVector3D & n0, MbVector3D & n1, MbVector3D &n2, MbVector3D & n3 ) const;
  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) нормали в вершинах. \en Get normals at vertices for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadrangleNormals( size_t i, MbFloatVector3D & n0, MbFloatVector3D & n1, MbFloatVector3D & n2, MbFloatVector3D & n3 ) const;

  // \ru Выдать первую нормаль для плоской триангуляции, если количество точек больше количества нормалей (только для плоской триангуляции). \en Get first normal for flat triangulation if count of points is greater than count of normals (only for planar triangulation). 
  virtual bool    GetSingleNormal   ( MbVector3D & ) const;
  // \ru Выдать первую нормаль для плоской триангуляции, если количество точек больше количества нормалей (только для плоской триангуляции). \en Get first normal for flat triangulation if count of points is greater than count of normals (only for planar triangulation). 
  virtual bool    GetSingleNormal   ( MbFloatVector3D & ) const;
  // \ru Если количество точек больше количества нормалей, то добавить недостающие нормали (только для плоской триангуляции). \en If count of points is greater than count of normals, then add missing normals (only for planar triangulation). 
  virtual void    SynchronizNormals ();

          // \ru Выдать контейнер параметров. \en Get the container of parameters. 
          template <class ParamsVector>
          void    GetParams( ParamsVector & paramsVector )  const { 
            paramsVector.reserve( paramsVector.size() + params.size() );
            for ( size_t i = 0, iCount = params.size(); i < iCount; i++ )
              paramsVector.push_back( params[i] );
          }
          // \ru Выдать контейнер точек. \en Get the container of points. 
          template <class PointsVector>
          void    GetPoints( PointsVector & pointsVector )  const {
            pointsVector.reserve( pointsVector.size() + points.size() );
            for ( size_t i = 0, iCount = points.size(); i < iCount; i++ )
              pointsVector.push_back( points[i] );
          }
          // \ru Выдать контейнер нормалей. \en Get the container of normals. 
          template <class NormalsVector>
          void    GetNormals( NormalsVector & normalsVector ) const { 
            normalsVector.reserve( normalsVector.size() + normals.size() );
            for ( size_t i = 0, iCount = normals.size(); i < iCount; i++ )
              normalsVector.push_back( normals[i] );
          }

  // \ru Расширить присланный габаритный прямоугольник так, чтобы он включал в себя проекцию данного объекта на глобальную плоскость XY. \en Extend given bounding box so that it enclose projection of this object to the global XY-plane. 
  virtual void    AddRect( MbRect & rect ) const; 
  // \ru Расширить присланный габаритный куб так, чтобы он включал в себя данный объект. \en Extend given bounding box so that it encloses the given object. 
  virtual void    AddCube( MbCube & r ) const; 

          // \ru Определить, пересекается ли проекция на глобальную плоскость XY треугольника с заданным номером с присланным прямоугольником. \en Determine whether the projection of triangle with a given index to the global XY-plane intersects the given rectangle. 
          bool    TriangleIntersectRect( size_t i, MbRect & rect ) const { return (i<triangles.size()) ? triangles[i].IntersectRect( rect, points ) : false; }
          // \ru Рассчитать габаритный прямоугольник проекции на глобальную плоскость XY треугольника с заданным номером. \en Determine bounding box of the projection of triangle with given index to the global XY-plane. 
          void    TriangleGetGabRect   ( size_t i, MbRect & rect ) const { if (i<triangles.size()) triangles[i].GetGabRect( rect, points ); }

          // \ru Определить, пересекается ли проекция на глобальную плоскость XY четырёхугольника с заданным номером с присланным прямоугольником. \en Determine whether the projection of quadrangle with given index to the global XY-plane intersects the given rectangle. 
          bool    QuadrangleIntersectRect( size_t i, MbRect & rect ) const { return (i<quadrangles.size()) ? quadrangles[i].IntersectRect( rect, points ) : false; }
          // \ru Рассчитать габаритный прямоугольник проекции на глобальную плоскость XY четырёхугольника с заданным номером. \en Determine bounding box of the projection of quadrangle with given index to the global XY-plane. 
          void    QuadrangleGetGabRect   ( size_t i, MbRect & rect ) const { if (i<quadrangles.size()) quadrangles[i].GetGabRect( rect, points ); }

  // \ru Определить положение объекта относительно плоскости XY локальной системы координат. \en Determine the object position relative to the XY-plane of a local coordinate system. \~
  virtual MbeItemLocation GetLocation( const MbPlacement3D & pl, double eps, bool onlyInItem = false ) const; 
  // \ru Определить, расположен ли объект внутри трубы прямоугольного сечения, заданного прямоугольником в плоскости XY локальной системы координат. \en Determine whether the object is inside the tube of rectangular section given by a rectangle in the XY plane of a local coordinate system. \~
  virtual bool    InsideLocation( const MbPlacement3D & place, MbRect & rect, double eps ) const; 

  // \ru Преобразовать триангуляцию так, чтобы её параллельная проекция выглядела как центральная проекция, наблюдаемая из заданной точки vista. \en Transform triangulation so that its parallel projection looks as the central projection observed from the given 'vista' point. 
  virtual void    SetVista   ( const MbCartPoint3D & vista ); 
  // \ru Отменить преобразование триангуляцию для центральной проекции, наблюдаемой из заданной точки vista. \en Undo the transformation of triangulation for central projection observed from given 'vista' point. 
  virtual void    DeleteVista( const MbCartPoint3D & vista ); 

  // \ru Зарезервировать память для контейнера параметров. \en Reserve memory for container of elements. 
  virtual void    ParamsReserve     ( size_t n ) { params.reserve( params.size() + n ); }
  // \ru Зарезервировать память для контейнера точек. \en Reserve memory for container of points. 
  virtual void    PointsReserve     ( size_t n ) { points.reserve( points.size() + n ); }
  // \ru Зарезервировать память для контейнера нормалей. \en Reserve memory for container of normals. 
  virtual void    NormalsReserve    ( size_t n ) { normals.reserve( normals.size() + n ); }
  // \ru Зарезервировать память для контейнера параметров. \en Reserve memory for container of elements. 
  virtual void    EscordsReserve    ( size_t n ) { escorts.reserve( escorts.size() + n ); }

  // \ru Зарезервировать память для контейнеров. \en Reserve memory for some containers. 
  virtual void    ReserveParamsPoints( size_t n ) { params.reserve( params.size() + n ); points.reserve( points.size() + n ); }
  // \ru Зарезервировать память для контейнеров. \en Reserve memory for some containers. 
  virtual void    ReservePointsNormals( size_t n ) { points.reserve( points.size() + n ); normals.reserve( normals.size() + n ); }
  // \ru Зарезервировать память для контейнеров. \en Reserve memory for some containers. 
  virtual void    ReserveParamsPointsNormals( size_t n ) { params.reserve( params.size() + n ); points.reserve( points.size() + n ); normals.reserve( normals.size() + n ); }

  // \ru Удалить дублирующие с заданной точностью друг друга точки. \en Remove redundant points with a given tolerance (duplicates).
  virtual bool    RemoveRedundantPoints( bool deleteNormals, double epsilon = LENGTH_EPSILON );

  // \ru Удалить всю триангуляцию без освобождения памяти, занятую контейнерами. \en Delete all triangulation without freeing the memory occupied by containers. 
  virtual void    Flush()     { params.clear(); points.clear(); normals.clear(); escorts.clear();
                                triangles.clear(); quadrangles.clear(); LoopsDelete();
                                cube.SetEmpty(); }
  // \ru Удалить всю триангуляцию и освободить память. \en Delete all triangulation and free the memory. 
  virtual void    HardFlush() { params.clear(); points.clear(); normals.clear(); escorts.clear(); 
                                triangles.clear(); quadrangles.clear(); LoopsDelete();
                                #ifdef STANDARD_C11
                                points.shrink_to_fit(); normals.shrink_to_fit(); params.shrink_to_fit(); escorts.shrink_to_fit();
                                triangles.shrink_to_fit(); quadrangles.shrink_to_fit(); loops.shrink_to_fit();
                                #endif
                                cube.SetEmpty(); }
  // \ru Освободить лишнюю память. \en Free the unnecessary memory. 
  virtual void    Adjust()    { 
                                #ifdef STANDARD_C11
                                points.shrink_to_fit(); normals.shrink_to_fit(); params.shrink_to_fit(); escorts.shrink_to_fit();
                                triangles.shrink_to_fit(); quadrangles.shrink_to_fit(); loops.shrink_to_fit(); 
                                #endif
                              }

  // \ru Выдать размер триангуляции в байтах. \en Get size of triangulation in bytes. 
  virtual size_t  SizeOf() const;
  // \ru Инвертировать последовательность вершин треугольников и четырехугольников. \en Reverse the sequence of vertices of triangles and quadrilaterals. 
  virtual void    Reverse();
  // \ru Являются ли объекты равными? \en Determine whether objects are equal. 
  virtual bool    IsSame( const MbGrid & init, double eps ) const;

  // \ru Инициировать по другой триангуляции. \en Init by other triangulation. 
  virtual void    Init( const MbGrid & grid );

  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbCartPoint3D *   GetExactPointsAddr() const { return &(points[0]); }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbVector3D *      GetExactNormalsAddr() const { return &(normals[0]); }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbCartPoint *     GetExactParamsAddr() const { return &(params[0]); }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbFloatPoint3D *  GetFloatPointsAddr() const { return NULL; }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbFloatVector3D * GetFloatNormalsAddr() const { return NULL; }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbFloatPoint *    GetFloatParamsAddr() const { return NULL; }

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation, to prevent an assignment by default. 
          void    operator = ( const MbExactGrid & ); 

  KNOWN_OBJECTS_RW_REF_OPERATORS_EX( MbExactGrid, MATH_FUNC_EX );
  KNOWN_OBJECTS_RW_PTR_OPERATORS_EX( MbExactGrid, MATH_FUNC_EX );
}; // MbExactGrid


////////////////////////////////////////////////////////////////////////////////
/** \brief \ru Триангуляция на числах float.
           \en Triangulation on float data. \~
  \details \ru Триангуляция представляет собой набор треугольных и четырёхугольных пластин, стыкующихся друг с другом по общим сторонам.\n
      Триангуляция состоит из согласованных наборов точек, нормалей, параметров триангулируемой поверхности и наборов треугольников и четырехугольников.
    Каждый треугольник - это три номера из набора точек, определяющих вершины треугольника, каждый четырехугольник - это четыре номера из набора точек, определяющих вершины четырехугольника. \n
           \en Triangulation represents a set of triangular and quadrangular plates which are joined to each other by their common sides.\n
      The triangulation consists of a sets of points, normals, surface parameters and a sets of triangles and quadrangles.
    The triangle is represented as three indices from the set of points defining vertices of triangle, the quadrangle is represented as four indices from the set of points defining vertices of quadrangle.\n \~
  \ingroup Polygonal_Objects
*/
////////////////////////////////////////////////////////////////////////////////
class MATH_CLASS MbFloatGrid : public MbGrid {
private:
  std::vector<MbFloatPoint3D>  points;      ///< \ru Множество контрольных точек триангуляции (согласовано с множеством параметров, если последнее не пустое, или пусто, если не пусто множество параметров). \en Set of control points of triangulation (synchronized with set of parameters if the last is not empty, or empty if the set of parameters isn't empty). 
  std::vector<MbFloatVector3D> normals;     ///< \ru Множество нормалей в контрольных точках согласовано с множеством контрольных точек. \en Set of normals at control points is synchronized with the set of control points. 
  std::vector<MbFloatPoint>    params;      ///< \ru Множество параметров - двумерных точек на параметрической области триангулируемой поверхности (может быть пустым). \en Set of parameters of two-dimensional points in parametric domain of surface being triangulated(can be empty). 
  std::vector<uint32>          escorts;     ///< \ru Множество значений для дополнительной информации в точках. \en The set of values for additional information of points. 

protected:
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en The copy constructor without implementation prevents from copying by default. 
  MbFloatGrid( const MbFloatGrid & init );
  // \ru Конструктор копирования с регистратором. \en Copy-constructor with the registrator. 
  explicit MbFloatGrid( const MbFloatGrid & init, MbRegDuplicate * iReg ); 
public:
  // \ru Конструктор без параметров. \en Constructor without parameters. 
  MbFloatGrid();
  // \ru Деструктор. \en Destructor. 
  virtual ~MbFloatGrid();

public:

  // \ru \name Общие функции примитива. \en \name Common functions of primitive.

  virtual MbePrimitiveType IsA() const; // \ru Тип объекта. \en A type of an object. 
  virtual MbFloatGrid & Duplicate( MbRegDuplicate * iReg = NULL ) const; // \ru Создать копию объекта. \en Create a copy of the object. 
  virtual void    Transform( const MbMatrix3D & matr );             // \ru Преобразовать сетку согласно матрице. \en Transform mesh according to the matrix. 
  virtual void    Move     ( const MbVector3D & to );               // \ru Сдвиг сетки. \en Move mesh. 
  virtual void    Rotate   ( const MbAxis3D & axis, double angle ); // \ru Поворот сетки вокруг оси. \en Rotation of mesh about an axis. 
  virtual void    AddYourGabaritTo( MbCube & r ) const;             // \ru Расширить присланный габаритный куб так, чтобы он включал в себя данный объект. \en Extend given bounding box so that it encloses the given object.  
  virtual double  DistanceToPoint( const MbCartPoint3D & pnt ) const; // \ru Вычислить расстояние до точки. \en Calculate distance to point.  
  virtual double  DistanceToLine( const MbAxis3D & axis, double maxDistance, double & t ) const;  // \ru Вычислить расстояние до оси. \en Calculate the distance to an axis.  
  virtual void    GetProperties( MbProperties & );        // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & );  // \ru Записать свойства объекта. \en Set properties of the object. 

  // \ru Выдать количество точек. \en Get the number of points. 
  virtual size_t  PointsCount()  const { return points.size();  }
  // \ru Выдать количество нормалей. \en Get the number of normals. 
  virtual size_t  NormalsCount() const { return normals.size(); }
  // \ru Выдать количество параметров. \en Get the number of parameters. 
  virtual size_t  ParamsCount()  const { return params.size();  } 
  // \ru Выдать количество значений. \en Get count of values. 
  virtual size_t  EscortsCount() const { return escorts.size(); } 
  // \ru Выдать количество точек минус 1 (максимальный индекс). \en Get the number of points minus one (maximal index). 
  virtual ptrdiff_t PointsMaxIndex()  const { ptrdiff_t n = points.size(); return ( n - 1 ); }
  // \ru Выдать количество нормалей минус 1 (максимальный индекс). \en Get the number of normals minus one (maximal index). 
  virtual ptrdiff_t NormalsMaxIndex() const { ptrdiff_t n = normals.size(); return ( n - 1 ); }
  // \ru Выдать количество параметров минус 1 (максимальный индекс). \en Get the number of parameters minus one (maximal index). 
  virtual ptrdiff_t ParamsMaxIndex()  const { ptrdiff_t n = params.size(); return ( n - 1 ); }

  // \ru Добавить в триангуляцию параметры, точку и нормаль триангулируемой поверхности в точке. \en Add parameters, point and normal of triangulated surface at point to triangulation. 
  virtual void    AddPoint ( const MbCartPoint   & p2D, const MbCartPoint3D & p3D, const MbVector3D & n3D );
  // \ru Добавить в триангуляцию параметры и точку. \en Add parameters and a point to triangulation. 
  virtual void    AddPoint ( const MbCartPoint   & p2D, const MbCartPoint3D & p3D );
  // \ru Добавить в триангуляцию точку и нормаль в точке. \en Add a point and normal at the point to triangulation. 
  virtual void    AddPoint ( const MbCartPoint3D & p3D, const MbVector3D & n3D );
  // \ru Добавить в триангуляцию точку. \en Add a point to triangulation. 
  virtual void    AddPoint ( const MbCartPoint3D & p3D );
  // \ru Добавить в триангуляцию нормаль. \en Add a normal to triangulation. 
  virtual void    AddNormal( const MbVector3D    & n3D );
  // \ru Добавить в триангуляцию параметры триангулируемой поверхности. \en Add parameters of triangulated surface to triangulation. 
  virtual void    AddParam ( const MbCartPoint   & p2D );

  // \ru Добавить в триангуляцию параметры, точку и нормаль триангулируемой поверхности в точке. \en Add parameters, point and normal of triangulated surface at point to triangulation. 
  virtual void    AddPoint ( const MbFloatPoint  & p2D, const MbFloatPoint3D & p3D, const MbFloatVector3D & n3D );
  // \ru Добавить в триангуляцию параметры и точку. \en Add parameters and a point to triangulation. 
  virtual void    AddPoint ( const MbFloatPoint  & p2D, const MbFloatPoint3D & p3D );
  // \ru Добавить в триангуляцию точку и нормаль в точке. \en Add a point and normal at the point to triangulation. 
  virtual void    AddPoint ( const MbFloatPoint3D & p3D, const MbFloatVector3D & n3D );
  // \ru Добавить в триангуляцию точку. \en Add a point to triangulation. 
  virtual void    AddPoint( const MbFloatPoint3D & p3D );
  // \ru Добавить в триангуляцию нормаль. \en Add a normal to triangulation. 
  virtual void    AddNormal( const MbFloatVector3D & n3D );
  // \ru Добавить в триангуляцию параметры триангулируемой поверхности. \en Add parameters of triangulated surface to triangulation. 
  virtual void    AddParam( const MbFloatPoint   & p2D );

          // \ru Добавить в триангуляцию точки. \en Add points to triangulation. 
          template <class PointsVector>
          void    AddPoints ( const PointsVector & pnts ) {
            size_t addCnt = pnts.size();
            points.reserve( points.size() + addCnt );
            for ( size_t k = 0; k < addCnt; k++ )
              points.push_back( pnts[k] );
          }
          // \ru Добавить в триангуляцию нормали. \en Add normals to triangulation. 
          template <class NormalsVector>
          void    AddNormals( const NormalsVector & nrms ) {
            size_t addCnt = nrms.size();
            normals.reserve( normals.size() + addCnt );
            for ( size_t k = 0; k < addCnt; k++ )
              normals.push_back( nrms[k] );
          }
          // \ru Добавить в триангуляцию параметры триангулируемой поверхности. \en Add parameters of triangulated surface to triangulation.
          template <class ParamsVector>
          void    AddParams( const ParamsVector & prms ) {
            size_t addCnt = prms.size();
            params.reserve( params.size() + addCnt );
            for ( size_t k = 0; k < addCnt; k++ )
              params.push_back( prms[k] );
          }

  // \ru Добавить в коллекцию данных. \en Add scores to collection. 
  virtual void    AddEscorts( const std::vector<uint32> & scores )  { escorts.insert(escorts.end(), scores.begin(), scores.end()); }

  // \ru Выдать точку по её номеру. \en Get point by its index. 
  virtual void    GetPoint ( size_t i, MbCartPoint3D  & p ) const;
  // \ru Выдать нормаль по её номеру. \en Get normal by its index. 
  virtual void    GetNormal( size_t i, MbVector3D     & n ) const;
  // \ru Выдать параметр по его номеру. \en Get parameter by its index. 
  virtual void    GetParam ( size_t i, MbCartPoint    & p ) const;
  // \ru Выдать дополнительную информацию по её номеру. \en Get additional information by its index. 
  virtual const   uint32 & GetEscort( size_t i ) const;

  /// \ru Выдать точку по её номеру. \en Get point by its index. 
  virtual void    GetPoint ( size_t i, MbFloatPoint3D  & p ) const;
  /// \ru Выдать нормаль по её номеру. \en Get normal by its index. 
  virtual void    GetNormal( size_t i, MbFloatVector3D & n ) const;
  /// \ru Выдать параметр по его номеру. \en Get parameter by its index. 
  virtual void    GetParam ( size_t i, MbFloatPoint    & p ) const;

          // \ru Выдать точку с заданным номером. \en Get point by the given index. 
          const   MbFloatPoint3D  & GetPoint ( size_t i ) const;
          // \ru Выдать нормаль с заданным номером. \en Get normal by the given index. 
          const   MbFloatVector3D & GetNormal( size_t i ) const;
          // \ru Выдать параметр с заданным номером. \en Get parameter by the given index. 
          const   MbFloatPoint    & GetParam ( size_t i ) const;

  // \ru Установить точку с заданным номером. \en Set point by the given index. 
  virtual void    SetPoint ( size_t i, const MbCartPoint3D & p );
  // \ru Установить нормаль с заданным номером. \en Set normal by the given index. 
  virtual void    SetNormal( size_t i, const MbVector3D    & n );
  // \ru Установить параметр с заданным номером. \en Set parameter by the given index. 
  virtual void    SetParam ( size_t i, const MbCartPoint   & p );
  // \ru Установить дополнительную информацию по её номеру. \en Set additional information by its index. 
  virtual void    SetEscort( size_t i, const uint32 & e );

  // \ru Удалить точку с заданным номером. \en Delete point by the given index. 
  virtual void    PointRemove ( size_t i );
  // \ru Удалить нормаль с заданным номером. \en Delete normal by the given index. 
  virtual void    NormalRemove( size_t i );
  // \ru Удалить параметры поверхности с заданным номером. \en Delete parameters of surface by the given index. 
  virtual void    ParamRemove ( size_t i );

  // \ru Удалить точки. \en Delete points. 
  virtual void    PointsDelete();
  // \ru Удалить нормали. \en Delete normal. 
  virtual void    NormalsDelete();
  // \ru Удалить параметры. \en Delete papams. 
  virtual void    PapamsDelete();
  // \ru Удалить дополнительную информацию. \en Delete additional information. 
  virtual void    EscortsDelete();

  /// \ru Инвертировать нормали. \en Invert normals. 
  virtual void    NormalsInvert();

  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) параметры поверхности. \en Get parameters of surface for i-th triangle in general numbering (with strips). 
  virtual bool    GetTriangleParams   ( size_t i, MbCartPoint & r0, MbCartPoint & r1, MbCartPoint & r2 ) const;
  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) точки вершин. \en Get points of vertices for i-th triangle in general numbering (with strips). 
  virtual bool    GetTrianglePoints   ( size_t i, MbCartPoint3D & p0, MbCartPoint3D & p1, MbCartPoint3D & p2 ) const;
  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) точки вершин. \en Get points of vertices for i-th triangle in general numbering (with strips). 
  virtual bool    GetTrianglePoints   ( size_t i, MbFloatPoint3D & p0, MbFloatPoint3D & p1, MbFloatPoint3D & p2 ) const;
  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) нормали в вершинах. \en Get normals at vertices for i-th triangle in general numbering (with strips). 
  virtual bool    GetTriangleNormals  ( size_t i, MbVector3D & n0, MbVector3D & n1, MbVector3D & n2 ) const;
  // \ru Выдать для треугольника с номером i в общей нумерации (с полосами) нормали в вершинах. \en Get normals at vertices for i-th triangle in general numbering (with strips). 
  virtual bool    GetTriangleNormals  ( size_t i, MbFloatVector3D & n0, MbFloatVector3D & n1, MbFloatVector3D & n2 ) const;

  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) параметры поверхности. \en Get parameters of surface for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadrangleParams ( size_t i, MbCartPoint & r0, MbCartPoint & r1, MbCartPoint & r2, MbCartPoint & r3 ) const;
  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) точки вершин. \en Get points of vertices for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadranglePoints ( size_t i, MbCartPoint3D & p0, MbCartPoint3D & p1, MbCartPoint3D & p2, MbCartPoint3D & p3 ) const;
  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) точки вершин. \en Get points of vertices for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadranglePoints ( size_t i, MbFloatPoint3D & p0, MbFloatPoint3D & p1, MbFloatPoint3D & p2, MbFloatPoint3D & n3 ) const;
  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) нормали в вершинах. \en Get normals at vertices for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadrangleNormals( size_t i, MbVector3D & n0, MbVector3D & n1, MbVector3D &n2, MbVector3D & n3 ) const;
  // \ru Выдать для четырёхугольника с номером i в общей нумерации (с полосами) нормали в вершинах. \en Get normals at vertices for i-th quadrangle in general numbering (with strips). 
  virtual bool    GetQuadrangleNormals( size_t i, MbFloatVector3D & n0, MbFloatVector3D & n1, MbFloatVector3D & n2, MbFloatVector3D & n3 ) const;

  // \ru Выдать первую нормаль для плоской триангуляции, если количество точек больше количества нормалей (только для плоской триангуляции). \en Get first normal for flat triangulation if count of points is greater than count of normals (only for planar triangulation). 
  virtual bool    GetSingleNormal   ( MbVector3D & ) const;
  // \ru Выдать первую нормаль для плоской триангуляции, если количество точек больше количества нормалей (только для плоской триангуляции). \en Get first normal for flat triangulation if count of points is greater than count of normals (only for planar triangulation). 
  virtual bool    GetSingleNormal   ( MbFloatVector3D & ) const;
  // \ru Если количество точек больше количества нормалей, то добавить недостающие нормали (только для плоской триангуляции). \en If count of points is greater than count of normals, then add missing normals (only for planar triangulation). 
  virtual void    SynchronizNormals ();

          // \ru Выдать контейнер параметров. \en Get the container of parameters. 
          template <class ParamsVector>
          void    GetParams( ParamsVector & paramsVector )  const { 
            paramsVector.reserve( paramsVector.size() + params.size() );
            for ( size_t i = 0, iCount = params.size(); i < iCount; i++ )
              paramsVector.push_back( params[i] );
          }
          // \ru Выдать контейнер точек. \en Get the container of points. 
          template <class PointsVector>
          void    GetPoints( PointsVector & pointsVector )  const {
            pointsVector.reserve( pointsVector.size() + points.size() );
            for ( size_t i = 0, iCount = points.size(); i < iCount; i++ )
              pointsVector.push_back( points[i] );
          }
          // \ru Выдать контейнер нормалей. \en Get the container of normals. 
          template <class NormalsVector>
          void    GetNormals( NormalsVector & normalsVector ) const { 
            normalsVector.reserve( normalsVector.size() + normals.size() );
            for ( size_t i = 0, iCount = normals.size(); i < iCount; i++ )
              normalsVector.push_back( normals[i] );
          }

  // \ru Расширить присланный габаритный прямоугольник так, чтобы он включал в себя проекцию данного объекта на глобальную плоскость XY. \en Extend given bounding box so that it enclose projection of this object to the global XY-plane. 
  virtual void    AddRect( MbRect & rect ) const; 
  // \ru Расширить присланный габаритный куб так, чтобы он включал в себя данный объект. \en Extend given bounding box so that it encloses the given object. 
  virtual void    AddCube( MbCube & r ) const; 

  // \ru Определить, пересекается ли проекция на глобальную плоскость XY треугольника с заданным номером с присланным прямоугольником. \en Determine whether the projection of triangle with a given index to the global XY-plane intersects the given rectangle. 
  virtual bool    TriangleIntersectRect( size_t i, MbRect & rect ) const { return (i<triangles.size()) ? triangles[i].IntersectRect( rect, points ) : false; }
  // \ru Рассчитать габаритный прямоугольник проекции на глобальную плоскость XY треугольника с заданным номером. \en Determine bounding box of the projection of triangle with given index to the global XY-plane. 
  virtual void    TriangleGetGabRect   ( size_t i, MbRect & rect ) const { if (i<triangles.size()) triangles[i].GetGabRect( rect, points ); }

  // \ru Определить, пересекается ли проекция на глобальную плоскость XY четырёхугольника с заданным номером с присланным прямоугольником. \en Determine whether the projection of quadrangle with given index to the global XY-plane intersects the given rectangle. 
  virtual bool    QuadrangleIntersectRect( size_t i, MbRect & rect ) const { return (i<quadrangles.size()) ? quadrangles[i].IntersectRect( rect, points ) : false; }
  // \ru Рассчитать габаритный прямоугольник проекции на глобальную плоскость XY четырёхугольника с заданным номером. \en Determine bounding box of the projection of quadrangle with given index to the global XY-plane. 
  virtual void    QuadrangleGetGabRect   ( size_t i, MbRect & rect ) const { if (i<quadrangles.size()) quadrangles[i].GetGabRect( rect, points ); }

  // \ru Определить положение объекта относительно плоскости XY локальной системы координат. \en Determine the object position relative to the XY-plane of a local coordinate system. \~
  virtual MbeItemLocation GetLocation( const MbPlacement3D & pl, double eps, bool onlyInItem = false ) const; 
  // \ru Определить, расположен ли объект внутри трубы прямоугольного сечения, заданного прямоугольником в плоскости XY локальной системы координат. \en Determine whether the object is inside the tube of rectangular section given by a rectangle in the XY plane of a local coordinate system. \~
  virtual bool    InsideLocation( const MbPlacement3D & place, MbRect & rect, double eps ) const; 

  // \ru Преобразовать триангуляцию так, чтобы её параллельная проекция выглядела как центральная проекция, наблюдаемая из заданной точки vista. \en Transform triangulation so that its parallel projection looks as the central projection observed from the given 'vista' point. 
  virtual void    SetVista   ( const MbCartPoint3D & vista ); 
  // \ru Отменить преобразование триангуляцию для центральной проекции, наблюдаемой из заданной точки vista. \en Undo the transformation of triangulation for central projection observed from given 'vista' point. 
  virtual void    DeleteVista( const MbCartPoint3D & vista ); 

  // \ru Зарезервировать память для контейнера параметров. \en Reserve memory for container of elements. 
  virtual void    ParamsReserve     ( size_t n ) { params.reserve( params.size() + n ); }
  // \ru Зарезервировать память для контейнера точек. \en Reserve memory for container of points. 
  virtual void    PointsReserve     ( size_t n ) { points.reserve( points.size() + n ); }
  // \ru Зарезервировать память для контейнера нормалей. \en Reserve memory for container of normals. 
  virtual void    NormalsReserve    ( size_t n ) { normals.reserve( normals.size() + n ); }
  // \ru Зарезервировать память для контейнера параметров. \en Reserve memory for container of elements. 
  virtual void    EscordsReserve    ( size_t n ) { escorts.reserve( escorts.size() + n ); }

  // \ru Зарезервировать память для контейнеров. \en Reserve memory for some containers. 
  virtual void    ReserveParamsPoints( size_t n ) { params.reserve( params.size() + n ); points.reserve( points.size() + n ); }
  // \ru Зарезервировать память для контейнеров. \en Reserve memory for some containers. 
  virtual void    ReservePointsNormals( size_t n ) { points.reserve( points.size() + n ); normals.reserve( normals.size() + n ); }
  // \ru Зарезервировать память для контейнеров. \en Reserve memory for some containers. 
  virtual void    ReserveParamsPointsNormals( size_t n ) { params.reserve( params.size() + n ); points.reserve( points.size() + n ); normals.reserve( normals.size() + n ); }

  // \ru Удалить дублирующие с заданной точностью друг друга точки. \en Remove redundant points with a given tolerance (duplicates).
  virtual bool    RemoveRedundantPoints( bool deleteNormals, double epsilon = LENGTH_EPSILON );

  // \ru Удалить всю триангуляцию без освобождения памяти, занятую контейнерами. \en Delete all triangulation without freeing the memory occupied by containers. 
  virtual void    Flush()     { params.clear(); points.clear(); normals.clear(); escorts.clear();
                                triangles.clear(); quadrangles.clear(); LoopsDelete();
                                cube.SetEmpty(); }
  // \ru Удалить всю триангуляцию и освободить память. \en Delete all triangulation and free the memory. 
  virtual void    HardFlush() { params.clear(); points.clear(); normals.clear(); escorts.clear(); 
                                triangles.clear(); quadrangles.clear(); LoopsDelete();
                                #ifdef STANDARD_C11
                                points.shrink_to_fit(); normals.shrink_to_fit(); params.shrink_to_fit(); escorts.shrink_to_fit();
                                triangles.shrink_to_fit(); quadrangles.shrink_to_fit(); loops.shrink_to_fit();
                                #endif
                                cube.SetEmpty(); }
  // \ru Освободить лишнюю память. \en Free the unnecessary memory. 
  virtual void    Adjust()    { 
                                #ifdef STANDARD_C11
                                points.shrink_to_fit(); normals.shrink_to_fit(); params.shrink_to_fit(); escorts.shrink_to_fit();
                                triangles.shrink_to_fit(); quadrangles.shrink_to_fit(); loops.shrink_to_fit(); 
                                #endif
                              }
  
  // \ru Выдать размер триангуляции в байтах. \en Get size of triangulation in bytes. 
  virtual size_t  SizeOf() const;
  // \ru Инвертировать последовательность вершин треугольников и четырехугольников. \en Reverse the sequence of vertices of triangles and quadrilaterals. 
  virtual void    Reverse();
  // \ru Являются ли объекты равными? \en Determine whether objects are equal. 
  virtual bool    IsSame( const MbGrid & init, double eps ) const;

  // \ru Инициировать по другой триангуляции. \en Init by other triangulation. 
  virtual void    Init( const MbGrid & grid );

  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbCartPoint3D *   GetExactPointsAddr() const { return NULL; }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbVector3D *      GetExactNormalsAddr() const { return NULL; }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbCartPoint *     GetExactParamsAddr() const { return NULL; }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbFloatPoint3D *  GetFloatPointsAddr() const { return &(points[0]); }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbFloatVector3D * GetFloatNormalsAddr() const { return &(normals[0]); }
  /// \ru Выдать адрес начала массива. \en Get the address of the beginning of the array. 
  virtual const   MbFloatPoint *    GetFloatParamsAddr() const { return &(params[0]); }

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation, to prevent an assignment by default. 
          void    operator = ( const MbFloatGrid & ); 

  KNOWN_OBJECTS_RW_REF_OPERATORS_EX( MbFloatGrid, MATH_FUNC_EX );
  KNOWN_OBJECTS_RW_PTR_OPERATORS_EX( MbFloatGrid, MATH_FUNC_EX );
}; // MbFloatGrid


////////////////////////////////////////////////////////////////////////////////
//
//         \ru Неклассные функции.   \en Other Functions.
//
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
/** \brief \ru Построить триангуляции в форме трубы заданного радиуса вокруг полигона.
           \en Construct triangulations in the form of a tube of given radius around the polygon. \~
  \details \ru Построить триангуляции в форме трубы заданного радиуса вокруг полигона. \n
           \en Construct triangulations in the form of a tube of given radius around the polygon. \n \~
  \param[in] poly - \ru Полигон.
                    \en A polygon. \~
  \param[in] radius - \ru Радиус трубы.
                      \en Radius of a tube. \~
  \param[in] sag - \ru Максимальное отклонение триангуляции от окружности (стрелка прогиба).
                   \en Maximum deviation of triangulation from a circle (sag). \~
  \param[out] grid - \ru Триангуляция - результат построения.
                     \en Triangulation - the result. \~
  \ingroup Triangulation
*/
// ---
MATH_FUNC (bool) PolygonTubeGrid( const MbPolygon3D & poly, 
                                  double radius, 
                                  double sag, 
                                  MbGrid & grid );


//------------------------------------------------------------------------------
/** \brief \ru Преобразовать двумерный полигон в триангуляцию.
           \en Convert two-dimensional polygon to triangulation. \~
  \details \ru Преобразовать двумерный полигон в триангуляцию. \n
           \en Convert two-dimensional polygon to triangulation. \n \~
  \param[in] poly - \ru Двумерный полигон.
                    \en A two-dimensional polygon. \~
  \param[out] grid - \ru Построенная триангуляция.
                     \en Constructed triangulation. \~
  \ingroup Triangulation
*/
// ---
MATH_FUNC (bool) PolygonToGrid( const MbPolygon & poly, MbGrid & grid );


//------------------------------------------------------------------------------
/** \brief \ru Найти пересечение прямой линии и треугольника.
           \en Find the intersection of a line with a triangle. \~
  \details \ru Найти пересечение прямой линии и треугольника, заданного своими вершинами. 
    Если прямая линия пересекает треугольник, то определяется значение параметра прямой линии для точки пересечения. \n
           \en Find the intersection of a line with a triangle defined by its vertices. 
    If a straight line crosses the triangle, then the value of parameter of a straight line at the intersection point is determined. \n \~
  \param[in] tri_v0 - \ru Первая вершина треугольника.
                      \en The first vertex of the triangle. \~
  \param[in] tri_v1 - \ru Вторая вершина треугольника.
                      \en The second vertex of the triangle. \~
  \param[in] tri_v2 - \ru Третья вершина треугольника.
                      \en The third vertex of the triangle. \~
  \param[in] line - \ru Прямая линия, для которой вычисляется пересечение с треугольником.
                    \en A straight line to calculate the intersection of triangle with. \~
  \param[in] epsilon - \ru Пространственная погрешность.
                       \en A spatial tolerance. \~
  \param[out] crossPnt - \ru Точка пересечения.
                         \en The intersection point. \~
  \param[out] tRes - \ru Параметр точки пересечения на линии.
                     \en Parameter of the intersection point on the line. \~
  \return \ru Пересекает ли прямая треугольник (true - В случае пересечения линии и треугольника).
          \en Whether the line intersects the triangle (true in case of line and triangle intersection). \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC(bool) LineTriangleIntersect( const MbFloatPoint3D & tri_v0,
                                       const MbFloatPoint3D & tri_v1, 
                                       const MbFloatPoint3D & tri_v2,
                                       const MbFloatAxis3D &  line,
                                             float            epsilon,
                                             MbFloatPoint3D & crossPnt,
                                             float &          tRes );


//------------------------------------------------------------------------------
/** \brief \ru Найти пересечение прямой линии и триангуляции.
           \en Find the intersection of a straight line with the triangulation. \~
  \details \ru Для всех треугольников определяется пересечение с прямой линии и вычисляется минимальное значение 
    параметра точки пересечения на секущей прямой линии. \n
           \en For all the triangles the intersection with the straight line is determined and the minimum value of 
    the intersection point parameter on the secant straight line is calculated. \n \~
  \param[in] grid - \ru Триангуляция.
                    \en Triangulation. \~
  \param[in] line - \ru Прямая линия, для которой вычисляется пересечение с триангуляцией.
                    \en Straight line to calculate the intersection of triangulation with. \~
  \param[out] crossPnt - \ru Точка пересечения.
                         \en The intersection point. \~
  \param[out] tRes - \ru Параметр точки пересечения линии.
                     \en Parameter of the intersection point on the line. \~
  \return \ru Найдено ли пересечение (true - В случае успеха).
          \en Whether the intersection is found (true if success). \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) LineGridIntersect( const MbGrid & grid, 
                                    const MbFloatAxis3D &  line,
                                          MbFloatPoint3D & crossPnt,
                                          float &          tRes );

//------------------------------------------------------------------------------
/** \brief \ru Найти пересечение прямой линии и триангуляции.
           \en Find the intersection of a straight line with the triangulation. \~
  \details \ru Для всех треугольников определяется пересечение с прямой линии и вычисляется минимальное значение 
    параметра точки пересечения на секущей прямой линии. \n
           \en For all the triangles the intersection with the straight line is determined and the minimum value of 
    the intersection point parameter on the secant straight line is calculated. \n \~
  \param[in] grid - \ru Триангуляция.
                    \en Triangulation. \~
  \param[in] line - \ru Прямая линия, для которой вычисляется пересечение с триангуляцией.
                    \en Straight line to calculate the intersection of triangulation with. \~
  \param[in] cutPlace - \ru Отсекающая плоскость.
                        \en Cutting plane. \~
  \param[out] crossPnt - \ru Точка пересечения.
                         \en The intersection point. \~
  \param[out] tRes - \ru Параметр точки пересечения линии.
                     \en Parameter of the intersection point on the line. \~
  \return \ru Найдено ли пересечение (true - В случае успеха).
          \en Whether the intersection is found (true if success). \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) LineGridIntersect( const MbGrid & grid, 
                                    const MbFloatAxis3D &  line,
                                    const MbPlacement3D &  cutPlace,
                                          MbFloatPoint3D & crossPnt,
                                          float &          tRes );

//------------------------------------------------------------------------------
/** \brief \ru Найти пересечение прямой линии и триангуляции.
           \en Find the intersection of a straight line with the triangulation. \~
  \details \ru Для всех треугольников определяется пересечение с прямой линии и вычисляется минимальное значение 
    параметра точки пересечения на секущей прямой линии. \n
           \en For all the triangles the intersection with the straight line is determined and the minimum value of 
    the intersection point parameter on the secant straight line is calculated. \n \~
  \param[in] grid - \ru Триангуляция.
                    \en Triangulation. \~
  \param[in] line - \ru Прямая линия, для которой вычисляется пересечение с триангуляцией.
                    \en Straight line to calculate the intersection of triangulation with. \~
  \param[in] cutPlaces - \ru Отсекающая плоскости.
                         \en Cutting planes. \~
  \param[out] crossPnt - \ru Точка пересечения.
                         \en The intersection point. \~
  \param[out] tRes - \ru Параметр точки пересечения линии.
                     \en Parameter of the intersection point on the line. \~
  \return \ru Найдено ли пересечение (true - В случае успеха).
          \en Whether the intersection is found (true if success). \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) LineGridIntersect( const MbGrid &            grid, 
                                    const MbFloatAxis3D &              line,
                                    const std::vector<MbPlacement3D> & cutPlaces,
                                          MbFloatPoint3D &             crossPnt,
                                          float &                      tRes );


//------------------------------------------------------------------------------
/** \brief \ru Найти пересечение прямой линии и триангуляции.
           \en Find the intersection of a straight line with the triangulation. \~
  \details \ru Для всех треугольников определяется пересечение с прямой линии и вычисляется минимальное значение 
    параметра точки пересечения на секущей прямой линии. \n
           \en For all the triangles the intersection with the straight line is determined and the minimum value of 
    the intersection point parameter on the secant straight line is calculated. \n \~
  \param[in] grid - \ru Триангуляция.
                    \en Triangulation. \~
  \param[in] line - \ru Прямая линия, для которой вычисляется пересечение с триангуляцией.
                    \en Straight line to calculate the intersection of triangulation with. \~
  \param[out] tRes - \ru Параметр точки пересечения линии.
                     \en Parameter of the intersection point on the line. \~
  \return \ru Найдено ли пересечение (true - В случае успеха).
          \en Whether the intersection is found (true if success). \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) LineGridIntersect( const MbGrid & grid, 
                                    const MbFloatAxis3D & line,
                                          float         & tRes );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить квадрат расстояния от линии до полигона.
           \en Calculate squared distance from a line to a polygon. \~
  \details \ru При вычислении квадрата расстояния от линии до полигона проверяется расстояние от каждого 
    сегмента полигона до первого попадания в окрестность delta.
    Возвращается значение параметра ближайшей точки на линии tRes и квадрат расстояния 
    от этой точки до сегмента полигона. \n
           \en During calculation of squared distance from a line to a polygon the distance from each 
    segment of the polygon is checked until the first getting to 'delta' neighborhood.
    Returns the value of the nearest point parameter on tRes line and the squared distance 
    from this point to a segment of the polygon. \n \~
  \param[in] grid - \ru Триангуляция.
                    \en Triangulation. \~
  \param[in] edgeInd - \ru Индекс тестируемого полигона.
                       \en Index of polygon to check. \~
  \param[in] line - \ru Линия, до которой вычисляется расстояние.
                    \en Line to calculate the distance to. \~
  \param[in] delta - \ru Радиус окрестности вокруг линии.
                     \en Neighborhood radius around the line. \~
  \param[out] tRes - \ru Значение параметра ближайшей точки линии.
                     \en The value of parameter of the nearest point on the line. \~
  \return \ru Квадрат расстояния ближайшей точки до линии.
          \en Squared distance between the nearest point and the line. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC(float) LineToGridEdgeDistanceSquared( const MbGrid        & grid,
                                                      size_t          edgeInd,
                                                const MbFloatAxis3D & line,
                                                      float           delta,
                                                      float         & tRes );


//------------------------------------------------------------------------------
/** \brief \ru Вычислить квадрат расстояния от линии до полигона.
           \en Calculate squared distance from a line to a polygon. \~
  \details \ru При вычислении квадрата расстояния от линии до полигона проверяется расстояние от каждого 
    сегмента полигона до первого попадания в окрестность delta.
    Возвращается значение параметра ближайшей точки на линии tRes, вектор между ближайшими точками и квадрат 
    расстояния от этой точки до сегмента полигона. \n
           \en During calculation of squared distance from a line to a polygon the distance from each 
    segment of the polygon is checked until the first getting to 'delta' neighborhood.
    Returns the value of the nearest point parameter on the line, the vector between the nearest points 
    and the squared distance from this point to a segment of the polygon. \n \~
  \param[in] grid - \ru Триангуляция.
                    \en Triangulation. \~
  \param[in] edgeInd - \ru Индекс тестируемого полигона.
                       \en Index of polygon to check. \~
  \param[in] line - \ru Линия, до которой вычисляется расстояние.
                    \en Line to calculate the distance to. \~
  \param[in] vDelta - \ru Габарит окрестности вокруг линии.
                     \en The dimensions of the area around the line. \~
  \param[out] vRes - \ru Вектор от ближайшей точки на линии до ближайшей точки на полигоне.
                     \en Vector from the nearest point on the line to the nearest point on the polygon. \~
  \param[out] tRes - \ru Значение параметра ближайшей точки линии.
                     \en The value of parameter of the nearest point on the line. \~
  \return \ru Квадрат расстояния ближайшей точки до линии.
          \en Squared distance between the nearest point and the line. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC(float) LineToGridEdgeDistanceSquared( const MbGrid          & grid,
                                                      size_t            edgeInd,
                                                const MbFloatAxis3D   & line,
                                                const MbFloatVector3D & vDelta,
                                                      MbFloatVector3D & vRes,
                                                      float           & tRes );


#endif // __MESH_GRID_H
