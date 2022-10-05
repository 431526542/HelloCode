// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloSphere.h"
//USphereComponent에러떠서 검색후 헤더 추가
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHelloSphere::AHelloSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // Tick이벤트를 발생하겠다와 안하겠다.

	/////////////////////////////////////////////////////////////////////////////
	
	//cpp에 구체를 선언하는 방법(1)
	//루트 컴포넌트는 겹침과 충돌을 알려주는 구체 컴포넌트가 될것
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>
		(TEXT("RootComponent")); // 컴퍼넌트르생성하는 명령어<내가만들고싶은 컴퍼넌트의 형태>(이컴퍼넌트의 이름)
	RootComponent = SphereComponent;
	//구체 컴포넌트에 속성을 적용한다.
	SphereComponent->InitSphereRadius(220.0f);//컴포넌트의 반지름값
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));//OverlapAllDynamic이라는 콜리전 프리셋을 적용하겠다.
	//구체 메시를 생성하고 연결한다.
	UStaticMeshComponent* SphereVisual = CreateAbstractDefaultSubobject< UStaticMeshComponent>
		(TEXT("SphereMesh"));
	SphereVisual->AttachTo(RootComponent);
	/*
	//Construction helper를 사용해 메시에 스태틱 메시를 적용한다
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //FObjectFinder ->오브젝트를 찾는다. <UStaticMesh>를 찾아 넣어준다.
	//메시 에셋이 발견됐다면 메시의 속성을 조절한다.
	if (SphereAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}
	*/
	//머터리얼 적용을 위해  위 코드를 아래와 같이 변경
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	ConstructorHelpers::FObjectFinder<UMaterial>SphereMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
	if (SphereAsset.Succeeded()&& SphereMaterial.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereAsset.Object);
		SphereVisual->SetMaterial(0, SphereMaterial.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}

	//파이어 파티클 추가하기(2)
	//파이어 파티클 시스템 생성하기
	UParticleSystemComponent* FireParticles = CreateDefaultSubobject<UParticleSystemComponent>
		(TEXT("FireParticles"));
	FireParticles->AttachTo(SphereVisual);
	FireParticles->bAutoActivate = true;
	//컴포넌트에 파이어 파티클 시스템 적용하기
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireVisual(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (FireVisual.Succeeded())
	{
		FireParticles->SetTemplate(FireVisual.Object);
		FireParticles->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	}

	//텍스트 추가하기(3)
	//텍스트 렌더 컴포넌트 초기화
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>
		(TEXT("Text"));
	TextRenderComponent->AttachTo(SphereVisual);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetYScale(2.0f);
	TextRenderComponent->SetXScale(2.0f);
	TextRenderComponent->SetVisibility(true);
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));//(네임스페이스(카테고리분류),키, 나오는 언어--)

	//델리게이트와 이벤트 선언 방법
	OnActorBeginOverlap.AddDynamic(this, &AHelloSphere::MyOnBegineOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHelloSphere::MyOnEndOverlap);
}

// Called when the game starts or when spawned
void AHelloSphere::BeginPlay()
{
	Super::BeginPlay(); //Super부모의 BeginPlay에 코드거 있다면 실행하겠다.
	
}

// Called every frame
void AHelloSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHelloSphere::MyOnBegineOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString outputString;
	outputString = "Hello " + OtherActor->GetName() + "!";
	TextRenderComponent->SetText(FText::FromString(outputString));
}

void AHelloSphere::MyOnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));
}

