//---------------------------------------------------------------------------

#ifndef labtimeH
#define labtimeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo;
	TButton *Bustart;
	TButton *Bustop;
	TLabel *Latime;
	TTimer *Tm;
	void __fastcall BustartClick(TObject *Sender);
	void __fastcall BustopClick(TObject *Sender);
	void __fastcall TmTimer(TObject *Sender);
private:	// User declarations
	TDateTime FTimeStart;
public:		// User declarations
	int t;
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
