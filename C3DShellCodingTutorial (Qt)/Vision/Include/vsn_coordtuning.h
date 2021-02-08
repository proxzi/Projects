////////////////////////////////////////////////////////////////////////////////
/**
  \file
    \brief \ru Класс CoordTuning хранит настройки для указанного списка координат.
           \en CoordTuning class stores the settings for the specified coordinate list. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_COORDTUNING_H
#define __VSN_COORDTUNING_H

#include "vsn_node.h"

VSN_BEGIN_NAMESPACE

class CoordTuningPrivate;
//------------------------------------------------------------------------------
/** \brief   \ru Класс CoordTuning хранит настройки для указанного списка координат.
             \en CoordTuning class stores the settings for the specified coordinate list. \~
    \details \ru CoordTuning cохраняет величину мертвой зоны связанную с этими координатами и определяет включено ли сглаживание. \n
             \en CoordTuning class saves a value of dead band linked with these coordinates and defines if antialiasing is enabled. \n \~
    \ingroup Vision_Interaction
*/
// ---
class CoordTuning : public Node
{
    VSN_OBJECT(CoordTuning)
    VSN_PROP_READ_WRITE_NOTIFY(deadband, GetDeadband, SetDeadband, OnDeadbandModified)
    VSN_PROP_READ_WRITE_NOTIFY(coords, GetCoords, SetCoords, OnCoordsModified)
    VSN_PROP_READ_WRITE_NOTIFY(smooth, IsSmoothEnabled, SetSmoothEnabled, OnSmoothModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit CoordTuning(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~CoordTuning();
public:
    /// \ru Вернуть радиус мертвой зоны. \en Returns dead band radius. \~
    float GetDeadband() const;
    /// \ru Вернуть текущий список внутренних координат, к которым применяются эти настройки. \en Returns the current list of internal coordinates these settings are applied to. \~
    std::vector<int> GetCoords() const;
    /// \ru Вернуть true, если сглаживание включено. \en Returns true if antialiasing is enabled. \~
    bool IsSmoothEnabled() const;
public: // slots group
    /// \ru Установить радиус мертвой зоны. \en Sets dead band radius. \~
    VSN_SLOT(Public, SetDeadband, void SetDeadband(float deadband))
    /// \ru Установить текущие координаты. \en Sets the current coordinates. \~
    VSN_SLOT(Public, SetCoords, void SetCoords(const std::vector<int>& coords))
    /// \ru Установить текущее состояние сглаживания координат. \en Sets the current state of coordinate antialiasing. \~
    VSN_SLOT(Public, SetSmoothEnabled, void SetSmoothEnabled(bool enabled))
public: // signals group
    /// \ru Этот сигнал будет сгенерирован, когда изменится мертвая зона. \en The signal will be generated when modifying dead band. \~
    VSN_SIGNAL(Public, OnDeadbandModified, void OnDeadbandModified(float deadband), deadband)
    /// \ru Этот сигнал буде сгенерирован, когда изменятся координаты устройства. \en The signal will be generated when modifying device coordinates. \~
    VSN_SIGNAL(Public, OnCoordsModified,   void OnCoordsModified(const std::vector<int>& coords), coords)
    /// \ru Этот сигнал буде сгенерирован, когда изменится признак сглаживания. \en The signal will be generated when modifying antialiasing flag. \~
    VSN_SIGNAL(Public, OnSmoothModified,   void OnSmoothModified(bool smooth), smooth)
private:
    NCreatedModificationBasicPtr  CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(CoordTuning);
};


VSN_END_NAMESPACE

#endif // __VSN_COORDTUNING_H
