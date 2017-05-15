// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/LevelDataStructures.h"

/**
*
*/


class HACKNSLASH_API BaseSegment
{
public:
	//BaseSegment(int width, int height, Coordinate2D location);
	BaseSegment();
	BaseSegment(FMapSectionData layoutdata);

	void Generate(TArray<TArray<TileData>> &InOutTileMap);


private:
protected:
	virtual void Aux_Initialize();
	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles);
	virtual void Aux_Finalize();
	
	FMapSectionData LayoutAttrs;
	bool isComplete;

	void PlaceTileDataInMap(TileData tile, Coordinate2D localSpace, TArray<TArray<TileData>> &InOutTileMap);

};