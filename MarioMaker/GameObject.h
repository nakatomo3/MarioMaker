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

	//オブジェクトの座標を取得します
	Vector3 GetPosition();
	//オブジェクトの座標を設定します
	void SetPosition(Vector3 newPos);

	//親との相対座標を取得します
	Vector3 GetLocalPosition();
	//親との相対座標を設定します
	void SetLocalPosition(Vector3 newPos);

	//現在の大きさを取得します
	Vector3 GetScale();
	//大きさを設定します
	void SetScale(Vector3 newScale);

	//現在の回転を取得します
	Vector3 GetRotation();
	//回転角度を設定します
	void SetRotation(Vector3 newRotation);

	//このオブジェクト自体の拡大率を取得します
	Vector3 GetLocalScale();
	//このオブジェクト自体の拡大率を設定します
	void SetLocalScale(Vector3 newScale);

	//現在の速度を取得します
	Vector3 GetVelocity();
	//速度を設定します
	void SetVelocity(Vector3 newVelocity);

	//このオブジェクトの名前を取得します
	string GetName();
	//このオブジェクトの名前を設定します
	void SetName(string newName);

	//このオブジェクトのタグを取得します
	Tag GetTag();
	//このオブジェクトにタグを設定します
	void SetTag(Tag _tag);
	//タグとtargetが一致しているかを返します
	bool CompareTag(Tag target);

	//親のオブジェクトを取得します
	GameObject* GetParent();
	//親を設定します
	void SetParent(GameObject* parent);

	//index番目の子供オブジェクトを取得します
	GameObject* GetChild(int index);
	//子供オブジェクトの数を取得します
	unsigned int GetChildCount();
	//子供を追加します
	void AddChild(GameObject* child);

	//オブジェクトを回転させます
	void Rotate(Vector3 angle);
	void Rotate(float x, float y, float z);

	//オブジェクトをその方向に向かせます
	//やりたかったけど意味分からんので一旦保留
	//void LookAt(Vector3 target);

	//オブジェクトを移動させます
	void Move(Vector3 range);
	void Move(float x, float y, float z);

	template<typename T>
	Component* GetComponent(T* t) {
		//そもそもComponent型なのかをチェックする
		Component* cast_t = dynamic_cast<Component*>(t);
		//引数はコンポーネントである
		if (cast_t != NULL) {
			for (unsigned int i = 0; i < components.size(); i++) {
				Component* checkComponent = dynamic_cast<T*>(components[i]);
				if (checkComponent != NULL) {
					//正常に見つかった
					return components[i];
				}
			}
			//引数はコンポーネントだったが見つからなかった
			return nullptr;
		} else {
			//引数がコンポーネントじゃなかった
			return nullptr;
		}
	}

	template<typename T>
	T* GetComponent() {
		for (unsigned int i = 0; i < components.size(); i++) {
			Component* checkComponent = dynamic_cast<T*>(components[i]);
			if (checkComponent != NULL) {
				//正常に見つかった
				return components[i];
			}
		}
		return nullptr;
	}

	//非推奨
	//同種類のコンポーネントが複数ある場合に使用、count番目のコンポーネントを返す
	template<typename T>
	T* GetComponent(int count) {
		vector<T> returnComponents;
		for (unsigned int i = 0; i < components.size(); i++) {
			Component* checkComponent = dynamic_cast<T*>(components[i]);
			if (checkComponent != NULL) {
				//正常に見つかった
				returnComponents.emplace_back(components[i]);
			}
		}
		if (returnComponents.size() > count) {
			return returnComponents[count];
		} else {
			LogWriter::Log("GetComponentの%d番目は見つかりませんでした", count);
			return nullptr;
		}
	}

	template<typename T>
	vector<T> GetComponents() {
		vector<T> returnComponents;
		for (unsigned int i = 0; i < components.size(); i++) {
			Component* checkComponent = dynamic_cast<T*>(components[i]);
			if (checkComponent != NULL) {
				//正常に見つかった
				returnComponents.emplace_back(components[i]);
			}
		}
		return returnComponents;
	}

	//[非推奨]　コンポーネントを取得します。num=上から数えたコンポーネントの数。
	Component* GetComponent(unsigned int num);

	//コンポーネントがどれだけアタッチされているかをカウントします。
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
					//正常に見つかった
					Component* cacheComponent = components[i];
					components[i] = components[components.size() - 1];
					components.pop_back();
					cacheComponent->Destroy();
					return;
				}
			}
			//引数はコンポーネントだったが見つからなかった
			return;
		} else {
			//引数がコンポーネントじゃなかった
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

