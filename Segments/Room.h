// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseSegment.h"


/**
 * 
 */
class HACKNSLASH_API Room : public BaseSegment
{
public:
	Room();
	Room(FMapSectionData layoutdata);

	virtual void Aux_Initialize() override;

	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutTileMap) override;

	virtual void Aux_Finalize() override;

};
