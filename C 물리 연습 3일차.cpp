#include <stdio.h>

struct Vector2 {
	float x;
	float y;
};

struct Body {
	struct Vector2 position;
	struct Vector2 velocity;
	struct Vector2 force;
	float mass;
};

void AddForce(struct Body* body, struct Vector2 f) {
	body->force.x += f.x;
	body->force.y += f.y;
}

void Physicsupdate(struct Body* body, float dt) {  // 사실 여기서부터는 뭘 의미하는지 잘 모름 ;;
	struct Vector2 acceleration;
	acceleration.x = body->force.x / body->mass;
	acceleration.y = body->force.y / body->mass;

	body->velocity.x += acceleration.x * dt;
	body->velocity.y += acceleration.y * dt;

	body->position.x += body->velocity.x * dt;
	body->position.y += body->velocity.y * dt;

	body->force.x = 0.0f;
	body->force.y = 0.0f;
};

int main() {
	struct Body player = {
		{0.0f, 0.0f},
		{0.0f, 0.0f},
		{0.0f, 0.0f},
		1.0f
	};

	struct Vector2 gravity = { 0.0f, -9.8f * player.mass };
	float dt = 0.016f; //약60frame 의미

	while (1) {
		AddForce(&player, gravity);
		Physicsupdate(&player, dt);

		printf("y = %f\n", player.position.y);
		getchar();
	}
}