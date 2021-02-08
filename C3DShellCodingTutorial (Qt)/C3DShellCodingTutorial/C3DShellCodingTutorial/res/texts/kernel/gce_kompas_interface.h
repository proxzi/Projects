//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file     
  \brief \ru Программный интерфейс для системы КОМПАС
         \en Program interface for KOMPAS system. \~
  \details \ru Данный файл содержит классы и методы, ориентированные на типы  
            данных CAD-системы КОМПАС. Для других приложений это API может оказаться
            не удобным, а его методы могут быть удалены или изменены в будущих 
            версиях. Рекомендуется применять эту часть API решателя, только если 
            не удасться найти требуемую функциональность в заголовочных файлах 
            gce_api.h или gce_types.h.
           \en This file contains classes and methods oriented to  
            data types of CAD-system KOMPAS. For other applications this API can be
            inconvenient and its methods can be deleted or modified in future 
            versions. It is recommended to apply this part of solver API only if 
            the required functionality is not found in header files 
            gce_api.h or gce_types.h. \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GCE_KOMPAS_INTERFACE_H
#define __GCE_KOMPAS_INTERFACE_H

#include <mt_ref_item.h>
#include <mb_cart_point.h>
#include <pars_tree_variable.h>
//
#include "gce_geom.h"
#include <vector>

class MtVectorN;
template <class Type> class RPArray;

//////////////////////////////////////////////////////////////////////////////////////////
//
/// \ru Ограничение для подмножества координат \en Constraint for subset of coordinates 
/**\ru Как правило, это алгебраические уравнение общего вида f(x1,x2,..,xn) = g(x1,x2,..,xn)
  явно-выраженной форме: x1 = g(x2,x3,..,xn).
   \en As a rule, it is an algebraic equation of a general form  f(x1,x2,..,xn) = g(x1,x2,..,xn)
  or, as a special case, it is an equation in explicit form: x1 = g(x2,x3,..,xn). \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

struct ItAlgebraicConstraint
{  
  /// \ru Выдать координату с индексом crdIdx. \en Get coordinate with crdIdx index. 
  virtual ItGeomCoord * GetCoord( ptrdiff_t crdIdx ) const = 0;
  /// \ru Количество координат, связанных с уравнением. \en Count of coordinates connected with the equation. 
  virtual ptrdiff_t     GetCoordCount() const = 0;
  /// \ru Вычисление первой производной по координате и значений функции. \en The first derivative by coordinate and the function values calculation. 
  virtual bool          CalcDerive( ItGeomCoord &, const std::vector<double> & /*argLine*/, double & /*fd*/, double & /*f*/ ) const { return false; }
  /// \ru Выдать координату зависимой переменной (для уравнений заданных в явно-выраженной форме). \en Get the coordinate of dependent variable (for explicit equations). 
  virtual ptrdiff_t     GetDependedCoordIdx() const = 0;
  /// \ru Признак уравнения, заданного в форме присвоения, по правилам КОМПАС-3D V12. \en Flag of equation specified in form of assignment, by the rules of KOMPAS-3D V12. 
  /**\ru Уравнения, заданные в явно выраженной форме, считающиеся присвоением выражения зависимой переменной: x1 = g(x2,x3,..,xn).
    Такие уравнения стремимся вычислять иерархическим способом, сверху-вниз.
     \en Equations specified explicitly, considered to be the assignment of dependent variable: x1 = g(x2,x3,..,xn).
    It is preferred to compute such equations by hierarchical top-down method. \~ 
  */
  virtual bool          IsAssignmentForm() const = 0;
  
  virtual refcount_t    AddRef()  const = 0;
  virtual refcount_t    Release() const = 0;

private:
  // It will be removed
  virtual bool CalcDerive( ItGeomCoord &, const MtVectorN &, double &, double & ) const { return false; }

protected:
  ~ItAlgebraicConstraint() {}
};

/** 
  \addtogroup Constraints2D_API   
  \{
*/

//----------------------------------------------------------------------------------------
/// \ru Задать ограничение, реализуемое на стороне клиента \en Specify a constraint implemented by the user 
/**
  \param \ru gSys контекст решателя
         \en gSys the solver context \~
  \param \ru iEqu  интерфейс уравнения, заданного пользователем
         \en iEqu  interface of the equation specified by the user \~
  \param \ru varsCount количество переменных
         \en varsCount count of variables \~
  \param \ru varsVector вектор переменных
         \en varsVector vector of variables \~
  \return \ru дескриптор нового ограничения
          \en descriptor of a new constraint \~
*/
// ---
GCE_FUNC(constraint_item) GCE_AddEquation(  GCE_system gSys
                                          , ItAlgebraicConstraint & iEqu
                                          , size_t    varsCount
                                          , const var_item * varsVector );

//----------------------------------------------------------------------------------------
/// \ru Определить смежные ли это ограничение и геометрический объект \en Determine whether the constraint and the geometric object are adjacent 
//---
GCE_FUNC(bool) GCE_IsAdjacentConstraint(   GCE_system gSys 
                                         , geom_item  g
                                         , constraint_item c );

//----------------------------------------------------------------------------------------
/// \ru Получить текущие координаты точки \en Get the current coordinates of point 
/**
  \param \ru gSys   контекст решателя
         \en gSys the solver context \~
  \param \ru g      дескриптор точки или иного геометрического объекта
         \en g      descriptor of a point or other geometric object \~
  \param \ru pName  идентификатор точки, принадлежащей объекту
         \en pName  identifier of a point belonging to the object \~
  \return \ru координаты точки
          \en point coordinates \~
*/
//---
GCE_FUNC(MbCartPoint) GCE_GetPoint( GCE_system gSys
                                  , geom_item g
                                  , point_type pName = GCE_PROPER_POINT );

/**
  \}
  Constraints2D_API
*/

//----------------------------------------------------------------------------------------
/*
      \brief \ru Добавить геометрический объект. \en Add a geometric object. \~
      \details  \ru Регистрирует объект пользователя в контексе решателя. 
  Пользователь отвечает за время жизни этого объекта в контексте 
  решателя и обязан в нужный момент также и удалить (разрегистрировать) 
  объект (см. #GCE_RemoveGeom).
      \en Register a user object in the solver context. 
  The user is responsible for the object life time in the context 
  of the solver and must delete (unregister) it at the appropriate time 
  object (see #GCE_RemoveGeom). \~
*/
/**
  \attention \ru Устаревшая функция. Вызов будет удален в одной из следующих версий (2016).
  \en An obsolete function. The call will be removed in one of the next versions. \~
*/
GCE_FUNC(geom_item) GCE_AddGeom( GCE_system gSys, IfGeom2d & );


#endif // __GCE_KOMPAS_INTERFACE_H

// eof