#include <stdio.h>
struct vector2{
	float x;
	float y;
};

int main(){
	struct vector2 position = { 0.0f,0.0f };
	struct vector2 velocity = { 1.0f,1.0f };
	
	float delataime = 0.016f; //약 60프레임

	while (1) {
		position.x += velocity.x * delataime;
		position.y += velocity.y * delataime;
		printf("pos = (%f,%f)\n", position.x, position.y);
		getchar();
	}

	return 0;
}