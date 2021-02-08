//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Объектное API геометрического решателя в 3D.
         \en Object API of geometric solver in 3D. \~
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GCM_MANAGER_H
#define __GCM_MANAGER_H

#include <math_define.h>
#include <mt_ref_item.h>
#include <gcm_res_code.h>
#include <gcm_geom.h>

struct ItConstraintItem;
struct ItPositionManager;
struct ItGCBlackbox;
struct GCM_c_params;

class  MbVector3D;
class  MbCartPoint3D;
class  MbPlacement3D;
class  MtGeomSolver;
class  MtParGeom;

/**
  \addtogroup GCM_3D_ObjectAPI
  \{
*/

//////////////////////////////////////////////////////////////////////////////////////////
//
/// \ru Состояние свободы тела \en State of the solid freedom  
//
//////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
  sof_Zero             = 0,        ///< \ru Полно-заданное или фиксированное тело (нулевая степень свободы). \en Fully-specified or fixed solid (zero degree of freedom).
  sof_WellConstrained  = sof_Zero, ///< \ru Полно-заданное или фиксированное тело (нулевая степень свободы). \en Fully-specified or fixed solid (zero degree of freedom).
  sof_UnderConstrained = 1,        ///< \ru Недоопределенное тело, т.е. имеющее степень свободы. \en Underconstrained solid, i.e. having a degree of freedom.
  sof_Unknown          = 2,        ///< \ru Нет сведений о степени свободы. \en No information about the degree of freedom.
} MtStateOfFreedom;


typedef GCM_reposition MtRepositionMode;

//----------------------------------------------------------------------------------------
/// \ru Неопределенное значение для некоторого типа. \en Undefined value of some datatype
//---
template<typename T>
struct GCM_undefined
{
private:
  static const int value = -1;
};
template<> struct GCM_undefined<GCM_result>
{
  static const GCM_result value = GCM_RESULT_None;
};
template<> struct GCM_undefined<GCM_tan_choice>
{
  static const GCM_tan_choice value = GCM_TAN_NONE;
};
template<> struct GCM_undefined<GCM_alignment>
{
  static const GCM_alignment value = GCM_NO_ALIGNMENT;
};
template<> struct GCM_undefined<GCM_angle_type>
{
  static const GCM_angle_type value = GCM_NONE_ANGLE;
};
template<> struct GCM_undefined<GCM_scale>
{
  static const GCM_scale value = GCM_NO_SCALE;
};
template<> struct GCM_undefined<GCM_dependency>
{
  static const GCM_dependency value = GCM_NO_DEPENDENCY;
};


//----------------------------------------------------------------------------------------
/** \brief \ru Числовой или перечислительный параметр ограничения.
           \en Numeric or enumerated parameter of constraint. \~
  \details \ru В зависимости от контекста тип #MtParVariant может трактоваться,
  как число с плавающей точкой или целочисленная величина (int, enum, bool).
           \en Depending on the context the type #MtParVariant can be treated 
  as a floating-point or integer (int, enum, bool). \~
*/
//---
class GCM_CLASS MtParVariant
{
public:
  static const MtParVariant undef;  ///< \ru Неопределенное значение. \en Undefined value.

public:
  MtParVariant() : tag( tagUndef ), enumVal( SYS_MAX_ST-2 ) {} // \ru Неопределенное значение \en Undefined value 
  MtParVariant( float val ) : tag( tagReal ), numVal( static_cast<double>(val) ) {}
  MtParVariant( double val ) : tag( tagReal ), numVal( val ) {}
  template< class _EnumType >
  MtParVariant( _EnumType val ) : tag( tagEnum ), enumVal( static_cast<ptrdiff_t>(val) ) {}

public:
  template< typename _EnumType >
  bool      GetEnum( _EnumType & ) const;
  template< typename _EnumType >
  _EnumType AsEnum() const;
  double    AsNumber() const { C3D_ASSERT(tag==tagReal); return numVal; }
  int       AsInteger() const { C3D_ASSERT(tag==tagInt); return static_cast<int>( enumVal ); }
  bool      operator == ( const MtParVariant & ) const;
  bool      operator != ( const MtParVariant & v ) const { return !(v == *this); }

public:
  GCM_alignment AlignType() const;
  GCM_c_arg     CArg() const;  ///< \ru Выдать как аргумент ограничения. \en Give as an argument of constraint.

private:
  union
  {
    double    numVal;
    ptrdiff_t enumVal;
  };  
  enum { tagUndef, tagReal, tagEnum, tagInt } tag : 8;
};

//----------------------------------------------------------------------------------------
//
//---
template< typename _EnumType >
inline _EnumType MtParVariant::AsEnum() const 
{ 
  if ( tag == tagUndef )
  {
    return GCM_undefined<_EnumType>::value;
  }
  C3D_ASSERT( tag == tagEnum ); 
  return static_cast<_EnumType>( enumVal ); 
}

//----------------------------------------------------------------------------------------
//
//---
template< typename _EnumType >
bool MtParVariant::GetEnum( _EnumType & val ) const
{  
  if ( tag == tagEnum )
  {
    val = AsEnum<_EnumType>(); 
    return true;
  }
  return false;  
}

//----------------------------------------------------------------------------------------
//
//---
inline bool MtParVariant::operator == ( const MtParVariant & var ) const
{
  if ( tag == var.tag )
  {
    return ( (numVal == var.numVal) || (enumVal == var.enumVal) );
  }
  return false;
}

//----------------------------------------------------------------------------------------
//
//---
inline GCM_alignment MtParVariant::AlignType() const
{
  if ( *this == undef )
    return GCM_NO_ALIGNMENT;

  if ( (tag == tagEnum) && (GCM_MIN_ALIGNMENT <= enumVal && enumVal < GCM_MAX_ALIGNMENT) )
  {
    return AsEnum<GCM_alignment>();
  }
  C3D_ASSERT_UNCONDITIONAL( false );
  return GCM_NO_ALIGNMENT;
}

//----------------------------------------------------------------------------------------
//
//---
inline GCM_c_arg MtParVariant::CArg() const
{
  GCM_c_arg cArg;  
  switch( tag )
  {
  case tagEnum:
  case tagInt:
    cArg = enumVal;
    break;
  case tagReal:
    cArg = numVal;
    break;
  case tagUndef:
    cArg = GCM_NULL;
    break;
  default:
    C3D_ASSERT_UNCONDITIONAL( false );
  }
  return cArg;
}

//----------------------------------------------------------------------------------------
/** \brief \ru Геометрический аргумент ограничения.
           \en Geometric argument of constraint. \~
*/
//---
class GCM_CLASS MtArgument
{
public:  
  /// \ru Конструктор аргумента, как геометрический объект. \en Constructor of argument as geometric object.
  MtArgument();
  MtArgument( const MtArgument & );
  /** \brief  \ru Конструктор аргумента, как геометрический объект.
              \en Constructor of argument as geometric object. \~
  */
  MtArgument( ItGeom * );

  /** \brief \ru Конструктор аргумента, как "геометрический объект в кластере".
             \en Constructor of argument as "geometric object in the cluster". \~
    \param[in]  cluster - \ru Кластер, как геометрически-жесткое объединение.
                          \en Cluster as geometrically rigid union. \~
    \param[in]  refGeom - \ru Геометрический объект, заданный в ЛСК кластера.
                          \en Geometric object given in the cluster LCS. \~
    \return \ru Аргумент геометрического ограничения.
            \en Argument of geometric constraint. \~

      \details \ru Аргумент, заданный этим способом, предполагает, что геометрический 
    объект refGeom, задан в ЛСК кластера. При этом в системе ограничений
    решение ищется для кластера, в то время, как refGeom считается неподвижно 
    заданным в ЛСК кластера.
               \en Argument given by this method assumes that the geometric 
    object refGeom is given in the cluster LCS. In this case in system of constraints
    the solution is sought for the cluster and refGeom is considered fixed  
    in the cluster LCS. \~ 

      \par \ru Аргумент, как матрица трансформации.
      Аргумент, созданный данным методом, можно интерпретировать, как матрицу трансформации, 
    заданную в виде произведения: G*T, где T - матрица кластера, переменная задачи ограничений, 
    G - матрица объекта refGeom, константа. Заметим, что если G = I - единичная матрица, 
    то геометрический объект имеет "стандартное положение".
           \en Argument as transformation matrix.
      Argument created by this method can be interpreted as a matrix
    of transformation given as multiplication: G*T, where T is cluster matrix, 
    variable of constraints, G - matrix of object refGeom, constant. 
    Note that if G = I - the identity matrix, then a geometric object 
    has "standard position". \~
  */  
  MtArgument( ItGeom * cluster, MtGeomVariant refGeom );
 ~MtArgument();
 
public:
  /// \ru Геометрический объект, вычисляемый в системе ограничений. \en Geometric object calculated in the constraint system.
  ItGeomPtr       Geom() { return m_geom; }
  /// \ru Геометрический объект, вычисляемый в системе ограничений. \en Geometric object calculated in the constraint system.
  const ItGeom *  Geom() const { return m_geom; }
  /** \brief  \ru Геометрическое значение аргумента, заданное в ЛСК объекта ItGeom * Geom(). 
              \en Geometric value of the argument specified in the LCS of the object ItGeom * Geom().
  */
  MtGeomVariant   RefGeom() const;
  /// \ru Тип геометрии. \en Geometry type.
  MtGeomType      GeomType() const;
  /// \ru Простой аргумент - не задан, как часть кластера. \en A simple argument, i.e. is not given as part of a cluster. \~
  bool            Simple() const;
  /// \ru Выдать положение геометрического объекта в виде ЛСК. \en Get a position of geometric object as its LSC.
  void            GetPlacement( MbPlacement3D & ) const;
  /// \ru Оператор присваивания. \en Assignment operator. 
  MtArgument &    operator = ( const MtArgument & );
  /// \ru Оператор равенства. \en Equality operator.
  inline bool     operator == ( const ItGeom * ) const;

private:
  SPtr<ItGeom>  m_geom;     // Geometric object of the constraint system (often, it is a rigid body)
  MtGeomVariant m_refGeom;  // Geometric object given in the m_geom's LCS. 
};

//----------------------------------------------------------------------------------------
// \ru Оператор равенства. \en Equality operator.
//---
inline bool MtArgument::operator == ( const ItGeom * geom ) const
{
  if ( m_geom == geom )
  {
    return Simple();
  }
  return false;
}


//----------------------------------------------------------------------------------------
//
// ---
struct ItConstraintsEnum : public MtRefItem
{
  virtual const ItConstraintItem * GetDataAndGo() = 0;
  virtual void                     Restart() = 0;
};

class MtConstraintManager;  // Internal implementation of the solver

//----------------------------------------------------------------------------------------
/** \brief \ru Геометрический решатель.
           \en Geometric constraint solver. \~
  \details \ru Интерфейс геометрического решателя. Клиентское приложение может 
  работать любым количеством систем ограничений, для каждой из них заводится по 
  одному экземпляру решателя с помощью  вызова #CreateSolver.
           \en Interface of geometric solver. Client application can 
  run any count of constraint systems, for each of them is put  
  one copy of the solver by calling #CreateSolver. \~
  
  \ingroup GCM_3D_ObjectAPI
*/
//---
class GCM_CLASS MtGeomSolver: public MtRefItem
{
    /**
      \ru \name Функции задания системы сопряжений
      \en \name Definition functions of the constraint system
      \{
    */
public:
    /// \ru Добавить паттерн. \en Add a pattern.
    MtPatternId     AddPattern( MtMateType, MtArgument, MtArgument, MtParVariant par=MtParVariant::undef );
    /// \ru Добавить геометрический объект в паттерн. \en Add a geometric object to the pattern.
    MtConstraintId  AddGeomToPattern( MtPatternId ptrn, MtArgument ptrnObj, MtParVariant par1 = MtParVariant::undef, 
                                      MtParVariant par2 = MtParVariant::undef, GCM_scale scale=GCM_RIGID );
    /// \ru Добавить ограничение. \en Add constraint. 
    MtResultCode3D  AddConstraintItem( ItConstraintItem & );

    /** \brief \ru Добавить сопряжение для пары геометрических объектов(ограничение).
               \en Add mate (constraint) of two geometric objects. \~
      \param[in]  t - \ru Тип геометрического ограничения.
                      \en Type of geometric constraint. \~
      \param[in]  g1, g2 - \ru Пара геометрических объектов - аргументы ограничения.
                           \en Pair of geometric objects - arguments of constraint. \~ 
      \param[in]  p1 - \ru Условие выравнивания для таких типов ограничений, как GCM_COINCIDENT, 
                       GCM_PARALLEL, GCM_PERPENDICULAR, GCM_CONCENTRIC, GCM_IN_PLACE,
                       GCM_TANGENT. Значения данного параметра берутся из #GCM_alignment.
                       \en Condition of alignment for or these types of constraints like GCM_COINCIDENT, 
                       GCM_PARALLEL, GCM_PERPENDICULAR, GCM_CONCENTRIC, GCM_IN_PLACE,
                       mct_Tangency. Values of this parameter are taken from #GCM_alignment. \~
      \param[in]  p1 - \ru Числовой параметр (double) размерных ограничений с типами GCM_ANGLE, GCM_DISTANCE.
                       \en Numeric parameter (double) of dimensional constraints to the types of GCM_ANGLE, GCM_DISTANCE. \~
      \param[in]  p2 - \ru  Вариант касания #GCM_tan_choice для ограничения типа GCM_TANGENCY 
                            или значение #GCM_alignment для размерных ограничений.
                       \en  Tangency variant #GCM_tan_choice for constraint with type GCM_TANGENCY 
                            or value #GCM_alignment for dimensional constraint. \~
      \param[in]  p3 - \ru Не имеет значения.
                       \en Irrelevant. \~    
      \return \ru Геометрическое ограничение. \en Geometric constraint. \~
    */
    ItConstraintItem *  AddConstraint ( MtMateType t, MtArgument g1, MtArgument g2
                                      , MtParVariant p1 = MtParVariant::undef
                                      , MtParVariant p2 = MtParVariant::undef
                                      , MtParVariant p3 = MtParVariant::undef );
    /** \brief \ru Добавить ограничение для тройки геометрических объектов.
               \en Add constraint of three geometric objects. \~
    */
    ItConstraintItem *  AddConstraint ( MtMateType, MtArgument, MtArgument, MtArgument, MtParVariant p1 = MtParVariant::undef );

    /// \ru Добавить ограничение. \en Add constraint. 
    ItConstraintItem *  AddConstraint( MtArgument, MtArgument, const GCM_c_params &, MtResultCode3D & );
    /** \brief \ru Добавить черный ящик в систему ограничений.
               \en Add black box to the constraint system. \~
      \param[in]  bBox  - \ru Интерфейс чёрного ящика.
                          \en Interface of Interface black box. \~
      \return \ru Код результата. \en Result code. \~      
    */  
    /// \ru Добавить геометрический объект. \en Add the geometric object. 
    ItGeom *            AddGeom( MtGeomVariant );
    // Not yet documented
    MtResultCode3D      AddBlackbox( ItGCBlackbox & );
    /// \ru Задать для данного ограничения зависимый объект. \ru Set a dependent object of constraint.
    ItGeom *            SetDependentGeom( ItConstraintItem *, ItGeom * );
    /// \ru Сообщить об изменении данных, определяющих сопряжение. \en Report about change in the data defining conjugation. 
    MtResultCode3D      ChangeDefinition( ItConstraintItem & );
    /// \ru Сообщить об изменении вещественного параметра размерного сопряжения. \en Report about change of float-parameter of dimensional conjugation. 
    MtResultCode3D      ChangeDimension( ItConstraintItem & );
    /** 
      \brief  \ru Сообщить о изменении положения сопрягаемых тел.
              \en Report about position change of conjugated solids. \~
      \return \ru Код результата. \en Result code. \~
      \details  \ru Через эту функцию осуществляется синхронизация положения 
      объектов системы ограничений по состоянию объектов стороне клиентского 
      приложения. Надо сказать, что обновление положений происходит только для тех 
      наследников #ItGeom, которые реализованы на стороне приложения. Состояние 
      объектов, добавленных методом #MtGeomSolver::AddGeom остается неизменным.
                \en Using this function implements synchronization of position 
      of objects of constraints as objects of a client 
      application. It should be said that the update of the positions happens only for those 
      inheritors of #ItGeom which are implemented by the application. State 
      of objects added by method #MtGeomSolver::AddGeom remains unchanged. \~
    */
    MtResultCode3D  ChangeGeomPositions();
    /** 
      \brief \ru Создать пользовательский кластер.
             \en Create an user-defined cluster.
      \note \ru Объекты объединяемого множества не должны иметь ограничений на момент вызова. 
                Создавайте кластер перед добавлением ограничений.
            \en The united objects should not have constraints at the moment of the call.
                Create a cluster before adding constraints.
    */
    ItGeom *        CreateCluster( std::vector<ItGeom *> & );
    /// \ru Зафиксировать геометрический объект в ГСК. \en Fix geometric object in the WCS. 
    MtResultCode3D  FixGeom( ItGeom & );
    /// \ru Узнать зафиксирован ли геометрический объект? \en Check if a geometric object is fixed?
    bool            IsFixed( const ItGeom * );
    /// \ru Очистить систему ограничений. \en Clear the system constraint. 
    void            Flush();
    /// \ru Удалить из системы ограничений все черные ящики. \en Remove all the black boxes from the constraint system. 
    MtResultCode3D  RemoveAllBlackboxes();
    /// \ru Удалить ограничение из системы. \en Remove constraint from system. 
    MtResultCode3D  RemoveConstraint( ItConstraintItem * );
    /// \ru Удалить чёрный ящик из системы ограничений. \en Remove black box from constraint system. 
    MtResultCode3D  RemoveBlackbox( ItGCBlackbox & );
    /// \ru Удалить геометрический объект из системы ограничений. \en Remove geometric object from constraint system. 
    bool            RemoveGeom( ItGeom * );
    /// \ru Освободить геометрический объект от фиксации в ГСК. \en Free geometric object from fixation in the WCS.
    MtResultCode3D  UnfixGeom( ItGeom & );

    /**
      \}
      \ru \name Функции решения и диагностики
      \en \name Functions of solution and diagnostics
      \{
    */
public:
    /// \ru Узнать удовлетворено ли ограничение? \en Check if constraint is satisfied? 
    bool              IsSatisfied( const ItConstraintItem & );
    /// \ru Узнать является ли тело полно-заданным или фиксированным ? \en Check if solid is fully-specified or fixed? 
    MtStateOfFreedom  IsWellConstrained( const ItGeom & );  
    /** 
      \brief  \ru Разослать диагностические коды ограничениям.
              \en Send out diagnostic codes to constraints. \~
      \details  \ru Осуществляется решение системы ограничений. Если она частично не решена, 
      то по результатам решения рассылаются диагностические коды ошибок всем ограничениям. 
      Функция не тратит существенного времени, если  систему ограничений до этого уже пытались решать.
                \en Solving the constraint system. If it is not solved partly, then by the 
      results of the solution diagnostic codes of errors are sent to all the constraints. 
      The function doesn't have a substantial amount of time if have already tried to 
      solve the constraint system before. \~
    */
    void              DiagnoseConstraints();       
    /**
      \brief    \ru Решить систему сопряжений. \en Solve the constraint system. \~
      \details  \ru Меняет положение геометрических объектов в соответствии с геометрическими ограничениями.
                \en Changes positions of geometric objects according to geometric constraints. \~
    */
    MtResultCode3D    Evaluate();
    /// \ru Текущее или вычисленное положение геометрического объекта \en Current or calculated position of a geometric object 
    MbMatrix3D        TransMatrix( ItGeom * ) const;
    /**
      \brief \ru Получить кластер, в котором содержится данный геометрический объект. 
             \en Get cluster which contains a given geometric object. \~
    */
    const ItGeom  *   Cluster( const ItGeom * subGeom ) const;

    /**
      \}
      \ru \name Функции для интерактивной манипуляции системой сопряжений
      \en \name Functions for interactive manipulation of the constraint system
      \{
    */
public:
  /// \ru Завершить режим "перетаскивания". \en Finish the dragging mode. 
  void           FinishReposition();
  /** \brief  \ru Выдать объект манипуляции, с которым работает решатель, находясь в режиме вращения/перемещения объектом (драггинг).
              \en Get manipulation object. Solver works with it when being in the dragging mode (rotating or moving).
  */
  ItGeom *       GetMovingGeom() const;
  /** 
    \brief  \ru Инициализировать режим перетаскивания объектов в плоскости экрана. 
            \en Initialize mode of object moving in the screen plane.
    \param movGeom   - \ru Компонент, деталь, которой манипулируют.
                       \en Component, part which is manipulated. \~
    \param projPlane - \ru Плоскость экрана, заданная в ГСК сборки.
                       \en Plane of the screen given in the WCS of assembly. \~
    \param curPnt    - \ru Точка, принадлежащая компоненту, которая проецируется на плоскость 
                          экрана в положение курсора, и за которую осуществляется 'перетаскивание'. 
                          curPnt задана в ЛСК геом.объекта movGeom.
                       \en Point of the component which is projected onto plane of the screen to 
                          cursor position and is 'dragging'. curPnt given in the LCS of 
                          the geometric object movGeom; \~
      \return \ru Код результата. \en Result code. \~      

      \details  
        \ru Функция запускается однократно перед входом в режим перетаскивания компонент, 
      который управляется (по движению мыши) через команду 
      MtResultCode3D SolveReposition( const MbCartPoint3D & ). Режим прекращается вызовом 
      любой иной команды, кроме этих двух; Также есть специальная функция для выхода из 
      режима "перетаскивания" - void FinishReposition(), для явного сбрасывания режима перемещения.
        \en The function runs once before running the dragging mode of components, 
      which is controlled (by movement of the mouse) by the command 
      MtResultCode3D SolveReposition( const MbCartPoint3D & ). Mode is stopped calling any other 
      command other than these two. There is also the special feature. To exit from 
      the dragging mode - void FinishReposition(), for explicit stop of the dragging mode. \~ 
  */
  MtResultCode3D PrepareReposition( ItGeom & movGeom, const MbPlacement3D & projPlane, const MbCartPoint3D & curPnt );
  /** \brief  \ru Инициализировать режим вращения компонента вокруг фиксированной оси. 
              \en Initialize mode of component rotation around a fixed point of axis.      

  \param geom  - \ru Геометрический объект, на которое направлено воздействие.
                  \en The geom object on which is directed at impact. \~
  \param org, axis - \ru Точка и вектор в ГСК, которые задают постоянную ось вращения.
                      \en Point and vector in the GCS which define constant axis of rotation. \~
  \return \ru Код ошибки, перечисленный enum #MtResultCode3D
          \en Error code, enum #MtResultCode3D \~
    \par
    \ru Функция запускается однократно перед входом в режим вращения, который управляется 
  через команду MtResultCode3D SolveReposition( double alpha ), где alpha - входной параметр,
  определяющий угловое положение компонента, и заданный в радианах. Режим прекращается вызовом
  void FinishReposition().
    \en The function runs once before running the rotation mode which is driven 
  by command MtResultCode3D SolveReposition( double alpha ), where "alpha" - input parameter,
  defines the angular position of the component and given in radians. Mode is stopped by 
  calling void FinishReposition(). \~
  */
  MtResultCode3D PrepareReposition( ItGeom & rotGeom, const MbCartPoint3D & org, const MbVector3D & axis );
  /**
    \brief  \ru Решить систему для произвольного изменения положения одного тела.
            \en Solve the system for an arbitrary change of position of one solid. \~
    \param  \ru gItem    тело, положение которого меняется;
            \en gItem    solid, the position of which is changed; \~
    \param  \ru newPos   новое пололожение тела g_item;
            \en newPos   new position of solid g_item; \~
    \param  \ru movType  код желаемого поведения
            \en movType  code of the desired behavior \~
    \return \ru Код результата. \en Result code. \~
              
    \note \ru Эта функция не позволяет вывести систему сопряжений из состояния решаемости, 
    кроме случаев, когда до вызова функции система уже находилась в нерешенном состоянии. 
    Если новое положение 'newPos' не позволяет удовлетворять системе сопряжений, то новое 
    положение тела окажется наиболее близким к newPos (при сохранении решаемости).
          \en This function doesn't allow to take out constraint system from decided state, 
    except when before call of function the system was already unsolved.  If new  position 
    'newPos' doesn't allow to satisfy the system of constraints, then new position of solid 
    will be the most nearest to newPos (while preserving solvability). \~
  */
  MtResultCode3D  SolveReposition( ItGeom & gItem, const MbPlacement3D & newPos, MtRepositionMode movType );
  /**
    \brief  \ru Решить систему сопряжений для новой позиции курсора в режиме драггинга. 
            \en Solve the system of conjugations for new position of cursor in the dragging mode.
    \param -  \ru curXYZ текущее положение курсора в ГСК.
              \en curXYZ the current position of cursor in the WCS. \~
    \return \ru Код результата. \en Result code. \~

    \details  \ru Рабочая процедура, управляющая режимом перетаскивания, который прекращается 
                  вызовом  любой иной команды, например, добавить новое ограничение или перестроить.
              \en Work procedure which controls dragging mode which are stopped after call
                  any other command. For example: add a new constraint or rebuild. \~
  */
  MtResultCode3D  SolveReposition( const MbCartPoint3D & curXYZ );    
  /**
    \brief  \ru Решить систему с изменением положения компонента через одну координату. 
            \en Solve the system with the position of the component through one coordinate. \~
    
    \param alpha - \ru Управляющий параметр (зачастую задается в радианах).
                   \en Driving parameter (often, it's in radians ). \~
    \return \ru Код результата. \en Result code. \~

    \details  \ru Это рабочая функция, управляющая режимом перепозиционирования, 
    в котором положение тела управляется изменением одной координаты, например, угол 
    вращения вокруг оси. Режим прекращается вызовом #MtGeomSolver::FinishReposition или любой 
    иной командой, меняющей состояние решетеля, например, #MtGeomSolver::AddConstraint.
    Функция для больших систем работает значительно быстрее, чем Solve(bool) или 
    SolveReposition( ItGeom &, const MbPlacement3D &).
              \en This is the work function controls reposition mode, in which the position of 
    the solid is controlled by changing one coordinate. For example the angle of rotation 
    around an axis. Mode is stopped by calling #MtGeomSolver::FinishReposition or any 
    other command, which is changes state of the solver. 
    For example #MtGeomSolver::AddConstraint. Function for large systems is faster than 
    the Solve(bool) or SolveReposition( ItGeom &, const MbPlacement3D &). \~
  */
  MtResultCode3D SolveReposition( double alpha );

public:
    /**
      \}
      \ru \name Вспомогательные функции и запросы.
      \en \name Auxiliary functions and queries.
      \{
    */

    /** \brief \ru Узнать принадлежит ли системе ограничений геометрический объект. 
               \en Check if geometric object belongs to the system. \~ 
    */
    bool IsMyGeom( const ItGeom & ) const;

    /** \brief  \ru Узнать принадлежит ли системе ограничений геометрическое ограничение. 
                \en Check if geometric constraint belongs to the system.
    */
    bool IsMyConstraint( const ItConstraintItem & ) const;

    /** \brief \ru Выдать кластер неподвижных объектов, заданных в глобальной системой координат.
               \en Get the cluster of rigid subset of objects which are given in global coordinate system. \~    
    */    
    ItGeom *    Ground() const;

    /** \brief \ru Выдать систему геометрических ограничений, которую обслуживает решатель.
               \en Get a geometric constraint system, which is served by the solver. \~
    */    
    GCM_system  System() const;

    // Not yet documented
    void  WriteSystem( TCHAR * fileName );
    /// \ru Выдать ограничения. \en Get the constraints iterator.
    SPtr<ItConstraintsEnum> GetConstraintsEnum();

    /**
      \}
      \ru \name Устаревшие функции, которые будут удалены в будущей версии.
      \en \name Deprecated functions will be removed in the future version.
      \{
    */

    /// \ru Функция будет удалена из API. Использовать ChangeDefinition(). \en The call is deprecated. Use ChangeDefinition() instead this.
    MtResultCode3D  ChangeAlignCondition( ItConstraintItem & );
    /// \ru Функция будет удалена из API. Использовать Evalute(). \en The call is deprecated. Use ChangeDefinition() instead this.
    MtResultCode3D  Solve( bool diagQuery );

    /**
      \}
    */

protected:
  MtGeomSolver();
 ~MtGeomSolver();

private:
        MtConstraintManager * _Impl();
  const MtConstraintManager * _Impl() const;

private:
  MtGeomSolver( const MtGeomSolver & );
  MtGeomSolver & operator = ( const MtGeomSolver & );
};

//----------------------------------------------------------------------------------------
/** \brief \ru Создать пустую систему ограничений.
           \en Create a simple constraint system. \~  
    \details \ru Вызов создает пустую систему ограничений. Кроме того, в памяти 
  создаются внутренние структуры данных геометрического решателя, обслуживающего 
  систему ограничений. Функция возвращает специальный дескриптор, по которому
  система ограничений доступна для различных манипуляций: добавление или удаление 
  геометрических объектов, ограничений, варьирование размеров, драггинг 
  недоопределенных объектов и т.д.
             \en The call creates an empty constraint system. Besides, there are created 
  internal data structures of geometric solver maintaining the system of constraints. 
  The function returns a special descriptor by which
  the constraint system is available for various manipulations: addition and deletion 
  of geometric objects, constraints, variation of sizes, dragging 
  underdetermined objects etc. \~
          
  \return \ru Дескриптор системы ограничений.
          \en Descriptor of  constraint system. \~
*/
//---
GCM_FUNC(GCM_system) GCM_CreateSystem( ItPositionManager * );

/** \} */

//----------------------------------------------------------------------------------------
// Запрос на аргумент (создать впервые или найти имеющийся), основано на базовом API
/*
  Internal use only.
*/
//---
GCM_geom GCM_QueryArgument( GCM_system gSys, const MtArgument & gArg );

/*
  Deprecated typenames
*/
typedef MtGeomSolver      IfGCManager;
typedef MtRepositionMode  MtTypeOfReposition;

#endif // __GCM_MANAGER_H

// eof
