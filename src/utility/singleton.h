#pragma once

#include <mutex>

#ifndef NONCOPYABLE
#define NONCOPYABLE(type_identifier)								\
    type_identifier(const type_identifier&) = delete;				\
    type_identifier& operator=(const type_identifier&) = delete;

#endif

template <class T>
class TSingleton
{
public:
	//Provide global access to the only instance of this class
	static T& Get()
	{
		if (!m_Instance)	//This if statement prevents the costly Lock-step being required each time the instance is requested
		{
			m_Instance = new T();
		}
		return *m_Instance;
	}

	//Provide global access to release/delete this class
	static void Release()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

protected:
	//Only allow the class to be created and destroyed by itself
	TSingleton() {}
	~TSingleton() {}

	static T* m_Instance;

private:
	NONCOPYABLE(TSingleton);
};

//Finally make sure that the instance is initialised to NULL at the start of the program
template <class T>
T* TSingleton<T>::m_Instance = nullptr;

template <class T>
class TSingletonInit
{
public:
	//Provide global access to the only instance of this class
	static T& Get()
	{
		//NRS_ASSERT(m_Instance == nullptr, "Singleton hasn't been Initialised");
		return *m_Instance;
	}

	template<typename... TArgs>
	static void Init(TArgs... args)
	{
		//NRS_ASSERT(m_Instance == nullptr, "Calling Init twice");
		m_Instance = new T(std::forward<TArgs>(args)...);
	}

	//Provide global access to release/delete this class
	static void Release()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

protected:
	//Only allow the class to be created and destroyed by itself
	TSingletonInit() {}
	~TSingletonInit() {}

	static T* m_Instance;

private:
	NONCOPYABLE(TSingletonInit);
};

template <class T>
T* TSingletonInit<T>::m_Instance = nullptr;


template <class T>
class ThreadSafeSingleton
{
public:
	//Provide global access to the only instance of this class
	static T& Get()
	{
		if (!m_Instance)	//This if statement prevents the costly Lock-step being required each time the instance is requested
		{
			std::lock_guard<std::mutex> lock(m_Constructed);		//Lock is required here though, to prevent multiple threads initialising multiple instances of the class when it turns out it has not been initialised yet
			if (!m_Instance) //Check to see if a previous thread has already initialised an instance in the time it took to acquire a lock.
			{
				m_Instance = new T();
			}
		}
		return *m_Instance;
	}

	//Provide global access to release/delete this class
	static void Release()
	{
		//Technically this could have another enclosing if statement, but speed is much less of a problem as this should only be called once in the entire program.
		std::lock_guard<std::mutex> lock(m_Constructed);
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

protected:
	//Only allow the class to be created and destroyed by itself
	ThreadSafeSingleton() {}
	~ThreadSafeSingleton() {}

	static T* m_Instance;
	//Keep a static instance pointer to refer to as required by the rest of the program
	static std::mutex m_Constructed;

private:
	NONCOPYABLE(ThreadSafeSingleton);
};

//Finally make sure that the instance is initialised to NULL at the start of the program
template <class T>
std::mutex ThreadSafeSingleton<T>::m_Constructed;
template <class T>
T* ThreadSafeSingleton<T>::m_Instance = nullptr;

