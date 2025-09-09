# PhysicsEngine
Designing a Physics Engine in 5 minutes
(https://www.youtube.com/watch?v=-_IspRG548E)�� 
�����ؼ� ���� ��������. ��ȹ ��ǥ���� ���� ����� ���� ��ǥ�Դϴ�.

## features
- Transform: ��ġ, ũ��, ȸ���� ����

- CollisionPoint: �浹 ��� ������ ���� ��ü

- Collider: �浹ü �⺻ Ŭ���� �� �������̽� 
	- CircleCollider
	- RectangleCollider
	- IsometricCollider

- Object: �������� Ư���� ���� ����ü

- Collision: �浹�� �� ��ü�� �浹 ��� ����

- PhysicsWorld: ���� ��ü�� �����ϰ� �ùķ��̼� ����

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

## �ܺ�
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
������Ʈ�� �����ϸ鼭 ��Ÿ ���� ��

## ���ӽ����̽��� ���� �����ϸ鼭 ���漱���ϱ�
`Collider` Ŭ�������� �ڽ� Ŭ������ �����͸� �Ű������� ���� ����
���漱���� �ߴµ�, �� �� `namespace` �ȿ� ������� ������
�����Ϸ��� �ܺ� Ŭ������ �ν��ع�����.
_2023-07-31_