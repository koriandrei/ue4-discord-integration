#pragma once

#include "Engine/DeveloperSettings.h"

#include "DiscordSettings.generated.h"

UCLASS(Config = Game, DefaultConfig)
class UDiscordSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:

	static int64 GetClientId();

private:

	UPROPERTY(EditDefaultsOnly, Config)
	int64 ClientId;
};

inline int64 UDiscordSettings::GetClientId()
{
	return GetDefault<UDiscordSettings>()->ClientId;
}
