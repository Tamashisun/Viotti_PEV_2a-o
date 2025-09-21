

// Directiva para evitar que se incluya el archivo m�s de una vez
#pragma once

// Incluye las definiciones b�sicas del motor de Unreal
#include "CoreMinimal.h"

// Incluye la clase base ACharacter, de la cual heredar� nuestro personaje
#include "GameFramework/Character.h"

// Incluye utilidades de logging (para imprimir mensajes en consola)
#include "Logging/LogMacros.h"

// Macro que genera c�digo necesario para integraci�n de UCLASS, UFUNCTION, etc.
#include "TP_Unidad1_ViottiCharacter.generated.h"

// Declaraci�n anticipada de clases usadas en este header (para optimizar compilaci�n)
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

// Declara una categor�a de log personalizada para este personaje
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 * Clase de personaje controlable por el jugador en tercera persona
 * Implementa una c�mara que orbita alrededor del personaje
 */
UCLASS(abstract) // Indica que la clase es abstracta (no instanciable directamente)
class ATP_Unidad1_ViottiCharacter : public ACharacter
{
	GENERATED_BODY() // Macro que genera c�digo boilerplate para UObject y ACharacter

		// Componente que act�a como "brazo de c�mara", posicionando la c�mara detr�s del personaje
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Componente de c�mara que sigue al personaje
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:

	// Acci�n de input para saltar
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	// Acci�n de input para moverse
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// Acci�n de input para mirar (ejemplo: con joystick)
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	// Acci�n de input para mirar con el mouse
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ShowMessageAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SizeAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CorrerAction;


public:

	// Constructor de la clase del personaje
	ATP_Unidad1_ViottiCharacter();

	bool bEstaAchicado = false;

protected:

	// Inicializa los bindings de input (asigna acciones a funciones)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Funci�n llamada cuando se recibe input de movimiento
	void Move(const FInputActionValue& Value);

	// Funci�n llamada cuando se recibe input de mirada
	void Look(const FInputActionValue& Value);

public:

	// Maneja inputs de movimiento (se puede llamar desde c�digo o interfaz Blueprint)
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	// Maneja inputs de c�mara/mirada (c�digo o Blueprint)
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	// Maneja el inicio del salto (c�digo o Blueprint)
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	// Maneja el final del salto (c�digo o Blueprint)
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoShowMessage();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoChangeSize();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void Correr();
	




public:

	// Devuelve el puntero al componente CameraBoom
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Devuelve el puntero al componente FollowCamera
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
