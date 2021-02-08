//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ImgList.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.ImageList.hpp>
#include <FMX.Colors.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *tb;
	TButton *buClear;
	TButton *buNewImage;
	TButton *buAbout;
	TToolBar *tbOptions;
	TTrackBar *trRotation;
	TButton *buToFront;
	TButton *buToBack;
	TButton *buDelete;
	TToolBar *tbImage;
	TButton *buPrev;
	TButton *buNext;
	TButton *buRND;
	TImageList *il;
	TLayout *ly;
	TToolBar *tbRect;
	TComboColorBox *ComboColorBoxRect;
	TTrackBar *trRectRadius;
	TButton *buNewRect;
	TButton *buLabel;
	void __fastcall SelectionAllMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buToFrontClick(TObject *Sender);
	void __fastcall buToBackClick(TObject *Sender);
	void __fastcall trRotationChange(TObject *Sender);
	void __fastcall buRNDClick(TObject *Sender);
	void __fastcall buPrevClick(TObject *Sender);
	void __fastcall buNextClick(TObject *Sender);
	void __fastcall buNewImageClick(TObject *Sender);
	void __fastcall buDeleteClick(TObject *Sender);
	void __fastcall ComboColorBoxRectChange(TObject *Sender);
	void __fastcall trRectRadiusChange(TObject *Sender);
	void __fastcall buClearClick(TObject *Sender);
	void __fastcall buNewRectClick(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall buLabelClick(TObject *Sender);
private:	// User declarations
	TSelection * FSel;
	void SelectionAll(TObject *Sender);
public:		// User declarations


	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
