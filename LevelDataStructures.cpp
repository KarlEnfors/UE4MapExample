// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "Map/LevelDataStructures.h"



Coordinate2D FMapSectionData::GetGlobalConnection(bool isStart)
{
	Coordinate2D res;
	if (isStart)
	{
		res = LocalStartPoint;

	}
	else {
		res = LocalExitPoint;
	}

	res.X += MapLocation.X;
	res.Y += MapLocation.Y;

	return res;
}
