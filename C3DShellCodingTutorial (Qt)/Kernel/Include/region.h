////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Двумерный регион.
         \en Two-dimensional region. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __REGION_H
#define __REGION_H

#include <cur_contour.h>
#include <templ_sptr.h>
#include <mb_operation_result.h>


//------------------------------------------------------------------------------
/** \brief \ru Двумерный регион.
           \en Two-dimensional region. \~
  \details \ru Регион состоит из набора замкнутых составных кривых (контуров) MbContour. \n
    Регион представляет собой связное множество точек двумерного пространства, границы которого описывают контуры.
    Контуры региона замкнуты и не имеют самопересечений (но могут иметь самокасания).
    В произвольном регионе обязан быть один (и только один) внешний контур (положительный
    обход внешнего контура осуществляется против часовой стрелки) и несколько
    внутренних контуров (положительный обход внутреннего контура осуществляется по часовой
    стрелке), которые полностью лежат внутри внешнего контура (или могут его касаться).
    В массиве contours первым всегда лежит внешний контур.
    Над регионами можно выполнять булевы операции.
           \en A region consists of a set of closed composite curves (contours) MbContour. \n
    A region represents a connected set of two-dimensional points, which boundaries are described by contours.
    Contours of region are closed and do not have self-intersections (but there may be self-contacts).
    In arbitrary region should be one (and only one) external contour (positive
    traverse of external contour is performed counterclockwise) and several
    internal contour (positive traverse of internal contour is performed clockwise)
    which are completely located inside external contour (or may contact it).
    In the array 'contours' external contour is always the first.
    Boolean operations may be performed with regions. \~
  \ingroup Region_2D
*/
// ---
class MATH_CLASS MbRegion : public MbPlaneItem {
private:
  RPArray<MbContour>  contours;   ///< \ru Контуры региона. \en Region contour. 
  mutable ThreeStates setCorrect; ///< \ru Результат проверки корректности. \en Correctness check result. 

public:
  MbRegion();                                                    ///< \ru Пустой регион. \en Empty region. 
  MbRegion( const MbContour          &,             bool same ); ///< \ru Регион с одним внешним контуром. \en Region with one external contour. 
  MbRegion( const SPtr<MbContour>    &,             bool same ); ///< \ru Регион с одним внешним контуром. \en Region with one external contour. 
  MbRegion( const RPArray<MbContour> &,             bool same ); ///< \ru Регион с несколькими контурами. \en Region with several contours. 
  MbRegion( const std::vector< SPtr<MbContour> > &, bool same ); ///< \ru Регион с несколькими контурами. \en Region with several contours. 
  MbRegion( const MbRegion           &,             bool same, MbRegDuplicate * iReg = NULL ); ///< \ru Конструктор копии. \en Copy-constructor. 
public:
  virtual ~MbRegion();

public:

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */
  virtual MbePlaneType IsA() const;     // \ru Тип объекта. \en A type of an object. 
  virtual MbePlaneType Type() const;    // \ru Групповой тип объекта. \en Group type of object. 
  virtual MbePlaneType Family() const;  // \ru Семейство объекта. \en Family of object. 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const;                     // \ru Сделать копию. \en Create a copy 
  virtual void        Transform( const MbMatrix & matr, MbRegTransform * iReg = NULL, const MbSurface * newSurface = NULL ); // \ru Преобразовать согласно матрице. \en Transform according to the matrix. 
  virtual void        Move  ( const MbVector & to, MbRegTransform * iReg = NULL, const MbSurface * newSurface = NULL );      // \ru Сдвинуть вдоль вектора. \en Move along a vector. 
  virtual void        Rotate( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * iReg = NULL, const MbSurface * newSurface = NULL );
  virtual bool        IsSame   ( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const;                      // \ru Являются ли объекты равными? \en Determine whether objects are equal. 
  virtual bool        SetEqual ( const MbPlaneItem & item );                            // \ru Сделать объекты равным. \en Make objects equal. 
  virtual void        AddYourGabaritTo( MbRect & r ) const;                             // \ru Добавить свой габарит в присланный габарит. \en Add your own bounding box into the sent bounding box. 
  virtual bool        IsVisibleInRect( const MbRect & r, bool exact = false ) const;    // \ru Виден ли объект в заданном прямоугольнике. \en Whether the object is visible in the given rectangle 
  virtual double      DistanceToPoint( const MbCartPoint & to ) const;                  // \ru Вычислить расстояние до точки to. \en Calculate the distance to a point 'to'. 
  virtual bool        DistanceToPointIfLess( const MbCartPoint & to, 
                                             double & distance ) const;                 // \ru Вычислить расстояние до точки to, если оно меньше d. \en Calculate the distance to the point 'to' if it is less than d. 
  virtual void        Refresh();                                                        // \ru Сбросить все временные данные. \en Reset all temporary data. 

  virtual MbProperty & CreateProperty( MbePrompt name ) const; // \ru Создать собственное свойство. \en Create a custom property. 
  virtual void        GetProperties( MbProperties & );         // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void        SetProperties( const MbProperties & );   // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void        GetBasisPoints( MbControlData & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  /** \} */   
  /**\ru \name Функции инициализации.
     \en \name Initialization functions.
      \{ */   
          /// \ru Инициализация. \en Initialization. 
          void        Init( const MbContour          &,             bool same );
          /// \ru Инициализация. \en Initialization. 
          void        Init( const RPArray<MbContour> &,             bool same );
          /// \ru Инициализация. \en Initialization. 
          void        Init( const std::vector< SPtr<MbContour> > &, bool same );
  /** \} */   
  /**\ru \name Функции доступа к данным.
     \en \name Functions for access to data.
      \{ */        
          size_t      GetContoursCount() const { return contours.size(); } ///< \ru Выдать количество контуров региона. \en Get the number of contours of region. 
    const MbContour * GetContour( size_t k ) const { return contours[k]; } ///< \ru Выдать контур с индексом index. \en Get contour with the given index. 
    const MbContour * GetOutContour() const;                               ///< \ru Выдать внешний контур. \en Get external contour. 
  /** \} */   
  /**\ru \name Функции изменения данных.
     \en \name Functions for changing data
      \{ */
          MbContour * SetContour( size_t k ) { setCorrect = ts_neutral; return contours[k]; } ///< \ru Выдать контур с индексом index. \en Get contour with the given index. 
    
          /// \ru Отсоединить используемые контуры и удалить остальные. \en Detach used contours and delete other. 
          void        DeleteContours();
          /// \ru Отцепить все контуры региона без удаления. \en Detach all region contours without deletion. 
          void        DetachContours( RPArray<MbContour> & );

          /// \ru Сделать регион корректным (если это нужно и возможно). \en Make region correct (if this is possible). 
          bool        SetCorrect();
          /// \ru Состояние проверки корректности региона. \en A state of region validation. 
          ThreeStates GetCorrectState() const { return setCorrect; }

          /// \ru Определить положение точки относительно региона. \en Define the point location relative to the region. 
          MbeItemLocation PointClassification( const MbCartPoint &, double metricAcc /*= Math::LengthEps*/ ) const;
          /// \ru Есть ли в контуре криволинейный сегмент. \en Whether the contour has a curved segment.
          bool        IsAnyCurvilinear() const; 
          /// \ru Одинаковы ли регионы геометрически. \en Whether regions are space same. 
          bool        IsSpaceSame( const MbRegion & ) const;
          /// \ru Рассчитать и добавить массивы отрисовочных точек с заданной стрелкой прогиба. \en Calculate and add arrays of drawn points with a given sag. 
          void        CalculatePolygons( double sag, RPArray<MbPolygon> & polygons ) const;
          /// \ru Удалить внутренние контуры. \en Remove internal contours. 
          void        DeleteInnerContours();
          
          /** \brief \ru Удалить внутренний контур.
                     \en Remove internal contour. \~
            \details \ru Удалить внутренний контур по индексу. Индекс проверяется на корректность.
                     \en Remove internal contour by index. An index is validated for correctness. \~
            \param[in] index - \ru Индекс внутреннего контура. Должен быть больше нуля, но меньше количества контуров.
                               \en An index of internal contour. It should be more than null and less than the number of contours. \~
            \return \ru true Если контур был удален.
                    \en True if the contour has been deleted. \~
          */
          bool        DeleteInnerContour( size_t index );
   /** \} */ 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbRegion )
OBVIOUS_PRIVATE_COPY( MbRegion )
}; // MbRegion

IMPL_PERSISTENT_OPS( MbRegion )

//-------------------------------------------------------------------------------
/** \brief \ru Получить набор регионов.
           \en Get a set of regions. \~
  \details \ru Получить набор корректных регионов из произвольного набора контуров.\n
    Из присланных контуров отбираются те, которые подходят для построения 
    региона - замкнутые несамопересекающиеся и без разрывов.
           \en Get a set of correct regions from arbitrary set of regions. \n
    From sent contours there are selected such contours which are suitable for construction 
    of region - closed, without self-intersections and discontinuities. \~
  \param[in]  contours     - \ru Набор контуров.
                             \en A set of contours. \~
  \param[in]  sameContours - \ru Флаг использования оригиналов контуров при создании регионов.
                             \en A flag of using of contours originals when creating regions. \~ 
  \param[out] regions      - \ru Результат - набор регионов.
                             \en The result is a set of points. \~
  \ingroup Algorithms_2D
*/
// ---
MATH_FUNC (void) GetCorrectRegions( const RPArray<MbContour> & contours, bool sameContours, 
                                    RPArray<MbRegion> & regions );


//-------------------------------------------------------------------------------
/** \brief \ru Разбить набор контуров на группы и построить по ним регионы.
           \en Divide a set of regions into groups and construct regions. \~
  \details \ru Разбить произвольный набор контуров на связные группы контуров и построить по ним регионы.\n
    Для любого контура, принадлежащего связной группе, этой же группе
    принадлежат все контуры:\n
    1) совпадающие с данным контуром\n
    2) пересекающие данный контур\n
    3) содержащие данный контур\n
    4) содержащиеся в данном контуре\n
    Группы возвращаются в виде регионов (возможно, некорректных).
           \en Divide arbitrary set of contours into connected groups of contours and construct regions.\n
    For any contour belonging to connected group, this group
    contain all contours:\n
    1) which coincide with the given contour\n
    2) which intersect the given contour\n
    3) which contain the given contour\n
    4) which are contained in the given contour\n
    Groups are returned in regions form (perhaps, incorrect). \~        
  \param[in]  contours        - \ru Набор контуров для разбиения на группы.
                                \en A set of contours for dividing into groups. \~
  \param[in]  useSelfIntCntrs - \ru Если true, то самопересекающиеся контуры образуют
                                отдельные группы (некорректные регионы), иначе - такие контуры
                                вообще не используются.
                                \en If true then self-intersected contours form
                                separate groups (incorrect regions), otherwise - such contours
                                are not used at all. \~
  \param[in]  sameContours    - \ru Флаг использования оригиналов контуров при создании регионов.
                                \en A flag of using of contours originals when creating regions. \~
  \param[out] regions         - \ru Результат - набор регионов.
                                \en The result is a set of points. \~ 
  \ingroup Algorithms_2D
*/
// ---
MATH_FUNC (void) MakeRegions( RPArray<MbContour> & contours, 
                              bool                 useSelfIntCntrs, 
                              bool                 sameContours,
                              RPArray<MbRegion> &  regions );

//------------------------------------------------------------------------------
/** \brief \ru Параметры булевой операции над регионами.
           \en Boolean operation parameters over regions. 
           \~
  \details \ru Параметры булевой операции над регионами.\n
           \en Boolean operation parameters over regions. \n
           \~
  \ingroup Region_2D
*/
// ---
struct MATH_CLASS MbRegionBooleanParams {
protected:
  RegionOperationType operType;       ///< \ru Тип булевой операции. \en А Boolean operation type.
  bool                allowSelfTouch; ///< \ru Допустимость самокасаний в результате. \en Admissibility of self-touches as a result..
  bool                mergeCurves;    ///< \ru Объединять подобные сегменты кривых. \en Merge similar segments of curves.
public:
  MbRegionBooleanParams( RegionOperationType type, bool selfTouch = true, bool mergeCrvs = true ) : operType( type ), allowSelfTouch( selfTouch ), mergeCurves( mergeCrvs ) {}
  MbRegionBooleanParams( const MbRegionBooleanParams & p ) : operType( p.operType ), allowSelfTouch( p.allowSelfTouch ), mergeCurves( p.mergeCurves ) {}
public:
  RegionOperationType OperationType() const { return operType; }
  void                OperationType( RegionOperationType type ) { operType = type; }

  bool  MergeCurves() const { return mergeCurves; }
  void  MergeCurves( bool b ) { mergeCurves = b; }

  bool  AllowSelfTouch() const { return allowSelfTouch; }
  void  AllowSelfTouch( bool b ) { allowSelfTouch = b; }

  const MbRegionBooleanParams & operator = ( const MbRegionBooleanParams & p ) { operType = p.operType; allowSelfTouch = p.allowSelfTouch; mergeCurves = p.mergeCurves; return *this; }
private:
  MbRegionBooleanParams();
};

                                                                     
//-------------------------------------------------------------------------------
/** \brief \ru Выполнить булеву операцию над регионами.
           \en Perform boolean operation with regions. \~
  \details \ru Выполнить булеву операцию над двумя регионами, заданными массивами контуров. \n
               Ломаную нежелательно использовать как сегмент контура. Ее нужно преобразовать на набор отрезков.
           \en Perform boolean operation with two regions, which are set by the contours array. \n
               Polyline is undesirable as a contour segment. It needs to be converted to a set of segments. \~
  \param[in] contours1  - \ru Первый набор контуров.
                          \en First set of contours. \~
  \param[in] contours2  - \ru Второй набор контуров.
                          \en Second set of contours. \~
  \param[in] operParams - \ru Параметры булевой операции.
                          \en A Boolean operation parameters. \~
  \param[out] regions   - \ru Результат - набор регионов.
                          \en The result is a set of points. \~
  \param[out] resInfo   - \ru Код результата операции.
                          \en Operation result code. \~
  \return \ru true в случае успеха операции.
          \en Returns true if the operation succeeded. \~
  \ingroup Algorithms_2D
*/
// ---
MATH_FUNC (bool) CreateBooleanResultRegions( RPArray<MbContour> & contours1, RPArray<MbContour> & contours2,
                                             const MbRegionBooleanParams & operParams, RPArray<MbRegion> & regions,
                                             MbResultType * resInfo = NULL );


//-------------------------------------------------------------------------------
/** \brief \ru Выполнить булеву операцию над регионами.
           \en Perform boolean operation with regions. \~
  \details \ru Выполнить булеву операцию над двумя регионами.
           \en Perform boolean operation with two regions. \~
  \param[in] region1    - \ru Первый регион.
                          \en First region. \~
  \param[in] region2    - \ru Второй регион.
                          \en Second region. \~
  \param[in] operParams - \ru Параметры булевой операции.
                          \en A Boolean operation parameters. \~
  \param[out] regions   - \ru Результат - набор регионов.
                          \en The result is a set of points. \~
  \param[out] resInfo   - \ru Код результата операции.
                          \en Operation result code. \~
  \return \ru true в случае успеха операции.
          \en Returns true if the operation succeeded. \~
  \ingroup Algorithms_2D
*/
// ---
MATH_FUNC (bool) CreateBooleanResultRegions( MbRegion & region1, MbRegion & region2,
                                             const MbRegionBooleanParams & operParams, RPArray<MbRegion> & regions,
                                             MbResultType * resInfo = NULL );


//-------------------------------------------------------------------------------
/** \brief \ru Выполнить объединение регионов.
           \en Perform union of regions. \~
  \details \ru Выполнить объединение регионов.
           \en Perform union of regions. \~
  \param[in,out] regions    - \ru Начальные и конечные регионы.
                              \en Initial and resulting regions. \~
  \param[in] allowSelfTouch - \ru Допустимость самокасаний в результате.
                              \en Admissibility of self-touches as a result. \~
  \param[in] mergeCurves    - \ru Объединять подобные сегменты кривых.
                              \en Merge similar segments of curves. \~
  \return \ru true, если какие-то регионы были объединены.
          \en Returns true if a pair of regions has been united. \~
  \ingroup Algorithms_2D
*/
// ---
MATH_FUNC (bool) MakeUnionRegions( RPArray<MbRegion> & regions, bool allowSelfTouch = true, bool mergeCurves = true );


#endif // __REGION_H