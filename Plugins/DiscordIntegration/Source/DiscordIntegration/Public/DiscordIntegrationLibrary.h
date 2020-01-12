// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiscordActivity.h"

#include "Kismet/BlueprintAsyncActionBase.h"

#include "DiscordIntegrationLibrary.generated.h"

UENUM(BlueprintType)
enum class EDiscordActivityUpdateResult : uint8
{
	Ok,
	Unidentified,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDiscordActivityUpdate, EDiscordActivityUpdateResult, Result, int, FriendsCount);

UCLASS()
class DISCORDINTEGRATION_API UUpdateDiscordActivity : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FOnDiscordActivityUpdate OnUpdated;


	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = true, WorldContext = Context))
	static UUpdateDiscordActivity* UpdateActivityHack(const FDiscordActivity& Activity, UObject* Context);

	UObject* Context;
private:
	friend class UDiscordIntegrationLibrary;

	void OnActivityUpdated(EDiscordActivityUpdateResult Result)
	{
		OnUpdated.Broadcast(Result, -100);

		//SetReadyToDestroy();
	}

	virtual void Activate() override;
	bool bIsCountAvailable = false;
};

/**
 * 
 */
UCLASS()
class DISCORDINTEGRATION_API UDiscordIntegrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = true, WorldContext = Context))
	static UUpdateDiscordActivity* UpdateActivity(const FDiscordActivity& Activity, UObject* Context);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = Context))
	static int GetFriendsCount(const UObject* Context);
};
