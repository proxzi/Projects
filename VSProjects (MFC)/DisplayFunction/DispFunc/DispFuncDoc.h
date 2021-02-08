
// DispFuncDoc.h : интерфейс класса CDispFuncDoc
//


#pragma once


#define FirstSize 40
#define SecondSize FirstSize*10

class CDispFuncDoc : public CDocument
{
protected: // создать только из сериализации
	CDispFuncDoc();
	DECLARE_DYNCREATE(CDispFuncDoc)

// Атрибуты
public:
	// 1
	CArray<double, double>m_cPointX;
	CArray<double, double>m_cPointY;
	double * m_dPointX;
	double * m_dPointY;
	double * m_dLagrangeX;
	double * m_dLagrangeY;

	double Xmax=0, Ymax = 0;
	double Xmin = 0, Ymin = 0;
	void GetMinMax();

	void GetCircle();
	double CalcFunR(double r, double x, double y);
	double m_dDocStep;
	// 2
	int m_iNum = FirstSize;
	int m_iLaNum = SecondSize;
	double FirstPoint = -20;
	double m_dStep = 1;
	double m_dLaStep = 0.1;
	double m_dX[FirstSize];
	double m_dY[FirstSize];
	
	// 3
	int m_iOriginHorizontal = 0;
	int m_iOriginVertical = 0;
	//4
	CString m_CInputSTRView;
	double Fonct(CString Cstr, double x);
	// 5
	COLORREF m_CPointColor = RGB(0, 255, 0);
	COLORREF m_CLineColor = RGB(255, 0, 0);
	//6
	int m_iDocChose;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CDispFuncDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnSetparam();
	afx_msg void OnForinsertfunction();
	
	double m_dCoordCenterX;
	double m_dCoordCenterY;
	double m_dCoordRadius;
	int m_ipsD = 3;
	int m_ilsD = 1;
};
