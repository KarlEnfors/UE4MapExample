// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseSegment.h"

/**
 * 
 */
class HACKNSLASH_API RoomFragment : public BaseSegment
{
public:
	RoomFragment();
	RoomFragment(FMapSectionData inLayoutAttrs);
	RoomFragment(FMapSectionData inLayoutAttrs, TArray<TArray<bool>> adjacentSegments);

	virtual void Aux_Initialize() override;

	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles) override;

	virtual void Aux_Finalize() override;


private:
	TArray<TArray<bool>> Adjacents;
	
	TileData GetCornerTileData(bool diag, bool a, bool b);
};