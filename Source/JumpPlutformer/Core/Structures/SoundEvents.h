// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/AssetPtr.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "SoundEvents.generated.h"


 //
 // Additional structs for FSoundEvents
 //

USTRUCT(BlueprintType)
struct FSound2D
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "2D Sound")
	TAssetPtr<USoundBase> Sound2D;

	UPROPERTY(BlueprintReadWrite, Category = "2D Sound")
	float DelayBeforePlaySec;
};


USTRUCT(BlueprintType)
struct FSound3D
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "3D Sound")
	TAssetPtr<USoundBase> Sound3D;

	UPROPERTY(BlueprintReadWrite, Category = "3D Sound")
	AActor* ActorToAttach;

	//Attach to taged actor with skip selected
	UPROPERTY(BlueprintReadWrite, Category = "3D Sound")
	bool bAttachToTagedActor;

	UPROPERTY(BlueprintReadWrite, Category = "3D Sound")
	FName ActorTag;

	UPROPERTY(BlueprintReadWrite, Category = "3D Sound")
	TAssetPtr<USoundAttenuation> SoundAttenuation;

	UPROPERTY(BlueprintReadWrite, Category = "3D Sound")
	float DelayBeforePlaySec;
};


USTRUCT(BlueprintType)
struct FSoundAmbient
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Ambient Sound")
	TAssetPtr<USoundBase> AmbientSound;

	UPROPERTY(BlueprintReadWrite, Category = "AmbientSound")
	TArray<FName> AmbientSoundTags;

	// 0 = instant 
	UPROPERTY(BlueprintReadWrite, Category = "AmbientSound")
	float FadeInDurationSec;

	UPROPERTY(BlueprintReadWrite, Category = "AmbientSound")
	float DelayBeforePlaySec;
};


USTRUCT(BlueprintType)
struct FStopSoundAmbient
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Stop Ambient Sound")
	TArray<FName> TagsAmbientSoundToStop;

	UPROPERTY(BlueprintReadWrite, Category = "Stop Ambient Sound")
	bool bSkipTagsAndStopAll;


	UPROPERTY(BlueprintReadWrite, Category = "Stop Ambient Sound")
	float FadeOutDurationSec;

	UPROPERTY(BlueprintReadWrite, Category = "Stop Ambient Sound")
	float DelayBeforeStopSec;
};


// Main struct
USTRUCT(BlueprintType)
struct FSoundEvents
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Sound Events")
	TArray<FSound2D> PlaySound2D;

	UPROPERTY(BlueprintReadWrite, Category = "Sound Events")
	TArray<FSound3D> PlaySound3D;

	UPROPERTY(BlueprintReadWrite, Category = "Sound Events")
	TArray<FSoundAmbient> PlayAmbientSound;

	UPROPERTY(BlueprintReadWrite, Category = "Sound Events")
	TArray<FStopSoundAmbient> StopAmbientSound;
};
