#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y;
} Vec2;

/* ================= 벡터 기본 ================= */

float Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 Add(Vec2 a, Vec2 b) {
    return (Vec2) { a.x + b.x, a.y + b.y };
}

Vec2 Sub(Vec2 a, Vec2 b) {
    return (Vec2) { a.x - b.x, a.y - b.y };
}

Vec2 Mul(Vec2 v, float s) {
    return (Vec2) { v.x* s, v.y* s };
}

float Length(Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vec2 Normalize(Vec2 v) {
    float len = Length(v);
    if (len == 0) return v;
    return Mul(v, 1.0f / len);
}

/* ================= 물리 ================= */

typedef struct {
    Vec2 pos;
    Vec2 vel;
} Player;

const float Gravity = -20.0f;
const float DT = 0.016f;
const float Friction = 0.2f;

/* ================= 슬라이딩 처리 ================= */

void ResolveSlide(Player* p, Vec2 normal) {

    normal = Normalize(normal);

    // 속도 → 법선 성분 크기
    float vn = Dot(p->vel, normal);

    // 바닥쪽으로만 처리
    if (vn < 0) {

        // 법선방향 속도 벡터
        Vec2 vn_vec = Mul(normal, vn);

        // 접선방향 속도
        Vec2 vt = Sub(p->vel, vn_vec);

        // 마찰
        vt = Mul(vt, 1.0f - Friction);

        // 최종 속도
        p->vel = vt;
    }
}

/* ================= 메인 ================= */

int main() {

    Player p;

    p.pos = (Vec2){ 0, 50 };
    p.vel = (Vec2){ 5, 0 };

    // 30도 경사면 노멀
    Vec2 slopeNormal = Normalize((Vec2) { -0.5f, 1.0f });

    for (int i = 0; i < 300; i++) {

        // 중력
        p.vel.y += Gravity * DT;

        // 위치
        p.pos = Add(p.pos, Mul(p.vel, DT));

        // 바닥 충돌
        if (p.pos.y < 0) {

            p.pos.y = 0;

            ResolveSlide(&p, slopeNormal);
        }

        printf("x=%.2f y=%.2f vx=%.2f vy=%.2f\n",
            p.pos.x, p.pos.y, p.vel.x, p.vel.y);
    }
}