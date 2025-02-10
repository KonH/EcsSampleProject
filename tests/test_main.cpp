#include <gtest/gtest.h>

#include "Execution/MainLoopRunnerTest.h"

#include "Systems/Animation/MovementAnimationSystemTest.h"
#include "Systems/Animation/TextBounceAnimationSystemTest.h"

#include "Systems/Buildings/BuildingIncomeSystemTest.h"

#include "Systems/Camera/CameraMovementIntentSystemTest.h"
#include "Systems/Camera/CameraMovementSystemTest.h"
#include "Systems/Camera/CameraZoomSystemTest.h"

#include "Systems/Core/TurnAdvanceSystemTest.h"

#include "Systems/Movement/MouseArmyMovementSystemTest.h"
#include "Systems/Movement/ObstacleFilterSystemTest.h"
#include "Systems/Movement/PlayerMovementSystemTest.h"
#include "Systems/Movement/WorldMovementSystemTest.h"

#include "Systems/Presentation/ScreenToRenderPositionSetSystemTest.h"
#include "Systems/Presentation/ScreenToRenderPositionSystemTest.h"
#include "Systems/Presentation/WorldToScreenPositionSetSystemTest.h"
#include "Systems/Presentation/WorldToScreenPositionSystemTest.h"
#include "Systems/Presentation/ResourceCounterUpdateSystemTest.h"
#include "Systems/Presentation/HighlightSelectedSystemTest.h"
#include "Systems/Presentation/HighlightCellByMousePositionSystemTest.h"

#include "Systems/Selection/MouseArmySelectionSystemTest.h"

#include "Systems/UI/ButtonClickSystemTest.h"

#include "Systems/Utility/ActionProgressCleanUpSystemTest.h"
#include "Systems/Utility/ActionProgressUpdateSystemTest.h"
#include "Systems/Utility/DeltaTimeUpdateSystemTest.h"
#include "Systems/Utility/EventCleanUpSystemTest.h"

#include "Systems/SystemsBuilderTest.h"

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}