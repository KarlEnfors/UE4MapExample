// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Map/BaseArea.h"
#include "Map/Segments/Room.h"

/**
 * 
 */
class HACKNSLASH_API IndoorPath : public BaseArea
{
public:
	IndoorPath(FMapSectionData InLayoutAttrs);

	virtual void Aux_Initialize() override;

	virtual void Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles) override;

	virtual void Aux_Finalize() override;

	


private:
	int MinEdgeDistance;
	int MinRoomSize;
	

	FRandomStream randoms;
	TArray<FMapSectionData> Nodes;

	void SetRoomConnection(Coordinate2D entry, Coordinate2D &roomConnection);
	void PutCorridoor(Coordinate2D a, Coordinate2D b, FMapSectionData &Node);
	void LinkRooms(Coordinate2D connection, Coordinate2D roomConnection, FMapSectionData &node, int dir);

};