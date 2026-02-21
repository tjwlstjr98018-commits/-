#include <stdio.h>
#include <string.h>

typedef void (*ActionFunc)(struct Character*);

typedef struct Character {
	char name[20];   //실제로는 끝에 /0들어가서19자리
	int hp;
	int damage;

	ActionFunc Attack;
	ActionFunc TakeDamage;
} Character;

void BasicAttack(Character* self) {
	printf("[%s] 가 %d의 데미지로 공격합니다!\n", self->name, self->damage);
}

void BasicTakeDamage(Character* self) {
	printf("[%s]가 공격받았습니다! 남은 체력: %d\n", self->name, self->hp);
}

int main() {
	Character Player;
	strcpy_s(Player.name, sizeof(Player.name), "Assault_Soldier");
	Player.hp = 100;
	Player.damage = 25;

	Player.Attack = BasicAttack;
	Player.TakeDamage = BasicTakeDamage;

	printf("-----오딩어 게임 띠딲-----\n");
	Player.Attack(&Player);
	Player.TakeDamage(&Player);

	return 0;
}