////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Глобальные настройки для модуля визуализации.
           \en Global settings for visualization module. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_GLOBALFLAGS_H
#define __VSN_GLOBALFLAGS_H

#include "vsn_string.h"
#include "vsn_namespace.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

//-----------------------------------------------------------------------------
/**
\brief \ru Глобальные настройки для модуля визуализации.
       \en Global settings for visualization module. \~
    \details \ru Класс GlobalFlags предоставляет функции для управления общими наcтройками модуля визуализации C3D Vision.
             \en GlobalFlags class provides functions to control C3D visualization module (C3D Vision) global settings. \~
*/
//---
class VSN_CLASS GlobalFlags
{
private:
    explicit GlobalFlags();
public:
    ~GlobalFlags();
public:
    /// \ru Инициализировать значения по умолчанию. \en Initializes default values.
    static void Initialize();
public:
    /// \ru Вернуть версию OpenGL. \en Returns OpenGL version.
    static String GetVersionOpenGl();
    /// \ru Вернуть имя поставщика. \en Returns vendor name.
    static String GetVendorOpenGl();
    /// \ru Вернуть имя отрисовщика OpenGL. \en Returns OpenGL render name.
    static String GetRendererOpenGl();

    /// \ru Вернуть true, если есть возможность загрузить данные на видеоустройство. \en True if possible to load data into video device.
    static bool HasVertexBufferObject();
    /** \brief \ru Вернуть true, если есть поддержка языка высокого уровня для программирования шейдеров.
    \en True if high-level language support for shader programing is available.
    */
    static bool HasGlsLanguage();
    /** \brief \ru Возвращает true, если есть поддержка закадровой отрисовки и отрисовка текстуры.
    \en True if frame buffer rendering is available and texture rendering too. \~
    */
    static bool HasFrameBufferObject();
    /** \brief  \ru Возвращает true, если есть поддержка закадровой отрисовки и отрисовка текстуры с копированием прямоугольной области пикселей.
    \en True if frame buffer rendering is available and texture rendering with pixel rectangular area copying too.
    */
    static bool HasFrameBufferObjectBlit();
    /// \ru Возвращает true, если есть поддержка точечных спрайтов. \en True if point sprites is available.
    static bool HasPointSprites();

    /// \ru Вернуть флаг возможности загрузки данных в VBO. \en Returns flag of loading data possibility for the Vertex Buffer Object (VBO).
    static bool IsVertexBufferObject();
    /// \ru Установить флаг использования загрузки данных в VBO. \en Sets flag of loading data usage for VBO.
    static void SetVertexBufferObject(bool set);

    /// \ru Вернуть флаг использования языка высокого уровня для программирования шейдеров. \en Returns flag of high-level language usage for shader programing.
    static bool IsGlsLanguage();
    /// \ru Установить флаг использования языка шейдеров. \en Sets shader language use flag.
    static void SetGlsLanguage(bool set);

    /// \ru Вернуть флаг выбора шейдера. \en Returns shader selection flag.
    static bool IsSelectionShader();
    /// \ru Установить флаг использования выбора шейдера. \en Sets shader selection use flag.
    static void SetSelectionShader(bool set);

    /// \ru Вернуть флаг режима выбора. \en Returns selection mode flag.
    static bool IsSelectionMode();
    /// \ru Установить флаг режима выбора. \en Sets selection mode flag.
    static void SetSelectionMode(bool set);

    /// \ru Вернуть true, если используется pixel culling. \en True if pixel culling is used.
    static bool IsPixelCulling();
    /// \ru Установить флаг использования pixel culling. \en Sets pixel culling use flag.
    static void SetPixelCulling(bool set);

    /// \ru Вернуть true, если учитывается ориентированный габарит при pixel culling. \en NO TRANSLATION.
    static bool IsPixelCullingOrientedBoundBox();
    /// \ru Установить флаг с учетом ориентированного габарита при pixel culling. \en NO TRANSLATION.
    static void SetPixelCullingOrientedBoundBox(bool set);

    /// \ru Вернуть флаг использования пространственного разбиения. \en Returns bounding volume use flag.
    static bool IsBoundingVolume();
    /// \ru Установить флаг использования пространственного разбиения. \en Sets bounding volume use flag.
    static void SetBoundingVolume(bool set);

    /// \ru Вернуть флаг использования отсечения по пирамиде. \en Returns frustum culling use flag.
    static bool IsFrustumCulling();
    /// \ru Установить флаг использования отсечения по пирамиде. \en Sets frustum culling use flag.
    static void SetFrustumCulling(bool set);

    /// \ru Вернуть флаг "скрывать ребра" при манипуляцией со сценой. \en NO TRANSLATION.
    static bool IsHiddenEdges();
    /// \ru Установить флаг "скрывать ребра" при манипуляцией со сценой. \en NO TRANSLATION.
    static void SetHideEdges(bool set);

    /// \ru Готовы ли все флаги к использованию пользователем. \en Checks if all flags are ready to be used by user.
    static bool IsReadyFlags();

    /// \ru Вернуть значение строить четырехугольную сетку. \en Returns value build quadrangle grid.
    static bool IsBuildQuadGrid();
    /// \ru Установить флаг строить четырехугольную сетку. \en Set the flag to build a quad grid.
    static void SetBuildQuadGrid(bool bBuild);

    /// \ru Вернуть тип подсветки грани. \en Returns highlight type to face.
    static HighlighterType GetFaceHighlighter();
    /// \ru Установить тип подсветки грани. \en Sets highlight type to face.
    static void SetFaceHighlighter(HighlighterType type);
};
VSN_END_NAMESPACE


#endif // __VSN_GLOBALFLAGS_H
