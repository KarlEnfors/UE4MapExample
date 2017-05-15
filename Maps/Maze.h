// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseMap.h"

/**
 * 
 */
class HACKNSLASH_API Maze : BaseMap
{
public:
	Maze();
	~Maze();

	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles) override;

	virtual void Aux_Initialize() override;

	virtual void Aux_Finalize() override;

};
