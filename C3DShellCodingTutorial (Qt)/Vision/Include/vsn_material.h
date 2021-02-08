////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Классы Material и SelectionMaterial для работы с визуальными свойствами материала.
       \en Material class and SelectionMaterial class for working with visual properties of the material. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATERIAL_H
#define __VSN_MATERIAL_H

#include <string>


//#include "vsn_openglcontext.h"
#include "vsn_color.h"
#include "vsn_feature.h"
#include "vsn_node.h"

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Texture2D;
class MaterialPrivate;
class OpenGLContextInterface;
class Geometry;
//------------------------------------------------------------------------------
/** \brief   \ru Визуальные свойства материала.
             \en Visual properties of the material. \~
    \details \ru Класс Material позволяет задавать визуальные параметры материала.
             \en Material class allows setting visual parameters of the material. \~
*/
//---
class VSN_CLASS Material : public Feature
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    Material();
    /**
    \brief \ru Конструктор по диффузному цвету. \en Constructor by diffuse color. \~
        \details \ru Конструктор задает диффузный цвет; цвет фона по умолчанию темно-серый.
                 \en The constructor sets diffuse color; the default ambient color is dark grey.
    */
    Material(const Color& color, double opacity = 1.);
    /**
    \brief \ru Конструктор по диффузному цвету. \en Constructor by diffuse color.  \~
        \param[in] name - \ru Строковое имя материала.
                          \en String name of the material. \~
        \param[in] pDiffuseColor - \ru Цвет диффузии материала.
                                   \en Diffuse color of the material. \~
        \details \ru Конструктор задает имя материала и диффузный цвет; цвет фона по умолчанию темно-серый.
                 \en The constructor sets material name and diffuse color; the default ambient color is dark grey.
    */
    Material(const String& name, const float* pDiffuseColor);
    /// \ru Конструктор по текстуре и имени материала. \en Constructor by texture and material name.
    Material(Texture2D* pTexture, const String& name = String());

    /// \ru Конструктор копирования. \en Copy constructor.
    Material(const Material& material);

    virtual ~Material();
public:
    /// \ru Задать другое значение материала. \en Sets other material value.
    void CopyFrom(const Material& material);
    /// \ru Вернуть true, если этот материал не применяется. \en True if material is not used.
    bool IsMaterialUnused() const;
    /// \ru Вернуть true, если материал представлен текстурой. \en True if material is represented by texture.
    bool IsMaterialPresentedTexture() const;
    /// \ru Вернуть цветовое значение общего фона. \en Returns the ambient color value.
    Color GetAmbient() const;
    /// \ru Задать цвет общего фона. \en Sets ambient color.
    void SetAmbient(const Color& ambient);

    /// \ru Вернуть цветовое значение диффузии. \en Returns diffuse color value.
    Color GetDiffuse() const;
    /// \ru Задать цвет диффузии. \en Sets diffuse color.
    void SetDiffuse(const Color& diffuse);

    /// \ru Вернуть значение зеркальности. \en Returns specular value.
    Color GetSpecular() const;
    /// \ru Задать значение зеркальности. \en Sets specular value.
    void SetSpecular(const Color& specular);

    /// \ru Вернуть значение излучения. \en Returns emission value.
    Color GetEmission() const;
    /// \ru Задать значение излучения. \en Sets emission value.
    void SetEmission(const Color& emission);

    /// \ru Вернуть значение блеска. \en Returns shininess value.
    float GetShininess() const;
    /// \ru Задать значение блеска. \en Sets shininess value.
    void SetShininess(float shininess);

    /// \ru Вернуть идентификатор текстуры. \en Returns texture identifier.
    uint GetTextureID() const;

    /// \ru Вернуть true, если текстура загружена. \en True if texture is loaded.
    bool IsTextureLoaded() const;

    /// \ru Вернуть true, если материал является прозрачным. \en True if material is transparent.
    bool IsTransparent() const;
    /// \ru Вернуть значение непрозрачности. \ru Returns opacity value.
    double GetOpacity() const;
    /// \ru Задать непрозрачность. \ru Sets opacity.
    void SetOpacity(double opacity);
    /// \ru Вернуть количество геометрии, использующей этот материал. \en Return a count of the geometric objects which use the material.
    size_t GetUseCount() const;


    /// \ru Вернуть указатель на текстуру. \en Returns pointer to the texture.
    Texture2D* GetTexture() const;
    /// \ru Установить новую текстуру. \en Sets new texture.
    void SetTexture(Texture2D* pTexture);

    /// \ru Вернуть хэш, собранный из всех составляющих. \en Returns hash composed from all components.
    uint GetHashMaterial() const;
public:

    /// \ru Удалить текстуру. \en Deletes texture.
    void DeleteTexture();

    /// \ru Добавить объект, который использует этот материал. \en Adds object with given material.
    bool AddGeomObject(Geometry* pGeom);

    /// \ru Открепить геометрический объект, использующий этот материал, из массива. \en Detaches geometry object with given material from the array.
    bool DetachGeomObject(NodeKey id);

    /// \ru Добавить в массив идентификатор геометрии, использующий этот материал. \en Adds geometry identifier with given material to the array.
    bool AddObjectId(NodeKey id);

    /// \ru Открепить объект из массива идентификаторов, использующих этот материал. \en Detaches object from the array of identifiers that use this material.
    bool DetachObjectId(NodeKey id);
public:
    /// \ru Выполнить инициализацию материала для отрисовки. \en Initializes material for rendering.
    virtual void glPerform();
    /// \ru Выполнить инициализацию материала для отрисовки с прозрачностью. \en Initializes material for rendering with transparency.
    virtual void glPerform(float);
public:
    /// \ru Оператор присвоения. \en Assignment operator.
    Material& operator = (const Material& mat);
    /// \ru Вернуть true, если материал эквивалентен. \en True if material is equivalent.
    bool operator == (const Material&) const;
private:
    VSN_DECLARE_EX_PRIVATE(Material);
};


//------------------------------------------------------------------------------
/** \brief  \ru Функции задания параметров материала для выбранных объектов.
            \en Functions for setting material parameters of selected objects.
    \details  \ru Класс SelectionMaterial группирует в себе функции, с помощью которых можно задавать
                  свойства материала для выбранных объектов.
              \en SelectionMaterial class contains functions that provide setting
                  material properties for selected objects. \~
*/
//---
class VSN_CLASS SelectionMaterial
{
private:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    SelectionMaterial();
public:
    /// \ru Установить режим подсветки. \en Sets highlight mode.
    static void SetHighlightMode(bool highlight);
    /// \ru Установить цвет материала для подсветки. \en Sets material color for highlight.
    static void SetHighlightColor(const Color& color);
    /// \ru Установить цвет материала для выбора. \en Sets material colour for selection.
    static void SetSelectionColor(const Color& color);

    /// \ru Получит цвет материала для подсветки. \en Returns material color for highlight.
    static const Color& GetHighlightColor();
    /// \ru Получит цвет материала для выбора. \en Returns material colour for selection.
    static const Color& GetSelectionColor();

    /// \ru Установить новый материал для выбора. \en Sets new material for selection.
    static void SetSelectionMaterial(Material* pMaterial);
    /// \ru Установить признак блокировки использования материала для выбора. \en Sets flag of locking material usage for selection.
    static void SetLockSelectionMaterial(bool bLock);
    /// \ru Сбросить материал выбора. Если не используется, удалить его. \en Resets material for selection. If it is not used, deletes it.
    static void ResetSelectionMaterial();
public:

    /// \ru Создать шейдер для выбора. \en Creates selection shader.
    static void CreateShader(const OpenGLContextInterface* pContext);
    /// \ru Удалить шейдер. \en Deletes shader.
    static void DeleteShader(const OpenGLContextInterface* pContext);
    /// \ru Установить шейдер выбора из файла. \en Sets selection shader from file.
    static void SetShadersFromFile(std::istream & file, std::istream & fileFragment, const OpenGLContextInterface* pContext);
    /// \ru Вернуть true, если есть шейдер выбора. \en True if selection shader exists.
    static bool IsExistShader(const OpenGLContextInterface* pContext);
    /// \ru Использовать шейдер для выбора. \en Enables selection shader.
    static void UseShaderForSelection();
    /// \ru Не использовать шейдер для выбора. \en Disables selection shader.
    static void UnuseShaderForSelection();

    /// \ru Выполнить инициализацию материала для отрисовки. \en Initializes material for rendering.
    static void glPerform();
};
VSN_END_NAMESPACE

#endif /* __VSN_MATERIAL_H */
