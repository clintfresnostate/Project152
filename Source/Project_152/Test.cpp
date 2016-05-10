// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "AutomationTest.h"
#include "Test.h"


// Sets default values
ATest::ATest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
/*
bool FSetResTest::RunTest(const FString& Parameters)
{
	FString MapName = TEXT("AutomationTest");
	FEngineAutomationTestUtilities::LoadMap(MapName);

	int32 ResX = GSystemSettings.ResX;
	int32 ResY = GSystemSettings.ResY;
	FString RestoreResolutionString = FString::Printf(TEXT("setres %dx%d"), ResX, ResY);

	ADD_LATENT_AUTOMATION_COMMAND(FEngineWaitLatentCommand(2.0f));
	ADD_LATENT_AUTOMATION_COMMAND(FExecStringLatentCommand(TEXT("setres 640x480")));
	ADD_LATENT_AUTOMATION_COMMAND(FEngineWaitLatentCommand(2.0f));
	ADD_LATENT_AUTOMATION_COMMAND(FExecStringLatentCommand(RestoreResolutionString));

	return true;
}
bool FAutoTargetTest::RunTest(const FString& Parameters)
{
	//Open a new blank map.
	UWorld* World = AutomationEditorCommonUtils::CreateNewMap();

	//Move the perspective viewport view to show the test.
	for (int32 i = 0; i < GEditor->LevelViewportClients.Num(); i++)
	{
		FLevelEditorViewportClient* ViewportClient = GEditor->LevelViewportClients[i];
		if (!ViewportClient->IsOrtho())
		{
			ViewportClient->SetViewLocation(FVector(890, 70, 280));
			ViewportClient->SetViewRotation(FRotator(0, 180, 0));
		}
	}
	return true;
}
*/