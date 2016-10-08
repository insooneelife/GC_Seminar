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

	// World가 시작되기 전에 한번 충돌판단을 한다.
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

// 충돌판단을 위한 함수
void World::checkCollision()
{
	for (auto e1 = std::begin(_entities); e1 != std::end(_entities); ++e1)
	{
		for (auto e2 = std::begin(_entities); e2 != std::end(_entities); ++e2)
		{
			if ((*e1)->getID() == (*e2)->getID())
				continue;

			// Story 1.
			// 두 entity가 충돌하는지 확인한다.
			// 여기서 생각해 보아야 할 부분은,
			// 같은 entity라도 서로 다른 충돌 영역을 갖을 수 있는지이다.
			// 예를 들어서 어떤 entity는 다각형 형태의 충돌 영역을 갖고, 
			// 또 다른 entity는 원 형태의 충돌 영역을 갖을 수 있을 것이다.
			// 그렇다면 entity class 내부에 충돌에 필요한 data를 넣을 것이 아니라,
			// shape이라는 class를 따로 만들고, entity는 shape을 갖도록 한 후
			// shape class 안에서 다양한 형태의 충돌 영역을 정의하도록 설계한다.
			// shape -> collide (shape) 의 형태로 두 entity의 shape이 서로 충돌하는지 확인하면 될 것이다.

			if ((*e1)->getBody()->collide((*e2)->getBody()))
			{
				std::cout << (*e1)->getID() << " collide with " << (*e2)->getID() << std::endl;
			}
		}
	}
}

// Story 2.
// 이와 같은 형태로 충돌에 대한 코드를 모두 작성해 보았다.
// Shape, Circle, Rect와 같은 class들을 정의하였고,
// double dispatching 기법을 이용하여 두 인자에 대한 추상화가 가능하도록 구현하였다.
// 이제 entity는 다양한 도형에 대해서도 충돌판별이 가능할 것이다.

// 하지만 과연 이 설계가 장기적인 관점에서 좋은 설계일까?
// 좀 더 다양한 충돌영역들이 정의된다고 생각해보자.
// Polygon이나 Shape Chain(여러 도형으로 정의된 도형)과 같은 도형들이 추가된다면 어떻게 될까?
// Double dispatching의 특성상 새로운 도형이 추가될 때마다,
// 다른 도형들에 있는 코드에서도 인터페이싱을 위한 함수들이 추가되어야 한다.
// 또한 단순히 충돌판단만을 하는 것이 아니라,
// 충돌영역의 넓이, 겹치는 최대 길이, 접점 등등 더 다양한 정보들이 필요해지는 상황이라면,
// 이러한 설계는 결국 한계를 갖게 될 것이다.

// 좀 더 다양하고 복잡한 충돌 정보들이 필요한 상황이라면,
// 충돌 계층을 따로 분리하고, 충돌 정보만을 지속적으로 갱신하도록 구현하는것이 좋을 것이다.
// 하지만 계층을 분리하고 충돌에 있는 다양한 정보들을 만드는 library를 직접 구현하기란 매우 어렵다.
// 그러므로 Box2D library를 이용한다.

