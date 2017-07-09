#pragma once

#include <map>
#include <string>

class ResourceContent
{
private:
	const char* m_path;
	std::map<std::string, void*> m_resourceMap;

	//load all resources
	void loadResources(const char * dir);

public:
	ResourceContent(const char* path) :m_path(path) {}

	//init
	void initialize();

	//add
	template <class Type> void add(Type* type, const char* key)
	{
		m_resourceMap[key] = type;
	}

	//get resource
	template <class Type> Type* get(const char* resourcePath)
	{
		return reinterpret_cast<Type*>(m_resourceMap.at(resourcePath));
	}
};