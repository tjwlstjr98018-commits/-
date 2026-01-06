#include <stdio.h>

struct vec2 {
	float x;
	float y;
};

struct Body {
	struct vec2 position;
	struct vec2 velocity;
};

void PhysicsStep(struct Body* body, float dt) {
	const float gravity = -9.8;

	body->velocity.y += gravity * dt;
	body->position.y += body->velocity.y * dt;
}

int main() {
	struct Body player = { 0 };
	player.position.y = 10.0f; //시작높이

	float accumulator = 0.0f; //누적자? 누적하다 의 의미를 가진 accumulator
	const float FIXED_DT = 1.0f / 60.0f;

	while (1) {
		//테스트용임! 프레임시간을 고정한다
		float frameTime = FIXED_DT;
		accumulator += frameTime;

		while (accumulator >= FIXED_DT) {
			PhysicsStep(&player, FIXED_DT);
			accumulator -= FIXED_DT;
		}

		printf("y = %f\n", player.position.y);

		if (player.position.y <= 0.0f)
			break;
	}
	return 0;
}
