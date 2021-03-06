﻿#pragma once

#define BOOST_PYTHON_STATIC_LIB
#define BOOST_NUMPY_STATIC_LIB
#include <boost/python/numpy.hpp>

#include "init.hpp"
#include "position.hpp"
#include "search.hpp"
#include "generateMoves.hpp"

#define LEN(array) (sizeof(array) / sizeof(array[0]))

const int MAX_HPAWN_NUM = 8; // 歩の持ち駒の上限
const int MAX_HLANCE_NUM = 4;
const int MAX_HKNIGHT_NUM = 4;
const int MAX_HSILVER_NUM = 4;
const int MAX_HGOLD_NUM = 4;
const int MAX_HBISHOP_NUM = 2;
const int MAX_HROOK_NUM = 2;

const u32 MAX_PIECES_IN_HAND[] = {
	MAX_HPAWN_NUM, // PAWN
	MAX_HLANCE_NUM, // LANCE
	MAX_HKNIGHT_NUM, // KNIGHT
	MAX_HSILVER_NUM, // SILVER
	MAX_HGOLD_NUM, // GOLD
	MAX_HBISHOP_NUM, // BISHOP
	MAX_HROOK_NUM, // ROOK
};
const u32 MAX_PIECES_IN_HAND_SUM = MAX_HPAWN_NUM + MAX_HLANCE_NUM + MAX_HKNIGHT_NUM + MAX_HSILVER_NUM + MAX_HGOLD_NUM + MAX_HBISHOP_NUM + MAX_HROOK_NUM;
const u32 MAX_FEATURES2_HAND_NUM = (int)ColorNum * MAX_PIECES_IN_HAND_SUM;

const int PIECETYPE_NUM = 14; // 駒の種類
const int MAX_ATTACK_NUM = 3; // 利き数の最大値
const u32 MAX_FEATURES1_NUM = PIECETYPE_NUM/*駒の配置*/ + PIECETYPE_NUM/*駒の利き*/ + MAX_ATTACK_NUM/*利き数*/;
const u32 MAX_FEATURES2_NUM = MAX_FEATURES2_HAND_NUM + 1/*王手*/;

// 移動の定数
enum MOVE_DIRECTION {
	UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN, DOWN_LEFT, DOWN_RIGHT,
	UP_PROMOTE, UP_LEFT_PROMOTE, UP_RIGHT_PROMOTE, LEFT_PROMOTE, RIGHT_PROMOTE, DOWN_PROMOTE, DOWN_LEFT_PROMOTE, DOWN_RIGHT_PROMOTE
};

const MOVE_DIRECTION MOVE_DIRECTION_PROMOTED[] = {
	UP_PROMOTE, UP_LEFT_PROMOTE, UP_RIGHT_PROMOTE, LEFT_PROMOTE, RIGHT_PROMOTE, DOWN_PROMOTE, DOWN_LEFT_PROMOTE, DOWN_RIGHT_PROMOTE
};

const MOVE_DIRECTION PAWN_MOVE_DIRECTION[] = { UP, UP_PROMOTE };
const MOVE_DIRECTION LANCE_MOVE_DIRECTION[] = { UP, UP_PROMOTE };
const MOVE_DIRECTION KNIGHT_MOVE_DIRECTION[] = {
	UP_LEFT, UP_RIGHT,
	UP_LEFT_PROMOTE, UP_RIGHT_PROMOTE };
const MOVE_DIRECTION SILVER_MOVE_DIRECTION[] = {
	UP, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT,
	UP_PROMOTE, UP_LEFT_PROMOTE, UP_RIGHT_PROMOTE, DOWN_LEFT_PROMOTE, DOWN_RIGHT_PROMOTE };
const MOVE_DIRECTION BISHOP_MOVE_DIRECTION[] = {
	UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT,
	UP_LEFT_PROMOTE, UP_RIGHT_PROMOTE, DOWN_LEFT_PROMOTE, DOWN_RIGHT_PROMOTE };
const MOVE_DIRECTION ROOK_MOVE_DIRECTION[] = {
	UP, LEFT, RIGHT, DOWN,
	UP_PROMOTE, LEFT_PROMOTE, RIGHT_PROMOTE, DOWN_PROMOTE };
const MOVE_DIRECTION GOLD_MOVE_DIRECTION[] = {
	UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN,
	UP_PROMOTE, UP_LEFT_PROMOTE, UP_RIGHT_PROMOTE, LEFT_PROMOTE, RIGHT_PROMOTE, DOWN };
const MOVE_DIRECTION KING_MOVE_DIRECTION[] = { UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN, DOWN_LEFT, DOWN_RIGHT };
const MOVE_DIRECTION PROM_PAWN_MOVE_DIRECTION[] = { UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN };
const MOVE_DIRECTION PROM_LANCE_MOVE_DIRECTION[] = { UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN };
const MOVE_DIRECTION PROM_KNIGHT_MOVE_DIRECTION[] = { UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN };
const MOVE_DIRECTION PROM_SILVER_MOVE_DIRECTION[] = { UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN };
const MOVE_DIRECTION PROM_BISHOP_MOVE_DIRECTION[] = { UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN, DOWN_LEFT, DOWN_RIGHT };
const MOVE_DIRECTION PROM_ROOK_MOVE_DIRECTION[] = { UP, UP_LEFT, UP_RIGHT, LEFT, RIGHT, DOWN, DOWN_LEFT, DOWN_RIGHT };

const int PIECE_MOVE_DIRECTION_INDEX[][16] = {
	{ 0, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 }, // PAWN
	{ 0, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1 }, // LANCE
	{ 0, 1, 2, 3, 4, -1, -1, -1, -1, 5, 6, 7, 8, -1, -1, -1 }, // KNIGHT
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, 13, 14 }, // SILVER
	{ 0, 1, 2, 3, 4, 5, 6, 7, -1, 8, 9, 10, 11, -1, 12, 13 }, // BISHOP
	{ 0, -1, -1, 1, 2, 3, -1, -1, 4, -1, -1, 5, 6, 7, -1, -1 }, // ROOK
	{ 0, 1, 2, 3, 4, 5, -1, -1, 6, 7, 8, 9, 10, -1, -1, -1 }, // GOLD
	{ 0, 1, 2, 3, 4, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1 }, // KING
	{ 0, 1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // PROM_PAWN
	{ 0, 1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // PROM_LANCE
	{ 0, 1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // PROM_KNIGHT
	{ 0, 1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // PROM_SILVER
	{ 0, 1, 2, 3, 4, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1 }, // PROM_BISHOP
	{ 0, 1, 2, 3, 4, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1 }, // PROM_ROOK
};

// classification label
const int PAWN_MOVE_DIRECTION_LABEL = 0;
const int LANCE_MOVE_DIRECTION_LABEL = LEN(PAWN_MOVE_DIRECTION);
const int KNIGHT_MOVE_DIRECTION_LABEL = LANCE_MOVE_DIRECTION_LABEL + LEN(LANCE_MOVE_DIRECTION);
const int SILVER_MOVE_DIRECTION_LABEL = KNIGHT_MOVE_DIRECTION_LABEL + LEN(KNIGHT_MOVE_DIRECTION);
const int BISHOP_MOVE_DIRECTION_LABEL = SILVER_MOVE_DIRECTION_LABEL + LEN(GOLD_MOVE_DIRECTION);
const int ROOK_MOVE_DIRECTION_LABEL = BISHOP_MOVE_DIRECTION_LABEL + LEN(BISHOP_MOVE_DIRECTION);
const int GOLD_MOVE_DIRECTION_LABEL = ROOK_MOVE_DIRECTION_LABEL + LEN(SILVER_MOVE_DIRECTION);
const int KING_MOVE_DIRECTION_LABEL = GOLD_MOVE_DIRECTION_LABEL + LEN(ROOK_MOVE_DIRECTION);
const int PROM_PAWN_MOVE_DIRECTION_LABEL = KING_MOVE_DIRECTION_LABEL + LEN(KING_MOVE_DIRECTION);
const int PROM_LANCE_MOVE_DIRECTION_LABEL = PROM_PAWN_MOVE_DIRECTION_LABEL + LEN(PROM_PAWN_MOVE_DIRECTION);
const int PROM_KNIGHT_MOVE_DIRECTION_LABEL = PROM_LANCE_MOVE_DIRECTION_LABEL + LEN(PROM_LANCE_MOVE_DIRECTION);
const int PROM_SILVER_MOVE_DIRECTION_LABEL = PROM_KNIGHT_MOVE_DIRECTION_LABEL + LEN(PROM_KNIGHT_MOVE_DIRECTION);
const int PROM_BISHOP_MOVE_DIRECTION_LABEL = PROM_SILVER_MOVE_DIRECTION_LABEL + LEN(PROM_SILVER_MOVE_DIRECTION);
const int PROM_ROOK_MOVE_DIRECTION_LABEL = PROM_BISHOP_MOVE_DIRECTION_LABEL + LEN(PROM_BISHOP_MOVE_DIRECTION);
const int MOVE_DIRECTION_LABEL_NUM = PROM_ROOK_MOVE_DIRECTION_LABEL + LEN(PROM_ROOK_MOVE_DIRECTION);
const int MAX_MOVE_LABEL_NUM = MOVE_DIRECTION_LABEL_NUM + HandPieceNum;

const int PIECE_MOVE_DIRECTION_LABEL[] = {
	0,
	PAWN_MOVE_DIRECTION_LABEL, LANCE_MOVE_DIRECTION_LABEL, KNIGHT_MOVE_DIRECTION_LABEL, SILVER_MOVE_DIRECTION_LABEL,
	BISHOP_MOVE_DIRECTION_LABEL, ROOK_MOVE_DIRECTION_LABEL,
	GOLD_MOVE_DIRECTION_LABEL,
	KING_MOVE_DIRECTION_LABEL,
	PROM_PAWN_MOVE_DIRECTION_LABEL, PROM_LANCE_MOVE_DIRECTION_LABEL, PROM_KNIGHT_MOVE_DIRECTION_LABEL, PROM_SILVER_MOVE_DIRECTION_LABEL,
	PROM_BISHOP_MOVE_DIRECTION_LABEL, PROM_ROOK_MOVE_DIRECTION_LABEL
};

void make_input_features(const Position& position, float(*features1)[ColorNum][MAX_FEATURES1_NUM][SquareNum], float(*features2)[MAX_FEATURES2_NUM][SquareNum]);
int make_move_label(const u16 move16, const Position& position);
int make_move_label(const u16 move16, const PieceType move_piece, const Color color);
void softmax_tempature_with_normalize(std::vector<float> &log_probabilities);
void set_softmax_tempature(const float tempature);

// 評価値から価値(勝率)に変換
// スケールパラメータは、elmo_for_learnの勝率から調査した値
inline float score_to_value(const Score score) {
	return 1.0f / (1.0f + expf(-(float)score * 0.00132566f));
}
