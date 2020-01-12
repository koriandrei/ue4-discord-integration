// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordIntegrationLibrary.h"

#include "discord/types.h"

#include "discord/core.h"

#include "DiscordHelpers.h"

#include "discord/activity_manager.h"
#include "DiscordObject.h"

UUpdateDiscordActivity* UDiscordIntegrationLibrary::UpdateActivity(const FDiscordActivity& Activity, UObject* Context)
{
	UUpdateDiscordActivity* AsyncNode = NewObject<UUpdateDiscordActivity>();

	UDiscordObject::Get(Context)->GetCore()->ActivityManager().UpdateActivity(Cast(Activity), [WeakNode = MakeWeakObjectPtr(AsyncNode)](discord::Result Result) { if (ensureAlways(WeakNode.IsValid())) {
		WeakNode->OnActivityUpdated(Cast(Result));
	} });

	AsyncNode->Context = Context;
	
	return AsyncNode;
}

int UDiscordIntegrationLibrary::GetFriendsCount(const UObject* Context)
{
	int32 Count = 0;
	//ensureAlwaysMsgf(ret == discord::Result::Ok, TEXT("%d"), static_cast<int>(ret));
	return Count;
}

UUpdateDiscordActivity* UUpdateDiscordActivity::UpdateActivityHack(const FDiscordActivity& Activity, UObject* Context)
{
	return UDiscordIntegrationLibrary::UpdateActivity(Activity, Context);
}

void UUpdateDiscordActivity::Activate()
{
	Super::Activate();

	//auto rel = UDiscordObject::Get(this)->GetCore()->RelationshipManager();

	UDiscordObject::Get(Context)->GetCore()->RelationshipManager().OnRefresh.Connect([WeakContext = MakeWeakObjectPtr(Context), WeakThis = MakeWeakObjectPtr(this)]() {
		//WeakThis->bIsCountAvailable = true;
	int count = -1;
	
	auto ret = UDiscordObject::Get(WeakContext.Get())->GetCore()->RelationshipManager().Count(&count);

	if (ret != discord::Result::Ok)
	{
		UE_LOG(LogTemp, Warning, TEXT("Relationship %d"), static_cast<int>(ret));
	}
	
	WeakThis->OnUpdated.Broadcast(ret == discord::Result::Ok ? EDiscordActivityUpdateResult::Ok : EDiscordActivityUpdateResult::Unidentified, count); });

		//auto ret = UDiscordObject::Get(const_cast<UObject*>(Context))->GetCore()->RelationshipManager().OnRefresh.Connect([Weak]).Count(&Count);
}
