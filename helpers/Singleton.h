#pragma once

template <class S>
class Singleton {
private:
    static S* pRet;

protected:
	Singleton() = default;
	~Singleton() = default;
	Singleton(const Singleton& obj) = delete;
	Singleton& operator = (const Singleton&) = delete;

public:
	static S* getInstance() {
		if (!pRet) {
			pRet = new S();
		}
		return pRet;
	}

	static S* release() {
		if (pRet) {
			delete pRet;
			pRet = nullptr;
		}
	}
};

template <class S>
S* Singleton<S>::pRet = nullptr;

