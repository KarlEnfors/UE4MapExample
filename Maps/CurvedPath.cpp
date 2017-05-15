// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "CurvedPath.h"

CurvedPath::CurvedPath()
{
}

CurvedPath::CurvedPath(FMapSectionData InLayoutAttrs)
{
	LayoutAttrs = InLayoutAttrs;

	seed = FMath::Rand() * 100;
	randoms.Initialize(seed);
}

CurvedPath::~CurvedPath()
{

}

void CurvedPath::Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles)
{
	NodeMap[Cursor.X][Cursor.Y].LocalStartPoint = LocalConnectionPoint;


	if (Cursor.X != ExitPoint.X && Cursor.Y != ExitPoint.Y)
	{
		goRight = FMath::RandBool();

	}
	else
	{
		goRight = (Cursor.X != ExitPoint.X);
	}
	
	if (goRight)
	{
		LocalConnectionPoint.X = NodeMap[Cursor.X][Cursor.Y].Size.X-1;
		LocalConnectionPoint.Y = randoms.RandRange(2, NodeMap[Cursor.X][Cursor.Y].Size.Y -3);
	}
	else
	{
		LocalConnectionPoint.X = randoms.RandRange(2, NodeMap[Cursor.X][Cursor.Y].Size.X -3);
		LocalConnectionPoint.Y = NodeMap[Cursor.X][Cursor.Y].Size.Y-1;
	}

	NodeMap[Cursor.X][Cursor.Y].LocalExitPoint = LocalConnectionPoint;

	if (Cursor.X == ExitPoint.X && Cursor.Y == ExitPoint.Y)
	{

		isComplete = true;
	}


	if (flipper)
	{
		ShapedRoom area = ShapedRoom(NodeMap[Cursor.X][Cursor.Y]);
		area.Generate(InOutMapTiles);
	}
	else
	{
		IndoorPath area = IndoorPath(NodeMap[Cursor.X][Cursor.Y]);
		area.Generate(InOutMapTiles);
	}
	flipper = !flipper;

// 	//BUILD ONE ONLY
// 	isComplete = true;


	//UE_LOG(LogTemp, Log, TEXT("Area at: (%i,%i) "), area.GetLayoutAttributes().MapLocation.X, area.GetLayoutAttributes().MapLocation.Y);

	if (goRight) {
		Cursor.X++;
		LocalConnectionPoint.X = 0;
	}
	else {
		Cursor.Y++;
		LocalConnectionPoint.Y = 0;
	}
}

void CurvedPath::Aux_Initialize()
{
	seed = FMath::Rand();
	FMath::SRandInit(seed);

	int AreaSizeX = 24;
	int AreaSizeY = 24;

	NodeMap.SetNum(LayoutAttrs.Size.X / AreaSizeX);
	for (int i = 0; i < NodeMap.Num(); i++) {
		NodeMap[i].SetNum(LayoutAttrs.Size.Y / AreaSizeY);
	}

	for (int y = 0; y < NodeMap.Num(); y++) {
		for (int x = 0; x < NodeMap.Num(); x++) {
			NodeMap[x][y].Size.X = AreaSizeX;
			NodeMap[x][y].Size.Y = AreaSizeY;

			NodeMap[x][y].MapLocation.X = AreaSizeX*x;
			NodeMap[x][y].MapLocation.Y = AreaSizeY*y;


		}
	}

	StartPoint.X = 0;
	StartPoint.Y = 0;

	ExitPoint.X = randoms.RandRange(1, NodeMap[0].Num() - 1);
	ExitPoint.Y = randoms.RandRange(1, NodeMap[0].Num() - 1);

	LocalConnectionPoint.X = 0;
	LocalConnectionPoint.Y = AreaSizeY / 2;

	NodeMap[ExitPoint.X][ExitPoint.Y].LocalExitPoint = Coordinate2D(0, AreaSizeY / 2);


	Cursor = StartPoint;

}

void CurvedPath::Aux_Finalize()
{
	LayoutAttrs.LocalExitPoint = NodeMap[ExitPoint.X][ExitPoint.Y].GetGlobalConnection(false);


}