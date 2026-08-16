#pragma once
#include "Common.h"

namespace Astral {

	class Asset {
	public:
		Asset(std::string name) : name(name) {}
		virtual ~Asset() = 0;
		std::string_view Name() const { return name; }

	private:
		std::string name;
	};

	inline Asset::~Asset() = default;
}