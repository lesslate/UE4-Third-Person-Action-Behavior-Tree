



## 프로젝트 개요

언리얼 엔진을 이용한 히트박스형 3인칭 액션 게임 프로젝트

언리얼 엔진 Behaviour Tree를 이용한 AI 구성을 중점적으로 다룸

> 사용 엔진

Unreal Engine 4 - 4.19

> 플랫폼

Window 64bit

> 장르

3인칭 액션

## Behaviour Tree 구성

![wholeBt](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Portfolio/RaidPort/wholeBT.png?raw=true)

비헤이비어 트리와 블랙보드를 이용하여 값에 따라 보스가 어떤 행동을 할지 구성

### 일반 공격 패턴

![normal](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Portfolio/RaidPort/normal.png?raw=true)

![normal2](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Portfolio/RaidPort/normal2.png?raw=true)

비헤이비어 트리가 루트에서 부터 실행되면 플레이어를 감지하고 난수를 발생시킨 다음 공격할 수 있는 거리를 체크하고 생성된 난수에따라(확률) 공격 애니메이션을 실행

### 회전 패턴

![LR](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Portfolio/RaidPort/leftright.png?raw=true)

일반 패턴이 끝나면 잠시 대기후 플레이어 방향으로 회전



> 타겟의 좌우를 판별하는 로직

![1](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/Direction/1.png?raw=true)



몬스터에서 타겟으로 향하는 벡터(타겟위치 - 몬스터위치) 와 Forward 벡터를 외적한다음 Up 벡터와 내적하면 그 값이 양수일때 왼쪽 음수일때 오른쪽으로 판별 할 수 있다.



![4](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/Direction/GIF.gif?raw=true)



## 원거리 패턴



![LD](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Portfolio/RaidPort/LD.png?raw=true)



보스와 플레이어와의 거리가 멀어 공격할 수 없는 상황일 때 난수를 발생시켜 원거리 패턴을 구사하고 일정거리 이하일땐 플레이어를 추격



### 메테오 패턴

> 메테오 액터 구성



![decal](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/MeteorPattern/decalmeterial.png?raw=true)

메테오가 떨어질 위치를 표시할 데칼 머티리얼 구성



![3](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/MeteorPattern/3.png?raw=true)

메테오 액터 구성



> 메테오 스폰 서비스

![6](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/MeteorPattern/6.png?raw=true)

메테오 스폰 서비스 Blueprint



> 실행 결과

![GIF](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/MeteorPattern/GIF.gif?raw=true)



### 돌진 패턴



> 거리 측정 서비스

```csharp
UBTService_Distance::UBTService_Distance()
{
    NodeName = TEXT("Distance");
    Interval = 1.0f;
}

void UBTService_Distance::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn) return;

    auto Grux = Cast<AGrux>(OwnerComp.GetAIOwner()->GetPawn());

    bool bResult;

    auto Target = Cast<ARaidPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGruxAIController::TargetKey));

    if (nullptr == Target)
        return;

    bResult = (Target->GetDistanceTo(ControllingPawn) >= 1000.0f);

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(AGruxAIController::Distance, bResult);
}
```

캐릭터와 몬스터의 거리가 1000이 넘으면 true를 반환하는 서비스



> 돌진 이동속도 서비스

![2](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/Dashattack/2.png?raw=true)

> 블랙보드 설정

![4](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/Dashattack/4.png?raw=true)

`Distance`가 1000이하일때 거리가 1000이상 벌어지면 중단하고 바로 돌진패턴을 시작하도록 `On Value Change`로 수정



> 실행 결과

![5](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/Dashattack/GIF.gif?raw=true)



### 범위 패턴

> 범위 패턴 AnimNotify

![1](https://github.com/lesslate/lesslate.github.io/blob/master/assets/img/Unreal/Quake/1.png?raw=true)



> RadialDamage

```csharp
void AGrux::ServerApplyRadialDamage_Implementation(float RDamage,float Radius)
{
    UGameplayStatics::ApplyRadialDamage(GetWorld(), RDamage, this->GetActorLocation(), Radius, nullptr, TArray<AActor*>(), this, false, ECC_GameTraceChannel5);
    GruxLeftCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GruxRightCheck->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    FVector Center = this->GetActorLocation();
    UWorld* World = GetWorld();

    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
    bool bResult = World->OverlapMultiByChannel(
        OverlapResults,
        Center,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel5,
        FCollisionShape::MakeSphere(Radius),
        CollisionQueryParam
    );
    if (bResult)
    {
        for (auto OverlapResult : OverlapResults)
        {
            ARaidPlayer* Player = Cast<ARaidPlayer>(OverlapResult.GetActor());
            if (Player != nullptr)
            {
                CHECK(Player != nullptr);
                FVector PlayerLocation = Player->GetActorLocation();
                FTransform PlayerTransform = Player->GetActorTransform();
                if (!Player->IsDodge)
                {
                    UGameplayStatics::PlaySoundAtLocation(this, GruxGroundHit, PlayerLocation);
                    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GruxFireEffect, PlayerTransform, true);
                }
            }
        }
    }
}
```

### 상세 개발과정

[캐릭터 콤보](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-C++-%EB%A9%80%ED%8B%B0%ED%94%8C%EB%A0%88%EC%9D%B4-%EC%BA%90%EB%A6%AD%ED%84%B0-%EC%BD%A4%EB%B3%B4/)

[비헤이비어 트리 좌우판별](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-Behavior-Tree-%EC%A2%8C%EC%9A%B0-%ED%8C%90%EB%B3%84/)

[비헤이비어 트리 돌진패턴](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-Behavior-Tree-%EC%9B%90%EA%B1%B0%EB%A6%AC-%EB%8F%8C%EC%A7%84-%ED%8C%A8%ED%84%B4/)

[비헤이비어 트리 원거리 스킬 패턴](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-Behavior-Tree-%EC%9B%90%EA%B1%B0%EB%A6%AC-%EC%8A%A4%ED%82%AC/)

[비헤이비어 트리 점프 패턴](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-Behavior-Tree-%EC%A0%90%ED%94%84-%ED%8C%A8%ED%84%B4/)

[비헤이비어 트리 범위 패턴](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-Behavior-Tree-%EB%B2%94%EC%9C%84-%ED%8C%A8%ED%84%B4/)

[비헤이비어 트리 랜덤 패턴](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-Behavior-Tree-%EB%9E%9C%EB%8D%A4-%ED%8C%A8%ED%84%B4/)

[AI 정지/시작](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-AI%EC%A0%95%EC%A7%80-%EC%8B%9C%EC%9E%91/)

[보스/캐릭터 데미지 전달](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-%EC%BA%90%EB%A6%AD%ED%84%B0-%EB%8D%B0%EB%AF%B8%EC%A7%80-%EC%A0%84%EB%8B%AC/)

[트레일 이펙트](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-Trail/)

[보스 페이즈 전환](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%B3%B4%EC%8A%A4-%ED%8E%98%EC%9D%B4%EC%A6%88-Boss-Phase/)

[레벨 스트리밍 (로딩)](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%A0%88%EB%B2%A8-%EC%8A%A4%ED%8A%B8%EB%A6%AC%EB%B0%8D(%EB%A1%9C%EB%94%A9)/)

[레벨 구성](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EB%A0%88%EB%B2%A8-%EA%B5%AC%EC%84%B1%ED%95%98%EA%B8%B0/)

[Setting UI 제작](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-%EC%84%B8%ED%8C%85-UI-%EB%A7%8C%EB%93%A4%EA%B8%B0/)

[UI 구성하기](https://lesslate.github.io/unreal4/%EC%96%B8%EB%A6%AC%EC%96%BC4-UI-%EA%B5%AC%EC%84%B1%ED%95%98%EA%B8%B0/)



### 데모 다운로드 링크

[RaidDemo.zip - Google Drive](https://drive.google.com/file/d/1HcpNnioHy_pP-sFhzAJn9HVU6Mo0Jc7s/view?usp=sharing)

> 데모조작키 

W,A,S,D - 이동

오른쪽 마우스 클릭 - 공격

왼쪽 마우스 클릭 - 콤보 공격

왼쪽 Shift - 달리기

ESC - 메뉴

Z - 스킬

### 플레이 영상

[UE4 Raid - YouTube](https://youtu.be/3UrmHi87_c0)
