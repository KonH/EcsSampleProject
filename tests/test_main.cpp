#include <gtest/gtest.h>

#include "Systems/Movement/ObstacleFilterSystemTest.h"
#include "Systems/Movement/PlayerMovementSystemTest.h"
#include "Systems/Movement/WorldMovementSystemTest.h"
#include "Systems/Selection/MouseArmySelectionSystemTest.h"
#include "Systems/Utility/ActionProgressCleanUpSystemTest.h"
#include "Systems/Utility/ActionProgressUpdateSystemTest.h"
#include "Systems/Utility/DeltaTimeUpdateSystemTest.h"
#include "Systems/Utility/EventCleanUpSystemTest.h"

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}