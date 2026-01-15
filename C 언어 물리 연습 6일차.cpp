#include <stdio.h>

struct Vec2 { //Vec2 = Vector2
	float x;
	float y;
};

struct Body {
	struct Vec2 position;
	struct Vec2 velocity;
};

void physicsStep(struct Body* body, float dt) {
	const float gravity = -9.8f;

	// 중력을 적.용 한다
	body->velocity.y += gravity * dt;
	// 위치를 적.분 한다
	body->position.y += body->velocity.y * dt;
	// 충돌을 구.현 한다
	if (body->position.y < 0.0f) {
		body->position.y = 0.0f;  // 위치를 보.정 한다
		body->velocity.y = 0.0f;  // 속도를 멈.춘 다 (위치만 멈출시 바닥 뚫고 나감)
	}
}

int main() {
	struct Body player = { 0 };
	player.position.y = 10.0f; // start y value

	float accumulater = 0.0f;
	const float FIXED_DT = 1.0f / 60.0f;

	while (1) {
		float fremeTime = FIXED_DT;
		accumulater += fremeTime;

		while (accumulater >= FIXED_DT) {
			physicsStep(&player, FIXED_DT);
			accumulater -= FIXED_DT;
		}
		
		printf("y = %f\n", player.position.y);

		if (player.position.y <= 0) {
			return 0;
		}

	}
	

}