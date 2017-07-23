#pragma once

#include <functional>
#include <list>

template <typename  ...Args> class Event
{
private:
	//handlers
	std::list<std::function<void(Args...)>> m_functions;

public:
	using Function = typename std::list<std::function<void(Args...)>>::iterator;

	Event() {}

	//add handler
	Function operator += (std::function<void(Args...)>&& newFunc)
	{
		m_functions.emplace_back(newFunc);
		return --m_functions.end();
	}
	//add handler
	Function operator += (void(*newFunc)(Args...))
	{
		m_functions.emplace_back(newFunc);
		return --m_functions.end();
	}
	//remove handler
	void operator -= (Function func)
	{
		if (m_functions.size() == 0)
			return;

		for (Function function = m_functions.begin(); function != m_functions.end(); function++)
			if (func == function)
			{
				m_functions.erase(function);
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