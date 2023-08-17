#include "Object.h"

namespace max
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}