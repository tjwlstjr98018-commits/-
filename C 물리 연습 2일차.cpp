#include <stdio.h>

struct vector2 {
	float x;
	float y;
};

struct vector2 addvector(struct vector2 a,struct vector2 b) {
	struct vector2 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}	

struct vector2 multiplyvector(struct vector2 v, float s){
	struct vector2 result;
	result.x = v.x * s;
	result.y = v.y * s;
	return result;
}

int main() {
	struct vector2 position = { 0.0f, 0.0f };
	struct vector2 velocity = { 0.0f, 0.0f };
	struct vector2 acceleration = { 0.0f, -9.8f };

	float deltatime = 0.016f;

	velocity = addvector(velocity, multiplyvector(acceleration, deltatime));
	position = addvector(position, multiplyvector(velocity, deltatime));

	printf("pos = (%f, %f)", position.x, position.y);
	getchar();
	return 0;
}