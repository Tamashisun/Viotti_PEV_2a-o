// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP_Unidad1_Viotti : ModuleRules
{
	public TP_Unidad1_Viotti(ReadOnlyTargetRules Target) : base(Target)
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
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TP_Unidad1_Viotti",
			"TP_Unidad1_Viotti/Variant_Platforming",
			"TP_Unidad1_Viotti/Variant_Platforming/Animation",
			"TP_Unidad1_Viotti/Variant_Combat",
			"TP_Unidad1_Viotti/Variant_Combat/AI",
			"TP_Unidad1_Viotti/Variant_Combat/Animation",
			"TP_Unidad1_Viotti/Variant_Combat/Gameplay",
			"TP_Unidad1_Viotti/Variant_Combat/Interfaces",
			"TP_Unidad1_Viotti/Variant_Combat/UI",
			"TP_Unidad1_Viotti/Variant_SideScrolling",
			"TP_Unidad1_Viotti/Variant_SideScrolling/AI",
			"TP_Unidad1_Viotti/Variant_SideScrolling/Gameplay",
			"TP_Unidad1_Viotti/Variant_SideScrolling/Interfaces",
			"TP_Unidad1_Viotti/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
