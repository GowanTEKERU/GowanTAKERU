#ifndef BLACKOUTRENDER_H
#define BLACKOUTRENDER_H

//60�t���[���Ŋ�������̂�30�t���[���Ő^���ÂɂȂ�
#define FINISHFRM 60

enum BLACKOUT_STATE {
	NON,
	FADE_IN,
	BLACKOUT,
	FADE_OUT,
	COMPLETION
};

struct BlackOutData {
	BLACKOUT_STATE BlackOutNextState;
	bool BlackOutflg;
};

//blackout���Ă���Ԃ�ON�ł�
//�����OFF�ɂ��Ă���܂�
BlackOutData* GetBlackOutData();

void BlackOutRender();

#endif
