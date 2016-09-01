#include "ziki.h"

ziki::ziki() {
	x = 0;
	y = 0;
	presenceflag = true;
	lifeflag = true; 	
}

void ziki::pass_load(int loadgraph, int loadwidth, int loadheight) {
	graph = loadgraph;
	width = loadwidth;
	height = loadheight;
}

void ziki::draw() {
	DrawGraph(x, y, graph, true);
}

void ziki::move() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (input_joypad & PAD_INPUT_UP) {
		if (input_joypad & PAD_INPUT_2) {
			y -= slowmove;
		}
		else {
			y -= normalmove;
		}
	}
	if (input_joypad & PAD_INPUT_DOWN) {
		if (input_joypad & PAD_INPUT_2) {
			y += slowmove;
		}
		else {
			y += normalmove;
		}
	}
	if (input_joypad & PAD_INPUT_LEFT) {
		if (input_joypad & PAD_INPUT_2) {
			x -= slowmove;
		}
		else {
			x -= normalmove;
		}
	}
	if (input_joypad & PAD_INPUT_RIGHT) {
		if (input_joypad & PAD_INPUT_2) {
			x += slowmove;
		}
		else {
			x += normalmove;
		}
	}
}

void ziki::run() {
	draw();
	move();
}