//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
#include <deque>
#include <list>
#include <vector>
#include <map>
using std::list;

class Bubble;

class Tfm : public TForm
{
__published:	// IDE-managed Components
	TLayout *ly;
	TTimer *render;
	TTabControl *tc;
	TTabItem *start;
	TTabItem *game;
	TButton *buStart;
	TLabel *laScore;
	TLabel *laTime;
	TTimer *Time;
	TLabel *Label1;
	TComboBox *cb;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall renderTimer(TObject *Sender);
	void __fastcall buStartClick(TObject *Sender);
	void __fastcall TimeTimer(TObject *Sender);

private:	// User declarations
   	void __fastcall toHitBubble(TObject *Sender);
	list<Bubble*>bubbles;
	std::map < UnicodeString , TColor > colorList;
public:		// User declarations
	int Score;
	int time;
	TColor currentColor;

	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
class Bubble{
public:
	Bubble(int size, float x, float y, TComponent * parent);
	~Bubble();
	float x();
	float y();
	void setX(float x);
	void setY(float y);
	TCircle * me;
    int speed;

private:

};
#endif
