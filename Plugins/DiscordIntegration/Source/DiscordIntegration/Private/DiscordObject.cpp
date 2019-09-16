#include "DiscordObject.h"

#include "DiscordSettings.h"

#include "core.h"

#include "GameInstance.h"

#include "Engine.h"

static ClientId GetClientId(const UObject* Context)
{
	return GetDefault<UDiscordSettings>()->GetClientId();
}

UDiscordObject* UDiscordObject::Get(UObject* Context)
{
	UGameInstance* GameInstance = Context->GetWorld()->GetGameInstance();

	UDiscordObject* DefaultObject = GetDefault<UDiscordObject>();

	if (UDiscordObject** Instance = DefaultObject->Objects.Find(GameInstance))
	{
		return *Instance;
	}

	return DefaultObject->Objects.Emplace(GameInstance, Create(Context));
}

UDiscordObject* UDiscordObject::Create(UObject* Context)
{
	UDiscordObject* Instance = NewObject<UDiscordObject>(Context);

	Instance->Initialize();

	return Instance;
}

void UDiscordObject::Initialize()
{
#if UE_EDITOR
	if (GetWorld()->IsPlayInEditor())
	{
		static const TCHAR const* InstanceIdEnvVarName = "DISCORD_INSTANCE_ID";

		const int InstanceId = GetWorld()->GetGameInstance()->GetWorldContext().PIEInstance;

		const TCHAR const* InstanceIdString = *FString::FromInt(InstanceId);

		FPlatformMisc::SetEnvironmentVar(InstanceIdEnvVarName, InstanceIdString);

		UE_LOG(LogDiscordIntegration, Log, TEXT("Setting environment variable \"%s\" to \"%s\" for Discord to hook up to"), InstanceIdEnvVarName, InstanceIdString);
	}
#endif

	UE_LOG(LogDiscordIntegration, Log, TEXT("Initializing Discord integration"));

	const discord::Result& Result = discord::Core::Create(GetClientId(this), discord::CreateFlags::Default, &Core);

	if (Result == discord::Result::Ok)
	{
		UE_LOG(LogDiscordIntegration, Log, TEXT("Discord integration initialized successfully"));
	}
	else
	{
		UE_LOG(LogDiscordIntegration, Error, TEXT("Error when initializing Discord, error code %d"), static_cast<int32>(Result));
	}
}

