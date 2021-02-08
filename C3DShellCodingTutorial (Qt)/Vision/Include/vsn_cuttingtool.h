////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Инструмент для управления плоскостями динамического сечения.
         \en The tool to control planes of a dynamic section. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_CUTTINGTOOL_H
#define __VSN_CUTTINGTOOL_H

#include <mb_placement3d.h>

#include "vsn_global.h"
#include "vsn_objectdefs.h"
#include "vsn_object.h"

VSN_BEGIN_NAMESPACE
class  Material;
class  RenderContainer;
class  Widget3DBasic;
class  CuttingToolPrivate;
struct RenderLayersParameters;
class  CuttingUtil;
typedef uint64 SectionPlaneId;

//------------------------------------------------------------------------------
/** \brief \ru Инструмент для управления плоскостями динамического сечения.
           \en The tool to control planes of a dynamic section. \~
*/
// ---
class VSN_CLASS CuttingTool : public Object
{
    VSN_OBJECT(CuttingTool)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    CuttingTool( CuttingUtil &, RenderLayersParameters& );
    /// \ru Деструктор. \en Destructor. \~
    ~CuttingTool();
public:
    /// \ru Вернуть признак включения режима динамического сечения. \en Returns flag of dynamic section mode enabled. \~
    bool IsEnabled() const;
     /// \ru Включить/Выключить режим динамического сечения. \en Turns dynamic section mode on or off. \~
    void SetEnable(bool bEnable);
     /// \ru Добавить секущую плоскость. \en Adds section plane. \~
    SectionPlaneId AddSectionPlane(const MbPlacement3D& plane);
     /// \ru Удалить секущую плоскость. \en Deletes section plane. \~
    void DeleteSectionPlane(SectionPlaneId id);
    /// \ru Вернуть признак включения секущей плоскости. \en Returns flag of section plane enabled. \~
    bool IsEnabled(SectionPlaneId id) const;
    /// \ru Включить/выключить секущую плоскость. \en Turns section plane on or off. \~
    void SetEnable(SectionPlaneId id, bool bEnable);
     /// \ru Изменить отсекаемую часть. \en Changes isolated section. \~
    void Invert(SectionPlaneId id, bool bInvert);
     /// \ru Признак направления отсекаемой стороны. \en Flag of isolated section direction. \~
    bool IsInverted(SectionPlaneId id) const;
     /// \ru Замкнуть оболочку, полученную с помощью указанной плоскости. \en Closes shell received with specified plane. \~
    void CloseSectionPlane(SectionPlaneId id, bool fill);
     /// \ru Нужно ли замкнуть оболочку. \en Checks if shell must be closed. \~
    bool IsClosedSectionPlane(SectionPlaneId id) const;
     /// \ru Включить режим отображения с манипулятором. \en Enables interactive mode with manipulator. \~
    void EnableInteractiveMode(SectionPlaneId idbool, bool bEnable );
     /// \ru Проверить режим отображения с манипулятором. \en Checks interactive mode with manipulator. \~
    bool IsEnabledInteractiveMode(SectionPlaneId id) const;
     /// \ru Получить математику плоскости. \en Returns plane math. \~
    const MbPlacement3D & GetPlacement(SectionPlaneId id) const;

     /** \brief \ru Получить параметры плоскости (угол в градусах).
                \en Returns plane parameters (angle in degrees). \~
         \param[in] id - \ru Идентификатор плоскости. 
                         \en Plane identifier. \~
         \param[in] angle1 - \ru Первый угол направления нормали. 
                             \en The first angle of normal direction. \~
         \param[in] angle2 - \ru Второй угол направления нормали. 
                             \en The second angle of normal direction. \~
         \param[in] offset - \ru Смещение плоскости. 
                             \en Plane offset. \~
     */
     void GetParams(SectionPlaneId id, double& angle1, double& angle2, double& offset) const;

     /** \brief \ru Материал созданной поверхности для замкнутой оболочки ("крышка").
                \en Material of created plane for closed shell ("cover"). \~
         \param[in] id - \ru Идентификатор плоскости. 
                         \en Plane identifier. \~
         \param[in] material - \ru Материал. 
                               \en Material. \~
     */
     void SetSurfaceMaterial(SectionPlaneId id, std::shared_ptr<Material> material); 

     /// \ru Изменить параметры плоскости. \en Changes plane parameters. \~
     void Init( SectionPlaneId id, const MbPlacement3D& plane);
     /** \brief \ru Изменить параметры плоскости (угол в градусах).
                \en Changes plane parameters (angle in degrees). \~
         \param[in] id \ru Идентификатор плоскости. 
                       \en Plane identifier. \~
         \param[in] angle1 - \ru Первый угол направления нормали. 
                             \en The first angle of normal direction. \~
         \param[in] angle2 - \ru Второй угол направления нормали. 
                             \en The second angle of normal direction. \~
         \param[in] offset - \ru Смещение плоскости. 
                             \en Plane offset. \~
     */
     void Init( SectionPlaneId id, double angle1, double angle2, double offset );
public:
    /// \ru Cигнал об изменении позиции плоскости при помощи манипуляторов. \en Signal about modifying plane position with manipulators. \~
    VSN_SIGNAL(Public, OnChangePlacement, void OnChangePlacement(SectionPlaneId id), id);
public:
    /// \ru Получить список всех созданных плоскостей. \en Returns list of all created planes. \~
    std::list<SectionPlaneId> GetSectionPlanes() const;
    /** \brief \ru Нарисовать плоскости.
               \en Renders planes. \~
        \param[in] gab  - \ru Габарит, в котором нужно отобразить плоскости. 
                          \en Size in which planes must be displayed. \~
    */
    void RenderPlanes( const MbCube& gab ) const;
    /// \ru Получить контейнер манипуляторов. \en Returns manipulator container. \~
    RenderContainer& GetWidgets3D();
private:
    VSN_DECLARE_PRIVATE(CuttingTool)
};

VSN_END_NAMESPACE

#endif // __VSN_CUTTINGTOOL_H
