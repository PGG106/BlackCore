//     BlackCore is a UCI Chess engine
//     Copyright (c) 2022 SzilBalazs
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "eval.h"

#ifdef TUNE

Score PIECE_VALUES[6] = {
        0, 150, 750, 850, 1250, 1600
};

#endif

Score eval(const Position &pos) {

    Score score = pos.getState()->accumulator.forward();
    return (pos.getSideToMove() == WHITE ? score : -score) + TEMPO_SCORE;
}