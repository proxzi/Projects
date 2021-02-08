////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс CoordLocationListener контролирует значение координат
             от устройств взаимодействия, например, 3D-мышь или клавиатура.
         \en CoordLocationListener class controls values of coordinates from
             interaction devices, for example, 3D-mouse and keyboard. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COORDLOCATIONLISTENER_H
#define __VSN_COORDLOCATIONLISTENER_H

#include "vsn_abscoordinatelistener.h"

VSN_BEGIN_NAMESPACE

class CoordLocationListenerPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс CoordLocationListener контролирует значение координат
               от устройств взаимодействия, например, 3D-мышь или клавиатура.
           \en CoordLocationListener class controls values of coordinates from
               interaction devices, for example, 3D-mouse and keyboard. \~
    \ingroup Vision_Interaction
*/
// ---
class CoordLocationListener : public AbsCoordinateListener
{
    VSN_OBJECT(CoordLocationListener)
    VSN_PROP_READ_WRITE_NOTIFY(loc, GetLocation, SetLocation, OnLocationModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit CoordLocationListener(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~CoordLocationListener();
public:
    /// \ru Вернуть координаты устройства. \en Returns device coordinates. \~
    int GetLocation() const;
public: // slots group
    /// \ru Установить координаты устройства. \en Sets device coordinates. \~
    VSN_SLOT(Public, SetLocation, void SetLocation(int loc))
public: // signals group
    VSN_SIGNAL(Public, OnLocationModified, void OnLocationModified(int loc), loc)
private:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(CoordLocationListener)
};


VSN_END_NAMESPACE

#endif // __VSN_COORDLOCATIONLISTENER_H
