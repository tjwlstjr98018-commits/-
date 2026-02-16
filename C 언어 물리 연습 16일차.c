#include <stdio.h>
#include <math.h>

typedef struct Vec2 {
	float x, y;
} Vec2;

Vec2 Normalize(Vec2 a) {                                       // 노멀라이즈 피타고라스 후 원래 x,y값에 각각 나눠서 리턴 그러 크기1
	float len = sqrt(a.x * a.x + a.y * a.y);
	if (len == 0) return a;
	a.x /= len;
	a.y /= len;
	return a;
}

int main() {
	Vec2 pos = { 0,0 };
	float angle = 0.785f;
	float speed = 5.0f;
	float dt = 0.016f;

	//카메라 기준 벡터
	Vec2 forward = { cos(angle), sin(angle) };  //sin 빗변 분의 높이 cos 빗변분의 높이
	Vec2 right = { -forward.y, forward.x };     //공식임 자세한건 메일 확인

	//W+D 누른상황
	Vec2 move = { 0,0 };
	move.x += forward.x;
	move.y += forward.y;

	move.x += right.x;
	move.y += right.y;

	move = Normalize(move);

	pos.x += move.x * speed * dt;
	pos.y += move.y * speed * dt;

	printf("pos: %f %f\n", pos.x, pos.y);
}