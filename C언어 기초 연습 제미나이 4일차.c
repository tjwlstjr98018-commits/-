#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Character {    // 총32바이트여서 패딩없음!(패딩:8의배수로 크기 맞춤)
	char name[20];   //문자열 아니여서 20바이트 할당(문자열일시 19바잍)
	int hp;
	void (*Attack)(struct Character*); // 구조체복사 안해서 8바이트만 전달(그래서 이게 8바이트라고)
} Character;

void BasicAttack(Character* self) {
	printf("[사격] %s 대원이 목표를 향해 공격합니다! (hp:%d)\n", self->name, self->hp);
}

int main() {
	int maxUnits = 5;       //임시유닛 동적할당

	// 1. 이중 포인터 선언 (Character 포인터 5개를 담을 '명부' 할당)
	// 명부 자체도 동적으로 할당합니다.
	Character** squad = (Character**)malloc(sizeof(Character*) * maxUnits);

	if (squad == NULL) return 1;

	// 2. 각 명부 칸에 실제 병사들을 하나씩 '개별 할당'
	for (int i = 0; i < maxUnits; i++) {
		squad[i] = (Character*)malloc(sizeof(Character)); //개별 병사 생성
		sprintf_s(squad[i]->name, sizeof(squad[i]->name), "Special_Op_%d", i);  //이게 머노;;
		squad[i]->hp = 100;
		squad[i]->Attack = BasicAttack; //자 왜 굳이 위에서 *Attack 함수를 썻을까 가독성때문 지저분한 코드는 나가라
	}

	printf("----- 부대 명부 작성 및 개별 배치 완료 -----\n\n");

	//3. 전체 공격 명령
	for (int i = 0; i < maxUnits; i++) {
		if (squad[i] != NULL) {   //병사가 살아있다면 (주소가 있다면)
			squad[i]->Attack(squad[i]);
		}
	}

	//4. [돌발상황] 2번 병사가 전사함 (메모리 해제 및 명부에서 삭제)
	printf("\n야! 2번병사 사망!\n");

	free(squad[2]); //메모리헤제 (2번병사)
	squad[2] = NULL; //명부에서 주소지움(중요!!! 안전창치임)

	//5. 다시 전체 명령 (2번은 건너뛰어야 함)
	for (int i = 0; i < maxUnits; i++) {
		if (squad[i] != NULL) {   //null 체크로 생존자만 골라냄 !=NULL 뜻은 이 포인터가 유효하다
			squad[i]->Attack(squad[i]);
		}
		else {
			printf(" \n %d 위치는 비어있습니다 ", i);
		}
	}

	//6. 모든 메모리 정리(역순으로 해제)
	for (int i = 0; i < maxUnits; i++) {
		if (squad[i] != NULL) free(squad[i]);  //살아남은 병사들 해제
	}
	free(squad);

	printf("\n작전 종료 및 모든 메모리 반납 완료\n");

	return 0;
}