// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordIntegrationLibrary.h"

#include "discord/types.h"

#include "discord/core.h"

#include "DiscordHelpers.h"

#include "discord/activity_manager.h"
#include "DiscordObject.h"

#include "DiscordIntegration.h"

template <class TResult>
static void LogResult(TResult Result)
{
	if (Result != TResult::Ok)
	{
		UE_LOG(LogDiscordIntegration, Error, TEXT("Error code %d"), static_cast<int>(Result));
	}
	else
	{
		UE_LOG(LogDiscordIntegration, Log, TEXT("Handled successfully"));
	}
}

template <class TResult>
static std::function<void(discord::Result)> ConvertHandler(TFunction<void(TResult)> TypedHandler)
{
	auto ConvertedHandler = [TypedHandler](discord::Result DiscordResult)
	{
		TypedHandler(Cast(DiscordResult));
	};

	return ConvertedHandler;
}

void UDiscordIntegrationLibrary::UpdateActivity(const FDiscordActivity& Activity, UObject* Context)
{
	return UpdateActivity(Activity, LogResult<EDiscordActivityUpdateResult>, Context);
}

void UDiscordIntegrationLibrary::UpdateActivity(const FDiscordActivity& Activity, TFunction<void(EDiscordActivityUpdateResult)> Callback, UObject* Context)
{
	UDiscordObject::GetCore(Context)->ActivityManager().UpdateActivity(
		Cast(Activity),
		ConvertHandler(Callback)
	);
}

int UDiscordIntegrationLibrary::GetFriendsCount(const UObject* Context)
{
	int32 Count = 0;
	//ensureAlwaysMsgf(ret == discord::Result::Ok, TEXT("%d"), static_cast<int>(ret));
	return Count;
}

UUpdateDiscordActivity* UUpdateDiscordActivity::UpdateActivity(const FDiscordActivity& Activity, UObject* Context)
{
	UUpdateDiscordActivity* AsyncNode = NewObject<UUpdateDiscordActivity>();

	auto Callback = [WeakNode = MakeWeakObjectPtr(AsyncNode)](EDiscordActivityUpdateResult Result)
	{
		if (ensureAlways(WeakNode.IsValid()))
		{
			WeakNode->OnActivityUpdated(Result);
		}
	};

	UDiscordIntegrationLibrary::UpdateActivity(Activity, Callback, Context);
	
	return AsyncNode;
}

void UUpdateDiscordActivity::OnActivityUpdated(EDiscordActivityUpdateResult Result)
{
	OnUpdated.Broadcast(Result);

	SetReadyToDestroy();
}

void UUpdateDiscordActivity::Activate()
{
	Super::Activate();

	//auto rel = UDiscordObject::Get(this)->GetCore()->RelationshipManager();

	//UDiscordObject::Get(Context)->GetCore()->RelationshipManager().OnRefresh.Connect([WeakContext = MakeWeakObjectPtr(Context), WeakThis = MakeWeakObjectPtr(this)]() {
	//	//WeakThis->bIsCountAvailable = true;
	//int count = -1;
	//
	//auto ret = UDiscordObject::Get(WeakContext.Get())->GetCore()->RelationshipManager().Count(&count);

	//if (ret != discord::Result::Ok)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Relationship %d"), static_cast<int>(ret));
	//}
	//
	//WeakThis->OnUpdated.Broadcast(ret == discord::Result::Ok ? EDiscordActivityUpdateResult::Ok : EDiscordActivityUpdateResult::Unidentified, count); });

		//auto ret = UDiscordObject::Get(const_cast<UObject*>(Context))->GetCore()->RelationshipManager().OnRefresh.Connect([Weak]).Count(&Count);
}
