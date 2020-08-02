#pragma once
#include "Object.h"

class GameObject;
class Component : public Object {
	friend class GameObject;
public:
	Component();

	//�R���|�[�l���g(�܂��͂��ꂪ�����Ă���Q�[���I�u�W�F�N�g)��Active���I���ɂȂ�����
	virtual void OnEnabled() {}

	//�R���|�[�l���g(�܂��͂��ꂪ�����Ă���Q�[���I�u�W�F�N�g)��Active���I�t�ɂȂ�����
	virtual void OnDisabled() {}

	//�������̈�ԍŏ��Ɏg�p�B
	virtual void Awake() {}

	//��ʓI�ȏ������Ɏg�p�B
	virtual void Start() {}

	//��ԍŏ��̖��t���[�����Ƃ̍X�V�Ɏg�p�B
	virtual void FirstUpdate() {}

	//��ʓI�Ȗ��t���[�����Ƃ̍X�V�Ɏg�p�B
	virtual void Update() {}

	//��ԍŌ�̖��t���[�����Ƃ̍X�V�Ɏg�p�B
	virtual void LateUpdate() {}

	//�R���|�[�l���g(�܂��͂��ꂪ�����Ă���Q�[���I�u�W�F�N�g)���폜���ꂽ��
	virtual void OnDestroy() {}

	void SetActive(bool active) override;

	GameObject* GetGameObject();
	void SetGameObject(GameObject* _gameObject);

protected :
	GameObject* gameObject;
	~Component();

private:
	//�g�p�֎~�BgameObject.RemoveComponent(this)�����邱��
	void Destroy() override final;
};