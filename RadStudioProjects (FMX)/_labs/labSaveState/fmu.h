//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TTabControl *TabControl1;
	TTabItem *TabItem1;
	TTabItem *TabItem2;
	TDateEdit *DateEdit1;
	TTimeEdit *TimeEdit1;
	TTrackBar *TrackBar1;
	TSwitch *Switch1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormSaveState(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
