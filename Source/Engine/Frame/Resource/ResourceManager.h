#pragma once
#include "Resource.h"
#include <map>
#include <memory>
#include <string>
#include "Frame/Singleton.h"

#define GET_RESOURCE(type, filename, ...) max::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)

namespace max
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};

	template<typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ... args) {
		if (m_resources.find(filename) != m_resources.end()) {
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}

		res_t<T> resource = std::make_shared<T>();
		resource->Create(filename, args...);
		m_resources[filename] = resource;

		return resource;
	}
}