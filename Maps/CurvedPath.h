// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseMap.h"
#include "Map/Areas/IndoorPath.h"
#include "Map/Areas/ShapedRoom.h"
#include "Map/Areas/CellBlock.h"

/**
 * 
 */
class HACKNSLASH_API CurvedPath : public BaseMap
{
public:
	CurvedPath();
	CurvedPath(FMapSectionData InLayoutAttrs);
	~CurvedPath();

	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles) override;

	virtual void Aux_Initialize() override;

	virtual void Aux_Finalize() override;




private:
	bool flipper = false;
	TArray<TArray<FMapSectionData>> NodeMap;
	Coordinate2D StartPoint;
	Coordinate2D ExitPoint;
	Coordinate2D LocalConnectionPoint;

	Coordinate2D Cursor;

	FRandomStream randoms;
	bool goRight;
};
