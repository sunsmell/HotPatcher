// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//project header
#include "FChunkInfo.h"
#include "FPakFileInfo.h"
#include "AssetManager/FAssetDependenciesInfo.h"
#include "FHotPatcherVersion.h"
#include "FlibPakHelper.h"
#include "FExternDirectoryInfo.h"
#include "FExternDirectoryInfo.h"

// engine header
#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include "Templates/SharedPointer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FlibPatchParserHelper.generated.h"

/**
 * 
 */
UCLASS()
class HOTPATCHERRUNTIME_API UFlibPatchParserHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static TArray<FString> GetAvailableMaps(FString GameName, bool IncludeEngineMaps,bool IncludePluginMaps, bool Sorted);
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static FString GetProjectName();
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static FString GetUnrealPakBinary();
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static FString GetUE4CmdBinary();

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool SerializeHotPatcherVersionToString(const FHotPatcherVersion& InVersion, FString& OutResault);
	static bool SerializeHotPatcherVersionToJsonObject(const FHotPatcherVersion& InVersion, TSharedPtr<FJsonObject>& OutJsonObject);
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool DeserializeHotPatcherVersionFromString(const FString& InStringContent, FHotPatcherVersion& OutVersion);
	static bool DeSerializeHotPatcherVersionFromJsonObject(const TSharedPtr<FJsonObject>& InJsonObject, FHotPatcherVersion& OutVersion);


	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool DiffVersionAssets(const FAssetDependenciesInfo& InNewVersion, 
								const FAssetDependenciesInfo& InBaseVersion,
								FAssetDependenciesInfo& OutAddAsset,
								FAssetDependenciesInfo& OutModifyAsset,
								FAssetDependenciesInfo& OutDeleteAsset
		);
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool DiffVersionExFiles(const FHotPatcherVersion& InNewVersion,
			const FHotPatcherVersion& InBaseVersion,
			TArray<FExternAssetFileInfo>& OutAddFiles,
			TArray<FExternAssetFileInfo>& OutModifyFiles,
			TArray<FExternAssetFileInfo>& OutDeleteFiles
		);

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool SerializePakFileInfoToJsonString(const FPakFileInfo& InFileInfo, FString& OutJson);

		static bool SerializePakFileInfoFromJsonObjectToString(const TSharedPtr<FJsonObject>& InFileInfoJsonObject, FString& OutJson);
		static bool SerializePakFileInfoToJsonObject(const FPakFileInfo& InFileInfo, TSharedPtr<FJsonObject>& OutJsonObject);

		static bool SerializePakFileInfoListToJsonObject(const TArray<FPakFileInfo>& InFileInfoList, TSharedPtr<FJsonObject>& OutJsonObject);
		
		static bool SerializePlatformPakInfoToString(const TMap<FString, FPakFileInfo>& InPakFilesMap, FString& OutString);
		static bool SerializePlatformPakInfoToJsonObject(const TMap<FString, FPakFileInfo>& InPakFilesMap, TSharedPtr<FJsonObject>& OutJsonObject);

		static bool SerializeDiffAssetsInfomationToJsonObject(const FAssetDependenciesInfo& InAddAsset,
				const FAssetDependenciesInfo& InModifyAsset,
				const FAssetDependenciesInfo& InDeleteAsset,
				TSharedPtr<FJsonObject>& OutJsonObject);

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static FString SerializeDiffAssetsInfomationToString(const FAssetDependenciesInfo& InAddAsset,
		 									 const FAssetDependenciesInfo& InModifyAsset,
											 const FAssetDependenciesInfo& InDeleteAsset);

		static bool SerializeDiffExternalFilesInfomationToJsonObject(
			const TArray<FExternAssetFileInfo>& InAddFiles,
			const TArray<FExternAssetFileInfo>& InModifyFiles,
			const TArray<FExternAssetFileInfo>& InDeleteFiles,
			TSharedPtr<FJsonObject>& OutJsonObject);

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static FString SerializeDiffExternalFilesInfomationToString(
			const TArray<FExternAssetFileInfo>& InAddFiles,
			const TArray<FExternAssetFileInfo>& InModifyFiles,
			const TArray<FExternAssetFileInfo>& InDeleteFiles);

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool GetPakFileInfo(const FString& InFile,FPakFileInfo& OutFileInfo);

	// Cooked/PLATFORM_NAME/Engine/GlobalShaderCache-*.bin
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static TArray<FString> GetCookedGlobalShaderCacheFiles(const FString& InProjectDir,const FString& InPlatformName);
	// Cooked/PLATFORN_NAME/PROJECT_NAME/AssetRegistry.bin
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool GetCookedAssetRegistryFiles(const FString& InProjectAbsDir, const FString& InProjectName, const FString& InPlatformName,FString& OutFiles);
	// Cooked/PLATFORN_NAME/PROJECT_NAME/Content/ShaderArchive-*.ushaderbytecode
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool GetCookedShaderBytecodeFiles(const FString& InProjectAbsDir, const FString& InProjectName, const FString& InPlatformName,bool InGalobalBytecode,bool InProjectBytecode, TArray<FString>& OutFiles);

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool ConvIniFilesToPakCommands(const FString& InEngineAbsDir, const FString& InProjectAbsDir, const FString& InProjectName, const TArray<FString>& InPakOptions, const TArray<FString>& InIniFiles, TArray<FString>& OutCommands);
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static bool ConvNotAssetFileToPakCommand(const FString& InProjectDir,const FString& InPlatformName, const TArray<FString>& InPakOptions,const FString& InCookedFile,FString& OutCommand);
	static bool ConvNotAssetFileToExFile(const FString& InProjectDir, const FString& InPlatformName, const FString& InCookedFile, FExternAssetFileInfo& OutExFile);
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
	static FString HashStringWithSHA1(const FString &InString);

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
		static TArray<FString> GetIniConfigs(const FString& InSearchDir, const FString& InPlatformName);
	// return abslute path
	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
	static TArray<FString> GetProjectIniFiles(const FString& InProjectDir,const FString& InPlatformName);

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
	static TArray<FString> GetEngineConfigs(const FString& InPlatformName);

	UFUNCTION(BlueprintCallable, Category = "HotPatcher|Flib")
	static TArray<FString> GetEnabledPluginConfigs(const FString& InPlatformName);


	static bool SerializeExAssetFileInfoToJsonObject(const FExternAssetFileInfo& InExFileInfo, TSharedPtr<FJsonObject>& OutJsonObject);
	static bool SerializeExDirectoryInfoToJsonObject(const FExternDirectoryInfo& InExDirectoryInfo, TSharedPtr<FJsonObject>& OutJsonObject);
	static bool SerializeSpecifyAssetInfoToJsonObject(const FPatcherSpecifyAsset& InSpecifyAsset, TSharedPtr<FJsonObject>& OutJsonObject);
	static bool DeSerializeSpecifyAssetInfoToJsonObject(const TSharedPtr<FJsonObject>& InJsonObject, FPatcherSpecifyAsset& OutSpecifyAsset);
	// serialize chunk
	static bool SerializeFPakInternalInfoToJsonObject(const FPakInternalInfo& InFPakInternalInfo, TSharedPtr<FJsonObject>& OutJsonObject);
	static bool DeSerializeFPakInternalInfoFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject, FPakInternalInfo& OutFPakInternalInfo);
	static bool SerializeFChunkInfoToJsonObject(const FChunkInfo& InChunkInfo, TSharedPtr<FJsonObject>& OutJsonObject);
	static bool DeSerializeFChunkInfoFromJsonObject(const TSharedPtr<FJsonObject>& InJsonObject, FChunkInfo& OutChunkInfo);

	static TArray<FExternAssetFileInfo> ParserExDirectoryAsExFiles(const TArray<FExternDirectoryInfo>& InExternDirectorys);
	static TArray<FAssetDetail> ParserExFilesInfoAsAssetDetailInfo(const TArray<FExternAssetFileInfo>& InExFiles);

	// get Engine / Project / Plugin ini files
	static TArray<FString> GetIniFilesByPakInternalInfo(const FPakInternalInfo& InPakInternalInfo,const FString& PlatformName);
	// get AssetRegistry.bin / GlobalShaderCache / ShaderBytecode
	static TArray<FString> GetCookedFilesByPakInternalInfo(const FPakInternalInfo& InPakInternalInfo, const FString& PlatformName);

	static TArray<FExternAssetFileInfo> GetInternalFilesAsExFiles(const FPakInternalInfo& InPakInternalInfo, const FString& InPlatformName);
	static TArray<FString> GetPakCommandsFromInternalInfo(const FPakInternalInfo& InPakInternalInfo, const FString& PlatformName,const TArray<FString>& InPakOptions);
	
	static FChunkInfo CombineChunkInfo(const FChunkInfo& R, const FChunkInfo& L);
	static FChunkInfo CombineChunkInfos(const TArray<FChunkInfo>& Chunks);

	static TArray<FString> GetDirectoryPaths(const TArray<FDirectoryPath>& InDirectoryPath);
	
	static TArray<FExternAssetFileInfo> GetExternFilesFromChunk(const FChunkInfo& InChunk, bool bCalcHash = false);
};
