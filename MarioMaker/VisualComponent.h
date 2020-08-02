#pragma once
#include "RendererManager.h"
#include "Component.h"

//�|�W�V�����̊�l�B��{�͐^�񒆂����ύX�\
typedef enum{
	CENTER		= (0 + 0),
	LEFT		= (0 + 1),
	RIGHT		= (0 + 2),
	UP			= (4 + 0),
	UP_LEFT		= (4 + 1),
	UP_RIGHT	= (4 + 2),
	DOWN		= (8 + 0),
	DOWN_LEFT	= (8 + 1),
	DOWN_RIGHT	= (8 + 2),
}Criterion;

//���C���[�ݒ�B�l���ɕ`������Ă���
typedef enum {
	CAMERA = 0,
	DEFAULT = 1,
	UI		= 2, 
	LAYERLAST
}Layer;

class VisualComponent :	public Component {
public:
	VisualComponent();
	~VisualComponent();

	//�`��Ɋ�����R���|�[�l���g�ł��鎞������I�[�o�[���C�h���Ďg�p�B
	virtual void Draw();

	//�Ō�ɕ`�悷��p�̊֐��BUI�Ȃǂ�z��
	virtual void LateDraw();

	virtual Layer GetLayer() final;

protected:
	Layer layer = DEFAULT;
};

