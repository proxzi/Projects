//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Утилита оценки столкновений и параметров близости тел.
         \en Utility of collision detection and proximity queries.
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CDET_UTILITY_H
#define __CDET_UTILITY_H

#include <cdet_data.h>

class  MbItem;
class  MbSolid;
class  MbAssembly;
struct MbLumpAndFaces;
class  MbCollisionDetector;

//----------------------------------------------------------------------------------------
/** \brief \ru Утилита расчета параметров пересечения и близости тел.
           \en Utility for calculation of intersection and proximity parameters of solids. \~
  \details \ru Предоставляет функциональность Collision Detection для взаимодействия 
               с приложением САПР.
           \en Provides facilities of The Collision Detection to interact with the CAD 
               application. \~
  \attention  \ru Для гарантированно правильной работы детектора необходимо, чтобы объект
    типа MbLumpAndFaces, добавляемый в рассмотрение посредством функции AddSolid, имел 
    правильную матрицу преобразования в мир в настоящем его положении, т.е. с самого начала.
              \en For the ensure proper functionality of detector it is necessary that 
    an object of type MbLumpAndFaces to be added in consideration by function AddSolid will 
    have a correct matrix of transformation to the world coordinate system in its current 
    state, i.e. from the beginning. \~
  \ingroup Collision_Detection
*/
// ---
class MATH_CLASS MbCollisionDetectionUtility 
{
  MbCollisionDetector & detector;

public:
    MbCollisionDetectionUtility();
   ~MbCollisionDetectionUtility();

public:
  /**
    \brief \ru Добавить твердое тело с заданным положением в набор для контроля столкновений.
           \en Add a solid with given placement to the collision detection set. \~
    \return \ru Дескриптор объекта для контроля столкновений. \en Descriptor of object for collision detection. \~
  */  
  cdet_item   AddItem( const MbSolid & solid, const MbPlacement3D & place, cdet_app_item appItem = CDET_APP_NULL );
  /**
    \brief \ru Удалить геометрический объект из набора для контроля столкновений.
           \en Remove a geometric object from the set of collision detection. \~
  */
  void        RemoveItem( cdet_item cdItem );
  /**
    \brief  \ru Поменять текущее положение геометрического объекта в наборе.
            \en Change current position of a geometric object. \~
  */
  void        Reposition( cdet_item, const MbPlacement3D & );
  /**
    \brief  \ru Проверить соударения между геометрическими объектами набора.
            \en Check collisions between geometric objects of the set. \~
    \return \ru Функция вернет CDET_RESULT_Intersected при обранужении хотя бы одной коллизии.
            \en The function will return CDET_RESULT_Intersected if it detects at least one collision.    

  */
  cdet_result CheckCollisions( cdet_query & );

  /**
    \brief  \ru Проверить соударения между геометрическими объектами набора.
            \en Check collisions between geometric objects of the set. \~
    \return \ru Функция вернет CDET_RESULT_Intersected при обранужении хотя бы одной коллизии.
            \en The function will return CDET_RESULT_Intersected if it detects at least one collision.    
  */
  cdet_result CheckCollisions();

  /**
    \brief  \ru Выдать дескриптор клиентского приложения по дескриптору контрольного набора столкновений.  
            \en Get an application pointer by descriptor of the collision detection set.
  */
  cdet_app_item AppItem( cdet_item cdItem ) const;


public: // the functions below can be deprecated in future version.
  /**
    \brief \ru Добавить модель тела, как набор граней и решеток. 
            \en Add a solid data as a set of faces and the grids. \~
    \return \ru Индекс добавленной твердотельной модели. \en Index of added solid data. \~
  */
  size_t        AddLump( const MbLumpAndFaces & );
  /**
    \brief \ru Добавить модель тела, как набор граней и решеток. 
           \en Add a solid data as a set of faces and the grids. \~
    \return \ru Внутренняя структура данных представляющая добавленную модель. \en Internal data structure representing added solid data. \~
  */
  cdet_item     AddSolid( const MbLumpAndFaces & );
  /// \ru Добавить тело с заданным положением. \en Add a solid with a given placement.
  cdet_item     AddSolid( const MbSolid &, const MbPlacement3D &, cdet_app_item = CDET_APP_NULL );
  /// \ru Удалить твердотельную модель из детектора столкновений. \en Remove a solid model from a collision detector. 
  void          RemoveSolid( cdet_item );
  /// \ru Выдать количество добавленных твердотельных моделей. \en Get number of added solid models.
  size_t        Count() const;
  // Use AppItem() insead this
  cdet_app_item Component( size_t solIdx ) const;
  /// \ru Номер твердотельной модели, зарегистрированной в детекторе. \en An index of solid model registered in the detector.
  size_t        SolidIndex( cdet_item cItem ) const;
  /// \ru Вычисление минимального расстояния между объектами (см.функцию SetDistanceComputationObjects(...)) \en Calculation of minimal distance between objects (see the function SetDistanceComputationObjects(...))
  cdet_result   DistanceQuery( MbProximityParameters & minDist ) const;
  /// \ru Выключить из рассмотрения все модели. \en Exclude all models from consideration.
  void          FlushSolids();
  /// \ru Выдать иерархическое представление тела (NULL = отсутствие такового в списке). \en Get the hierarchical representation of the solid (NULL means that the solid is not in the list).
  cdet_item     GetHRepSolid ( const MbLumpAndFaces & ) const;
  /// \ru Задать барьер для отличия касания от пересечения. \en Set the barrier for the difference between the touch and the intersection.
  void          SetTouchTolerance( double lTol );
  /// \ru Вкл./выкл. приближенного вычисления пересечений тел \en On/off approximated calculation of intersections of solids 
  void          SetApproxCollisionQuery( bool ff );
  /// \ru Вкл./выкл. приближенного вычисления параметров близости - по триангуляции \en On/off approximated calculation of proximity parameters - by triangulation 
  void          SetApproxDistanceComputation ( bool ff );
  /// \ru Назначить объекты слежения для контроля за расстоянием между ними \en Assign monitoring objects to control the distance between them 
  void          SetDistanceComputationObjects( const MbLumpAndFaces & comp1, const MbLumpAndFaces & comp2 );
  /// \ru Обновить текущее положение тела с индексом solIdx. \en Update current placement of solid with index solIdx.
  void          SetPlacement( size_t solIdx, const MbPlacement3D & );

  // \ru Объявление конструктора копирования и оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration without implementation of the copy-constructor and assignment operator to prevent an assignment by default. 
  OBVIOUS_PRIVATE_COPY( MbCollisionDetectionUtility );

public: 
  // The func is deprecated. Instead, use CheckCollisions
  cdet_result InterferenceDetect( void * formalPar = NULL ) const;

private:
  /*
    \brief \ru Добавить объект геометрической модели в набор для контроля столкновений.
           \en Add an object of geometric model to the set of collision detection control. \~
    \return \ru Объект в наборе для контроля столкновений. \en Object of the set of collision detection. \~
  */  
  cdet_item   AddItem( const MbItem & );
  // Set an assembly to detect collisions between its elements
  void        SetAssembly( const MbAssembly & );
  void        UpdateGeometry();  
};

//----------------------------------------------------------------------------------------
// Default implemention of the call CheckCollisions.
//---
inline cdet_result MbCollisionDetectionUtility::CheckCollisions()
{  
  cdet_query_result defaultQuery;
  return CheckCollisions( defaultQuery );
}

#endif // __CDET_UTILITY_H

// eof