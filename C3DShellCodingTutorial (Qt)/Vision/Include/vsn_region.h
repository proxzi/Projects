#ifndef __VSN_REGION_H
#define __VSN_REGION_H

#include "vsn_atomic.h"
#include "vsn_rect.h"
#include "vsn_point.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

struct RegionPrivate;
struct RegionData;
/* Region */
class VSN_CLASS Region
{
public:
    enum RegionType { Rectangle, Ellipse };
public:
    Region();
    Region(int x, int y, int w, int h, RegionType t = Rectangle);
    Region(const IntRect& r, RegionType t = Rectangle);
    Region(const Region& region);
    Region(Region&& other);
    ~Region();
public:
    Region& operator=(const Region& other);
    inline void Swap(Region &other) { std::swap(d, other.d); }
    bool IsEmpty() const;
    bool IsNull() const;

    bool PntInRegion(const IntPoint& pnt) const;
    bool RectInRegion(const IntRect& rc) const;

    void Offset(int dx, int dy);
    inline void Offset(const IntPoint &p) { Offset(p.GetX(), p.GetY()); }
    Region Offseted(int dx, int dy) const;
    inline Region Offseted(const IntPoint &p) const { return Offseted(p.GetX(), p.GetY()); }

    Region United(const Region& reg) const;
    Region United(const IntRect& rc) const;
    Region Intersected(const Region& reg) const;
    Region Intersected(const IntRect& rc) const;
    Region Subtracted(const Region& reg) const;
    Region Xored(const Region& reg) const;

    bool Intersects(const Region& reg) const;
    bool Intersects(const IntRect& rc) const;

    IntRect GetBoundingRect() const;
    std::vector<IntRect> GetRects() const;
    void SetRects(const IntRect* rect, int num);
    int GetRectCount() const;

    Region operator|(const Region& reg) const;
    Region operator+(const Region& reg) const;
    Region operator+(const IntRect& rc) const;
    Region operator&(const Region& reg) const;
    Region operator&(const IntRect& rc) const;
    Region operator-(const Region& reg) const;
    Region operator^(const Region& reg) const;

    Region& operator|=(const Region& reg);
    Region& operator+=(const Region& reg);
    Region& operator+=(const IntRect& rc);
    Region& operator&=(const Region& reg);
    Region& operator&=(const IntRect& rc);
    Region& operator-=(const Region& reg);
    Region& operator^=(const Region& reg);

    bool operator==(const Region& reg) const;
    inline bool operator!=(const Region& reg) const { return !(operator==(reg)); }
private:
    Region Duplicate() const;
    void Detach();
    struct RegionData* d;
};

VSN_END_NAMESPACE

#endif // __VSN_REGION_H
