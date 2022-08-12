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

#include <chrono>
#include <iostream>
#include "movegen.h"
#include "utils.h"

const int DEPTH = 6;

U64 perft(Position &position, int depth) {
    Move moves[200];
    Move *movesEnd = generateMoves(position, moves);
    if (depth == 1) return movesEnd - moves;
    U64 nodes = 0;
    for (Move *it = moves; it != movesEnd; it++) {
        position.makeMove(*it);
        U64 a = perft(position, depth - 1);
        if (depth == DEPTH) std::cout << it->str() << ": " << a << std::endl;
        nodes += a;
        position.undoMove(*it);
    }
    return nodes;
}

int main() {
    initBitboard();

    Position position = {"r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w - - 0 1"};

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::cout << perft(position, DEPTH) << std::endl;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << std::endl;
    return 0;
}
