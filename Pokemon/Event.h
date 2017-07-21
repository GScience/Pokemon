#pragma once

#include <functional>
#include <vector>

template <typename  ...Args> class Event
{
private:
	//handlers
	std::vector<std::function<void(Args...)>> m_functions;

public:
	Event() {}

	//add handler
	void* operator += (std::function<void(Args...)>&& newFunc)
	{
		m_functions.emplace_back(newFunc);
		return &m_functions[m_functions.size() - 1];
	}
	//add handler
	void* operator += (void(*newFunc)(Args...))
	{
		m_functions.emplace_back(newFunc);
		return &m_functions[m_functions.size() - 1];
	}
	//remove handler
	void operator -= (void* func)
	{
		for (unsigned int i = 0; i < m_functions.size(); i++)
			if (func == &m_functions[i])
			{
				m_functions.erase(m_functions.begin() + i);
				break;
			}
	}

	//clear events
	void clear() { m_functions.clear(); }

	//call handlers
	void operator ()(Args... args)
	{
		for (auto& func : m_functions)
		{
			func(args...);
		}
	}
};