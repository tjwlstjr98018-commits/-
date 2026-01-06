#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// 1. 데이터 구조 정의
struct Vector2 {
    float x, y;
};

enum State { IDLE, MOVING };

struct Body {
    struct Vector2 position;
    struct Vector2 velocity;
    struct Vector2 force;
    float mass;
    enum State state;
};

// 2. 물리 연산 함수 (Fixed Update용)
void ApplyPhysics(struct Body* b, float dt) {
    if (b->mass <= 0.0f) return;

    // 가속도 = 힘 / 질량 (a = F / m)
    struct Vector2 acceleration = { b->force.x / b->mass, b->force.y / b->mass };

    // 속도 변화량 계산
    b->velocity.x += acceleration.x * dt;
    b->velocity.y += acceleration.y * dt;

    // 위치 변화량 계산
    b->position.x += b->velocity.x * dt;
    b->position.y += b->velocity.y * dt;

    b->state = (b->velocity.x != 0 || b->velocity.y != 0) ? MOVING : IDLE;
}

int main() {
    struct Body ball = { {0, 0}, {0, 0}, {10, 0}, 1.0f, IDLE }; // 10의 힘을 오른쪽으로 가함

    const float DT = 0.01666f; // 고정 시간 간격 (약 60Hz)
    float accumulator = 0.0f;
    clock_t previous_time = clock();

    printf("시뮬레이션 시작...\n");

    // 메인 루프 (예시를 위해 100번만 반복)
    for (int i = 0; i < 100; i++) {
        clock_t current_time = clock();
        float frame_time = (float)(current_time - previous_time) / CLOCKS_PER_SEC;
        previous_time = current_time;

        accumulator += frame_time;

        // 핵심: 누적된 시간이 DT보다 크면, 그 횟수만큼 물리 연산을 반복 수행
        while (accumulator >= DT) {
            ApplyPhysics(&ball, DT);
            accumulator -= DT;
        }

        // 출력 (매 프레임 위치 확인)
        printf("위치: x=%.2f, y=%.2f | 상태: %s\n",
            ball.position.x, ball.position.y,
            (ball.state == MOVING ? "MOVING" : "IDLE"));
    }

    return 0;
}