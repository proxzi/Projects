#include "cell.h"

Cell::Cell(ms::TOptions &options, ms::TPosition pos)
	: options(options)
	, pos(pos)
	, pImage(nullptr)
	, pRec(new TRectangle(options.pLayout))
	, pLabel(new TLabel(options.pLayout))
	, state(State::Closed), mined(false)
{
	// Setup rectangle
	pRec->Parent = options.pLayout;
	pRec->Width = options.cellSize;
	pRec->Height = options.cellSize;
	pRec->Position->X = pos.x * options.cellSize;
	pRec->Position->Y = pos.y * options.cellSize;
	pRec->Fill->Kind = TBrushKind::Solid;
	pRec->Stroke->Thickness = 1.0f;
	pRec->Opacity = 0.5f;
	pRec->HitTest = false;
	// Setup label
	pLabel->Parent = options.pLayout;
	pLabel->Width = options.cellSize;
	pLabel->Height = options.cellSize;
	pLabel->Position->X = pos.x * options.cellSize;
	pLabel->Position->Y = pos.y * options.cellSize;
	pLabel->Text = Format("%d:%d", ARRAYOFCONST((pos.x, pos.y)));

	pLabel->StyledSettings = pLabel->StyledSettings >> TStyledSetting::Other;
	pLabel->StyledSettings = pLabel->StyledSettings >> TStyledSetting::FontColor;
	pLabel->StyledSettings = pLabel->StyledSettings >> TStyledSetting::Size;

	pLabel->TextSettings->HorzAlign = TTextAlign::Center;
	pLabel->Visible = false;
	pLabel->HitTest = false;
}

Cell::~Cell() {
	if (pLabel != nullptr) {
		pLabel->DisposeOf();
		pLabel = nullptr;
	}
	if (pRec != nullptr) {
		pRec->DisposeOf();
		pRec = nullptr;
	}

	if (pImage != nullptr) {
		pImage->DisposeOf();
		pImage = nullptr;
    }

}

void Cell::resize(ms::TOptions &o) {
	// Setup rectangle
	pRec->Width = o.cellSize;
	pRec->Height = o.cellSize;
	pRec->Position->X = pos.x * o.cellSize;
	pRec->Position->Y = pos.y * o.cellSize;
	// Setup label
	pLabel->Width = o.cellSize;
	pLabel->Height = o.cellSize;
	pLabel->Position->X = pos.x * o.cellSize;
	pLabel->Position->Y = pos.y * o.cellSize;
	//TextFont
	pLabel->TextSettings->Font->Size = 0.8f * (float)o.cellSize;
	// Setup image
	if (pImage != nullptr) {
		pImage->Width = o.cellSize;
		pImage->Height = o.cellSize;
		pImage->Position->X = pos.x * o.cellSize;
		pImage->Position->Y = pos.y * o.cellSize;
	}

	options = o;
}

Cell::State Cell::status() {
	return state;
}

void Cell::toMine() {
	mined = true;
}

void Cell::createGlyph(int imIndex) {
	if (pImage == nullptr)
		pImage = new TGlyph(options.pLayout);

	pImage->Parent = options.pLayout;
	pImage->Images = options.pImageList;
	pImage->Width = options.cellSize;
	pImage->Height = options.cellSize;
	pImage->Position->X = pos.x * options.cellSize;
	pImage->Position->Y = pos.y * options.cellSize;
	pImage->ImageIndex = imIndex;
    pImage->HitTest = false;
}

void Cell::toExploid() {
	createGlyph(0);
}

void Cell::toCheck() {
	state = State::Marked;
	createGlyph(1);
}

void Cell::toUncheck() {
	state = State::Closed;
	if (pImage != nullptr) {
		pImage->DisposeOf();
		pImage = nullptr;
	}

}

int Cell::toMark() {
	if (state == State::Closed) {
		toCheck();
		return -1;
	} else if (state == State::Marked) {
		toUncheck();
		return 1;
	}
	return 0;
}

void Cell::toDemine() {
	mined = false;
}

bool Cell::isMined() {
	return mined;
}

void Cell::open() {
	state = State::Opened;
	//Edit disp
	pRec->Fill->Kind = TBrushKind::Solid;
	pRec->Visible = true;
	pLabel->TextSettings->Font->Size = 0.8f * (float)options.cellSize;
}

void Cell::empty() {
	pLabel->Text = "";
	pRec->Visible = false;
}

void Cell::displayNumber(int n)
{
	//Edit disp
	pRec->Opacity = 0.8f;
	pLabel->Text = n;
	pLabel->Visible = true;
}
