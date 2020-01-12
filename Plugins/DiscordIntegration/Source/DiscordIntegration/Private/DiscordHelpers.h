#pragma once

#include "DiscordActivity.h"

#include "discord/types.h"

#include "discord/core.h"

#include "DiscordIntegrationLibrary.h"

#include "DiscordObject.h"

discord::Activity Cast(const FDiscordActivity& DiscordActivity);

EDiscordActivityUpdateResult Cast(const discord::Result DiscordActivity);

EUeDiscordLogLevel Cast(const discord::LogLevel InLogLevel);

FDiscordFriend Cast(const discord::Relationship& relationship);

discord::Core* GetCore(class UObject* Context);
