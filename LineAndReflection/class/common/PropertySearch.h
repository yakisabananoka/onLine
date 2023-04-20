#pragma once
#include <string>
#include "../../parser/rapidjson/document.h"

//rapidjson‚Åƒƒ“ƒo‚ð’Tõ‚·‚é‚½‚ß
struct PropertySearch
{
	const rapidjson::Value& value_;

	PropertySearch(const rapidjson::Value& value) :value_(value) {};

	const rapidjson::Value& operator()(std::string name, bool* result = nullptr)
	{
		if (result)
		{
			(*result) = true;
		}

		if (value_.HasMember(name.c_str()))
		{
			return value_[name.c_str()];
		}

		const rapidjson::Value& properties = value_["properties"];

		for (auto itr = properties.Begin(); itr != properties.End(); ++itr)
		{
			if (itr->GetObj()["name"].GetString() != name)
			{
				continue;
			}

			return itr->GetObj()["value"];
		}

		if (result)
		{
			(*result) = false;
		}

		return value_;
	}
};