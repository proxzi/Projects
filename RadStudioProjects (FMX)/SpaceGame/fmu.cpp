// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
#include <windows.h>

// #include <GIFimg.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfm *fm;

UnicodeString txt(char * str, int n)
{
	return Format(str, ARRAYOFCONST((n)));
}

typedef std::list<Enemy*>::iterator enIt;
typedef std::list<Shot*>::iterator shIt;
typedef std::list<Upgrade*>::iterator upIt;

int since = 500;
int to = 1500;
int timerIntervalShoot = RandomRange(since, to);

// ---------------------------------------------------------------------------
__fastcall Tfm::Tfm(TComponent* Owner) : TForm(Owner), count(0) {
		state = UnClicked;
		countVisibleEnemies = 0;
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::reMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, float X, float Y) {
    if (X >= space->Position->X && X <= (space->Position->X + space->Width)
			&& Y >= space->Position->Y && Y <= (space->Position->Y + space->Height)
			&& state == UnClicked) {
			state = Clicked;
			stepX = X - space->Position->X;
			stepY = Y - space->Position->Y;
		}

}
// ---------------------------------------------------------------------------

void __fastcall Tfm::reMouseMove(TObject *Sender, TShiftState Shift, float X,
	float Y)

{
	 if (state == Clicked) {
			space->Position->X = X - stepX;
			space->Position->Y = Y - stepY;
		}
		posX->Text = X;
		posY->Text = Y;

}
// ---------------------------------------------------------------------------

void __fastcall Tfm::reMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, float X, float Y) {
	state = UnClicked;

	//
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::FormCreate(TObject *Sender) {
	tc->TabPosition = TTabPosition::None;
	tc->ActiveTab = Start;
	re->Visible = true;
	level = 1;

}
// ---------------------------------------------------------------------------

void __fastcall Tfm::renderTimer(TObject *Sender) {


	showlinesize->Text = enemies.size();
	float speedY = 2.0f;
	float speedX = 5.0f;
	if (state == Clicked) {
		if (upgradelevel == 1) {

			if (shotRecharge == false) {
				lines.push_back(new Shot(0, 1, 20,
					space->Position->X + space->Width / 2.0f,
					space->Position->Y - 20, new TLine(NULL)));

				shotRecharge = true;
				timerShotRecharge->Enabled = true;
			}

		}
		else if (upgradelevel == 2) {

			shIt it;
			if (shotRecharge == false) {
				lines.push_back(new Shot(0, 1, 20,
					space->Position->X + space->Width / 2.0f + 15.0f,
					space->Position->Y - 20, new TLine(NULL)));

				it = lines.end();
				--it;
				((TLine *)(*it)->get())->RotationAngle = 20.0f;

				lines.push_back(new Shot(0, 1, 20,
					space->Position->X + space->Width / 2.0f,
					space->Position->Y - 20, new TLine(NULL)));

				lines.push_back(new Shot(0, 1, 20,
					space->Position->X + space->Width / 2.0f - 15.0f,
					space->Position->Y - 20, new TLine(NULL)));

				it = lines.end();
				--it;
				((TLine*)(*it)->get())->RotationAngle = -20.0f;

				shotRecharge = true;
				timerShotRecharge->Enabled = true;
			}

		}

	}
	//////////////////Shot/////////////////
	float speedShotY = 10.0f;
	float speedShotX = 5.0f;

	if (upgradelevel == 1) {
		timerUpgrade->Enabled = true;
		for (shIt it = lines.begin(); it != lines.end(); ++it) {
			(*it)->setY((*it)->y() - speedShotY);

			if ((*it)->y() <= -20) {
				delete *it;
				lines.remove(*it);
			}
		}
	}

	if (upgradelevel == 2) {
		for (shIt it = lines.begin(); it != lines.end(); ++it) {

			(*it)->setY((*it)->y() - speedShotY);

			if (((TLine*)(*it)->get())->RotationAngle == -20.0f) {
				(*it)->setX((*it)->x() - speedShotX);
			}
			else if (((TLine*)(*it)->get())->RotationAngle == 20.0f) {
				(*it)->setX((*it)->x() + speedShotX);
			}
			if ((*it)->y() <= -20 || (*it)->x() >= Width || (*it)->x() <= 0) {
				delete *it;
				lines.remove(*it);
			}
		}
	}

	//////////////////ENEMY Shot/////////////////
	float enemyShotSpeedY = 7.0f;
	for (shIt it = circles.begin(); it != circles.end(); ++it) {

		(*it)->setY((*it)->y() + enemyShotSpeedY);
		(*it)->setX((*it)->x() + 4 * (*it)->direction);

		if ((*it)->y() <= -20) {
			delete *it;
			circles.remove(*it);
		}

		if (HPLine->Value != 0) {
			if ((*it)->x() >= space->Position->X && (*it)->x() <=
				(space->Position->X + space->Width) && (*it)->y() >=
				space->Position->Y && (*it)->y() <=
				(space->Position->Y + space->Height)) {
				HPLine->Value -= 10;
				upgradelevel = 1;
				delete *it;
				circles.remove(*it);
			}
		}
	}

	///////////////ENEMY/////////////////////
	for (enIt enemy = enemies.begin(); enemy != enemies.end();) {

		if ((*enemy)->isHide() == true) {
			++enemy;
			continue;
		}

		for (shIt line = lines.begin(); line != lines.end(); ++line) {

			if ((*line)->x() >= (*enemy)->x() && (*line)->x() <= (*enemy)->x() +
				(*enemy)->w() && (*line)->y() >= (*enemy)->y() && (*line)->y()
				<= (*enemy)->y() + (*enemy)->h() - 20) {
				delete *line;
				lines.remove(*line);
				(*enemy)->setOpacity((*enemy)->opacity() - 0.2f);

				if ((*enemy)->opacity() <= 0.1f) {
					enIt tmp = enemy;
					++enemy;
					--countVisibleEnemies;
					laCount->Text = txt("Î÷êè: %d", ++count);
					delete *tmp;
					enemies.remove(*tmp);
					break;
				}
			}
		}

		if (enemy != enemies.end()) {

			if ((*enemy)->status() == Enemy::Up) {
				(*enemy)->setRand(RandomRange(200, 400));

				if ((*enemy)->y() >= (*enemy)->meRand()) {
					(*enemy)->setStatus(Enemy::Down);
				}

				(*enemy)->setY((*enemy)->y() + speedY);
			}

			else if ((*enemy)->status() == Enemy::Down) {
				(*enemy)->setRand(RandomRange(0, 70));

				if ((*enemy)->y() <= (*enemy)->meRand()) {
					(*enemy)->setStatus(Enemy::Up);
				}

				(*enemy)->setY((*enemy)->y() - speedY);
			}

			if ((*enemy)->x() <= 0) {
				(*enemy)->setSpeed(speedX);
				(*enemy)->setX(0);
			}
			else if ((*enemy)->x() >= (Width - (*enemy)->w())) {
				(*enemy)->setSpeed(-speedX);
				(*enemy)->setX(Width - (*enemy)->get()->Size->Width);
			}

			(*enemy)->setX((*enemy)->x() + (*enemy)->speed());

			++enemy;
		}
	}

	//////////////////Upgrade////////////////
	if (upgradelevel < 2) {
		if (upgrades.size() >= 1) {
			for (upIt up = upgrades.begin(); up != upgrades.end(); ++up) {
				(*up)->upI->Position->Y += 5;

				if (((*up)->y() >= Height + (*up)->upI->Size->Height)) {
					delete *up;
					upgrades.remove(*up);
				}

				else if ((((*up)->x() >= space->Position->X && (*up)->x() <=
					space->Position->X + space->Size->Width) && (((*up)->y() <=
					space->Position->Y + space->Size->Height && (*up)->y() >=
					space->Position->Y) || ((*up)->y() + (*up)->sizeH() >=
					space->Position->Y && (*up)->y() + (*up)->sizeH() <=
					space->Position->Y + space->Size->Height)))
					// ---------
					|| (((*up)->x() + (*up)->sizeW() >=
					space->Position->X && (*up)->x() + (*up)->sizeW() <=
					space->Position->X + space->Size->Width) && ((*up)->y() +
					(*up)->sizeH() >= space->Position->Y && (*up)->y() +
					(*up)->sizeH() <= space->Position->Y +
					space->Size->Height))) {

					delete *up;
					upgrades.remove(*up);

					if (upgradelevel == 1) {
						upgradelevel += 1;
					}
				}
			}

		}
	}

	//////////////// CHECK LEVEL ///////////////

	if (enemies.size() == 0) {
		timerShowEnemy->Enabled = true;
		enemyShotSpeedY += 0.5f;
		since -= 20;
		to -= 150;
		timerIntervalShoot = RandomRange(since, to);
		countkills += 5;
		int rN[] {
			-50, Width + 50
		};
		for (unsigned i = 0; i < countkills; ++i) {
			enemies.push_back(new Enemy(1.0, 50, 50, rN[RandomRange(0, 2)],
				RandomRange(0, Height * 0.5f - 100), imlist));
			enIt it = enemies.end();
			--it;
			(*it)->hide();
			if ((*it)->get()->Position->Y <= Height / 0.4f)
				(*it)->setStatus(Enemy::Up);
			else if ((*it)->get()->Position->Y <= Height / 0.4f)
				(*it)->setStatus(Enemy::Down);
		}

		last = enemies.begin();

	}
	//// new Game ////
	if (HPLine->Value == 0) {
		HPLine->Value = 100;
		timerShowEnemy->Enabled = false;
		timerUpgrade->Enabled = false;
		timerEnemyShoot->Enabled = false;
		timerShotRecharge->Enabled = false;


		for (enIt clear = enemies.begin(); clear != enemies.end(); ++clear) {

			delete *clear;
			enemies.remove(*clear);
		}
		for (shIt clear = lines.begin(); clear != lines.end(); ++clear) {

			delete *clear;
			lines.remove(*clear);
		}
		for (upIt clear = upgrades.begin(); clear != upgrades.end(); ++clear) {

			delete *clear;
			upgrades.remove(*clear);
		}
		for (shIt clear = circles.begin(); clear != circles.end(); ++clear) {

			delete *clear;
			circles.remove(*clear);
		}

		state = UnClicked;
		fireAnim->Enabled = true;
		tc->ActiveTab = Start;
		upgradelevel = 1;
		render->Enabled = false;
		ShowMessage(L"Êîíåö èãðû");
	}
}

void __fastcall Tfm::timerShowEnemyTimer(TObject * Sender) {

	(*last)->show();

	if ((*last)->x() <= Height * 0.25) {
		(*last)->setStatus(Enemy::Up);
	}
	else if ((*last)->x() >= Height * 0.25) {
		(*last)->setStatus(Enemy::Down);
	}

	last++;
	countVisibleEnemies++;

	if (last == enemies.end()) {
		timerShowEnemy->Enabled = false;
	}

	if (countVisibleEnemies > 0) {
		timerEnemyShoot->Enabled = true;
	}
}

// ---------------------------------------------------------------------------
void __fastcall Tfm::timerEnemyShootTimer(TObject * Sender) {
	if (countVisibleEnemies == 0) {
		timerEnemyShoot->Enabled = false;
		return;
	}

	timerEnemyShoot->Interval = timerIntervalShoot;

	int choseEnemy = RandomRange(0, countVisibleEnemies);

	enIt oneEnemy = enemies.begin();
	while (choseEnemy--)
		++oneEnemy;

	if (oneEnemy != enemies.end())
		circles.push_back(new Shot(0, 10, 10,
		(*oneEnemy)->x() + (*oneEnemy)->w() / 2.0f,
		(*oneEnemy)->y() + (*oneEnemy)->h(), new TCircle(NULL)));

	shIt circle = circles.end();
	--circle;
	(*circle)->direction = (space->Position->X - (*circle)->x()) /
		(space->Position->Y - (*circle)->y());

}
// ---------------------------------------------------------------------------

void __fastcall Tfm::timerShotRechargeTimer(TObject * Sender) {
	shotRecharge = false;
	timerShotRecharge->Enabled = false;
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::timerUpgradeTimer(TObject *Sender) {
	if (upgradelevel == 2) {
		timerUpgrade->Enabled = false;

	}
	else if (upgrades.size() == 0 && timerUpgrade->Enabled == true) {
		upgrades.push_back(new Upgrade(50, 50, RandomRange(0, Width - 50),
			RandomRange(0, 200), imlist));

	}
}
void __fastcall Tfm::timerDelayTimer(TObject *Sender)
{
    timerShowEnemy->Enabled = true;
	render->Enabled = true;
	timerUpgrade->Enabled = true;
	timerEnemyShoot->Enabled = true;
    countkills = 10;
	int rN[] {-50, Width + 50};
	for (unsigned i = 0; i < countkills; ++i) {
		enemies.push_back(new Enemy(1.0, 50, 50, rN[RandomRange(0, 2)],
			RandomRange(0, Height * 0.5f - 100), imlist));
		enIt it = enemies.end();
		--it;
		(*it)->hide();
		if ((*it)->get()->Position->Y <= Height / 0.4f)
			(*it)->setStatus(Enemy::Up);
		else if ((*it)->get()->Position->Y <= Height / 0.4f)
			(*it)->setStatus(Enemy::Down);
	}
	last = enemies.begin();
    timerDelay->Enabled = false;
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::FormKeyDown(TObject * Sender, WORD & Key,
	System::WideChar & KeyChar, TShiftState Shift) {
	 if (Key == VK_SHIFT) {
		 ShowMessage(enemies.size());
	 }
}

void __fastcall Tfm::buStartClick(TObject *Sender) {
	tc->ActiveTab = Game;
    timerDelay->Enabled = true;
	shotRecharge = false;
	upgradelevel = 1;
	space->Position->X = Width/2 - space->Size->Width;
	space->Position->Y = Height - Height/4;
	rdyAnimation->Enabled = true;
	laCount->Text = txt("Î÷êè: %d", 0);            //%d - int, %s - str %n - float,double
	fireAnim->Enabled = false;
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::buAboutClick(TObject *Sender)
{
    ShowMessage(L"Created by Dmitry Yakuba");
}

//////////ENEMY/////
// ---------------------------------------------------------------------------

Enemy::Enemy(int op, int w, int h, float x, float y, TImageList * imlist)
	: enI(new TGlyph(NULL)) {
	m_mStatus = Down;
	m_iSpeed = -2;
	enI->Images = imlist;
	enI->ImageIndex = RandomRange(0, 3);
	enI->Width = w;
	enI->Height = h;
	enI->Position->X = x;
	enI->Position->Y = y;
	enI->Opacity = op;

	fm->AddObject(enI);

}

Enemy::~Enemy() {
	if (enI != NULL)
		delete enI;
}

float Enemy::x() {
	return enI->Position->X;
}

float Enemy::y() {
	return enI->Position->Y;
}

void Enemy::setX(float x) {
	enI->Position->X = x;
}

void Enemy::setY(float y) {
	enI->Position->Y = y;
}

float Enemy::opacity() {
	return enI->Opacity;
}

void Enemy::setOpacity(float op) {
	enI->Opacity = op;
}

void Enemy::setWidth(int w) {
	enI->Width = w;
}

void Enemy::setHeight(int h) {
	enI->Height = h;
}

int Enemy::w() {
	return enI->Width;
}

int Enemy::h() {
	return enI->Height;
}

int Enemy::speed() {
	return m_iSpeed;
}

int Enemy::meRand() {
	return m_iRand;
}

void Enemy::setSpeed(int s) {
	m_iSpeed = s;
}

void Enemy::setRand(int r) {
	m_iRand = r;
}

TGlyph * Enemy::get() {
	return enI;
}

Enemy::Move Enemy::status() {
	return m_mStatus;
}

void Enemy::setStatus(Move state) {
	m_mStatus = state;
}

void Enemy::show() {
	enI->Opacity = 1.0f;
}

void Enemy::hide() {
	enI->Opacity = 0.0f;

}

bool Enemy::isHide() {
	return enI->Opacity == 0.0f;
}
// ---------------------------------------------------------------------------

///SHOT

Shot::Shot(int rotation, int w, int h, float x, float y, TShape * shape)
	: me(shape) {
	me->Width = w;
	me->Height = h;
	me->Position->X = x;
	me->Position->Y = y;
	fm->AddObject(me);
}

Shot::~Shot() {
	delete me;
}

float Shot::x() {
	return me->Position->X;
}

float Shot::y() {
	return me->Position->Y;
}

TShape * Shot::get() {
	return me;
}

void Shot::setX(float x) {
	me->Position->X = x;
}

void Shot::setY(float y) {
	me->Position->Y = y;
}

Upgrade::Upgrade(int w, int h, float x, float y, TImageList * imlist)

	: upI(new TGlyph(NULL)) {

	upI->Images = imlist;
	upI->ImageIndex = 4;
	upI->Width = w;
	upI->Height = h;
	upI->Position->X = x;
	upI->Position->Y = y;

	fm->AddObject(upI);
}

Upgrade::~Upgrade() {

	if (upI != NULL)

		delete upI;

}

float Upgrade::y() {

	return upI->Position->Y;
}

float Upgrade::x() {
	return upI->Position->X;
}

float Upgrade::sizeW() {
	return upI->Size->Width;
}

float Upgrade::sizeH() {
	return upI->Size->Height;

}
//////////// ÍÀ ÇÀÌÅÒÊÓ /////////////

/*


 TFloatAnimation * fa1 = new TFloatAnimation(imenemy);
 fa1->Enabled = true;
 fa1->Duration = 1;
 fa1->Parent = imenemy;
 fa1->PropertyName = "Position.X";
 fa1->StartValue = 0;
 fa1->StopValue = 100;

 fa1->Start();
 TFloatAnimation * fa2 = new TFloatAnimation(imenemy);
 fa2->Enabled = true;
 fa2->Duration = 1;
 fa2->Parent = imenemy;
 fa2->PropertyName = "Position.Y";
 fa2->StartValue = 0;
 fa2->StopValue = 10;
 fa2->Start();
 */


//---------------------------------------------------------------------------



