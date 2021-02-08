//////////////////////////////////////////////////////////////////////////////////////////
/** 
  \file     
  \brief  Абстрактный интерфейс для чёрного ящика
*/
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GCM_BLACKBOX_H
#define __GCM_BLACKBOX_H

#include <mb_placement3d.h>
#include <templ_ifc_array.h>
#include <templ_s_array.h>
#include <gcm_geom.h>
#include <gcm_manager.h>

//----------------------------------------------------------------------------------------
/** \brief  \ru Чёрный ящик.
            \en Blackbox. \~
  \details  
    \ru Черный ящик реализует закон позиционирования геометрических объектов, зависящих 
  от позиции других объектов. Интерфейс #ItGCBlackbox реализуется обычно на стороне 
  клиентского приложения и передается геометрическому решателю для исполнения через метод 
  #MtGeomSolver::AddBlackbox. например, в системе КОМПАС-3D черный ящик применяется для 
  моделирования массивов тел (паттерны), которые родились путем тиражирования детали
  по закону определенному на стороне приложения. 
    Черный ящик может применяться не только для организации паттернов, но и для задания на 
  стороне клиентского приложения различных однонаправленных зависимостей,  с определенным 
  законом позиционирования тел. Объекты, которые рассматриваются, как входящие для черного 
  ящика, называются независимыми. Объекты, которые рассматриваются, как исходящие для 
  черного ящика, называются зависимыми.
            \en Blackbox implements a law of positioning of geometric objects which are 
  dependent on positions of other objects. Interface #ItGCBlackbox is usually implemented 
  on the side of application and it is transferred from the application to the solver 
  by method #MtGeomSolver::AddBlackbox. The functionality of blackboxes can be used to 
  the organization of patterns in assembly structures, when the elements of the pattern 
  are copies of the same part replicated according to a law specified my the application. \~
    \ingroup  GCM_3D_ObjectAPI
*/
//---
struct ItGCBlackbox
{
	/// \ru Выдать независимые геометрические объекты. \en The function collects in the array independent geoms of a blackbox.
	virtual void    CollectMyInGeoms( IFC_Array<ItGeom> & ) const = 0;
	/// \ru Выдать зависимые геометрические объекты. \en The function collects in the array dependent geoms of a blackbox.
	virtual void    CollectMyOutGeoms( IFC_Array<ItGeom> & ) const = 0;
	/** \brief \ru Рассчитать положение зависимого объекта.
             \en Calculate position of a dependent geometric object. \~
    \param[in]  inPlaces  - \ru Позиции независимых объектов, получаемых методом #ItGCBlackbox::CollectMyInGeoms.
                            \en Positions of independed geoms, which are got by #ItGCBlackbox::CollectMyInGeoms.\~
    \param[in]  depGeom   - \ru Зависимый геометрический объект.
                            \en Depended geometric object.\~
    \param[out] depPlace  - \ru Вычисленное положение для объекта outGeom.
                            \en Calculated position for a dependent geom 'outGeom'\~
    \return                 \ru true, если функция корректно исполнена.    
                            \en true if the function performed succeeded. \~
  */
	virtual bool    Calculate(  const SArray<MbPlacement3D> & inPlaces
                            , const ItGeom  & depGeom
                            , MbPlacement3D & depPlace ) const = 0;
	/// \ru Является ли данный объект зависимым для черного ящика? \en Check if the given geometric item is dependent
	virtual bool    IsMyOutGeom( const ItGeom & ) const = 0;
  /** 
    \brief \ru Сформулировать ограничения для зависимого геометрического объекта. 
           \en Formulate constraints for the dependent geometric object. \~
    \details \ru Функция позволяет задать положение зависимого объекта относительно управляющих в явном виде с помощью 
                 интерфейса #MtGeomSolver (#MtGeomSolver::AddConstraint, #MtGeomSolver::AddConstraintItem, 
                 #MtGeomSolver::AddPattren). Данный механизм является альтернативой вызову #ItGCBlackbox::Calculatе.
                 Его использование сообщает решателю не только о наличии зависимости (как в случае с 
                 #ItGCBlackbox::Calculatе), но и о ее характере. Данное знание позволяет расширить класс разрешимых 
                 задач, но в некоторых случаях может привести к ухудшению производительности.
             \en The function allows to set the position of the dependent object relative to it's governing objects 
                 explicitly using the interface #MtGeomSolver (#MtGeomSolver::AddConstraint, 
                 #MtGeomSolver::AddConstraintItem, #MtGeomSolver::AddPattren). This mechanism is an alternative to calling 
                 #ItGCBlackbox::Calculate. Using this mechanism provides an information about the dependency character.
                 This information allows to extend the class of solvable problems but in some cases can lead to 
                 performance degradation.
    \param[in, out] solver  - \ru Система ограничений. 
                              \en System of constraints. \~
    \param[in]      outGeom - \ru Зависимый геометрический объект. 
                              \en Depended geometric object.\~
    \return \ru Должна возвращать true, если положение зависимого объекта было задано в явном виде через задание в 
                решателе нужных для этого ограничений; если же положение зависимого объекта должно вычисляться с помощью 
                метода #ItGCBlackbox::Calculate, функция должна возвращать false.
            \en The function should return true, if the position of the dependent object was formulated in the 
                constraints solver explicitly using #MtGeomSolver::AddConstraint, #MtGeomSolver::AddConstraintItem or 
                #MtGeomSolver::AddPattren methods.
                If the position of the dependent object must be calculated using the method #ItGCBlackbox::Calculate, 
                the function should return false.
  */
  virtual bool    FormulateOutGeom( MtGeomSolver & solver, ItGeomPtr outGeom );
  /**
    \brief \ru Завершить работу с черным ящиком. \en To finish work with the black box. \~
    \details \ru Функция предоставляет возможность пользователю данного интерфейса корректно завершить работу с черным 
                 ящиком в тот момент, когда он удаляется в решателе.
             \en The function allows the user of this interface correctly to complete work with the black box when 
                 it is removing from the solver. \~
  */ 
  virtual void    FinishBlackBox() {}

public:
  virtual refcount_t AddRef() const = 0;
  virtual refcount_t Release() const = 0;
};

//----------------------------------------------------------------------------------------
// \ru Сформулировать ограничения для зависимого геометрического объекта. \en Formulate constraints for the dependent geometric object. \~
// ---
inline bool ItGCBlackbox::FormulateOutGeom( MtGeomSolver & /*solver*/, ItGeomPtr /*outGeom*/ )
{
  return false;
}

#endif // __GCM_BLACKBOX_H

// eof
