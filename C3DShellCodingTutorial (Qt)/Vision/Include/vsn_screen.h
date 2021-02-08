#ifndef __VSN_SCREEN_H
#define __VSN_SCREEN_H

#include <string>
#include <list>

#include "vsn_object.h"
#include "vsn_global.h"

#include "vsn_rect.h"
#include "vsn_size.h"


VSN_BEGIN_NAMESPACE


class PlatformScreen;
class ScreenPrivate;
class Window;
class IntRect;
/* Screen */
class VSN_CLASS Screen : public Object
{
    VSN_OBJECT(Screen)
public:
    enum ScreenOrientation
    {
        PrimaryOrientation = 0x00000000,
        PortraitOrientation = 0x00000001,
        LandscapeOrientation = 0x00000002,
        InvertedPortraitOrientation = 0x00000004,
        InvertedLandscapeOrientation = 0x00000008
    };

public:
    ~Screen();
public:
    PlatformScreen* GetPlatformOpenGLContext() const;

    PlatformScreen* handle() const;
    std::string name() const;

    int depth() const;

    Size size() const;
    IntRect geometry() const;

    DoubleSize physicalSize() const;

    double physicalDotsPerInchX() const;
    double physicalDotsPerInchY() const;
    double physicalDotsPerInch() const;

    double logicalDotsPerInchX() const;
    double logicalDotsPerInchY() const;
    double logicalDotsPerInch() const;

    double devicePixelRatio() const;

    Size availableSize() const;
    IntRect availableGeometry() const;

    std::list<Screen*> virtualSiblings() const;

    Size virtualSize() const;
    IntRect virtualGeometry() const;

    Size availableVirtualSize() const;
    IntRect availableVirtualGeometry() const;

    ScreenOrientation primaryOrientation() const;
    ScreenOrientation orientation() const;
    ScreenOrientation nativeOrientation() const;

    uint8 orientationUpdateMask() const;
    void setOrientationUpdateMask(uint8 mask);

    int angleBetween(ScreenOrientation a, ScreenOrientation b) const;
    //    Transform transformBetween(Qt::ScreenOrientation a, Qt::ScreenOrientation b, const IntRect &target) const;
    IntRect mapBetween(ScreenOrientation a, ScreenOrientation b, const IntRect& rect) const;

    bool isPortrait(ScreenOrientation orientation) const;
    bool isLandscape(ScreenOrientation orientation) const;
    double refreshRate() const;
private:
    explicit Screen(PlatformScreen *screen);

private:
    OBVIOUS_PRIVATE_COPY(Screen)
    friend class PlatformScreen;
    friend class PlatformIntegration;
protected:
    VSN_DECLARE_EX_PRIVATE(Screen)
};

VSN_END_NAMESPACE

#endif // __VSN_SCREEN_H

