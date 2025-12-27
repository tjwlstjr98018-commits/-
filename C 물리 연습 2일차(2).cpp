#include <stdio.h>

struct vector2 {
	float x;
	float y;
};

struct vector2 Add(struct vector2 a, struct vector2 b) {   // 이해 필요 요망
	return (struct vector2) { a.x + b.x, a.y + b.y };
}

struct vector2 Mul(struct vector2 v, float s) {     // 이게 뭔지 이해해야할듯
	return (struct vector2) { v.x* s, v.y* s };
}

int main() {
	struct vector2 position = { 0.0f, 10.0f };  //위에서 시작
	struct vector2 velocity = { 0.0f, 0.0f };
	struct vector2 gravity = { 0.0f, -9.8f };

	float dt = 0.016f;

	while (1) {
		velocity = Add(velocity, Mul(gravity, dt));
		position = Add(position, Mul(velocity, dt));

		if (position.y <= 0.0f) {
			position.y = 0.0f;
			velocity.y = 0.0f;
		}
		printf("y = %f\n", position.y);
		getchar();
	}
	return 0;
}