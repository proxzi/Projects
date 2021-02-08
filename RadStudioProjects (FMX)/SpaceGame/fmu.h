// ---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include <FMX.Ani.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.Layers3D.hpp>
#include <System.Math.Vectors.hpp>
// ---------------------------------------------------------------------------
#include <deque>
#include <list>
#include <vector>
using std::list;

class Enemy;
class Shot;
class Upgrade;

/*
 template<typename Object>
 class Container {
 typedef std::list<Object*>::iterator listIter;

 public:
 Container() {
 }

 ~Container() {
 for (listIter it = m_olist.begin(); it != m_olist.end(); ++it) {
 delete *it;
 }
 }

 void add(Object * o)
 {
 m_olist.push_back(o);
 }

 void add(int op, int w, int h, float x, float y, TImageList * imlist)
 {
 m_olist.push_back(new Object(op, w, h, x, y, imlist));
 }

 int size();

 private:
 list<Object*>m_olist;
 }; */

class Tfm : public TForm {
__published: // IDE-managed Components
	TLabel *posX;
	TLabel *posY;
	TImage *space;
	TRectangle *re;
	TTimer *render;
	TImageList *imlist;
	TTimer *timerShowEnemy;
	TLabel *laCount;
	TTimer *timerShotRecharge;
	TTimer *timerEnemyShoot;
	TProgressBar *HPLine;
	TTimer *timerUpgrade;
	TTabControl *tc;
	TTabItem *Start;
	TTabItem *Game;
	TLabel *showlinesize;
	TButton *buStart;
	TRectangle *Rectangle1;
	TRectangle *Rectangle2;
	TTimer *timerDelay;
	TLabel *laReady;
	TFloatAnimation *rdyAnimation;
	TToolBar *ToolBar1;
	TButton *buAbout;
	TImage *Image1;
	TBitmapListAnimation *fireAnim;
	TLayout3D *Layout3D1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall renderTimer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
		System::WideChar &KeyChar, TShiftState Shift);
	void __fastcall timerShowEnemyTimer(TObject *Sender);
	void __fastcall timerShotRechargeTimer(TObject *Sender);
	void __fastcall timerEnemyShootTimer(TObject *Sender);
	void __fastcall timerUpgradeTimer(TObject *Sender);
	void __fastcall buStartClick(TObject *Sender);
	void __fastcall reMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall reMouseMove(TObject *Sender, TShiftState Shift, float X, float Y);
	void __fastcall reMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall timerDelayTimer(TObject *Sender);
	void __fastcall buAboutClick(TObject *Sender);



private: // User declarations
	int w;
	int h;
	int x;
	float step;

    int level;
	int countkills;
	int upgradelevel;
	list<Shot*>lines;
	list<Enemy*>enemies;
	list<Shot*>circles;
    list<Upgrade*>upgrades;

	std::list<Enemy*>::iterator last;

	int count;

	enum State {
		UnClicked, Clicked
	};

	float stepX;
	float stepY;

	State state;

	bool shotRecharge;

    int countVisibleEnemies;

public: // User declarations
	__fastcall Tfm(TComponent* Owner);
};

class Shot {
public:
	Shot(int rotation, int w, int h, float x, float y, TShape * shape);
	~Shot();
	float x();
	float y();
	void setX(float x);
	void setY(float y);
	int rotation;
    int id;

	TShape *get();

	float direction;
private:
	TShape *me;
};

class Enemy {

public:
	enum Move {
		Up, Down
	};

	Enemy(int op, int w, int h, float x, float y, TImageList * imlist);
	~Enemy();
	float x();
	float y();
	void setX(float x);
	void setY(float y);
	float opacity();
	void setOpacity(float op);
	void setWidth(int w);
	void setHeight(int h);
	int w();
	int h();
	int speed();
	int meRand();
	void setSpeed(int s);
	void setRand(int r);
	Move status();
	void setStatus(Move state);
	TGlyph * get();
	void show();
	void hide();
	bool isHide();


private:
	int m_iRand;
	int m_iSpeed;
	Move m_mStatus;
	TGlyph * enI;
};

class Upgrade{

public:
	Upgrade(int w, int h, float x, float y, TImageList * imlist);
    ~Upgrade();
	TGlyph * upI;
	float y();
	float x();
	float sizeW();
	float sizeH();

private:
};

// ---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
// ---------------------------------------------------------------------------
#endif
