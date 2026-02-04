#include <stdio.h>

// 1. 무기들의 공통 규격(함수 포인터 타입) 정의
// 반환값 없고, 매개변수 없는 함수들의 주소를 담는 'WeaponFunc'라는 타입을 만듭니다.
typedef void (*WeaponFunc)();

// 2. 각 무기별 실제 동작 함수
void FirePistol() {
    printf("[권총] 탕! ----------------- (데미지: 10)\n");
}

void FireRifle() {
    printf("[소총] 타타탕! ------------- (데미지: 30)\n");
}

void FireSniper() {
    printf("[스나이퍼] 콰앙! ------------ (데미지: 100, 반동 큼)\n");
}

// 3. 캐릭터 구조체
typedef struct {
    char name[20];
    WeaponFunc currentWeapon; // 현재 장착된 무기(함수 주소)
} Player;

int main() {
    Player p1 = { "Soldier_1", NULL };

    int choice;
    while (1) {
        printf("\n[1] 권총 [2] 소총 [3] 스나이퍼 [4] 공격 [0] 종료\n");
        printf("선택: ");
        scanf_s("%d", &choice);

        if (choice == 1) p1.currentWeapon = FirePistol;
        else if (choice == 2) p1.currentWeapon = FireRifle;
        else if (choice == 3) p1.currentWeapon = FireSniper;
        else if (choice == 4) {
            if (p1.currentWeapon != NULL) {
                // 함수 포인터를 통해 현재 무기 발사!
                p1.currentWeapon();
            }
            else {
                printf("무기가 없습니다!\n");
            }
        }
        else if (choice == 0) break;
    }

    return 0;
}