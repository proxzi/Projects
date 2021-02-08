////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс AbsCoordLocator конвертирует значение координат
             от устройств взаимодействия, например, мышь или клавиатуры.
         \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COORDLOCATOR_H
#define __VSN_COORDLOCATOR_H

#include <surface.h>

#include "vsn_object.h"
#include "vsn_point.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Viewport;
//------------------------------------------------------------------------------
/** \brief \ru Класс AbsCoordLocator конвертирует значение координат
               от устройств взаимодействия, например, мышь или клавиатуры.
           \en NO TRANSLATION. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS AbsCoordLocator : public Object
{
public:
    enum TypeLoc
    {
        tl_Model,
        tl_Surface,
        tl_Curve,
    };
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit AbsCoordLocator(Object* pParent = nullptr);
public:
    /// \ru Деструктор. \en Destructor. \~
    virtual ~AbsCoordLocator();
public:
    /// \ru Вернуть тип локатора. \en NO TRANSLATION.
    virtual TypeLoc GetTypeLocator() const = 0;
public:
    /// \ru Вернуть указатель на отрисовочный порт. \en NO TRANSLATION.
    Viewport* GetViewport() const;
    /// \ru Установить отрисовочный порт. \en NO TRANSLATION.
    void SetViewport(Viewport* pViewport);
    /// \ru Вернуть матрицу преобразования из локальных координат в координаты модели. \en NO TRANSLATION. \~
    const MbMatrix3D& GetTransform() const;
    /// \ru Установить матрицу преобразования из локальных координат в координаты модели. \en Set the transformation from local coordinates to model coordinates. \~
    void SetTransform(const MbMatrix3D& transform);
public:
    virtual bool ConvertLocalTo(const IntPoint& locPnt, MbCartPoint3D& pnt) = 0;
protected:
    void WorldPointToScreenPoint(const MbCartPoint3D& wPnt, MbCartPoint3D& lPnt) const;
    void ScreenPointToWorldPoint(const MbCartPoint3D& lPnt, MbCartPoint3D& wPnt) const;
    /// \ru конвертация точки из мира на экран. \en NO TRANSLATION. \~
    bool ProjectPoint(const MbCartPoint3D& pw, MbCartPoint3D& ps) const;
    bool UnProjectPoint(const MbCartPoint3D& ps, MbCartPoint3D& pw) const;
    void ConvertLogPosToParPlane(const MbCartPoint & logPos, const MbCartPoint3D & origin, MbCartPoint3D & point);
protected:
    Viewport* m_pViewport;
    MbCartPoint3D m_oldPoint; ///< \ru Координаты старой точки. \en NO TRANSLATION. \~
    MbMatrix3D m_matrix;      ///< \ru Mатрица преобразований из локальных координат в координаты модели. \en NO TRANSLATION. \~
private:
    VSN_DISABLE_COPY(AbsCoordLocator)
};

//------------------------------------------------------------------------------
/** \brief \ru Класс ModelCoordLocator конвертирует значение координат
               от устройств взаимодействия, например, мышь или клавиатуры 
               в модельные координаты в плоскости эрана.
           \en . \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS ModelCoordLocator : public AbsCoordLocator
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit ModelCoordLocator(Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~ModelCoordLocator();
public:
    /// \ru Вернуть тип локатора. \en NO TRANSLATION.
    virtual TypeLoc GetTypeLocator() const final { return tl_Model; }
public:
    virtual bool ConvertLocalTo(const IntPoint& locPnt, MbCartPoint3D& pnt) final;
private:
    VSN_DISABLE_COPY(ModelCoordLocator)
};

//------------------------------------------------------------------------------
/** \brief \ru Класс SurfaceScreenCoordLocator конвертирует значение координат
               от устройств взаимодействия, например, мышь или клавиатуры  
               в заданную поверхность.
           \en . \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS SurfaceScreenCoordLocator : public AbsCoordLocator
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit SurfaceScreenCoordLocator(Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~SurfaceScreenCoordLocator();
public:
    /// \ru Вернуть тип локатора. \en NO TRANSLATION.
    virtual TypeLoc GetTypeLocator() const final { return tl_Surface; }
public:
    /// \ru Вернуть поверхность. \en NO TRANSLATION.
    const MbSurface* GetSurface() const { return m_pBaseSurface; }
    /// \ru Установить поверхность в качестве опорного объекта. \en NO TRANSLATION.
    void SetSurface(const MbSurface* pSurface);
public:
    virtual bool ConvertLocalTo(const IntPoint& locPnt, MbCartPoint3D& pnt) final;
protected:
    const MbSurface* m_pBaseSurface;
private:
    VSN_DISABLE_COPY(SurfaceScreenCoordLocator)
};

//------------------------------------------------------------------------------
/** \brief \ru Класс SurfaceScreenCoordLocator конвертирует значение координат
               от устройств взаимодействия, например, мышь или клавиатуры
               в заданную кривую.
           \en . \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS CurveScreenCoordLocator : public AbsCoordLocator
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit CurveScreenCoordLocator(Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~CurveScreenCoordLocator();
public:
    /// \ru Вернуть тип локатора. \en NO TRANSLATION.
    virtual TypeLoc GetTypeLocator() const final { return tl_Curve; }
public:
    /// \ru Вернуть поверхность. \en NO TRANSLATION.
    const MbCurve3D* GetpCurve() const { return m_pBaseCurve; }
    /// \ru Установить поверхность в качестве опорного объекта. \en NO TRANSLATION.
    void SetCurve(const MbCurve3D* pCurve);
public:
    virtual bool ConvertLocalTo(const IntPoint& locPnt, MbCartPoint3D& pnt) final;
protected:
    const MbCurve3D* m_pBaseCurve;
private:
    VSN_DISABLE_COPY(CurveScreenCoordLocator)
};


VSN_END_NAMESPACE

#endif // __VSN_COORDLOCATOR_H
