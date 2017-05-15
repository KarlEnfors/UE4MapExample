// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "CellBlock.h"

CellBlock::CellBlock()
{
}

CellBlock::CellBlock(FMapSectionData inLayoutAttrs)
{
	this->LayoutAttrs = inLayoutAttrs;
}

void CellBlock::Aux_Initialize()
{



}

void CellBlock::Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles)
{

	Room r = Room(LayoutAttrs);
	r.Generate(InOutMapTiles);

	FMapSectionData Layout = LayoutAttrs;
	Layout.Size.X /= 2;
	Layout.Size.Y /= 2;

	Layout.MapLocation.X += Layout.Size.X / 2;
	Layout.MapLocation.Y += Layout.Size.Y / 2;

	NegativeSpace neg = NegativeSpace(Layout);
	neg.Generate(InOutMapTiles);

	isComplete = true;


}

void CellBlock::Aux_Finalize()
{



}
