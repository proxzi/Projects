#ifndef GLOBALOPTIONS
#define GLOBALOPTIONS

#include <vector>
#include <algorithm>

namespace ms {
	struct TPosition {
		int x;
		int y;

		TPosition() : x(0), y(0) {
		}

		TPosition(int x, int y) : x(x), y(y) {
		}

		TPosition& operator =(const TPosition & other) {
			x = other.x;
			y = other.y;
			return *this;
		}

		TPosition& operator +(const TPosition &other) {
			x = x + other.x;
			y = y + other.y;
			return *this;
		}
	};

	struct TOptions {
		int cellsWidth;
		int cellsHeight;
		int cellsCount;
		int minesCount;
		int globalWidth;
		int globalHeight;
		int width;
		int height;
		TForm *parent;
		TLayout *pLayout;
		TImage *pPlayer;
        TImage *pCity;
		TImageList *pImageList;
        TLabel *pMinesCount;
		float cellSize;
		bool isPlayerActive;
	};
}

#endif
