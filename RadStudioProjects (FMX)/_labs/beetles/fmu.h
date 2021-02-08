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
#include <FMX.Objects.hpp>
#include <FMX.TabControl.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TButton *Player_1;
	TButton *Player_2;
	TLabel *Label1;
	TGridPanelLayout *GridPanelLayout2;
	TImage *Image1;
	TImage *Image2;
	TGridPanelLayout *GridPanelLayout3;
	TImage *I_p1;
	TImage *I_p2;
	TGridPanelLayout *GridPanelLayout1;
	TTabControl *tc;
	TTabItem *Start;
	TTabItem *Game;
	TButton *Button1;
	void __fastcall Player_1Click(TObject *Sender);
	void __fastcall Player_2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	void Check();
	void Reset();
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
