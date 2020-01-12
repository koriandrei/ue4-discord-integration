#include "DiscordObject.h"

#include "DiscordSettings.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "Engine.h"

#include "DiscordIntegration.h"
#include "DiscordHelpers.h"

static discord::ClientId GetClientId(const UObject* Context)
{
	return GetDefault<UDiscordSettings>()->GetClientId();
}

UDiscordObject* UDiscordObject::Get(UObject* Context)
{
	UGameInstance* GameInstance = Context->GetWorld()->GetGameInstance();

	UDiscordObject* DefaultObject = GetMutableDefault<UDiscordObject>();

	if (UDiscordObject** Instance = DefaultObject->Objects.Find(GameInstance))
	{
		return *Instance;
	}

	return DefaultObject->Objects.Emplace(GameInstance, Create(Context));
}

void UDiscordObject::Update()
{
	UE_LOG(LogDiscordIntegration, Verbose, TEXT("Running Discord callbacks..."));

	Core->RunCallbacks();
}

void UDiscordObject::LogDiscordMessage(EUeDiscordLogLevel InLogLevel, const FString& Message)
{
	switch (InLogLevel)
	{
	case EUeDiscordLogLevel::Debug:
		UE_LOG(LogDiscordIntegration, Verbose, TEXT("Discord SDK: \"%s\""), *Message);
		break;
	case EUeDiscordLogLevel::Log:
		UE_LOG(LogDiscordIntegration, Log, TEXT("Discord SDK: \"%s\""), *Message);
		break;
	case EUeDiscordLogLevel::Warning:
		UE_LOG(LogDiscordIntegration, Warning, TEXT("Discord SDK: \"%s\""), *Message);
		break;
	case EUeDiscordLogLevel::Error:
		UE_LOG(LogDiscordIntegration, Error, TEXT("Discord SDK: \"%s\""), *Message);
		break;
	default:
		ensureAlways(false);
	}

	//UE_LOG(LogDiscordIntegration, )
}

UDiscordObject* UDiscordObject::Create(UObject* Context)
{
	UDiscordObject* Instance = NewObject<UDiscordObject>(Context);

	Instance->Initialize();

	return Instance;
}

void UDiscordObject::BeginDestroy()
{
	

	Super::BeginDestroy();
}

void UDiscordObject::Initialize()
{
#if UE_EDITOR
	if (GetWorld()->IsPlayInEditor())
	{
		static const TCHAR* const InstanceIdEnvVarName = TEXT("DISCORD_INSTANCE_ID");

		const int InstanceId = GetWorld()->GetGameInstance()->GetWorldContext()->PIEInstance;

		if (InstanceId > 0)
		{
			const FString InstanceIdStringS = FString::FromInt(InstanceId - 1);

			const TCHAR* const InstanceIdString = *InstanceIdStringS;

			FPlatformMisc::SetEnvironmentVar(InstanceIdEnvVarName, InstanceIdString);

			UE_LOG(LogDiscordIntegration, Log, TEXT("Setting environment variable \"%s\" to \"%s\" for Discord to hook up to"), InstanceIdEnvVarName, InstanceIdString);
		}
	}
#endif

	const uint64 ClientId = GetClientId(this);

	UE_LOG(LogDiscordIntegration, Log, TEXT("Initializing Discord integration with client ID %llu"), ClientId);

	const discord::Result& Result = discord::Core::Create(ClientId, static_cast<uint64_t>(discord::CreateFlags::Default), &Core);

	if (Result == discord::Result::Ok)
	{
		UE_LOG(LogDiscordIntegration, Log, TEXT("Discord integration initialized successfully"));
	}
	else
	{
		UE_LOG(LogDiscordIntegration, Error, TEXT("Error when initializing Discord, error code %d"), static_cast<int32>(Result));

		return;
	}

	FTimerHandle Dummy;

	GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(Dummy, this, &UDiscordObject::Update, 0.01f, true);

	Core->SetLogHook(discord::LogLevel::Debug, [WeakThis = MakeWeakObjectPtr(this)](discord::LogLevel InLogLevel, const char* Message)
	{
		if (ensureAlways(WeakThis.IsValid()))
		{
			WeakThis->LogDiscordMessage(Cast(InLogLevel), FString(UTF8_TO_TCHAR(Message)));
		}
	});
}

discord::Core* UDiscordObject::GetCore()
{
	return Core;
}

