#include <stdio.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Vec2;

typedef struct {
	Vec2 pos;
	Vec2 vel;
} Ball;

Vec2 Vec2_Sub(Vec2 a, Vec2 b) {        //b위치-a위치 a와b사이의 거리의미
	Vec2 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

Vec2 Vec2_Mul(Vec2 v, float s) {          //v=원본벡터값(x,y) s=스칼라값 
	Vec2 r;
	r.x = v.x * s;
	r.y = v.y * s;
	return r;
}
    
float Vec2_Dot(Vec2 a, Vec2 b){         //내적  구하는거
	return a.x * b.x + a.y * b.y;
}

Vec2 Normalize(Vec2 v) {                    //노멀라이즈!!!!!!!
	float len = sqrt(v.x * v.x + v.y * v.y);

	if (len == 0) return v;

	v.x /= len;
	v.y /= len;
	return v;
}

//여기서 부터 중요
void ResolveCollision(Vec2* vel, Vec2 normal, float restitution, float friction) {
	normal = Normalize(normal);              // 노멀 단위화

	float vn = Vec2_Dot(*vel, normal);     // 노멀 방향 속도 크기

	if (vn == 0)return;   // 이미 떨어지고 있으면 무시
	
	Vec2 vn_vec = Vec2_Mul(normal, vn);    // 노멀 성분

	Vec2 vt = Vec2_Sub(*vel, vn_vec);    // 접선 성분

	float new_vn = -restitution * vn;    // 반사

	vt.x *= (1.0f - friction);    // 마찰
	vt.y *= (1.0f - friction);

	vel->x = normal.x * new_vn + vt.x;    // 합치기
	vel->y = normal.y * new_vn + vt.y;
}

int main()
{
    Ball ball;

    // 초기 위치
    ball.pos.x = 0;
    ball.pos.y = 10;

    // 초기 속도
    ball.vel.x = 3;
    ball.vel.y = 0;

    const float gravity = -9.8f;
    const float dt = 0.016f;

    const float restitution = 0.7f; // 탄성
    const float friction = 0.2f;    // 마찰

    for (int i = 0; i < 500; i++)
    {
        // 중력
        ball.vel.y += gravity * dt;

        // 이동
        ball.pos.x += ball.vel.x * dt;
        ball.pos.y += ball.vel.y * dt;

        // 바닥 충돌
        if (ball.pos.y <= 0)
        {
            ball.pos.y = 0;

            Vec2 normal = { 0, 1 }; // 바닥 위 방향

            ResolveCollision(&ball.vel, normal, restitution, friction);
        }

        printf("x=%.2f y=%.2f vx=%.2f vy=%.2f\n",
            ball.pos.x,
            ball.pos.y,
            ball.vel.x,
            ball.vel.y);
    }

    return 0;
}