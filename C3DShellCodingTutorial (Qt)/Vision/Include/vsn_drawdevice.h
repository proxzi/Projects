#ifndef __VSN_DRAWDEVICE_H
#define __VSN_DRAWDEVICE_H

#include "vsn_rect.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE


class DrawEngine;
/* DrawDevice */
class VSN_CLASS DrawDevice
{
public:
    enum DrawDeviceMetric 
    {
        PdmWidth = 1,
        PdmHeight,
        PdmWidthMM,
        PdmHeightMM,
        PdmNumColors,
        PdmDepth,
        PdmDpiX,
        PdmDpiY,
        PdmPhysicalDpiX,
        PdmPhysicalDpiY,
        PdmDevicePixelRatio,
        PdmDevicePixelRatioScaled
    };

    virtual ~DrawDevice();
public:
    virtual int GetDeviceType() const;
    bool IsDrawActive() const;
    virtual DrawEngine* GetDrawEngine() const = 0;
public:
    int GetWidth() const;
    int GetHeight() const;
    int GetWidthMM() const;
    int GetHeightMM() const;
    int GetLogicalDpiX() const;
    int GetLogicalDpiY() const;
    int GetPhysicalDpiX() const;
    int GetPhysicalDpiY() const;
    int GetDevicePixelRatio() const;
    double GetDevicePixelRatioD() const;
    int GetColorCount() const;
    int GetDepth() const;
    static double GetDevicePixelRatioDoubleDoubleScale();
protected:
    DrawDevice();
    virtual int GetMetric(DrawDeviceMetric metric) const;
    uint m_draws;
private:
    VSN_DISABLE_COPY(DrawDevice);
    friend VSN_FUNC_EX int GetDrawDeviceMetric(const DrawDevice* device, DrawDeviceMetric metric);
};

VSN_END_NAMESPACE

#endif // __VSN_DRAWDEVICE_H
