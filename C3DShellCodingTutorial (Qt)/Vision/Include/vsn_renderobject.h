////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс RenderObject содержит GeometryRep + bounding box.
         \en RenderObject class contains GeometryRep + bounding box. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_RENDEROBJECT_H
#define __VSN_RENDEROBJECT_H

#include <mb_cube.h>
#include <mb_matrix3d.h>    

#include "vsn_mutex.h"
#include "vsn_node.h"
#include "vsn_renderstate.h"
#include "vsn_namespace.h"
#include "vsn_globalflags.h"
#include "vsn_geometryrep.h"

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class Camera;
class Octant;
class Viewport;
class CuttingUtil;
//------------------------------------------------------------------------------
/** \brief   \ru Класс RenderObject содержит GeometryRep + bounding box.
             \en RenderObject class contains GeometryRep + bounding box. \~
    \details \ru Класс RenderObject содержит GeometryRep + bounding box. \n
             \en RenderObject class contains GeometryRep + bounding box. \n \~
    \ingroup NO GROUP
*/
// ---
class VSN_CLASS RenderObject
{
public:
    // состояние видимости 
    enum VisibleState
    {
        Absolute_Visible = 300,  /// абсолютно видимый
        Relative_Visible = 301,  /// относительно видимый
        Absolute_Hide = 302,  /// абсолютно невидимый
        Absolute_Visible_Pixel_Culling = 304, /// абсолютно видимый
        Absolute_Hide_Pixel_Culling = 308, /// абсолютно невидимый
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    RenderObject();
    /// \ru Специальный конструктор с инициализацией геометрии. \en Special constructor with geometry initialization. \~
    explicit RenderObject(WireframeGeometry*);
    /// \ru Специальный конструктор с инициализацией геометрии и уникальным идентификатором. \en Special constructor with geometry initialization and the unique identifier. \~
    RenderObject(WireframeGeometry*, NodeKey id);
    /// \ru Специальный конструктор с инициализацией геометрического представления. \en Special constructor with initialization of geometry representation. \~
    explicit RenderObject(const GeometryRep&);
    /// \ru Специальный конструктор с инициализацией геометрического представления и идентификатором. \en Special constructor with initialization of geometry representation and the unique identifier. \~
    RenderObject(const GeometryRep&, NodeKey id);
    /// \ru Конструктор копирования. \en Copy constructor. \~
    RenderObject(const RenderObject& other);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~RenderObject();
public:
    /// \ru Получить имя объекта. \en Returns name.
    inline String GetObjectName() const { return m_objectName; }
    /// \ru Установить имя объекту. \en Sets name.
    inline void SetObjectName(const String& name) { m_objectName = name; }

    /// \ru Вернуть ключ, идентифицирующий экземпляр Node. \en Returns key identifing Node instance. \~
    NodeKey GetUniqueKey() const { return m_key; }
    /// \ru Прозрачен ли весь объект. \en Checks if the whole object is transparent. \~
    bool IsTransparent() const;
    /// \ru Есть ли хотя бы одна прозрачная часть объекта. \en Checks if transparent parts of object exist (at least one part). \~
    bool IsExistTransparentMaterials() const;

    /// \ru Является ли объект пустым. \en Checks if object is empty. \~
    bool IsEmpty() const;
    /// \ru Выбран ли объект. \en Checks if object is selected. \~
    bool IsSelected() const;

    /// \ru Вернуть геометрическую часть по индексу. \en Returns geometry part by index. \~
    WireframeGeometry* GetGeometryByIndex(size_t index) const;
    /// \ru Получить геометрическое представление объекта. \en Returns geometry representation of the object. \~
    const GeometryRep & GetRepresentation() const;

    /// \ru Получить копию габаритного куба объекта. \en Returns copy of object bounding box. \~
    MbCube GetBoundingBox();

    /// \ru Является ли габаритный куб действительным. \en Checks if bounding box is valid. \~
    bool IsBoundingBoxValid() const;

    /// \ru Вернуть абсолютную матрицу трансформации. \en Returns absolute transformation matrix. \~
    const MbMatrix3D & GetMatrix() const;
    /// \ru Вернуть полную матрицу с учетом абсолютной матрицы объекта. \en Returns full matrix with given absolute matrix of the object.
    const MbMatrix3D& GetFullMatrix() const;

    /** \brief \ru Вернуть режим отрисовки объекта.
                \en Returns object rendering mode. \~    
    \details \ru Вернуть режим отрисовки объекта. Режим может быть: GL_POINT, GL_LINE или GL_FILL. \n
                \en Returns object rendering mode. It can be GL_POINT, GL_LINE or GL_FILL. \n \~
    */
    uint GetPolygonMode() const;

    /** \brief \ru Установить режим отображения полигонов в выбранном стиле.
               \en Sets polygon mapping mode in selected style. \~
       \details \ru Установить режим отображения полигонов в выбранном стиле. 
                    Режим сетки может быть: GL_FRONT_AND_BACK, GL_FRONT или GL_BACK.
                    Стиль может быть: GL_POINT, GL_LINE или GL_FILL. \n
                \en Sets polygon mapping mode in selected style.
                    Mesh mode can be GL_FRONT_AND_BACK, GL_FRONT or GL_BACK. 
                    The style can be GL_POINT, GL_LINE or GL_FILL. \n \~
    */
    void SetPolygonMode(uint face, uint mode);

    /// \ru Вернуть указатель на состояние отрисовки. \en Returns pointer to rendering state. \~
    RenderState* GetRenderState();
    /// \ru Установить состояние отрисовки для этого объекта. \en Sets rendering state for this object. \~
    void SetStateRender(const RenderState& renderState);

    /// \ru Является ли объект видимым. \en Checks if object is visible. \~
    bool IsVisible() const;
    /// \ru Установить видимость объекту. \en Sets visibility for object. \~
    void SetVisible( bool bVisible );

    /// \ru Вернуть состояние видимости объекта. \en Returns object visibility state. \~
    VisibleState GetVisibleState() const;
    /// \ru Установить состояние видимости объекта. \en Sets object visibility state.
    bool SetStateVisible(VisibleState state);

    /// \ru Является ли видимым объект, полученный по индексу. \en Checks if object received by index is visible.
    bool IsGeomVisibleByIndex(size_t index) const;
    /// \ru Установить видимость геометрии внутри этого объекта по индексу. \en Sets geometry visibility inside the object by index.
    void SetVisibleGeomByIndex(size_t index, bool bVisible);

    /// \ru Получить количество граней. \en Returns face count.
    size_t GetFaceCount() const;
    /// \ru Получить количество вершин. \en Returns vertex count.
    size_t GetVertexCount() const;

    /// \ru Вернуть количество материалов. \en Returns material count.
    size_t GetMaterialCount() const;
    /// \ru Вернуть массив материалов. \en Returns material array.
    std::set<Material *> GetMaterials() const;

    /// \ru Вернуть значение LOD по умолчанию. \en Returns the default value of LOD.
    int GetDefaultLevelOfDetail() const;
    /// \ru Установить значение LOD по умолчанию этому объекту. \en Sets the default value of LOD for this object.
    void SetDefaultLevelOfDetail(int value);

    /// \ru Вернуть представление объекта. \en Returns object representation.
    const GeometryRep* GetRepObject() const;
    /// \ru Вернуть количество тел в объекте. \en Returns body count in the object.
    size_t GetGeometryCount() const;

    /// \ru Вернуть глобальное значение уровня детализации. \en Returns the global value of LOD.
    static int GetGlobalDefaultLevelOfDetail();
    /// \ru Установить глобальное значение уровня детализации. \en Sets the global value of LOD.
    static void SetGlobalDefaultLevelOfDetail( int value );

    void     SetRenderLayer(uint32_t);
    uint32_t GetRenderLayer() const;

    void     SetNoScalable(bool);
    bool     GetNoScalable() const;

    void     SetScreenOnly(bool value);
    bool     GetScreenOnly();

    void     SetDisableForPick(bool value);
    bool     IsDisabledForPick();

    void     SetDoubleSidedLighting(bool value);
    bool     IsDoubleSidedLighting() const;
public:
    /// \ru Добавить новую геометрию. \en Adds new geometry.
    bool AddGeometry(WireframeGeometry* pGeometry);
    /// \ru Удалить пустую геометрию. \en Deletes empty geometry.
    void DeleteEmptyGeometry();
    /// \ru Инвертировать нормали геометрии. \en Reverses geometry normals.
    void ReverseNormalsOfGeometry();

    /// \ru Преобразовать объект по параметрам. \en Transforms object by parameters.
    RenderObject& Translate( double px, double py, double pz );
    /// \ru Преобразовать объект по вектору. \en Transforms object by vector.
    RenderObject& Translate( const MbVector3D& );
    /// \ru Преобразовать объект по указанной матрице. \en Transforms object by specified matrix.
    RenderObject& MultMatrix( const MbMatrix3D& );
    /// \ru Установить абсолютную матрицу по матрице. \en Sets absolute matrix by specified matrix.
    RenderObject& SetMatrix( const MbMatrix3D& );

    /// \ru Сбросить абсолютную матрицу до единичной. \en Resets absolute matrix to identity matrix.
    RenderObject & ResetMatrixToIdentityMatrix();

    /// \ru Использовать полную матрицу с учетом абсолютной матрицы объекта. \en Uses full matrix with given absolute matrix of the object.
    void SetUseFullMatrix( bool bUse );
    /// \ru Установить полную матрицу с учетом абсолютной матрицы объекта. \en Sets full matrix with given absolute matrix of the object.
    void SetFullMatrix(const MbMatrix3D& mx);
    /// \ru Сбросить полную матрицу до единичной. \en Resets full matrix to identity matrix.
    void ResetFullMatrixToIdentityMatrix();

    /// \ru Установить признак выбранного объекта в геометрии. \en Sets flag of selected object in geometry.
    void SetSelect( bool primitive );
    /// \ru Снять выбор объекта в геометрии. \en Unselects object within geometry.
    void Unselect();

    /// \ru Установить идентификатор объекту. \en Sets identifier for object.
    void SetUniqueKey(NodeKey id);

    /// \ru Установить признак использования VBO. \en Sets flag of Vertex Buffer Object (VBO) usage.
    void SetUseVertexBufferObjects(bool usage);
public:
    /// \ru Отрисовать представления этого объекта в заданном режиме. \en Renders representation of the object in set mode.
    void OGLDrawGivenMode(RenderMode renderingMode = rm_Shaded, bool useLod = false, const Viewport* pView = nullptr, CuttingUtil* cuttingTool = nullptr);
    /// \ru Отрисовка тела в режиме выбора. \en Renders body in selection mode.
    void OGLDrawBodySelectionMode();
    /// \ru Отрисовать примитивы объекта в режиме выбора по идентификатору тела и вернуть индекс тела. \en Renders object primitives in selection mode by body identifier and return body index.
    size_t OGLDrawPrimitiveSelectionMode(uint idBody);
    /// \ru Оператор копирования. \en Copy operator.
    RenderObject & operator = (const RenderObject &);

    std::list<WireframeGeometry*>::const_iterator GeometryBegin() const;
    std::list<WireframeGeometry*>::const_iterator GeometryEnd() const;
private:
    // установить свойства визуализации объекта
    void SetVisualisationMode();
    // подсчитать габаритник всей геометрии и преобразовать его в матрицу объекта
    void CalcBoundingBox();
    // очистить этот объект
    void Clear();
    // подсчитать и выбрать уровень детализации для этого объекта
    int CalcChoseLevelOfDetail(const MbCube&, const Viewport*, bool);
    // подсчитать и выбрать уровень детализации для этого объекта c учетом ориентированного его габарита
    int CalcChoseLevelOfDetailOrientedBoundBox(const MbCube&, const Viewport*, bool);
private:
    GeometryRep m_representation;         /// 3D представление объекта
    MbCube m_boundingBox;                 /// габаритник представления
    MbMatrix3D m_absoluteMatrix;          /// абсолютная матрица объекта
    MbMatrix3D m_fullMatrix;              /// суммарная матрица (m_absoluteMatrix * pView->GetCamera()->GetModelViewMatrix())
    bool m_bUsefullMatrix;                /// признак использовать полную матрицу 
    bool m_bIsValidBoundingBox;           /// признак правильного габаритника
    RenderState m_renderState;            /// состояние визуализации объекта
    bool m_bIsVisible;                    /// признак видимости объекта
    unsigned char m_colorId[4];           /// цветовой идентификатор объекта
    int m_defaultLODetail;                /// значение уровня детализации по умолчанию
    VisibleState m_visibleState;          /// флаг видимости объекта
    std::vector<bool> m_visibleGeomFlags; /// массив признаков видимости объекта
    String m_objectName;
    NodeKey m_key;
    uint32_t m_layer = 0;
    bool m_noScalable = false;
    bool m_screenOnly = false;
    bool m_disableForPick = false;
    bool m_doubleSideLighting = false;

    static Mutex m_mutex;             /// Mutex
    static int g_defaultLevelDetail;  /// глобальное значение уровня детализации по умолчанию
private:
    friend class RenderContainerPrivate;
    friend class RenderContainer;
};


VSN_END_NAMESPACE

#endif /* __VSN_RENDEROBJECT_H */
