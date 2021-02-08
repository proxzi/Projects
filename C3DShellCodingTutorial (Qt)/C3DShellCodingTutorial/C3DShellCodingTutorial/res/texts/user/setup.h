#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
#include <string>

#include <reference_item.h>
#include <plane_item.h>
#include <space_item.h>
#include <mb_variables.h>
#include <mb_cart_point.h>

class MbRefItem;
class MbPlacement3D;
class MbCartPoint;
class MbPlaneItem;
class MbSpaceItem;
class MbPoint3D;
class MbLegend;
class MbItem;

class Style {
protected:
    uint32_t color;
    uint32_t width;
    uint32_t style;

public:
    Style(uint32_t w = 1, uint32_t c = 0xFF7F00) {
        style = 0;
        width = w;
        color = c;
    }
    Style(const Style& init) {
        style = init.style;
        width = init.width;
        color = init.color;
    }
    virtual ~Style() {}

public:

    bool operator == (const Style& with) const
    {
        return (style == with.style && width == with.width && color == with.color);
    }

    bool operator != (const Style& with) const
    {
        return !(*this == with);
    }

    void operator = (const Style& init)
    {
        set(init);
    }
    void set(const Style& init)
    {
        style = init.style;
        width = init.width;
        color = init.color;
    }
    void set(uint32_t s, uint32_t w, uint32_t c)
    {
        style = s;
        width = w;
        color = c;
    }
    void setColor(uint32_t c)
    {
        color = c;
    }
    void setWidth(uint32_t w)
    {
        width = w;
    }
    void setStyle(uint32_t s)
    {
        style = s;
    }

    uint32_t getColor() const
    {
        return color;
    }
    int getWidth() const
    {
        return width;
    }
    int getStyle() const
    {
        return style;
    }

    uint32_t& setColor()
    {
        return color;
    }
    uint32_t& setWidth()
    {
        return width;
    }
    uint32_t& setStyle()
    {
        return style;
    }
    void init(uint32_t w = 1, uint32_t c = 0)
    {
        width = w;
        color = c;
    }
}; // Style


#define BLACK         RGB(0  ,   0,   0)
#define BLUE          RGB(0  ,   0, 192)
#define GREEN         RGB(0  , 192,   0)
#define CYAN          RGB(0  , 128, 128)
#define RED           RGB(192,   0,   0)
#define MAGENTA       RGB(96 ,   0, 192)
#define BROWN         RGB(192, 128,   0)
#define LIGHTGRAY     RGB(192, 192, 192)
#define DARKGRAY      RGB(128, 158, 158)
#define LIGHTBLUE     RGB(0  ,   0, 255)
#define LIGHTGREEN    RGB(0  , 255,   0)
#define LIGHTCYAN     RGB(0  , 125, 255)
#define LIGHTRED      RGB(255,   0,   0)
#define LIGHTMAGENTA  RGB(255,   0, 255)
#define YELLOW        RGB(128, 128,   0)
#define WHITE         RGB(255, 255, 255)
#define GOLDEN        RGB(222, 222, 125)

struct Model
{
    Style style;
    MbItem* item = nullptr;
};

void addModels(const Style& style, MbItem* geomItem);

void show(const Style& style, MbSpaceItem* item);
void show(uint32_t color, MbSpaceItem* refItem);
void show(MbSpaceItem* refItem);

void show(const Style& style, MbPlaneItem* refItem, const MbPlacement3D* p = nullptr);
void show(uint32_t color, MbPlaneItem* refItem, const MbPlacement3D* p = nullptr);
void show(MbPlaneItem* refItem, const MbPlacement3D* p = nullptr);

void show(const Style& style, const MbCartPoint& cartPoint, const MbPlacement3D* p = nullptr);
void show(uint32_t color, const MbCartPoint& cartPoint, const MbPlacement3D* p = nullptr);
void show(const MbCartPoint& cartPoint, const MbPlacement3D* p = nullptr);

void message(const std::string& msg);
void messageBox(const std::string& title, const std::string& msg);
void messageBox(const std::string& msg);

bool run();