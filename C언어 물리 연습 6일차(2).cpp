#include <stdio.h>

struct Vec2 { 
	float x;
	float y;
};

struct Body {
	struct Vec2 position;
	struct Vec2 velocity;
};

void physicsStep(struct Body* body, float dt) {
	const float gravity = -9.8f;

	
	body->velocity.y += gravity * dt;
	
	body->position.y += body->velocity.y * dt;
	
	if (body->position.y < 0.0f) { //변경점
		body->position.y = 0.0f; 
		
		float restitution = 0.8f; //1.0 == 완전 탄성 0.0 == 완전 비탄성
		body->velocity.y = -body->velocity.y * restitution; //바디 앞에 - 의미는 방향반전임 위 <-> 아래 여기선 아래->위 로 쓰임
		// 벨로시티.y는 충돌직전 속도, 레스티투션은 에너지보존 비율 예시(바닥에 -10만큼 떨어짐 {레스티투션= 0.8f} +8만큼 튀어오름
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

	}
}
