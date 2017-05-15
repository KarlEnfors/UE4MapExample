// Fill out your copyright notice in the Description page of Project Settings.

#include "HackNSlash.h"
#include "LevelDecorator.h"


// Sets default values
ALevelDecorator::ALevelDecorator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelDecorator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelDecorator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

