#include "World.h"
#include "Entity.h"
#include <iostream>

#include "Shapes\Rect.h"
#include "Shapes\Circle.h"

World::World()
{
	// unique_ptr needs to be initialized by emplace_back.
	_entities.emplace_back(new Entity(*this, 1, Vec2(100, 100), new Rect(Vec2(100, 100), 50, 50)));
	_entities.emplace_back(new Entity(*this, 2, Vec2(180, 200), new Rect(Vec2(180, 200), 70, 30)));
	_entities.emplace_back(new Entity(*this, 3, Vec2(50, 100), new Rect(Vec2(50, 100), 130, 70)));
	_entities.emplace_back(new Entity(*this, 4, Vec2(400, 200), new Rect(Vec2(400, 200), 40, 50)));
	_entities.emplace_back(new Entity(*this, 5, Vec2(500, 200), new Rect(Vec2(500, 200), 60, 50)));
	_entities.emplace_back(new Entity(*this, 6, Vec2(150, 200), new Circle(Vec2(150, 200), 70)));
	_entities.emplace_back(new Entity(*this, 7, Vec2(450, 200), new Circle(Vec2(450, 200), 50)));
	_entities.emplace_back(new Entity(*this, 8, Vec2(250, 200), new Circle(Vec2(250, 200), 50)));

	// World�� ���۵Ǳ� ���� �ѹ� �浹�Ǵ��� �Ѵ�.
	checkCollision();
}

World::~World()
{}

void World::update()
{
	for (auto e = std::begin(_entities); e != std::end(_entities); ++e)
	{
		(*e)->update();
	}
}

void World::render()
{
	for (auto e = std::begin(_entities); e != std::end(_entities); e++)
	{
		(*e)->render();
	}
}

// �浹�Ǵ��� ���� �Լ�
void World::checkCollision()
{
	for (auto e1 = std::begin(_entities); e1 != std::end(_entities); ++e1)
	{
		for (auto e2 = std::begin(_entities); e2 != std::end(_entities); ++e2)
		{
			if ((*e1)->getID() == (*e2)->getID())
				continue;

			// Story 1.
			// �� entity�� �浹�ϴ��� Ȯ���Ѵ�.
			// ���⼭ ������ ���ƾ� �� �κ���,
			// ���� entity�� ���� �ٸ� �浹 ������ ���� �� �ִ����̴�.
			// ���� �� � entity�� �ٰ��� ������ �浹 ������ ����, 
			// �� �ٸ� entity�� �� ������ �浹 ������ ���� �� ���� ���̴�.
			// �׷��ٸ� entity class ���ο� �浹�� �ʿ��� data�� ���� ���� �ƴ϶�,
			// shape�̶�� class�� ���� �����, entity�� shape�� ������ �� ��
			// shape class �ȿ��� �پ��� ������ �浹 ������ �����ϵ��� �����Ѵ�.
			// shape -> collide (shape) �� ���·� �� entity�� shape�� ���� �浹�ϴ��� Ȯ���ϸ� �� ���̴�.

			if ((*e1)->getBody()->collide((*e2)->getBody()))
			{
				std::cout << (*e1)->getID() << " collide with " << (*e2)->getID() << std::endl;
			}
		}
	}
}

// Story 2.
// �̿� ���� ���·� �浹�� ���� �ڵ带 ��� �ۼ��� ���Ҵ�.
// Shape, Circle, Rect�� ���� class���� �����Ͽ���,
// double dispatching ����� �̿��Ͽ� �� ���ڿ� ���� �߻�ȭ�� �����ϵ��� �����Ͽ���.
// ���� entity�� �پ��� ������ ���ؼ��� �浹�Ǻ��� ������ ���̴�.

// ������ ���� �� ���谡 ������� �������� ���� �����ϱ�?
// �� �� �پ��� �浹�������� ���ǵȴٰ� �����غ���.
// Polygon�̳� Shape Chain(���� �������� ���ǵ� ����)�� ���� �������� �߰��ȴٸ� ��� �ɱ�?
// Double dispatching�� Ư���� ���ο� ������ �߰��� ������,
// �ٸ� �����鿡 �ִ� �ڵ忡���� �������̽��� ���� �Լ����� �߰��Ǿ�� �Ѵ�.
// ���� �ܼ��� �浹�Ǵܸ��� �ϴ� ���� �ƴ϶�,
// �浹������ ����, ��ġ�� �ִ� ����, ���� ��� �� �پ��� �������� �ʿ������� ��Ȳ�̶��,
// �̷��� ����� �ᱹ �Ѱ踦 ���� �� ���̴�.

// �� �� �پ��ϰ� ������ �浹 �������� �ʿ��� ��Ȳ�̶��,
// �浹 ������ ���� �и��ϰ�, �浹 �������� ���������� �����ϵ��� �����ϴ°��� ���� ���̴�.
// ������ ������ �и��ϰ� �浹�� �ִ� �پ��� �������� ����� library�� ���� �����ϱ�� �ſ� ��ƴ�.
// �׷��Ƿ� Box2D library�� �̿��Ѵ�.

