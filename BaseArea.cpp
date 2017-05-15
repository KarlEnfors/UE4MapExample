// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "BaseArea.h"



BaseArea::BaseArea()
{

}

BaseArea::BaseArea(FMapSectionData InLayoutAttrs)
{
	LayoutAttrs = InLayoutAttrs;
}

void BaseArea::Generate(TArray<TArray<TileData>> &InOutMapTiles)
{

	isComplete = false;
	Aux_Initialize();

	while (!isComplete)
	{
		Aux_Generate(InOutMapTiles);
		//CommitSegmentTiles(InOutSegments);
	}

	Aux_Finalize();
}

void BaseArea::Aux_Initialize()
{

}

void BaseArea::Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles)
{
	Room r = Room(LayoutAttrs);

	SegmentBrush = BaseSegment(LayoutAttrs);
	r.Generate(InOutMapTiles);

	isComplete = true;
}

void BaseArea::Aux_Finalize()
{

}


FMapSectionData BaseArea::GetLayoutAttributes()
{
	return LayoutAttrs;
}

void BaseArea::CommitSegmentTiles(TArray<TArray<TileData*>> &InOutSegments)
{
	//Add logic please.
}
