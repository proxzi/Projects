//---------------------------------------------------------------------------

#include <fmx.h>
#include <algorithm>
#pragma hdrstop

#include "fmu.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfm *fm;
//---------------------------------------------------------------------------
using namespace std;
typedef std::list<Bubble*>::iterator buIt;

UnicodeString txt(char * str, int n)
{
	return Format(str, ARRAYOFCONST((n)));
}

__fastcall Tfm::Tfm(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->TabPosition = TTabPosition::None;
	tc->ActiveTab = start;

	colorList[cb->ListItems[0]->Text] = claRed;
	colorList[cb->ListItems[1]->Text] = claBlue;
	colorList[cb->ListItems[2]->Text] = claBlueviolet;
}
//---------------------------------------------------------------------------

Bubble::Bubble(int size, float x, float y, TComponent * parent)
	: me(new TCircle(NULL)){
	me->Parent = (TFmxObject*)parent;
	me->Size->Height = size;
	me->Size->Width = size;
	me->Position->X = x;
	me->Position->Y = y;
	me->HitTest = false;
}
Bubble::~Bubble(){
}

void __fastcall Tfm::renderTimer(TObject *Sender)
{
	for (buIt bu = bubbles.begin(); bu != bubbles.end(); ++bu) {
		(*bu)->me->Position->Y -= (*bu)->speed;
		laScore->BringToFront();
		laTime->BringToFront();
		if((*bu)->me->Position->Y <= -(*bu)->me->Size->Height) {
			(*bu)->me->Size->Height = (int)RandomRange(30,80);
			(*bu)->me->Size->Width = (*bu)->me->Size->Height;
			(*bu)->me->Position->Y = Height;
			(*bu)->speed = (int)RandomRange(4,8);
			(*bu)->me->Position->X = (float)Random(Width - (*bu)->me->Size->Width);
			 (*bu)->me->Fill->Color = colorList[cb->ListItems[(int)Random(3)]->Text];
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfm::toHitBubble(TObject *Sender)
{

	TCircle *currentCircle = (TCircle *)Sender;
	//TColor temp = ;
	if(currentCircle->Fill->Color == currentColor) {
		currentCircle->Size->Height = (int)RandomRange(30,80);
		currentCircle->Size->Width = currentCircle->Size->Height;
		currentCircle->Position->Y = Height;
		currentCircle->Position->X = (float)Random(Width - currentCircle->Size->Width);
		laScore->Text = txt("Счет: %d", ++Score);
	}
	else {
	--Score ;

		if (Score < 0) {
			Score = 0;
		}
		laScore->Text = txt("Счет: %d", Score);
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfm::buStartClick(TObject *Sender)
{
	tc->ActiveTab = game;
	Time->Enabled = true;
	render->Enabled = true;
	currentColor = colorList[cb->ListItems[cb->ItemIndex]->Text];
	ly->Visible = true;
	for (int i = 0; i < 20; i++) {
		int Size_b = (int)RandomRange(30,80);
		bubbles.push_back(new Bubble(Size_b,(float)Random(Width - Size_b),
		Height,ly));
		buIt it= bubbles.end();
		(*(--it))->me->OnClick = toHitBubble;
		(*(it))->me->HitTest = true;
        int tag = 0;
		(*(it))->me->Tag = tag;
		(*it)->me->Fill->Color = colorList[cb->ListItems[(int)Random(3)]->Text];
		(*(it))->speed = (int)RandomRange(4,8);
		tag++;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfm::TimeTimer(TObject *Sender)
{
	laTime->Text = txt("Время: %d", ++time);
	if (time == 30) {
		Time->Enabled = false;
		render->Enabled = false;
		ShowMessage(txt("Вы набрали : %d очков", Score));
		tc->ActiveTab = start;
		for (buIt bu = bubbles.begin(); bu != bubbles.end(); ++bu) {
            (*bu)->me->Position->Y = Height;
		}
		laTime->Text = "Время: 0";
		laScore->Text = "Счет: 0";
		time = 0;
		Score = 0;
	}
}
//---------------------------------------------------------------------------






