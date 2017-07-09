#pragma once

#include <functional>
#include <vector>

template <typename  ...Args> class Event
{
private:
	//handlers
	std::vector<std::function<void(Args...)>> functions;

public:
	Event() {}

	//add handler
	void operator += (std::function<void(Args...)>&& newFunc)
	{
		functions.emplace_back(newFunc);
	}
	//add handler
	void operator += (void(*newFunc)(Args...))
	{
		functions.emplace_back(newFunc);
	}

	//clear events
	void clear() { functions.clear(); }

	//call handlers
	void operator ()(Args... args)
	{
		for (auto& func : functions)
		{
			func(args...);
		}
	}
};