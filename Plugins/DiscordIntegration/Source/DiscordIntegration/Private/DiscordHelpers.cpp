#pragma once

#include "DiscordHelpers.h"

#include "DiscordSettings.h"

#include "DiscordObject.h"

#include "DiscordIntegration.h"

static char* StringToUtf8(const FString& String)
{
	return TCHAR_TO_UTF8(*String);
}

discord::Activity Cast(const FDiscordActivity& DiscordActivity)
{
	discord::Activity Activity;

	Activity.SetName(StringToUtf8(DiscordActivity.Name));
	Activity.SetState(StringToUtf8(DiscordActivity.State));
	Activity.SetDetails(StringToUtf8(DiscordActivity.Details));
	Activity.SetType(discord::ActivityType::Playing);

	return Activity;
}

EDiscordActivityUpdateResult Cast(const discord::Result DiscordActivity)
{
	switch (DiscordActivity)
	{
	case discord::Result::Ok:
		return EDiscordActivityUpdateResult::Ok;
	}

	UE_LOG(LogDiscordIntegration, Warning, TEXT("Received unexpected result for ActivityUpdate: %d"), static_cast<int>(DiscordActivity));

	return EDiscordActivityUpdateResult::Unidentified;
}

EUeDiscordLogLevel Cast(const discord::LogLevel InLogLevel)
{
	switch (InLogLevel)
	{
	case discord::LogLevel::Debug:
		return EUeDiscordLogLevel::Debug;
	case discord::LogLevel::Warn:
		return EUeDiscordLogLevel::Warning;
	case discord::LogLevel::Error:
		return EUeDiscordLogLevel::Error;
	case discord::LogLevel::Info:
		return EUeDiscordLogLevel::Log;
	}

	ensureAlways(false);
	return EUeDiscordLogLevel::Error;
}

discord::Core* GetCore(UObject* Context)
{
	return UDiscordObject::Get(Context)->GetCore();
}

