#include <stdio.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Vec2;

Vec2 Vec2_Add(Vec2 a, Vec2 b) {        // 벡터 덧셈 여러 힘이나 움직임이 합쳐질 때 사용(위치,속도 누적
	Vec2 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

Vec2 Vec2_Mul(Vec2 v, float s) {      // 벡터v와 소수 s값을 받는 함수? 크기(길이)를 조절하고 싶을 때 사용(크기만 변화, 방향 유지
	Vec2 r;
	r.x = v.x * s;
	r.y = v.y * s;
	return r;
}

float Vec2_Dot(Vec2 a, Vec2 b) {      //벡터 내적 만약 값>0 노멀방향이동중 값<0 벽을 향해 이동중 값=0 평행
	return a.x * b.x + a.y * b.y;
}

void ReflectVelocity(Vec2* velocity, Vec2 nomal, float restitution) {   // 이걸 이해하면 앞으로 C언어 물리엔진은 쉬울듯 
	float vn = Vec2_Dot(*velocity, nomal);

	//이미 벽에서 멀어지는 중이면 반사 X
	if (vn > 0.0f)
		return;

	float impulse = (1.0f + restitution) * vn;
	Vec2 correction = Vec2_Mul(nomal, impulse);

	velocity->x -= correction.x;
	velocity->y -= correction.y;
}

int main() {
	Vec2 Velocity = { 0.0f, -10.0f }; //아래로 떨어지는 속도
	Vec2 nomal = { 0.0f, 1.0f };  //바닥 노멀
	float restitution = 0.8f;   //탄성

	printf("충돌 전 속도: (%f, %f)\n", Velocity.x, Velocity.y);

	ReflectVelocity(&Velocity, nomal, restitution); //ReflectVelocity는 반사속도라는 뜻

	printf("충돌 후 속도: (%f, %f)\n", Velocity.x, Velocity.y);

	return 0;
}