#include "load.h"

load::load() {
	et1bullet.graph = LoadGraph("graph/ETama1");
	GetGraphSize(et1bullet.graph, &et1bullet.width, &et1bullet.height);

	ziki1.graph = LoadGraph("graph/ziki1.png");
	GetGraphSize(ziki1.graph, &ziki1.width, &ziki1.height);
}