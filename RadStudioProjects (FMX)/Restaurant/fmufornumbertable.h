//---------------------------------------------------------------------------

#ifndef fmufornumbertableH
#define fmufornumbertableH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class Tffnt : public TForm
{
__published:	// IDE-managed Components
	TEdit *edAmount;
	TLabel *Label1;
	TButton *btnokey;
	TLabel *labellll;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnokeyClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tffnt(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tffnt *ffnt;
//---------------------------------------------------------------------------
#endif
