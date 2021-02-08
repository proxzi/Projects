#include "setup.h"
#include <action_solid.h> // Функции построения твердых тел
#include "surf_plane.h" // Плоскость MbPlain

bool run()
{
    // Множитель для преобразования угловых значений из градусов в радианы
    const double DEG_TO_RAD = M_PI / 180.0;
   
    //Создание двумерные точки на осях X и Y
    MbCartPoint p1(40, 0);
    MbCartPoint p2(-15, 0);
    MbCartPoint p3(-15, 15);
    MbCartPoint p4(-10, 15);
    MbCartPoint p5(-10, 45);
    MbCartPoint p6(10, 45);
    MbCartPoint p7(10, 55);
    MbCartPoint p8(30, 55);
    MbCartPoint p9(30, 25);
    MbCartPoint p10(30, 25);
    MbCartPoint p11(40, 25);
    
    //Динамическое создание объектов отрезков
    MbLineSegment* Seg1   = new MbLineSegment(p1, p2);
    MbLineSegment* Seg2   = new MbLineSegment(p2, p3);
    MbLineSegment* Seg3   = new MbLineSegment(p3, p4);
    MbLineSegment* Seg4   = new MbLineSegment(p4, p5);
    MbLineSegment* Seg5   = new MbLineSegment(p5, p6);
    MbLineSegment* Seg6   = new MbLineSegment(p6, p7);
    MbLineSegment* Seg7   = new MbLineSegment(p7, p8);
    MbLineSegment* Seg8   = new MbLineSegment(p8, p9);
    MbLineSegment* Seg9   = new MbLineSegment(p9, p10);
    MbLineSegment* Seg10 = new MbLineSegment(p10, p11);
    MbLineSegment* Seg11 = new MbLineSegment(p11, p1);

    //Динамическое создание контура
    MbContour* ptrContour = new MbContour();
    //Добавление в контур сегментов
    ptrContour->AddSegment(Seg1);
    ptrContour->AddSegment(Seg2);
    ptrContour->AddSegment(Seg3);
    ptrContour->AddSegment(Seg4);
    ptrContour->AddSegment(Seg5);
    ptrContour->AddSegment(Seg6);
    ptrContour->AddSegment(Seg7);
    ptrContour->AddSegment(Seg8);
    ptrContour->AddSegment(Seg9);
    ptrContour->AddSegment(Seg10);
    ptrContour->AddSegment(Seg11);

    // Создание плоскости - она совпадает с плоскостью XY локальной СК
    MbPlacement3D* place = new MbPlacement3D();
    MbPlane* ptrSurface = new MbPlane(*place);

    //Создание образующей для тела вращения
    RPArray<MbContour>* ptrContours = new RPArray<MbContour>();
    ptrContours->Add(ptrContour);

    //объект, в котором хранятся сведения об образующей
    MbSweptData* pCurves;
    pCurves = new MbSweptData(*ptrSurface, *ptrContours);

    // Объект параметров для построения тел вращения.
    RevolutionValues revParms( 360*DEG_TO_RAD, 0, 0);

    //Именователи для операции построения тела вращения и для контуров образующей
    MbSNameMaker operNames( 1, MbSNameMaker::i_SideNone, 0);
    PArray<MbSNameMaker> cNames(0, 1, false);

    //Ось вращения для построения тела
    MbAxis3D axis(place->GetAxisX());

    // Вызов функции-утилиты для построения твердого тела вращения
    MbSolid* m_pResSolid = nullptr;
    MbResultType m_bResult = RevolutionSolid(*pCurves, axis, revParms, operNames, cNames, m_pResSolid);

    // отображение построенного тела
    if(m_bResult == rt_Success)
        show(m_pResSolid);

    return true;
}