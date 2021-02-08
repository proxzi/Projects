#ifndef __TRI_BALL_PIVOTING_H
#define __TRI_BALL_PIVOTING_H

#include <mb_cart_point.h>
#include <mesh_triangle.h>
#include <collection.h>
#include <templ_kdtree.h>
#include <list>


class  MATH_CLASS  MbGrid;
class  MATH_CLASS  MbCollection;


//------------------------------------------------------------------------------
// Облако точек
// ---
class MbPointCloud 
{
protected:
  enum { 
    pnt_Deleted     = 0x0001, // Точка удалена из сетки.
    pnt_Visited     = 0x0010, // Точка используется в сетке (является вершиной построенного треугольника).
    pnt_Border      = 0x0020, // Точка находится на внешней границе построенной сетки.
    pnt_Processed   = 0x0100  // Точка уже обработана алгоритмом.
  };

public:
  const std::vector<MbCartPoint3D> & points;  // Множество точек.
  const std::vector<MbVector3D> &    normals; // Множество нормалей в точках (согласовано с множеством точек). 
        std::vector<int>             flags;   // Множество битовых флагов для точек.

public:
  /// Конструктор.
  MbPointCloud( const MbCollection & collection )
   : points  ( collection.GetPoints()      )
   , normals ( collection.GetNormals()     )
   , flags   ( collection.PointsCount(), 0 )
  { }

protected:
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en The copy constructor without implementation prevents from copying by default. 
  MbPointCloud( const MbPointCloud & );

public:
  /// Выдать количество точек.
  size_t        PointsCount() const { return points.size(); } 
  /// Выдать точку по её номеру.
  MbCartPoint3D GetPoint ( size_t i ) const { return points[i]; }
  /// Выдать нормаль по её номеру.
  MbVector3D    GetNormal( size_t i ) const { return normals[i]; }
  /// Находится ли точка на границе построенной сетки. 
  bool          IsBorder( size_t i ) const { return (flags[i] & pnt_Border) != 0; }
  /// Установить признак того, что точка находится на границе построенной сетки. 
  void          SetBorder( size_t i ) { flags[i] |= pnt_Border; }
  /// Очистить признак того, что точка находится на границе построенной сетки. 
  void          ClearBorder( size_t i ) { flags[i] &= ~pnt_Border;}
  /// Обработана ли точка алгоритмом. 
  bool          IsUsed( size_t i ) const { return (flags[i] & pnt_Processed) != 0; }
  /// Установить признак того, что точка обработана алгоритмом. 
  void          SetUsed( size_t i ) { flags[i] |= pnt_Processed; }
  /// Очистить признак того, что точка обработана алгоритмом. 
  void          ClearUsed( size_t i ) { flags[i] &= ~pnt_Processed;}
  /// Удалена ли точка из сетки. 
  bool          IsDeleted( size_t i ) const { return (flags[i] & pnt_Deleted) != 0; }
  /// Установить признак того, что точка удалена из сетки. 
  void          SetDeleted( size_t i ) { flags[i] |= pnt_Deleted; }
  /// Является ли точка вершиной уже построенного треугольника. 
  bool          IsVisited( size_t i ) const { return (flags[i] & pnt_Visited) != 0; }
  /// Установить признак того, что точка является вершиной построенного треугольника. 
  void          SetVisited( size_t i ) { flags[i] |= pnt_Visited; }
  /// Очистить признак того, что точка является вершиной построенного треугольника. 
  void          ClearVisite( size_t i ) { flags[i] &= ~pnt_Visited; }

private:
  // Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию.
  void operator = ( const MbPointCloud & );
};


//------------------------------------------------------------------------------
// Граница фронта.
// ---
class MbFrontEdge 
{
public:
  size_t v0, v1, v2; // v0, v1 - описывают отрезок - границу фронта, 
                     // v2 - точка внутри области, ограниченной фронтом.
  bool active; // Является ли ребро границей фронта или внутренним ребром.

  // Цикл границ фронта рассматривается как двусвязный список.
  std::list<MbFrontEdge>::iterator next;
  std::list<MbFrontEdge>::iterator previous;

public:
  /// Конструктор.
  MbFrontEdge() 
  {}
  /// Конструктор по параметрам.
  MbFrontEdge( size_t _v0, size_t _v1, size_t _v2 )
    : v0    ( _v0  ) 
    , v1    ( _v1  )
    , v2    ( _v2  )
    , active( true ) 
  {
    C3D_ASSERT( v0 != v1 && v1 != v2 && v0 != v2 );
  }
  /// Оператор сравнения.
  bool operator== ( const MbFrontEdge & f ) const
  {
    return ( (v0 == f.v0) && (v1 == f.v1) && (v2 == f.v2) );
  }
};


//-------------------------------------------------------------------------------
// Алгоритм подвижного фронта (Advancing Front Algorithm, R. Lohner)
// Основной идеей является расширение границ области (фронта) путем
// присоединения точки из набора и построения новых границ области из вершин 
// текущей актиной границы до этой точки. Активная граница при этом убирается из 
// фронта.
// Наследник этого класса должен определить правила:
// 1) Seed - правило выбора трех точек из набора для построения начального треугольника;
// 2) Place- правило выбора точки из набора для построения новых границ области из вершин 
//    текущей активной границы до этой точки.
// ---
class MbAdvancingFront 
{
public:
  typedef std::list<MbFrontEdge>::iterator  ListIterator; 

  std::list<MbFrontEdge> front;      // Список границ фронта области.
  std::list<MbFrontEdge> internal;   // Список внутренних границ области.
  std::vector<size_t>    nb;         // Вектор со значениями, соответствующими числу границ фронта, проходящих через точку с данным индексом.
  MbPointCloud           pointCloud; // Облако точек.
  MbGrid &               grid;       // Объект триангуляции, который необходимо наполнить.

public:
  /// Конструктор.
  MbAdvancingFront( const MbCollection & coll, MbGrid & _grid ) ;
  /// Деструктор.
  virtual ~MbAdvancingFront();

protected:
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en The copy constructor without implementation prevents from copying by default. 
  MbAdvancingFront( const MbAdvancingFront & );

public:
  /// Построить сетку.
  void BuildMesh();

protected:
  enum ListID { 
   edge_Front,    // Внешняя граница.
   edge_Internal  // Внутреннее ребро.
  };

  typedef std::pair<ListID, ListIterator>   ResultIterator;
 
  // Найти точки для исходного(порождающего фронт) треугольника.
  virtual bool Seed( size_t & v0, size_t & v1, size_t & v2 ) = 0;
  // Найти точку для построения треугольника по заданному ребру.
  virtual bool Place( MbFrontEdge & e, ResultIterator & touch, size_t & v ) = 0;
  // Построить новый фронт по треугольнику.
  bool         SeedFace();
  // Расширить фронт путем поиска, присоединения точки и построения треугольника по активному ребру фронта.
  bool         Advance();
  // Добавить треугольник в сетку. 
  void         AddTriangleToMesh( size_t v0, size_t v1, size_t v2 );
  // Проверить ребро:
  // 1. На правильность ориентации, т.е. ребро (v0,v1) может быть включено в другие треугольники только с обратным направлением.
  // 2. Ребро существует по краней мере в единственном экземпляре.
  bool         CheckEdge( size_t v0, size_t v1 );
  // Добавить новое ребро фронта в конец очереди.
  ListIterator addNewEdge( const MbFrontEdge & e );
  // Квалифицировать ребро как внутреннюю границу.
  void         MoveEdgeToInternals( ListIterator e );
  // Удалить ребро.
  void         EraseEdge( ListIterator e );
  // Перемесить ребро в конец очереди.
  void         MoveBack( ListIterator e );
  // Перемесить ребро в начало очереди.
  void         MoveFront( ListIterator e );
  // Проверить, может ли ребро быть сшито с одним из соседей.
  bool         Glue( ListIterator e );
  // Склеить вместе два ребра, если a.next = b.
  bool         Glue( ListIterator a, ListIterator b );
  // Разорвать фронт в точке.
  void         Detach( size_t v );

private:
  void operator = ( const MbAdvancingFront & );
};


//-------------------------------------------------------------------------------
// Алгоритм поворотного шара (Ball pivoting algorithm)
// Reference: Bernardini F., Mittleman J., Rushmeier H., Silva C., Taubin G.
// "The ball-pivoting algorithm for surface reconstruction", IEEE TVCG, 1999
// 1) Точки, использованные в алгоритме маркируются как pnt_Visited;
// 2) Граничные точки сетки маркируются как pnt_Border;
// 3) В векторе nb по индексу вершины хранится количество ребер, проходяших через нее;
// 4) Точки, обработанные в алгоритме маркируются как pnt_Processed.
// ---
class MbBallPivoting: public MbAdvancingFront
{
public:
  double radius;    // Радиус поворотного шара (абсолютная величина в единицах измерения сетки).
  double minEdge;   // Минимальная длина ребра.
  double maxEdge;   // Максимальная длина ребра.
  double maxAngle;  // Максимальный угол между двумя гранями сетки (косинус).

public:
  /// Конструктор.
  MbBallPivoting( const MbCollection & coll,               // Объект с облаком точек,
                        MbGrid &       grid,               // триангуляция, которую нужно наполнить/дополнить, 
                        double         radBall = 0.0,      // радиус поворотного шара, если 0 будет предпринята попытка его автоопределения,
                        double         radMin = 0.2,       // радиус кластеризации ( в % от радиуса поворотного шара ),
                        double         angle = M_PI / 2 ); // максимальный угол между двумя элементами сетки.
  /// Деструктор.
  ~MbBallPivoting();

protected:
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en The copy constructor without implementation prevents from copying by default. 
  MbBallPivoting( const MbBallPivoting & );

private:
  /// Найти точки начального треугольника по алгоритму поворотного шара.
  bool   Seed( size_t & v0, size_t & v1, size_t & v2 );
  /// Найти точку для построения треугольника по заданному ребру согласно алгоритму поворотного шара.
  bool   Place( MbFrontEdge & edge, MbAdvancingFront::ResultIterator & touch, size_t & v );
  /// Найти сферу, проходящую через три заданных точки, такую что нормаль к грани через эти три точки направлена в центр сферы.
  bool   FindSphere( const MbCartPoint3D & p0, const MbCartPoint3D & p1, const MbCartPoint3D & p2, MbCartPoint3D & center );
  /// Рассчитать угол между векторами, учитывая ориентацию axis.
  double OrientedAngleRad( MbVector3D p, MbVector3D q, const MbVector3D & axis );
  /// Пометить точку и ее соседей.
  void   Mark( size_t idx );

private:
  size_t           last_seed;   // Испольуется для поиска нового фронта когда текущий фронт пуст.
  MbCartPoint3D    baricenter;  // Используется для первого поиска.
  KdTree<double> * tree;        // К-мерное дерево для поиска N ближайших соседей точки.

private:
  void operator = ( const MbBallPivoting & );
};


#endif // __TRI_BALL_PIVOTING_H