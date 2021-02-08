#ifndef PLAYER
#define PLAYER

#ifdef _WIN32

#include "fmxheaders.h"
#include "globaloptions.h"

class Player {
public:
	Player(ms::TOptions &options);
	~Player();

	bool move(WORD &Key, System::WideChar &KeyChar);
	void setStep(float s);
	float getStep();
	void setX(int x);
	void setY(int y);
	int x();
	int y();
	ms::TPosition xy();
	void setLimit(const ms::TPosition &pos);
	ms::TPosition & getLimit();
	TImage *me();
	void setMe(TImage * im);
	void setAngle(float angle);

	TImage * operator->();
	void resize(ms::TOptions &o);

private:
	TImage *pImage;
	float step;
	ms::TPosition pos;
	ms::TPosition limit;
	//////

	bool toLeft();
	bool toRight();
	bool toUp();
	bool toDown();

	////
	WORD *key;
	System::WideChar *keyChar;
};
#endif

#endif
