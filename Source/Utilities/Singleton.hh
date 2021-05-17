#pragma once

#ifndef Singleton_hh
#define Singleton_hh

template <typename T>
class CSingleton {
protected:
	CSingleton() = default;
	~CSingleton() = default;

	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;

	CSingleton(CSingleton&&) = delete;
	CSingleton& operator=(CSingleton&&) = delete;

public:
	static T& Get() {
		static T Instance{ };
		return Instance;
	}
};

#endif // !Singleton_hh