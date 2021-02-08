#pragma once
#include <QVector>

#include <vsn_gridgeometry.h>
#include <qt_openglwidget.h>
#include <attribute.h>
#include <attr_geometric_attribut.h>

#include "consoletext.h"
#include "globaldef.h"

#include <solid.h>
//#include <last.h>
#define OTHER_METHOD_1 0
#define OTHER_METHOD_2 0

VSN_USE_NAMESPACE

VSN_BEGIN_NAMESPACE
class SphereRep;
VSN_END_NAMESPACE

class MbRefItem;

//struct TypeSpaceStr {
//    QString typeStr;
//    MbeSpaceType typeSpace;
//};

typedef std::vector<MbAttribute*> AttrVector;

struct SelectObjectInfo
{
    NodeKey m_segmentId = {};
    uint    m_indexBody = 0;
    uint    m_primitiveId = 0;
    Material* m_mat = nullptr;
    SelectObjectInfo() = default;

    SelectObjectInfo(NodeKey segmentId, uint indexBody, uint primitiveId)
        : m_segmentId(segmentId)
        , m_indexBody(indexBody)
        , m_primitiveId(primitiveId)
    {}

    bool operator == (const SelectObjectInfo& other) const
    {
        return m_segmentId == other.m_segmentId &&
            m_indexBody == other.m_indexBody &&
            m_primitiveId == other.m_primitiveId;
    }

    bool operator != (const SelectObjectInfo& other) const
    {
        return m_segmentId != other.m_segmentId ||
            m_indexBody != other.m_indexBody ||
            m_primitiveId != other.m_primitiveId;
    }
};

class VisionScene : public QtVision::QtOpenGLSceneWidget
{
    Q_OBJECT
public:
    explicit VisionScene(QWidget* parent = nullptr);
    ~VisionScene() override;
    void createScene();
    void openModel();
    void addModel();
    void openFile(bool state);
    void cleanScene();
    void animated();
    bool event(QEvent* event) override;
    SceneSegment* rootSegment;
    SceneSegment* AxisSegment;
    SceneSegment* ObjectsSegment;
    void CreateLineAxis(MbCartPoint3D pIn1, MbCartPoint3D pIn2, Color clr);
    bool m_isZoomToFit = true;
    bool m_enableAnimated = false;
    int m_timerId = 0;
    void changeOrientation(Orientation orientation);
    void changeRenderMode(RenderMode mode);
    QColor highlightColor() const;
    QColor selectionColor() const;
    void PrepareDictionary();
    QString typePrimitive(InstSelectionItem* item);
    QMap<NodeKey, QString> m_mapKeyToString;
    QMap<MbeSpaceType, QString> m_mapSpaceTypeToString;
    void setFilter(bool bodyEnable);
    SelectionManagerPtr m_ptrSelectManager;
private:
    QVector<SceneSegment*> m_sceneSegments;
    QVector<SceneSegment*> m_sceneSolidSegments;
    QVector<SceneSegment*> m_sceneLoadedSegments;
    QVector<SceneSegment*> m_pSceneAxis;
    QVector<MbModel*> m_MbModels;
    BoxRep* m_pBoxRep;
    RenderObject m_box;
    MbPlacement3D m_place;
    SelectObjectInfo m_hoverInfo;
    QCursor bitmapCursor(int size) const;
    QPixmap paintPixmap(int size, QColor c) const;

    QCursor m_curEdge;
    QCursor m_curFace;
    QCursor m_curVertex;
    QCursor m_curPoint;

    void slotFinishBuildRep();
    void releaseRootSegment();
    void setGradientImage();
    
protected:
    void initializeGL() override;
    void paintGL() override;
    void timerEvent(QTimerEvent*);
    void signalItemSelectModified();

    void mouseMoveEvent(QMouseEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

    

public slots:
    void drawObjects(const QVector<Model>& models);
    void slotObjectHoverMove(std::shared_ptr<PickSelectionEvent> event);

    void slotHighlightColor(const QColor& clr);
    void slotSelectionColor(const QColor& clr);
    void slotModelColor(const QColor& clr);
signals:
    void updateScene();
    void signalReadyForFocus();
    void sendToSceneMessage(const QString& txt, ConsoleText::ResultType t = ConsoleText::ResultType::Standart);
    void sendToSceneMessageColor(const QString& txt, const QColor& color);

    void clearConsole();

private:
    Q_DISABLE_COPY(VisionScene)
};