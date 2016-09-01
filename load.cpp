#include "load.h"

load::load() {
	et1bullet.graph = LoadGraph("graph/ETama1");
	GetGraphSize(et1bullet.graph, &et1bullet.width, &et1bullet.height);

	ziki1.graph = LoadGraph("graph/ziki1.png");
	GetGraphSize(ziki1.graph, &ziki1.width, &ziki1.height);

	ziki1bullet.graph = LoadGraph("graph/ZTama.png");
	GetGraphSize(ziki1bullet.graph, &ziki1bullet.width, &ziki1bullet.height);
}

int load::ziki1graph_pass() {
	return ziki1.graph;
}
int load::ziki1width_pass() {
	return ziki1.width;;
}
int load::ziki1height_pass() {
	return ziki1.height;
}

int load::ziki1bulletgraph_pass() {
	return ziki1bullet.graph;
}
int load::ziki1bulletwidth_pass() {
	return ziki1bullet.width;;
}
int load::ziki1bulletheight_pass() {
	return ziki1bullet.height;
}