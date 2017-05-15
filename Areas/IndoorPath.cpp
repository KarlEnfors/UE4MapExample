// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "IndoorPath.h"



IndoorPath::IndoorPath(FMapSectionData InLayoutAttrs)
{
	this->LayoutAttrs = InLayoutAttrs;

}

void IndoorPath::Aux_Initialize()
{
	isComplete = false;
	
	int32 seed = FMath::Rand() * 100;
	randoms.Initialize(seed);

	MinEdgeDistance		= 3;
	MinRoomSize			= LayoutAttrs.Size.X / 2;

	FMapSectionData hall;

	hall.Size.X = randoms.RandRange(MinRoomSize, LayoutAttrs.Size.X - MinEdgeDistance * 2);
	hall.Size.Y = randoms.RandRange(MinRoomSize, LayoutAttrs.Size.Y - MinEdgeDistance * 2);

	hall.MapLocation = LayoutAttrs.MapLocation;
	hall.MapLocation.X += randoms.RandRange(MinEdgeDistance, LayoutAttrs.Size.X - hall.Size.X - MinEdgeDistance);
	hall.MapLocation.Y += randoms.RandRange(MinEdgeDistance, LayoutAttrs.Size.Y - hall.Size.Y - MinEdgeDistance);

// 	hall.Size.X = 8;
// 	hall.Size.Y = 8;
// 
// 	hall.MapLocation = LayoutAttrs.MapLocation;
// 	hall.MapLocation.X += 4;
// 	hall.MapLocation.Y += 4;

	Nodes.Add(hall);

}

void IndoorPath::Aux_Generate(TArray<TArray<TileData>> &InOutMapTiles)
{
	SetRoomConnection(LayoutAttrs.LocalStartPoint, Nodes[0].LocalStartPoint);
	SetRoomConnection(LayoutAttrs.LocalExitPoint, Nodes[0].LocalExitPoint);


	Room r;
	

	for (FMapSectionData node : Nodes)
	{
		r = Room(node);
		r.Generate(InOutMapTiles);

	}


	isComplete = true;
}

void IndoorPath::Aux_Finalize()
{




}

void IndoorPath::SetRoomConnection(Coordinate2D connection, Coordinate2D &roomConnection)
{


	Coordinate2D localRoomEntry;
	localRoomEntry = Nodes[0].MapLocation;
	localRoomEntry.X -= LayoutAttrs.MapLocation.X;
	localRoomEntry.Y -= LayoutAttrs.MapLocation.Y;
	Coordinate2D corrExtraSize;
	FMapSectionData corr;
	int dir = 0;


	if (connection.X == 0)
	{
		//LEFT
		roomConnection.X = 0;
		roomConnection.Y = randoms.RandRange(2, Nodes[0].Size.Y - 2);
		corrExtraSize.Y = 2;
		dir = 1;
	}


	else if(connection.Y == 0)
	{
		//UP
		roomConnection.Y = 0;
		roomConnection.X = randoms.RandRange(2, Nodes[0].Size.X - 2);
		corrExtraSize.X = 2;
		dir = 2;
	}


	else if (connection.X == LayoutAttrs.Size.X - 1)
	{
		//Right
		roomConnection.X = Nodes[0].Size.X - 1;
		roomConnection.Y = randoms.RandRange(2, Nodes[0].Size.Y - 2);
		localRoomEntry.X++;
		corrExtraSize.Y = 2;
		corrExtraSize.X = 1;
		dir = 3;
	}


	else if (connection.Y == LayoutAttrs.Size.Y - 1)
	{
		//Down
		roomConnection.Y = Nodes[0].Size.Y - 1;
		roomConnection.X = randoms.RandRange(2, Nodes[0].Size.X - 2);
		localRoomEntry.Y++;
		corrExtraSize.X = 2;
		corrExtraSize.Y = 1;
		dir = 4;

	}

	localRoomEntry.X += roomConnection.X;
	localRoomEntry.Y += roomConnection.Y;

	PutCorridoor(connection, localRoomEntry, corr);
	corr.Size.X += corrExtraSize.X;
	corr.Size.Y += corrExtraSize.Y;
	LinkRooms(connection, localRoomEntry, corr, dir);

	Nodes.Add(corr);


}


void IndoorPath::LinkRooms(Coordinate2D localA, Coordinate2D localB, FMapSectionData &node, int dir)
{

	Coordinate2D nodeLocalLoc = node.MapLocation;
	nodeLocalLoc.X -= LayoutAttrs.MapLocation.X;
	nodeLocalLoc.Y -= LayoutAttrs.MapLocation.Y;

	Coordinate2D ConnectionTilt = Coordinate2D();

	switch (dir)
	{
	case 1:
		//LEFT
		localB.X--;
		node.MapLocation.Y--;
		node.Size.Y++;

		ConnectionTilt.Y++;

		
		break;
	case 2:
		//UP
		localB.Y--;
		node.MapLocation.X--;
		node.Size.X++;

		ConnectionTilt.X++;


		break;
	case 3:
		//RIGHT
		node.MapLocation.Y--;
		node.Size.Y++;
		ConnectionTilt.Y++;


		break;
	case 4:
		//DOWN
		node.MapLocation.X--;
		node.Size.X++;
		ConnectionTilt.X++;


		break;
	default:
		node.LocalStartPoint = Coordinate2D();
		node.LocalExitPoint = Coordinate2D();
		return;
	}
	localA.X -= nodeLocalLoc.X;
	localA.Y -= nodeLocalLoc.Y;
	localB.X -= nodeLocalLoc.X;
	localB.Y -= nodeLocalLoc.Y;


	node.LocalStartPoint = localA;
	node.LocalExitPoint = localB;

	node.LocalStartPoint.X += ConnectionTilt.X;
	node.LocalStartPoint.Y += ConnectionTilt.Y;
	node.LocalExitPoint.X += ConnectionTilt.X;
	node.LocalExitPoint.Y += ConnectionTilt.Y;

}


void IndoorPath::PutCorridoor(Coordinate2D a, Coordinate2D b, FMapSectionData &Node)
{
	uint8 tmp;

	if (a.X > b.X)
	{
		tmp = a.X;
		a.X = b.X;
		b.X = tmp;
	}

	if (a.Y > b.Y)
	{
		tmp = a.Y;
		a.Y = b.Y;
		b.Y = tmp;
	}

	Node.MapLocation = LayoutAttrs.MapLocation;
	Node.MapLocation.X += a.X;
	Node.MapLocation.Y += a.Y;
	Node.Size.X = b.X - a.X;
	Node.Size.Y = b.Y - a.Y;

	if (Node.Size.X <= 1)
	{
		Node.Size.X = MinEdgeDistance;
	}
	if (Node.Size.Y <= 1)
	{
		Node.Size.Y = MinEdgeDistance;
	}


// 	double d = (Node.MapLocation.X - Nodes[0].MapLocation.X);
// 	Node.LocalStartPoint.X -= (Node.MapLocation.X - Nodes[0].MapLocation.X);
// 
// 	UE_LOG(LogTemp, Log, TEXT("Double: %i"), d);
// 	UE_LOG(LogTemp, Log, TEXT("Start: (%i,%i)"), Node.LocalStartPoint.X, Node.LocalStartPoint.Y);

	//Node.LocalStartPoint = Coordinate2D();

}


