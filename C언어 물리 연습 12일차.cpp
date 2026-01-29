#include <stdio.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Vec2;

Vec2 Vec2_add(Vec2 a, Vec2 b) {
	Vec2 r = { a.x + b.x,a.y+b.y };
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


typedef struct {
	Vec2 pos;
	Vec2 vel;
} Player;


int grounded = 0;
Vec2 groundNormal = { 0,1 };


void ResolveCollision(Vec2* vel, Vec2 normal, float restitution, float friction) {
	normal = Normalize(normal);

	float vn = Vec2_Dot(*vel, normal);

	if (vn >= 0)return;

	grounded = 1;
	groundNormal = normal;

	Vec2 vn_vec = Vec2_Mul(normal, vn);
	Vec2 vt = Vec2_Sub(*vel, vn_vec);

	float new_vn = -restitution * vn;

	vt.x *= (1.0f - friction);
	vt.y *= (1.0f - friction);

	vel->x = normal.x * new_vn + vt.x;
	vel->y = normal.y * new_vn + vt.y;
}


int IsJumpPressed(int frame) {
	if (frame % 120 == 0)
		return 1;

	return 0;
}


int main() {
	Player p;

	p.pos.x = 0;
	p.pos.y = 10;

	p.vel.x = 2;
	p.vel.y = 0;

	const float gravity = -9.8f;
	const float dt = 0.016f;

	const float restitution = 0.0f;
	const float friction = 0.2f;
	const float jumpower = 8.0f;

	for (int i = 0; i < 1000; i++) {
		grounded = 0;

		p.vel.y += gravity * dt;

		p.pos.x += p.vel.x * dt;
		p.pos.y += p.vel.y * dt;

		Vec2 normal;

		if (p.pos.y < 5) {
			if (p.pos.y < 0) {
				p.pos.y = 0;
				normal.x = 0;
				normal.y = 1;
				ResolveCollision(&p.vel, normal, restitution, friction);
			}
		}

		else if (p.pos.x < 12) {
			float groundY = (p.pos.x - 5) * 0.5f;

			if (p.pos.y <= groundY) {
				p.pos.y = groundY;

				normal.x = -0.447f;
				normal.y = 0.894f;

				ResolveCollision(&p.vel, normal, restitution, friction);
			}
		}

		if (grounded && IsJumpPressed(i)) {
			Vec2 jump = Vec2_Mul(groundNormal, jumpower);
			p.vel = Vec2_add(p.vel, jump);
		}

		printf("F:%3d  x:%.2f y:%.2f vx=%.2f vy=%.2f G=%d\n",
			i, p.pos.x, p.pos.y, p.vel.x, p.vel.y, grounded);
	}
	return 0;
}	