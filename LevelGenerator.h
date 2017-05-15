// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/TriggerBox.h"
#include "Map/BaseMap.h"
#include "Map/LevelBuilder.h"
#include "DrawDebugHelpers.h"
#include "Map/BaseArea.h"
#include "Map/BaseSegment.h"
#include "Map/LevelDataStructures.h"
#include "LevelGenerator.generated.h"

UCLASS()
class HACKNSLASH_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	void initMap(BaseMap* map);

	UFUNCTION()
		void ExitMap(class AActor* ExitDevice, class AActor* OtherActor);

	
protected:
	TArray<TArray<TileData>>	TileMap;
	TArray<TArray<TileData*>>	Segments;
	TArray<TArray<TileData*>>	Areas;

	FMapSectionData HugeMap;
	FMapSectionData LargeMap;
	FMapSectionData SmallMap;

	ALevelBuilder* lvlbuilder;

	void FetchMapConditions();
	void PrintDebugMap();

	TileSet DebugTileSet;

};