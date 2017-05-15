// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "Engine/TriggerBox.h"
#include "LevelBuilder.h"
#include "LevelGenerator.h"


// Sets default values
ALevelBuilder::ALevelBuilder(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorMeshQuery(TEXT("StaticMesh'/Game/HackNSlash/Tiles/SM_EmptyFloor.SM_EmptyFloor'"));
	if (FloorMeshQuery.Succeeded())
	{
		EmptyFloorMesh = FloorMeshQuery.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WallMeshQuery(TEXT("StaticMesh'/Game/HackNSlash/Tiles/SM_Wall.SM_Wall'"));
	if (WallMeshQuery.Succeeded())
	{
		WallMesh = WallMeshQuery.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CornerMeshQuery(TEXT("StaticMesh'/Game/HackNSlash/Tiles/SM_Corner.SM_Corner'"));
	if (CornerMeshQuery.Succeeded())
	{
		CornerMesh = CornerMeshQuery.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> InvCornerMeshQuery(TEXT("StaticMesh'/Game/HackNSlash/Tiles/SM_InverseCorner.SM_InverseCorner'"));
	if (InvCornerMeshQuery.Succeeded())
	{
		InvCornerMesh = InvCornerMeshQuery.Object;
	}


}

// Called when the game starts or when spawned
void ALevelBuilder::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ALevelBuilder::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	

	if (MapExitDevice)
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString(TEXT("Yes MapExitDevice")));
	}
	else
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString(TEXT("No MapExitDevice")));
	}
}

void ALevelBuilder::BuildTiles(TArray<TArray<TileData>> TileMap)
{

	FloorISM = NewObject<UInstancedStaticMeshComponent>(this);
	FloorISM->RegisterComponent();
	FloorISM->SetStaticMesh(EmptyFloorMesh);
	FloorISM->SetFlags(RF_Transactional);
	this->AddInstanceComponent(FloorISM);

	WallISM = NewObject<UInstancedStaticMeshComponent>(this);
	WallISM->RegisterComponent();
	WallISM->SetStaticMesh(WallMesh);
	WallISM->SetFlags(RF_Transactional);
	this->AddInstanceComponent(WallISM);

	CornerISM = NewObject<UInstancedStaticMeshComponent>(this);
	CornerISM->RegisterComponent();
	CornerISM->SetStaticMesh(CornerMesh);
	CornerISM->SetFlags(RF_Transactional);
	this->AddInstanceComponent(CornerISM);

	InvCornerISM = NewObject<UInstancedStaticMeshComponent>(this);
	InvCornerISM->RegisterComponent();
	InvCornerISM->SetStaticMesh(InvCornerMesh);
	InvCornerISM->SetFlags(RF_Transactional);
	this->AddInstanceComponent(InvCornerISM);


	FTransform TempTransform;
	TempTransform.SetScale3D(FVector(1.f, 1.f, 1.f));
	TempTransform.SetRotation(FRotator(0, 0, 0).Quaternion());
	

	for (int y = 0; y < 128; y++) {
		for (int x = 0; x < 128; x++) {

			TempTransform.SetLocation(FVector(x * 100, y * 100, 0));
			switch (TileMap[x][y].TileType)
			{
			case TILETYPE_Void:
				break;
			case TILETYPE_Floor:
				FloorISM->AddInstance(TempTransform);
				break;
			case TILETYPE_Wall:
				TempTransform.SetRotation(TileMap[x][y].Rotation);
				WallISM->AddInstance(TempTransform);
				break;
			case TILETYPE_Corner:
				TempTransform.SetRotation(TileMap[x][y].Rotation);
				CornerISM->AddInstance(TempTransform);
				break;
			case TILETYPE_InvCorner:
				TempTransform.SetRotation(TileMap[x][y].Rotation);
				InvCornerISM->AddInstance(TempTransform);
				break;
			case TILETYPE_MAX:
				break;
			default:
				break;
			}

// 			if (TileMap[x][y].TileType != TILETYPE_Void)
// 			{
// 				Trans.SetLocation(FVector(x * 150, y * 150, 0));
// 				FloorISM->AddInstance(Trans);
// 			}
		}
		//UE_LOG(LogTemp, Log, TEXT("Building!"));
	}
}

void ALevelBuilder::ForgetMap()
{
	MapExitDevice->OnActorBeginOverlap.Clear();
	WallISM->ClearInstances();
	FloorISM->ClearInstances();
	CornerISM->ClearInstances();
	InvCornerISM->ClearInstances();
	
}

void ALevelBuilder::PlaceExitDevice(Coordinate2D Here, FActorBeginOverlapSignature OverlapSignature)
{
	if (!MapExitDevice) {
		this->MapExitDevice = GetWorld()->SpawnActor<ATriggerBox>(ATriggerBox::StaticClass());
		this->MapExitDevice->SetActorScale3D(FVector(5, 5, 5));
		this->MapExitDevice->SetActorHiddenInGame(false);
		this->MapExitDevice->UpdateOverlaps(false);

	}
	
	MapExitDevice->SetActorLocation(FVector(Here.X * 100.f, Here.Y * 100.f, 60.f));
	MapExitDevice->OnActorBeginOverlap = OverlapSignature;


}
