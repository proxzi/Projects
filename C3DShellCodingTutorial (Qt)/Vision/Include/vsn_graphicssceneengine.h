////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс GraphicsScene представляет реализацию отрисовки сцены OpenGl'ем.
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GRAPHICSSCENEENGINE_H
#define __VSN_GRAPHICSSCENEENGINE_H

#include "vsn_visionengine.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class Process;
class SceneSegment;
class GraphicsScene;
class ObjectPickSelection;
class GraphicsSceneEnginePrivate;
/* GraphicsSceneEngine */
class VSN_CLASS GraphicsSceneEngine : public Object
{
    VSN_OBJECT(GraphicsSceneEngine);
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION. \~
    explicit GraphicsSceneEngine();
    /// \ru Деструктор. \en NO TRANSLATION. \~
    virtual ~GraphicsSceneEngine();
public:
    /// \ru Инициализация. \en NO TRANSLATION. \~
    void Initialize();
    /// \ru Подготовка сцены к отображению. \en NO TRANSLATION. \~
    void PreparingToDisplay();
    /// \ru Вернуть указатель на VisionEngine. \en NO TRANSLATION. \~
    VisionEnginePtr GetVisionEngine() const;
    /// \ru Вернуть указатель на Essence. \en NO TRANSLATION. \~
    Essence* GetTopEssence() const;
    /// \ru Вернуть указатель на SceneSegment. \en NO TRANSLATION. \~
    SceneSegment* GetTopSceneSegment() const;
    /// \ru Вернуть указатель на содержание сцены. \en NO TRANSLATION.\~
    std::shared_ptr<SceneContent> GetSceneContent() const;
    /// \ru Вернуть указатель на сцену отрисовки графа. \en NO TRANSLATION. \~
    GraphicsScene* GetGraphicsScene() const;
    /// \ru Вернуть указатель на компонент выбора объектов. \en NO TRANSLATION. \~
    ObjectPickSelection* GetObjectPickSelection() const;
private:
    VSN_DISABLE_COPY(GraphicsSceneEngine);
    VSN_DECLARE_PRIVATE(GraphicsSceneEngine);
};

typedef std::shared_ptr<GraphicsSceneEngine> GraphicsSceneEnginePtr;

VSN_END_NAMESPACE

#endif // __VSN_GRAPHICSSCENEENGINE1_H
