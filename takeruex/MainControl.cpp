#include"MainControl.h"
#include"PlayerControl.h"

void MainControl() {
	PlayerControl();
}

bool Circle_Hit(float cx1, float cy1, float r1, float cx2, float cy2, float r2) {

	float sumR = r1 + r2;//2�̉~�̔��a�̍��v���߂�
						 // �O�����̒藝�Œ��S�_�̒��������߂Ă���
	float L = pow(cx1 - cx2, 2) + pow(cy1 - cy2, 2);
	L = sqrt(L);

	if (sumR >= L) {//���S�_�̒��������a�̍��v���Z��������^
		return TRUE;
	}
	else if (sumR < L) {//���S�_�̒��������a�̍��v��蒷��������U
		return FALSE;
	}
}

double Calculate_rad(float x1, float y1, float x2, float y2) {

	double rad;

	double lengthX = x1 - x2;
	double lengthY = y1 - y2;

	if (lengthX < 0 && lengthY > 0) {
		rad = atan(lengthY / lengthX) + 180;
	}
	else if (lengthX < 0 && lengthY < 0) {
		rad = atan(lengthY / lengthX) + 180;
	}
	else {
		rad = atan(lengthY / lengthX);
	}

	return rad;
}