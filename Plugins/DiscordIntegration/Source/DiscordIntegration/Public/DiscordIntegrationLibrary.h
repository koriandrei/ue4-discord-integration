// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiscordActivity.h"

#include "DiscordIntegrationLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DISCORDINTEGRATION_API UDiscordIntegrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	void UpdateActivity(const FDiscordActivity& Activity);
};
