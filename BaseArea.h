// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseSegment.h"
#include "Map/LevelDataStructures.h"
#include "Map/Segments/Room.h"
#include "Map/Segments/NegativeSpace.h"

/**
*
*/
class HACKNSLASH_API BaseArea
{
public:
	BaseArea();
	BaseArea(FMapSectionData InLayoutAttrs);

	void Generate(TArray<TArray<TileData>> &InOutMapTiles);


	FMapSectionData GetLayoutAttributes();
private:

	void CommitSegmentTiles(TArray<TArray<TileData*>> &InOutSegments);

protected:
	FMapSectionData LayoutAttrs;
	bool isComplete;

	BaseSegment SegmentBrush;

	virtual void Aux_Initialize();
	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles);
	virtual void Aux_Finalize();


};
