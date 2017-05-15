// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "RoomFragment.h"

RoomFragment::RoomFragment()
{
}

RoomFragment::RoomFragment(FMapSectionData inLayoutAttrs)
{
	this->LayoutAttrs = inLayoutAttrs;
}


RoomFragment::RoomFragment(FMapSectionData inLayoutAttrs, TArray<TArray<bool>> adjacentSegments)
{
	this->LayoutAttrs = inLayoutAttrs;
	Adjacents = adjacentSegments;
}

void RoomFragment::Aux_Initialize()
{



}

void RoomFragment::Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles)
{
	//Fill with floor
	TileData brush = TileData();


	brush.TileType = TILETYPE_Floor;
	brush.Rotation = FRotator(0, 0, 0).Quaternion();
	
	for (int y = 0; y < LayoutAttrs.Size.Y; y++)
	{
		for (int x = 0; x < LayoutAttrs.Size.X; x++)
		{
			PlaceTileDataInMap(brush, Coordinate2D(x, y), InOutMapTiles);
		}
	}

	//Put appropiate walls.

	brush.TileType = TILETYPE_Wall;
	if (!Adjacents[1][0])
	{
		//UP
		brush.Rotation = FRotator(0.f, 180.f, 0.f).Quaternion();
		for (int x = 0; x < LayoutAttrs.Size.X - 1; x++)
		{

			PlaceTileDataInMap(brush, Coordinate2D(x, 0), InOutMapTiles);
		}

	}
	if (!Adjacents[1][2])
	{
		//DOWN
		brush.Rotation = FRotator(0.f, 0.f, 0.f).Quaternion();
		for (int x = 0; x < LayoutAttrs.Size.X - 1; x++)
		{

			PlaceTileDataInMap(brush, Coordinate2D(x, LayoutAttrs.Size.Y-1), InOutMapTiles);
		}

	}
	if (!Adjacents[0][1])
	{
		//LEFT
		brush.Rotation = FRotator(0.f, 90.f, 0.f).Quaternion();
		for (int y = 0; y < LayoutAttrs.Size.Y - 1; y++)
		{

			PlaceTileDataInMap(brush, Coordinate2D(0, y), InOutMapTiles);
		}

	}
	if (!Adjacents[2][1])
	{
		//RIGHT
		brush.Rotation = FRotator(0.f, -90.f, 0.f).Quaternion();
		for (int y = 0; y < LayoutAttrs.Size.Y - 1; y++)
		{

			PlaceTileDataInMap(brush, Coordinate2D(LayoutAttrs.Size.X -1, y), InOutMapTiles);
		}
	}

	FRotator tempRot;

	//UP LEFT
	brush = GetCornerTileData(Adjacents[0][0], Adjacents[0][1], Adjacents[1][0]);
	tempRot = brush.Rotation.Rotator();
	tempRot.Yaw -= 0;
	brush.Rotation = tempRot.Quaternion();

	PlaceTileDataInMap(brush, Coordinate2D(0, 0), InOutMapTiles);
	

	//UP RIGHT
	brush = GetCornerTileData(Adjacents[2][0], Adjacents[1][0], Adjacents[2][1]);
	tempRot = brush.Rotation.Rotator();
	tempRot.Yaw += 90;
	brush.Rotation = tempRot.Quaternion();

	PlaceTileDataInMap(brush, Coordinate2D(LayoutAttrs.Size.X -1, 0), InOutMapTiles);
	

	//DOWN RIGHT
	brush = GetCornerTileData(Adjacents[2][2], Adjacents[2][1], Adjacents[1][2]);
	tempRot = brush.Rotation.Rotator();
	tempRot.Yaw += 180;
	brush.Rotation = tempRot.Quaternion();

	PlaceTileDataInMap(brush, Coordinate2D(LayoutAttrs.Size.X - 1, LayoutAttrs.Size.Y - 1), InOutMapTiles);



	//DOWN LEFT
	brush = GetCornerTileData(Adjacents[0][2], Adjacents[1][2], Adjacents[0][1]);
	tempRot = brush.Rotation.Rotator();
	tempRot.Yaw -= 90;
	brush.Rotation = tempRot.Quaternion();

	PlaceTileDataInMap(brush, Coordinate2D(0, LayoutAttrs.Size.Y - 1), InOutMapTiles);

	//ADD OFFSET





	isComplete = true;
}

void RoomFragment::Aux_Finalize()
{
	//Adjust startpoints?


}

TileData RoomFragment::GetCornerTileData(bool diag, bool a, bool b)
{
	TileData result = TileData();
	FRotator rot = FRotator(0, 0.f, 0);

	result.TileType = TILETYPE_Floor;

	if (!diag)
	{
		result.TileType = TILETYPE_InvCorner;
		rot.Yaw = 180;
	}

	if (!a && !b)
	{
		result.TileType = TILETYPE_Corner;
		rot.Yaw = 180;
	}
	else
	{
		if (!a)
		{
			result.TileType = TILETYPE_Wall;
			rot.Yaw = +90;
		}else if(!b) {
			result.TileType = TILETYPE_Wall;
			rot.Yaw = -180;
		}
	}

	//SET ROTATION!
	result.Rotation = rot.Quaternion();

	return result;
}
