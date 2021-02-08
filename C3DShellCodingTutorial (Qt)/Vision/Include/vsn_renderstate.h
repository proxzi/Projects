////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс Renderstate представляет состояние отрисовки объекта.
         \en Renderstate class represents an object rendering state. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_RENDERSTATE_H
#define __VSN_RENDERSTATE_H

#include <set>
#include <unordered_map>

#include "vsn_material.h"
#include "vsn_namespace.h"

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class RenderStatePrivate;
class CuttingUtil;
//------------------------------------------------------------------------------
/** \brief  \ru Состояние отрисовки объекта.
            \en Object rendering state.
    \details  \ru Класс RenderState хранит состояние отрисовки и предоставляет
                  функции для управления режимами отрисовки объектов RenderObject.
              \en RenderState class stores a rendering state and provides 
                  functions to control RenderObject object rendering modes. \~
*/
//---
class VSN_CLASS RenderState
{
public: /** \ru \name Конструкторы.
            \en \name Constructors.
            \{ */

    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    RenderState();

    /// \ru Конструктор копирования. \en Copy constructor. \~
    RenderState( const RenderState& other );  

    /// \ru Деструктор. \en Destructor.
    virtual ~RenderState();
public: /** \}
            \ru \name Функции получения/задания свойств отрисовки.
            \en \name The functions to return/set rendering properties.
            \{ */
    /// \ru Вернуть текущее состояние отрисовки. \en Returns the current rendering state. \~
    RenderingState GetRenderingState() const;
    /// \ru Установить состояние отрисовки. \en Sets the rendering state. \~
    void  SetRenderingState( RenderingState state );

    /** \brief \ru Вернуть собственное состояние отрисовки. 
               \en Returns the proper rendering state. \~
        \details \ru Функция возвращает собственное состояние отрисовки, присущее данному 
                    объекту вне зависимости от его временных состояний, таких как режим подсветки 
                    или выбор.
                 \en The function returns the proper rendering state that belongs to given 
                     object not depending on its temporary states such as highlight mode and selection. \~
    */
    RenderingState GetProperRenderingState() const;

    /** \brief \ru Вернуть значение режима отрисовки для граней.
               \en Returns rendering mode value for faces. \~ 
        \return \ru Одно из следующих значений отрисовки: GL_FRONT_AND_BACK, GL_FRONT или GL_BACK.
                \en One of the following rendering values: GL_FRONT_AND_BACK, GL_FRONT and GL_BACK. \~
    */
    uint GetPolyFaceMode() const;

    /** \brief \ru Вернуть значение режима отрисовки для полигонов.
               \en Returns rendering mode value for polygons.
        \return \ru Одно из следующих значений отрисовки: GL_POINT, GL_LINE или GL_FILL.
                \en One of the following rendering values: GL_POINT, GL_LINE and GL_FILL.
    */
    uint GetPolygonMode() const;
    /** \brief \ru Установить режим отображения для граней и полигонов.
               \en Sets rendering mode for faces and polygons. \~
        \param[in] fMode - \ru Режим отрисовки для граней с одним из следующих значений: GL_FRONT_AND_BACK, GL_FRONT, and GL_BACK.
                            \en Rendering mode for faces with one of the following values: GL_FRONT_AND_BACK, GL_FRONT, and GL_BACK. \~
        \param[in] pMode - \ru Режим отрисовки для кривых с одним из следующих значений: GL_POINT, GL_LINE, or GL_FILL.
                           \en Rendering mode for curves with one of the following values: GL_FRONT_AND_BACK, GL_FRONT, and GL_BACK. \~
    */  
    void SetPolygonMode(uint fMode, uint pMode);

    /// \ru Вернуть текущий режим визуализации модели. \en Returns the current model visualization mode. \~
    RenderMode  GetRenderingMode() const;
    /// \ru Установить текущий режим визуализации модели. \en Sets the current model visualization mode. \~
    void SetRenderingMode(RenderMode mode);

    /** \brief \ru Вернуть true, если текущий режим требует отрисовки с прозрачностью.
               \en True if the current mode requires transparency rendering.
    */
    bool IsTransparencyRequired() const;

    /// \ru Вернуть текущий индекс геометрической части. \en Returns the current index of geometry part. \~
    int GetCurrentBodyIndex() const;

    /// \ru Задать текущий индекс геометрической части. \en Sets the current index of geometry part. \~
    void SetCurrentBodyIndex( int partIdx );

    // \ru Вернуть true, если состояние визуализации имеет значение по умолчанию. \en True if visualization state has the default value. \~
    bool IsRenderStateDefault() const;

public: /** \}
            \ru \name Функции работы с материалом.
            \en \name The functions for working with material.
            \{ */

    /** \brief \ru Вернуть указатель на другой материал, отличный от исходного. 
                \en Returns pointer to other material that is different from the source. \~
    */
    Material* GetSpecialMaterial() const;

    /** \brief \ru Задать другой материал, отличный от исходного.
               \en Sets other material that is different from the source. \~
    */
    void SetSpecialMaterial( Material* pMaterial );

    /** \brief \ru Установить прозрачность специального материала.
               \en Sets transparency for the special material. \~
    */
    void SetSpecialMaterialTransparency( float alpha );

    /** \brief \ru Вернуть прозрачность специального материала.
               \en Returns transparency for the special material. \~
    */
    float GetSpecialTransparency() const;

    /** \brief \ru Добавить специальный материал для примитива.
                \en Adds special material for primitive. \~
        \param[in] id - \ru Идентификатор примитива.
                        \en Primitive identifier. \~      
        \param[in] mat- \ru Указатель на идентификатор примитива.
                        \en Pointer to primitive identifier. \~      
        \param[in] partIdx - \ru Индекс геометрической части.
                            \en Geometry part index. \~ 
    */
    void AddSpecialMaterial(uint id, Material* mat, int partIdx = 0);

    /// \ru Очистить специальные материалы. \en Clears special materials.
    void ClearSpecialMaterials();

    /** \brief \ru Вернуть контейнер специальных материалов текущей геометрической части.
               \en Returns special material container of the current geometry part. \~
        \details \ru Функция возвращает таблицу указателей на специальные материалы и 
                    идентификаторы примитивов текущей геометрической части. 
                 \en The function returns pointer map to special materials and 
                     primitive identifiers of the current geometry part. \~
    */
    std::unordered_map<uint, Material*>* GetSpecialMaterials() const;
    /** \brief \ru Вернуть true, если нет специальных материалов.
               \en True if no special materials. \~
    */
    bool IsSpecialMaterialsEmpty() const;

    /// \ru Применить указанный материал. \en Applies the specified material. \~
    void ApplyMaterial(Material* pMaterial);

    /// \ru Исключить указанный материал. \en Excludes the specified material. \~
    void ExcludeMaterial(Material* pMaterial);
public: /** \}
            \ru \name Функции управления выбором.
            \en \name Selection control functions.
            \{ */


    /// \ru Вернуть массив подсвеченных объектов. \en Returns highlighted objects array. \~
    std::unordered_map<int, uint>* GetHighlightedPrimitives() const;
    /** \brief \ru Вернуть true, если примитив является выбранным.
               \en True if primitive is selected.
      \param[in] id - \ru Идентификатор примитива.
                      \en Primitive identifier. \~
    */
    bool IsHighlightedPrimitive(uint id) const;
    /// \ru Вернуть true, если нет подсвеченых объектов. \en Returns true if there are no highlighted objects. \~
    bool IsHighlightedEmpty() const;
    /// \ru Вернуть true, если массив подсвеченных примитивов пуст. \en True if array of highlighted primitives is empty. \~
    bool IsNoHighlightedPrimitive() const;
    /** \brief \ru Вернуть идентификатор подсвеченного примитива текущей геометрической части.
               \en Returns identifier of highlighted primitive of the current geometry part.\~
    */
    uint GetHighlightedPrimitive(int body) const;
    /** \brief \ru Добавить подсвеченый примитив по идентификатору и индексу геометрической части.
               \en Adds primitive by identifier and geometry part index to highlight. \~
    */
    void SetHighlightedPrimitiveId(uint, int body = 0);
    /** \brief \ru Удалить примитив по идентификатору и индексу геометрической части.
               \en Remove primitive by identifier and geometry part index to selection. \~
    */
    void RemoveHighlightedPrimitiveId(uint id, int body);

    /// \ru Вернуть true, если текущий режим отрисовки является выбранным. \en True if the current rendering mode is selected. \~
    bool IsSelected() const;
    /// \ru Установить/Сбрость выбор. \en Sets/Resets selection. \~
    void SetSelected(bool selected);
    /// \ru Отменить выбор. \en Unselect.
    void Unselect();
    /** \brief \ru Вернуть true, если примитив является выбранным.
               \en True if primitive is selected.
        \param[in] id - \ru Идентификатор примитива.
                        \en Primitive identifier. \~
    */
    bool IsSelectedPrimitive(uint id) const;
    /** \brief \ru Вернуть true, если примитив по этому идентификатору и индексу тела является выбранным.
               \en True if primitive by identifier and body index is selected. \~
        \param[in] id - \ru Идентификатор примитива.
                        \en Primitive identifier. \~
        \param[in] partIdx - \ru Индекс геометрической части.
                             \en Geometry part index. \~
    */
    bool IsSelectedPrimitive(int partIdx, uint id) const;
    /// \ru Вернуть true, если массив выбранных примитивов пуст. \en True if array of selected primitives is empty. \~
    bool IsNoSelectedPrimitive() const;
    /** \brief \ru Вернуть массив идентификаторов выбранных примитивов текущей геометрической части.
               \en Returns identifier array of selected primitives of the current geometry part.\~
    */
    std::set<uint>* GetSelectedPrimitives() const;
    /** \brief \ru Добавить массив выбранных примитивов по идентификатору и индексу тела.
               \en Adds selected primitive array by identifier and body index. \~
    */
    void AddSelectedPrimitivesId(const std::set<uint>&, int body = 0);
    /** \brief \ru Добавить в выбор примитив по идентификатору и индексу геометрической части.
               \en Adds primitive by identifier and geometry part index to selection. \~
    */
    void AddSelectedPrimitiveId(uint, int body = 0);
    /** \brief \ru Удалить примитив по идентификатору и индексу геометрической части.
               \en Remove primitive by identifier and geometry part index to selection. \~
    */
    void RemoveSelectedPrimitiveId(uint id, int body);
    /// \ru Очистить выбранные примитивы. \en Clears all selected primitives. \~
    void ClearSelectedPrimitives();
public: 
    /// \ru Получить указатель на инструмент для отсечения. \en NO TRANSLATION. \~
    CuttingUtil* GetCuttingTool() const;
    /// \ru Установить указатель на инструмент для отсечения. \en NO TRANSLATION. \~
    void SetCuttingTool(CuttingUtil * tool);
    /// \ru Получить модельньную матрицу. \en NO TRANSLATION. \~
    const MbMatrix3D & GetModelViewMatrix() const;
    /// \ru Установить модельньную матрицу. \en NO TRANSLATION. \~
    void SetModelViewMatrix(const MbMatrix3D& mx);
    // получить масштаб
    double GetScale() const;
    // установить масштаб
    void SetScale(double scale);
public: /** \} */
    /** \brief  \ru Очистить содержимое визуализации и обновить значения материалов.
                \en Clears visualization content and update material values. \~
    */
    void Clear();
    /// \ru Оператор присвоения. \en Assignment operator.
    RenderState & operator = ( const RenderState & );
private:
  VSN_DECLARE_PRIVATE( RenderState )
};

VSN_END_NAMESPACE

#endif /* __VSN_RENDERSTATE_H */
