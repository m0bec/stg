#include "load.h"

load::load() {
	et1bullet.graph = LoadGraph("graph/ETama1");
	GetGraphSize(et1bullet.graph, &et1bullet.width, &et1bullet.height);
}