// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //최소한의 코드만 담아 컴파일한다.
#include "GameFramework/Actor.h" //
#include "HelloSphere.generated.h" //HelloSphere를 generated해야 돌아간다.(규칙)

UCLASS() //언리얼 클래스 사용(규칙)
class HELLOCODE_API AHelloSphere : public AActor //HELLOCODE_API로 클래스를 만들겠다(규칙)
{
	GENERATED_BODY()//(규칙)언리얼 클래스를 만들때 생성자 단위에서 처리해야할 단위를 GENERATED_BODY서 처리하겠다.
	
public:	
	// Sets default values for this actor's properties
	AHelloSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; //virtual~~override이면 상속받는다 -> 비긴플레이는 부모로부터 기능을 상속받는다. 
									   

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//헤더에 구체를 선언하는 방법(1)
protected:
	class UTextRenderComponent* TextRenderComponent;

};
