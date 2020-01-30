// Fill out your copyright notice in the Description page of Project Settings.

#include "ProductionEnv.h"
#include "Modules/ModuleManager.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Engine.h"
#include "EngineUtils.h"

class FTestModuleImpl : public FDefaultGameModuleImpl {

	void ShutdownModule() override {
		/* Workaround for UE-25350 */
		FAutomationTestFramework::Get().UnregisterAutomationTest("FAutomatedTests");
		//... for every test you defined.
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FTestModuleImpl, ProductionEnv, "ProductionEnv" );
