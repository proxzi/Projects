//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Ani.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include <FMX.Edit.hpp>
#include <list>
//---------------------------------------------------------------------------
using std::list;

class Mobile;

class Tfm : public TForm
{
__published:	// IDE-managed Components
	TTabControl *tc;
	TTabItem *menu;
	TTabItem *settings;
	TTabItem *instruction;
	TTabItem *game;
	TButton *buStart;
	TButton *buSettings;
	TRectangle *Rectangle2;
	TRectangle *Rectangle4;
	TRectangle *Rectangle5;
	TRectangle *Rectangle1;
	TRectangle *Rectangle3;
	TRectangle *Rectangle6;
	TRectangle *Rectangle7;
	TRectangle *Rectangle8;
	TRectangle *Rectangle9;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *laAnswer;
	TTimer *delay;
	TTimer *GameTimer;
	TTimer *TimerWait;
	TButton *buSave;
	TLabel *Label10;
	TButton *buIn;
	TButton *buBack;
	TButton *Button1;
	TLabel *Label11;
	TRadioButton *rb1;
	TRadioButton *rb2;
	TRadioButton *rb3;
	TLabel *Label12;
	TFloatAnimation *rdyAnim;
	TLabel *laScore;
	TRectangle *recbackground;
	TRectangle *Rectangle17;
	TGradientAnimation *ga2;
	TProgressBar *pg;
	TButton *buBackmenu;
	TRectangle *Rectangle11;
	TGradientAnimation *ga3;
	TRectangle *Rectangle12;
	TGradientAnimation *ga1;
	TTimer *TimeUp;
	TStyleBook *StyleBook1;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TGradientAnimation *GradientAnimation1;
	TRectangle *Rectangle13;
	TLabel *Label13;
	TRectangle *Rectangle10;
	TLabel *Label14;
	TRectangle *Rectangle15;
	TLabel *Label15;
	TImageList *imList;
	TGlyph *gl;
	TFloatAnimation *keyAnim;
	TEdit *eName;
	TLabel *laName;
	TButton *buAbout;
	TLabel *laAttempt;
	TTimer *renderMobile;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall buStartClick(TObject *Sender);
	void __fastcall RectClick(TObject *Sender);
	void __fastcall delayTimer(TObject *Sender);
	void __fastcall GameTimerTimer(TObject *Sender);
	void __fastcall TimerWaitTimer(TObject *Sender);
	void __fastcall buSettingsClick(TObject *Sender);
	void __fastcall buInClick(TObject *Sender);
	void __fastcall buBackClick(TObject *Sender);
	void __fastcall buSaveClick(TObject *Sender);
	void __fastcall buBackmenuClick(TObject *Sender);
	void __fastcall TimeUpTimer(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);
	void __fastcall renderMobileTimer(TObject *Sender);



private:	// User declarations
    list<Mobile*>mobiles;
public:		// User declarations
	UnicodeString str;
    UnicodeString Answer;
	TRectangle * RectGlobal;
	int Repeat;
	int RepeatAnswer;
	int up;
	int Score;
    int Attempt;
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------

class Mobile{

public:
	Mobile(int size, float x, float y, TComponent * parent, TImageList * il);
	TGlyph * moGl;
	int speed;
private:

};
#endif
