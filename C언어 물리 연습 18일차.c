#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vec2 {
	float x, y;
} Vec2;

Vec2 Vec2_add(Vec2 a, Vec2 b) {
	Vec2 r = { a.x + b.x, a.y + b.y };
	return r;
}

Vec2 Vec2_mul(Vec2 a, float s) {
	Vec2 r = { a.x * s,a.y * s };
	return r;
}

float Vec2_dot(Vec2 a, Vec2 b) {
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
	Vec2 pos, vel;
	int grounded;
	Vec2 groundNormal;
	float jumpPower;
} Player;



typedef struct Input {
	int moveLeft, moveRight;
	int jump;
} Input;

Input GetInput( int frame ){
	Input in = { 0 };
	if (frame % 200 < 100)
		in.moveRight = 1;
	else in.moveLeft = 1;
	if (frame % 120 == 0)
		in.jump = 1;

	return in;
}


void ResolveCollision(Player* p, Vec2 normal) {
	normal = Normalize(normal);

	float vn = Vec2_dot(p->vel, normal);

	if (vn >= 0) return;

	p->grounded = 1;
	p->groundNormal = normal;

	Vec2 vn_vec = Vec2_mul(normal, vn);
	Vec2 vt = (Vec2){ p->vel.x - vn_vec.x, p->vel.y - vn_vec.y };

	float restitution = 0.0f;
	float friction = 0.2f;

	float new_vn = -restitution * vn;

	vt.x *= (1.0f - friction);
	vt.y *= (1.0f - friction);

	p->vel.x = normal.x * new_vn + vt.x;
	p->vel.y = normal.y * new_vn + vt.y;
}

void Player_Update(Player* p, Input in) {
	float moveSpeed = 8.0f;

	if (in.moveRight)
		p->vel.x = moveSpeed;
	else if (in.moveLeft)
		p->vel.x = -moveSpeed;
	else
		p->vel.x = 0;

	if (p->grounded && in.jump)
	{
		Vec2 jump = Vec2_mul(p->groundNormal, p->jumpPower);
		p->vel.x += jump.x;
		p->vel.y += jump.y;
	}
}


void Physics_Update(Player* p, float dt) {
	float gravity = -25.0f;

	p->grounded = 0;

	p->vel.y += gravity * dt;

	p->pos.x += p->vel.x * dt;
	p->pos.y += p->vel.y * dt;

	if (p->pos.y <= 0)
	{
		p->pos.y = 0;
		Vec2 normal = { 0, 1 };
		ResolveCollision(p, normal);
	}
}


int main()
{
	int playerCount = 3;

	Player* players = (Player*)malloc(sizeof(Player) * playerCount);

	for (int i = 0; i < playerCount; i++)
	{
		players[i].pos = (Vec2){ i * 2.0f, 10 };
		players[i].vel = (Vec2){ 0, 0 };
		players[i].grounded = 0;
		players[i].groundNormal = (Vec2){ 0,1 };
		players[i].jumpPower = 10.0f;
	}

	float dt = 0.016f;

	for (int frame = 0; frame < 300; frame++)
	{
		for (int i = 0; i < playerCount; i++)
		{
			Input in = GetInput(frame);

			Player_Update(&players[i], in);

			Physics_Update(&players[i], dt);

			printf("F:%3d P%d x:%.2f y:%.2f\n",
				frame, i,
				players[i].pos.x,
				players[i].pos.y);
		}
	}

	free(players);

	return 0;
}