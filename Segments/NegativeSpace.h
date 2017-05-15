// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseSegment.h"


/**
 * 
 */
class HACKNSLASH_API NegativeSpace : public BaseSegment
{
public:
	NegativeSpace();
	NegativeSpace(FMapSectionData layoutdata);

	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles) override;

	virtual void Aux_Initialize() override;

	virtual void Aux_Finalize() override;


private:
	

};