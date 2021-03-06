﻿#pragma once

#include "position.hpp"

const unsigned int UCT_HASH_SIZE = 262144;

struct node_hash_t {
	unsigned long long hash;
	int color;
	int moves;
	bool flag;
};

//  UCT用ハッシュテーブル
extern node_hash_t *node_hash;

//  UCT用ハッシュテーブルのサイズ
extern unsigned int uct_hash_size;

//  ハッシュテーブルのサイズの設定
void SetHashSize(const unsigned int new_size);

//  UCTノードのハッシュの初期化
void InitializeUctHash(void);

//  UCTノードのハッシュ情報のクリア
void ClearUctHash(void);

//  古いデータの削除
void DeleteOldHash(const Position *pos);

//  未使用のインデックスを探す
unsigned int SearchEmptyIndex(const unsigned long long hash, const int color, const int moves);

//  ハッシュ値に対応するインデックスを返す
unsigned int FindSameHashIndex(const unsigned long long hash, const int color, const int moves);

//  ハッシュ表が埋まっていないか確認
bool CheckRemainingHashSize(void);

// ハッシュ使用率を取得(単位はパーミル(全体を1000とした値))
int GetUctHashUsageRate();
