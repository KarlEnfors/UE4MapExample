// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "NegativeSpace.h"

NegativeSpace::NegativeSpace()
{



}

NegativeSpace::NegativeSpace(FMapSectionData layoutdata)
{

	this->LayoutAttrs = layoutdata;

}

void NegativeSpace::Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles)
{

	/*	UE_LOG(LogTemp, Log, TEXT("WHEN THE TRUTH IS FOUND!"));*/

	TileData tileBrush = TileData();
	tileBrush.TileType = TILETYPE_Void;
	tileBrush.Rotation = FRotator(0, 0, 0).Quaternion();


	for (int x = 0; x < LayoutAttrs.Size.X; x++) {
		for (int y = 0; y < LayoutAttrs.Size.Y; y++) {
			PlaceTileDataInMap(tileBrush, Coordinate2D(x, y), InOutMapTiles);

		}
	}


	isComplete = true;

}

void NegativeSpace::Aux_Initialize()
{


}

void NegativeSpace::Aux_Finalize()
{



}


