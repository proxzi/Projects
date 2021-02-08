// CAcCtrl.h: объ€вление классов-оболочек дл€ элементов управлени€ ActiveX, созданных при помощи Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CModelViewCtrl

class CModelViewCtrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CModelViewCtrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x4E871D32, 0x203E, 0x4777, { 0xB4, 0x2A, 0x45, 0x1F, 0xC1, 0xB2, 0xFC, 0x90 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// јтрибуты
public:

// ќперации
public:

	CString GetSourcePath()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long PutSourcePath(LPCTSTR bstrDWGFileFullPath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDWGFileFullPath);
		return result;
	}
	void Plot()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Plot_Preview()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ViewPlotDetails()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long PublishForMarkup(LPCTSTR bstrDWFFileFullPath, short nSpace)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDWFFileFullPath, nSpace);
		return result;
	}
	void Publish()
	{
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ViewPublishDetails()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Drawing_Properties()
	{
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_Realtime()
	{
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_Previous()
	{
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_Window()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_Dynamic()
	{
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_Center()
	{
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_In()
	{
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_Out()
	{
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_All()
	{
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Zoom_Extents()
	{
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Pan_Realtime()
	{
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Pan_Point()
	{
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Named_Views()
	{
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void View_3D_Orbit()
	{
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Shade_2D_Wireframe()
	{
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Shade_3D_Wireframe()
	{
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Shade_Hidden()
	{
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Shade_Flat_Shaded()
	{
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Shade_Gourand_Shaded()
	{
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Shade_Flat_Shaded_Edges_On()
	{
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Shade_Gourand_Shaded_Edges_On()
	{
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void callBackImageResolve(LPCTSTR InParentFilename, LPCTSTR InEmbeddedName, BSTR * OutFilename, long * eCode)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_PBSTR VTS_PI4 ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, InParentFilename, InEmbeddedName, OutFilename, eCode);
	}
	void callBackFileResolve(LPCTSTR InParentFilename, LPCTSTR InEmbeddedName, BSTR * OutFilename, long * eCode)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_PBSTR VTS_PI4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, InParentFilename, InEmbeddedName, OutFilename, eCode);
	}
	void Layer_Properties_Manager()
	{
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Options()
	{
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Help()
	{
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_ActiveSheet()
	{
		CString result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ActiveSheet(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL CheckAutocadActiveState()
	{
		BOOL result;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void _Deactivate()
	{
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long SilentPublish(VARIANT * pArraybstrDWGFileFullPath)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pArraybstrDWGFileFullPath);
		return result;
	}
	void VisualStyle_2D_Wireframe()
	{
		InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void VisualStyle_3D_Wireframe()
	{
		InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void VisualStyle_Hidden()
	{
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void VisualStyle_Realistic()
	{
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void VisualStyle_Conceptual()
	{
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetPc3File(LPCTSTR pc3File)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pc3File);
	}
	void SetProd(LPCTSTR rclsid)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, rclsid);
	}


};
