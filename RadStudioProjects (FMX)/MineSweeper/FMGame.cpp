// ---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "FMGame.h"
#include "FMMenu.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TgameForm *gameForm;

// ---------------------------------------------------------------------------
__fastcall TgameForm::TgameForm(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
__fastcall TgameForm::~TgameForm() {
}

// ---------------------------------------------------------------------------
void __fastcall TgameForm::FormShow(TObject *Sender) {

	if (game != nullptr) {
		delete game;
		ltGame->DestroyComponents();
	}

	menuForm->Hide();

	options.cellsWidth = options.cellsHeight = menuForm->getFieldNumber();
	options.cellsCount = options.cellsWidth * options.cellsHeight;

	options.pLayout = ltGame;
	options.parent = this;
	options.pPlayer = imagePlayer;
	options.pImageList = imageCollection;

    options.pMinesCount = laMinesCount;

	options.isPlayerActive = menuForm->getPlayerStatus();
	buInstruction->Visible = options.isPlayerActive;

	checkSize();
	game = new GameLogic(options);

	imCity->SendToBack();
}

void TgameForm::checkSize()
{
	float Length = (ltField->Height < ltField->Width) ? ltField->Height : ltField->Width;

	options.globalHeight = Length;
	options.globalWidth = Length;
	options.cellSize = Length / options.cellsHeight;
}
// ---------------------------------------------------------------------------
void __fastcall TgameForm::FormClose(TObject *Sender, TCloseAction &Action) {
	menuForm->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TgameForm::btnMenuClick(TObject *Sender) {
	Hide();
}

// ---------------------------------------------------------------------------
void __fastcall TgameForm::FormResize(TObject *Sender) {
	if (game != nullptr) {
		checkSize();
		game->resize(options);
	}
}

// ---------------------------------------------------------------------------

void __fastcall TgameForm::FormKeyDown(TObject *Sender, WORD &Key,
	System::WideChar &KeyChar, TShiftState Shift) {
#ifdef _WIN32
	if (options.isPlayerActive) {
		game->render(Key, KeyChar);
	}
#endif
}

// ---------------------------------------------------------------------------
void __fastcall TgameForm::FormCreate(TObject *Sender) {
#ifdef _WIN32
	StyleBook = sbWin;
	rbFlag->Visible = false;
	rbOpen->Visible = false;
#else
	StyleBook = sbAndroid;
	laI->Visible = false;
#endif
}
// ---------------------------------------------------------------------------

void __fastcall TgameForm::buInstructionClick(TObject *Sender)
{
	ShowMessage(L"WASD(↑←↓→) = Ходьба\nShift = Флаг\nCtrl = Открыть");
}
//---------------------------------------------------------------------------

void __fastcall TgameForm::FormHide(TObject *Sender)
{
	menuForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TgameForm::ltGameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y)
{
	if (!options.isPlayerActive) {

		using Mode = GameLogic::ClickMode;

		Mode mode;

#ifdef _WIN32
		mode = (Button == TMouseButton::mbRight ? Mode::Flag : Mode::Click);
#else
		mode = (rbFlag->IsChecked ? Mode::Flag : Mode::Click);
#endif
		game->click(X, Y, mode);
	}
}
//---------------------------------------------------------------------------

