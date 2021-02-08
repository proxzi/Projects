//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TButton *buYes;
	TButton *buNo;
	TToolBar *ToolBar1;
	TButton *buReset;
	TRectangle *Rectangle1;
	TRectangle *Rectangle2;
	TButton *buAbout;
	TLabel *laCorrect;
	TLabel *laWrong;
	TLabel *laCode;
	TGridPanelLayout *GridPanelLayout1;
	TGridPanelLayout *GridPanelLayout2;
	TFloatAnimation *FloatAnimation1;
	TStyleBook *StyleBook1;
	void __fastcall buResetClick(TObject *Sender);
	void __fastcall buYesClick(TObject *Sender);
	void __fastcall buNoClick(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	int FCountCorrect;
	int FCountWrong;
	bool FAnswerCorrect;
	void DoReset();
	void DoContinue();
    void DoAnswer(bool aValue);

public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
