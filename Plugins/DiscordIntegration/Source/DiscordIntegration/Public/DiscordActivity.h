#pragma once

#include "CoreMinimal.h"

#include "DiscordActivity.generated.h"

USTRUCT(BlueprintType)
struct DISCORDINTEGRATION_API FDiscordActivity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString State;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString Details;
};

USTRUCT(BlueprintType)
struct DISCORDINTEGRATION_API FDiscordFriend
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FString Name;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FString State;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FString Details;
};

