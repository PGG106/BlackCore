#include "move.h"
#include "utils.h"

Move::Move(Square from, Square to, unsigned int flags, Piece capturedPiece) {
    data = ((encodePiece(capturedPiece)) << 16 | (flags & 0xf) << 12 | (from & 0x3f) << 6 | (to & 0x3f));
}

Move::Move(Square from, Square to, unsigned int flags) {
    data = ((flags & 0xf) << 12 | (from & 0x3f) << 6 | (to & 0x3f));
}

Move::Move() {
    data = 0;
}

bool Move::isNull() const {
    return data == 0;
}

void Move::operator=(Move a) {
    data = a.data;
}

Square Move::getTo() const {
    return Square(data & 0x3f);
}

Square Move::getFrom() const {
    return Square((data >> 6) & 0x3f);
}

Piece Move::getCapturedPiece() const {
    return decodePiece(data >> 16);
}

bool Move::isFlag(unsigned int flag) const {
    return ((data >> 12) & 0xf) & flag;
}

bool Move::operator==(Move a) const {
    return (data & 0xFFFF) == (a.data & 0xFFFF);
}

bool Move::operator!=(Move a) const {
    return (data & 0xFFFF) != (a.data & 0xFFFF);
}

Move::operator bool() const {
    return !isNull();
}

bool Move::isCapture() const {
    return isFlag(CAPTURE_FLAG);
}

bool Move::isPromo() const {
    return isFlag(PROMO_FLAG);
}

bool Move::isSpecial1() const {
    return isFlag(SPECIAL1_FLAG);
}

bool Move::isSpecial2() const {
    return isFlag(SPECIAL2_FLAG);
}

bool Move::isQuiet() const {
    return !isCapture();
}

std::string Move::str() const {
    std::string token;
    if (isPromo()) {
        if (!isSpecial1() && !isSpecial2()) token += "n";
        else if (isSpecial1() && !isSpecial2()) token += "b";
        else if (!isSpecial1() && isSpecial2()) token += "r";
        else token += "q";
    }
    return formatSquare(getFrom()) + formatSquare(getTo()) + token;
}

