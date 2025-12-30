#include <stdio.h> //공이 10m에서 중력이 누적되어 위치가 0이 되면 속도가 0 으로 변하는것 구현

struct Vector2 {
	float x;
	float y;
};

struct Ball {
	struct Vector2 position;
	struct Vector2 velocity;
	struct Vector2 force;
	float mass;
};

void Addforce(struct Ball* ball, struct Vector2 f) {
	ball->force.x += f.x;
	ball->force.y += f.y;
}
void physicsupdate(struct Ball* ball, float dt) {
	struct Vector2 acceleration;
	acceleration.x = ball->force.x / ball->mass;
	acceleration.y = ball->force.y / ball->mass;

	ball->velocity.x += acceleration.x * dt;
	ball->velocity.y += acceleration.y * dt;

	ball->position.x += ball->velocity.x * dt;
	ball->position.y += ball->velocity.y * dt;

	//바닥 충돌 추가
	if (ball->position.y <= 0.0f) {
		ball->position.y = 0.0f;
		ball->velocity.y = 0.0f;
	}

	ball->force.x = 0.0f;
	ball->force.y = 0.0f;
}

int main() {
	struct Ball po = {
		{0.0f, 10.0f},
		{0.0f, 0.0f},
		{0.0f, 0.0f},
		1.0f
	};
	struct Vector2 gravity = { 0.0f, -9.8f * po.mass };
	float dt = 0.016f;

	while (1) {
		Addforce(&po, gravity);
		physicsupdate(&po, dt);

		printf("현재 높이 y= %f 현재 속도 y= %f\n ", po.position.y, po.velocity.y);

		if (po.position.y <= 0.0f) {
			printf("바닥에 닿음\n");
			break;
		}
		getchar();
	}
	return 0;
};