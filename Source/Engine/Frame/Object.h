#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLERATION(classname) \
	virtual const char* GetClassName() {return #classname;} \
	void Read(const rapidjson::Value& value); \
	class Register \
	{ \
	public: \
		Register() \
		{ \
			Factory::Instance().Register<classname>(#classname); \
		} \
	}; \


#define CLASS_DEFINITION(classname) \
	classname::Register register_class; \

namespace max
{
	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) : name{name} {}
		virtual ~Object() { OnDestroy(); }

		CLASS_DECLERATION(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	protected:
		std::string name;
	};
}