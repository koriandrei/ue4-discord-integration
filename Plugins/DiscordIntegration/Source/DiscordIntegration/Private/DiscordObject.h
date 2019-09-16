#pragma once

#include "Object.h"

#include "types.h"

#include "DiscordObject.generated.h"

UCLASS()
class UDiscordObject : public UObject
{
	GENERATED_BODY()

public:

	static UDiscordObject* Get(UObject* Context);

	void Initialize();

private:

	static UDiscordObject* Create(UObject* Context);

	UPROPERTY()
	TMap<class UGameInstance*, UDiscordObject*> Objects;

	discord::Core* Core = nullptr;
};
