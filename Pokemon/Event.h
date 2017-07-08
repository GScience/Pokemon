#pragma once

#include <functional>

template <typename  ...Args> class Event
{
private:
	//handlers
	std::list<std::function<void(Args...)>> functions;

public:
	//add handler
	void operator += (std::function<void(Args...)>&& newFunc)
	{
		functions.emplace_back(newFunc);
	}

	//call handlers
	void operator ()(Args... args)
	{
		for (auto& func : functions)
		{
			func(args...);
		}
	}
};