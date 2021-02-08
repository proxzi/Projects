#include "gamelogic.h"

using std::vector;

GameLogic::GameLogic(ms::TOptions &options) : options(options) {
#ifdef _WIN32
	player = new Player(options);
#endif
	options.pPlayer->Visible = options.isPlayerActive;
	options.pLayout->Width = options.cellsWidth * options.cellSize;
	options.pLayout->Height = options.cellsHeight * options.cellSize;

	setup();
	setMines();
	startGame();

#ifdef _WIN32
	if (options.isPlayerActive)
		player->me()->BringToFront();
#endif
}

void GameLogic::resize(ms::TOptions &o) {
	o.pLayout->Width = o.cellsWidth * o.cellSize;
	o.pLayout->Height = o.cellsHeight * o.cellSize;

	for_each(begin(vecCells), end(vecCells),[&o](std::vector<Cell *> & vecCol)
	{
		for_each(begin(vecCol), end(vecCol),[&o](Cell * cell)
		{
			cell->resize(o);
		});
	});

#ifdef _WIN32
	if (options.isPlayerActive)
		player->resize(o);
#endif

	options = o;
}

void GameLogic::setup() {

	vecCells.resize(options.cellsWidth);

	int tmpHeight = options.cellsHeight;
	std::for_each(vecCells.begin(), vecCells.end(), [tmpHeight](std::vector<Cell*>&item)
	{
		item.resize(tmpHeight);
	});

	for (unsigned i = 0; i < options.cellsWidth; ++i) {
		for (unsigned j = 0; j < options.cellsHeight; ++j) {
			vecCells[i][j] = new Cell(options, ms::TPosition(i, j));
		}
	}
}

GameLogic::~GameLogic() {

   /*	for (unsigned i = 0; i < vecCells.size(); ++i) {
		for (unsigned j = 0; j < vecCells[i].size(); ++j) {
			delete vecCells[i][j];
		}
	} */
#ifdef _WIN32
	delete player;
#endif
}

ms::TOptions &GameLogic::settings() {
	return options;
}

#ifdef _WIN32

Player & GameLogic::getPlayer() {
	return *player;
}

void GameLogic::render(WORD &key, System::WideChar &keyChar) {

	if (m_bIsGameActive && options.isPlayerActive) {

		player->move(key, keyChar);
		int x = player->x();
		int y = player->y();

		if (key == VK_CONTROL)
			open(x, y);
		if (key == VK_SHIFT) {
			showMinesCount += vecCells[x][y]->toMark();
			options.pMinesCount->Text = Format(L"Мин : %d", ARRAYOFCONST((showMinesCount)));
		}

		player->me()->BringToFront();
	}
}
#endif

void GameLogic::setMines() {

	int x = 0, y = 0;

	options.minesCount = RandomRange(options.cellsWidth,
		options.cellsWidth * 2);

	showMinesCount = options.minesCount;

	for (int i = 0; i < options.minesCount; i++) {
		do {
			x = RandomRange(0, options.cellsWidth);
			y = RandomRange(0, options.cellsHeight);
		}
		while (vecCells[x][y]->isMined());

		vecCells[x][y]->toMine();
	}

	options.pMinesCount->Text =
		Format(L"Мин : %d", ARRAYOFCONST((showMinesCount)));
}

bool GameLogic::outOfBorders(int x, int y) {
	return x >= 0 && y >= 0 && x < options.cellsWidth && y <
		options.cellsHeight;
}

int GameLogic::countMineAround(int x, int y) {
	int count = 0;

	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
			if (outOfBorders(x + i, y + j) && vecCells[x + i][y + j]->isMined())
				count++;

	return count;
}

void GameLogic::open(int x, int y) {

	if (!outOfBorders(x, y))
		return;

	if (vecCells[x][y]->status() == Cell::State::Opened)
		return;

	if (vecCells[x][y]->isMined()) {
		gameOver();
		return;
	}

	if (vecCells[x][y]->status() == Cell::State::Marked)
		vecCells[x][y]->toMark();

	vecCells[x][y]->open();
	--options.cellsCount;

	int count = countMineAround(x, y);

	if (count == 0) {
		vecCells[x][y]->empty();

		for (int i = -1; i <= 1; ++i)
			for (int j = -1; j <= 1; ++j)
				if (outOfBorders(x + i, y + j) && vecCells[x + i][y + j]->status
					() == Cell::State::Closed)
					open(x + i, y + j);
	}
	else {
		vecCells[x][y]->displayNumber(count);
	}
	if (options.cellsCount == options.minesCount && m_bIsGameActive)
		gameOver();
}

void GameLogic::startGame() {
	m_bIsGameActive = true;
}

void GameLogic::gameOver() {
	exploidMines();
	if (options.cellsCount == options.minesCount) {
		ShowMessage(L"Победа!!!");
	}
	else
		ShowMessage(L"Конец игры.");
	m_bIsGameActive = false;

	options.parent->Hide();
}

void GameLogic::exploidMines() {
	for_each(begin(vecCells), end(vecCells),[](vector<Cell *> & vecCol)
	{
		for_each(begin(vecCol), end(vecCol),[](Cell * cell)
		{
			if(cell->isMined()) cell->toExploid();
		});
	});
}

void GameLogic::click(float X, float Y, ClickMode clickMode) {

	if (m_bIsGameActive && !options.isPlayerActive) {

		int x = X / options.cellSize;
		int y = Y / options.cellSize;

		if (clickMode == ClickMode::Click) {
			open(x, y);
		}
		else {
			showMinesCount += vecCells[x][y]->toMark();
			options.pMinesCount->Text =
				Format(L"Мин : %d", ARRAYOFCONST((showMinesCount)));
		}
	}
}
