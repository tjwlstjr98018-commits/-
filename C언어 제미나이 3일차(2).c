#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Character {
	char name[20];
	int hp;
	int damage;
	void (*Attack)(struct Character*);
	void (*TakeDamage)(struct Character*, int);
} Character;

void BasicAttack(Character* self) {
	printf("[공격] %s 대원이 %d의 위력으로 사격\n", self->name, self->damage);
}

void BasicTakeDamage(Character* self, int amunt) {
	self->hp -= amunt;
	printf("[피격] %s 대원이 %d 만큼의 피해 입음 [남은 hp %d]\n", self->name, amunt, self->hp);
}

int main() {
	int unitCount;
	printf("부대에 배치할 병사수 입력:\n");
	scanf_s("%d", &unitCount);

	Character* squad = (Character*)malloc(sizeof(Character) * unitCount);
	//메모리 할당 앞 캐릭터는 이걸 int,char등어떤형태로 쓸지 선택(여기선 구조체 크기만큼씀)

	if (squad == NULL) {
		printf("메모리 곱창났다!!!!!!!!\n");
		return 1;
	}

	//대원들 초기화
	for (int i = 0; i < unitCount; i++) {
		sprintf_s(squad[i].name, sizeof(squad[i].name), "soldeier_%d", i);
		squad[i].hp = 100;
		squad[i].damage = 25;
		squad[i].TakeDamage = BasicTakeDamage;

		squad[i].Attack = BasicAttack;
		squad[i].TakeDamage = BasicTakeDamage;
	}

	printf("\n----스쿼드 전원 배치 완료-----\n\n");

	//수어사이드 어택
	for (int i = 0; i < unitCount; i++) {
		squad[i].Attack(&squad[i]);
	}

	printf("\n-----수어사이드 전멸중-----\n");

	//특정병사 피해
	if (unitCount > 0) {
		squad[0].TakeDamage(&squad[0], 30);
	}
	
	//메모리 반남(끝난거지 스쿼드 전멸해서 아님)
	//게임 종료전or전멸시 메모리free해줘야 누수없음
	free(squad);
	printf("\n작전 종료 메모리반납\n");

	return 0;

}