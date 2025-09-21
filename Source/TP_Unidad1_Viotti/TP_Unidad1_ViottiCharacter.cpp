// Incluye el archivo de cabecera de la clase del personaje "TP_Unidad1_ViottiCharacter"
#include "TP_Unidad1_ViottiCharacter.h"

// Incluye definiciones relacionadas con jugadores locales
#include "Engine/LocalPlayer.h"

// Incluye la clase de cámara usada para crear la cámara de seguimiento
#include "Camera/CameraComponent.h"

// Incluye la clase del componente cápsula, usada para las colisiones del personaje
#include "Components/CapsuleComponent.h"

// Incluye el sistema de movimiento de personajes (caminata, salto, etc.)
#include "GameFramework/CharacterMovementComponent.h"

// Incluye el componente "Spring Arm" que permite alejar/acercar la cámara con colisiones
#include "GameFramework/SpringArmComponent.h"

// Incluye la clase de controlador, necesaria para obtener y manejar input
#include "GameFramework/Controller.h"

// Incluye la clase para manejar inputs mejorados (Enhanced Input)
#include "EnhancedInputComponent.h"

// Incluye los subsistemas de Enhanced Input (manejan bindings e inputs avanzados)
#include "EnhancedInputSubsystems.h"

// Incluye el tipo de datos InputActionValue (para inputs como Vector2D, bool, float, etc.)
#include "InputActionValue.h"

// Incluye el archivo principal del proyecto, con logs y definiciones globales
#include "TP_Unidad1_Viotti.h"


// Constructor de la clase del personaje
ATP_Unidad1_ViottiCharacter::ATP_Unidad1_ViottiCharacter()
{
	// Configura el tamaño de la cápsula de colisión del personaje
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Indica que el personaje no debe rotar al rotar el controlador (la rotación solo afecta a la cámara)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configura el movimiento del personaje para que rote en dirección al movimiento
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Define la velocidad de rotación al moverse
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Define parámetros básicos de movimiento y salto del personaje
	GetCharacterMovement()->JumpZVelocity = 500.f;               // Fuerza del salto
	GetCharacterMovement()->AirControl = 0.35f;                  // Control en el aire
	GetCharacterMovement()->MaxWalkSpeed = 500.f;                // Velocidad máxima caminando
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;           // Velocidad mínima al usar joystick
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // Frenado al caminar
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;// Frenado al caer

	// Crea un "Spring Arm" para alejar la cámara y ajustarla en colisiones
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// Adjunta el brazo de cámara al componente raíz
	CameraBoom->SetupAttachment(RootComponent);
	// Define la distancia de la cámara al personaje
	CameraBoom->TargetArmLength = 400.0f;
	// Permite que la cámara siga la rotación del controlador
	CameraBoom->bUsePawnControlRotation = true;

	// Crea la cámara de seguimiento
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Adjunta la cámara al final del brazo de cámara
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// La cámara no rota con el personaje, solo con el controlador
	FollowCamera->bUsePawnControlRotation = false;

	// Nota: El esqueleto y el anim blueprint del mesh se asignan en el Blueprint derivado
}


// Configura los inputs del jugador
void ATP_Unidad1_ViottiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Configura las acciones de input
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Acción de salto: comienza al presionar la tecla
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		// Acción de salto: termina al soltar la tecla
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Saluda a Kent (Tecla M)
		EnhancedInputComponent->BindAction(ShowMessageAction, ETriggerEvent::Started, this, &ATP_Unidad1_ViottiCharacter::DoShowMessage);

		// Achica al personaje (Tecla C)
		EnhancedInputComponent->BindAction(SizeAction, ETriggerEvent::Started, this, &ATP_Unidad1_ViottiCharacter::DoChangeSize);

		// Correr (W + Shift izquierdo)
		EnhancedInputComponent->BindAction(CorrerAction, ETriggerEvent::Started, this, &ATP_Unidad1_ViottiCharacter::Correr);
		


		// Acción de movimiento, recibe un Vector2D (eje X/Y)
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP_Unidad1_ViottiCharacter::Move);
		// Acción de mirar con el mouse
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATP_Unidad1_ViottiCharacter::Look);

		// Acción de mirar (ejemplo duplicado con otro InputAction configurado)
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATP_Unidad1_ViottiCharacter::Look);
	}
	else
	{
		// Muestra un error si no encuentra un componente de Enhanced Input
		UE_LOG(LogTP_Unidad1_Viotti, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


// Función que procesa el movimiento del jugador
void ATP_Unidad1_ViottiCharacter::Move(const FInputActionValue& Value)
{
	// El input es un Vector2D (X = izquierda/derecha, Y = adelante/atrás)
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Redirige el movimiento a la función DoMove
	DoMove(MovementVector.X, MovementVector.Y);
}


// Función que procesa la rotación de la cámara/jugador
void ATP_Unidad1_ViottiCharacter::Look(const FInputActionValue& Value)
{
	// El input es un Vector2D (X = giro horizontal, Y = giro vertical)
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// Redirige la mirada a la función DoLook
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}


// Función auxiliar para mover al personaje
void ATP_Unidad1_ViottiCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr) // Comprueba si hay un controlador activo
	{
		// Obtiene la rotación actual del controlador
		const FRotator Rotation = GetController()->GetControlRotation();
		// Solo usa el eje Yaw (horizontal)
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Calcula el vector de dirección hacia adelante
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Calcula el vector de dirección hacia la derecha
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Aplica el movimiento hacia adelante
		AddMovementInput(ForwardDirection, Forward);
		// Aplica el movimiento hacia la derecha
		AddMovementInput(RightDirection, Right);
	}
}


// Función auxiliar para controlar la cámara
void ATP_Unidad1_ViottiCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr) // Comprueba si hay un controlador activo
	{
		// Aplica la rotación horizontal al controlador
		AddControllerYawInput(Yaw);
		// Aplica la rotación vertical al controlador
		AddControllerPitchInput(Pitch);
	}
}


// Función que inicia el salto
void ATP_Unidad1_ViottiCharacter::DoJumpStart()
{
	// Señala al personaje que debe saltar
	Jump();
}


// Función que detiene el salto
void ATP_Unidad1_ViottiCharacter::DoJumpEnd()
{
	// Señala al personaje que debe dejar de saltar
	StopJumping();
}

void ATP_Unidad1_ViottiCharacter::DoShowMessage()
{
	if (GEngine) 
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Purple, 
			"Hola Kent");
	}
}

void ATP_Unidad1_ViottiCharacter::DoChangeSize()
{
	
	if (bEstaAchicado)
	{
		// Vuelve al tamaño normal
		SetActorScale3D(FVector(1.f, 1.f, 1.f));
		
	}
	else
	{
		// Se achica a la mitad
		SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
		
	}

	// Cambia el estado
	bEstaAchicado = !bEstaAchicado;
}

void ATP_Unidad1_ViottiCharacter::Correr()
{
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
}



