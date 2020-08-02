#pragma once
#include "GameObject.h"
#include "Component.h"
class ScriptBase : public Component{
public:
	ScriptBase();
	ScriptBase(GameObject* gameObject);
	~ScriptBase();

	//�������ꂽ�Ƃ��Ɉ�ԍŏ��ɌĂяo����܂��BStart�֐�������ɌĂяo����܂�
	virtual void Awake();
	//�������ꂽ�Ƃ��ɌĂяo����܂��BAwake�֐�������ɌĂяo����܂��B
	virtual void Start();
	//�ŏ��ɌĂяo�����Update�ł��B
	virtual void FirstUpdate();
	//�ʏ�Ăяo�����Update�ł��B
	virtual void Update();
	//�Ō�ɌĂяo�����Update�ł��B
	virtual void LateUpdate();

	//Collider���A�^�b�`����Ă��鎞�ɁACollider���m���ڐG�����Ƃ��ɌĂ΂��֐��ł��B
	virtual void OnCollisionStay(Collision* collision);
	//�{�^�����A�^�b�`����Ă���ꍇ�A�{�^�����N���b�N���ꂽ�Ƃ��ɌĂ΂��֐��ł��B
	virtual void OnClick();

protected:

private:

};