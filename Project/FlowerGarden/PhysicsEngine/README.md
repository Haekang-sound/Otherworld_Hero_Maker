# PhysicsEngine
Designing a Physics Engine in 5 minutes
(https://www.youtube.com/watch?v=-_IspRG548E)를 
참고해서 만든 물리엔진. 기획 발표까지 샘플 만드는 것이 목표입니다.

## features
- Transform: 위치, 크기, 회전을 관리

- CollisionPoint: 충돌 결과 정보를 담은 객체

- Collider: 충돌체 기본 클래스 및 인터페이스 
	- CircleCollider
	- RectangleCollider
	- IsometricCollider

- Object: 물리적인 특성을 가진 구조체

- Collision: 충돌한 두 객체와 충돌 결과 관리

- PhysicsWorld: 물리 객체를 관리하고 시뮬레이션 진행

## Dependency
Transform <- CircleCollider
Transform <- Collision
Transform <- Collider

CollisionPoint <- Collider
CollisionPoint <- Collision

Collider <- CircleCollider
Collider <- RectangleCollider
Collider <- IsometricCollider
Collider <- Object

CircleCollider <- RectangleCollider
CircleCollider <- Collider

RectangleCollider <- CircleCollider
RectangleCollider <- Collider

IsometricCollider <- Collider

Object <- Collision

Collision <- PhysicsWorld

## 외부
Constants <- CircleCollider

DirectY <-CircleCollider
DirectY <-RectangleCollider
DirectY <-IsometricCollider
DirectY <-PhysicsWorld

Vector2 <- Transform
Vector2 <- CollisionPoints
Vector2 <- Collider
Vector2 <- Object
Vector2 <- PhysicsWorld

# Journal
프로젝트를 진행하면서 기타 느낀 것

## 네임스페이스의 범위 생각하면서 전방선언하기
`Collider` 클래스에서 자식 클래스의 포인터를 매개변수로 갖기 위해
전방선언을 했는데, 이 때 `namespace` 안에 선언되지 않으면
컴파일러가 외부 클래스로 인식해버린다.
_2023-07-31_