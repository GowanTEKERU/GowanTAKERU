#include "SceneManagement.h"
#include"FileManagement.h"
#include"MainRender.h"
#include"MainControl.h"
#include"MainSceneInit.h"

void SceneManagement() {
	static int step = 0;

	//�摜�I��
	//if(���C���V�[��){
	switch (step) {

	case 0:
		MainSceneLoad();
		MainSceneInit();
		step++;
		break;

	case 1:
		MainControl();
		MainRender();

		//if  step++;
		break;

	case 2:
		TextureFree();
		//step=0;
		//break;
	}
		//if(step==2){
		//
	//else


}