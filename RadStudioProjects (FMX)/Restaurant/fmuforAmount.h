//---------------------------------------------------------------------------

#ifndef fmuforAmountH
#define fmuforAmountH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class Tffa : public TForm
{
__published:	// IDE-managed Components
	TEdit *edAmount;
	TLabel *Label1;
	TButton *btnokey;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnokeyClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tffa(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tffa *ffa;
//---------------------------------------------------------------------------
#endif
