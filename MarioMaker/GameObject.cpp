#include "GameObject.h"
#include "LogWriter.h"
#include "ObjectManager.h"
#include "ScriptBase.h"
#include "Time.h"
#include <cmath>

void GameObject::Destroy() {

	ObjectManager::AddDestroyList(this);

	auto componentCount = components.size();
	auto childCount = children.size();

	if (componentCount > 0) {
		for (unsigned int i = 0; i < componentCount; i++) {
			Component* removeComponent = components[0];
			RemoveComponent(removeComponent);
		}
	}
	if (childCount >= 1) {
		for (unsigned int i = 0; i < childCount - 1; i++) {
			GameObject* child = children[i];
			child->Destroy();
		}
	}
}

void GameObject::Destroy(float time) {
	if (time < 0) {
		LogWriter::Log("Destroyに負の値を入れないでください");
	}
	destroyTimer = time;
}

GameObject::GameObject() {
	position		= Vector3(0, 0, 0);
	localPosition	= Vector3(0, 0, 0);
	scale			= Vector3(1, 1, 1);
	localScale		= Vector3(1, 1, 1);
	rotation		= Vector3(0, 0, 0);
	velocity		= Vector3(0, 0, 0);
	name			= "New GameObject";
}

GameObject::GameObject(string _name) {
	position		= Vector3(0, 0, 0);
	localPosition	= Vector3(0, 0, 0);
	scale			= Vector3(1, 1, 1);
	localScale		= Vector3(1, 1, 1);
	rotation		= Vector3(0, 0, 0);
	velocity		= Vector3(0, 0, 0);
	name			= _name;
}

void GameObject::Start() {
	for (unsigned int i = 0; i < GetComponentCount(); i++) {
		if (GetComponent(i)->GetActive() == true) {
			GetComponent(i)->Start();
		}
	}
}

void GameObject::Update() {
	for (unsigned int j = 0; j < GetComponentCount(); j++) {
		if (destroyTimer > 0) {
			destroyTimer -= (float)Time::GetDeltaTime();
		}
		if (destroyTimer < 0) {
			Destroy();
			return;
		}
		if (GetComponent(j)->GetActive() == true) {
			GetComponent(j)->Update();
		}
	}
}

void GameObject::OnCollisionEnter(Collision* collision) {
}

void GameObject::OnCollisionStay(Collision* collision) {
	for (unsigned int i = 0; i < components.size(); i++) {
		ScriptBase* cast_c = dynamic_cast<ScriptBase*>(components[i]);
		if (cast_c != NULL) {
			cast_c->OnCollisionStay(collision);
		}
	}
}

void GameObject::OnCollisionExit(Collision* collision) {
}

void GameObject::OnTriggerEnter(Collision* collision) {
}

void GameObject::OnTriggerStay(Collision* collision) {
}

void GameObject::OnTriggerExit(Collision* collision) {
}

void GameObject::OnClick() {
	for (unsigned int i = 0; i < components.size(); i++) {
		ScriptBase* cast_c = dynamic_cast<ScriptBase*>(components[i]);
		if (cast_c != NULL) {
			cast_c->OnClick();
		}
	}
}

void GameObject::SetDestroyOnload(bool willDestroy) {
	isDestroyOnLoad = willDestroy;
}

bool GameObject::GetDestroyOnload() {
	return isDestroyOnLoad;
}

void GameObject::SetActive(bool _active) {
	Object::SetActive(_active);
}

GameObject::~GameObject() {
	LogWriter::Log("%sというオブジェクトを削除しました", name.c_str());
}

Vector3 GameObject::GetPosition() {
	return position;
}

void GameObject::SetPosition(Vector3 newPos) {
	auto delta = newPos - position;
	position = newPos;
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->Move(delta);
	}
}

Vector3 GameObject::GetLocalPosition() {
	if (parent == nullptr) {
		return Vector3(0, 0, 0);
	} else {
		return this->position - parent->GetPosition();
	}
}

void GameObject::SetLocalPosition(Vector3 newPos) {
	localPosition = newPos;
	if (parent != nullptr) {
		position = parent->position + localPosition;
	}
}

Vector3 GameObject::GetScale() {
	return scale;
}

void GameObject::SetScale(Vector3 newScale) {
	for (unsigned int i = 0; i < GetChildCount(); i++) {
		GetChild(i)->SetScale(newScale);
	}
	scale = newScale;
}

Vector3 GameObject::GetRotation() {
	return rotation;
}

void GameObject::SetRotation(Vector3 newRotation) {
	rotation = newRotation;
}

Vector3 GameObject::GetLocalScale() {
	return localScale;
}

void GameObject::SetLocalScale(Vector3 newScale) {
	localScale = newScale;
}

void GameObject::SetVelocity(Vector3 newVelocity) {
	velocity = newVelocity;
}

Vector3 GameObject::GetVelocity() {
	return velocity;
}

string GameObject::GetName() {
	return name;
}

void GameObject::SetName(string newName) {
	name = newName;
}

Tag GameObject::GetTag() {
	return tag;
}

void GameObject::SetTag(Tag newTag) {
	tag = newTag;
}

bool GameObject::CompareTag(Tag target) {
	return tag == target;
}

GameObject * GameObject::GetParent() {
	return parent;
}

void GameObject::SetParent(GameObject * _parent) {
	if (parent == _parent) {
		return;
	}
	_parent->AddChild(this);
	parent = _parent;
}

GameObject * GameObject::GetChild(int index) {
	return children[index];
}

unsigned int GameObject::GetChildCount() {
	return children.size();
}

void GameObject::AddChild(GameObject * _child) {
	for (unsigned int i = 0; i < children.size(); i++) {
		if (children[i] == _child) {
			return;
		}
	}
	children.emplace_back(_child);
	_child->SetParent(this);
}

void GameObject::Rotate(Vector3 angle) {
	for (unsigned int i = 0; i < GetChildCount(); i++) {
		GetChild(i)->Rotate(angle);
	}
	rotation = angle + rotation;
}

void GameObject::Rotate(float x, float y, float z) {
	auto angle = Vector3(x, y, z);
	for (unsigned int i = 0; i < GetChildCount(); i++) {
		GetChild(i)->Rotate(angle);
	}
	rotation = angle + rotation;
}

//void GameObject::LookAt(Vector3 _target) {
//	if (position == _target) {
//		LogWriter::Log("現在の座標と目標が同じだったので回転はしませんでした\n");
//		return;
//	}
//
//	Vector3 difference = _target - position;
//
//	float rotY = atan2(difference.GetX(), difference.GetZ());
//	float rotX = atan2(difference.GetY(), hypot(difference.GetX(), difference.GetZ()));
//
//	rotation = Vector3(rotX, rotY, 0);
//	LogWriter::Log("%f,%f", rotX, rotY);
//}

void GameObject::Move(Vector3 range) {
	for (unsigned int i = 0; i < GetChildCount(); i++) {
		GetChild(i)->Move(range);
	}
	SetPosition(Vector3(position.GetX() + range.GetX(), position.GetY() + range.GetY(), position.GetZ()+ range.GetZ()));
}

void GameObject::Move(float x, float y, float z) {
	auto range = Vector3(x, y, z);
	for (unsigned int i = 0; i < GetChildCount(); i++) {
		GetChild(i)->Move(range);
	}
	SetPosition(Vector3(position.GetX() + range.GetX(), position.GetY() + range.GetY(), position.GetZ() + range.GetZ()));
}

Component* GameObject::GetComponent(unsigned int num) {
	if (num >= components.size() || num < 0) {
		LogWriter::LogWorning("コンポーネントの取得に失敗しました。\nゲームオブジェクト名：%s\nコンポーネント引数：%d", name, num);
		return nullptr;
	}
	return components[num];
}

unsigned int GameObject::GetComponentCount() {
	return components.size();
}


void GameObject::AddComponent(Component* component) {
	components.emplace_back(component);
	component->SetGameObject(this);
}
