#include <stdio.h>
#include <math.h>

/* =========================
   벡터 구조체 & 함수
========================= */

typedef struct {
    float x;
    float y;
} Vec2;

Vec2 Vec2_add(Vec2 a, Vec2 b) {
    Vec2 r = { a.x + b.x, a.y + b.y };
    return r;
}

Vec2 Vec2_sub(Vec2 a, Vec2 b) {
    Vec2 r = { a.x - b.x, a.y - b.y };
    return r;
}

Vec2 Vec2_mul(Vec2 v, float s) {
    Vec2 r = { v.x * s, v.y * s };
    return r;
}

float Vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 Vec2_normalize(Vec2 v) {
    float len = sqrtf(v.x * v.x + v.y * v.y);
    if (len == 0.0f) return v;

    v.x /= len;
    v.y /= len;
    return v;
}

/* =========================
   플레이어 구조체
========================= */

typedef struct {
    Vec2 pos;
    Vec2 vel;

    int grounded;
    Vec2 groundNormal;

    float jumpPower;
} Player;

/* =========================
   점프 입력 (테스트용)
========================= */

int IsJumpPressed(int frame) {
    if (frame % 120 == 0)
        return 1;
    return 0;
}

/* =========================
   충돌 해결
========================= */

void ResolveCollision(Player* p, Vec2 normal, float restitution, float friction)
{
    normal = Vec2_normalize(normal);

    float vn = Vec2_dot(p->vel, normal);

    // 이미 바깥쪽으로 나가고 있으면 무시
    if (vn >= 0.0f)
        return;

    p->grounded = 1;
    p->groundNormal = normal;

    // 법선 방향 속도 벡터
    Vec2 vn_vec = Vec2_mul(normal, vn);

    // 접선 방향 속도
    Vec2 vt = Vec2_sub(p->vel, vn_vec);

    // 반발 계산
    float new_vn = -restitution * vn;

    // 마찰
    vt.x *= (1.0f - friction);
    vt.y *= (1.0f - friction);

    // 최종 속도 재조합
    p->vel.x = normal.x * new_vn + vt.x;
    p->vel.y = normal.y * new_vn + vt.y;
}

/* =========================
   플레이어 업데이트
========================= */

void Player_Update(Player* p, float dt, int frame)
{
    const float gravity = -9.8f;
    const float restitution = 0.0f;
    const float friction = 0.2f;

    p->grounded = 0;

    /* 1️⃣ 중력 */
    p->vel.y += gravity * dt;

    /* 2️⃣ 이동 */
    p->pos.x += p->vel.x * dt;
    p->pos.y += p->vel.y * dt;

    Vec2 normal;

    /* 3️⃣ 평지 (y=0) */
    if (p->pos.y < 5.0f)
    {
        if (p->pos.y < 0.0f)
        {
            p->pos.y = 0.0f;
            normal.x = 0.0f;
            normal.y = 1.0f;

            ResolveCollision(p, normal, restitution, friction);
        }
    }
    /* 4️⃣ 경사면 */
    else if (p->pos.x < 12.0f)
    {
        float groundY = (p->pos.x - 5.0f) * 0.5f;

        if (p->pos.y <= groundY)
        {
            p->pos.y = groundY;

            // (0.5 기울기 선의 정규화된 법선)
            normal.x = -0.447f;
            normal.y = 0.894f;

            ResolveCollision(p, normal, restitution, friction);
        }
    }

    /* 5️⃣ 점프 */
    if (p->grounded && IsJumpPressed(frame))
    {
        Vec2 jump = Vec2_mul(p->groundNormal, p->jumpPower);
        p->vel = Vec2_add(p->vel, jump);
    }
}

/* =========================
   메인
========================= */

int main()
{
    Player p;

    p.pos.x = 0.0f;
    p.pos.y = 10.0f;

    p.vel.x = 2.0f;
    p.vel.y = 0.0f;

    p.grounded = 0;
    p.groundNormal.x = 0.0f;
    p.groundNormal.y = 1.0f;

    p.jumpPower = 8.0f;

    const float dt = 0.016f;

    for (int i = 0; i < 1000; i++)
    {
        Player_Update(&p, dt, i);

        printf("F:%3d  x:%6.2f y:%6.2f  vx:%6.2f vy:%6.2f  G:%d\n",
            i,
            p.pos.x,
            p.pos.y,
            p.vel.x,
            p.vel.y,
            p.grounded);
    }

    return 0;
}