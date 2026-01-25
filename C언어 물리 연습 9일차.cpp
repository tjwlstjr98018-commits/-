#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  //sleep 나중에 다른걸로 바꿀 수 있을떄 바꿈

#define COUNT 100

typedef struct {
	float x;
	float y;
} Vec2;

typedef struct {
	Vec2 pos;
	Vec2 vel;
} Body;

const float Gravity = -20.0f;
const float DT = 0.016f;

void PhysicsStep(Body* b) {
	//속도 업뎃
	b->vel.y += Gravity * DT;
	//위치
	b->pos.y += b->vel.y * DT;
	//바닥 충돌
	if (b->pos.y < 0) {
		b->pos.y = 0;
		b->vel.y = -b->vel.y * 0.7f;
	}
}

int main() {
	Body balls[COUNT];

	//초기화 단계
	for (int i = 0; i < COUNT; i++) {
		balls[i].pos.x = i;
		balls[i].pos.y = 50 + i;

		balls[i].vel.x = 0;
		balls[i].vel.y = 0;
	}

	//게임 루프
	while (1) {
		system("cls");
		
		for (int i = 0; i < COUNT; i++) {
			PhysicsStep(&balls[i]);

			printf("Ball %d : y = %.2f\n", i, balls[i].pos.y);
		}
		Sleep(16);
	}
	return 0;
}
