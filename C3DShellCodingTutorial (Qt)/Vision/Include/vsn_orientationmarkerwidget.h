////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ORIENTATIONMARKERWIDGET_H
#define __VSN_ORIENTATIONMARKERWIDGET_H

#include "vsn_widget3dbasic.h"
#include "vsn_variant.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE

enum MarkerDataRole
{
    dt_OriginRadius = dr_User + 1,
    dt_MaterialKey,
    dt_RadiusAxis,
    dt_HeightAxis,
    dt_RadiusArrow,
    dt_heightArrow,
    dt_symbol,
};

class OrientationMarkerWidget;
class VisionNativeMarkerModelPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \details \ru NOT TRANSLATED.
             \en NOT TRANSLATED. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS MarkerWidgetItem
{
public:
    enum ItemType { it_Type = 0, it_Origin, it_Axis, it_Arrow, it_Symbol, it_User = 1000 };
    explicit MarkerWidgetItem(int type = it_Type);
    virtual ~MarkerWidgetItem();
public:
    inline int GetItemType() const { return GetData(dt_Type).GetInt();  }
    inline void SetItemType(int type);

    inline NodeKey GetNodeKey() const { return GetData(dt_NodeKey).GetNodeKey(); }
    inline void SetNodeKey(const NodeKey& nodeKey);

    inline NodeKey GetMaterialKey() const { return GetData(dt_MaterialKey).GetNodeKey(); }
    inline void SetMaterialKey(const NodeKey& materialKey);

    inline Color GetColor() const { return GetData(dt_Color).GetColor(); }
    inline void SetColor(const Color& color);

    virtual Variant GetData(int role) const;
    virtual void SetData(int role, const Variant& value);
public:
    NodeKey m_nodeKey;
    std::map<int, Variant> m_values;
    OrientationMarkerWidget* m_pWidget;
};

inline void MarkerWidgetItem::SetItemType(int type)
{ SetData(dt_Type, type); }
inline void MarkerWidgetItem::SetNodeKey(const NodeKey& nodeKey)
{ SetData(dt_NodeKey, nodeKey); }
inline void MarkerWidgetItem::SetMaterialKey(const NodeKey& materialKey)
{ SetData(dt_MaterialKey, materialKey); }
inline void MarkerWidgetItem::SetColor(const Color& color)
{ SetData(dt_Color, color); }

//----------------------------------------------------------------------------
//
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \details \ru NOT TRANSLATED.
             \en NOT TRANSLATED. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS VisionNativeMarkerModel : public AbstractRenderModel
{
    VSN_OBJECT(VisionNativeMarkerModel);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit VisionNativeMarkerModel(OrientationMarkerWidget* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~VisionNativeMarkerModel();
public:
    MarkerWidgetItem* GetItem(const NodeKey& key) const;
    void AddItem(MarkerWidgetItem* pItem);
    void Clear();
    void ItemModified(MarkerWidgetItem* item);
public:
    /// \ru Построение модели. \en NOT TRANSLATED.
    virtual void BuildModel() final;
private:
    /// \ru Построение модели маркера. \\en NOT TRANSLATED.
    void BuildMarkerModel();
    void UpdateMaterials();
    RenderObject BuildOriginMarker(MarkerWidgetItem& item);
    RenderObject BuildAxisMarker(MarkerWidgetItem& item);
    RenderObject BuildArrowMarker(MarkerWidgetItem& item);
    /// \ru Создать геометрическое представление символов. \en NOT TRANSLATED.
    RenderObject BuildAxisSymbol(MarkerWidgetItem& item, char symbol);
    Material* GetMaterialByKey(const NodeKey& key) const;
protected:
    Color m_colorO;
    Color m_colorX;
    Color m_colorY;
    Color m_colorZ;

    Material* m_pMaterialO;
    Material* m_pMaterialX;
    Material* m_pMaterialY;
    Material* m_pMaterialZ;
    std::vector<MarkerWidgetItem*> m_items;
private:
    VSN_DECLARE_EX_PRIVATE(VisionNativeMarkerModel);
    VSN_DISABLE_COPY(VisionNativeMarkerModel);
};


class OrientationMarkerWidgetPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \details \ru NOT TRANSLATED.
             \en NOT TRANSLATED. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS OrientationMarkerWidget : public Widget3DBasic
{
    VSN_OBJECT(OrientationMarkerWidget)
    VSN_ENUM(Corner)
    VSN_PROP_READ_WRITE_NOTIFY(corner, GetCorner, SetCorner, CornerModified)
public:
    /// \ru перечисление расположения маркера ориентации. \en NOT TRANSLATED.
    enum Corner
    {
        c_TopLeft     = 0x00000, ///< \ru верхний левый угол. \en NOT TRANSLATED.
        c_TopRight    = 0x00001, ///< \ru верхний правый угол. \en NOT TRANSLATED.
        c_BottomLeft  = 0x00002, ///< \ru нижний левый угол. \en NOT TRANSLATED.
        c_BottomRight = 0x00003  ///< \ru нижний правый угол. \en NOT TRANSLATED.
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit OrientationMarkerWidget(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~OrientationMarkerWidget();
public:
    /// \ru Установить модель для представления виджета. \en NOT TRANSLATED.
    virtual void SetModel(AbstractRenderModel* model) override;
public:
    /// \ru Вернуть текущее расположение маркера. \en NOT TRANSLATED.
    Corner GetCorner() const;
    /// \ru Вернуть габаритный куб всех видимых объектов. \en NOT TRANSLATED.
    MbCube GetBoundingBox();
public:
    /// \ru Установить текущее расположение маркера. \en NOT TRANSLATED.
    VSN_SLOT(Public, SetCorner, void SetCorner(Corner corner))
public:
    VSN_SIGNAL(Public, CornerModified, void CornerModified(Corner corner), corner)
public:
    /// \ru Отрисовать геометрическое представление виджета. \en NOT TRANSLATED.
    void Render();
private:
    VSN_DECLARE_EX_PRIVATE(OrientationMarkerWidget);
    VSN_DISABLE_COPY(OrientationMarkerWidget);
    VSN_SLOT(Private, vsn_OnProcessed, void vsn_OnProcessed(float dValue))
};

VSN_END_NAMESPACE


#endif /* __VSN_ORIENTATIONMARKERWIDGET_H */
