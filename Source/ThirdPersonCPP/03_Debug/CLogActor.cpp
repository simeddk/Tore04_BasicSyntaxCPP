#include "CLogActor.h"
#include "Global.h"

ACLogActor::ACLogActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACLogActor::BeginPlay()
{
	Super::BeginPlay();

	CLog::Print(1);
	CLog::Print(2, 1);
	CLog::Print(3, 2, 20.f);
	CLog::Print(4, 2, 20.f, FColor::Orange);
	CLog::Print("Hello C++ World");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

	CLog::Log(777);
	CLog::Log(PI);
	CLog::Log("Hohoho~~~~~");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());
	CLog::Log(this);
	CLog::Log(__FILE__);
	CLog::Log(__FUNCTION__, __LINE__);
	PrintLine();
}

void ACLogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//RunningTime += DeltaTime; //GetWorld()->TimeSeconds
	RunningTime = GetWorld()->TimeSeconds;
	CLog::Print(RunningTime, 100);
}

