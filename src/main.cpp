#include "include/physics/Scene.hpp"
#include "include/SFML/Main.hpp"
#include "physics/main.hpp"
#include "test.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
using namespace physics;
using namespace geometry;
int main()
{
	Scene s(Vector(0, 0));
	sf::Sprite sprite;
	sf::Texture t;
	t.loadFromFile("bin/textures/Square.png");
	sprite.setTexture(t);
	Transform tmp;
	tmp.position.Set(20, 50);	
	Rigidbody rb;
	rb.SetTransform(tmp);
	rb.SetUsesGravity(0);
	rb.SetCollider(BoxCollider(Vector(0, 0), Vector(50, 50)));
	Entity e;
	e.SetCollisionObject(rb);
	e.SetSprite(sprite);
	e.Update();
	s.AddEntity(e);
	Entity e2;
	tmp.position.Set(20, 100);
	rb.SetMass(1);
	rb.SetCollider(BoxCollider(Vector(0, 0), Vector(10, 10)));
	rb.SetTransform(tmp);
	rb.SetUsesGravity(true);
	rb.SetGravity(Vector(0, -9.81).Normalized());
	sf::Texture circ;
	sprite.setTextureRect(sf::IntRect(1, 1, 10, 10));
	//sprite.setColor(sf::Color::Blue);
	e2.SetCollisionObject(rb);
	e2.SetSprite(sprite);
	e2.Update();
	s.AddEntity(e2);
	s.physicsUpdateFrequency = 1000;
	while (s.display->WindowIsOpen())
	{
		Time::Tick();
		s.Update(Time::deltaTime);
		std::cerr<<s.GetEntities()[0]->GetTransform()<<"\n";
		std::cerr<<s.GetEntities()[1]->GetTransform()<<"\n";
	}
}