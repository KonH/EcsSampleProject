#include "BuildingConfigProvider.h"

#include "Logging/Logger.h"

namespace Sample::Configs {  
	std::shared_ptr<BuildingConfig> BuildingConfigProvider::GetBuildingConfig(const std::string& buildingId) const {  
		auto it = _buildingConfigs.find(buildingId);  
		if (it != _buildingConfigs.end()) {   
			return std::make_shared<BuildingConfig>(it->second);  
		} else {  
			Sample::Logging::Logger::LogWarning("Building ID not found: {}", buildingId);  
			return nullptr;  
		}  
	}
}
