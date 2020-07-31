#pragma once
#include "Object.h"

class GameObject;
class Component : public Object {
	friend class GameObject;
public:
	Component();

	//コンポーネント(またはこれが入っているゲームオブジェクト)のActiveがオンになったら
	virtual void OnEnabled() {}

	//コンポーネント(またはこれが入っているゲームオブジェクト)のActiveがオフになったら
	virtual void OnDisabled() {}

	//初期化の一番最初に使用。
	virtual void Awake() {}

	//一般的な初期化に使用。
	virtual void Start() {}

	//一番最初の毎フレームごとの更新に使用。
	virtual void FirstUpdate() {}

	//一般的な毎フレームごとの更新に使用。
	virtual void Update() {}

	//一番最後の毎フレームごとの更新に使用。
	virtual void LateUpdate() {}

	//コンポーネント(またはこれが入っているゲームオブジェクト)が削除されたら
	virtual void OnDestroy() {}

	void SetActive(bool active) override;

	GameObject* GetGameObject();
	void SetGameObject(GameObject* _gameObject);

protected :
	GameObject* gameObject;
	~Component();

private:
	//使用禁止。gameObject.RemoveComponent(this)をすること
	void Destroy() override final;
};