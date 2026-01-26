#include <stdio.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Vec2;

float Vec2_Dot(Vec2 a, Vec2 b) {
	return a.x * b.x + a.y * b.y;
}

Vec2 Vec2_Mul(Vec2 v, float s) {
	Vec2 r;
	r.x = v.x * s;
	r.y = v.y * s;
	return r;
}

Vec2 Normalize(Vec2 v) { 
	float len = sqrt(v.x * v.x + v.y * v.y);

	if (len == 0) return v;

	Vec2 r;
	r.x = v.x / len;
	r.y = v.y / len;
	return r;
}

void Reflect(Vec2* vel, Vec2 normal, float restitution) { 
	//반드시 벡터단위
	normal = Normalize(normal);

	float vn = Vec2_Dot(*vel, normal);

	if (vn > 0)return;

	float j = (1.0f + restitution) * vn;

	Vec2 impulse = Vec2_Mul(normal, j);

	vel->x -= impulse.x;
	vel->y -= impulse.y;
}

int main() {
	Vec2 v = { 5,-10 };
	Vec2 n = { 0,1 };

	Reflect(&v, n, 0.7f);
	
	printf("vx = %f, vy = %f \n", v.x, v.y);

}
