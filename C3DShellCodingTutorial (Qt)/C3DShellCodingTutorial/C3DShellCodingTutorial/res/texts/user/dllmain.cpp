#include "setup.h"

#include <model_item.h>
#include <reference_item.h>
#include <mb_placement3d.h>
#include <point_frame.h>
#include <plane_instance.h>
#include <plane_item.h>
#include <attribute_container.h>
#include <point3d.h>
#include <legend.h>
#include <curve3d.h>
#include <surface.h>
#include <space_instance.h>

#define CALL_DECLARATION __cdecl
#define FUNC(retType) __declspec( dllexport ) retType CALL_DECLARATION

std::vector<Model> models;
std::vector<std::string> messages;
struct Pair
{
    std::string first;
    std::string second;
};
std::vector<Pair> messageBoxes;

void addModels(const Style& style, MbItem* geomItem)
{
    if (geomItem == nullptr) return;

    ::AddRefItem(geomItem);
    models.push_back({ style, geomItem });
}

void show(const Style& style, MbSpaceItem* item)
{
    MbItem* newObj = nullptr;

    if (item != nullptr)
    {
        if (item->Family() == st_Item)
        {
            newObj = (MbItem*)item;
        }
        else
        {
            switch (item->Family())
            {
            case st_Point3D:
            {
                newObj = new MbSpaceInstance((MbPoint3D&)*item);
            }
            break;
            case st_Curve3D:
            {
                newObj = new MbSpaceInstance((MbCurve3D&)*item);
            }
            break;
            case st_Surface:
            {
                newObj = new MbSpaceInstance((MbSurface&)*item);
            }
            break;
            case st_Legend:
            {
                newObj = new MbSpaceInstance((MbLegend&)*item);
            }
            break;
            default:
                break;
            }
        }
        if (newObj != nullptr)
        {
            addModels(style, newObj);
        }
    }
}

//------------------------------------------------------------------------------

void show(const Style& style, MbPlaneItem* item, const MbPlacement3D* p)
{
    MbItem* newObj = nullptr;

    MbPlacement3D pl;
    if (p != nullptr)
        pl.Init(*p);

    newObj = new MbPlaneInstance(*item, pl);
    addModels(style, newObj);
}

//------------------------------------------------------------------------------

void show(const Style& style, const MbCartPoint& p0, const MbPlacement3D* p)
{
    MbPlacement3D pl;
    if (p != nullptr)
        pl.Init(*p);
    MbCartPoint3D pnt;
    pl.PointOn(p0, pnt);

    MbPointFrame* newObj = new MbPointFrame(pnt);
    addModels(style, newObj);
}

void show(uint32_t color, MbSpaceItem* item)
{
    show(Style(1, color), item);
}

void show(uint32_t color, MbPlaneItem* item, const MbPlacement3D* p)
{
    show(Style(1, color), item, p);
}

void show(uint32_t color, const MbCartPoint& p0, const MbPlacement3D* p)
{
    show(Style(1, color), p0, p);
}

void show(MbSpaceItem* item)
{
    show(Style(), item);
}

void show(MbPlaneItem* item, const MbPlacement3D* p)
{
    show(Style(), item, p);
}

void show(const MbCartPoint& p0, const MbPlacement3D* p)
{
    show(Style(), p0, p);
}

/*
void show(const Style& style, MbSpaceItem* refItem)
{
    if (refItem == nullptr) return;

    MbRefItem* item = refItem;
    ::AddRefItem(item);
    models.push_back({ style, item });
}
*/
/*
void show(const Style& style, MbPlaneItem* refItem, const MbPlacement3D* p)
{
    if (refItem == nullptr) return;

    MbItem* item = nullptr;

    MbPlacement3D pl;
    if (p != nullptr)
        pl.Init(*p);
    MbPlaneItem* planeItem = static_cast<MbPlaneItem*>(refItem);
    MbPlaneInstance* planeInstance = new MbPlaneInstance(*planeItem, pl);
    item = planeInstance;
    show(style, item);

}
*/

/*
void show(const Style& style, const MbCartPoint& cartPoint, const MbPlacement3D* p)
{
    MbPlacement3D pl;
    if (p != nullptr)
        pl.Init(*p);

    MbCartPoint3D pnt;
    pl.PointOn(cartPoint, pnt);

    MbPointFrame* pointFrame = new MbPointFrame(pnt);
    show(style, pointFrame);
}
*/



void message(const std::string& msg)
{
    messages.push_back(msg);
}

void messageBox(const std::string& title, const std::string& msg)
{
    messageBoxes.push_back({ title, msg });
}

void messageBox(const std::string& msg)
{
    messageBoxes.push_back({ "Message", msg });
}

extern "C"
{
    FUNC(std::size_t) get_models_size()
    {
        return models.size();
    }

    FUNC(Model*) get_model(int index)
    {
        return &models[index];
    }

    FUNC(bool) entry_point()
    {
        try
        {
            bool res = run();
            return res;

        }
        catch (std::exception& exp)
        {
            messageBox("Error", exp.what());
            return false;
        }
        catch (...)
        {
            messageBox("Error", "...");
            return false;
        }
    }

    FUNC(std::size_t) get_messages_size()
    {
        return messages.size();
    }

    FUNC(const char*) get_message(int index)
    {
        return messages[index].c_str();
    }

    FUNC(std::size_t) get_messageBoxes_size()
    {
        return messageBoxes.size();
    }

    FUNC(const char*) get_messageBoxTitle(int index)
    {
        return messageBoxes[index].first.c_str();
    }

    FUNC(const char*) get_messageBoxText(int index)
    {
        return messageBoxes[index].second.c_str();
    }
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/,
    DWORD  ul_reason_for_call,
    LPVOID /*lpReserved*/)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        //for (Model& model : models)
        //{
        //    ::DeleteItem(model.item);
        //}
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}