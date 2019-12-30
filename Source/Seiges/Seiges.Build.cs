// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Seiges : ModuleRules
{
	public Seiges(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        //Mine from UnrealEngine 4.X Scripting Cookbook.
        ///Need this to attach an AIBlackBoard to the AI class.
        PublicDependencyModuleNames.AddRange(new string[] { "AIModule","GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
