#include "enemy.h"
#include "control.h"

enemy::enemy() {
	dartenemy.graph = LoadGraph("graph/dart.png");
	GetGraphSize(dartenemy.graph, &dartenemy.width, &dartenemy.height);
}