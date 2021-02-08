//---------------------------------------------------------------------------

#ifndef FMMenuH
#define FMMenuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class TmenuForm : public TForm
{
__published:	// IDE-managed Components
	TButton *btnStart;
	TLabel *lblShowFieldSize;
	TTrackBar *trbChangeFieldSize;
	TRadioButton *rbPlayer;
	TRadioButton *rbClick;
	TStyleBook *sbAndroid;
	TStyleBook *sbWin;
	TLayout *ltradbtn1;
	TLayout *ltradbtn2;
	void __fastcall trbChangeFieldSizeChange(TObject *Sender);
	void __fastcall btnStartClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	int fieldNumber;
public:		// User declarations
	__fastcall TmenuForm(TComponent* Owner);
	int getFieldNumber();
    bool getPlayerStatus();
};
//---------------------------------------------------------------------------
extern PACKAGE TmenuForm *menuForm;
//---------------------------------------------------------------------------
#endif
