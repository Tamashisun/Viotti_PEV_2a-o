// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlmaCharacter.generated.h"

class USphereComponent; 
class UStaticMeshComponent; 

UCLASS()
class TP_UNIDAD1_VIOTTI_API AAlmaCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlmaCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	int Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta=(ClampMin="0.0", ClampMax="1000", UIMin="0.0", UIMax="1000", ToolTip="Potencia de ataque del jugador"));
	int Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0", ClampMax = "1000", UIMin = "0.0", UIMax = "1000", ToolTip = "Potencia de ataque del jugador"));
	int Distance;
	  
	UPROPERTY(EditAnywhere)
	FString MyName;

	UFUNCTION(BlueprintCallable)
	void MostrarMensaje();

	UFUNCTION(BlueprintPure)
	int GetHealth();

	UFUNCTION(BlueprintNativeEvent)
	void MostrarDistancia();
	virtual void MostrarDistancia_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent>SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent>SphereMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

};
