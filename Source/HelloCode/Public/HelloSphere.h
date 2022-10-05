// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //�ּ����� �ڵ常 ��� �������Ѵ�.
#include "GameFramework/Actor.h" //
#include "HelloSphere.generated.h" //HelloSphere�� generated�ؾ� ���ư���.(��Ģ)

UCLASS() //�𸮾� Ŭ���� ���(��Ģ)
class HELLOCODE_API AHelloSphere : public AActor //HELLOCODE_API�� Ŭ������ ����ڴ�(��Ģ)
{
	GENERATED_BODY()//(��Ģ)�𸮾� Ŭ������ ���鶧 ������ �������� ó���ؾ��� ������ GENERATED_BODY�� ó���ϰڴ�.
	
public:	
	// Sets default values for this actor's properties
	AHelloSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; //virtual~~override�̸� ��ӹ޴´� -> ����÷��̴� �θ�κ��� ����� ��ӹ޴´�. 
									   

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//����� ��ü�� �����ϴ� ���(1)
protected:
	class UTextRenderComponent* TextRenderComponent;

};
