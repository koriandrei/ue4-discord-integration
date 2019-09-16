#pragma once

#include "DiscordHelpers.h"

#include "types.h"

static char* StringToUtf8(const FString* String)
{
	return TCHAR_TO_UTF8(*String);
}

discord::Activity Cast(const FDiscordActivity& DiscordActivity)
{
	discord::Activity Activity;

	Activity.SetName(StringToUtf8(DiscordActivity.Name));

	return Activity;
}

