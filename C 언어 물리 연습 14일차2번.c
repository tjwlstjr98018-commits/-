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


/* ===== 벡터 ===== */

Vec2 Add(Vec2 a, Vec2 b) {
    return (Vec2) { a.x + b.x, a.y + b.y };
}

Vec2 Sub(Vec2 a, Vec2 b) {
    return (Vec2) { a.x - b.x, a.y - b.y };
}

Vec2 Mul(Vec2 v, float s) {
    return (Vec2) { v.x* s, v.y* s };
}

float Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 Normalize(Vec2 v) {
    float l = sqrt(v.x * v.x + v.y * v.y);
    if (l == 0) return v;
    return (Vec2) { v.x / l, v.y / l };
}


/* ===== 충돌 반응 ===== */

void Slide(Vec2* vel, Vec2 normal) {

    normal = Normalize(normal);

    float vn = Dot(*vel, normal);

    if (vn >= 0) return;

    Vec2 remove = Mul(normal, vn);

    *vel = Sub(*vel, remove);
}


/* ===== 월드 ===== */

float GetGroundY(float x) {

    // 경사면
    if (x > 5 && x < 15)
        return (x - 5) * 0.4f;

    return 0;
}


void SolveCollision(Player* p) {

    p->grounded = 0;

    /* 바닥 */

    float gy = GetGroundY(p->pos.x);

    if (p->pos.y <= gy) {

        p->pos.y = gy;

        Vec2 n = { 0,1 };

        if (p->pos.x > 5 && p->pos.x < 15)
            n = Normalize((Vec2) { -0.4f, 1 });

        Slide(&p->vel, n);

        p->grounded = 1;
    }


    /* 벽 */

    if (p->pos.x < 0) {

        p->pos.x = 0;

        Vec2 n = { 1,0 };

        Slide(&p->vel, n);
    }

    if (p->pos.x > 20) {

        p->pos.x = 20;

        Vec2 n = { -1,0 };

        Slide(&p->vel, n);
    }
}


/* ===== 메인 ===== */

int main() {

    Player p;

    p.pos = (Vec2){ 2,5 };
    p.vel = (Vec2){ 5,0 };
    p.grounded = 0;

    const float gravity = -25;
    const float dt = 0.016f;

    for (int i = 0; i < 800; i++) {

        /* 중력 */
        if (!p.grounded)
            p.vel.y += gravity * dt;


        /* 이동 */
        p.pos = Add(p.pos, Mul(p.vel, dt));


        /* 충돌 */
        SolveCollision(&p);


        printf("F:%3d  x=%.2f y=%.2f vx=%.2f vy=%.2f G=%d\n",
            i,
            p.pos.x,
            p.pos.y,
            p.vel.x,
            p.vel.y,
            p.grounded);
    }
}