// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLibrary.h"
#include "RuntimeMeshComponent.h"
#include "ProcMeshActor.generated.h"


UCLASS()
class CITY_API AProcMeshActor : public AActor
{
	GENERATED_BODY()
	
public:

	static unsigned int workersWorking;
	GenerationMode generationMode;
	unsigned int maxThreads = 10000;
	// Sets default values for this actor's properties
	AProcMeshActor();
	~AProcMeshActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URuntimeMeshComponent* RuntimeMeshComponent;

	UFUNCTION(BlueprintCallable, Category = "Generation")
	bool buildMaterialPolygons(TArray<FMaterialPolygon> pols, FVector offset);

	bool clearMeshes(bool fullReplacement);

	UFUNCTION(BlueprintCallable, Category = "Settings")
		void init(GenerationMode generationMode_in) {
		generationMode = generationMode_in;
		switch (generationMode) {
		case GenerationMode::complete: maxThreads = 1000; break;
		case GenerationMode::procedural_aggressive: maxThreads = 1000; break;
		case GenerationMode::procedural_relaxed: maxThreads = 1; break;
		}
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* exteriorMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* sndExteriorMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* windowMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* windowFrameMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* occlusionWindowMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* interiorMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* floorMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* roofMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* greenMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* concreteMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* roadMiddleMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		UMaterial* asphaltMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = appearance, meta = (AllowPrivateAccess = "true"))
		float texScaleMultiplier = 1.0f;

	//TArray<
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool buildPolygons(TArray<FPolygon> &pols, FVector offset, URuntimeMeshProviderStatic* mesh, UMaterialInterface *mat);


	bool wantsToWork = false;
	bool isWorking = false;
	int currentlyWorkingArray = 0;




	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* exteriorMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* interiorMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* windowMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* occlusionWindowMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* windowFrameMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* sndExteriorMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* floorMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* roofMesh;

	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* greenMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* concreteMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* roadMiddleMesh;
	UPROPERTY(VisibleAnywhere, Category = Meshes)
		URuntimeMeshProviderStatic* asphaltMesh;

	TArray<URuntimeMeshProviderStatic*> components;
	TArray<UMaterialInterface*> materials;
	TArray<TArray<FPolygon>> polygons;

	int currIndex = 1;
	
	
};
