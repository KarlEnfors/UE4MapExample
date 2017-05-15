// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "Room.h"

Room::Room(FMapSectionData layoutdata)
{
	this->LayoutAttrs = layoutdata;
}

Room::Room()
{

}

void Room::Aux_Initialize()
{



}

void Room::Aux_Generate(TArray<TArray<TileData>> &InOutTileMap)
{

/*	UE_LOG(LogTemp, Log, TEXT("WHEN THE TRUTH IS FOUND!"));*/

	for (int x = 0; x < LayoutAttrs.Size.X; x++) {
		for (int y = 0; y < LayoutAttrs.Size.Y; y++) {
			InOutTileMap[x + LayoutAttrs.MapLocation.X][y + LayoutAttrs.MapLocation.Y].TileType = ETileType::TILETYPE_Floor;
		}

	}

	FQuat rot = FQuat(0.f, 0.f, 1.f, 0.f);
	//							Z


	for (int y = 0; y < LayoutAttrs.Size.Y; y++) {
		InOutTileMap[LayoutAttrs.MapLocation.X]						[y + LayoutAttrs.MapLocation.Y].TileType = ETileType::TILETYPE_Wall;
		InOutTileMap[LayoutAttrs.MapLocation.X]						[y + LayoutAttrs.MapLocation.Y].Rotation = FRotator(0.f, 90.f, 0.f).Quaternion();

		InOutTileMap[LayoutAttrs.MapLocation.X + LayoutAttrs.Size.X -1][y + LayoutAttrs.MapLocation.Y].TileType = ETileType::TILETYPE_Wall;
		InOutTileMap[LayoutAttrs.MapLocation.X + LayoutAttrs.Size.X -1][y + LayoutAttrs.MapLocation.Y].Rotation = FRotator(0.f, -90.f, 0.f).Quaternion();

	}

	for (int x = 0; x < LayoutAttrs.Size.X; x++) {
		InOutTileMap[x + LayoutAttrs.MapLocation.X]					[LayoutAttrs.MapLocation.Y].TileType = ETileType::TILETYPE_Wall;
		InOutTileMap[x + LayoutAttrs.MapLocation.X]					[LayoutAttrs.MapLocation.Y].Rotation = FRotator(0.f, 180.f, 0.f).Quaternion();

		InOutTileMap[x + LayoutAttrs.MapLocation.X][LayoutAttrs.MapLocation.Y + LayoutAttrs.Size.Y -1].TileType = ETileType::TILETYPE_Wall;
		InOutTileMap[x + LayoutAttrs.MapLocation.X][LayoutAttrs.MapLocation.Y + LayoutAttrs.Size.Y -1].Rotation = FRotator(0.f, 0.f, 0.f).Quaternion(); 

	}
	InOutTileMap[LayoutAttrs.MapLocation.X][LayoutAttrs.MapLocation.Y].TileType = ETileType::TILETYPE_Corner;
	InOutTileMap[LayoutAttrs.MapLocation.X][LayoutAttrs.MapLocation.Y].Rotation = FRotator(0.f, 180.f, 0.f).Quaternion();

	InOutTileMap[LayoutAttrs.MapLocation.X + LayoutAttrs.Size.X -1][LayoutAttrs.MapLocation.Y].TileType = ETileType::TILETYPE_Corner;
	InOutTileMap[LayoutAttrs.MapLocation.X + LayoutAttrs.Size.X -1][LayoutAttrs.MapLocation.Y].Rotation = FRotator(0.f, -90.f, 0.f).Quaternion();

	InOutTileMap[LayoutAttrs.MapLocation.X][LayoutAttrs.MapLocation.Y + LayoutAttrs.Size.Y -1].TileType = ETileType::TILETYPE_Corner;
	InOutTileMap[LayoutAttrs.MapLocation.X][LayoutAttrs.MapLocation.Y + LayoutAttrs.Size.Y -1].Rotation = FRotator(0.f, 90.f, 0.f).Quaternion();

	InOutTileMap[LayoutAttrs.MapLocation.X + LayoutAttrs.Size.X -1][LayoutAttrs.MapLocation.Y + LayoutAttrs.Size.Y -1].TileType = ETileType::TILETYPE_Corner;
	InOutTileMap[LayoutAttrs.MapLocation.X + LayoutAttrs.Size.X -1][LayoutAttrs.MapLocation.Y + LayoutAttrs.Size.Y -1].Rotation = FRotator(0.f, 0.f, 0.f).Quaternion();

 	InOutTileMap[LayoutAttrs.MapLocation.X + LayoutAttrs.LocalStartPoint.X][LayoutAttrs.MapLocation.Y + LayoutAttrs.LocalStartPoint.Y].TileType = ETileType::TILETYPE_Floor;
	InOutTileMap[LayoutAttrs.MapLocation.X + LayoutAttrs.LocalExitPoint.X][LayoutAttrs.MapLocation.Y  + LayoutAttrs.LocalExitPoint.Y].TileType  = ETileType::TILETYPE_Floor;


	isComplete = true;
}

void Room::Aux_Finalize()
{



}
