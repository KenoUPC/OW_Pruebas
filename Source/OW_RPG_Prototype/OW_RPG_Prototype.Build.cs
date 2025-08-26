// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OW_RPG_Prototype : ModuleRules
{
	public OW_RPG_Prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"OW_RPG_Prototype",
			"OW_RPG_Prototype/Variant_Platforming",
			"OW_RPG_Prototype/Variant_Combat",
			"OW_RPG_Prototype/Variant_Combat/AI",
			"OW_RPG_Prototype/Variant_SideScrolling",
			"OW_RPG_Prototype/Variant_SideScrolling/Gameplay",
			"OW_RPG_Prototype/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
