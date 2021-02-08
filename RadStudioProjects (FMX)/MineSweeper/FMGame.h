//---------------------------------------------------------------------------

#ifndef FMGameH
#define FMGameH

#include "globaloptions.h"
#include "gamelogic.h"
//---------------------------------------------------------------------------
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Classes.hpp>

#include <FMX.ExtCtrls.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
class TgameForm : public TForm
{
__published:	// IDE-managed Components
	TImage *imCity;
	TImage *imagePlayer;
	TImageList *imageCollection;
	TButton *btnMenu;
	TRadioButton *rbOpen;
	TRadioButton *rbFlag;
	TLayout *ltRadBtn;
	TLayout *ltField;
	TStyleBook *sbAndroid;
	TStyleBook *sbWin;
	TLabel *laMinesCount;
	TToolBar *tbMenu;
	TButton *buInstruction;
	TLayout *ltGame;
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnMenuClick(TObject *Sender);

	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buInstructionClick(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall ltGameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);

private:	// User declarations
	GameLogic * game;
	ms::TOptions options;
    void checkSize();
public:		// User declarations
	__fastcall TgameForm(TComponent* Owner);
	__fastcall ~TgameForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TgameForm *gameForm;
//---------------------------------------------------------------------------
#endif
