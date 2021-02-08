#ifndef CELL
#define CELL

#include "fmxheaders.h"
#include "globaloptions.h"

class Cell {

public:
	enum class State{Closed, Opened, Marked};

	Cell(ms::TOptions &options, ms::TPosition pos);
	~Cell();
	State status();

	void resize(ms::TOptions &o);
	void toDemine();
	void toMine();
	bool isMined();
	void open();
	int toMark();
	void toExploid();
	void empty();
	void displayNumber(int n);
private:
//methods
	void toCheck();
	void toUncheck();
	void createGlyph(int imIndex);
//variables
	ms::TOptions options;
	ms::TPosition pos;

	TGlyph *pImage;
	TRectangle *pRec;
	TLabel *pLabel;

	State state;

	bool mined;
};
#endif
