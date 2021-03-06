// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CorePortal.h"
#include "SimplePortal.generated.h"

class USceneCaptureComponent2D;
class UCanvasRenderTarget2D;
class ACorePlayerController;
class UMaterialParameterCollection;

UCLASS()
class INSIDER_API ASimplePortal : public ACorePortal
{
	GENERATED_BODY()
	
public:	

	ASimplePortal();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Simple Portal")
	void SetIsOpen(bool Value);

	UFUNCTION(BlueprintCallable, Category = "Simple Portal")
	void SetIsRenderEnable(bool Value);

	UFUNCTION(BlueprintCallable, Category = "Simple Portal")
	void SetMeshSurfaceSize(FVector Value);

	UFUNCTION(BlueprintCallable, Category = "Simple Portal")
	void SetRenderMipLevels(int Value);

	UFUNCTION(BlueprintCallable, Category = "Simple Portal")
	void SetRenderMipScaledownSpeed(float Value);

	UFUNCTION()
	void PortalBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PortalMeshFrame")
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SceneCapture")
	USceneCaptureComponent2D* SceneCapture;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RecSceneCapture")
	USceneCaptureComponent2D* RecSceneCapture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParamCollection")
	UMaterialParameterCollection* ParamCollection;

private:

	// default param

	bool bOpen = true;
	bool bRenderEnable = true;
	bool bCaptureFrame = false, bCaptureRecFrame = false;
	FVector MeshSurfaceSize = FVector(500, 500, 500);
	float ClipPlaneOffset = -30;

	//render mip

	int RenderMipLevels = 15;
	float RenderMipScaledownSpeed = 0.1;
	int CurrentMipLevel = 0;

	UPROPERTY()
	TArray<UCanvasRenderTarget2D*> RenderTargetArray;

	UPROPERTY()
	UCanvasRenderTarget2D*	PortalTexture;

	UPROPERTY()
	ACorePlayerController* CorePlayerController;

	UPROPERTY()
	ASimplePortal* TargetPortal;

	// Construct Init Params

	void InitMeshes();
	void InitSceneCapture();
	void InitRecSceneCapture();

	//Mips funct

	void GenerateRenderTargetsByMipMap();
	void GeneratePortalTexture(int Index);
	void SetRenderTargetsWithMip(int Index);
	int CalcRenderMip();

	void Render();
	void IsUpdateSceneCapture();
	bool PlayerOverlapPortal();
	FVector UpdateSceneCaptureLocation(USceneCaptureComponent2D* SceneCapture, FVector Location);
	FRotator UpdateSceneCaptureRotation(USceneCaptureComponent2D* SceneCapture, FRotator Rotation);
	
	// Update Location, Rotation, Clip Plane for SceneCapture and RecSceneCapture

	void SetSceneCapturesParams();
	void SetClipPlane(USceneCaptureComponent2D* SceneCapture);

	void SetSceneCapturesLocationAndRotation();


	// Calculate Projection Matrix for SceneCapture and RecSceneCapture

	void CalcRecProjectionMatrix();
	void CalcProjectionMatrix();
	void CalcScaleAndOffset(float ScreenRadius, FVector2D PortalScreenSpacePosition, float FinalPortalScale, float &OutScale, FVector2D &OutOffset);

	// Update Captures 

	void UpdateSceneCapture();
	void UpdateRecSceneCapture();
	void UpdateSceneCaptureWithoutRec();

	//
	void SetMaterialParams(int TextureID, float Subscale, bool CustomMatrix, bool Recurse, float Invscale, FVector2D Offset, FVector TargetPosition);

	FVector2D FinalPortalOffset, RecFinalPortalOffset;
	float FinalPortalScale = 1, RecFinalPortalScale = 0;


	float GetProjectedScreenRadius(FVector Position);
	float ScreenRadius, RecScreenRadius;


};
