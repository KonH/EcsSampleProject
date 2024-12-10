#include <gtest/gtest.h>

#include "Systems/Movement/PlayerMovementSystemTest.h"
#include "Systems/Selection/MouseArmySelectionSystemTest.h"

// TODO: integrate code coverage

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}