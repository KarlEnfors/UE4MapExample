// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseArea.h"
#include "Map/Segments/RoomFragment.h"

/**
 * 
 */

enum ERoomStyle {

	ROOMSTYLE_Cross,
	ROOMSTYLE_Random,
	ROOMSTYLE_Donut,
	ROOMSTYLE_Box,
	ROOMSTYLE_MAX
};


class HACKNSLASH_API ShapedRoom : public BaseArea
{
public:
	ShapedRoom();
	ShapedRoom(FMapSectionData inLayoutAttrs);

	virtual void Aux_Initialize() override;

	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles) override;

	virtual void Aux_Finalize() override;



private:

	bool bIsIndoor = true;
	ERoomStyle style;
	int seed;
	Coordinate2D nodeSize;
	FRandomStream randoms;
	
	TArray<TArray<bool>> nodeMap;

	void AddNegShapes();
	void PutDonut();
	void PutCross();
	void PutRandom();

	void SetNegativeNode(int x, int y);
	ERoomStyle setStyle();
	TArray<TArray<bool>> getAdjacentNodes(int x, int y);
	uint8 NoOfAdjacent(int x, int y);
	bool ContainsConnection(int x, int y, Coordinate2D connection);
};
