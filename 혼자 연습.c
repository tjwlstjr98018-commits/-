#include <stdio.h>
#include <stdlib.h>

typedef struct Vec2 {  //위치 계산용
	float x, y;
} Vec2;

typedef struct map {
	char xlen[21];
	char ylen[21];
} map;

typedef struct Player {  //갤러그 특유의 뚝뚝 끈키는 모션구현 속도X
	Vec2 pos;
	int Attack;
	int dead;
} Player;

void MapFirstloding(map* a) {
	for (int s = 0; s < 21; s++) {
		a->xlen[s] = ' ';
		a->ylen[s] = ' ';
	}
	a->xlen[20] = '\0';
	a->ylen[20] = '\0';
}

void ML(map* a) {    //맵 로딩 약자
	for (int s = 0; s < 21; s++) {
		for (int b = 0; b < 21; b++) {
			if (s == 0 || s == 20) {
				a->xlen[s] = '|';
			}
			else a->xlen[s] = ' ';
		}
	}
}


