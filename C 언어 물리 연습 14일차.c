#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    Vec2 pos;
    Vec2 vel;
    int grounded;
} Player;

// 벡터 함수들
Vec2 Add(Vec2 a, Vec2 b) {
    Vec2 r = { a.x + b.x, a.y + b.y };
    return r;
}

Vec2 Mul(Vec2 v, float s) {
    Vec2 r = { v.x * s, v.y * s };
    return r;
}

float Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 Normalize(Vec2 v) {
    float len = sqrt(v.x * v.x + v.y * v.y);
    if (len == 0) return v;
    v.x /= len;
    v.y /= len;
    return v;
}

// 바닥 충돌 해결
void SolveGround(Player* p) {

    float groundY = 0.0f;   // 바닥 높이

    if (p->pos.y <= groundY) {

        p->pos.y = groundY;   // 위치 보정

        if (p->vel.y < 0)
            p->vel.y = 0;     // 아래 속도 제거

        p->grounded = 1;
    }
    else {
        p->grounded = 0;
    }
}

int main() {

    Player p;

    p.pos.x = 0;
    p.pos.y = 5;

    p.vel.x = 3;
    p.vel.y = 0;

    p.grounded = 0;

    const float gravity = -20.0f;
    const float dt = 0.016f;

    for (int i = 0; i < 600; i++) {

        // 중력
        if (!p.grounded)
            p.vel.y += gravity * dt;

        // 이동
        p.pos = Add(p.pos, Mul(p.vel, dt));

        // 충돌 처리
        SolveGround(&p);

        printf("F:%3d  x=%.2f y=%.2f vx=%.2f vy=%.2f G=%d\n",
            i,
            p.pos.x, p.pos.y,
            p.vel.x, p.vel.y,
            p.grounded);
    }

    return 0;
}
