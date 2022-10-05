// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HybridSphere.generated.h"

UCLASS(BlueprintType)
class HELLOCODE_API AHybridSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHybridSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//이거 추가
protected:
	UPROPERTY(Category = "Components", EditAnywhere)
		class USphereComponent* Sphere;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite);
		class UTextRenderComponent* Text;

	UPROPERTY(Category = "Components", EditAnywhere)
		class UParticleSystemComponent* Particles;

	UPROPERTY(Category = "Components", EditAnywhere)
		class UStaticMeshComponent* Mesh;

//네이티브 이벤트와 나
	//오버랩 수행
	UFUNCTION(BlueprintNativeEvent)
		void MyOnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void MyOnBeginOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor);

	//오버랩 수행 종료
	UFUNCTION(BlueprintNativeEvent)
		void MyOnEndOverlap(AActor* OverlappedActor, AActor* OtherActor); //블루프린트와 c++에서 사용하는 이름을 이렇게 정하고

	void MyOnEndOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor); //실기능을 여기로 사용한다.
};
