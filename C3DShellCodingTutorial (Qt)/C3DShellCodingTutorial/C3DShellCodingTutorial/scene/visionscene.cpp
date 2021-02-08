#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <QContextMenuEvent>
#include <QFile>
#include <QFileDialog>

#include <plane_instance.h>
#include <op_swept_parameter.h>
#include <cur_line_segment.h>
#include <cur_contour.h>
#include <action_solid.h>
#include <solid.h>
#include <reference_item.h>
#include <point_frame.h>
#include <mesh.h>
#include <point3d.h>

#include <vsn_texture2d.h>
#include <vsn_segmentfeatures.h>
#include <vsn_pointgeometry.h>
#include <vsn_pen.h>

#include "visionscene.h"
#include "globaldef.h"
#include "storagelocation.h"



using ResultType = ConsoleText::ResultType;

static inline Image ConvertToImage(QImage&& image)
{
    /// convert to vision image
    Image::Format format = Image::Format::UINT32;
    image = image.convertToFormat(QImage::Format_RGBA8888);
    image = image.mirrored();
    image = image.rgbSwapped();

    Image result;
    result.Init(image.width(), image.height(), format, (const unsigned char*)image.bits());

    return result;
}

//-----------------------------------------------------------------------------
// 
// ---
VisionScene::VisionScene(QWidget* pParent)
    : QtVision::QtOpenGLSceneWidget(pParent)
    , m_pBoxRep(SceneGenerator::Instance()->CreateBox(1.5, 1.5, 1.5))
    , rootSegment(sceneContent()->GetRootSegment())
    , m_ptrSelectManager(std::make_shared<SelectionManager>())
{
    PrepareDictionary();
    m_curPoint = QCursor(QPixmap(":/res/scenecursor/point_cur.cur"));
    m_curEdge = QCursor(QPixmap(":/res/scenecursor/edge.cur"));
    m_curFace = QCursor(QPixmap(":/res/scenecursor/face.cur"));
    m_curVertex = QCursor(QPixmap(":/res/scenecursor/vertex.cur"));

    createScene();

    QtVision::CreateProcessesCameraControls(graphicsEngine()->GetTopEssence());

    //Object::Connect(graphicsEngine()->GetObjectPickSelection(), &ObjectPickSelection::ObjectHoverMove, this, &VisionScene::slotObjectHoverMove);
    graphicsEngine()->GetObjectPickSelection()->SetHoverEnabled(true);
    m_box = RenderObject(*m_pBoxRep);
}


VisionScene::~VisionScene()
{
    releaseRootSegment();
    VSN_DELETE_AND_NULL(m_pBoxRep);
}

bool VisionScene::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Wheel:
        if (hasFocus() == false)
        {
            setFocus();
        }
        break;
    default:
        break;
    }
    return QtOpenGLSceneWidget::event(event);
}




void VisionScene::paintGL()
{
    QtOpenGLSceneWidget::paintGL();
}

void VisionScene::setGradientImage() {
    makeCurrent();
    viewport()->DeleteBackgroundImage();

    QImage imageBackground = QImage(800, 480, QImage::Format_ARGB32_Premultiplied);
    imageBackground.fill(qRgba(0, 0, 0, 0));
    QPainter p(&imageBackground);
    QRect boundingRect(QPoint(0, 0), imageBackground.size());
    double radius = qMax(imageBackground.width(), imageBackground.height()) / 2.0;
    QRadialGradient radialGradient(QPointF(imageBackground.width() / 2.0, imageBackground.height() / 2.0), radius);
    radialGradient.setColorAt(0, QColor(213, 225, 241, 255));
    radialGradient.setColorAt(1, QColor(152, 165, 184, 255));

    p.fillRect(boundingRect, QBrush(radialGradient));
    viewport()->SetBackgroundColour(Color(0, 0, 0));
    viewport()->LoadBackgroundImage(ConvertToImage(imageBackground.copy()));
}


void VisionScene::initializeGL()
{
    // Установка настроек сцены
    QtOpenGLSceneWidget::initializeGL();
    GlobalFlags::SetVertexBufferObject(true);

    // Класс SelectionManager управляет списком выбранных элементов
    m_ptrSelectManager->SetSceneContent(sceneContent());
    m_ptrSelectManager->SetObjectPickSelection(objectPickSelection());
    m_ptrSelectManager->SetSelectionMode(SelectionManager::MultiSelection);
    m_ptrSelectManager->SetDynamicHighlighting(true);

    Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalStateModified, this, &QtOpenGLWidget::updateWidget);
    Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalItemSelectModified, this, &VisionScene::signalItemSelectModified);
    Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalItemsSelectModified, this, &VisionScene::signalItemSelectModified);

    setFilter(false);
    m_ptrSelectManager->SetDynamicHighlighting(true);

    viewport()->ClearColor();
    viewport()->SetGradientBackgroundColour(Color(213, 225, 241), Color(152, 165, 184));
    viewport()->GetCamera()->SetPosition(MbCartPoint3D(0, 0.0, 200.0));
    viewport()->GetCamera()->SetUpVector(MbVector3D(0.0, 1.0, 0.0));
    viewport()->GetCamera()->SetPositionTarget(MbCartPoint3D(0.0, 0.0, 0.0));
    viewport()->GetCamera()->RotateAboutTarget(X_AXIS, -0.5);
    viewport()->SetPixelCullingSize(0);

    mainLight()->SetDoubleSided(false);
    graphicsView()->SetSmoothTransition(true);
    graphicsView()->SetOrientationCamera(Orientation::IsoXYZ, true);
    // обновление сцены
    update();
}
//-----------------------------------------------------------------------------

void VisionScene::setFilter(bool bodyEnable)
{
    if (!bodyEnable) {
        m_ptrSelectManager->SetBodySelectionEnabled(false);

        m_ptrSelectManager->SetFaceSelectionEnabled(true);

        m_ptrSelectManager->SetEdgeSelectionEnabled(true);

        m_ptrSelectManager->SetVertexSelectionEnabled(true);
    }
    else {
        m_ptrSelectManager->SetBodySelectionEnabled(true);

        m_ptrSelectManager->SetFaceSelectionEnabled(false);

        m_ptrSelectManager->SetEdgeSelectionEnabled(false);

        m_ptrSelectManager->SetVertexSelectionEnabled(false);
    }
}


void VisionScene::releaseRootSegment()
{

    //if (!m_sceneSegments.empty())
    //{
    //    for (auto& segment : m_sceneSegments)
    //    {
    //        if (segment != nullptr) {
    //            ObjectsSegment->RemoveSegment(segment);
    //            VSN_DELETE_AND_NULL(segment);
    //        }
    //    }
    //    m_sceneSegments.clear();
    //}

    //if (!m_sceneSolidSegments.empty())
    //{
    //    for (auto& segment : m_sceneSolidSegments)
    //    {
    //        if (segment != nullptr) {
    //            ObjectsSegment->RemoveSegment(segment);
    //            VSN_DELETE_AND_NULL(segment);
    //        }
    //    }
    //    m_sceneSolidSegments.clear();
    //}

    std::list<SceneSegment*> seg = ObjectsSegment->GetSegments();
    for (auto& segment : seg) {
        if (segment != nullptr) {
            ObjectsSegment->RemoveSegment(segment);
            VSN_DELETE_AND_NULL(segment);
        }
    }
    //if (!m_sceneLoadedSegments.empty())
    //{
    //    for (auto& segment : m_sceneLoadedSegments)
    //    {
    //        if (segment != nullptr) {
    //            ObjectsSegment->RemoveSegment(segment);
    //            VSN_DELETE_AND_NULL(segment);
    //        }
    //    }
    //    m_sceneLoadedSegments.clear();
    //}
    if (!m_MbModels.empty()) {
        for (auto& model : m_MbModels)
        {
            if (model != nullptr) {
                ::DeleteItem(model);
            }

        }
    }
}
//-----------------------------------------------------------------------------
// 
// ---

void VisionScene::CreateLineAxis(MbCartPoint3D pIn1, MbCartPoint3D pIn2, Color clr) {
    GeomLineSegmentObject* line = new GeomLineSegmentObject;
    line->InitSegment(pIn1, pIn2);
    line->SetPen(Pen(1.0f, PenStyle::solid, clr));
    auto segment = new SceneSegment(new GeometryRep(line), AxisSegment);
    segment->SetIgnoreForPick(true);
}

void VisionScene::createScene()
{
    AxisSegment = new SceneSegment(rootSegment);
    ObjectsSegment = new SceneSegment(rootSegment);
    // ось x
    CreateLineAxis(MbCartPoint3D(0, 0, 0), MbCartPoint3D(50, 0, 0), Color(200, 50, 0));
    // ось y
    CreateLineAxis(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 50, 0), Color(50, 200, 0));
    // ось z
    CreateLineAxis(MbCartPoint3D(0, 0, 0), MbCartPoint3D(0, 0, 50), Color(0, 50, 200));

    viewport()->ZoomToFit(sceneContent()->GetBoundingBox());
}
//-----------------------------------------------------------------------------
// 
// ---


void asd(int* k) {

}


void VisionScene::drawObjects(const QVector<Model>& models)
{
    int a = 10;
    int* b = &a;
    asd(b);
    for (auto &model : models) {
        //auto ref = model.item->RefType();
        NodeKey key = NodeKey::GenerationKey();

        
        MbItem* item = model.item;
        Style style = model.style;
        /*item->SetColor(style.getColor);
        item->SetWidth(style.getWidth);
        item->SetStyle(style.getStyle);*/
        MbItem* drawItem = nullptr;
        if (item->Family() == st_Solid) { 
            MbSolid& solid = static_cast<MbSolid&>(*item);
            if (!solid.IsClosed() && (solid.GetFacesCount() == 1)) {
                AttrVector attrs;
                solid.GetAttributes(attrs, at_GeomAttribute); // Выдать атрибуты заданного типа. Get attributes of a given type. 
                if (attrs.size() == 1 && (attrs[0]->AttributeType() == at_GeomAttribute)) {
                    MbGeomAttribute* attr = (MbGeomAttribute*)attrs[0];
                    if (attr != nullptr) {
                        const MbSpaceItem* spaceItem = attr->GetSpaceItem();
                        if (spaceItem != NULL && spaceItem->IsA() == st_Solid) {
                            drawItem = ((MbSolid*)spaceItem)->CreateMesh(MbStepData(ist_SpaceStep, Math::visualSag), MbFormNote(), nullptr);
                        }
                    }
                }
            }
        }

        if (drawItem == nullptr)
            drawItem = item->CreateMesh(MbStepData(ist_SpaceStep, Math::visualSag), MbFormNote(), nullptr);

        if (drawItem != nullptr) {
            //drawModel.AddItem(*drawItem, geomItem.GetItemName()); // Добавить объект 
            MbMesh* pMesh = new MbMesh;
            AddRefItem(pMesh);
            drawItem->CalculateMesh(MbStepData(ist_SpaceStep, Math::visualSag), MbFormNote(), *pMesh);
            auto mathRep = SceneGenerator::Instance()->CreateMathRep(pMesh, ObjectsSegment, MathGeometry::Synchronous);
            auto segment = new SceneSegment(mathRep, key, ObjectsSegment);
            segment->AddFeature(new Features::DoubleSidedLighting());
        }
    }
    /*
    releaseRootSegment();
    if (models.empty())
    {
        update();
        return;
    }

    auto colors = [](const Model& model_) -> ColorRGB
    {
        return {
            getR(model_.style.getColor()),
            getG(model_.style.getColor()),
            getB(model_.style.getColor())
        };
    };

    for (auto& model : models)
    {
        auto refModel = model.item->RefType();
        switch (refModel)
        {
        case rt_SpaceItem:
        {
            auto item = static_cast<MbSpaceItem*>(model.item);

            QString str = m_mapSpaceTypeToString[item->IsA()];
            NodeKey key = NodeKey::GenerationKey();

            auto typeItem = item->Type();
            switch (typeItem)
            {
            case st_PointFrame:
            {
                auto pointFrame = static_cast<MbPointFrame*>(item);

                std::vector<MbCartPoint3D> points;
                size_t count = pointFrame->GetVerticesCount();
                for (size_t i = 0; i < count; ++i)
                {
                    points.push_back(pointFrame->GetVertex(i)->GetCartPoint());
                }

                auto [r, g, b] = colors(model);
                std::vector <VSN::Color> clr(points.size(), VSN::Color(r, g, b));

                auto pointsGeom = new PointGeometry();

                pointsGeom->AddPoints(points);
                pointsGeom->SetPointSize(model.style.getWidth() + 5);
                pointsGeom->AddColors(clr); 

                auto segment = new SceneSegment(new GeometryRep(pointsGeom), key, ObjectsSegment);
                segment->AddFeature(new Features::DoubleSidedLighting());
                m_sceneSegments.push_back(segment);
                break;
            }
            default:
            {
                MbMesh* pMesh = new MbMesh;
                AddRefItem(pMesh);
                item->CalculateMesh(MbStepData(ist_SpaceStep, Math::visualSag), MbFormNote(), *pMesh);
                auto mathRep = SceneGenerator::Instance()->CreateMathRep(pMesh, ObjectsSegment, MathGeometry::Synchronous);

                mathRep->GetMaterials();
                auto [r, g, b] = colors(model);

                auto segment = new SceneSegment(mathRep, key, ObjectsSegment);

                segment->AddFeature(new Features::DoubleSidedLighting());

                if (typeItem == st_Solid)
                {
                    segment->SetColorPresentationMaterial(Color(r, g, b));
                    m_sceneSolidSegments.push_back(segment);
                }
                else
                {
                    RenderObject* pObject3D = sceneContent()->GetContainer()->GetObjectById(key);
                    pObject3D->GetRenderState()->SetSpecialMaterial(new Material(Color(r, g, b)));
                    pObject3D->GetRenderState()->SetRenderingState(VSN::SpecialMaterialState);
                    m_sceneSegments.push_back(segment);
                }
                DeleteItem(pMesh);
                break;
            }
            }
            m_mapKeyToString[key] = str;
            break;
        }
        default:
            break;
        }
    }
    if(m_isZoomToFit) viewport()->ZoomToFit(ObjectsSegment->GetBoundingBox());
    update();
    */
}
//
void VisionScene::slotObjectHoverMove(std::shared_ptr<PickSelectionEvent> event)
{

}
//-----------------------------------------------------------------------------
// 
// ---


void VisionScene::changeOrientation(Orientation orientation)
{
    graphicsView()->SetOrientationCamera(orientation, false);
    update();
}

void VisionScene::changeRenderMode(RenderMode mode)
{
    graphicsView()->SetRenderMode(mode);
    update();
}


void VisionScene::openModel()
{
    openFile(true);
}

void VisionScene::addModel()
{
    openFile(false);
}

void VisionScene::cleanScene()
{
    releaseRootSegment();
    update();
}
void VisionScene::animated()
{
    switch (m_enableAnimated) {
        case true:
            killTimer(m_timerId);
            m_enableAnimated = false;
            break;
        case false:
            m_timerId = startTimer(1000.0 / 30.0); // 30 fps
            m_enableAnimated = true;
            break;
    }
}

void VisionScene::timerEvent(QTimerEvent*) 
{
    viewport()->GetCamera()->RotateAboutTarget(Y_AXIS,0.1);
    update();
}

void VisionScene::openFile(bool state)
{
    Q_ASSERT(ObjectsSegment != nullptr);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open models"), APP.modelsDir(), ("*.c3d"));

    if (!fileName.isEmpty())
    {
        if (state) releaseRootSegment();
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly))
            return;

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        QByteArray data = file.readAll();
        if (auto m_pModel = SceneGenerator::Instance()->LoadModel(data.constData(), data.length()))
        {
            Q_ASSERT(ObjectsSegment != nullptr);
            ProgressBuild* pProgressBuild = SceneGenerator::Instance()->CreateProgressBuild();

            auto segment = SceneGenerator::Instance()->CreateSceneSegment(m_pModel);
            ObjectsSegment->AddSegment(segment);
            Object::Connect(pProgressBuild, &ProgressBuild::BuildAllCompleted, this, &VisionScene::slotFinishBuildRep);
            ::AddRefItem(m_pModel);
            m_sceneLoadedSegments.push_back(segment);
            m_MbModels.push_back(m_pModel);
        }
        QApplication::restoreOverrideCursor();
    }
}

void VisionScene::slotFinishBuildRep()
{
    sceneContent()->GetContainer()->SetUseVertexBufferObjects(true);
    if(m_isZoomToFit) viewport()->ZoomToFit(ObjectsSegment->GetBoundingBox());
    update();
}

QColor VisionScene::highlightColor() const
{
    Color clr = m_ptrSelectManager->GetHighlightColor();
    return QColor(clr.GetRed(), clr.GetGreen(), clr.GetBlue()); 
    //return QColor(20, 230, 0);
}

QColor VisionScene::selectionColor() const
{
    Color clr = m_ptrSelectManager->GetSelectionColor();
    return QColor(clr.GetRed(), clr.GetGreen(), clr.GetBlue());
    //return QColor(240, 240, 0);
}

void VisionScene::slotHighlightColor(const QColor& clr)
{
    m_ptrSelectManager->SetHighlightColor(Color(clr.red(), clr.green(), clr.blue()));
}

void VisionScene::slotSelectionColor(const QColor& clr)
{
    m_ptrSelectManager->SetSelectionColor(Color(clr.red(), clr.green(), clr.blue()));
}

void VisionScene::slotModelColor(const QColor& clr)
{
    std::list<SelectionItem*> lstItem = m_ptrSelectManager->GetSelectionList();
    //int index = 0;
    for (std::list<SelectionItem*>::iterator it = lstItem.begin(); it != lstItem.end(); ++it)
    {
        if (InstSelectionItem* item = dynamic_cast<InstSelectionItem*>(*it))
        {
            auto segment = item->GetSceneSegment();
            std::list<SceneSegment*> seg = ObjectsSegment->GetSegments();
            for (auto& s : seg) {
                if (segment == s) {
                    s->SetColorPresentationMaterial(Color(clr.red(), clr.green(), clr.blue()));
                }
            }
        }
    }
}


QString VisionScene::typePrimitive(InstSelectionItem* item)
{
    QString strText("N");
    switch (item->GetType())
    {
    case ObjectType::Vertex: strText = QString("Vertex"); break;
    case ObjectType::Edge: strText = QString("Edge"); break;
    case ObjectType::Face: strText = QString("Face"); break;
    }
    return strText;
}

void VisionScene::signalItemSelectModified() {
    emit clearConsole();
    std::list<SelectionItem*> lstItem = m_ptrSelectManager->GetSelectionList();
    //int index = 0;
    for (std::list<SelectionItem*>::iterator it = lstItem.begin(); it != lstItem.end(); ++it)
    {
        if (InstSelectionItem* item = dynamic_cast<InstSelectionItem*>(*it))
        {
            String strKey = item->GetNodeKey().ToString();
            QString type = m_mapKeyToString[item->GetNodeKey()].isEmpty() ? "N" : m_mapKeyToString[item->GetNodeKey()];
            QString str = {"Type: " + typePrimitive(item) + ", NodeKey: " + QString::number(strKey.ToInt())
                + ", TypeFamily: " + type + ", Body Id: " + QString::number(item->GetIndexBody()) +
                ", Primitive Id: " + QString::number(item->GetPrimitiveId())};
            sendToSceneMessage(str, ResultType::Standart);
        }
    }
}

void VisionScene::mouseMoveEvent(QMouseEvent* event)
{
    QtVision::QtOpenGLSceneWidget::mouseMoveEvent(event);
    ObjectType type = ObjectType::None;
    if (SelectionItem* item = m_ptrSelectManager->GetHighlightItem())
        type = item->GetType();

    QCursor curCursor;
    switch (type)
    {
        case ObjectType::Vertex: curCursor = m_curVertex; break;
        case ObjectType::Edge:   curCursor = m_curEdge;   break;
        case ObjectType::Face:   curCursor = m_curFace;   break;
        default: curCursor = m_curPoint; break;
    }
    setCursor(curCursor);
}

void VisionScene::contextMenuEvent(QContextMenuEvent* event)
{
    if (event->modifiers() == Qt::CTRL)
    {
        QMenu menu(this);
        auto Action = menu.addAction(tr("Choice 1")/*, sender, SLOT()*/);
        menu.addSeparator();
        Action = menu.addAction(tr("Choice 2")/*, sender, SLOT()*/);
        menu.addAction(tr("Choice 3")/*, sender, SLOT()*/);
        menu.exec(event->globalPos());

        event->accept();
    }
}

QCursor VisionScene::bitmapCursor(int size) const
{
    return QCursor(paintPixmap(size, QColor(Qt::transparent)), size / 2, size / 2);
}

QPixmap VisionScene::paintPixmap(int size, QColor c) const
{
    //QString str = "SALAM";
    //QFontMetrics fm(font());
    //int height = fm.boundingRect("Q").height();
    //QPixmap result(size + fm.width(strX) + height * 2, size * 6);
    //result.fill(c);
    //QPainter p(&result);
    //p.setFont(font());
    //p.setPen(QPen(Qt::white, 2));
    //p.drawLine(0, 0, size, size);
    //p.drawLine(0, size, size, 0);

    //p.drawText(size * 2, size * 2, strX);
    //p.drawText(size * 2, size * 2 + height, strY);
    //p.drawText(size * 2, size * 2 + height * 2, strZ);
    //return result;
    return QPixmap();
}







void VisionScene::PrepareDictionary()
{
    m_mapSpaceTypeToString =
    {
        {st_Undefined, "st_Undefined"},
        {st_SpaceItem, "st_SpaceItem"},
        {st_Point3D, "st_Point3D"},
        {st_FreePoint3D, "st_FreePoint3D"},
        {st_Curve3D, "st_Curve3D"},
        {st_Line3D, "st_Line3D"},
        {st_LineSegment3D, "st_LineSegment3D"},
        {st_Arc3D, "st_Arc3D"},
        {st_Spiral, "st_Spiral"},
        {st_ConeSpiral, "st_ConeSpiral"},
        {st_CurveSpiral, "st_CurveSpiral"},
        {st_CrookedSpiral, "st_CrookedSpiral"},
        {st_PolyCurve3D, "st_PolyCurve3D"},
        {st_Polyline3D, "st_Polyline3D"},
        {st_Nurbs3D, "st_Nurbs3D"},
        {st_Bezier3D, "st_Bezier3D"},
        {st_Hermit3D, "st_Hermit3D"},
        {st_CubicSpline3D, "st_CubicSpline3D"},
        {st_PlaneCurve, "st_PlaneCurve"},
        {st_OffsetCurve3D, "st_OffsetCurve3D"},
        {st_TrimmedCurve3D, "st_TrimmedCurve3D"},
        {st_ReparamCurve3D, "st_ReparamCurve3D"},
        {st_BridgeCurve3D, "st_BridgeCurve3D"},
        {st_CharacterCurve3D, "st_CharacterCurve3D"},
        {st_ContourOnSurface, "st_ContourOnSurface"},
        {st_ContourOnPlane, "st_ContourOnPlane"},
        {st_SurfaceCurve, "st_SurfaceCurve"},
        {st_SilhouetteCurve, "st_SilhouetteCurve"},
        {st_SurfaceIntersectionCurve, "st_SurfaceIntersectionCurve"},
        {st_BSpline, "st_BSpline"},
        {st_Contour3D, "st_Contour3D"},
        {st_CoonsDerivative, "st_CoonsDerivative"},
        {st_FreeCurve3D, "st_FreeCurve3D"},
        {st_Surface, "st_Surface"},
        {st_ElementarySurface, "st_ElementarySurface"},
        {st_Plane, "st_Plane"},
        {st_ConeSurface, "st_ConeSurface"},
        {st_CylinderSurface, "st_CylinderSurface"},
        {st_SphereSurface, "st_SphereSurface"},
        {st_TorusSurface, "st_TorusSurface"},
        {st_SweptSurface, "st_SweptSurface"},
        {st_ExtrusionSurface , "st_ExtrusionSurface"},
        {st_RevolutionSurface, "st_RevolutionSurface"},
        {st_EvolutionSurface , "st_EvolutionSurface"},
        {st_ExactionSurface  , "st_ExactionSurface"},
        {st_ExpansionSurface , "st_ExpansionSurface"},
        {st_SpiralSurface    , "st_SpiralSurface"},
        {st_RuledSurface     , "st_RuledSurface"},
        {st_SectorSurface    , "st_SectorSurface"},
        {st_PolySurface      , "st_PolySurface"},
        {st_HermitSurface    , "st_HermitSurface"},
        {st_SplineSurface    , "st_SplineSurface"},
        {st_GridSurface      , "st_GridSurface"},
        {st_TriBezierSurface , "st_TriBezierSurface"},
        {st_TriSplineSurface , "st_TriSplineSurface"},
        {st_OffsetSurface      , "st_OffsetSurface"},
        {st_DeformedSurface    , "st_DeformedSurface"},
        {st_NurbsSurface       , "st_NurbsSurface"},
        {st_CornerSurface      , "st_CornerSurface"},
        {st_CoverSurface       , "st_CoverSurface"},
        {st_CoonsPatchSurface  , "st_CoonsPatchSurface"},
        {st_GregoryPatchSurface, "st_GregoryPatchSurface"},
        {st_LoftedSurface      , "st_LoftedSurface   "},
        {st_ElevationSurface   , "st_ElevationSurface"},
        {st_MeshSurface        , "st_MeshSurface"},
        {st_GregorySurface     , "st_GregorySurface"},
        {st_SmoothSurface      , "st_SmoothSurface"},
        {st_ChamferSurface     , "st_ChamferSurface"},
        {st_FilletSurface      , "st_FilletSurface"},
        {st_ChannelSurface     , "st_ChannelSurface"},
        {st_FullFilletSurface  , "st_FullFilletSurface"},
        {st_JoinSurface        , "st_JoinSurface"},
        {st_CurveBoundedSurface, "st_CurveBoundedSurface"},
        {st_BendedUnbendedSurface, "st_BendedUnbendedSurface"},
        {st_CylindricBendedSurface, "st_CylindricBendedSurface"},
        {st_CylindricUnbendedSurface, "st_CylindricUnbendedSurface"},
        {st_ConicBendedSurface, "st_ConicBendedSurface"},
        {st_ConicUnbendedSurface, "st_ConicUnbendedSurface"},
        {st_GregoryRibbonPatchSurface, "st_GregoryRibbonPatchSurface"},
        {st_ExplorationSurface, "st_ExplorationSurface"},
        {st_FreeSurface, "st_FreeSurface"},
        {st_Legend, "st_Legend"},
        {st_Marker, "st_Marker"},
        {st_Thread, "st_Thread"},
        {st_Symbol, "st_Symbol"},
        {st_PointsSymbol       , "st_PointsSymbol"},
        {st_Rough              , "st_Rough "},
        {st_Leader             , "st_Leader"},
        {st_Dimension3D        , "st_Dimension3D"},
        {st_LinearDimension3D  , "st_LinearDimension3D"},
        {st_DiameterDimension3D, "st_DiameterDimension3D"},
        {st_RadialDimension3D  , "st_RadialDimension3D"},
        {st_AngularDimension3D , "st_AngularDimension3D"},
        {st_FreeLegend         , "st_FreeLegend"},
        {st_Item          , " st_Item"},
        {st_AssistedItem  , " st_AssistedItem"},
        {st_PointFrame    , " st_PointFrame"},
        {st_WireFrame     , " st_WireFrame"},
        {st_Solid         , " st_Solid"},
        {st_Instance      , " st_Instance"},
        {st_Assembly      , " st_Assembly"},
        {st_Mesh          , " st_Mesh"},
        {st_SpaceInstance , " st_SpaceInstance"},
        {st_PlaneInstance , " st_PlaneInstance"},
        {st_Collection    , " st_Collection"},
        {st_FreeItem      , " st_FreeItem"}
    };
}