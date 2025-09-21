

// Directiva para evitar que se incluya el archivo más de una vez
#pragma once

// Incluye las definiciones básicas del motor de Unreal
#include "CoreMinimal.h"

// Incluye la clase base ACharacter, de la cual heredará nuestro personaje
#include "GameFramework/Character.h"

// Incluye utilidades de logging (para imprimir mensajes en consola)
#include "Logging/LogMacros.h"

// Macro que genera código necesario para integración de UCLASS, UFUNCTION, etc.
#include "TP_Unidad1_ViottiCharacter.generated.h"

// Declaración anticipada de clases usadas en este header (para optimizar compilación)
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

// Declara una categoría de log personalizada para este personaje
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 * Clase de personaje controlable por el jugador en tercera persona
 * Implementa una cámara que orbita alrededor del personaje
 */
UCLASS(abstract) // Indica que la clase es abstracta (no instanciable directamente)
class ATP_Unidad1_ViottiCharacter : public ACharacter
{
	GENERATED_BODY() // Macro que genera código boilerplate para UObject y ACharacter

		// Componente que actúa como "brazo de cámara", posicionando la cámara detrás del personaje
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Componente de cámara que sigue al personaje
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:

	// Acción de input para saltar
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	// Acción de input para moverse
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// Acción de input para mirar (ejemplo: con joystick)
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	// Acción de input para mirar con el mouse
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

	// Función llamada cuando se recibe input de movimiento
	void Move(const FInputActionValue& Value);

	// Función llamada cuando se recibe input de mirada
	void Look(const FInputActionValue& Value);

public:

	// Maneja inputs de movimiento (se puede llamar desde código o interfaz Blueprint)
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	// Maneja inputs de cámara/mirada (código o Blueprint)
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	// Maneja el inicio del salto (código o Blueprint)
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	// Maneja el final del salto (código o Blueprint)
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
