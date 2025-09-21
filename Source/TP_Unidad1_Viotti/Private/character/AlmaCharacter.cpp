// Fill out your copyright notice in the Description page of Project Settings.


#include "character/AlmaCharacter.h"
#include "Components/SphereComponent.h" 
//#include "AlmaCharacter.h"

// Sets default values
AAlmaCharacter::AAlmaCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyName = TEXT("Actor");
	Distance = 100;


	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh")); 
	SphereMesh->SetupAttachment(RootComponent);

}


void AAlmaCharacter::MostrarMensaje()
{
	if (GEngine) // GEngine si existe muestro mensaje
	{
		GEngine->AddOnScreenDebugMessage(
			-1,//Esto es el key
			5.f,// esto es el tiempo que va permanecer
			FColor::Purple, // esto es el color
			MyName); // y esto es el mensaje a mostrar en pantalla
	}

}

int AAlmaCharacter::GetHealth()
{
	return Health;
}

void AAlmaCharacter::MostrarDistancia_Implementation()
{
	if (GEngine) // GEngine si existe muestro mensaje
	{
		GEngine->AddOnScreenDebugMessage(
			-1,//Esto es el key
			5.f,// esto es el tiempo que va permanecer
			FColor::Purple, // esto es el color
			FString::FromInt(Distance)); // y esto es el mensaje a mostrar en pantalla
	}
}

// Called when the game starts or when spawned
void AAlmaCharacter::BeginPlay()
{
	Super::BeginPlay();

	MostrarDistancia();	
	
}

// Called every frame
void AAlmaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

