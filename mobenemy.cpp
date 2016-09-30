#include "enemy.h"
#include "control.h"

void bossenemy::allocation_enemygraph(std::list<enemy_element> *mob) {
	auto itr = mob->begin();
	switch (itr->graphnum) {
	case 0:
		DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), dartenemy.graph, true);
		break;

	}
}