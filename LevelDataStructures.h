// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
*
*/

enum HACKNSLASH_API ETileType
{
	TILETYPE_Void,
	TILETYPE_Floor,
	TILETYPE_Wall,
	TILETYPE_Corner,
	TILETYPE_InvCorner,
	TILETYPE_MAX

};

struct HACKNSLASH_API Coordinate2D {
public:

	Coordinate2D()
		: X(0)
		, Y(0) {
	};
	Coordinate2D(uint16 x, uint16 y)
		: X(x)
		, Y(y) {
	};
	uint16 X;
	uint16 Y;
};

struct HACKNSLASH_API TileSet
{

	FString FloorMeshRef;
	FString WallMeshRef;
	FString CornerMeshRef;
	FString NegCornerMeshRef;

	

};


struct HACKNSLASH_API FMapSectionData {

	FMapSectionData() {};
	FMapSectionData(Coordinate2D sectionlocation, Coordinate2D sectionsize, Coordinate2D localstart, Coordinate2D localexit)
		: MapLocation(sectionlocation)
		, Size(sectionsize)
		, LocalStartPoint(localstart)
		, LocalExitPoint(localexit) {};
public:
	Coordinate2D MapLocation;
	Coordinate2D Size;
	Coordinate2D LocalStartPoint;
	Coordinate2D LocalExitPoint;

	Coordinate2D GetGlobalConnection(bool isStart);
};


struct HACKNSLASH_API FGenerationRules
{

public:

	FName TileSetName;

	bool bIsIndoors;

	TArray<FName> OptionalTags;

};



struct HACKNSLASH_API TileData
{

public:
	TileData()
		: TileType(ETileType::TILETYPE_Void)
		, AreaID(-1)
		, SegmentID(-1) {
	};
	TileData(ETileType type)
		: TileType(type) {};

	ETileType TileType;
	FQuat Rotation;
	uint32 AreaID;
	uint32 SegmentID;

private:


protected:


};
