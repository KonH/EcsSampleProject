#pragma once

#include <map>
#include <string>

namespace Sample::Configs {
	struct BuildingConfig {
		std::string id;
		std::map<std::string, long> income;
	};
}
