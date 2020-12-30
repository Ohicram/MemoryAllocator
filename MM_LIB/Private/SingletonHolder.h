#pragma once

template<class T>
class SingletonHolder {
public:
	static T& get() {
		static SingletonHolder instance;
		return instance.m_content;
	};
	void operator =(SingletonHolder const&) = delete;
	SingletonHolder(SingletonHolder&) = delete;
private:
	T m_content;
	SingletonHolder() {}
};