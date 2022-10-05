// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloSphere.h"
//USphereComponent�������� �˻��� ��� �߰�
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHelloSphere::AHelloSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // Tick�̺�Ʈ�� �߻��ϰڴٿ� ���ϰڴ�.

	/////////////////////////////////////////////////////////////////////////////
	
	//cpp�� ��ü�� �����ϴ� ���(1)
	//��Ʈ ������Ʈ�� ��ħ�� �浹�� �˷��ִ� ��ü ������Ʈ�� �ɰ�
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>
		(TEXT("RootComponent")); // ���۳�Ʈ�������ϴ� ��ɾ�<������������ ���۳�Ʈ�� ����>(�����۳�Ʈ�� �̸�)
	RootComponent = SphereComponent;
	//��ü ������Ʈ�� �Ӽ��� �����Ѵ�.
	SphereComponent->InitSphereRadius(220.0f);//������Ʈ�� ��������
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));//OverlapAllDynamic�̶�� �ݸ��� �������� �����ϰڴ�.
	//��ü �޽ø� �����ϰ� �����Ѵ�.
	UStaticMeshComponent* SphereVisual = CreateAbstractDefaultSubobject< UStaticMeshComponent>
		(TEXT("SphereMesh"));
	SphereVisual->AttachTo(RootComponent);
	/*
	//Construction helper�� ����� �޽ÿ� ����ƽ �޽ø� �����Ѵ�
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); //FObjectFinder ->������Ʈ�� ã�´�. <UStaticMesh>�� ã�� �־��ش�.
	//�޽� ������ �߰ߵƴٸ� �޽��� �Ӽ��� �����Ѵ�.
	if (SphereAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}
	*/
	//���͸��� ������ ����  �� �ڵ带 �Ʒ��� ���� ����
	ConstructorHelpers::FObjectFinder<UStaticMesh>SphereAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	ConstructorHelpers::FObjectFinder<UMaterial>SphereMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
	if (SphereAsset.Succeeded()&& SphereMaterial.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereAsset.Object);
		SphereVisual->SetMaterial(0, SphereMaterial.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}

	//���̾� ��ƼŬ �߰��ϱ�(2)
	//���̾� ��ƼŬ �ý��� �����ϱ�
	UParticleSystemComponent* FireParticles = CreateDefaultSubobject<UParticleSystemComponent>
		(TEXT("FireParticles"));
	FireParticles->AttachTo(SphereVisual);
	FireParticles->bAutoActivate = true;
	//������Ʈ�� ���̾� ��ƼŬ �ý��� �����ϱ�
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireVisual(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (FireVisual.Succeeded())
	{
		FireParticles->SetTemplate(FireVisual.Object);
		FireParticles->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	}

	//�ؽ�Ʈ �߰��ϱ�(3)
	//�ؽ�Ʈ ���� ������Ʈ �ʱ�ȭ
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>
		(TEXT("Text"));
	TextRenderComponent->AttachTo(SphereVisual);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetYScale(2.0f);
	TextRenderComponent->SetXScale(2.0f);
	TextRenderComponent->SetVisibility(true);
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));//(���ӽ����̽�(ī�װ��з�),Ű, ������ ���--)

	//��������Ʈ�� �̺�Ʈ ���� ���
	OnActorBeginOverlap.AddDynamic(this, &AHelloSphere::MyOnBegineOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHelloSphere::MyOnEndOverlap);
}

// Called when the game starts or when spawned
void AHelloSphere::BeginPlay()
{
	Super::BeginPlay(); //Super�θ��� BeginPlay�� �ڵ�� �ִٸ� �����ϰڴ�.
	
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

