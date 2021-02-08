///////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс Shader реализует пиксельный шейдер и его программу, этот класс обеспечивает
             загрузку, а также компиляцию и выполнение подпрограммы вершин и самого шейдера.
         \en Shader class implements a pixel shader and its program. This class provides
             loading and also compiling and performing subprogram of vertexes and shader itself. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_SHADER_H
#define __VSN_SHADER_H

#include <map>
#include <vector>
#include <unordered_map>

#include "vsn_string.h"
#include "vsn_global.h"

typedef unsigned int GLuint;
typedef unsigned int GLenum;

VSN_BEGIN_NAMESPACE
class OpenGLShaderProgram;
class ShaderPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс Shader реализует приксельный шейдер и его программу, этот класс обеспечивает
                загрузку, а также компиляцию и выполнение подпрограммы вершин и самого шейдера. 
            \en Shader class implements a pixel shader and its program. This class provides
                loading and also compiling and performing subprogram of vertexes and shader itself. \~
    \ingroup Vision_Shaders
*/
// ---
class VSN_CLASS Shader
{
public:
    /// \ru Конструктор по умолчанию. \en Default consructor. \~
    Shader();
    /// \ru Конструктор с загрузкой вершин и фрагмента. \en Constructor with loading vertexes and fragment. \~
    Shader(std::istream& vertex, std::istream& fragment);
    // конструктор копирования
    /// \ru Конструктор копирования. \en Copy constructor. \~
    Shader(const Shader&);
    /// \ru Деструктор. \en Destructor. \~
    ~Shader();
public:
    /// \ru Вернуть идентификатор программы. \en Returns program identifier. \~
    GLuint GetId() const;
    /// \ru Вернуть true, если шейдер используется. \en Returns true if shader is used. \~
    bool IsShaderUsed() const;
    /// \ru Вернуть true, если шейдер можно удалить. \en Returns true if shader can be deleted. \~
    bool IsCanBeDeleted() const;
    /// \ru Вернуть имя шейдера. \en Returns shader name. \~
    const String& GetName() const;
    /// \ru Установить имя шейдера. \en Sets shader name. \~
    void SetName(const String& name);
    /// \ru Вернуть указатель на QGLProgramShader для этого шейдера. \en Returns pointer to QGLProgramShader for this shader. \~
    OpenGLShaderProgram* GetProgramShader();
    /// \ru Вернуть идентификатор позиции. \en Returns position identifier. \~
    int GetPositionAttrId() const;
    /// \ru Вернуть идентификатор текстуры. \en Returns texture identifier. \~
    int GetTextureAttrId() const;
    /// \ru Вернуть идентификатор цвета. \en Returns color identifier. \~
    int GetColorAttrId() const;
    /// \ru Вернуть идентификатор нормали. \en Returns normal identifier. \~
    int GetNormalAttrId() const;
public:
    /// \ru Вернуть количество шейдеров. \en Returns shader quantity. \~
    static size_t GetShaderCount();
    /// \ru Вернуть true, если идентификатор группы применяется для шейдеров. \en Returns true if group identifier is applied for shaders. \~
    static bool IsExistIdAsShader(uint shadingGroupId);
    /// \ru Вернуть указатель на шейдер по идентификатору, если такого нет, то вернется nullptr. \en Returns pointer to shader by identifier, if no shader, then nullptr is returned. \~
    static Shader* GetShaderById(uint shadingGroupId);
    /// \ru Вернуть true, если есть активный шейдер. \en Returns true if there is an active shader. \~
    static bool IsExistActiveShader();
    /// \ru Вернуть указатель на активный шейдер, если такого нет, то вернется nullptr. \en Returns pointer to active shader, if no shader, then nullptr is returned. \~
    static Shader* GetActiveShader();
public:
    /// \ru Установить из файла шейдеры вершин и фрагмента. \en Sets shaders of vertexes and fragment from file. \~
    void SetupVertexFragmentShader(std::istream & vertex, std::istream & fragment);
    /// \ru Заменить этот шейдер копией другого шейдера. \en Replaces this shader with copy of another shader. \~
    void ReplaceShader(const Shader& other);
    /// \ru Вернуть идентификатор матрицы вида модели. \en Returns identifier of model view matrix. \~
    int GetModelViewMatrixId() const;
    /// \ru Вернуть идентификатор проекционной матрицы вида модели. \en Returns identifier of projection matrix of model view. \~
    int GetModelViewProjMatrixId() const;
    /// \ru Вернуть идентификатор видовой обратной матрицы (местоположения). \en Returns identifier of view inverse matrix (location). \~
    int GetModelViewInverseMatrixId() const;
public:
    /// \ru Вернуть идентификатор включения освещения. \en Returns identifier of lighting enabled. \~
    int GetEnableLightingId() const;
    /// \ru Вернуть идентификатор состояния освещенности. \en Returns identifier of lighting state. \~
    int GetEnableLightingStateId() const;
    /// \ru Вернуть положение источника света по его идентификатору. \en Returns position of light source by its identifier. \~
    int GetPositionLightingId(GLenum lightId) const;
    /// \ru Вернуть значение освещения общего фона по идентификатору. \en Returns value of ambient lighting by identifier. \~
    int GetAmbientLightingId(GLenum lightId) const;
    /// \ru Вернуть значение диффузии по идентификатору. \en Returns value of diffusion by identifier. \~
    int GetDiffuseLightingId(GLenum lightId) const;
    /// \ru Вернуть значение зеркальности по идентификатору. \en Returns value of specularity by identifier. \~
    int GetSpecularLightingId(GLenum lightId) const;
    /// \ru Вернуть значение пятна освещения по идентификатору. \en Returns value of lighting spot by identifier. \~
    int GetSpotDirectionLightingId(GLenum lightId) const;
    /// \ru Вернуть значение ослабления освещения по идентификатору. \en Returns value of lighting attenuation by identifier. \~
    int GetAttebuationFactorsLightingId(GLenum lightId) const;
    /// \ru Вернуть значение одиночного освещения (пятно) по идентификатору. \en Returns value of single lighting (spot) by identifier. \~
    int GetSpotExponentLightingId(GLenum lightId) const;
    /// \ru Вернуть значение среза пятна по идентификатору. \en Returns value of spot cut by identifier. \~
    int GetSpotCutoffLightingId(GLenum lightId) const;
    /// \ru Вернуть значение ослабления освещения от дистанции по идентификатору. \en Returns value of lighting attenuation from distance by identifier. \~
    int GetDistanceAttenuationLightingId(GLenum lightId) const;
public:
    /// \ru Активировать программу шейдера. \en Activates shader program. \~
    void ActivateProgram();
    /// \ru Aктивировать программу шейдера по идентификатору. \en Activates shader program by identifier. \~
    static bool ActivateProgram(uint ShadingGroupId);
    /// \ru Отключить программу шейдера. \en Deactivates shader program. \~
    static void DeactivateProgram();
    /// \ru Cоздать и слинковать программу шейдера, если линковка с ошибкой, то сработает исключение. \en Creates and links shader program. If linking error, then exception occurs. \~
    void CreateLinkProgrammShader();
    /// \ru Удалить шейдер. \en Deletes shader. \~
    void DeleteShader();
public:
    /// \ru Присвоить данные другому шейдеру. \en Assigns data to another shader. \~
    Shader& operator = (const Shader& other);
private:
    VSN_DECLARE_PRIVATE(Shader)
};
VSN_END_NAMESPACE

#endif /* __VSN_SHADER_H */
