// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "Map/Maps/CurvedPath.h"
#include "LevelGenerator.h"


// Sets default values
ALevelGenerator::ALevelGenerator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SmallMap.MapLocation = Coordinate2D(0, 0);
	SmallMap.Size = Coordinate2D(32, 32);
	
	LargeMap.MapLocation = Coordinate2D(0, 0);
	LargeMap.Size = Coordinate2D(64, 64);
	LargeMap.LocalExitPoint = Coordinate2D(100, 100);
	
	HugeMap.MapLocation = Coordinate2D(0, 0);
	HugeMap.Size = Coordinate2D(128, 128);

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();
;
	initMap(new CurvedPath(LargeMap));

}

// Called every frame
void ALevelGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALevelGenerator::initMap(BaseMap* MapLayout)
{
	TileMap.Empty();
	TileMap.SetNum(128);
	for (int i = 0; i < 128; i++) {
		TileMap[i].SetNum(128);
	}

	MapLayout->Generate(TileMap);

	FActorSpawnParameters Params;
	if (!GetWorld()) return;

	if (!lvlbuilder)
	{
		lvlbuilder = GetWorld()->SpawnActor<ALevelBuilder>(ALevelBuilder::StaticClass(), Params);
	}
	
	lvlbuilder->BuildTiles(TileMap);

	FActorBeginOverlapSignature OverlapSignature;
	OverlapSignature.AddDynamic(this, &ALevelGenerator::ExitMap);
	lvlbuilder->PlaceExitDevice(MapLayout->GetExitPoint(), OverlapSignature);

}


void ALevelGenerator::ExitMap(class AActor* ExitDevice, class AActor* OtherActor)
{
	lvlbuilder->ForgetMap();
	initMap(new CurvedPath(LargeMap));
	OtherActor->SetActorLocation(FVector(790.f, 840.f, 362.f));
}

void ALevelGenerator::FetchMapConditions()
{
	// Set a TileSet
	// Find fitting layout-theme(s)
	// 
}

void ALevelGenerator::PrintDebugMap()
{
	FString DebugMap;
	DebugMap.Empty();
	DebugMap.Append("\n");

	for (int x = 0; x < 128; x++) {
		for (int y = 0; y < 128; y++) {
			if (TileMap[x][y].TileType != TILETYPE_Void)
			{
				DebugMap.Append("X ");
			}
			else {
				DebugMap.Append("  ");
			}
		}
		DebugMap.Append("\n");
	}

	UE_LOG(LogTemp, Log, TEXT("%s"), *DebugMap);

}
