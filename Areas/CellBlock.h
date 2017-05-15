// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseArea.h"
#include "Map/Segments/NegativeSpace.h"
#include "Map/Segments/Room.h"

/**
 * 
 */
class HACKNSLASH_API CellBlock : public BaseArea
{
public:
	CellBlock();
	CellBlock(FMapSectionData inLayoutAttrs);

	virtual void Aux_Initialize() override;

	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles) override;

	virtual void Aux_Finalize() override;

};
