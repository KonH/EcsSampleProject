#pragma once

#include <string>

namespace Sample::ResourceConstants {
	constexpr double RESOURCE_UNITS_PER_DISPLAY_UNIT = 100.0;
	
	const std::string TURNS_RESOURCE_ID = "Turns";

	static long GetResourceUnits(double units) { 
		return static_cast<long>(units * RESOURCE_UNITS_PER_DISPLAY_UNIT);
	}

	static double GetDisplayUnits(long units) {
		return static_cast<double>(units) / RESOURCE_UNITS_PER_DISPLAY_UNIT;
	}
}