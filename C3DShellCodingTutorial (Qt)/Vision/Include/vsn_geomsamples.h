////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Примеры классов объектов, содержащих геометрические данные.
           \en Samples of classes that include geometric data. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GEOMSAMPLES_H
#define __VSN_GEOMSAMPLES_H

#include "vsn_meshgeometry.h"
#include "vsn_global.h"

class MbSolid;

VSN_BEGIN_NAMESPACE

//------------------------------------------------------------------------------
/** \brief \ru Полилиния.
           \en Polyline. \~
    \details \ru Множество точек, которые соединяются между собой ломаной.
             \en Set of points connected by a polyline. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS GeomPolylineObject : public WireframeGeometry
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    GeomPolylineObject(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~GeomPolylineObject();
public:
    /// \ru Выдать габаритный куб. \en Get a bounding box.
    virtual const MbCube& GetBoundingBox();
    /// \ru Определить, является ли объект пустым. \en Determine whether the object is empty.
    bool IsEmpty() const;
public:
    /// \ru Добавить массив точек для построения полилинии и вернуть идентификатор этой группы точек. \en Add a vector of points of polyline.
    uint AddPolyline(const std::vector<float>& data);
    /// \ru Добавить массив точек для построения полилинии и вернуть идентификатор этой группы точек. \en Add a vector of points of polyline.
    uint AddPolyline(const std::vector<MbCartPoint3D>& points);
    /// \ru Добавить массив точек для построения полилинии и вернуть идентификатор этой группы точек. \en Add a vector of points of polyline.
    uint AddPolyline(const std::vector<MbFloatPoint3D>& pointsList);
public:
    /// \ru Очистить содержимое полигона и сделать его пустым. \en Clear the object.
    virtual void Clear();
    /// \ru Оператор копирования. \en A copy operator.
//    GeomPolylineObject& operator = (const GeomPolylineObject& other);
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data. \~
    virtual void UpdateGeometry() override;
protected:
    /// \ru Отрисовать полилинию. \en Draw a polyline.
    virtual void OpenGLDraw(const RenderState& state) override;
    /// \ru Сконвертировать сетку в точки для рисования. \en NOT TRANSLATED.
    void MeshToPoints(const MbMesh& mesh);
    /// \ru Создать каркас. \en Create a wireframe.
    virtual void BuildWireframe();
};


//------------------------------------------------------------------------------
/** \brief \ru Отрезок.
           \en Line segment. \~
    \details \ru Линия, ограниченную конечными точками.
             \en A line limited by points. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS GeomLineSegmentObject : public GeomPolylineObject
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    GeomLineSegmentObject(Node* pParent = nullptr);
    /// \ru Конструктор по точкам. \en Constructor by points.
    GeomLineSegmentObject(const MbCartPoint3D& first, const MbCartPoint3D& second, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~GeomLineSegmentObject();
public:
    /// \ru Инициализация отрезка. \en Line segment initialization.
    void InitSegment(const MbCartPoint3D& first, const MbCartPoint3D& second);
private:
    /// \ru Создать каркас. \en Create a wireframe.
    virtual void BuildWireframe() override;
private:
    MbCartPoint3D m_pntFirst;  // первая точка отрезка
    MbCartPoint3D m_pntSecond; // вторая точка отрезка
};


//------------------------------------------------------------------------------
/** \brief \ru Окружность.
           \en A circle. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS GeomCircleObject : public GeomPolylineObject
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    GeomCircleObject(Node* pParent = nullptr);
    /// \ru Конструктор по радиусу. \en Constructor by radius.
    GeomCircleObject(double radius, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~GeomCircleObject();
public:
    /// \ru Задать отклонение для расчета полигона. \en Set the deviation for the calculating of the polygon.
    void SetDeviation(double sag);
private:
    /// \ru Создать каркас. \en Create a wireframe.
    virtual void BuildWireframe() override;
private:
    double m_radius; // радиус окружности
    double m_deviation; // коэффициент отклонения для расчета полигонов
};



VSN_END_NAMESPACE


#endif /* __VSN_GEOMSAMPLES_H */
