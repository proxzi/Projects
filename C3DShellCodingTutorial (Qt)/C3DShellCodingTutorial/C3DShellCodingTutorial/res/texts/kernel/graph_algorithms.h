//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file     
  \brief \ru Обобщенные алгоритмы на графах.
         \en Generic graph algorithms. \~
         
*/
/////////////////////////////////////////////////////////////////////// MA 25.10.2010 ////

#ifndef __GRAPH_ALGORITHMS_H
#define __GRAPH_ALGORITHMS_H
//
#include <generic_utility.h>
#include <vector>

//----------------------------------------------------------------------------------------
//
/// Пустой посетитель алгоритма обхода графа в глубину
/**  
  \ingroup MathGC_Algo
  \attention Класс не предназначен для того, что бы применять статический 
             или динамический полиморфизм, т.е. не обязывает своих наследников 
             перегружать методы.
*/
//---
template<class Graph>
struct DefaultDFSVisitor
{   
  typedef typename Graph::vertex_index vertex_index;  

  /// Встретили "обратное" ребро (дуга, если орграф) dfs-дерева.
  /**
    Вызывается когда при посещении вершины v найдено исх.ребро, направленное к 
    ранее посещенной вершине. Другими словами, вершина u является предком 
    вершине v в dfs-дереве.
  */
  void  BackEdge( vertex_index /*v*/, vertex_index /*u*/, const Graph & /*g*/ ) {}
  /// Вызывается, когда впервые проходим через исходящую дугу v->u, вершину u еще не посещали
  void  ExamineEdge( vertex_index /*v*/, vertex_index /*u*/, const Graph & /*g*/ ) {}
  /// Посещение вершины: Вызывается один раз для каждой вершины, когда она впервые начинает просматриваться
  void  DiscoverNode( vertex_index /*v*/, const Graph & /*g*/ ) {}
  /// Вершина рассмотрена: Означает, что все исходящие ребра вершины рассмотрены
  void  FinishNode( vertex_index /*v*/, const Graph & /*g*/ ) {}
  /// Встретили "поперечное" или "прямое" ребро 
  /** 
    Вызывается, когда находим дугу, идущую к другому dfs-дереву, либо прямую дугу, 
    идущую к потомку того же дерева, имеющему два и более  отцов.
    Для поперечного ребра вызывается только для ориентированных графов.
  */
  void  ForwardOrCrossEdge( vertex_index /*v*/, vertex_index /*u*/, const Graph & /*g*/ ) {}
  /// Отвечает, что вершина исключена из рассмотрения
  bool  Ignored( vertex_index /*v*/, const Graph & /*g*/ ) const { return false; }
  /// Означает, что начато рассмотрение корневой вершины будущего дерева обхода
  void  StartNode( vertex_index /*v*/, const Graph & /*g*/ ) {}
  /// Ребро стало "древесным" (принадлежит dfs-дереву). Вызывается перед переходом от посещенной вершины v к еще не посещенной вершине u
  void  TreeEdge( vertex_index /*v*/, vertex_index /*u*/, const Graph & /*g*/ ) {}
};


//////////////////////////////////////////////////////////////////////////////////////////
//
/// Посетитель алгоритма поиска блоков и точек сочленения в неориентированном графе
/**
  Позволяет настроить алгоритм поиска блоков и точек сочленения под конкретные реализации.
*/
//////////////////////////////////////////////////////////////////////////////////////////

template< class Graph >
struct DefaultBicompVisitor
{
  /// Найден блок, как последовательность ребер
  template<class EdgeIterator>
  void BlockFounded( EdgeIterator, EdgeIterator, const Graph & ) {}

  /// Обнаружена точка сочленения (articulation vertex)
  template<class Vertex>
  void CutNode( Vertex, const Graph & ) {}

  /// Функция обратного вызова: Фильтрация для точек сочленения
  /**
    С момощью этой функции пользователь настраивает поведение алгорита поиска блоков.
    Если визитер отвечает true, то алгоритм не учитывает данную вершину, 
    как вершину разреза, отделяющую блоки. Таким образом в результате 
    отфильтрованная  точка сочленения всегда будет принадлежать одному блоку.
  */
  template<class Vertex>
  bool IsFilteredCut( Vertex, const Graph & ) const { return false; }
};


//////////////////////////////////////////////////////////////////////////////////////////
//
/// Посетитель обхода в глубину для поиска блоков и точек сочленения
/**
  Класс является автономным и не нуждается в уточнении наследованием от него.
  Graph - предполагается, что это неориентированный граф.
  BicompVisitor - надстроенный визитер, посетитель этого визитера, который
                  реализует события обнаружения блока, точки сочленения и 
                  фильтрацию вершин, которые принудительно запрещается быть 
                  точками сочленения.
*/
//////////////////////////////////////////////////////////////////////////////////////////

template< class Graph, class BicompVisitor = DefaultBicompVisitor<Graph> >
class BicompDFSVisitor: public DefaultDFSVisitor<Graph>
{
public:
  typedef typename Graph::adj_iterator  adj_iterator;
  typedef typename Graph::edge          edge;

public:
  static const typename Graph::vertex_index NO_VERTEX = (size_t)-1;

  BicompDFSVisitor( BicompVisitor & vis )
    : m_graph( NULL )
    , m_bicompVis( vis )
    , m_dfsCounter( 1 )
    , num()
    , father()
    , lval()
    , m_stackEdges()
  {}  
  
  /// Встретили поперечное или прямое ребро
  void  ForwardOrCrossEdge( typename Graph::vertex_index v, typename Graph::vertex_index u, const Graph & ) 
  { 
    DEBUG_UNUSED_PARAMETER( u );
    DEBUG_UNUSED_PARAMETER( v );
    PRECONDITION( num[v] < num[u] ); 
  }

  /// Найдено обратное ребро dfs-дерева, вызывается когда при посещении вершины v найдено исх.ребро к ранее посещенной вершине
  /**
    Вершина u является предком вершине v в dfs-дереве.
  */
  void  BackEdge( typename Graph::vertex_index v, typename Graph::vertex_index u, const Graph & g )
  {
    DEBUG_UNUSED_PARAMETER( g );
    PRECONDITION( m_graph == &g );    
    PRECONDITION( num[u] < num[v] );
    PRECONDITION( father[v] != NO_VERTEX );
    if ( u != father[v] )
    {
      // Здесь vu - есть обратное ребро входящее в вершину u, которая выше, чем v в d-дереве;       
      m_stackEdges.push_back( edge(v,u) );  // вставить ребро vu;
      lval[v] = min_of( lval[v], num[u] );  // см.лемму 6;
    }
  }
  
  /// Посещение вершины: Вызывается один раз для каждой вершины, когда она впервые начинает просматриваться
  void  DiscoverNode( typename Graph::vertex_index v, const Graph & g ) 
  {
    DEBUG_UNUSED_PARAMETER( g );
    C3D_ASSERT( m_graph == &g );
    PRECONDITION( num[v] == 0 );
    PRECONDITION( lval[v] == 0 );    
    num[v] = lval[v] = m_dfsCounter++;    
  }

  /// Вершина рассмотрена: Означает, что все исходящие ребра вершины рассмотрены
  void  FinishNode( typename Graph::vertex_index u, const Graph & g )
  {
    PRECONDITION( m_graph == &g );
    typename Graph::vertex_index v = father[u];
    if ( v == NO_VERTEX ) // СЛУЧАЙ 1: Вершина u - корневая, завершен обход fds-дерева
    {
      // Оценить является ли u - точкой сочленения
      // Сколько раз стартовая вершина стала папой (столько же в ней стыкуется блоков)
      if ( _ChildrenNb(u, g) > 1)
      {
        // В корневой вершине стыкуются 2 или более блоков - значит она же является и точкой сочленения
        m_bicompVis.CutNode( u, g );
      }
      // Извещение о найденном блоке
      if ( !m_stackEdges.empty() ) // Все что есть в m_stackEdges - следует считать последним найденным блоком.
      {
        m_bicompVis.BlockFounded( m_stackEdges.begin(), m_stackEdges.end(), g );
        // После извещения визитера - вычищаем стек
        m_stackEdges.clear();
      }
    }
    else // СЛУЧАЙ 2: u - не корневая вершина
    {      
      lval[v] = min_of( lval[v], lval[u] ); // см. лемму 6;
      if ( lval[u] >= num[v] )
      {
        //  Здесь можно получить новый блок, для чего достаточно вытолкнуть из 
        //  стека все ребра, включая ребро vu.
        
        // (!) Если вершина v не корень d-дерева, то можно утверждать, что она - есть точка сочленения;
        //     См. теорему 8.2.        
        if ( father[v] != NO_VERTEX ) // если v корневая вершина, то оценки для неё делаются в конце обхода дерева
        {
          m_bicompVis.CutNode( v, *m_graph );
        }
        
        // Извещение о найденном блоке
        if ( !m_bicompVis.IsFilteredCut(v,*m_graph) ) // Запрет на отфильтрованные точки сочленения - они не могут "вырезать" блоки.
        {
          // Тут мы запретили собирать блок, т.к. вершина фильтрованная, однако это не принесет ущерба, 
          // если окажется что v - не точка сочленения. Вот почему:
          /*
            Если v - есть корень dfs-дерева, то возможны 2 варианта: v принадлежит одному блоку, 
            тогда v не точка сочленения; v принадлежит двум и более блокам, тогда v - есть точка сочленения.
            В первом случае единственный блок, куда включена v, будет собран в конце текущего обхода dfs-дерева, 
            массив m_stackEdges полностью будет содержать этот блок. Во втором случае, если блок не 
            единственный, то v - есть точка сочленения, тогда очевидно запрет правомерен - в конце обхода дерева все, 
            что осталось в стеке ребер есть один блок.
          */
          
          PRECONDITION( !m_stackEdges.empty() );
          /*
          std::vector<edge>::reverse_iterator vuIter =
            std::find( m_stackEdges.rbegin(), m_stackEdges.rend(), edge(v,u) ); // Ищем с конца
          PRECONDITION( vuIter != m_stackEdges.rend() ) // Это ребро обязано быть в стеке
          m_bicompVis.BlockFounded( vuIter.base()-1, m_stackEdges.end(), *m_graph );
          // После извещения визитера - вычищаем блок из стека конца
          m_stackEdges.erase( vuIter.base()-1, m_stackEdges.end() );
          */
          
          const edge seek( v, u );
          typename std::vector<edge>::iterator first = m_stackEdges.begin();
          typename std::vector<edge>::iterator iter, last;          
          for ( iter = last = m_stackEdges.end(); iter != first; )          
          { 
            --iter;
            if ( *iter == seek )
            {
              break;
            }
          }
          
          PRECONDITION( *iter == seek ); // Это ребро обязано быть в стеке
          m_bicompVis.BlockFounded( iter, last, *m_graph );
          // После извещения визитера - вычищаем блок из стека конца
          m_stackEdges.erase( iter, last );
        }         
      }
    }
  }

  /// Означает, что начато рассмотрение корневой вершины будущего дерева обхода
  void  StartNode( typename Graph::vertex_index v, const Graph & g ) 
  {
    DEBUG_UNUSED_PARAMETER( v );
    _Init( g );
    PRECONDITION( father[v] == NO_VERTEX );
    PRECONDITION( num[v] == 0 &&  lval[v] == 0 );
  }

  /// Заход в ребро dfs-дерева, вызывается перед переходом от посещенной вершины v к еще не посещенной вершине u
  void  TreeEdge( typename Graph::vertex_index v, typename Graph::vertex_index u, const Graph & g ) 
  {
    DEBUG_UNUSED_PARAMETER( g );
    PRECONDITION( m_graph == &g );
    PRECONDITION( father[u] == NO_VERTEX );
    m_stackEdges.push_back( edge(v,u) );  // Вставить ребро vu;    
    father[u] = v;  // зафиксируем отца для вершины u;
  }

private:
  /// Количество сыновей вершины
  size_t _ChildrenNb( typename Graph::vertex_index u, const Graph & g ) const
  {
    PRECONDITION( m_graph == &g );
    // Оценить является ли u - точкой сочленения
    size_t fatherNb = 0; // Сколько раз  вершина u стала папой
    std::pair<adj_iterator,adj_iterator> adjIterPair = g.AdjacentVertices( u );
    for ( ; adjIterPair.first != adjIterPair.second; ++adjIterPair.first )
    {
      if ( father[*adjIterPair.first] == u )
      {
        ++fatherNb;
      }
    }
    return fatherNb;
  }

  void _Init( const Graph & graph )
  {
    m_graph = &graph;    
    const typename Graph::vertices_size_t vertNb = graph.NumVertices();
    m_dfsCounter = 1;
    num.assign( vertNb, 0 );  
    father.assign( vertNb, NO_VERTEX );  
    lval.assign( vertNb, 0 );  
    m_stackEdges.clear();
  }

private:
  const Graph *             m_graph;      ///< Рассматриваемый граф, для которого ищутся точки сочленения
  BicompVisitor &           m_bicompVis;  ///< Посетитель алгоритмов этого класса
  ptrdiff_t                 m_dfsCounter; ///< Cчетчик вершин dfs-дерева
  std::vector<size_t>       num;          ///< Нумерация порядка обхода вершин d-дерева  
  std::vector<size_t>       lval;         ///< Массив значений функции L[v] на каждую вершину - см.теорию стр.166, [Asan], Лемма 6;
  std::vector<typename Graph::vertex_index> father;///< Отец вершины в dfs-дереве
  std::vector<edge>         m_stackEdges; ///< Cтек ребер для обслуживания нахождения блоков

private:
  BicompDFSVisitor & operator = ( const BicompDFSVisitor & );
};

//----------------------------------------------------------------------------------------
// Стековый элемент для алгоритма обхода в глубину.
// ---
template<class Graph>
struct DFSVertexInfo
{
private:
  typedef typename Graph::vertex_index    vertex_index;
  typedef typename Graph::adj_iterator    adj_iterator;

public:
  vertex_index  m_node;
  adj_iterator  m_iter;
  adj_iterator  m_last;  

  DFSVertexInfo( vertex_index v, adj_iterator iter, adj_iterator last )
    : m_node( v )
    , m_iter( iter )
    , m_last( last )
  {}

  DFSVertexInfo( vertex_index v, const Graph & graph )
    : m_node( v )
    , m_iter()
    , m_last()
  {
    tie(m_iter,m_last) = graph.AdjacentVertices( v ); 
  }

  DFSVertexInfo( const DFSVertexInfo & vi )
    : m_node( vi.m_node )
    , m_iter( vi.m_iter )
    , m_last( vi.m_last )
  {}
  
  DFSVertexInfo & operator = ( const DFSVertexInfo & vi )
  {      
    m_node = vi.m_node;
    m_iter = vi.m_iter;
    m_last = vi.m_last;
    return *this;
  }  
};

//----------------------------------------------------------------------------------------
/// Алгоритм обхода в глубину графа смежности
/**
  Вычислительная сложность алгоритма практически линейная, если считать что 
  методы визитера выполняются за константное время.

  \param graph Граф смежности
  \param vis Посетитель алгоритма
*/
//---

template<class Graph, class Visitor>
void DepthFirstSearch( const Graph & graph, Visitor & vis )
{  
  typedef typename Graph::vertices_size_t vertices_size_t;
  typedef typename Graph::vertex_index  vertex_index;
  typedef typename Graph::adj_iterator  adj_iterator;
  
  enum Color // Разметка
  {
      col_white // не посещалась
    , col_gray  // в стеке
    , col_black // 
  };  

  const vertices_size_t vCount = graph.NumVertices();

  std::vector<DFSVertexInfo<Graph>> stack;
  std::vector<Color> colourMap( vCount, col_white ); // отображение: вершина -> цвет

  // Пометить, как рассмотренные, игнорируемые вершины 
  for ( vertex_index xIdx = 0; xIdx<vCount; ++xIdx )
  {
    if ( vis.Ignored(xIdx,graph) )
    {
      colourMap[xIdx] = col_black;
    }
  }

  adj_iterator vIter, vLast;
  vertex_index srcNode;

  for ( vertex_index startNode = 0; startNode < vCount; ++startNode )
  {
    if ( colourMap[startNode] == col_white ) // Начинаем с x-вершины
    {      
      colourMap[startNode] = col_gray;
      vis.StartNode( startNode, graph );
      vis.DiscoverNode( startNode, graph );      
      stack.push_back( DFSVertexInfo<Graph>(startNode,graph) );

      while ( !stack.empty() )
      {
        {
          DFSVertexInfo<Graph> & curr = stack.back();
          vIter = curr.m_iter;
          vLast = curr.m_last;
          srcNode = curr.m_node;
          stack.pop_back();
        }
        
        while ( vIter != vLast )
        { 
          const vertex_index trgNode = *vIter;
          ++vIter;

          vis.ExamineEdge( srcNode, trgNode, graph );

          Color trgCol = colourMap[trgNode];
          if ( trgCol == col_white ) // Переход по дереву к следующей вершине
          {
            vis.TreeEdge( srcNode, trgNode, graph ); // "древесное" ребро
            colourMap[trgNode] = col_gray;            
            stack.push_back( DFSVertexInfo<Graph>(srcNode, vIter, vLast) );
            vis.DiscoverNode( srcNode = trgNode, graph );
            tie( vIter, vLast ) = graph.AdjacentVertices( srcNode );
          }
          else if ( trgCol == col_gray ) // Встетили обратное ребро
          {
            vis.BackEdge( srcNode, trgNode, graph );
          }
          else // Встретили "прямое" или "кросс-ребро" в ориентированном графе
          {
            vis.ForwardOrCrossEdge( srcNode, trgNode, graph );
          }
        }
        
        // Событие завершения обхода текущей вершины        
        colourMap[srcNode] = col_black;
        vis.FinishNode( srcNode, graph );
      }
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////
//
/// Отображение реберных свойств для графов, поддерживающих концепцию смежности вершин (без явных ребер)
/**
  Для графов с инцидентными ребрами лучше использовать другие типы отображений
*/
//////////////////////////////////////////////////////////////////////////////////////////
/*
template<class Graph, class Prop>
class EdgePropertyMap
{
  typedef Graph::vertex_descriptor        vertex_descriptor;
  typedef Graph::edge_descriptor          edge_descriptor;
  typedef std::pair<edge_descriptor,Prop> pair;
  class node
  {    
  public:
    node( const node & );
    node & operator = ( const node & );

  private:
    vertex_descriptor vertex;
    std::vector<pair> props;
  };

  std::vector<node> nodes;

public:
  const Prop & operator[]( edge_descriptor ) const;
        Prop & operator[]( edge_descriptor );
};
*/

//////////////////////////////////////////////////////////////////////////////////////////
//
/// Инкапсуляция алгоритма поиска 2-связных компонент и/или точек сочленения
/**
  ПЛАНИРУЕТСЯ ЗАМЕНИТЬ ЭТОТ АЛГОРИТМ НА БОЛЕЕ ОБЩИЙ НО НЕ МЕНЕЕ ЭФФЕКТИВНЫЙ:
  DepthFirstSearch + BicompDFSVisitor

  \par Определение
  d-деревом называем ациклический подграф рассматриваеморго графа, состоящего
  из вершин и ребер, которые обходит поиск в глубину, на основе которого построен 
  данный адгоритм.
  Graph - тип, отвечающий требованиям обычного графа смежности по вершинам

  \par РЕФАКТОРИНГ
  1) Нужно обобщить это алгоритм с библиотекой MtGraph
  2) Возможно снабдить это класс-алгоритм посетителем поиска компонент. 
     Это, например, позволит генерировать два варианта алгоритма поиска блоков:
     Вариант, когда нужно найти только вершины сочленения (без блоков) вариант, 
     когда нужно искать шарниры и/или блоки;
  2.1.) Возможны другие рецепты, как генерить шаблоном два похожих алгоритма.
  3) Алгоритм можно упростить, если переложить его на еще более общный 
     алгоритм обхода в глубину.
*/
//////////////////////////////////////////////////////////////////////////////////////////

template<class Graph>
class MtBicompSearch
{
  // Ассоциативные типы
  typedef typename  Graph::vertex_index  vertex_index;
  typedef typename  Graph::vertex_size_t vertex_size_t;
  typedef typename  Graph::adj_iterator  adj_iterator;

private:
  const Graph &             m_graph;
  ptrdiff_t                 m_dfsCounter;  
  std::vector<ptrdiff_t>    num;            ///< Нумерация порядка обхода вершин d-дерева
  std::vector<ptrdiff_t>    father;         ///< Отец вершины в d-дереве
  std::vector<ptrdiff_t>    lval;           ///< Массив значений функции L[v] на каждую вершину - см.теорию стр.166, [Asan], Лемма 6;
  std::vector<vertex_index> m_cutnodes;     ///< Обнаруженные точки сочленения
  std::vector<bool>         m_cutnodeProp;  ///< Признак точки сочленения для вершин

public:
  MtBicompSearch( const Graph & );
  /// Найти все точки сочленения
  const std::vector<vertex_index> & SearchCutnodes();

private:
  /// Алгоритм реккурсивного вызова поиска блоков и точек сочленения в графе
  void BiComp( vertex_index );
  /// Инициализировать все рабочие данные для нового поиска
  void Init();
  /// Запустить алгоритм
  void Perform();
};

//----------------------------------------------------------------------------------------
//
//---
template<class Graph>
MtBicompSearch<Graph>::MtBicompSearch( const Graph & g )
  : m_graph( g )
  , m_dfsCounter(1)
  , num()
  , father()
  , lval()
  , m_cutnodes()
  , m_cutnodeProp()
{}

//----------------------------------------------------------------------------------------
/// Найти все точки сочленения
//---
template<class Graph>
const std::vector<typename Graph::vertex_index> & MtBicompSearch<Graph>::SearchCutnodes()
{
  Init();
  Perform();
  return m_cutnodes;
}

//----------------------------------------------------------------------------------------
/// Инициализировать все рабочие данные для нового поиска
//---
template<class Graph>
void MtBicompSearch<Graph>::Init()
{
  const vertex_size_t vertNb = m_graph.NumVertecies();
  m_dfsCounter = 1;
  num.assign( vertNb, 0 );  
  father.assign( vertNb, -1 );  
  lval.assign( vertNb, -1 );  
  m_cutnodeProp.assign( vertNb, false );
  m_cutnodes.clear();
}

//----------------------------------------------------------------------------------------
/// Запустить алгоритм
//---
template<class Graph>
void MtBicompSearch<Graph>::Perform()
{
  PRECONDITION( m_cutnodes.empty() );
  
  const vertex_size_t vertNb = m_graph.NumVertecies();
  for ( vertex_index startIdx = 0; startIdx<vertNb; ++startIdx ) // startIdx - корень d-дерева
  {
    if ( num[startIdx] == 0 )
    {
      BiComp( startIdx );
      PRECONDITION( father[startIdx] == -1 );

      // Оценить является ли startIdx - точкой сочленения
      size_t fatherNb = 0; // Сколько раз стартовая вершина стала папой
      std::pair<adj_iterator,adj_iterator> adjIterPair = m_graph.AdjacentVertices( startIdx );
      for ( ; adjIterPair.first!=adjIterPair.second; ++adjIterPair.first )
      {
        if ( father[*adjIterPair.first] == startIdx )
        {
          ++fatherNb;
        }
      }
      if ( fatherNb > 1 )
      {
        // Корневая вершина - есть точка сочленения
        PRECONDITION( !m_cutnodeProp[startIdx] );
        m_cutnodes.push_back( startIdx );
        m_cutnodeProp[startIdx] = true;
      }
    }
  }
}

//----------------------------------------------------------------------------------------
/// Алгоритм реккурентного вызова поиска блоков и точек сочленения в графе
/**
  Теорию см.главе 8, стр.166, Графы, матроиды, алгоритмы [Asan];
  \param vIdx   -  вершина (индекс), с которой начинаем поиск, которая ещё не рассмотрена, т.е. 
                   num[vIdx] = 0;

  \par Определения
  d-дерево - ациклический подграф основного подграфа, образуемого при обходе 
            вершин во время поиска в глубину;  

  \par Вычислительная сложность
  Вычислительная сложность: O(n+m), где n-кол-во вершин, m-кол-во ребер. Это следует из 
  того факта, что каждая вершина посещается не более одного раза.
*/
//---
template<class Graph>
void MtBicompSearch<Graph>::BiComp( const vertex_index vIdx )
{  
  PRECONDITION( num[vIdx] == 0 );
  num[vIdx] = lval[vIdx] = m_dfsCounter;  
  ++m_dfsCounter;

  // Цикл по всем смежным вершинам vert;
  std::pair<adj_iterator,adj_iterator> adjIterPair = m_graph.AdjacentVertices( vIdx );
  for ( ; adjIterPair.first!=adjIterPair.second; ++adjIterPair.first )
  {
    const vertex_index uIdx = *adjIterPair.first; // Вершина - сын в d-дереве;
    // const edge_descriptor vuEdg = m_graph.GetEdge( vIdx, uIdx );
    if ( num[uIdx] == 0 ) // uIdx - сын вершины vIdx
    {
      // stackE.push_back( vuEdg );  // Вставить ребро vu;
      PRECONDITION( father[uIdx] == -1 );
      father[uIdx] = vIdx;  // зафиксируем отца для данной вершины uIdx;
      BiComp( uIdx );
      
      // При выходе из рекурсии значение функции L[u] уже вычислено;
      lval[vIdx] = min_of( lval[vIdx], lval[uIdx] ); // см.лемму 6;
      if ( lval[uIdx] >= num[vIdx] )
      {
        //  Здесь можно получить новый блок, для чего достаточно вытолкнуть из 
        //  стека все ребра, включая ребро vu.
        
        // (!) Если вершина vIdx не корень d-дерева, то можно утверждать, что она - есть точка сочленения;
        //     См. теорему 8.2.
        if ( father[vIdx] != -1 ) // Первородитель
        {
          if ( !m_cutnodeProp[vIdx] )
          {
            m_cutnodes.push_back( vIdx );
            m_cutnodeProp[vIdx] = true;
          }
        }
        /*
        PRECONDITION( !stackE.empty() )
        blocks.NewComp();
        
        #pragma message ( __TODO__ "(**) Собирать ребра возможно не понадобится! Достаточно cutnodes;" )
        while( !stackE.empty() )  
        {          
          edge_descriptor edge = stackE.back();
          blocks.AddEdge( edge );
          stackE.pop_back(); // вытолкнуть ребро из стека;
          if ( edge == vuEdg  )
          {
            break;
          }
        }
        */
      }
    }
    else if ( num[uIdx] < num[vIdx] && uIdx != father[vIdx] )
    {
      // Здесь vu - есть обратное ребро входящее в вершину u, которая выше, чем v в d-дереве;       
      // stackE.push_back( vuEdg );  // вставить ребро vu;
      lval[vIdx] = min_of( lval[vIdx], num[uIdx] ); // см.лемму 6;
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// Посетитель алгоритма поиска компонент сильной связности
//
//////////////////////////////////////////////////////////////////////////////////////////
struct DefaultSCVisitor
{
  // Вызывается алгоритмом перед началом обхода всего графа
  template<class Graph>
  inline void Start( const Graph & ) {}
  // Вызывается, когда найден очередной компонент сильной связности в орграфе
  /*
    Аргументы: граф и пара вершинных итераторов, пробегающих подмножество компонента
  */
  template<class Graph, class VertexIter>
  inline void Component( const Graph &, VertexIter, VertexIter ) {}
  // Если IsFiltered = true, вершина считается исключенной из графа
  template<class Graph, class Vertex>
  inline bool IsFiltered( const Graph &, Vertex ) { return false; }
};


//////////////////////////////////////////////////////////////////////////////////////////
//
/// Алгоритм поиска компонент сильной связности в орграфе
/** 
     Напомним, что две вершины орграфа считаются сильно связанными, если 
  существует маршрут из первой вершины ко второй и обратный маршрут из второй 
  к первой. Подграф называется <b>сильно связным</b>, если любая пары его 
  вершин сильно связаны. <b>Компонент сильной связности</b> графа - это один из 
  его сильно сзязный подграфов G', для которого не существует сильно связной пары 
  вершин u и v, таких, что u-принадлежит G', а v не принадлежит G'. Другими словами, 
  вершины компонента сильной связости принадлежат классу взаимной достижимости вершин;
    \note Алгоритм #MtStrongComponents имеет линейную сложность вычислений
  \ingroup GCBase
*/
//////////////////////////////////////////////////////////////////////////////////////////

template <class Graph, class SCVisitor, class VertexPropertyMap>
class MtStrongComponents
{
public:  // Ассоциативные типы
  typedef typename graph_traits<Graph>::vertex           vertex;
  typedef typename graph_traits<Graph>::edge             edge;
  typedef typename graph_traits<Graph>::edge_iterator    edge_iterator;
  typedef typename graph_traits<Graph>::vertex_iterator  vertex_iterator;

public:  
        MtStrongComponents( const Graph &, SCVisitor & );
        void operator() ();  ///< Исполнить алгоритм поиска сильных компонентов

private:
  // DFS-алгоритм для поиска компонент сильной связности в графе ограничений
  void  StrongSearch( vertex, std::vector<vertex> & );

private:
  const Graph &           m_diGraph;  ///< Ориентированный граф
        SCVisitor &       m_vis;      ///< Посетитель алгоритма поиска компонент сильной связности
        size_t            m_counter;  ///< Порядок DFS-обхода
        VertexPropertyMap num;        ///< Вспомогательный массив порядковых номеров обхода в глубину
        VertexPropertyMap lval;       ///< Массив для промежуточных целочисленных вычислений        

private:
  MtStrongComponents( const MtStrongComponents & );
  MtStrongComponents & operator = ( const MtStrongComponents & );
};

//----------------------------------------------------------------------------------------
//
//---
template <class Graph, class Vis, class VPropMap>
MtStrongComponents<Graph,Vis,VPropMap>::MtStrongComponents( const Graph & b_graph, Vis & vis )
  : m_diGraph( b_graph )
  , m_vis( vis )
  , num( b_graph.NumVertices() )
  , lval( b_graph.NumVertices() )
  , m_counter( 1 )
{}

//----------------------------------------------------------------------------------------
// Главный алгоритм поиска компонент сильной связности в графе ограничений
//---
template <class Graph, class Vis, class VPropMap>
void MtStrongComponents<Graph,Vis,VPropMap>::operator() ()
{
  m_vis.Start( m_diGraph );

  std::vector<vertex> stack;
  stack.reserve( m_diGraph.NumVertices() );
  m_counter = 1;

  vertex_iterator vIter, vLast;
  
  for ( tie(vIter,vLast) = m_diGraph.Vertices(); vIter!=vLast; ++vIter )
  {
    num[*vIter] = 0;
  }

  for ( tie(vIter,vLast) = m_diGraph.Vertices(); vIter!=vLast; ++vIter )
  {
    if ( num[*vIter] == 0 && !m_vis.IsFiltered(m_diGraph,*vIter) )
      StrongSearch( *vIter, stack );
  }
}

//#define _RECURSIVE_STRONG_SEARCH 1

#ifdef _RECURSIVE_STRONG_SEARCH

//----------------------------------------------------------------------------------------
/// Алгоритм поиска компонент сильной связности в орграфе
/**    
    Алгоритм применяется для разбиения графа ограничений на независимо
  решаемые подсистемы (сегменты). Рекурсивный вариант. Описание алгоритма приведено 
  в книжке Асанова по теории графов, стр.171.\n
  \param vx - корневая вершина поддерева DFS
  \param stack - стек рассмотренных вершин, для которых не установлена компонентная принадлежность
*/
//---
template <class Graph, class Vis, class VPropMap>
void MtStrongComponents<Graph,Vis,VPropMap>::StrongSearch( vertex vx, std::vector<vertex> & stack )
{
  PRECONDITION( !m_vis.IsFiltered(m_diGraph,vx) );

  num[vx] = m_counter;
  lval[vx] = m_counter;
  ++m_counter;
  stack.push_back( vx );
  
  edge_iterator eIter, eLast; // итераторы обхода инцидентных ребер
  for ( tie(eIter,eLast) = m_diGraph.OutArcs(vx); eIter!=eLast; ++eIter )
  {
    vertex w = m_diGraph.Target( *eIter ); // Выходящая вершина прямого ребра
    PRECONDITION( w != vx ); // Граф не ориентированный !!!
    if ( w != vx && !m_vis.IsFiltered(m_diGraph,w) )  // игнорируем обратное ребро из w в vx, а также отфильтрованные узлы;
    {  
      if ( num[w] == 0 ) // <v,w> - "древесная" дуга
      {
        StrongSearch( w, stack );
        if ( lval[w] < lval[vx] ) // При выходе из рекурсии значение l(w) должно быть уже насчитано;
          lval[vx] = lval[w];
      }
      else
      {          
        const size_t wNum = num[w];
        if ( wNum < num[vx] && wNum < lval[vx] ) // <v,w> - "поперечная" или "обратная" дуга
        {
          // Предположение: В стеке лежат вершины, из которых вершина vx достижима;
          if ( std::find(stack.rbegin(), stack.rend(), w) != stack.rend() )
          {              
            lval[vx] = wNum; 
          }
        }
      }
    }
  }  
  
  const size_t vNum = num[vx];
  if ( lval[vx] == vNum ) // vx - корневая вершина очередной компоненты сильной связности
  {
    // Обнаружен очередной сильный компонент
    if ( !stack.empty() && num[stack.back()] >= vNum )
    {
      // Посчитать размер компонента
      typename std::vector<vertex>::reverse_iterator vIter, vLast;
      vIter = stack.rbegin();
      vLast = stack.rend();
      ptrdiff_t compSize = 0;
      for ( ; vIter != vLast && num[*vIter] >= vNum; ++vIter, ++compSize );
        
      // Передать диапазон компонента визитеру
      typename std::vector<vertex>::iterator cIter, cLast;
      cIter = cLast = stack.end();
      std::advance( cIter, -compSize );
      m_vis.Component( m_diGraph, cIter, cLast );
      stack.erase( cIter, cLast ); // очистить верхушку стека
    }
  }
}

#else // _RECURSIVE_STRONG_SEARCH


//----------------------------------------------------------------------------------------
/// Стековый элемент для алгоритма обхода в глубину
//---
template<class Graph>
struct DFS_element
{
  typedef typename Graph::vertices_size_t vertices_size_t;
  typedef typename Graph::vertex          vertex;
  typedef typename Graph::edge_iterator  edge_iterator;

  vertex        node;
  edge_iterator iter;
  edge_iterator last;

  DFS_element( vertex v, const std::pair<edge_iterator,edge_iterator> & pair )
    : node( v )
    , iter( pair.first )
    , last( pair.second )
  {}
  
  DFS_element( vertex v, const Graph & graph )
    : node( v )
    , iter()
    , last()
  {
    tie( iter, last ) = graph.OutArcs( v ); 
  }  

  DFS_element( const DFS_element & vi )
    : node( vi.node )
    , iter( vi.iter )
    , last( vi.last )
  {}

  DFS_element & operator = ( const DFS_element & vi )
  {      
    node = vi.node;
    iter = vi.iter;
    last = vi.last;
    return *this;
  }  
};

//----------------------------------------------------------------------------------------
/// Алгоритм поиска компонент сильной связности в орграфе
/**    
    Алгоритм применяется для разбиения графа ограничений на независимо-решаемые 
  подсистемы (сегменты). Описание алгоритма приведено в книжке Асанова по 
  теории графов, стр.171.\n
    MA2013-02-22: Алгоритм переделан под нерекурсивный вариант;
  \param rootVert - корневая вершина поддерева DFS
  \param comStack - стек рассмотренных вершин, для которых не установлена компонентная принадлежность
*/
//---
template <class Graph, class Vis, class VPropMap>
void MtStrongComponents<Graph,Vis,VPropMap>::StrongSearch(  vertex rootVert
                                                          , std::vector<vertex> & comStack )
{  
  typedef DFS_element<Graph> DfsStackElem;  

  PRECONDITION( !m_vis.IsFiltered(m_diGraph,rootVert) );
  std::vector<DfsStackElem> dfsStack;  
  
  num[rootVert] = lval[rootVert] = m_counter;
  ++m_counter;
  comStack.push_back( rootVert );  
  dfsStack.push_back( DfsStackElem( rootVert, m_diGraph ) );
  DfsStackElem * topElem = &dfsStack.back();    

  while( !dfsStack.empty() ) // Цикл возвратов из стека (одна итерация - одно возвращение против древесного ребра )
  {    
    while ( topElem->iter != topElem->last )
    {
      vertex w = m_diGraph.Target( *topElem->iter ); // Выходящая вершина прямого ребра <v,w>
      PRECONDITION( w != topElem->node ); // Граф не ориентированный !!!
      if ( (w != topElem->node) && !m_vis.IsFiltered(m_diGraph,w) )  // игнорируем обратное ребро из w в vx, а также отфильтрованные узлы;
      {  
        if ( num[w] == 0 ) // <v,w> - "древесная" дуга
        {          
          // Вместо рекурсии: StrongSearch( w, stack );          
          num[w] = lval[w] = m_counter;
          ++m_counter;
          comStack.push_back( w );
          dfsStack.push_back( DfsStackElem(w, m_diGraph) );
          topElem = &dfsStack.back();
          continue;
        }
        else
        {          
          const size_t wNum = num[w];
          if ( wNum < num[topElem->node] && wNum < lval[topElem->node] ) // <v,w> - "поперечная" или "обратная" дуга
          {
            // Предположение: В стеке лежат вершины, из которых вершина vx достижима;
            if ( std::find(comStack.rbegin(), comStack.rend(), w) != comStack.rend() )
            {              
              lval[topElem->node] = wNum; 
            }
          }
        }
      }
      ++topElem->iter;
    }

    PRECONDITION( dfsStack.back().iter == dfsStack.back().last );
    PRECONDITION( topElem == &dfsStack.back() );
    
    // Завершено посещение узла sElem->m_node
    const size_t vNum = num[topElem->node/*vx*/];
    if ( lval[topElem->node/*vx*/] == vNum ) // vx - корневая вершина очередной компоненты сильной связности
    {
      // Обнаружен очередной сильный компонент
      if ( !comStack.empty() && num[comStack.back()] >= vNum )
      {
        // Посчитать размер компонента
        typename std::vector<vertex>::reverse_iterator vIter, vLast;
        vIter = comStack.rbegin();
        vLast = comStack.rend();
        ptrdiff_t compSize = 0;
        for ( ; vIter != vLast && num[*vIter] >= vNum; ++vIter, ++compSize );
          
        // Передать диапазон компонента визитеру
        typename std::vector<vertex>::iterator cIter, cLast;
        cIter = cLast = comStack.end();
        std::advance( cIter, -compSize );
        m_vis.Component( m_diGraph, cIter, cLast );
        comStack.erase( cIter, cLast ); // очистить верхушку стека
      }
    }
    // Возвращение против древесного ребра <v,w>, где w-просмотренная вершина, v-вершина из которой пришли в w;
    {      
      const vertex w = topElem->node;
      dfsStack.pop_back();
      
      if ( !dfsStack.empty() )
      {
        topElem = &dfsStack.back();
        const vertex vxPrev = dfsStack.back().node;
        // При выходе из рекурсии значение lVal(w) должно быть уже насчитано;
        if ( lval[w] < lval[vxPrev] ) 
        {
          lval[vxPrev] = lval[w];
        }
      }
    }
  }
}

#endif // _RECURSIVE_STRONG_SEARCH

#endif // __GRAPH_ALGORITHMS_H

// eof
