// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "BaseSegment.h"


BaseSegment::BaseSegment()
{



}

BaseSegment::BaseSegment(FMapSectionData layoutdata)
{
	LayoutAttrs = layoutdata;


}


void BaseSegment::Generate(TArray<TArray<TileData>> &InOutTileMap) 
{

	Aux_Initialize();
	isComplete = false;
	Aux_Generate(InOutTileMap);
	Aux_Finalize();
}

void BaseSegment::Aux_Initialize()
{




}

void BaseSegment::Aux_Generate(TArray<TArray<TileData>> &InOutTileMap)
{
	for (int x = 0; x < LayoutAttrs.Size.X; x++) {
		for (int y = 0; y < LayoutAttrs.Size.Y; y++) {
			InOutTileMap[x + LayoutAttrs.MapLocation.X][y + LayoutAttrs.MapLocation.Y].TileType = ETileType::TILETYPE_Floor;
		}
		//UE_LOG(LogTemp, Log, TEXT("Writing Tiles..."));

	}
	isComplete = true;
}

void BaseSegment::Aux_Finalize()
{



}

void BaseSegment::PlaceTileDataInMap(TileData tile, Coordinate2D localSpace, TArray<TArray<TileData>> &InOutTileMap)
{

	localSpace.X += LayoutAttrs.MapLocation.X;
	localSpace.Y += LayoutAttrs.MapLocation.Y;

	InOutTileMap[localSpace.X][localSpace.Y].TileType = tile.TileType;
	InOutTileMap[localSpace.X][localSpace.Y].Rotation = tile.Rotation;


}

