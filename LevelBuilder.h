// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Map/LevelDataStructures.h"
#include "LevelBuilder.generated.h"

UCLASS()
class HACKNSLASH_API ALevelBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelBuilder(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void BuildTiles(TArray<TArray<TileData>> TileMap);
	void ForgetMap();
	void PlaceExitDevice(Coordinate2D Here, FActorBeginOverlapSignature OverlapSignature);

UPROPERTY(VisibleAnywhere)
	class ATriggerBox* MapExitDevice;


private:


	UStaticMesh* EmptyFloorMesh;
	UInstancedStaticMeshComponent* FloorISM;

	UStaticMesh* WallMesh;
	UInstancedStaticMeshComponent* WallISM;

	UStaticMesh* CornerMesh;
	UInstancedStaticMeshComponent* CornerISM;

	UStaticMesh* InvCornerMesh;
	UInstancedStaticMeshComponent* InvCornerISM;

};