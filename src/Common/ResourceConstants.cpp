#include "ResourceConstants.h"

namespace Sample::ResourceConstants {
	long GetResourceUnits(double units) {
		return static_cast<long>(units * RESOURCE_UNITS_PER_DISPLAY_UNIT);
	}

	double GetDisplayUnits(long units) {
		return static_cast<double>(units) / RESOURCE_UNITS_PER_DISPLAY_UNIT;
	}
}
