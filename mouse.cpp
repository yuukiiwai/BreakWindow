#include"DxLib.h"
#include"Value.h"

int mouseX, mouseY, mouseS;

int Click() {
	mouseS = GetMouseInput();
	if (mouseS == MOUSE_INPUT_LEFT) {
		return 1;
	}
	else {
		return 0;
	}
}

int PointClick(int MouseX1, int MouseY1, int MouseX2, int MouseY2) {
	GetMousePoint(&mouseX, &mouseY);
	if ((MouseX1 <= mouseX) && (MouseY1 <= mouseY) && (MouseX2 >= mouseX) && (MouseY2 >= mouseY) && (Click())) {
		return 1;
	}
	else {
		return 0;
	}
}