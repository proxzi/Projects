#ifndef GAMELOGIC
#define GAMELOGIC

#include "fmxheaders.h"
#include "globaloptions.h"
#include "cell.h"

#ifdef _WIN32
	#include "player.h"
#endif

class GameLogic {
public:
	enum class ClickMode {Click, Flag};

	GameLogic(ms::TOptions &options);
	~GameLogic();

	#ifdef _WIN32
	Player & getPlayer();
	void render(WORD &key, System::WideChar &keyChar);
	#endif
	void click(float X, float Y, ClickMode clickMode);
	ms::TOptions &settings();
    void resize(ms::TOptions &o);
private:
	void startGame();
	void gameOver();
	void exploidMines();
	void setMines();
	void setup();
	bool outOfBorders(int x, int y);
	int countMineAround(int x, int y);
	void open(int x, int y);
	bool m_bIsGameActive;
	int iCellCount;
	std::vector<std::vector<Cell *>> vecCells;
    int showMinesCount;
	#ifdef _WIN32
	Player *player;
	#endif
	ms::TOptions options;
};
#endif
