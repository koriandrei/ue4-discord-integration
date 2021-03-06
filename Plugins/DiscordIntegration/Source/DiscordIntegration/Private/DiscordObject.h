#pragma once

#include "CoreMinimal.h"

#include "discord/types.h"

#include "discord/core.h"

#include "DiscordObject.generated.h"

enum class EUeDiscordLogLevel : uint8
{
	Debug,
	Log,
	Warning,
	Error,
};

UCLASS()
class UDiscordObject : public UObject
{
	GENERATED_BODY()

public:

	static discord::Core* GetCore(UObject* Context);

private:

	static UDiscordObject* Get(UObject* Context);

	void Initialize();

	UFUNCTION()
	void Update();

	void LogDiscordMessage(EUeDiscordLogLevel LogLevel, const FString& Message);

	static UDiscordObject* Create(UObject* Context);

	virtual void BeginDestroy() override;

	UPROPERTY()
	TMap<class UGameInstance*, UDiscordObject*> Objects;

	discord::Core* Core = nullptr;
};
