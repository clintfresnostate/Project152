// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "NPC.h"

ANPC::ANPC(const class FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer)
{
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,
		TEXT("Proximity Sphere"));
	ProxSphere->AttachTo(RootComponent);
	ProxSphere->SetSphereRadius(32.f);
	// Code to make ANPC::Prox() run when this proximity sphere
	// overlaps another actor.
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox_Implementation);
	NpcMessage = "Shop";//default message, can be edited
	// in blueprints
	// This is where our code will go for what happens
	// when there is an intersection
	
}



