#include"MainHitManagement.h"
#include<d3dx9.h>


void HitManage() {

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