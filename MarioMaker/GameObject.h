#pragma once
using namespace std;
#include "Object.h"
#include "Vector3.h"
#include <vector>
#include <string>
#include "Component.h"
#include "TagManager.h"
class Collision;
class ObjectManager;
class Scene;

class GameObject : public Object {
	friend class ObjectManager;
public:

	void Destroy() override final;
	void Destroy(float time);

	//�I�u�W�F�N�g�̍��W���擾���܂�
	Vector3 GetPosition();
	//�I�u�W�F�N�g�̍��W��ݒ肵�܂�
	void SetPosition(Vector3 newPos);

	//�e�Ƃ̑��΍��W���擾���܂�
	Vector3 GetLocalPosition();
	//�e�Ƃ̑��΍��W��ݒ肵�܂�
	void SetLocalPosition(Vector3 newPos);

	//���݂̑傫�����擾���܂�
	Vector3 GetScale();
	//�傫����ݒ肵�܂�
	void SetScale(Vector3 newScale);

	//���݂̉�]���擾���܂�
	Vector3 GetRotation();
	//��]�p�x��ݒ肵�܂�
	void SetRotation(Vector3 newRotation);

	//���̃I�u�W�F�N�g���̂̊g�嗦���擾���܂�
	Vector3 GetLocalScale();
	//���̃I�u�W�F�N�g���̂̊g�嗦��ݒ肵�܂�
	void SetLocalScale(Vector3 newScale);

	//���݂̑��x���擾���܂�
	Vector3 GetVelocity();
	//���x��ݒ肵�܂�
	void SetVelocity(Vector3 newVelocity);

	//���̃I�u�W�F�N�g�̖��O���擾���܂�
	string GetName();
	//���̃I�u�W�F�N�g�̖��O��ݒ肵�܂�
	void SetName(string newName);

	//���̃I�u�W�F�N�g�̃^�O���擾���܂�
	Tag GetTag();
	//���̃I�u�W�F�N�g�Ƀ^�O��ݒ肵�܂�
	void SetTag(Tag _tag);
	//�^�O��target����v���Ă��邩��Ԃ��܂�
	bool CompareTag(Tag target);

	//�e�̃I�u�W�F�N�g���擾���܂�
	GameObject* GetParent();
	//�e��ݒ肵�܂�
	void SetParent(GameObject* parent);

	//index�Ԗڂ̎q���I�u�W�F�N�g���擾���܂�
	GameObject* GetChild(int index);
	//�q���I�u�W�F�N�g�̐����擾���܂�
	unsigned int GetChildCount();
	//�q����ǉ����܂�
	void AddChild(GameObject* child);

	//�I�u�W�F�N�g����]�����܂�
	void Rotate(Vector3 angle);
	void Rotate(float x, float y, float z);

	//�I�u�W�F�N�g�����̕����Ɍ������܂�
	//��肽���������ǈӖ��������̂ň�U�ۗ�
	//void LookAt(Vector3 target);

	//�I�u�W�F�N�g���ړ������܂�
	void Move(Vector3 range);
	void Move(float x, float y, float z);

	template<typename T>
	Component* GetComponent(T* t) {
		//��������Component�^�Ȃ̂����`�F�b�N����
		Component* cast_t = dynamic_cast<Component*>(t);
		//�����̓R���|�[�l���g�ł���
		if (cast_t != NULL) {
			for (unsigned int i = 0; i < components.size(); i++) {
				Component* checkComponent = dynamic_cast<T*>(components[i]);
				if (checkComponent != NULL) {
					//����Ɍ�������
					return components[i];
				}
			}
			//�����̓R���|�[�l���g��������������Ȃ�����
			return nullptr;
		} else {
			//�������R���|�[�l���g����Ȃ�����
			return nullptr;
		}
	}

	template<typename T>
	T* GetComponent() {
		for (unsigned int i = 0; i < components.size(); i++) {
			Component* checkComponent = dynamic_cast<T*>(components[i]);
			if (checkComponent != NULL) {
				//����Ɍ�������
				return components[i];
			}
		}
		return nullptr;
	}

	//�񐄏�
	//����ނ̃R���|�[�l���g����������ꍇ�Ɏg�p�Acount�Ԗڂ̃R���|�[�l���g��Ԃ�
	template<typename T>
	T* GetComponent(int count) {
		vector<T> returnComponents;
		for (unsigned int i = 0; i < components.size(); i++) {
			Component* checkComponent = dynamic_cast<T*>(components[i]);
			if (checkComponent != NULL) {
				//����Ɍ�������
				returnComponents.emplace_back(components[i]);
			}
		}
		if (returnComponents.size() > count) {
			return returnComponents[count];
		} else {
			LogWriter::Log("GetComponent��%d�Ԗڂ͌�����܂���ł���", count);
			return nullptr;
		}
	}

	template<typename T>
	vector<T> GetComponents() {
		vector<T> returnComponents;
		for (unsigned int i = 0; i < components.size(); i++) {
			Component* checkComponent = dynamic_cast<T*>(components[i]);
			if (checkComponent != NULL) {
				//����Ɍ�������
				returnComponents.emplace_back(components[i]);
			}
		}
		return returnComponents;
	}

	//[�񐄏�]�@�R���|�[�l���g���擾���܂��Bnum=�ォ�琔�����R���|�[�l���g�̐��B
	Component* GetComponent(unsigned int num);

	//�R���|�[�l���g���ǂꂾ���A�^�b�`����Ă��邩���J�E���g���܂��B
	unsigned int GetComponentCount();

	void AddComponent(Component* component);
	template<typename T> T* AddComponent() {
		T* component = new T();
		AddComponent(component);
		return component;
	}

	template<typename T>
	void RemoveComponent(T* t) {
		Component* cast_t = dynamic_cast<Component*>(t);
		if (cast_t != NULL) {
			auto componentCount = components.size();
			for (unsigned int i = 0; i < componentCount; i++) {
				Component* checkComponent = dynamic_cast<T*>(components[i]);
				if (t == components[i]) {
					//����Ɍ�������
					Component* cacheComponent = components[i];
					components[i] = components[components.size() - 1];
					components.pop_back();
					cacheComponent->Destroy();
					return;
				}
			}
			//�����̓R���|�[�l���g��������������Ȃ�����
			return;
		} else {
			//�������R���|�[�l���g����Ȃ�����
			return;
		}
	}

	GameObject();
	GameObject(string name);

	void Start();

	void Update();

	void OnCollisionEnter(Collision* collision);
	void OnCollisionStay(Collision* collision);
	void OnCollisionExit(Collision* collision);

	void OnTriggerEnter(Collision* collision);
	void OnTriggerStay(Collision* collision);
	void OnTriggerExit(Collision* collision);

	void OnClick();

	void SetDestroyOnload(bool willDestroy);
	bool GetDestroyOnload();

protected:
	bool isActive;

	Vector3 position;
	Vector3 localPosition;
	Vector3 scale;
	Vector3 localScale;
	Vector3 rotation;
	Vector3 velocity;

	string name;
	Tag tag = UNTAGGED;

	GameObject* parent;
	vector<GameObject*> children{};

	vector<Component*> components;

	~GameObject();

	float destroyTimer = 0;

	Scene* scene;

	bool isDestroyOnLoad = true;

private:

};

