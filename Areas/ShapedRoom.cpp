// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "ShapedRoom.h"

ShapedRoom::ShapedRoom()
{
}

ShapedRoom::ShapedRoom(FMapSectionData inLayoutAttrs)
{
	this->LayoutAttrs = inLayoutAttrs;
	seed = FMath::Rand() * 100;
	randoms.Initialize(seed);
}

void ShapedRoom::Aux_Initialize()
{
	nodeSize = LayoutAttrs.Size;
	nodeSize.X /= 8;
	nodeSize.Y /= 8;


	nodeMap.SetNum(10);
	for (int i = 0; i < nodeMap.Num(); i++)
	{
		nodeMap[i].SetNum(10);
	}

	style = setStyle();

	bIsIndoor = randoms.FRandRange(1, 10) > 5;

}

void ShapedRoom::Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles)
{


	FMapSectionData segmentLayout;
	RoomFragment room;
	segmentLayout.Size = nodeSize;

	for (int y = 1; y < 9; y++)
	{
		for (int x = 1; x < 9; x++)
		{
			nodeMap[x][y] = true;

			 	
		}
	}

	AddNegShapes();



	for (int y = 1; y < 9; y++)
	{
		for (int x = 1; x < 9; x++)
		{
			
			segmentLayout.MapLocation = LayoutAttrs.MapLocation;
			segmentLayout.MapLocation.X += (x - 1) * nodeSize.X;
			segmentLayout.MapLocation.Y += (y - 1) * nodeSize.Y;


			if (nodeMap[x][y])
			{

				room = RoomFragment(segmentLayout, getAdjacentNodes(x, y));
				room.Generate(InOutMapTiles);

			}
		}
	}

	Coordinate2D connection = LayoutAttrs.MapLocation;
	connection.X += LayoutAttrs.LocalStartPoint.X;
	connection.Y += LayoutAttrs.LocalStartPoint.Y;
	InOutMapTiles[connection.X][connection.Y].TileType = TILETYPE_Floor;

	connection = LayoutAttrs.MapLocation;
	connection.X += LayoutAttrs.LocalExitPoint.X;
	connection.Y += LayoutAttrs.LocalExitPoint.Y;
	InOutMapTiles[connection.X][connection.Y].TileType = TILETYPE_Floor;


	isComplete = true;
}

void ShapedRoom::Aux_Finalize()
{


}

void ShapedRoom::AddNegShapes()
{

	if (randoms.RandRange(0,7) > 3)
	{
		PutCross();
	}
	else
	{
		PutDonut();
	}
	
	//PutRandom();


}

void ShapedRoom::PutDonut()
{
	int size = randoms.RandRange(1, 5);
	int x = nodeMap.Num() / 2;
	x -= (size / 2);
	int y = nodeMap[x].Num() / 2;
	y -= (size / 2);

	
	for (int i = 0; i < size; i++)
	{
		nodeMap[x][y] = false;
		nodeMap[x][y+1]   = false;
		nodeMap[x+1][y]   = false;
		nodeMap[x+1][y+1] = false;

		if (i % 2 == 0)
		{
			x++;
		}
		else
		{
			y++;
		}
	}
}


void ShapedRoom::PutCross()
{
	
	for (int i = 1; i < randoms.RandRange(2, 4); i++)
	{
		for (int j = 1; j < randoms.RandRange(2, 4); j++)
		{
			SetNegativeNode(i, j);
			SetNegativeNode(nodeMap.Num() - j -1, i);
			SetNegativeNode(j, nodeMap[4].Num() - i -1);
			SetNegativeNode(nodeMap.Num() - j -1, nodeMap[4].Num() - i -1);
		}
	}


}

void ShapedRoom::PutRandom()
{



	
}

void ShapedRoom::SetNegativeNode(int x, int y)
{
	x--;
	y--;
	Coordinate2D connection = LayoutAttrs.LocalStartPoint;

	if (x >= nodeMap.Num() || x < 0) return;
	if (y >= nodeMap.Num() || y < 0)  return;

	if (!ContainsConnection(x, y, connection))
	{
		connection = LayoutAttrs.LocalExitPoint;
		if (!ContainsConnection(x, y, connection))
		{
			nodeMap[x + 1][y + 1] = false;
		}
	}

}

ERoomStyle ShapedRoom::setStyle()
{
	
	return ROOMSTYLE_MAX;
}

TArray<TArray<bool>> ShapedRoom::getAdjacentNodes(int x, int y)
{
	TArray<TArray<bool>> adjacent;
	TArray<bool> tempRow;
	adjacent.SetNum(3);
	for (int i = 0; i < 3; i++)
	{
		adjacent[i].SetNum(3);
	}

	adjacent[0][0] = nodeMap[x - 1][y - 1];
	adjacent[1][0] = nodeMap[x ][y - 1];
	adjacent[2][0] = nodeMap[x + 1][y - 1];

	adjacent[0][1] = nodeMap[x - 1][y];
	adjacent[1][1] = nodeMap[x][y];
	adjacent[2][1] = nodeMap[x + 1][y];

	adjacent[0][2] = nodeMap[x - 1][y + 1];
	adjacent[1][2] = nodeMap[x][y + 1];
	adjacent[2][2] = nodeMap[x + 1][y + 1];

	return adjacent;
}


uint8 ShapedRoom::NoOfAdjacent(int x, int y)
{
	return 0;
}

bool ShapedRoom::ContainsConnection(int x, int y, Coordinate2D connection)
{
	if (connection.X >= (x * nodeSize.X) - 1 && connection.X <= ((x + 1) * nodeSize.X) + 1)
	{
		if (connection.Y >= (y * nodeSize.Y) - 1 && connection.Y <= ((y + 1) * nodeSize.Y) + 1)
		{
			return true;
		}
	}

	return false;
}
