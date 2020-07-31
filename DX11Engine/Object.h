#pragma once
class Object{
public:
	Object();
	~Object();

	void virtual Destroy();

	bool GetActive();
	virtual void SetActive(bool active);

protected:
	bool isActive;
};

