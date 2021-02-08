#ifndef __VSN_RENDERLAYERS_H
#define __VSN_RENDERLAYERS_H

#include "vsn_namespace.h"
#include "vsn_light.h"



VSN_BEGIN_NAMESPACE

/*

*/
enum class LayerEnableParam
{
    on,     // \ru Включить. \n \en Turn on the parameter.\~
    off,    // \ru Выключить.\n \en Turn off the parameter.\~
    inherit // \ru Унаследовать значение. \n \en Inherit the value.\~
};


//------------------------------------------------------------------------------
/** \brief  \ru Настройки освещения слоя
            \en Lighting settings. \~

            \details \ru Позваляет установить разные источники освещения на каждый слой или выключить освещение.\n
                     \en Allows you to set different sources of lighting on each layer or turn off the lighting.\n \~
*/
// ---
struct LightingSettings
{
    LayerEnableParam                   m_enable = LayerEnableParam::inherit;
    std::list<std::shared_ptr<Light>>  m_lightsources;
};

//------------------------------------------------------------------------------
/** \brief  \ru Настройки динамического сечения 
            \en Dynamic section settings. \~

            \details \ru Позволяет задать разные плоскости динамического сечения на каждый слой или выключить динамическое сечение. \n
                     \en Allows you to set different dynamic section plane on each layer or turn off the dynamic section.\n \~
*/
// ---
typedef uint64 SectionPlaneId;
struct CuttingSettings
{
    LayerEnableParam         m_enable = LayerEnableParam::inherit;
    std::set<SectionPlaneId> m_ids;
};

class Material;
class RenderContext;
//------------------------------------------------------------------------------
/** \brief  \ru Настройки отрисовочного слоя
            \en Render layer settings. \~

            \details \ru Позволяет настроить режим отрисовки, освещение слоя, сечение модели.
                         Позваляет задать материал слою, для рисования всех объектов слоя одним материалом.
                         Есть возможность установить Callback функцию для собственной реализации отрисовки
                         Параметры могут наследовать свои значения.\n

            \en It Allows to customize the lighting, dynamic section and render mode.
                It Allows to set the layer material to render all layer objects uses only one material.
                It is possible to install Callback function for custom rendering. 
                Some parameters may inherit values. \n \~

*/
// ---
struct RenderLayerSettings
{
    // показать/погасить слой
    bool              m_enable     = true; 
    // Режим отображения
    RenderMode        m_mode       = RenderMode::rm_Inherit;
    // Настройки освещения
    LightingSettings  m_lighting   = {};
    // Настройки динамического сечения
    CuttingSettings   m_cutting    = {};
    // Пользовательский материал
    std::shared_ptr<Material>           m_pMaterial;
    // Пользовательская функция отрисовки
    std::function<void(RenderContext&)> m_customRender;
};


VSN_END_NAMESPACE

#endif //__VSN_RENDERLAYERS_H