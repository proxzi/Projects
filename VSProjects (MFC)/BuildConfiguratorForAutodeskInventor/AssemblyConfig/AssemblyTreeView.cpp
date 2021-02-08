// AssemblyTreeView.cpp: файл реализации
//

#include "stdafx.h"
#include "AssemblyConfig.h"
#include "AssemblyTreeView.h"
#include "AssemblyConfigDoc.h"


#define PI 3.141592
//Подключение библиотеки Инвентора /*Принудительное переименование пространств имен*/
#import <RxInventor.tlb> \
rename_namespace("InventorNative") \
named_guids raw_dispinterfaces \
high_method_prefix("Method") \
rename("DeleteFile", "APIDeleteFile") \
rename("CopyFile", "APICopyFile") \
rename("MoveFile", "APIMoveFile") \
rename("SetEnvironmentVariable", "APISetEnvironmentVariable") \
rename("GetObject", "APIGetObject") \
exclude("_FILETIME", "IStream", "ISequentialStream", \
"_LARGE_INTEGER", "_ULARGE_INTEGER", "tagSTATSTG", \
"IEnumUnknown", "IPersistFile", "IPersist", "IPictureDisp")

IMPLEMENT_DYNCREATE(CAssemblyTreeView, CTreeView)

CAssemblyTreeView::CAssemblyTreeView()
{
	m_ComponentNames.RemoveAll();
	//m_ComponentNames.Add(L"Сборка");
	m_ComponentNames.Add(L"Вал 1");
	m_ComponentNames.Add(L"Вал 2");
	m_ComponentNames.Add(L"Подшипник 1");
	m_ComponentNames.Add(L"Подшипник 2");
	m_ComponentNames.Add(L"Шестерёнка");
	m_ComponentNames.Add(L"Колесо");
	m_ComponentNames.Add(L"|НАЧАТЬ СБОРКУ|");
}

CAssemblyTreeView::~CAssemblyTreeView()
{
}

BEGIN_MESSAGE_MAP(CAssemblyTreeView, CTreeView)
	
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// диагностика CAssemblyTreeView

#ifdef _DEBUG
void CAssemblyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CAssemblyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// обработчики сообщений CAssemblyTreeView


void CAssemblyTreeView::FillTree()
{
	CTreeCtrl& ctlTree = (CTreeCtrl&)GetTreeCtrl();

	ctlTree.DeleteAllItems();

	m_hRoot = ctlTree.InsertItem(L"Сборка", -1, -1, NULL, TVI_FIRST);
	ctlTree.SetItemData(m_hRoot,-1);
	if (m_iSelected ==-1)
		ctlTree.SetItemState(m_hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM item;

	for (int i = 0; i < m_ComponentNames.GetSize(); i++)
	{
		item = ctlTree.InsertItem(m_ComponentNames[i], -1, -1, m_hRoot, TVI_LAST);
		ctlTree.SetItemData(item, i);
		if (i == m_iSelected)
			ctlTree.SetItemState(item, TVIS_BOLD, TVIS_BOLD);
		else
			ctlTree.SetItemState(item, 0, TVIS_BOLD);

	}

	ctlTree.Expand(m_hRoot, TVE_EXPAND);
}

int CAssemblyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{


	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CTreeCtrl& ctlTree = (CTreeCtrl&)GetTreeCtrl();

	FillTree();
	
	

	
	return 0;
}


void CAssemblyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& ctlTree = (CTreeCtrl&)GetTreeCtrl();

	HTREEITEM hItem = ctlTree.GetSelectedItem();
	if (hItem)
	{
         m_iSelected = ctlTree.GetItemData(hItem);
		FillTree();
	}

	LongB4 = Long2 / 2;
	Diam = DiamVerh + Long2;
	Diam2 = DiamVerh2 + Long2;

	if (m_iSelected == 0) {
		Val01.DiamPod = DiamPod;
		Val01.DiamOsnov = DiamOsnov;
		Val01.DiamShest = DiamShest;
		Val01.Long1 = Long1;
		Val01.Long2 = Long2;
		Val01.Long3 = Long3;
		if (Val01.DoModal() == IDOK) {
			DiamPod = Val01.DiamPod;
			DiamOsnov = Val01.DiamOsnov;
			DiamShest = Val01.DiamShest;
			Long1 = Val01.Long1;
			Long2 = Val01.Long2;
			Long3 = Val01.Long3;
			VvodParametrov++;
			val1 = true;
		}
	}

	if (m_iSelected == 1) {
		Val02.DiamShest2 = DiamShest2;
		Val02.DiamPod2 = DiamPod2;
		Val02.DiamOsnov2 = DiamOsnov2;
		Val02.LongB1 = LongB1;
		Val02.LongB2 = LongB2;
		Val02.LongB3 = LongB3;
		Val02.LongB4 = LongB4;
		if (Val02.DoModal() == IDOK) {
			DiamShest2 = Val02.DiamShest2;
			DiamPod2 = Val02.DiamPod2;
			DiamOsnov2 = Val02.DiamOsnov2;
			LongB1 = Val02.LongB1;
			LongB2 = Val02.LongB2;
			LongB3 = Val02.LongB3;
			VvodParametrov++;
			val2 = true;
		}
	}
	if (m_iSelected == 2) {
		Pod01.DiamVnesh = DiamVnesh;
		Pod01.Kol_Vo_Shar = Kol_Vo_Shar;
		Pod01.DiamShar = DiamShar;
		Pod01.DiamPod = DiamPod;
		Pod01.Long1 = Long1;
		if (Pod01.DoModal() == IDOK) {
			DiamVnesh = Pod01.DiamVnesh;
			Kol_Vo_Shar = Pod01.Kol_Vo_Shar;
			DiamShar = Pod01.DiamShar;
			VvodParametrov++;
			pod1 = true;
		}
	}
	if (m_iSelected == 3) {
		Pod02.DiamVnesh2 = DiamVnesh2;
		Pod02.Kol_Vo_Shar2 = Kol_Vo_Shar2;
		Pod02.DiamShar2 = DiamShar2;
		Pod02.DiamPod2 = DiamPod2;
		Pod02.LongB3 = LongB3;
		if (Pod02.DoModal() == IDOK) {
			DiamVnesh2 = Pod02.DiamVnesh2;
			Kol_Vo_Shar2 = Pod02.Kol_Vo_Shar2;
			DiamShar2 = Pod02.DiamShar2;
			VvodParametrov++;
			pod2 = true;
		}
	}

	if (m_iSelected == 4) {
		Shest.Diam2 = Diam2;
		Shest.DiamVerh2 = DiamVerh2;
		Shest.ZubVisota2 = ZubVisota2;
		Shest.Kol_vo_Zubov2 = Kol_vo_Zubov2;
		Shest.DiamShest2 = DiamShest2;
		Shest.LongB4 = LongB4;
		if (Shest.DoModal() == IDOK) {
			Diam2 = Shest.Diam2;
			DiamVerh2 = Shest.DiamVerh2;
			ZubVisota2 = Shest.ZubVisota2;
			Kol_vo_Zubov2 = Shest.Kol_vo_Zubov2;
			VvodParametrov++;
			shest = true;
		}
	}
	if (m_iSelected == 5) {
		Kol.Diam = Diam;
		Kol.DiamVerh = DiamVerh;
		Kol.ZubVisota = ZubVisota;
		Kol.Kol_vo_Zubov = Kol_vo_Zubov;
		Kol.DiamShest = DiamShest;
		Kol.Long2 = Long2;
		if (Kol.DoModal() == IDOK) {
			Diam = Kol.Diam;
			DiamVerh = Kol.DiamVerh;
			ZubVisota = Kol.ZubVisota;
			Kol_vo_Zubov = Kol.Kol_vo_Zubov;
			VvodParametrov++;
			kol = true;
		}
	}

	if (m_iSelected == 6) {
		if(MessageBox(L"Вы действительно хотите начать сборку?", L"Предупреждение", MB_YESNO) == IDYES)
			if (!val1 || !val2 || !pod1 || !pod2 || !shest || !kol) {
				CString MessageErrors = L"Не все параметры были введены!\n\n Отсутствуют:";
				if (!val1)
					MessageErrors += L"\n\tВал 1";
				if (!val2)
					MessageErrors += L"\n\tВал 2";
				if (!pod1)
					MessageErrors += L"\n\tПодшипник 1";
				if (!pod2)
					MessageErrors += L"\n\tПодшипник 2";
				if (!shest)
					MessageErrors += L"\n\tШестеренка";
				if (!kol)
					MessageErrors += L"\n\tКолесо";
				MessageBox(MessageErrors, L"Предупреждение", MB_OK);
			}
	
			else if (DiamPod == DiamOsnov || DiamPod == DiamShest || DiamOsnov == DiamShest ||
				Long1 <= 0 || Long2 <= 0 || Long3 <= 0 ||
				DiamPod <= 0 || DiamOsnov <= 0 || DiamShest <= 0 ||
				DiamPod2 == DiamOsnov2 || DiamPod2 == DiamShest2 || DiamOsnov2 == DiamShest2 ||
				LongB1 <= 0 || LongB2 <= 0 || LongB3 <= 0 || LongB4 <= 0 ||
				DiamPod2 <= 0 || DiamOsnov2 <= 0 || DiamShest2 <= 0 ||
				LongB1 < LongB3 ||
				DiamPod > DiamVnesh ||
				DiamVnesh / 2 - DiamPod / 2 <= DiamShar ||
				Long1 <= DiamShar ||
				DiamPod2 > DiamVnesh2 ||
				DiamVnesh2 / 2 - DiamPod2 / 2 <= DiamShar2 ||
				LongB3 <= DiamShar2 ||
				DiamShest2 > DiamVerh2 ||
				DiamShest > DiamVerh ||
				DiamPod > DiamShest)
			{
				CString Err;
				Err += _T("Вал 1:\n");
				if (DiamPod == DiamOsnov || DiamPod == DiamShest || DiamOsnov == DiamShest)
					Err += _T("\tДиаметры не должны совпадать!\n");
				if (Long1 <= 0 || Long2 <= 0 || Long3 <= 0)
					Err += _T("\tДлина <= 0!\n");
				if (DiamPod <= 0 || DiamOsnov <= 0 || DiamShest <= 0)
					Err += _T("\tДиаметр <= 0!\n");

				Err += _T("Вал 2:\n");
				if (DiamPod2 == DiamOsnov2 || DiamPod2 == DiamShest2 || DiamOsnov2 == DiamShest2)
					Err += _T("\tДиаметры не должны совпадать!\n");
				if (LongB1 <= 0 || LongB2 <= 0 || LongB3 <= 0 || LongB4 <= 0)
					Err += _T("\tДлина <= 0!\n");
				if (DiamPod2 <= 0 || DiamOsnov2 <= 0 || DiamShest2 <= 0)
					Err += _T("\tДиаметр <= 0!\n");
				if (LongB1 < LongB3)
					Err += _T("\tШирина участка < ширины подшипника!\n");

				Err += _T("Подшипник 1:\n");
				if (DiamPod > DiamVnesh)
					Err += _T("\tВнутренний диаметр > внешнего!\n");
				if (DiamVnesh/2 - DiamPod/2 <= DiamShar)
					Err += _T("\tДиаметр шара слишком велик!\n");
				if (Long1 <= DiamShar)
					Err += _T("\tШарик больше ширины!\n");

				Err += _T("Подшипник 2:\n");
				if (DiamPod2 > DiamVnesh2)
					Err += _T("\tВнутренний диаметр > внешнего!\n");
				if (DiamVnesh2 / 2 - DiamPod2 / 2 <= DiamShar2)
					Err += _T("\tДиаметр шара слишком велик!\n");
				if (LongB3 <= DiamShar2)
					Err += _T("\tШарик больше ширины!\n");

				Err += _T("Шестеренка:\n");
				if (DiamShest2 > DiamVerh2)
					Err += _T("\tВнутренний диаметр > внешнего!\n");

				Err += _T("Колесо:\n");
				if (DiamShest > DiamVerh)
					Err += _T("\tВнутренний диаметр > внешнего!\n");

				Err += _T("Сборка:\n");
				if (DiamPod > DiamShest)
					Err += _T("\tПодшипник больше диаметра колеса!\n");

				MessageBox(Err, L"Предупреждение", MB_OK | MB_ICONWARNING);
			}
			else
				Code();
	}
}

void CAssemblyTreeView::Code()
{
	//См в мм
	DiamPod /= 10;
	DiamOsnov /= 10;
	DiamShest /= 10;
	Long1 /= 10;
	Long2 /= 10;
	Long3 /= 10;

	DiamShest2 /= 10;
	DiamPod2 /= 10;
	DiamOsnov2 /= 10;;
	LongB1 /= 10;
	LongB2 /= 10;
	LongB3 /= 10;
	LongB4 /= 10;

	DiamVnesh /= 10;
	DiamShar /= 10;

	DiamVnesh2 /= 10;
	DiamShar2 /= 10;

	Diam /= 10;
	DiamVerh /= 10;
	ZubVisota /= 10;

	Diam2 /= 10;
	DiamVerh2 /= 10;
	ZubVisota2 /= 10;
	//
	double Chamfer = 0.04;
	double Fillet = 0.4;
	double GlobalKoeff = 3.2;

	//Использование пространства имен
	using namespace InventorNative;
	//Указатель на инвентор
	CComPtr<Application> pInvApp;
	//Указатели на остальные компаненты 
	TransactionManagerPtr pTransManager;

	PlanarSketches *sketches;
	Sketches3D   *sketches3D;
	WorkPlanes *wp;
	PartFeatures *ft;
	WorkAxes *wax;
	WorkPoints *wpt;


	// Запуск инвентора и проверка не был ли он запущен
	CLSID InvAppClsid;
	HRESULT hRes = CLSIDFromProgID(L"Inventor.Application", &InvAppClsid);
	if (FAILED(hRes)) {
		pInvApp = nullptr;
		return;
	}
	CComPtr<IUnknown> pInvAppUnk = nullptr;
	hRes = ::GetActiveObject(InvAppClsid, NULL, &pInvAppUnk);
	if (FAILED(hRes)) {
		TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
		hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void **)&pInvAppUnk);
		if (FAILED(hRes)) {
			pInvApp = nullptr;
			return;
		}
	}
	hRes = pInvAppUnk->QueryInterface(__uuidof(Application), (void **)&pInvApp);
	if (FAILED(hRes))
		return;
	pInvApp->put_Visible(TRUE);

	///



	///////////////////////////////////////
	///Val 1

	// Указатели на деталь
	PartDocumentPtr pPartDoc;
	PartComponentDefinition *pPartComDef;
	TransientGeometry *pTransGeom;
	Transaction *pTrans;
	//Открытие Создания детали
	pPartDoc = pInvApp->Documents->MethodAdd(kPartDocumentObject, pInvApp->FileManager->MethodGetTemplateFile(kPartDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true);
	pPartDoc->DisplayName = _T("Вал 1");
	// Указатели что были выше объявлены указывают на компоненты в этой детали
	pPartDoc->get_ComponentDefinition(&pPartComDef);

	pInvApp->get_TransientGeometry(&pTransGeom);

	pTransManager = pInvApp->GetTransactionManager();
	pTransManager->raw_StartTransaction(CComQIPtr <Document>(pPartDoc), _T(""), &pTrans);

	pPartComDef->get_Sketches(&sketches);
	pPartComDef->get_Sketches3D(&sketches3D);
	pPartComDef->get_WorkPlanes(&wp);
	pPartComDef->get_Features(&ft);
	pPartComDef->get_WorkAxes(&wax);
	pPartComDef->get_WorkPoints(&wpt);

	////////////////////////////////////////
	// Создание модели вала

	PlanarSketch *pSketch;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch);

	SketchLinePtr lines[10];
	SketchLines *skLines;
	SketchPointPtr point[10];
	SketchPoints *skPoints;
	Profiles *skProfiles;
	
	pSketch->get_SketchPoints(&skPoints);
	pSketch->get_SketchLines(&skLines);
	pSketch->get_Profiles(&skProfiles);

	point[0] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(0, 0), false);
	point[1] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(0, DiamPod / 2), false);
	point[2] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(Long1, DiamPod / 2), false);
	point[3] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(Long1, DiamOsnov / 2), false);
	point[4] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(Long1 + Long3, DiamOsnov / 2), false);
	point[5] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(Long1 + Long3, DiamShest / 2), false);
	point[6] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(Long1 + Long3 + Long2, DiamShest / 2), false);
	point[7] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(Long1 + Long3 + Long2, DiamPod / 2), false);
	point[8] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(Long1 + Long3 + Long2 + Long1, DiamPod / 2), false);
	point[9] = skPoints->MethodAdd(pTransGeom->MethodCreatePoint2d(Long1 + Long3 + Long2 + Long1, 0), false);

	for (int i = 0; i < 9; i++)
		lines[i] = skLines->MethodAddByTwoPoints(point[i], point[i + 1]);
	lines[9] = skLines->MethodAddByTwoPoints(point[9], point[0]);
	Profile *pProfile;
	skProfiles->raw__AddForSolid(&pProfile);
	RevolveFeatures *ftRevolve;
	ft->get_RevolveFeatures(&ftRevolve);

	RevolveFeaturePtr oRevolveDef = ftRevolve->MethodAddFull(pProfile, lines[9], kJoinOperation);

	//Фаска
	EdgeCollection *edgeColl;

	pInvApp->TransientObjects->raw_CreateEdgeCollection(vtMissing, &edgeColl);

	SurfaceBody *SurfBody0;
	SurfaceBodies *SurfBodies0;

	pPartComDef->get_SurfaceBodies(&SurfBodies0);

	SurfBodies0->get_Item(1, &SurfBody0);

	Edges *edges, *edges2;

	SurfBody0->get_Edges(&edges);
	SurfBody0->get_Edges(&edges2);

	Edge *ed, *ed2;
	edges->get_Item(8, &ed);
	edges2->get_Item(1, &ed2);

	edgeColl->MethodAdd(ed);
	edgeColl->MethodAdd(ed2);

	ChamferFeatures *chamFeatures;
	ft->get_ChamferFeatures(&chamFeatures);

	ChamferFeature *chamFeature = chamFeatures->MethodAddUsingDistance(edgeColl, Chamfer, false, false, false);  //фаска

	pTrans->MethodEnd();

	///////////////////////////////////////
	///Val 2

	//
	PartDocumentPtr pPartDoc2;
	PartComponentDefinition *pPartComDef2;
	TransientGeometry *pTransGeom2;
	Transaction *pTrans2;
	//
	pPartDoc2 = pInvApp->Documents->MethodAdd(kPartDocumentObject, pInvApp->FileManager->MethodGetTemplateFile(kPartDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true);
	pPartDoc2->DisplayName = _T("Вал 2");
	//
	pPartDoc2->get_ComponentDefinition(&pPartComDef2);
	
	pInvApp->get_TransientGeometry(&pTransGeom2);

	pTransManager = pInvApp->GetTransactionManager();
	pTransManager->raw_StartTransaction(CComQIPtr <Document>(pPartDoc2), _T(""), &pTrans2);

	pPartComDef2->get_Sketches(&sketches);
	pPartComDef2->get_Sketches3D(&sketches3D);
	pPartComDef2->get_WorkPlanes(&wp);
	pPartComDef2->get_Features(&ft);
	pPartComDef2->get_WorkAxes(&wax);
	pPartComDef2->get_WorkPoints(&wpt);

	////////////////////////////////////////
	//Вал 2

	PlanarSketch *pSketch2;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch2);

	SketchLinePtr lines2[10];
	SketchLines *skLines2;
	SketchPointPtr point2[10];
	SketchPoints *skPoints2;
	Profiles *skProfiles2;

	pSketch2->get_SketchPoints(&skPoints2);
	pSketch2->get_SketchLines(&skLines2);
	pSketch2->get_Profiles(&skProfiles2);

	point2[0] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(0, 0), false);
	point2[1] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(0, DiamPod2 / 2), false);
	point2[2] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(LongB1, DiamPod2 / 2), false);
	point2[3] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(LongB1, DiamOsnov2 / 2), false);
	point2[4] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(LongB1 + LongB2, DiamOsnov2 / 2), false);
	point2[5] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(LongB1 + LongB2, DiamPod2 / 2), false);
	point2[6] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(LongB1 + LongB2 + LongB3, DiamPod2 / 2), false);
	point2[7] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(LongB1 + LongB2 + LongB3, DiamShest2 / 2), false);
	point2[8] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(LongB1 + LongB2 + LongB3 + LongB4, DiamShest2 / 2), false);
	point2[9] = skPoints2->MethodAdd(pTransGeom2->MethodCreatePoint2d(LongB1 + LongB2 + LongB3 + LongB4, 0), false);

	for (int i = 0; i < 9; i++)
		lines2[i] = skLines2->MethodAddByTwoPoints(point2[i], point2[i + 1]);
	lines2[9] = skLines2->MethodAddByTwoPoints(point2[9], point2[0]);
	Profile *pProfile2;
	skProfiles2->raw__AddForSolid(&pProfile2);
	RevolveFeatures *ftRevolve2;
	ft->get_RevolveFeatures(&ftRevolve2);

	RevolveFeaturePtr oRevolveDef2 = ftRevolve2->MethodAddFull(pProfile2, lines2[9], kJoinOperation);

	//Фаска
	EdgeCollection *edgeColla;

	pInvApp->TransientObjects->raw_CreateEdgeCollection(vtMissing, &edgeColla);

	SurfaceBody *SurfBodya;
	SurfaceBodies *SurfBodiesa;

	pPartComDef2->get_SurfaceBodies(&SurfBodiesa);

	SurfBodiesa->get_Item(1, &SurfBodya);

	Edges *edgesa;

	SurfBodya->get_Edges(&edgesa);

	Edge *eda;
	edgesa->get_Item(8, &eda);

	edgeColla->MethodAdd(eda);
	//edgeColla->MethodAdd(eda2);

	ChamferFeatures *chamFeaturesa;
	ft->get_ChamferFeatures(&chamFeaturesa);

	ChamferFeature *chamFeaturea = chamFeaturesa->MethodAddUsingDistance(edgeColla, Chamfer, false, false, false);

	pTrans2->MethodEnd();
	
	///////////////////
	///Под 1
	//
	PartDocumentPtr pPartDoc3;
	PartComponentDefinition *pPartComDef3;
	TransientGeometry *pTransGeom3;
	Transaction *pTrans3;
	//
	pPartDoc3 = pInvApp->Documents->MethodAdd(kPartDocumentObject, pInvApp->FileManager->MethodGetTemplateFile(kPartDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true);
	pPartDoc3->DisplayName = _T("Под 1");
	//
	pPartDoc3->get_ComponentDefinition(&pPartComDef3);
	
	pInvApp->get_TransientGeometry(&pTransGeom3);

	pTransManager = pInvApp->GetTransactionManager();
	pTransManager->raw_StartTransaction(CComQIPtr <Document>(pPartDoc3), _T(""), &pTrans3);

	pPartComDef3->get_Sketches(&sketches);
	pPartComDef3->get_Sketches3D(&sketches3D);
	pPartComDef3->get_WorkPlanes(&wp);
	pPartComDef3->get_Features(&ft);
	pPartComDef3->get_WorkAxes(&wax);
	pPartComDef3->get_WorkPoints(&wpt);
	//Подшипник первого вала
	PlanarSketch *pSketch3;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch3);

	SketchLinePtr lines3[10];
	SketchLines *skLines3;
	SketchPointPtr point3[13];
	SketchPoints *skPoints3;
	SketchArcPtr arc3[5];
	SketchArcs *skArcs3;
	Profiles *skProfiles3;

	pSketch3->get_SketchPoints(&skPoints3);
	pSketch3->get_SketchLines(&skLines3);
	pSketch3->get_Profiles(&skProfiles3);
	pSketch3->get_SketchArcs(&skArcs3);

	point3[12] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(0, (DiamPod + DiamVnesh) / 4), false);

	point3[0] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(-Long1 / 2, DiamPod / 2), false);
	point3[1] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(Long1 / 2, DiamPod / 2), false);
	point3[2] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(Long1 / 2, (DiamPod + DiamVnesh) / 4 + DiamShar / 2 * sin(-PI / 6)), false);
	point3[3] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(DiamShar / 2 * cos(-PI / 6), (DiamPod + DiamVnesh) / 4 + DiamShar / 2 * sin(-PI / 6)), false);
	point3[4] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(DiamShar / 2 * cos(7 * PI / 6), (DiamPod + DiamVnesh) / 4 + DiamShar / 2 * sin(7 * PI / 6)), false);
	point3[5] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(-Long1 / 2, (DiamPod + DiamVnesh) / 4 + DiamShar / 2 * sin(7 * PI / 6)), false);

	lines3[0] = skLines3->MethodAddByTwoPoints(point3[0], point3[1]);
	lines3[1] = skLines3->MethodAddByTwoPoints(point3[1], point3[2]);
	lines3[2] = skLines3->MethodAddByTwoPoints(point3[2], point3[3]);
	arc3[0] = skArcs3->MethodAddByCenterStartEndPoint(point3[12], point3[3], point3[4], false);
	lines3[3] = skLines3->MethodAddByTwoPoints(point3[4], point3[5]);
	lines3[4] = skLines3->MethodAddByTwoPoints(point3[5], point3[0]);

	point3[6] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(-Long1 / 2, DiamVnesh / 2), false);
	point3[7] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(Long1 / 2, DiamVnesh / 2), false);
	point3[8] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(Long1 / 2, (DiamPod + DiamVnesh) / 4 + DiamShar / 2 * sin(PI / 6)), false);
	point3[9] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(DiamShar / 2 * cos(PI / 6), (DiamPod + DiamVnesh) / 4 + DiamShar / 2 * sin(PI / 6)), false);
	point3[10] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(DiamShar / 2 * cos(5 * PI / 6), (DiamPod + DiamVnesh) / 4 + DiamShar / 2 * sin(5 * PI / 6)), false);
	point3[11] = skPoints3->MethodAdd(pTransGeom3->MethodCreatePoint2d(-Long1 / 2, (DiamPod + DiamVnesh) / 4 + DiamShar / 2 * sin(5 * PI / 6)), false);

	lines3[5] = skLines3->MethodAddByTwoPoints(point3[6], point3[7]);
	lines3[6] = skLines3->MethodAddByTwoPoints(point3[7], point3[8]);
	lines3[7] = skLines3->MethodAddByTwoPoints(point3[8], point3[9]);
	arc3[1] = skArcs3->MethodAddByCenterStartEndPoint(point3[12], point3[9], point3[10], true);
	lines3[8] = skLines3->MethodAddByTwoPoints(point3[10], point3[11]);
	lines3[9] = skLines3->MethodAddByTwoPoints(point3[11], point3[6]);

	Profile *pProfile3;
	skProfiles3->raw__AddForSolid(&pProfile3);
	RevolveFeatures *ftRevolve3;
	ft->get_RevolveFeatures(&ftRevolve3);

	RevolveFeaturePtr oRevolveDef3 = ftRevolve3->MethodAddFull(pProfile3, wax->GetItem(1), kJoinOperation);

	PlanarSketch *pSketch3B;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch3B);

	SketchLinePtr lines3B[1];
	SketchLines *skLines3B;
	SketchPointPtr point3B[3];
	SketchPoints *skPoints3B;
	SketchArcPtr arc3B[1];
	SketchArcs *skArcs3B;
	Profiles *skProfiles3B;


	pSketch3B->get_SketchPoints(&skPoints3B);
	pSketch3B->get_SketchLines(&skLines3B);
	pSketch3B->get_Profiles(&skProfiles3B);
	pSketch3B->get_SketchArcs(&skArcs3B);

	point3B[0] = skPoints3B->MethodAdd(pTransGeom3->MethodCreatePoint2d(0, (DiamPod + DiamVnesh) / 4), false);
	point3B[1] = skPoints3B->MethodAdd(pTransGeom3->MethodCreatePoint2d(0, (DiamPod + DiamVnesh) / 4 - DiamShar / 2), false);
	point3B[2] = skPoints3B->MethodAdd(pTransGeom3->MethodCreatePoint2d(0, (DiamPod + DiamVnesh) / 4 + DiamShar / 2), false);

	lines3B[0] = skLines3B->MethodAddByTwoPoints(point3B[1], point3B[2]);
	arc3B[0] = skArcs3B->MethodAddByCenterStartEndPoint(point3B[0], point3B[1], point3B[2], true);

	Profile *pProfile3B;
	skProfiles3B->raw__AddForSolid(&pProfile3B);

	RevolveFeatures *ftRevolve3B;
	ft->get_RevolveFeatures(&ftRevolve3B);

	RevolveFeaturePtr oRevolveDef3B = ftRevolve3B->MethodAddFull(pProfile3B, wax->GetItem(2), kJoinOperation);

	ObjectCollection *pCollection;

	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pCollection);
	pCollection->MethodAdd(oRevolveDef3B);
	CircularPatternFeatures *pCircPatFeat;
	ft->get_CircularPatternFeatures(&pCircPatFeat);

	CircularPatternFeature *circFeat = pCircPatFeat->MethodAdd(pCollection, wax->GetItem(1), true, Kol_Vo_Shar, "360 deg", true, kIdenticalCompute);

	//Фаска
	EdgeCollection *edgeCollb;

	pInvApp->TransientObjects->raw_CreateEdgeCollection(vtMissing, &edgeCollb);

	SurfaceBody *SurfBodyb;
	SurfaceBodies *SurfBodiesb;

	pPartComDef3->get_SurfaceBodies(&SurfBodiesb);

	SurfBodiesb->get_Item(1, &SurfBodyb);

	Edges *edgesb, *edgesb2, *edgesb3, *edgesb4;

	SurfBodyb->get_Edges(&edgesb);
	SurfBodyb->get_Edges(&edgesb2);
	SurfBodyb->get_Edges(&edgesb3);
	SurfBodyb->get_Edges(&edgesb4);

	Edge *edb, *edb2, *edb3, *edb4;
	edgesb->get_Item(69, &edb);
	edgesb2->get_Item(76, &edb2);
	edgesb3->get_Item(80, &edb3);
	edgesb4->get_Item(74, &edb4);

	edgeCollb->MethodAdd(edb);
	edgeCollb->MethodAdd(edb2);
	edgeCollb->MethodAdd(edb3);
	edgeCollb->MethodAdd(edb4);

	ChamferFeatures *chamFeaturesb;
	ft->get_ChamferFeatures(&chamFeaturesb);

	ChamferFeature *chamFeatureb = chamFeaturesb->MethodAddUsingDistance(edgeCollb, Chamfer, false, false, false);

	pTrans3->MethodEnd();

	///////////////////
	///Под 2
	//
	PartDocumentPtr pPartDoc4;
	PartComponentDefinition *pPartComDef4;
	TransientGeometry *pTransGeom4;
	Transaction *pTrans4;
	//
	pPartDoc4 = pInvApp->Documents->MethodAdd(kPartDocumentObject, pInvApp->FileManager->MethodGetTemplateFile(kPartDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true);
	pPartDoc4->DisplayName = _T("Под 2");
	//
	pPartDoc4->get_ComponentDefinition(&pPartComDef4);

	pInvApp->get_TransientGeometry(&pTransGeom4);

	pTransManager = pInvApp->GetTransactionManager();
	pTransManager->raw_StartTransaction(CComQIPtr <Document>(pPartDoc4), _T(""), &pTrans4);

	pPartComDef4->get_Sketches(&sketches);
	pPartComDef4->get_Sketches3D(&sketches3D);
	pPartComDef4->get_WorkPlanes(&wp);
	pPartComDef4->get_Features(&ft);
	pPartComDef4->get_WorkAxes(&wax);
	pPartComDef4->get_WorkPoints(&wpt);
	//Подшипник 2ого вала
	PlanarSketch *pSketch4;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch4);

	SketchLinePtr lines4[10];
	SketchLines *skLines4;
	SketchPointPtr point4[13];
	SketchPoints *skPoints4;
	SketchArcPtr arc4[5];
	SketchArcs *skArcs4;
	Profiles *skProfiles4;

	pSketch4->get_SketchPoints(&skPoints4);
	pSketch4->get_SketchLines(&skLines4);
	pSketch4->get_Profiles(&skProfiles4);
	pSketch4->get_SketchArcs(&skArcs4);

	point4[12] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(0, (DiamPod2 + DiamVnesh2) / 4), false);

	point4[0] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(-LongB3 / 2, DiamPod2 / 2), false);
	point4[1] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(LongB3 / 2, DiamPod2 / 2), false);
	point4[2] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(LongB3 / 2, (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2 * sin(-PI / 6)), false);
	point4[3] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(DiamShar2 / 2 * cos(-PI / 6), (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2 * sin(-PI / 6)), false);
	point4[4] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(DiamShar2 / 2 * cos(7 * PI / 6), (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2 * sin(7 * PI / 6)), false);
	point4[5] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(-LongB3 / 2, (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2 * sin(7 * PI / 6)), false);

	lines4[0] = skLines4->MethodAddByTwoPoints(point4[0], point4[1]);
	lines4[1] = skLines4->MethodAddByTwoPoints(point4[1], point4[2]);
	lines4[2] = skLines4->MethodAddByTwoPoints(point4[2], point4[3]);
	arc4[0] = skArcs4->MethodAddByCenterStartEndPoint(point4[12], point4[3], point4[4], false);
	lines4[3] = skLines4->MethodAddByTwoPoints(point4[4], point4[5]);
	lines4[4] = skLines4->MethodAddByTwoPoints(point4[5], point4[0]);

	point4[6] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(-LongB3 / 2, DiamVnesh2 / 2), false);
	point4[7] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(LongB3 / 2, DiamVnesh2 / 2), false);
	point4[8] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(LongB3 / 2, (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2 * sin(PI / 6)), false);
	point4[9] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(DiamShar2 / 2 * cos(PI / 6), (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2 * sin(PI / 6)), false);
	point4[10] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(DiamShar2 / 2 * cos(5 * PI / 6), (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2 * sin(5 * PI / 6)), false);
	point4[11] = skPoints4->MethodAdd(pTransGeom4->MethodCreatePoint2d(-LongB3 / 2, (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2 * sin(5 * PI / 6)), false);

	lines4[5] = skLines4->MethodAddByTwoPoints(point4[6], point4[7]);
	lines4[6] = skLines4->MethodAddByTwoPoints(point4[7], point4[8]);
	lines4[7] = skLines4->MethodAddByTwoPoints(point4[8], point4[9]);
	arc4[1] = skArcs4->MethodAddByCenterStartEndPoint(point4[12], point4[9], point4[10], true);
	lines4[8] = skLines4->MethodAddByTwoPoints(point4[10], point4[11]);
	lines4[9] = skLines4->MethodAddByTwoPoints(point4[11], point4[6]);

	Profile *pProfile4;
	skProfiles4->raw__AddForSolid(&pProfile4);
	RevolveFeatures *ftRevolve4;
	ft->get_RevolveFeatures(&ftRevolve4);

	RevolveFeaturePtr oRevolveDef4 = ftRevolve4->MethodAddFull(pProfile4, wax->GetItem(1), kJoinOperation);

	PlanarSketch *pSketch4B;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch4B);

	SketchLinePtr lines4B[1];
	SketchLines *skLines4B;
	SketchPointPtr point4B[3];
	SketchPoints *skPoints4B;
	SketchArcPtr arc4B[1];
	SketchArcs *skArcs4B;
	Profiles *skProfiles4B;

	pSketch4B->get_SketchPoints(&skPoints4B);
	pSketch4B->get_SketchLines(&skLines4B);
	pSketch4B->get_Profiles(&skProfiles4B);
	pSketch4B->get_SketchArcs(&skArcs4B);

	point4B[0] = skPoints4B->MethodAdd(pTransGeom4->MethodCreatePoint2d(0, (DiamPod2 + DiamVnesh2) / 4), false);
	point4B[1] = skPoints4B->MethodAdd(pTransGeom4->MethodCreatePoint2d(0, (DiamPod2 + DiamVnesh2) / 4 - DiamShar2 / 2), false);
	point4B[2] = skPoints4B->MethodAdd(pTransGeom4->MethodCreatePoint2d(0, (DiamPod2 + DiamVnesh2) / 4 + DiamShar2 / 2), false);

	lines4B[0] = skLines4B->MethodAddByTwoPoints(point4B[1], point4B[2]);
	arc4B[0] = skArcs4B->MethodAddByCenterStartEndPoint(point4B[0], point4B[1], point4B[2], true);

	Profile *pProfile4B;
	skProfiles4B->raw__AddForSolid(&pProfile4B);

	RevolveFeatures *ftRevolve4B;
	ft->get_RevolveFeatures(&ftRevolve4B);

	RevolveFeaturePtr oRevolveDef4B = ftRevolve4B->MethodAddFull(pProfile4B, wax->GetItem(2), kJoinOperation);

	ObjectCollection *pCollection2;

	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pCollection2);
	pCollection2->MethodAdd(oRevolveDef4B);
	CircularPatternFeatures *pCircPatFeat2;
	ft->get_CircularPatternFeatures(&pCircPatFeat2);

	CircularPatternFeature *circFeat2 = pCircPatFeat2->MethodAdd(pCollection2, wax->GetItem(1), true, Kol_Vo_Shar2, "360 deg", true, kIdenticalCompute);


	//Фаска
	EdgeCollection *edgeCollc;

	pInvApp->TransientObjects->raw_CreateEdgeCollection(vtMissing, &edgeCollc);

	SurfaceBody *SurfBodyc;
	SurfaceBodies *SurfBodiesc;

	pPartComDef4->get_SurfaceBodies(&SurfBodiesc);

	SurfBodiesc->get_Item(1, &SurfBodyc);

	Edges *edgesc, *edgesc2, *edgesc3, *edgesc4;

	SurfBodyc->get_Edges(&edgesc);
	SurfBodyc->get_Edges(&edgesc2);
	SurfBodyc->get_Edges(&edgesc3);
	SurfBodyc->get_Edges(&edgesc4);

	Edge *edc, *edc2, *edc3, *edc4;
	edgesc->get_Item(69, &edc);
	edgesc2->get_Item(76, &edc2);
	edgesc3->get_Item(80, &edc3);
	edgesc4->get_Item(74, &edc4);

	edgeCollc->MethodAdd(edc);
	edgeCollc->MethodAdd(edc2);
	edgeCollc->MethodAdd(edc3);
	edgeCollc->MethodAdd(edc4);

	ChamferFeatures *chamFeaturesc;
	ft->get_ChamferFeatures(&chamFeaturesc);

	ChamferFeature *chamFeaturec = chamFeaturesc->MethodAddUsingDistance(edgeCollc, Chamfer, false, false, false);

	pTrans4->MethodEnd();

	///////////////////
	///Кол
	//
	PartDocumentPtr pPartDoc5;
	PartComponentDefinition *pPartComDef5;
	TransientGeometry *pTransGeom5;
	Transaction *pTrans5;
	//
	pPartDoc5 = pInvApp->Documents->MethodAdd(kPartDocumentObject, pInvApp->FileManager->MethodGetTemplateFile(kPartDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true);
	pPartDoc5->DisplayName = _T("Колесо 1");
	//
	pPartDoc5->get_ComponentDefinition(&pPartComDef5);

	pInvApp->get_TransientGeometry(&pTransGeom5);

	pTransManager = pInvApp->GetTransactionManager();
	pTransManager->raw_StartTransaction(CComQIPtr <Document>(pPartDoc5), _T(""), &pTrans5);

	pPartComDef5->get_Sketches(&sketches);
	pPartComDef5->get_Sketches3D(&sketches3D);
	pPartComDef5->get_WorkPlanes(&wp);
	pPartComDef5->get_Features(&ft);
	pPartComDef5->get_WorkAxes(&wax);
	pPartComDef5->get_WorkPoints(&wpt);
	//Колесо 
	
	PlanarSketch *pSketch5;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch5);

	SketchLinePtr lines5[1];
	SketchLines *skLines5;
	SketchCirclePtr circles5[1]; 
	SketchCircles *skCircles5;
	SketchPointPtr point5[4];
	SketchPoints *skPoints5;
	SketchArcPtr arc5[3];
	SketchArcs *skArcs5;
	Profiles *skProfiles5;

	pSketch5->get_SketchCircles(&skCircles5);
	pSketch5->get_SketchPoints(&skPoints5);
	pSketch5->get_SketchLines(&skLines5);
	pSketch5->get_Profiles(&skProfiles5);
	pSketch5->get_SketchArcs(&skArcs5);

	circles5[0] = skCircles5->MethodAddByCenterRadius(pTransGeom5->MethodCreatePoint2d(0, 0), Diam / 2);

	Profile *pProfile5;
	skProfiles5->raw__AddForSolid(&pProfile5);

	PlanarSketch *pSketch6;
	sketches->raw_Add(wp->MethodAddByPlaneAndOffset(wp->GetItem(3), Long2 / 2, true), false, &pSketch6);
	SketchLinePtr lines6[1];
	SketchLines *skLines6;
	SketchCirclePtr circles6[1];
	SketchCircles *skCircles6;
	SketchPointPtr point6[4];
	SketchPoints *skPoints6;
	SketchArcPtr arc6[3];
	SketchArcs *skArcs6;
	Profiles *skProfiles6;

	pSketch6->get_SketchCircles(&skCircles6);
	pSketch6->get_SketchPoints(&skPoints6);
	pSketch6->get_SketchLines(&skLines6);
	pSketch6->get_Profiles(&skProfiles6);
	pSketch6->get_SketchArcs(&skArcs6);

	circles6[0] = skCircles6->MethodAddByCenterRadius(pTransGeom5->MethodCreatePoint2d(0, 0), DiamVerh / 2);

	Profile *pProfile6;
	skProfiles6->raw__AddForSolid(&pProfile6);

	ObjectCollection *pLoftCollection;
	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pLoftCollection);

	pLoftCollection->MethodAdd(pProfile5);
	pLoftCollection->MethodAdd(pProfile6);

	LoftFeatures *ftLoft;
	ft->get_LoftFeatures(&ftLoft);
	LoftFeaturePtr oLoftDef = ftLoft->MethodAdd(ftLoft->MethodCreateLoftDefinition(pLoftCollection, kJoinOperation));

	Profiles *skProfiles5B;
	pSketch5->get_Profiles(&skProfiles5B);

	double k1 = Diam / GlobalKoeff;

	point5[0] = skPoints5->MethodAdd(pTransGeom5->MethodCreatePoint2d((Diam / 2) * cos(PI / 50 / k1), (Diam / 2) * sin(PI / 50 / k1)), false);
	point5[1] = skPoints5->MethodAdd(pTransGeom5->MethodCreatePoint2d((Diam / 2) * cos(-PI / 50 / k1), (Diam / 2) * sin(-PI / 50 / k1)), false);
	point5[2] = skPoints5->MethodAdd(pTransGeom5->MethodCreatePoint2d((Diam / 2 + ZubVisota) * cos(PI / 90 / k1), (Diam / 2 + ZubVisota) * sin(PI / 90 / k1)), false);
	point5[3] = skPoints5->MethodAdd(pTransGeom5->MethodCreatePoint2d((Diam / 2 + ZubVisota) * cos(-PI / 90 / k1), (Diam / 2 + ZubVisota) * sin(-PI / 90 / k1)), false);

	arc5[0] = skArcs5->MethodAddByThreePoints(point5[0], pTransGeom5->MethodCreatePoint2d((Diam / 2 + ZubVisota / 2) * cos(PI / 70 / k1), (Diam / 2 + ZubVisota / 2) * sin(PI / 70 / k1)), point5[2]);
	arc5[1] = skArcs5->MethodAddByThreePoints(point5[1], pTransGeom5->MethodCreatePoint2d((Diam / 2 + ZubVisota / 2) * cos(-PI / 70 / k1), (Diam / 2 + ZubVisota / 2) * sin(-PI / 70 / k1)), point5[3]);
	arc5[2] = skArcs5->MethodAddByCenterStartEndPoint(pTransGeom5->MethodCreatePoint2d(0, 0), point5[0], point5[1], false);
	lines5[0] = skLines5->MethodAddByTwoPoints(point5[2], point5[3]);

	Profile *pProfile5B;
	skProfiles5B->raw__AddForSolid(&pProfile5B);

	Profiles *skProfiles6B;
	pSketch6->get_Profiles(&skProfiles6B);

	double k2 = DiamVerh / GlobalKoeff;

	point6[0] = skPoints6->MethodAdd(pTransGeom5->MethodCreatePoint2d((DiamVerh / 2) * cos(PI / 50 / k2), (DiamVerh / 2) * sin(PI / 50 / k2)), false);
	point6[1] = skPoints6->MethodAdd(pTransGeom5->MethodCreatePoint2d((DiamVerh / 2) * cos(-PI / 50 / k2), (DiamVerh / 2) * sin(-PI / 50 / k2)), false);
	point6[2] = skPoints6->MethodAdd(pTransGeom5->MethodCreatePoint2d((DiamVerh / 2 + ZubVisota) * cos(PI / 90 / k2), (DiamVerh / 2 + ZubVisota) * sin(PI / 90 / k2)), false);
	point6[3] = skPoints6->MethodAdd(pTransGeom5->MethodCreatePoint2d((DiamVerh / 2 + ZubVisota) * cos(-PI / 90 / k2), (DiamVerh / 2 + ZubVisota) * sin(-PI / 90 / k2)), false);

	arc6[0] = skArcs6->MethodAddByThreePoints(point6[0], pTransGeom5->MethodCreatePoint2d((DiamVerh / 2 + ZubVisota / 2) * cos(PI / 70 / k2), (DiamVerh / 2 + ZubVisota / 2) * sin(PI / 70 / k2)), point6[2]);
	arc6[1] = skArcs6->MethodAddByThreePoints(point6[1], pTransGeom5->MethodCreatePoint2d((DiamVerh / 2 + ZubVisota / 2) * cos(-PI / 70 / k2), (DiamVerh / 2 + ZubVisota / 2) * sin(-PI / 70 / k2)), point6[3]);
	arc6[2] = skArcs6->MethodAddByCenterStartEndPoint(pTransGeom5->MethodCreatePoint2d(0, 0), point6[0], point6[1], false);
	lines6[0] = skLines6->MethodAddByTwoPoints(point6[2], point6[3]);
	Profile *pProfile6B;
	skProfiles6B->raw__AddForSolid(&pProfile6B);

	ObjectCollection *pLoftCollection2;
	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pLoftCollection2);

	pLoftCollection2->MethodAdd(pProfile5B);
	pLoftCollection2->MethodAdd(pProfile6B);

	LoftFeatures *ftLoft2;
	ft->get_LoftFeatures(&ftLoft2);
	LoftFeaturePtr oLoftDef2 = ftLoft2->MethodAdd(ftLoft2->MethodCreateLoftDefinition(pLoftCollection2, kJoinOperation));

	ObjectCollection *pCollection3;

	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pCollection3);
	pCollection3->MethodAdd(oLoftDef2);
	CircularPatternFeatures *pCircPatFeat3;
	ft->get_CircularPatternFeatures(&pCircPatFeat3);

	CircularPatternFeature *circFeat3 = pCircPatFeat3->MethodAdd(pCollection3, wax->GetItem(3), true, Kol_vo_Zubov, "360 deg", true, kIdenticalCompute);

	PlanarSketch *pSketch5A;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch5A);

	SketchCirclePtr circles5A[1];
	SketchCircles *skCircles5A;
	Profiles *skProfiles5A;
	pSketch5A->get_SketchCircles(&skCircles5A);
	pSketch5A->get_Profiles(&skProfiles5A);

	circles5A[0] = skCircles5A->MethodAddByCenterRadius(pTransGeom5->MethodCreatePoint2d(0, 0), DiamShest / 2);

	Profile *pProfile5A;
	skProfiles5A->raw__AddForSolid(&pProfile5A);

	ExtrudeFeatures *ftExtrude5A;

	ft->get_ExtrudeFeatures(&ftExtrude5A);

	ExtrudeFeaturePtr oExtrudeDef5A = ftExtrude5A->MethodAddByDistanceExtent(pProfile5A, Long2, kPositiveExtentDirection, kCutOperation);

	


	PlanarSketch *pSketch5C;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch5C);

	SketchCirclePtr circles5C[2];
	SketchCircles *skCircles5C;

	Profiles *skProfiles5C;

	pSketch5C->get_SketchCircles(&skCircles5C);

	pSketch5C->get_Profiles(&skProfiles5C);

	circles5C[0] = skCircles5C->MethodAddByCenterRadius(pTransGeom5->MethodCreatePoint2d(0, 0), DiamShest / 2);
	circles5C[1] = skCircles5C->MethodAddByCenterRadius(pTransGeom5->MethodCreatePoint2d(0, 0), DiamShest / 2 + Long2/2);
	Profile *pProfile5C;
	skProfiles5C->raw__AddForSolid(&pProfile5C);

	ExtrudeFeatures *ftExtrude5C;

	ft->get_ExtrudeFeatures(&ftExtrude5C);

	ExtrudeFeaturePtr oExtrudeDef5C = ftExtrude5C->MethodAddByDistanceExtent(pProfile5C, Long2/2, kNegativeExtentDirection, kJoinOperation);


	//Сопряжение
	EdgeCollection *edgeColle;

	pInvApp->TransientObjects->raw_CreateEdgeCollection(vtMissing, &edgeColle);

	SurfaceBody *SurfBodye;
	SurfaceBodies *SurfBodiese;

	pPartComDef5->get_SurfaceBodies(&SurfBodiese);

	SurfBodiese->get_Item(1, &SurfBodye);

	Edges *edgese;

	SurfBodye->get_Edges(&edgese);


	Edge *ede;;
	edgese->get_Item(2, &ede);


	edgeColle->MethodAdd(ede);

	FilletFeatures *pFilletFte;
	ft->get_FilletFeatures(&pFilletFte);

	FilletFeature *fillFeate = pFilletFte->MethodAddSimple(edgeColle, Fillet, false, false, false, false, false, false); // скругление
	

	pTrans5->MethodEnd();
	///////////////////
	///Шест
	//
	
	

	//
	PartDocumentPtr pPartDoc6;
	PartComponentDefinition *pPartComDef6;
	TransientGeometry *pTransGeom6;
	Transaction *pTrans6;
	//
	pPartDoc6 = pInvApp->Documents->MethodAdd(kPartDocumentObject, pInvApp->FileManager->MethodGetTemplateFile(kPartDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true);
	pPartDoc6->DisplayName = _T("Шестерёнка 2");
	//
	pPartDoc6->get_ComponentDefinition(&pPartComDef6);

	pInvApp->get_TransientGeometry(&pTransGeom6);

	pTransManager = pInvApp->GetTransactionManager();
	pTransManager->raw_StartTransaction(CComQIPtr <Document>(pPartDoc6), _T(""), &pTrans6);

	pPartComDef6->get_Sketches(&sketches);
	pPartComDef6->get_Sketches3D(&sketches3D);
	pPartComDef6->get_WorkPlanes(&wp);
	pPartComDef6->get_Features(&ft);
	pPartComDef6->get_WorkAxes(&wax);
	pPartComDef6->get_WorkPoints(&wpt);
	//Шестерёнка
	PlanarSketch *pSketch7;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch7);

	SketchLinePtr lines7[1];
	SketchLines *skLines7;
	SketchCirclePtr circles7[1];
	SketchCircles *skCircles7;
	SketchPointPtr point7[4];
	SketchPoints *skPoints7;
	SketchArcPtr arc7[3];
	SketchArcs *skArcs7;
	Profiles *skProfiles7;

	pSketch7->get_SketchCircles(&skCircles7);
	pSketch7->get_SketchPoints(&skPoints7);
	pSketch7->get_SketchLines(&skLines7);
	pSketch7->get_Profiles(&skProfiles7);
	pSketch7->get_SketchArcs(&skArcs7);

	circles7[0] = skCircles7->MethodAddByCenterRadius(pTransGeom6->MethodCreatePoint2d(0, 0), Diam2 / 2);

	Profile *pProfile7;
	skProfiles7->raw__AddForSolid(&pProfile7);

	PlanarSketch *pSketch8;
	sketches->raw_Add(wp->MethodAddByPlaneAndOffset(wp->GetItem(3), LongB4, true), false, &pSketch8);
	SketchLinePtr lines8[1];
	SketchLines *skLines8;
	SketchCirclePtr circles8[1];
	SketchCircles *skCircles8;
	SketchPointPtr point8[4];
	SketchPoints *skPoints8;
	SketchArcPtr arc8[3];
	SketchArcs *skArcs8;
	Profiles *skProfiles8;

	pSketch8->get_SketchCircles(&skCircles8);
	pSketch8->get_SketchPoints(&skPoints8);
	pSketch8->get_SketchLines(&skLines8);
	pSketch8->get_Profiles(&skProfiles8);
	pSketch8->get_SketchArcs(&skArcs8);

	circles8[0] = skCircles8->MethodAddByCenterRadius(pTransGeom6->MethodCreatePoint2d(0, 0), DiamVerh2 / 2);

	Profile *pProfile8;
	skProfiles8->raw__AddForSolid(&pProfile8);

	ObjectCollection *pLoftCollection5;
	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pLoftCollection5);

	pLoftCollection5->MethodAdd(pProfile7);
	pLoftCollection5->MethodAdd(pProfile8);

	LoftFeatures *ftLoft5;
	ft->get_LoftFeatures(&ftLoft5);
	LoftFeaturePtr oLoftDef5 = ftLoft5->MethodAdd(ftLoft5->MethodCreateLoftDefinition(pLoftCollection5, kJoinOperation));

	Profiles *skProfiles7B;
	pSketch7->get_Profiles(&skProfiles7B);

	double k3 = Diam2 / GlobalKoeff;


	point7[0] = skPoints7->MethodAdd(pTransGeom6->MethodCreatePoint2d((Diam2 / 2) * cos(PI / 50 / k3), (Diam2 / 2) * sin(PI / 50 / k3)), false);
	point7[1] = skPoints7->MethodAdd(pTransGeom6->MethodCreatePoint2d((Diam2 / 2) * cos(-PI / 50 / k3), (Diam2 / 2) * sin(-PI / 50 / k3)), false);
	point7[2] = skPoints7->MethodAdd(pTransGeom6->MethodCreatePoint2d((Diam2 / 2 + ZubVisota) * cos(PI / 90 / k3), (Diam2 / 2 + ZubVisota) * sin(PI / 90 / k3)), false);
	point7[3] = skPoints7->MethodAdd(pTransGeom6->MethodCreatePoint2d((Diam2 / 2 + ZubVisota) * cos(-PI / 90 / k3), (Diam2 / 2 + ZubVisota) * sin(-PI / 90 / k3)), false);

	arc7[0] = skArcs7->MethodAddByThreePoints(point7[0], pTransGeom6->MethodCreatePoint2d((Diam2 / 2 + ZubVisota / 2) * cos(PI / 70 / k3), (Diam2 / 2 + ZubVisota / 2) * sin(PI / 70 / k3)), point7[2]);
	arc7[1] = skArcs7->MethodAddByThreePoints(point7[1], pTransGeom6->MethodCreatePoint2d((Diam2 / 2 + ZubVisota / 2) * cos(-PI / 70 / k3), (Diam2 / 2 + ZubVisota / 2) * sin(-PI / 70 / k3)), point7[3]);
	arc7[2] = skArcs7->MethodAddByCenterStartEndPoint(pTransGeom6->MethodCreatePoint2d(0, 0), point7[0], point7[1], false);
	lines7[0] = skLines7->MethodAddByTwoPoints(point7[2], point7[3]);

	Profile *pProfile7B;
	skProfiles7B->raw__AddForSolid(&pProfile7B);

	Profiles *skProfiles8B;
	pSketch8->get_Profiles(&skProfiles8B);


	double k4 = DiamVerh2 / GlobalKoeff;

	point8[0] = skPoints8->MethodAdd(pTransGeom6->MethodCreatePoint2d((DiamVerh2 / 2) * cos(PI / 50 / k4), (DiamVerh2 / 2) * sin(PI / 50 / k4)), false);
	point8[1] = skPoints8->MethodAdd(pTransGeom6->MethodCreatePoint2d((DiamVerh2 / 2) * cos(-PI / 50 / k4), (DiamVerh2 / 2) * sin(-PI / 50 / k4)), false);
	point8[2] = skPoints8->MethodAdd(pTransGeom6->MethodCreatePoint2d((DiamVerh2 / 2 + ZubVisota) * cos(PI / 90 / k4), (DiamVerh2 / 2 + ZubVisota) * sin(PI / 90 / k4)), false);
	point8[3] = skPoints8->MethodAdd(pTransGeom6->MethodCreatePoint2d((DiamVerh2 / 2 + ZubVisota) * cos(-PI / 90 / k4), (DiamVerh2 / 2 + ZubVisota) * sin(-PI / 90 / k4)), false);

	arc8[0] = skArcs8->MethodAddByThreePoints(point8[0], pTransGeom6->MethodCreatePoint2d((DiamVerh2 / 2 + ZubVisota / 2) * cos(PI / 70 / k4), (DiamVerh2 / 2 + ZubVisota / 2) * sin(PI / 70 / k4)), point8[2]);
	arc8[1] = skArcs8->MethodAddByThreePoints(point8[1], pTransGeom6->MethodCreatePoint2d((DiamVerh2 / 2 + ZubVisota / 2) * cos(-PI / 70 / k4), (DiamVerh2 / 2 + ZubVisota / 2) * sin(-PI / 70 / k4)), point8[3]);
	arc8[2] = skArcs8->MethodAddByCenterStartEndPoint(pTransGeom6->MethodCreatePoint2d(0, 0), point8[0], point8[1], false);
	lines8[0] = skLines8->MethodAddByTwoPoints(point8[2], point8[3]);
	Profile *pProfile8B;
	skProfiles8B->raw__AddForSolid(&pProfile8B);

	ObjectCollection *pLoftCollection8;
	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pLoftCollection8);

	pLoftCollection8->MethodAdd(pProfile7B);
	pLoftCollection8->MethodAdd(pProfile8B);

	LoftFeatures *ftLoft8;
	ft->get_LoftFeatures(&ftLoft8);
	LoftFeaturePtr oLoftDef8 = ftLoft8->MethodAdd(ftLoft8->MethodCreateLoftDefinition(pLoftCollection8, kJoinOperation));

	ObjectCollection *pCollection9;

	pInvApp->TransientObjects->raw_CreateObjectCollection(vtMissing, &pCollection9);
	pCollection9->MethodAdd(oLoftDef8);
	CircularPatternFeatures *pCircPatFeat9;
	ft->get_CircularPatternFeatures(&pCircPatFeat9);

	CircularPatternFeature *circFeat9 = pCircPatFeat9->MethodAdd(pCollection9, wax->GetItem(3), true, Kol_vo_Zubov2, "360 deg", true, kIdenticalCompute);

	PlanarSketch *pSketch9A;
	sketches->raw_Add(wp->GetItem(3), false, &pSketch9A);

	SketchCirclePtr circles9A[1];
	SketchCircles *skCircles9A;

	Profiles *skProfiles9A;
	pSketch9A->get_SketchCircles(&skCircles9A);
	pSketch9A->get_Profiles(&skProfiles9A);
	circles9A[0] = skCircles9A->MethodAddByCenterRadius(pTransGeom6->MethodCreatePoint2d(0, 0), DiamShest2 / 2);

	Profile *pProfile9A;
	skProfiles9A->raw__AddForSolid(&pProfile9A);

	ExtrudeFeatures *ftExtrude9A;

	ft->get_ExtrudeFeatures(&ftExtrude9A);

	ExtrudeFeaturePtr oExtrudeDef9A = ftExtrude9A->MethodAddByDistanceExtent(pProfile9A, LongB4, kPositiveExtentDirection, kCutOperation);

	pTrans6->MethodEnd();

	//Сохранение деталей
	pPartDoc->MethodSaveAs("D:\\One.ipt", true);
	pPartDoc2->MethodSaveAs("D:\\Two.ipt", true);
	pPartDoc3->MethodSaveAs("D:\\Three.ipt", true);
	pPartDoc4->MethodSaveAs("D:\\Four.ipt", true);
	pPartDoc5->MethodSaveAs("D:\\Five.ipt", true);
	pPartDoc6->MethodSaveAs("D:\\Six.ipt", true);


	//Объявление указателей на сборку
	AssemblyDocumentPtr pAsmDoc;
	AssemblyComponentDefinitionPtr pAsmComDef;
	TransientGeometry *pTransGeomAsm;
	Matrix *oPositionMatrix;
	//Указатели на модели
	ComponentOccurrencePtr Model, Model2, Model3, Model3_2, Model4, Model4_2, Model5, Model6;
	//ОТкрытие сборки
	pAsmDoc = pInvApp->Documents->MethodAdd(kAssemblyDocumentObject, pInvApp->FileManager->MethodGetTemplateFile(kAssemblyDocumentObject, kMetricSystemOfMeasure, kGOST_DraftingStandard), true);
	pAsmDoc->DisplayName = _T("Сборка");
	//Использование компоненатов
	pAsmDoc->get_ComponentDefinition(&pAsmComDef);
	pInvApp->get_TransientGeometry(&pTransGeomAsm);
	pTransGeomAsm->raw_CreateMatrix(&oPositionMatrix);
	//Вставка моделей в сборку
	Model = pAsmDoc->ComponentDefinition->Occurrences->MethodAdd("D:\\One.ipt" , oPositionMatrix);
	Model2 = pAsmDoc->ComponentDefinition->Occurrences->MethodAdd("D:\\Two.ipt", oPositionMatrix);
	Model3 = pAsmDoc->ComponentDefinition->Occurrences->MethodAdd("D:\\Three.ipt", oPositionMatrix);
	Model3_2 = pAsmDoc->ComponentDefinition->Occurrences->MethodAdd("D:\\Three.ipt", oPositionMatrix);
	Model4 = pAsmDoc->ComponentDefinition->Occurrences->MethodAdd("D:\\Four.ipt", oPositionMatrix);
	Model4_2 = pAsmDoc->ComponentDefinition->Occurrences->MethodAdd("D:\\Four.ipt", oPositionMatrix);
	Model5 = pAsmDoc->ComponentDefinition->Occurrences->MethodAdd("D:\\Five.ipt", oPositionMatrix);
	Model6 = pAsmDoc->ComponentDefinition->Occurrences->MethodAdd("D:\\Six.ipt", oPositionMatrix);
	
	// Вал + 2 подшипника
	//Указатели на тело одной модели
	SurfaceBody *SurfBody, *SurfBody2,*SurfBody3, *SurfBody4;
	SurfaceBodies *SurfBodies, *SurfBodies2,*SurfBodies3,*SurfBodies4;
	//Указатели на рёбра
	Edges *oEdges, *oEdges2,*oEdges3,*oEdges4;
	EdgePtr oEdge, oEdge2, oEdge3, oEdge4;
	//Указатель на зависимость
	MateConstraintPtr sPlane, sPlane2;

	//Получение номера тела
	Model->get_SurfaceBodies(&SurfBodies);
	SurfBodies->get_Item(1, &SurfBody);

	Model3->get_SurfaceBodies(&SurfBodies2);
	SurfBodies2->get_Item(1, &SurfBody2);

	Model->get_SurfaceBodies(&SurfBodies3);
	SurfBodies3->get_Item(1, &SurfBody3);

	Model3_2->get_SurfaceBodies(&SurfBodies4);
	SurfBodies4->get_Item(1, &SurfBody4);
	//ПОлучение номера грани
	SurfBody->get_Edges(&oEdges);
	oEdges->get_Item(6, &oEdge);

	SurfBody2->get_Edges(&oEdges2);
	oEdges2->get_Item(1, &oEdge2);

	SurfBody3->get_Edges(&oEdges3);
	oEdges3->get_Item(3, &oEdge3);

	SurfBody4->get_Edges(&oEdges4);
	oEdges4->get_Item(1, &oEdge4);


	//Зависимость (метод вставка двух рёбер)
	sPlane = pAsmComDef->Constraints->MethodAddInsertConstraint(oEdge, oEdge2, true, 0);
	sPlane2 = pAsmComDef->Constraints->MethodAddInsertConstraint(oEdge3, oEdge4, true, 0);

	
	//Вал 2 + 2 подшипника

	//Аналогично первому коду
	SurfaceBody *SurfBodyB, *SurfBodyB2, *SurfBodyB3, *SurfBodyB4;
	SurfaceBodies *SurfBodiesB, *SurfBodiesB2, *SurfBodiesB3, *SurfBodiesB4;

	Edges *oEdgesB, *oEdgesB2, *oEdgesB3, *oEdgesB4;
	EdgePtr oEdgeB, oEdgeB2, oEdgeB3, oEdgeB4;

	MateConstraintPtr sPlaneB, sPlaneB2;

	Model2->get_SurfaceBodies(&SurfBodiesB);
	SurfBodiesB->get_Item(1, &SurfBodyB);

	Model4->get_SurfaceBodies(&SurfBodiesB2);
	SurfBodiesB2->get_Item(1, &SurfBodyB2);

	Model2->get_SurfaceBodies(&SurfBodiesB3);
	SurfBodiesB3->get_Item(1, &SurfBodyB3);

	Model4_2->get_SurfaceBodies(&SurfBodiesB4);
	SurfBodiesB4->get_Item(1, &SurfBodyB4);

	SurfBodyB->get_Edges(&oEdgesB);
	oEdgesB->get_Item(3, &oEdgeB);

	SurfBodyB2->get_Edges(&oEdgesB2);
	oEdgesB2->get_Item(1, &oEdgeB2);

	SurfBodyB3->get_Edges(&oEdgesB3);
	oEdgesB3->get_Item(7, &oEdgeB3);

	SurfBodyB4->get_Edges(&oEdgesB4);
	oEdgesB4->get_Item(1, &oEdgeB4);

	sPlaneB = pAsmComDef->Constraints->MethodAddInsertConstraint(oEdgeB, oEdgeB2, true, 0);
	sPlaneB2 = pAsmComDef->Constraints->MethodAddInsertConstraint(oEdgeB3, oEdgeB4, true, 0);

	
	//Вал + колесо
	SurfaceBody *SurfBodyС, *SurfBodyС2;
	SurfaceBodies *SurfBodiesС, *SurfBodiesС2;

	Edges *oEdgesС, *oEdgesС2;
	EdgePtr oEdgeС, oEdgeС2;

	MateConstraintPtr sPlaneС;

	Model->get_SurfaceBodies(&SurfBodiesС);
	SurfBodiesС->get_Item(1, &SurfBodyС);

	Model5->get_SurfaceBodies(&SurfBodiesС2);
	SurfBodiesС2->get_Item(1, &SurfBodyС2);

	SurfBodyС->get_Edges(&oEdgesС);
	oEdgesС->get_Item(8, &oEdgeС);

	SurfBodyС2->get_Edges(&oEdgesС2);
	oEdgesС2->get_Item(3, &oEdgeС2);

	sPlaneС = pAsmComDef->Constraints->MethodAddInsertConstraint(oEdgeС, oEdgeС2, true, 0);

	//Вал2 + шестеренка
	SurfaceBody *SurfBodyD, *SurfBodyD2;
	SurfaceBodies *SurfBodiesD, *SurfBodiesD2;

	Edges *oEdgesD, *oEdgesD2;
	EdgePtr oEdgeD, oEdgeD2;

	MateConstraintPtr sPlaneD;

	Model2->get_SurfaceBodies(&SurfBodiesD);
	SurfBodiesD->get_Item(1, &SurfBodyD);

	Model6->get_SurfaceBodies(&SurfBodiesD2);
	SurfBodiesD2->get_Item(1, &SurfBodyD2);

	SurfBodyD->get_Edges(&oEdgesD);
	oEdgesD->get_Item(5, &oEdgeD);

	SurfBodyD2->get_Edges(&oEdgesD2);
	oEdgesD2->get_Item(2, &oEdgeD2);

	sPlaneD = pAsmComDef->Constraints->MethodAddInsertConstraint(oEdgeD, oEdgeD2, true, 0);


	//Аналогично предыдущим, только получаем номер грани вместо рёбер
	//Вал1+вал2
	SurfaceBody *SurfBodyF, *SurfBodyF2;
	SurfaceBodies *SurfBodiesF, *SurfBodiesF2;

	Faces *oFacesF, *oFacesF2;
	FacePtr oFaceF, oFaceF2;

	MateConstraintPtr sPlaneF;

	Model->get_SurfaceBodies(&SurfBodiesF);
	SurfBodiesF->get_Item(1, &SurfBodyF);

	Model2->get_SurfaceBodies(&SurfBodiesF2);
	SurfBodiesF2->get_Item(1, &SurfBodyF2);

	SurfBodyF->get_Faces(&oFacesF);
	oFacesF->get_Item(8, &oFaceF);

	SurfBodyF2->get_Faces(&oFacesF2);
	oFacesF2->get_Item(4, &oFaceF2);

	double Distance2 = (DiamVerh - DiamShest) / 2 + 0.1;
	sPlaneF = pAsmComDef->Constraints->MethodAddTangentConstraint(oFaceF, oFaceF2, false, Distance2);

	//Вал1 + Вал2
	SurfaceBody *SurfBodyE, *SurfBodyE2;
	SurfaceBodies *SurfBodiesE, *SurfBodiesE2;

	Faces *oFacesE, *oFacesE2;
	FacePtr oFaceE, oFaceE2;

	MateConstraintPtr sPlaneE;

	Model->get_SurfaceBodies(&SurfBodiesE);
	SurfBodiesE->get_Item(1, &SurfBodyE);

	Model2->get_SurfaceBodies(&SurfBodiesE2);
	SurfBodiesE2->get_Item(1, &SurfBodyE2);

	SurfBodyE->get_Faces(&oFacesE);
	oFacesE->get_Item(9, &oFaceE);

	SurfBodyE2->get_Faces(&oFacesE2);
	oFacesE2->get_Item(5, &oFaceE2);

	double Distance = (Long2 + (DiamVerh2 - DiamShest2) / 2) + 0.1;
	sPlaneE = pAsmComDef->Constraints->MethodAddTangentConstraint(oFaceE, oFaceE2, false, Distance);




	//мм в см
	DiamPod *= 10;
	DiamOsnov *= 10;
	DiamShest *= 10;
	Long1 *= 10;
	Long2 *= 10;
	Long3 *= 10;

	DiamShest2 *= 10;
	DiamPod2 *= 10;
	DiamOsnov2 *= 10;;
	LongB1 *= 10;
	LongB2 *= 10;
	LongB3 *= 10;
	LongB4 *= 10;

	DiamVnesh *= 10;
	DiamShar *= 10;

	DiamVnesh2 *= 10;
	DiamShar2 *= 10;

	Diam *= 10;
	DiamVerh *= 10;
	ZubVisota *= 10;

	Diam2 *= 10;
	DiamVerh2 *= 10;
	ZubVisota2 *= 10;
	//

	//Освобождение указателей для повторного запуска
	if (pTransManager)
		pTransManager.Release();
	if (pInvApp)
		pInvApp.Release();
	if (pPartDoc)
		pPartDoc.Release();
	if (pPartDoc2)
		pPartDoc2.Release();
	if (pPartDoc3)
		pPartDoc3.Release();	
	if (pPartDoc4)
		pPartDoc4.Release();
	if (pPartDoc5)
		pPartDoc5.Release();
	if (pPartDoc6)
		pPartDoc6.Release();
	if (pAsmDoc)
		pAsmDoc.Release();
}