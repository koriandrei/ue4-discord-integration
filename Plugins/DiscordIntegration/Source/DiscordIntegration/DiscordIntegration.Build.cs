// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DiscordIntegration : ModuleRules
{
	public DiscordIntegration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				//PluginDirectory + "/Libraries/cpp/"
				// ... add other private include paths required here ...
			}
			);

        

        string LibraryPath = System.IO.Path.GetFullPath(System.IO.Path.Combine(PluginDirectory, "Libraries/lib/x86_64/discord_game_sdk.dll.lib"));

        PublicAdditionalLibraries.AddRange(
			new string[]{
                LibraryPath
            }
			);

        string LibrariesPath = System.IO.Path.Combine(PluginDirectory, "Libraries/lib/x86_64/");

        //PrivateRuntimeLibraryPaths.Add());

        RuntimeDependencies.Add(PluginDirectory + "/Binaries/Win64/" + "/discord_game_sdk.dll", LibrariesPath + "/discord_game_sdk.dll");

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
