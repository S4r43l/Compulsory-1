// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPawn.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <UObject/ConstructorHelpers.h>
#include "Containers/Array.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMainPawn::AMainPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Spheres.Init(NULL, 9);
	Spheres[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_1"));
	Spheres[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_2"));
	Spheres[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_3"));
	Spheres[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_4"));
	Spheres[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_5"));
	Spheres[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_6"));
	Spheres[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_7"));
	Spheres[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_8"));
	Spheres[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_9"));

	RootComponent = Spheres[4]; //to middle Sphere

	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));

	for(int i{}; i < 9 ; i++)
	{
		if(i!=4) //not to middle Sphere
		{
			Spheres[i]->SetupAttachment((GetRootComponent()));
		}

		//Spheres[i]->SetStaticMesh(MeshComponentAsset.Object);
	}

	//Location of Spheres:
	Spheres[0]->SetRelativeLocation(FVector(200.f, -200.f, 0.f));
	Spheres[1]->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	Spheres[2]->SetRelativeLocation(FVector(200.f, 200.f, 0.f));
	Spheres[3]->SetRelativeLocation(FVector(0.f, -200.f, 0.f));
	Spheres[4]->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Spheres[5]->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	Spheres[6]->SetRelativeLocation(FVector(-200.f, -200.f, 0.f));
	Spheres[7]->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
	Spheres[8]->SetRelativeLocation(FVector(-200.f, 200.f, 0.f));

	//Material(Colors):
	White = CreateDefaultSubobject<UMaterial>(TEXT("M_White"));
	Red = CreateDefaultSubobject<UMaterial>(TEXT("M_Red"));
	Blue = CreateDefaultSubobject<UMaterial>(TEXT("M_Blue"));

	//SpringArm:
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment((GetRootComponent()));
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 600.f;

	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); //attach to SpringArm

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	TurnCount = 0;
	GameOver = false;
	SphereStatus.Init(NULL, 9);
	SphereB.Init(NULL, 9);
	SphereR.Init(NULL, 9);
}

// Called when the game starts or when spawned
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();

	//Make Spheres White at start
	for (int i{}; i < 9; i++)
	{
		Spheres[i]->SetMaterial(0, White); 
	}

}

// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("1", IE_Pressed, this, &AMainPawn::OnePressed);
	PlayerInputComponent->BindAction("2", IE_Pressed, this, &AMainPawn::TwoPressed);
	PlayerInputComponent->BindAction("3", IE_Pressed, this, &AMainPawn::ThreePressed);
	PlayerInputComponent->BindAction("4", IE_Pressed, this, &AMainPawn::FourPressed);
	PlayerInputComponent->BindAction("5", IE_Pressed, this, &AMainPawn::FivePressed);
	PlayerInputComponent->BindAction("6", IE_Pressed, this, &AMainPawn::SixPressed);
	PlayerInputComponent->BindAction("7", IE_Pressed, this, &AMainPawn::SevenPressed);
	PlayerInputComponent->BindAction("8", IE_Pressed, this, &AMainPawn::EightPressed);
	PlayerInputComponent->BindAction("9", IE_Pressed, this, &AMainPawn::NinePressed);

}



void AMainPawn::OnePressed()
{
	TurnController(0);
}

void AMainPawn::TwoPressed()
{
	TurnController(1);
}

void AMainPawn::ThreePressed()
{
	TurnController(2);
}

void AMainPawn::FourPressed()
{
	TurnController(3);
}

void AMainPawn::FivePressed()
{
	TurnController(4);
}

void AMainPawn::SixPressed()
{
	TurnController(5);
}

void AMainPawn::SevenPressed()
{
	TurnController(6);
}

void AMainPawn::EightPressed()
{
	TurnController(7);
}

void AMainPawn::NinePressed()
{
	TurnController(8);
}

void AMainPawn::TurnController(int sphereindex)
{
	if (GameOver == true) 
	{
		return;
	}


	if (SphereStatus[sphereindex] == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("This one is already taken"))

				return;
		}

	if (TurnCount % 2 == 0)
		{
			Spheres[sphereindex]->SetMaterial(0, Red);
			SphereR[sphereindex] = 2;
		}
	else if (TurnCount % 2 == 1)
		{
			Spheres[sphereindex]->SetMaterial(0, Blue);
			SphereB[sphereindex] = 1;
		}

	SphereStatus[sphereindex] = true;
	TurnCount++;

	WinCheck();
	
}


void AMainPawn::WinCheck()
{
	

	if (SphereB[0] + SphereB[1] + SphereB[2] == 3 || SphereB[0] + SphereB[4] + SphereB[8] == 3 || SphereB[0] + SphereB[3] + SphereB[6] == 3 || SphereB[2] + SphereB[4] + SphereB[6] == 3 || SphereB[3] + SphereB[4] + SphereB[5] == 3 || SphereB[6] + SphereB[7] + SphereB[8] == 3 || SphereB[1] + SphereB[4] + SphereB[7] == 3 || SphereB[2] + SphereB[5] + SphereB[8] == 3) {
		GameOver = true;
		UE_LOG(LogTemp, Warning, TEXT("Blue Wins!"));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Blue Wins!"));
	}
	if (SphereR[0] + SphereR[1] + SphereR[2] == 6 || SphereR[0] + SphereR[4] + SphereR[8] == 6 || SphereR[0] + SphereR[3] + SphereR[6] == 6 || SphereR[2] + SphereR[4] + SphereR[6] == 6 || SphereR[3] + SphereR[4] + SphereR[5] == 6 || SphereR[6] + SphereR[7] + SphereR[8] == 6 || SphereR[1] + SphereR[4] + SphereR[7] == 6 || SphereR[2] + SphereR[5] + SphereR[8] == 6) {
		GameOver = true;
		UE_LOG(LogTemp, Warning, TEXT("Red Wins!"));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Red Wins!"));
	}
	if (TurnCount == 9) {
		UE_LOG(LogTemp, Warning, TEXT("Draw"));
		GameOver = true;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Magenta, TEXT("Draw!"));

	}

}
