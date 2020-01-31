// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomationTests.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"

#include "Engine/Engine.h"
#include "AssetRegistryModule.h"
#include "Engine/LevelScriptBlueprint.h"

UWorld* GetTestWorld() {
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (const FWorldContext& Context : WorldContexts) {
		if (((Context.WorldType == EWorldType::PIE) || (Context.WorldType == EWorldType::Game))
			&& (Context.World() != nullptr)) {
			return Context.World();
		}
	}

	return nullptr;
}

IMPLEMENT_COMPLEX_AUTOMATION_TEST(FAutomationTests, "PETest.LaunchLevels", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ProductFilter)

void FAutomationTests::GetTests(TArray<FString>& OutBeautifiedNames, TArray <FString>& OutTestCommands) const
{
	// 1. Get the array of assets from Maps directory.
	FAssetRegistryModule& ARM = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetDataArray;
	ARM.Get().GetAssetsByPath(TEXT("/Game/Tests/Maps"), AssetDataArray);

	for (const auto& AssetData : AssetDataArray)
	{
		// 2. Check if the asset is a World class, which means it is a umap.
		if (AssetData.AssetClass == "World")
		{
			// 3. Use the asset name as a test name and package name (map path) as a test parameter.
			OutBeautifiedNames.Add(AssetData.AssetName.ToString());
			OutTestCommands.Add(AssetData.PackageName.ToString());
		}
	}
}

bool FAutomationTests::RunTest(const FString& Parameters)
{

	TestTrue("World created", AutomationOpenMap(Parameters));
	UWorld* world = GetTestWorld();

	TArray<ULevel*> levels = world->GetLevels();

	for (auto level : levels)
	{
		ULevelScriptBlueprint* lvlBlueprint = level->GetLevelScriptBlueprint(); // replace with inherited level script actor
		//lvlBlueprint->
	}

	/*for (TActorIterator<"MyClassHere"> It(world, "MyClassHere"::StaticClass()); It; ++It) {
		TestTrue("Classes do something", It->DoSomething());
	}*/ // Can iterate over all actors of a specified class here, maybe grab from level

	return true;
}
