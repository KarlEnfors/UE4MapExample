// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Map/LevelDataStructures.h"
#include "Map/BaseArea.h"
#include "Map/BaseSegment.h"


class HACKNSLASH_API BaseMap
{

public:

	BaseMap();
	BaseMap(FMapSectionData InLayoutAttrs);

	TArray<TArray<TileData>>	TileMap;
	TArray<TArray<TileData*>>	Segments;
	TArray<TArray<TileData*>>	Areas;

	void Generate(TArray<TArray<TileData>> &InOutMapTiles);
	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles) = 0;
	virtual void Aux_Initialize() = 0;
	virtual void Aux_Finalize() = 0;

	Coordinate2D GetExitPoint();

protected:
	FMapSectionData LayoutAttrs;
	void CommitAreaTiles();
	BaseArea AreaBrush;
	bool isComplete;
	float seed;

};