////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Диагностика оболочек и их составляющих.
         \en Diagnostics of shells and their components. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CHECK_GEOMETRY_H
#define __CHECK_GEOMETRY_H

#include <templ_rp_array.h>
#include <templ_sptr.h>
#include <mb_operation_result.h>
#include <mb_variables.h>
#include <topology.h>
#include <solid.h>
#include <point_frame.h>
#include <vector>
#include <iterator>
#include <utility>


//------------------------------------------------------------------------------
/** \brief \ru Информация о пересечении двух тел.
           \en Information about two solids intersection. \~
  \details \ru Информация о пересечении двух тел при диагностике их оболочек. \n
           \en Information about intersection of two solids during diagnostics of their shells. \n \~
  \ingroup Algorithms_3D
*/
//---
struct MATH_CLASS MbIntersectionData {
protected:
  c3d::EdgesSPtrVector edges;          ///< \ru Ребра пересечения (владеет по счетчику ссылок). \en Intersection edges (owns by reference counter). 
  c3d::IndicesVector   faceIndices1;   ///< \ru Номера касающихся граней первого тела. \en The numbers concerning faces of the first  solid.
  c3d::IndicesVector   faceIndices2;   ///< \ru Номера касающихся граней второго тела. \en The numbers concerning faces of the second solid.

  c3d::SolidSPtr       solid;          ///< \ru Тело пересечения  (владеет по счетчику ссылок). \en Intersection solid (owns by reference counter). 

  c3d::PointFrameSPtr  pointFrame;     ///< \ru Группа точек касания. \en Group of touch points. 

  bool                 isTangentCurve; ///< \ru Пересечения - это линии касания. \en Intersections are tangency lines. 
  bool                 isSolid;        ///< \ru Пересечения образуют тела. \en Intersections form solids.

public:
  /// \ru Конструктор. \en Constructor. 
  MbIntersectionData();
  /// \ru Конструктор по ребру. \en Constructor by an edge. 
  MbIntersectionData( const MbCurveEdge & );
  /// \ru Конструктор по ребрам. \en Constructor by edges. 
  template <class EdgesVector>
  MbIntersectionData( const EdgesVector &, bool isSolidEdges );
  /// \ru Конструктор по ребрам. \en Constructor by edges. 
  template <class EdgesVector, class FaceIndicesVector>
  MbIntersectionData( const EdgesVector &, const FaceIndicesVector & faceNumbers1, const FaceIndicesVector & faceNumbers2 );
  /// \ru Конструктор по ребрам. \en Constructor by edges. 
  template <class EdgesVector>
  MbIntersectionData( const EdgesVector &, const c3d::IndicesPairsVector & faceNumbersPairs );
  /// \ru Конструктор по телу. \en Constructor by a solid. 
  explicit MbIntersectionData( const MbSolid & );
  /// \ru Конструктор по точкам. \en Constructor by points. 
  explicit MbIntersectionData( const std::vector<MbCartPoint3D> & );
  /// \ru Конструктор по вершинам и флагу использования этих объектов, а не их копий. \en Constructor by vertices and by flag of use of these objects instead of their copies. 
  explicit MbIntersectionData( const c3d::ConstVerticesVector &, bool same );
  /// \ru Конструктор по вершинам и флагу использования этих объектов, а не их копий. \en Constructor by vertices and by flag of use of these objects instead of their copies. 
  explicit MbIntersectionData( const c3d::ConstVerticesSPtrVector &, bool same );
  /// \ru Деструктор. \en Destructor. 
  ~MbIntersectionData();

public:
        /// \ru Пересечение - есть тело. \en Intersection is a solid. 
        bool            IsSolid()   const { return ((solid != NULL) || (isSolid && !edges.empty())); }
        /// \ru Пересечение касательной областью поверхности. \en Intersection by a tangent region of a surface. 
        bool            IsSurface() const { return !isTangentCurve && !edges.empty(); } 
        /// \ru Пересечение вдоль касательной линии. \en Intersection along a tangent line. 
        bool            IsCurve()   const { return  isTangentCurve && !edges.empty(); }
        /// \ru Пересечение точкой (еще не реализовано). \en Intersection is a point (not implemented yet). 
        bool            IsPoint()   const { return ((pointFrame != NULL) && (pointFrame->GetVerticesCount() > 0)); } 

        /// \ru Установить флаг пересечения вдоль касательной линии. \en Set the flag of intersection along a tangent line. 
        //void            SetTangent( bool b ) { isTangentCurve = b; } 

        /// \ru Отдать указатель для просмотра тела. \en Get a pointer for viewing the solid. 
  const MbSolid     *   GetSolid() const { return solid; } 
        /// \ru Отдать указатель для просмотра/модификации тела. \en Get a pointer for viewing/modification of the solid. 
        MbSolid     *   SetSolid()       { return solid; }

        /// \ru Количество кривых пересечения. \en The number of intersection curves. 
        size_t          GetCurvesCount() const { return edges.size(); } 
        /// \ru Получить массив кривых пересечения. \en Get the intersection curve array. 
        template <class EdgesVector>
        void            GetCurves( EdgesVector & curves ) const;
        /// \ru Получить указатель на кривую пересечения по индексу. \en Get a pointer to an intersection curve by the index. 
  const MbCurveEdge *   GetCurve( size_t k ) const { return ((k < edges.size()) ? edges[k].get() : NULL); } 
        /// \ru Получить номера касающихся граней первого/второго тела. \en Get numbers concerning faces of the first/second solid. 
        template <class OutputIndicesVector>
        void            GetFaceNumbers( bool first, OutputIndicesVector & ) const;
        /// \ru Получить номера касающихся граней первого и второго тел. \en Get numbers concerning faces of the first and second solids. 
        template <class OutputIndicesPairsVector>
        void            GetFaceNumbersPairs( OutputIndicesPairsVector & ) const;

        /// \ru Количество точек касания. \en The number of touch points. 
        size_t          GetPointsCount() const { return ((pointFrame != NULL) ? pointFrame->GetVerticesCount() : 0); }
        /// \ru Получить набор точек касания. \en Get a set of touch points. 
  const MbPointFrame *  GetPointFrame() const { return pointFrame; }

OBVIOUS_PRIVATE_COPY( MbIntersectionData ) // \ru Не реализовано \en Not implemented 
};


//------------------------------------------------------------------------------
// \ru Конструктор по ребрам. \en Constructor by edges. 
//---
template <class EdgesVector>
MbIntersectionData::MbIntersectionData( const EdgesVector & initEdges, bool isSolidEgdes )
  : edges         (              )
  , faceIndices1  (              )
  , faceIndices2  (              )
  , solid         ( NULL         )
  , pointFrame    ( NULL         )
  , isTangentCurve( false        )
  , isSolid       ( isSolidEgdes )
{
  size_t addCnt = initEdges.size();
  if ( addCnt > 0 ) {
    c3d::EdgeSPtr edge;
    edges.reserve( addCnt );
    for ( size_t k = 0; k < addCnt; ++k ) {
      if ( initEdges[k] != NULL ) {
        edge = const_cast<MbCurveEdge *>( &(*initEdges[k]) );
        edges.push_back( edge );
      }
    }
  }
}


//------------------------------------------------------------------------------
// \ru Конструктор по ребрам. \en Constructor by edges. 
//---
template <class EdgesVector, class FaceIndicesVector>
MbIntersectionData::MbIntersectionData( const EdgesVector &       initEdges, 
                                        const FaceIndicesVector & faceInds1,
                                        const FaceIndicesVector & faceInds2 )
  : edges         (       )
  , faceIndices1  (       )
  , faceIndices2  (       )
  , solid         ( NULL  )
  , pointFrame    ( NULL  )
  , isTangentCurve( false )    
  , isSolid       ( false )
{ 
  size_t edgesCnt = initEdges.size();

  if ( edgesCnt > 0 ) {
    c3d::EdgeSPtr edge;
    edges.reserve( edgesCnt );
    for ( size_t k = 0; k < edgesCnt; ++k ) {
      if ( initEdges[k] != NULL ) {
        edge = const_cast<MbCurveEdge *>(&(*initEdges[k]));
        edges.push_back( edge );
      }
    }
    std::copy( faceInds1.begin(), faceInds1.end(), std::back_inserter( faceIndices1 ) );
    std::copy( faceInds2.begin(), faceInds2.end(), std::back_inserter( faceIndices2 ) );
  }
}


//------------------------------------------------------------------------------
// \ru Конструктор по ребрам. \en Constructor by edges. 
//---
template <class EdgesVector>
MbIntersectionData::MbIntersectionData( const EdgesVector &             initEdges,
                                        const c3d::IndicesPairsVector & faceIndicesPairs )
  : edges         (       )
  , faceIndices1  (       )
  , faceIndices2  (       )
  , solid         ( NULL  )
  , pointFrame    ( NULL  )
  , isTangentCurve( false )
  , isSolid       ( false )
{
  size_t edgesCnt = initEdges.size();

  if ( edgesCnt > 0 ) {
    c3d::EdgeSPtr edge;
    edges.reserve( edgesCnt );
    size_t k;
    for ( k = 0; k < edgesCnt; ++k ) {
      if ( initEdges[k] != NULL ) {
        edge = const_cast<MbCurveEdge *>(&(*initEdges[k]));
        edges.push_back( edge );
      }
    }
    size_t facePairsCnt = faceIndicesPairs.size();
    faceIndices1.reserve( facePairsCnt );
    faceIndices2.reserve( facePairsCnt );
    for ( k = 0; k < facePairsCnt; ++k ) {
      faceIndices1.push_back( faceIndicesPairs[k].first );
      faceIndices2.push_back( faceIndicesPairs[k].second );
    }
  }
}


//------------------------------------------------------------------------------
// \ru Получить массив кривых пересечения. \en Get the intersection curve array. 
//---
template <class EdgesVector>
void MbIntersectionData::GetCurves( EdgesVector & dstEdges ) const
{
  size_t addCnt = edges.size();
  c3d::EdgeSPtr edge;
  dstEdges.reserve( dstEdges.size() + addCnt );
  for ( size_t k = 0; k < addCnt; ++k ) {
    edge = const_cast<MbCurveEdge *>( &(*edges[k]) );
    dstEdges.push_back( edge );
    ::DetachItem( edge );
  }
}


//------------------------------------------------------------------------------
// \ru Получить номера касающихся граней первого/второго тела. \en Get numbers concerning faces of the first/second solid. 
//---
template <class OutputIndicesVector>
void MbIntersectionData::GetFaceNumbers( bool first, OutputIndicesVector & outputIndices ) const
{ 
  const c3d::IndicesVector & faceIndices = first ? faceIndices1 : faceIndices2;
  size_t addCnt = faceIndices.size();
  if ( addCnt > 0 ) {
    outputIndices.reserve( outputIndices.size() + addCnt );
    for ( size_t k = 0; k < addCnt; ++k ) {
      outputIndices.push_back( faceIndices[k] );
    }
  }
}


//------------------------------------------------------------------------------
// \ru Получить номера касающихся граней первого и второго тел. \en Get numbers concerning faces of the first and second solids. 
//---
template <class OutputIndicesPairsVector>
void MbIntersectionData::GetFaceNumbersPairs( OutputIndicesPairsVector & outputIndicesPairs ) const
{
  size_t addCnt = std_min( faceIndices1.size(), faceIndices2.size() );
  if ( addCnt > 0 ) {
    outputIndicesPairs.reserve( outputIndicesPairs.size() + addCnt );
    for ( size_t k = 0; k < addCnt; ++k ) {
      outputIndicesPairs.push_back( std::make_pair( faceIndices1[k], faceIndices2[k] ) );
    }
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Проверка вырожденности кривой в трехмерном пространстве.
           \en Check for the curve degeneration in three-dimensional space. \~
  \details \ru Проверка вырожденности кривой в трехмерном пространстве. \n
           \en Check for the curve degeneration in three-dimensional space. \n \~
  \param[in] curve - \ru Кривая.
                     \en Curve. \~
  \param[in] eps - \ru Неразличимая метрическая область, критерий вырождения кривой.
                   \en Indistinguishable metric domain, curve degeneration criterion. \~
  \return \ru Возвращает состояние вырожденности кривой.
          \en Returns the state of the curve degeneration. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) IsDegeneratedCurve( const MbCurve3D & curve, double eps );


//------------------------------------------------------------------------------
/// \ru Проверка на полное совпадение двух кривых пересечения поверхностей c метрической точностью lenEps \en Check for complete coincidence of two intersection curves of surfaces with metric tolerance lenEps 
//---
bool IsCoincidentCurves( const MbSurfaceIntersectionCurve & intCurve1,
                         const MbSurfaceIntersectionCurve & intCurve2,
                         double lenEps );


//------------------------------------------------------------------------------
/** \brief \ru Проверка оболочки тела на замкнутость.
           \en Check of solid's shell for closedness. \~
  \details \ru Проверка оболочки тела на замкнутость. \n
           \en Check of solid's shell for closedness. \n \~
  \param[in] shell - \ru Оболочка.
                     \en A shell. \~
  \param[in] checkChangedOnly - \ru Проверять только измененные грани оболочки.
                                \en Only modified faces of a shell are to be checked. \~
  \return \ru Возвращает состояние замкнутости оболочки.
          \en Returns the state of shell closedness. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) CheckShellClosure( const MbFaceShell & shell, bool checkChangedOnly = false );


//------------------------------------------------------------------------------
/** \brief \ru Проверка оболочки тела на замкнутость.
           \en Check of solid's shell for closedness. \~
  \details \ru Проверка оболочки тела на замкнутость. \n
           \en Check of solid's shell for closedness. \n \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) CheckSolidClosure( const MbSolid & solid );



////////////////////////////////////////////////////////////////////////////////
//
// \ru Функции для проверки элементов оболочки \en Functions for checking shell's elements 
//
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
/** \brief \ru Поиск краевых ребер замкнутой оболочки.
           \en Search for the boundary edges of a closed shell. \~
  \details \ru Поиск краевых ребер замкнутой оболочки. \n
               Краевое ребер - это ребро у которого нет ссылки на одну из смежных граней. \n
               Наличие краевых ребер замкнутой оболочки может приводит к отказу операций над оболочкой,
               если операцией будет затронута часть оболочки с краевыми ребрами. \n
               Наличие одиночных краевых ребер практически никак не влияет на правильность расчета МЦХ.
               Множественные краевые ребра, особенно в виде связных цепочек, являются серьезным дефектом замкнутой оболочки. \n
           \en Search for the boundary edges of a closed shell. \n
               Boundary edge is an edge that has no reference to one of the adjacent faces. \n
               The presence of boundary edges of a closed shell may lead to failure of operations on the shell, 
               if the operation affects a part of the shell with such edges. \n
               The presence of single boundary edges has practically no effect on the correctness of the MIP calculation. \n 
               Multiple boundary edges, especially in the form of related chains, is a serious defect of the closed shell. \n \~
  \param[in] allEdges - \ru Множество ребер оболочки.
                        \en Set of edges of a shell. \~
  \param[in] boundaryEdges - \ru Множество найденных краевых ребер.
                             \en Set of found boundary edges. \~
  \return \ru Возвращает true, если найдено хотя бы одно краевое ребро.
          \en Returns true if at least one boundary edges is found. \~
  \ingroup Algorithms_3D
*/
// ---
template <class Edges>
bool CheckBoundaryEdges( const Edges & allEdges, Edges * boundaryEdges )
{
  bool isBoundary = false;
  C3D_ASSERT( boundaryEdges != &allEdges );

  if ( boundaryEdges != &allEdges ) {
    for ( size_t i = 0, cnt = allEdges.size(); i < cnt; ++i ) {
      if ( allEdges[i] != NULL && allEdges[i]->IsBoundaryFace( METRIC_PRECISION ) ) {
        isBoundary = true;
        if ( boundaryEdges != NULL )
          boundaryEdges->push_back( allEdges[i] );
        else
          break;
      }
    }
  }

  return isBoundary;
}

//------------------------------------------------------------------------------
/** \brief \ru Поиск некорректных ребер.
           \en Search of incorrect edges. \~
  \details \ru Поиск некорректных ребер. Не ищет краевые ребра замкнутой оболочки. \n
               Для поиска краевых ребер используйте функцию CheckBoundaryEdges. \n
               Функция проверяет следующие варианты некорректности ребер :
               1. Ребро с типом граница (cbt_Boundary) должно указывать только на одну грань \n
               2. Поверхности в кривой пересечения ребра должны быть такие же как и поверхности в смежных гранях ребра \n
               3. Граничные точки поверхностных кривых в кривой пересечения ребра должны совпадать с точностью не хуже 1e-6 или толерантности в вершинах ребра \n
               4. Опорные точки сплайнов поверхностных кривых в уточняемой кривой пересечения (cbt_Specific) должны совпадать в пространстве c точностью не хуже 1e-6 \n
               Наличие некорректных ребер является серьезным дефектом оболочки. \n
           \en Search of incorrect edges. Does not look for the boundary edges of a closed shell. \n
               Use function CheckBoundaryEdges for searching for boundary edges. \n 
               The function checks the next parameters of an edge as signs of its incorrectness :
               1. An edge with the border type cbt_Boundary must point to only one face. \n
               2. The surfaces of the intersection curve of the edge have to be the same as the surfaces in the adjacent faces of the edge. \n
               3. The boundary points of the surface curves in the curve of intersection of the edge must coincide with an accuracy not worse than 1e-6 or tolerance at the vertices of the edge. \n
               4. The reference points of the splines of the surface curves in the intersection curve with the border type cbt_Specific must coincide in space with an accuracy not worse than 1e-6. \n
               The presence of incorrect edges is a serious defect of the shell. \n \~
  \param[in] allEdges - \ru Множество ребер оболочки.
                        \en Set of edges of a shell. \~
  \param[in] badEdges - \ru Множество найденных некорректных ребер.
                        \en Set of found incorrect edges. \~
  \return \ru Возвращает true, если найдено хотя бы одно некорректное ребро.
          \en Returns true if at least one incorrect edge is found. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) CheckBadEdges( const RPArray<MbCurveEdge> & allEdges,
                                RPArray<MbCurveEdge> * badEdges );

//------------------------------------------------------------------------------
/** \brief \ru Поиск неточных вершин.
           \en Search for inexact vertices. \~
  \details \ru Поиск неточных вершин оболочки. \n
               Наличие неточных вершин не является серьезным дефектом оболочки.
               В большинстве случаев никак не влияет на работу операций с оболочкой.
               Не влияет на расчет МЦХ. \n
           \en Search for inexact vertices of a shell. \n 
               The presence of inaccurate vertices is not a serious shell defect. 
               In most cases, does not affect on the result of operations with this shell. 
               Does not affect the calculation of the MIP. \n \~
  \param[in] vertArr - \ru Множество вершин оболочки.
                       \en Set of shell's vertices. \~
  \param[in] mAcc - \ru Порог отбора неточных вершин.
                    \en Accuracy of inexact vertices filtration. \~
  \param[in] inexactVerts - \ru Множество для неточных вершин.
                            \en Set of inexact vertices. \~
  \return \ru Возвращает true, если найдена хотя бы одна неточная вершина.
          \en Returns true if at least one inexact vertex is found. \~
  \ingroup Algorithms_3D
*/
// ---
template <class Vertices>
bool CheckInexactVertices( const Vertices & vertArr, double mAcc, Vertices * inexactVerts )
{
  bool isInexactVertex = false;
  C3D_ASSERT( inexactVerts != &vertArr );

  if ( inexactVerts != &vertArr ) {
    for ( size_t i = 0, icnt = vertArr.size(); i < icnt; ++i ) {
      MbVertex * v = vertArr[i];
      if ( v != NULL && v->GetTolerance() > mAcc ) {
        isInexactVertex = true;
        if ( inexactVerts != NULL )
          inexactVerts->push_back( v );
        else
          break;
      }
    }
  }

  return isInexactVertex;
}


//------------------------------------------------------------------------------
/** \brief \ru Является ли кривая пересечения ребра неточной.
           \en Is the curve of intersection edges inaccurate. \~
  \details \ru Является ли кривая пересечения ребра неточной (оценочно). \n
               Наличие неточных ребер (кривых пересечения) не является серьезным дефектом оболочки.
               В большинстве случаев никак не влияет на работу операций с оболочкой.
               Незначительно влияет на расчет МЦХ. \n
           \en Is the curve of intersection edges inaccurate (estimated). \n 
               The presence of inaccurate edges is not a serious shell defect.
               In most cases, does not affect on the result of operations with this shell.
               Can slightly affect the calculation of the MIP. \n \~
  \param[in] edge - \ru Ребро оболочки.
                    \en The edge of the shell. \~
  \param[in] mMaxAcc - \ru Порог отбора неточного ребра.
                       \en Accuracy selection inaccurate ribs. \~
  \return \ru Возвращает true, если ребро неточное.
          \en Returns true, if the edge is inaccurate. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) IsInexactEdge( const MbCurveEdge & edge, double mMaxAcc );


//------------------------------------------------------------------------------
/** \brief \ru Поиск неточных ребер оценочно.
           \en Approximate search of inexact edges. \~
  \details \ru Поиск неточных ребер оболочки оценочно. \n
               Наличие неточных ребер (кривых пересечения) не является серьезным дефектом оболочки.
               В большинстве случаев никак не влияет на работу операций с оболочкой.
               Незначительно влияет на расчет МЦХ. \n
           \en Approximate search of inexact edges of a shell. \n
               The presence of inaccurate edges is not a serious shell defect.
               In most cases, does not affect on the result of operations with this shell.
               Can slightly affect the calculation of the MIP. \n \~
  \param[in] allEdges - \ru Множество ребер оболочки.
                        \en Set of edges of a shell. \~
  \param[in] mAcc - \ru Порог отбора неточных ребер.
                    \en Accuracy of inexact edges filtration. \~
  \param[in] inexactEdges - \ru Множество найденных неточных ребер.
                            \en Set of found inexact edges. \~
  \return \ru Возвращает true, если найдено хотя бы одно неточное ребро.
          \en Returns true if at least one inexact edge is found. \~
  \ingroup Algorithms_3D
*/
// ---
template <class Edges>
bool CheckInexactEdges( const Edges & allEdges, double mAcc, Edges * inexactEdges )
{
  bool isInexactEdge = false;

  for ( size_t i = 0, icnt = allEdges.size(); i < icnt; ++i ) {
    if ( allEdges[i] != NULL) {
      bool isSpaceNear = !::IsInexactEdge( *allEdges[i], mAcc );

      if ( !isSpaceNear ) {
        isInexactEdge = true;
        if ( inexactEdges != NULL )
          inexactEdges->push_back( allEdges[i] );
        else
          break;
      }
      else if ( !allEdges[i]->IsClosed() ) {
        const MbVertex & v1 = allEdges[i]->GetBegVertex();
        const MbVertex & v2 = allEdges[i]->GetEndVertex();
        if ( &v1 == &v2 ) {
          double mTol = v1.GetTolerance();
          double mLen = allEdges[i]->GetLengthEvaluation();
          if ( mLen > METRIC_PRECISION && mLen > mTol + METRIC_PRECISION ) {
            isInexactEdge = true;
            if ( inexactEdges != NULL )
              inexactEdges->push_back( allEdges[i] );
            else
              break;
          }
        }
      }
    }
  }

  return isInexactEdge;
}

//------------------------------------------------------------------------------
/** \brief \ru Проверка подложек и указаний на грани.
           \en Check of substrates and pointers to faces. \~
  \details \ru Проверка подложек и указаний на грани оболочки. \n
               Наличие общих подложек (базовые поверхности в ограниченных кривыми поверхностях) 
               и неверных ссылок на грани в ребрах является серьезным дефектом оболочки. \n
           \en Check of substrates and pointers to faces of a shell. \n 
               The presence of common substrates (base surfaces in bounded curved surfaces) 
               and invalid references to faces in edges is a serious shell defect. \n \~
  \param[in] shell - \ru Проверяемая оболочка.
                     \en A shell to check. \~
  \param[out] areIdenticalBaseSurfaces - \ru Наличие общих подложек.
                                         \en Whether there are common substrates. \~
  \param[out] areBadFacePointers - \ru Наличие неверных указателей на соседние грани.
                                   \en Whether there are invalid pointers to neighboring faces. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (void) CheckBadFaces( const MbFaceShell & shell,
                                bool & areIdenticalBaseSurfaces,
                                bool & areBadFacePointers );


//------------------------------------------------------------------------------
/** \brief \ru Проверка взаимного расположения циклов грани.
           \en Check interposition of face loops. \~
  \details \ru Проверка взаимного расположения циклов грани.
               Функция проверять корректность ориентации циклов грани.
               Неправильная ориентация циклов граней является серьезным дефектом оболочки.
           \en Check interposition of face loops. \n 
               The function is to check the correctness of the orientation of the face loops (chains of oriented edges). 
               Incorrect orientation of face's loops is a serious defect in the shell. \n \~
  \param[in] face - \ru Грань.
                    \en Face. \~
  \return \ru Возвращает true, если расположение и ориентация циклов корректны.
          \en Returns true if interposition of loops and their orientations are correct. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) CheckLoopsInterposition( const MbFace & face );


//------------------------------------------------------------------------------
/** \brief \ru Проверка связности ребер цикла.
           \en Check for connectivity of loop edges. \~
  \details \ru Проверка связности ребер цикла грани.
               Возвращает максимальные метрическую и параметрическую (опционально) погрешности построения цикла. \n
               Наличие неточных стыковок в циклах грани не обязательно является серьезным дефектом оболочки. \n
           \en Check for connectivity of loop edges.
               Returns the maximal metric and parametric (optionally) tolerances of the loop construction. \n
               The presence of inaccurate connection in face loops (chains of oriented edges) is not necessarily a serious shell defect. \n \~
  \param[in] face - \ru Грань, содержащая проверяемый цикл.
                    \en Face containing the loop under test. \~
  \param[in] loop - \ru Цикл грани.
                    \en Face loop. \~
  \param[out] lengthTolerance - \ru Максимальное метрическое значение разрыва между ребрами.
                                \en The maximal metric value of a gap between edges. \~
  \param[out] paramTolerance  - \ru Максимальное параметрическое значение разрыва между ребрами.
                                \en The maximal parametric value of a gap between edges. \~
  \param[out] badLocs         - \ru Пары номеров ориентированных ребер с плохой связностью.
                                \en Edges pairs with bad connectivity. \~
  \return \ru Возвращает true, если связность ребер не нарушена.
          \en Returns true if the connectivity is good. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) CheckLoopConnection( const MbFace & face, const MbLoop & loop, 
                                      double & lengthTolerance, double & paramTolerance,
                                      c3d::IndicesPairsVector & badLocs );

//------------------------------------------------------------------------------
/** \brief \ru Проверка связности ребер цикла.
           \en Check for connectivity of a loop edges. \~
  \details \ru Проверка связности ребер цикла грани.
               Возвращает максимальные метрическую и параметрическую (опционально) погрешности построения цикла. \n
               Наличие неточных стыковок в циклах грани не обязательно является серьезным дефектом оболочки. \n
           \en Check for connectivity of a loop edges.
               Returns the maximal metric and parametric (optionally) tolerances of the loop construction. \n
               The presence of inaccurate connection in face loops (chains of oriented edges) is not necessarily a serious shell defect. \n \~
  \param[in] face - \ru Грань, содержащая проверяемый цикл.
                    \en Face containing the loop under test. \~
  \param[in] loop - \ru Цикл грани.
                    \en Face loop. \~
  \param[out] lengthTolerance - \ru Максимальное метрическое значение разрыва между ребрами.
                                \en The maximal metric value of a gap between edges. \~
  \param[out] paramTolerance  - \ru Максимальное параметрическое значение разрыва между ребрами.
                                \en The maximal parametric value of a gap between edges. \~
  \param[out] badConnectedEdges - \ru Ребра с плохой связностью.
                                  \en Edges with bad connectivity. \~
  \param[out] badVertexEdges - \ru Ребра с неправильными вершинами.
                               \en Edges with incorrect vertices. \~
  \return \ru Возвращает true, если связность ребер не нарушена.
          \en Returns true if the connectivity is good. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) CheckLoopConnection( const MbFace & face, const MbLoop & loop, 
                                      double & lengthTolerance, double * paramTolerance,
                                      RPArray<const MbOrientedEdge> & badConnectedEdges,
                                      RPArray<const MbCurveEdge> & badVertexEdges );

//------------------------------------------------------------------------------
/** \brief \ru Проверка связности ребер цикла.
           \en Check for connectivity of a loop edges. \~
  \details \ru Проверка связности ребер цикла грани.
               Возвращает максимальные метрическую и параметрическую (опционально) погрешности построения цикла. \n
               Наличие неточных стыковок в циклах грани не обязательно является серьезным дефектом оболочки. \n
           \en Check for connectivity of a loop edges.
               Returns the maximal metric and parametric (optionally) tolerances of the loop construction. \n 
               The presence of inaccurate connection in face loops (chains of oriented edges) is not necessarily a serious shell defect. \n \~
  \param[in] face - \ru Грань, содержащая проверяемый цикл.
                    \en Face containing the loop under test. \~
  \param[in] loop - \ru Цикл грани.
                    \en Face loop. \~
  \param[out] lengthTolerance - \ru Максимальное метрическое значение разрыва между ребрами.
                                \en The maximal metric value of a gap between edges. \~
  \param[out] paramTolerance  - \ru Максимальное параметрическое значение разрыва между ребрами.
                                \en The maximal parametric value of a gap between edges. \~
  \param[out] badConnectedEdges - \ru Ребра с плохой связностью.
                                  \en Edges with bad connectivity. \~
  \return \ru Возвращает true, если связность ребер не нарушена.
          \en Returns true if the connectivity is good. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) CheckLoopConnection( const MbFace & face, const MbLoop & loop, 
                                      double & lengthTolerance, double * paramTolerance,
                                      RPArray<const MbOrientedEdge> & badConnectedEdges );

//------------------------------------------------------------------------------
/** \brief \ru Проверка связности ребер цикла.
           \en Check for connectivity of a loop edges. \~
  \details \ru Проверка связности ребер цикла грани.
               Возвращает максимальные метрическую и параметрическую (опционально) погрешности построения цикла. \n
               Наличие неточных стыковок в циклах грани не обязательно является серьезным дефектом оболочки. \n
           \en Check for connectivity of a loop edges.
               Returns the maximal metric and parametric (optionally) tolerances of the loop construction. \n
               The presence of inaccurate connection in face loops (chains of oriented edges) is not necessarily a serious shell defect. \n \~
  \param[in] face - \ru Грань, содержащая проверяемый цикл.
                    \en Face containing the loop under test. \~
  \param[in] loop - \ru Цикл грани.
                    \en Face loop. \~
  \param[out] lengthTolerance - \ru Максимальное метрическое значение разрыва между ребрами.
                                \en The maximal metric value of a gap between edges. \~
  \param[out] paramTolerance  - \ru Максимальное параметрическое значение разрыва между ребрами.
                                \en The maximal parametric value of a gap between edges. \~
  \return \ru Возвращает true, если связность ребер не нарушена.
          \en Returns true if the connectivity is good. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) CheckLoopConnection( const MbFace & face, const MbLoop & loop, 
                                      double & lengthTolerance, double * paramTolerance );


//------------------------------------------------------------------------------
/** \brief \ru Найти циклы грани с самопересечениями.
           \en Find face loops with self-intersections. \~
  \details \ru Найти циклы грани с самопересечениями.
               Возвращает найденные циклы с самопересечениям. \n
               Наличие самопересечений в циклах граней является серьезным дефектом оболочки. \n
           \en Find face loops with self-intersections.
               Returns the found loops with self-intersections. \n 
               The presence of self-intersections in face loops is a serious shell defect. \n \~
  \param[in] face - \ru Грань, содержащая проверяемые циклы.
                    \en Face containing loops under test. \~
  \param[in] nameMaker - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[in] checkInsideEdges - \ru Искать самопересечения внутри области определения двумерных кривых ребер.
                                \en Find edges with self-intersections inside. \~
  \param[out] loopPnts - \ru Точки самопересечения c номерами циклов.
                         \en Points of self-intersecting loops and the numbers of loops. \~
  \return \ru Возвращает true, если найдены самопересечения циклов.
          \en Returns true if the self-intersection has been found. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) FindLoopsSelfIntersections( const MbFace & face, const MbSNameMaker & nameMaker, bool checkInsideEdges,
                                             std::vector< std::pair<c3d::IndicesPair, MbCartPoint3D> > * loopPnts );


//------------------------------------------------------------------------------
/** \brief \ru Проверка связности граней faces.
           \en Check for connectivity of faces 'faces'. \~
  \details \ru Проверка топологической связности граней faces. \n
           \en Check for topological connectivity of faces 'faces'. \n \~
  \param[in] faces - \ru Проверяемый набор граней.
                     \en Set of faces under check. \~
  \return \ru Возвращает true, все грани топологически связаны.
          \en Returns true if all the faces are topologically connected. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) CheckFacesConnection( const RPArray<MbFace> & faces );


//------------------------------------------------------------------------------
/** \brief \ru Найти в исходной оболочке "родительские" грани производной оболочки.
           \en Find "parent" faces of a derived shell in the initial shell. \~
  \details \ru Найти в исходной оболочке "родительские" грани производной оболочки геометрическим поиском подобных граней с наложением. \n
               Флаг sameNormals установить false, если исходная оболочка участвовала в булевом вычитании тел вторым операндом. \n
           \en Find "parent" faces of a derived shell in the initial shell by geometric search of similar faces with overlapping. \n
               Flag sameNormals is to be set to false if the initial shell was involved in the boolean subtraction of solids as a second operand. \n \~
  \param[in] srcShell - \ru Исходная оболочка.
                        \en The source shell. \~
  \param[in] dstShell - \ru Производная оболочка.
                        \en The derived shell. \~
  \param[in] sameNormals - \ru Искать с одинаковым (true) или противоположным (false) направлением нормалей.
                           \en Search with the same (true) or the opposite (false) direction of normals. \~
  \param[out] simPairs - \ru Множество соответствий - номеров граней в исходной и производной оболочках.
                         \en Set of correspondences - indices of faces in the initial and the derived shells. \~
  \return \ru Возвращает true, все найдено хоть одно соответствие.
          \en Returns true if at least one correspondence is found. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) FindOverlappingSimilarFaces( const MbFaceShell &             srcShell, 
                                              const MbFaceShell &             dstShell, 
                                                    bool                      sameNormals,
                                                    c3d::IndicesPairsVector & simPairs );


//------------------------------------------------------------------------------
/** \brief \ru Найти на каких гранях исходной оболочки базируются ребра производной оболочки.
           \en Find faces edges of the derived shell are based on. \~
  \details \ru Найти на каких гранях исходной оболочки базируются ребра производной оболочки геометрическим поиском. 
    Поиск соответствия проводится по поверхностям из граней, на которые ссылается ребро, а не по поверхностям в кривой пересечения ребра. 
    Флаг sameNormals установить false, если исходная оболочка участвовала в булевом вычитании тел вторым операндом. \n
           \en Determine on which faces of the initial shell edges of the derived shell are based on by the geometric search. 
    Search of the correspondence is performed by surfaces from faces the edge refers to, but not by surfaces from the intersection curve of the edge. 
    Flag sameNormals is to be set to false if the initial shell was involved in the boolean subtraction of solids as a second operand. \n \~
  \param[in] edges - \ru Ребра производной оболочки.
                     \en Edges of an arbitrary shell. \~
  \param[in] shell - \ru Исходная оболочка.
                     \en The source shell. \~
  \param[in] sameNormals - \ru Искать с одинаковым (true) или противоположным (false) направлением нормалей.
                           \en Search with the same (true) or the opposite (false) direction of normals. \~
  \param[out] efPairs - \ru Множество соответствий - номеров ребер во входном массиве и номеров граней в исходной оболочке.
                        \en Set of correspondence - indices of edges in the input array and numbers of faces in the input shell. \~
  \return \ru Возвращает true, все найдено хоть одно соответствие.
          \en Returns true if at least one correspondence is found. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC (bool) FindFacesEdgesCarriers( const c3d::ConstEdgesVector &   edges, 
                                         const MbFaceShell &             shell, 
                                               bool                      sameNormals,
                                               c3d::IndicesPairsVector & efPairs );

//------------------------------------------------------------------------------
/** \brief \ru Починить некорректное ребро оболочки.
           \en Repair incorrect edge of a shell. \~
  \details \ru Починить некорректное ребро оболочки (псевдо-толерантное, псевдо-точное). \n
           \en Repair incorrect edge of a shell (pseudo-tolerant, pseudo-exact). \n \~
  \param[in] edge - \ru Ребро оболочки.
                    \en Shell edge. \~
  \param[in] updateFacesBounds - \ru Обновить границы поверхностей в гранях ребра.
                                 \en Update surface bounds of edge faces. \~
  \return \ru Возвращает true, если была выполнена модификация ребра.
          \en Returns true if edge modification was performed. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC( bool ) RepairEdge( MbCurveEdge & edge, bool updateFacesBounds );


//------------------------------------------------------------------------------
/** \brief \ru Починить некорректные ребра оболочки.
           \en Repair incorrect edges of a shell. \~
  \details \ru Починить некорректное ребро оболочки (псевдо-толерантное, псевдо-точное). \n
           \en Repair incorrect edge of a shell (pseudo-tolerant, pseudo-exact). \n \~
  \param[in] shell - \ru Оболочка.
                    \en Shell. \~
  \param[in] updateFacesBounds - \ru Обновить границы поверхностей в гранях ребра.
                                 \en Update surface bounds of edge faces. \~
  \return \ru Возвращает true, если была выполнена модификация ребра.
          \en Returns true if edge modification was performed. \~
  \ingroup Algorithms_3D
*/
//---
MATH_FUNC( bool ) RepairEdges( MbFaceShell & shell, bool updateFacesBounds = true );


#endif // __CHECK_GEOMETRY_H
