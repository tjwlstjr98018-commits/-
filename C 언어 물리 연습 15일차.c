#include <stdio.h>
#include <Windows.h>
#include <math.h>

typedef struct Vec2 {
	float x, y;
} Vec2;

typedef struct Input {
	int W, A, S, D;
	int Jump;
} Input;

typedef struct Player {
	Vec2 pos, vel;
	int grounded;
} Player;

// 우 주 상 수
const float MOVE_ACCEL = 40.0f;
const float MAX_SPEED  = 8.0f;
const float FRICTION   = 8.0f;
const float GRAVITY    = -25.0f;
const float JUMP_FORCE = 10.0f;
const float DT         = 0.016f;

//노멀라이즈,벡터
float Length(Vec2 v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

Vec2 Normalize(Vec2 v) {   //노멀라이즈 len 값*x,y 각각 1나옴 방향만 남김
	float len = Length(v);
	if (len == 0) return (Vec2) { 0, 0 };
	return (Vec2) { v.x / len, v.y / len };
}

// 입력 읽기
Input GetInput(void) {
	Input in = { 0 };

	if (GetAsyncKeyState('W') & 0x8000) in.W = 1;
	if (GetAsyncKeyState('A') & 0x8000) in.A = 1;
	if (GetAsyncKeyState('S') & 0x8000) in.S = 1;
	if (GetAsyncKeyState('D') & 0x8000) in.D = 1;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) in.Jump = 1;

	return in;
}


//입력->방향벡터
Vec2 GetWishDir(Input In) {
	Vec2 dir = { 0,0 };

	if (In.W) dir.y += 1;
	if (In.S) dir.y -= 1;
	if (In.D) dir.x += 1;
	if (In.A) dir.x -= 1;

	return Normalize(dir);
}

//이동 가속 
void ApplyMovement(Player* p, Vec2 dir) {
	p->vel.x += dir.x * MOVE_ACCEL * DT;
	p->vel.y += dir.y * MOVE_ACCEL * DT;

	// 속도 제한 
	if (Length(p->vel) > MAX_SPEED) {
		Vec2 n = Normalize(p->vel);
		p->vel.x = n.x * MAX_SPEED;
		p->vel.y = n.y * MAX_SPEED;
	}
}

// 마찰
void ApplyFriction(Player* p) {
	if (!p->grounded) return;

	p->vel.x -= p->vel.x * FRICTION * DT;
}

//중력
void ApplyGravity(Player* p) {
	if (!p->grounded)
		p->vel.y += GRAVITY * DT;
}

//점프

void TryJump(Player* p, Input In) {
	if (In.Jump && p->grounded) {
		p->vel.y = JUMP_FORCE;
		p->grounded = 0;
	}
}

//위치
void UpdatePosition(Player* p) {
	p->pos.x += p->vel.x * DT;
	p->pos.y += p->vel.y * DT;
}

//바닥 충돌
void ResolveGround(Player* p) {
	if (p->pos.y <= 0) {
		p->pos.y = 0;
		p->vel.y = 0;
		p->grounded = 1;
	}
}

int main(void) {
	Player p = { 0 };
	p.pos.y = 0;
	p.grounded = 1;

	while (1) {
		Input in = GetInput();

		Vec2 WishDir = GetWishDir(in);

		ApplyMovement(&p, WishDir);
		ApplyFriction(&p);
		TryJump(&p, in);
		ApplyGravity(&p);
		UpdatePosition(&p);
		ResolveGround(&p);

		system("cls");
		printf("POS x: %.2f y: %.2f\n", p.pos.x, p.pos.y);
		printf("VEL x: %.2f Y: %.2f\n", p.vel.x, p.vel.y);
		printf("GROUND: %d\n", p.grounded);

		Sleep(16);

	}
}