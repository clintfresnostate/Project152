// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "MyHUD.h"

void AMyHUD::DrawHUD()
{
	// call superclass DrawHUD() function first
	Super::DrawHUD();
	// iterate from back to front thru the list, so if we remove
	// an item while iterating, there won't be any problems
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		// draw the background box the right size
		// for the message
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont,
			1.f);
		float messageH = outputHeight + 2.f*pad;
		float x = 0.f, y = c*messageH;
		// black backing
		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		// draw our message using the hudFont
		DrawText(messages[c].message, messages[c].color, x + pad, y + pad,
			hudFont);
		// reduce lifetime by the time that passed since last
		// frame.
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// if the message's time is up, remove it
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}
	}
	// then proceed to draw your stuff.
	// we can draw lines..
	DrawLine(200, 300, 400, 500, FLinearColor::Blue);
	// and we can draw text!
	DrawText("Greetings from Unreal!", FVector2D(0, 0), hudFont,
		FVector2D(1, 1), FColor::White);
}

void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}
