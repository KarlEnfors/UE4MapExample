
// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "BaseMap.h"


// Sets default values
BaseMap::BaseMap()
{
	


}




BaseMap::BaseMap(FMapSectionData InLayoutAttrs)
{
	LayoutAttrs = InLayoutAttrs;
}

/************************************************************************/
/*	Generate
After map conditions are initialized.
Creates singular Area of segments of tiles
by initializing the area, generating it, then committing it.
Do not override.
Safe to override Auxillary tools. Aux_generate/initialize/finalize
*/
/************************************************************************/
void BaseMap::Generate(TArray<TArray<TileData>> &InOutMapTiles)
{
	isComplete = false;
	Aux_Initialize();
	while (!isComplete)
	{
		Aux_Generate(InOutMapTiles);

		//Impletment later 
		//CommitAreaTiles();

	}
	Aux_Finalize();
}

Coordinate2D BaseMap::GetExitPoint()
{
	return this->LayoutAttrs.LocalExitPoint;
}

void BaseMap::CommitAreaTiles()
{
	TArray<TileData*> AreaTileRefs;
	for (int y = AreaBrush.GetLayoutAttributes().MapLocation.Y; y < AreaBrush.GetLayoutAttributes().Size.Y; y++)
	{
		for (int x = AreaBrush.GetLayoutAttributes().MapLocation.X; x < AreaBrush.GetLayoutAttributes().Size.X; x++)
		{
			AreaTileRefs.Add(&TileMap[x][y]);
		}
	}
	Areas.Add(AreaTileRefs);
}