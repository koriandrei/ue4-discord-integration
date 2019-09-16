#pragma once

#include "Engine/DeveloperSettings.h"

#include "DiscordSettings.generated.h"

UCLASS(Config = Discord, DefaultConfig)
class UDiscordSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	int64 GetClientId();

private:

	UPROPERTY(EditDefaultsOnly)
	int64 ClientId;
};

int64 UDiscordSettings::GetClientId()
{
	return ClientId;
}
