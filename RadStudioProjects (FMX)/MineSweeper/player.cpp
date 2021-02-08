#ifdef _WIN32

#include "player.h"

constexpr float ROTATE_LEFT = 90.0f;
constexpr float ROTATE_RIGHT = -90.0f;
constexpr float ROTATE_UP = 180.0f;
constexpr float ROTATE_DOWN = 0.0f;

Player::Player(ms::TOptions &options) {

	pImage = options.pPlayer;

	if (options.isPlayerActive) {
		step = options.cellSize;
		limit.x = options.cellsWidth - 1;
		limit.y = options.cellsHeight - 1;
		pImage->Width = step;
		pImage->Height = step;
		pImage->Position->X = 0;
		pImage->Position->Y = 0;
	}
}

Player::~Player() {
}

bool Player::move(WORD &Key, System::WideChar &KeyChar) {
	key = &Key;
	keyChar = &KeyChar;

	if (toLeft() && x() > 0) {
		setX(x() - 1);
		setAngle(ROTATE_LEFT);
	}
	else if (toRight() && x() < getLimit().x) {
		setX(x() + 1);
		setAngle(ROTATE_RIGHT);
	}

	if (toUp() && y() > 0) {
		setY(y() - 1);
		setAngle(ROTATE_UP);
	}
	else if (toDown() && y() < getLimit().y) {
		setY(y() + 1);
		setAngle(ROTATE_DOWN);
	}
	return true;
}

void Player::resize(ms::TOptions &o) {
		if (o.isPlayerActive) {
		step = o.cellSize;
		pImage->Width = step;
		pImage->Height = step;
		pImage->Position->X = x() * o.cellSize;
		pImage->Position->Y = y() * o.cellSize;
	}
}

TImage * Player:: operator->() {
	return pImage;
}

TImage *Player::me() {
	return pImage;
}

void Player::setMe(TImage * im) {
	pImage = im;
}

void Player::setStep(float s) {
	step = s;
}

float Player::getStep() {
	return step;
}

void Player::setX(int x) {
	me()->Position->X = x * getStep();
	pos.x = x;
}

void Player::setY(int y) {
	me()->Position->Y = y * getStep();
	pos.y = y;
}

int Player::x() {
	return pos.x;
}

int Player::y() {
	return pos.y;
}

void Player::setLimit(const ms::TPosition &pos) {
	limit.x = pos.x;
	limit.y = pos.y;
}

ms::TPosition & Player::getLimit() {
	return limit;
}

bool Player::toLeft() {
	return *key == VK_LEFT || *keyChar == 'a' || *keyChar == 'A' ||
		*keyChar == L'ô' || *keyChar == L'Ô';
}

bool Player::toRight() {
	return *key == VK_RIGHT || *keyChar == 'd' || *keyChar == 'D' ||
		*keyChar == L'â' || *keyChar == L'Â';
}

bool Player::toUp() {
	return *key == VK_UP || *keyChar == 'w' || *keyChar == 'W' ||
		*keyChar == L'ö' || *keyChar == L'Ö';
}

bool Player::toDown() {
	return *key == VK_DOWN || *keyChar == 's' || *keyChar == 'S' ||
		*keyChar == 'û' || *keyChar == 'Û';
}

void Player::setAngle(float angle) {
	me()->RotationAngle = angle;
}

ms::TPosition Player::xy() {
	return pos;
}

#endif
