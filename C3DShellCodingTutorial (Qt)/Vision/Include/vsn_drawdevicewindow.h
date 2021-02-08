#ifndef __VSN_DRAWDEVICEWINDOW_H
#define __VSN_DRAWDEVICEWINDOW_H

#include "vsn_drawdevice.h"
#include "vsn_region.h"
#include "vsn_window.h"

VSN_BEGIN_NAMESPACE

class DrawDeviceWindowPrivate;
/* DrawDeviceWindow */
class VSN_CLASS DrawDeviceWindow : public Window, public DrawDevice
{
    VSN_OBJECT(DrawDeviceWindow)
public:
    void UpdateWindowRect(const IntRect& rect);
    void UpdateWindowRegion(const Region& region);
public:
    VSN_SLOT(Public, UpdateWindow, void UpdateWindow());
protected:
    virtual int GetMetric(DrawDeviceMetric metric) const override;
    DrawDeviceWindow(DrawDeviceWindowPrivate& dd, Window* pParent);
protected:
    virtual bool OnEvent(ProcessEvent* pEvent) override;
    virtual void OnExposeEvent(ExposeEvent* pEvent) override;
    virtual void OnDrawEvent(DrawEvent* pEvent);
private:
    virtual DrawEngine* GetDrawEngine() const override;
    VSN_DISABLE_COPY(DrawDeviceWindow)
    VSN_DECLARE_EX_PRIVATE(DrawDeviceWindow)
};

VSN_END_NAMESPACE

#endif // __VSN_DRAWDEVICEWINDOW_H
