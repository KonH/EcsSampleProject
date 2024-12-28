#pragma once

#include <map>
#include <string>
#include <memory>

#include "Configs/BuildingConfig.h"

namespace Sample::Configs {
	class BuildingConfigProvider {
	public:
		BuildingConfigProvider(std::map<std::string, BuildingConfig> buildingConfigs) : _buildingConfigs(buildingConfigs) {}

		std::shared_ptr<BuildingConfig> GetBuildingConfig(const std::string &buildingId) const;
	
	private:
		std::map<std::string, BuildingConfig> _buildingConfigs;
	};
}
