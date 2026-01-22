#include <stdio.h>

#define GRAVITY 9.8f
#define DT 0.016f //60f

typedef struct {
	float x;
	float y;
} vector2;

typedef struct {
	vector2 position;
	vector2 velocity;
	float restitution;
} Body;

void physicsUpdate(Body* b) {
	//중력적용 속도먼저
	b->velocity.y -= GRAVITY * DT;
	//위치적분
	b->position.x += b->velocity.x * DT;
	b->position.y += b->velocity.y * DT;
	//바닥충돌
	if (b->position.y <= 0.0f) {
		b->position.y = 0.0f;
		b->velocity.y = -b->velocity.y * b->restitution;
	}
}
int main() {
	Body ball;  //위에서 타입스트럭 바디선언그럼으로 바디 볼 사용가능
	ball.position.x = 0.0f;
	ball.position.y = 10.0f;

	ball.velocity.x = 2.0f;
	ball.velocity.y = 0.0f;

	ball.restitution = 0.8f;

	for (int i = 0; i < 600; i++) {
		physicsUpdate(&ball);

		printf("x = %.3f, y = %.3f\n",
			ball.position.x,
			ball.position.y);
	}
	return 0;
}

