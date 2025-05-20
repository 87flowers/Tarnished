#pragma once
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "external/chess.hpp"
#include "search.h"
#include "parameters.h"

using namespace chess;
constexpr int INFINITE = std::numeric_limits<int>::max();
constexpr int MATE = 32767;
constexpr int32_t FOUND_MATE  = MATE - MAX_PLY;
constexpr int32_t GETTING_MATED = -MATE + MAX_PLY;

#define NO_SCORE MATE + 2

#define MakeScore(mg, eg) ((int32_t)((uint32_t)(eg) << 16) + (mg))
#define S(mg, eg) MakeScore((mg), (eg))
#define MgScore(s) ((int16_t)((uint16_t)((uint32_t)((s)))))
#define EgScore(s) ((int16_t)((uint16_t)((uint32_t)((s) + 0x8000) >> 16)))

typedef int32_t Score;

// Stockfish yoink
// https://github.com/official-stockfish/Stockfish/blob/94e6c0498ff24d0a66fd0817fcbb88855a9b6116/src/uci.cpp#L502
// Unused for now
// struct WinRateParams {
// 	double a;
// 	double b;
// };

// WinRateParams winRateParams(Board& board) {

// 	int material = board.pieces(PieceType::PAWN).count() + 3 * board.pieces(PieceType::KNIGHT).count() + 3 * board.pieces(PieceType::BISHOP).count()
// 				+ 5 * board.pieces(PieceType::ROOK).count() + 9 * board.pieces(PieceType::QUEEN).count();
// 	// The fitted model only uses data for material counts in [17, 78], and is anchored at count 58.
// 	double m = std::clamp(material, 17, 78) / 58.0;

// 	// Return a = p_a(material) and b = p_b(material), see github.com/official-stockfish/WDL_model
// 	constexpr double as[] = {-13.50030198, 40.92780883, -36.82753545, 386.83004070};
// 	constexpr double bs[] = {96.53354896, -165.79058388, 90.89679019, 49.29561889};

// 	double a = (((as[0] * m + as[1]) * m + as[2]) * m) + as[3];
// 	double b = (((bs[0] * m + bs[1]) * m + bs[2]) * m) + bs[3];

// 	return {a, b};
// }

// int winRateModel(Value v, Board& board) {

// 	auto [a, b] = winRateParams(board);

// 	// Return the win rate in per mille units, rounded to the nearest integer.
// 	return int(0.5 + 1000 / (1 + std::exp((a - double(v)) / b)));
// }