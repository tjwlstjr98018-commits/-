#include <stdio.h>
#include <math.h>

typedef struct Vec2 {
	float x, y;
} Vec2;

Vec2 Vec2_Add(Vec2 a, Vec2 b) {
	Vec2 r = { a.x + b.x, a.y + b.y };
	return r;
}

Vec2 Vec2_Sub(Vec2 a, Vec2 b) {
	Vec2 r = { a.x - b.x, a.y - b.y };
	return r;
}

Vec2 Vec2_Mul(Vec2 v, float s) {
	Vec2 r = { v.x * s, v.y * s };
	return r;
}

float Vec2_Dot(Vec2 a, Vec2 b) {
	return a.x * b.x + a.y * b.y;
}

Vec2 Normalize(Vec2 v) {
	float len = sqrt(v.x * v.x + v.y * v.y);

	if (len == 0) return v;

	v.x /= len;
	v.y /= len;
	return v;
}

typedef struct Player {
	Vec2 pos;
	Vec2 vel;

	int grounded;
	Vec2 groundNormal;

	float jumpPower;
} Player;

typedef struct Input {
	int moveLeft;
	int moveRight;
	int Jump;
} Input;

//가짜입력
Input GetInput(int frame) {
	Input in = { 0 };
	
	if (frame % 200 < 100)
		in.moveRight = 1;
	else
		in.moveLeft = 1;

	if (frame % 120 == 0)
		in.Jump = 1;

	return in;
}

void ResolveCollision(Player* p, Vec2 normal, float restitution, float friction) {
	normal = Normalize(normal);

	float vn = Vec2_Dot(p->vel, normal);

	if (vn >= 0) return;

	p->grounded = 1;
	p->groundNormal = normal;

	Vec2 vn_vec = Vec2_Mul(normal, vn);
	Vec2 vt = Vec2_Sub(p->vel, vn_vec);

	float new_vn = -restitution * vn;

	vt.x *= (1.0f - friction);
	vt.y *= (1.0f - friction);

	p->vel.x = normal.x * new_vn + vt.x;
	p->vel.y = normal.y * new_vn + vt.y;
}

void Player_Update(Player* p, Input in)
{
	const float moveSpeed = 8.0f;

	if (in.moveRight)
		p->vel.x = moveSpeed;
	else if (in.moveLeft)
		p->vel.x = -moveSpeed;
	else
		p->vel.x = 0;

	if (p->grounded && in.Jump)
	{
		Vec2 jump = Vec2_Mul(p->groundNormal, p->jumpPower);
		p->vel = Vec2_Add(p->vel, jump);
	}
}

void Physics_Update(Player* p, float dt) {
	const float gravity = -25.0f;

	p->grounded = 0;

	p->vel.y += gravity * dt;

	p->pos = Vec2_Add(p->pos, Vec2_Mul(p->vel, dt));

	//충돌
	if (p->pos.y <= 0) {
		p->pos.y = 0;

		Vec2 normal = { 0,1 };

		ResolveCollision(p, normal, 0.0f, 0.2f);
	}
}

int main() {
	Player p;

	p.pos = (Vec2) { 0, 10 };
	p.vel = (Vec2) { 0,0 };
	p.grounded = 0;
	p.groundNormal = (Vec2) { 0,1 };
	p.jumpPower = 10.0f;

	const float dt = 0.016f;

	for (int i = 0; i < 500; i++) {
		Input in = GetInput(i);
		Player_Update(&p, in);
		Physics_Update(&p, dt);

		printf("F:%3d  x:%.2f y:%.2f  vx=%.2f vy=%.2f G=%d\n",
			i, p.pos.x, p.pos.y, p.vel.x, p.vel.y, p.grounded);
	}
	return 0;
}