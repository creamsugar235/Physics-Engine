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
double timeout = 0;
void Update(std::vector<Rigidbody>& rigidbodies, std::vector<sf::Drawable*>& drawables, std::vector<Collision>& c);

void Draw(std::vector<sf::Drawable*> drawables, sf::RenderWindow* win, std::vector<physics::Collision> collisions)
{
	win->clear();
	for (sf::Drawable* d: drawables)
	{
		win->draw(*d);
	}
	for (Collision c: collisions)
	{
		CollisionPoints p = c.points;
		sf::CircleShape c1(2);
		c1.setFillColor(sf::Color::Red);
		sf::CircleShape c2(2);
		c2.setFillColor(sf::Color::Blue);
		c1.setPosition(p.a.x - 2, p.a.y - 2);
		c2.setPosition(p.b.x - 2, p.b.y - 2);
		sf::RectangleShape line(sf::Vector2f(Calc::Distance(p.a, p.b), 1));
		line.setPosition(p.a.x, p.a.y);
		line.rotate(Calc::Degrees(Calc::GetAngle(p.a, p.b)));
		win->draw(line);
		win->draw(c1);
		win->draw(c2);
	}
	win->display();
}

void Generate(sf::RenderWindow& w, std::vector<Rigidbody>& v, std::vector<sf::Drawable*>& drawTo)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			BoxCollider b(Vector(0, 0), Vector(20, 20));
			sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(20, 20));
			rect->setOutlineThickness(1);
			rect->setFillColor(sf::Color::Transparent);
			rect->setOutlineColor(sf::Color::White);
			Transform t;
			sf::Vector2f pos = w.mapPixelToCoords(sf::Mouse::getPosition(w));
			t.position.x = pos.x;
			t.position.y = pos.y;
			rect->setPosition(sf::Vector2f(pos.x, pos.y));
			Rigidbody r(t, b, false, 20);
			v.push_back(r);
			drawTo.push_back(rect);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			BoxCollider b(Vector(0, 0), Vector(50, 50));
			sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(50, 50));
			rect->setOutlineThickness(1);
			rect->setFillColor(sf::Color::Transparent);
			rect->setOutlineColor(sf::Color::White);
			Transform t;
			sf::Vector2f pos = w.mapPixelToCoords(sf::Mouse::getPosition(w));
			t.position.x = pos.x;
			t.position.y = pos.y;
			rect->setPosition(sf::Vector2f(pos.x, pos.y));
			Rigidbody r(t, b, false, 50);
			v.push_back(r);
			drawTo.push_back(rect);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			CircleCollider b(Vector(0, 0), 20);
			sf::CircleShape* circ = new sf::CircleShape(20);
			circ->setOutlineThickness(1);
			circ->setFillColor(sf::Color::Transparent);
			circ->setOutlineColor(sf::Color::White);
			Transform t;
			sf::Vector2f pos = w.mapPixelToCoords(sf::Mouse::getPosition(w));
			t.position.x = pos.x;
			t.position.y = pos.y;
			circ->setPosition(sf::Vector2f(pos.x - 20, pos.y - 20));
			Rigidbody r(t, b, false, 50);
			v.push_back(r);
			drawTo.push_back(circ);
		}
	}
}

int main(int argc, char** args)
{
	Time __t__();
	srand(time(NULL));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(300, 300), "PhysicsSim", sf::Style::Default, settings);
	std::vector<Rigidbody> bodies;
	std::vector<sf::Drawable*> sprites;
	std::vector<Collision> collisions;
	while (window.isOpen())
	{
		if (timeout > 0) {timeout--;}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		Time::Tick();
		if (!timeout)
			Generate(window, bodies, sprites);
		Update(bodies, sprites, collisions);
		Draw(sprites, &window, collisions);
	}
	for (sf::Drawable* d: sprites)
	{
		delete d;
	}
	BoxCollider b(Vector(0, 0), Vector(20, 20));
	Transform trans;
	CollisionObject c(trans, b, false);
	b.~BoxCollider();
	std::cerr<<"Err?\n";
	c.~CollisionObject();
	return 0;
}

void Update(std::vector<Rigidbody>& rigidbodies,
std::vector<sf::Drawable*>& drawables, std::vector<Collision>& c)
{
	c.clear();
	for (Rigidbody& a: rigidbodies)
	{
		for (Rigidbody& b: rigidbodies)
		{
			if (a != b)
			{
				Collider& tmp = b.GetCollider();
				if (a.GetCollider().TestCollision(a.GetTransform(), &tmp, b.GetTransform()).hasCollision)
				{
					Collision collision;
					collision.a = &a;
					collision.b = &b;
					collision.points = a.GetCollider().TestCollision(a.GetTransform(), &tmp, b.GetTransform());
					c.push_back(collision);
				}
			}
		}
	}
}