////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Множество проекций тел.
         \en The array of projections of solids. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MAP_IMPLEMENTATION_H
#define __MAP_IMPLEMENTATION_H


#include <map_lump.h>
#include <templ_psrt_array.h>


struct           MbLump;
struct           MbBody;
class            MbMapBody;
class MATH_CLASS MbProjectionsObjects;
class MATH_CLASS MbSpacePoints;
class MATH_CLASS MbSpaceCurves;
class MATH_CLASS MbSymbol;
class MATH_CLASS MbMapViewInfo;



////////////////////////////////////////////////////////////////////////////////
//
// \ru Построение плоских проекций по модельным объектам \en The planar projections construction on model objects 
//
////////////////////////////////////////////////////////////////////////////////

  enum MbeMatrixCompareResult 
  {
    mcr_Same,
    mcr_Shift,
    mcr_ShiftZ,
    mcr_Other
  };

//------------------------------------------------------------------------------
/** \brief \ru Множество проекций тел.
           \en The set of solids projections. \~
  \details \ru Множество проекций тел.\n
    Содержит набор проецируемых тел.
           \en The set of solids projections.\n
    Contains a set of projected solids. \~  
  \ingroup Mapping
*/
// ---
class MATH_CLASS MbMapBodiesPArray {

private: 
  RPArray<MbMapBody> mapBodies;         ///< \ru Множество проекций тел \en A set of solids projections     
  SArray<size_t>     originIndices;     ///< \ru Индексы оригинальных тел в mapBodies. \en indices of original body in mapBodies.
                                        ///< \ru Все тела в mapBodies сгруппированы так ОsssОssОООssОsО, O - оригинальное тело, s - тело полученное сдвигом. 
                                        ///< \en All bodies in mapBodies was grouped like ОsssОssОООssОsО? O- original body, s - body was shifted. 
public:
  /// \ru Конструктор объекта с пустым набором тел. \en Constructor of an object with an empty set of solids. 
  MbMapBodiesPArray() : mapBodies( 0, 1 ), originIndices( 0, 1 ) {}
  /// \ru Деструктор. \en Destructor. 
  ~MbMapBodiesPArray();

public:  
  /// \ru Число проецируемых тел. \en The number of projected solids. 
        size_t        MapBodiesCount() const { return mapBodies.Count(); }

  /** \brief \ru Выдать тело.
             \en Get a solid. \~
    \details \ru Выдать тело по индексу. Без проверки индекса. \n
             \en Get a solid by an index. Without index checking. \n \~
    \param[in] index - \ru Индекс тела.
                       \en A solid index. \~
  */
        MbMapBody *  _SetMapBody( size_t index ) const { return mapBodies[index]; }

  /** \brief \ru Выдать тело.
             \en Get a solid. \~
    \details \ru Выдать тело по индексу. Без проверки индекса. \n
             \en Get a solid by an index. Without index checking. \n \~
    \param[in] index - \ru Индекс тела.
                       \en A solid index. \~
  */
  const MbMapBody *  _GetMapBody( size_t index ) const { return mapBodies[index]; }

  /** \brief \ru Построение ассоциативных проекций.
             \en The construction of associative projections. \~
    \details \ru Построение ассоциативных проекций. Первая часть.\n
             \en The construction of associative projections. The first part.\n \~
    \param[in] lumps       - \ru Набор тел для проецирования.
                             \en A set of solids for projection. \~
    \param[in] into        - \ru Матрица перехода в локальную систему координат.
                             \en A matrix of translation to the local coordinate system. \~
    \param[in] znear       - \ru Параметр перспективного отображения. Задавать равным 0.0.
                             \en A parameter of perspective mapping. Set to be equal to 0.0. \~
    \param[in] perspective - \ru Признак перспективного отображения. Задавать равным false.
                             \en An attribute of perspective mapping. Set to be equal to false. \~
    \param[in] visMode     - \ru Признак проецирования невидимых линий.
                             \en An attribute of invisible lines projection. \~
    \param[in] version     - \ru Версия построения чертежа. Задавать версию Math::DefaultMathVersion().
                             \en The version of construction of drawing. Set the Math::DefaultMathVersion() version. \~
    \param[in]  prevCubes  - \ru Габариты тел до изменений.
                             \en Bounding boxes of solids before changes. \~
    \warning \ru Для внутреннего использования.
             \en For internal use only. \~
  */
        void          CreateFirst( const RPArray<MbLump> & lumps, 
                                   const MbMatrix3D & into, double znear,
                                   bool perspective, const MbMapVisibilityMode & visMode, VERSION version,
                                   const std::vector<MbLumpCube> * prevCubes = NULL );

  /** \brief \ru Построение ассоциативных проекций.
             \en The construction of associative projections. \~
    \details \ru Построение ассоциативных проекций. Вторая часть.\n    
      Построение проекций и заполнение следов объектов.
             \en The construction of associative projections. The second part.\n    
      The construction of projections and filling the vestiges. \~
    \param[out] vestiges      - \ru Результат - набор следов проецируемых объектов.
                                \en The result is a set of vestiges of projected objects. \~
    \param[in]  visMode       - \ru Признак проецирования невидимых линий.
                                \en An attribute of the invisible lines projection. \~
    \param[in]  into          - \ru Матрица перехода в локальную систему координат.
                                \en A matrix of translation to the local coordinate system. \~
    \param[in]  znear         - \ru Параметр перспективного отображения. Задавать равным 0.0.
                                \en A parameter of perspective mapping. Set to be equal to 0.0. \~
    \param[in]  perspective   - \ru Признак перспективного отображения. Задавать равным false.
                                \en An attribute of perspective mapping. Set to be equal to false. \~
    \param[in]  annotations   - \ru Набор аннотационных объектов.
                                \en A set of annotation objects. \~
    \param[in]  pointsData    - \ru Набор пространственных точек.
                                \en A set of spatial points. \~
    \param[in]  curvesData    - \ru Набор пространственных кривых.
                                \en A set of spatial curves. \~
    \param[in]  symbolObjects - \ru Набор условных обозначений.
                                \en A set of conventional notations. \~    
    \param[in]  merge         - \ru Флаг слияния подобных кривых (по умолчанию true).
                                \en Murge same curves (true default). \~    
    \warning \ru Для внутреннего использования.
             \en For internal use only. \~     
  */
      void            GetVestiges( MbVEFVestiges & vestiges, 
                                   const MbMapVisibilityMode & visMode, const MbMatrix3D & into, 
                                   double znear, bool perspective,
                                   PArraySort<MbSimbolthThreadView> * annotations,
                                   RPArray<MbSpacePoints> * pointsData,
                                   RPArray<MbSpaceCurves> * curvesData,
                                   RPArray<MbSymbol> *      symbolObjects, 
                                   bool merge = true );

  /** \brief \ru Рассчитать полигоны линий.
             \en Calculate polygons of lines. \~
    \details \ru Рассчитать полигоны видимых и невидимых линий для сборки.
             \en Calculate polygons of visible and invisible lines for assembly. \~       
    \param[out] arVL        - \ru Полигоны видимых линий ребер.
                              \en Polygons of visible lines of edges. \~
    \param[out] arHL        - \ru Полигоны невидимых линий ребер.
                              \en Polygons of invisible lines of edges. \~
    \param[out] arVT        - \ru Полигоны видимых линий гладких ребер.
                              \en Polygons of visible lines of smooth edges. \~
    \param[out] arHT        - \ru Полигоны невидимых линий гладких ребер.
                              \en Polygons of invisible lines of smooth edges. \~
    \param[in]  sag         - \ru Угловая толерантность.
                              \en An angular tolerance. \~
    \param[in]  annotations - \ru Набор аннатационных объектов.
                              \en A set of annotation objects. \~    
    \param[in]  place       - \ru Проекционная плоскость.
                              \en A projection plane. \~
    \param[in]  into        - \ru Матрица перехода в локальную систему координат.
                              \en A matrix of translation to the local coordinate system. \~   
    \warning \ru Для внутреннего использования.
             \en For internal use only. \~ 
  */
      void            GetVestiges( PArray<MbPolygon3DSolid> & arVL, 
                                   PArray<MbPolygon3DSolid> & arHL,
                                   PArray<MbPolygon3DSolid> & arVT, 
                                   PArray<MbPolygon3DSolid> & arHT, 
                                   double sag,
                                   PArraySort<MbSimbolthThreadView> * annotations,
                                   const MbPlacement3D & place,
                                   const MbMatrix3D & into );

private:
  // \ru заполнить массивы линий и поверхностей \en fill arrays of lines and surfaces 
      void            Fill              ( const RPArray<MbLump> & lumps, const MbMatrix3D & into, 
                                          double znear, bool perspective, const MbMapVisibilityMode & visMode, 
                                          VERSION version, const std::vector<MbLumpCube> * prevCubes ); 
  // \ru тест видимости пробной точки \en the test of a trial point visibility 
      int             IsShadeAll        ( const MbCartPoint3D &, bool section ) const;
  // \ru получение очерков и разрезка \en isocline getting and cutting 
  // \note \ru В многопоточном режиме m_Items выполняется параллельно. \en In multithreaded mode m_Items runs in parallel. \~
      void            BodiesCreateFirst();   
  // \ru Определение видимости тел. \en Define solids visibility. 
  // \note \ru В многопоточном режиме m_Items выполняется параллельно. \en In multithreaded mode m_Items runs in parallel. \~
      void            BodiesCreateSecondLocal( const PArraySort<MbSimbolthThreadView> * annotations );   
  // \ru добавление тела \en addition of solid 
      bool            AddBody( MbMapBody * mapBody, size_t & iFnd );

OBVIOUS_PRIVATE_COPY( MbMapBodiesPArray )
};


//------------------------------------------------------------------------------
/** \brief \ru Определение участков граничной кривой.
           \en The definition of boundary curve regions. \~
    \details \ru Определение участков граничной кривой местного вида, выносного элемента,
      местного разреза (или сечения).
             \en The definition of regions of a local view boundary curve, a detail view,
      a local cutaway (or section). \~
    \param[in]  lumps        - \ru Проецируемые объекты.
                               \en Projected objects. \~
    \param[in]  contour      - \ru Граничная кривая.
                               \en A boundary curve. \~
    \param[in]  cross        - \ru Точки пересечения граничной кривой с линиями чертежа.
                               \en Points of intersection between boundary curve and lines of drawing. \~
    \param[in]  baseViewInfo - \ru Информация о базовом виде, на котором построен местный вид\разрез:\n
      тип вида:\n
        mvt_View - Вид,\n
        mvt_Cut - Разрез,\n
        mvt_Section - Сечечние;\n
      плоскость вида, разреза или сечения.\n
                               \en The information about basic view on witch a local view\cutaway is constructed:\n
      a view type:\n
        mvt_View - View,\n
        mvt_Cut - Cutaway,\n
        mvt_Section - Section;\n
      a plane of view, cutaway or section.\n \~
    \param[in]  viewInfo     - \ru Информация о производном виде:\n
      тип вида:\n
        mvt_View - Местный вид, Выносной элемент,\n
        mvt_Cut - Местный разрез,\n
        mvt_Section - Местное сечение;\n
      плоскость вида, разреза или сечения.\n
      Если тип производного и базового вида != mvt_View, то тип производного вида должен совпадать с видом базового.\n
                               \en The information about derived view:\n
      a view type:\n
        mvt_View - A local view, a detail view,\n
        mvt_Cut - A local cutaway,\n
        mvt_Section - A local section;\n
      a plane of view, cutaway or section.\n
      If the type of derived and basic view is not equal to the mvt_View then the type of the derived view must coincide with the type of the basic view.\n \~
    \param[out] curves       - \ru Результат - набор участков граничной кривой.
                               \en The result is a set of boundary curve regions. \~    
    \warning \ru Для внутреннего использования.
             \en For internal use only. \~  
*/ // ---
void LimitCurveSectionsVisibility( const RPArray<MbLump>      & lumps,         // проецируемые объекты 
                                   const MbCurve              & contour,
                                   const SArray<MbCrossPoint> & cross,  
                                   const MbMapViewInfo        & baseViewInfo,
                                   const MbMapViewInfo        & viewInfo,
                                         RPArray<MbCurve>     & curves );      // результат


#endif // __MAP_IMPLEMENTATION_H
