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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			CircleCollider b(Vector(0, 0), 10);
			sf::CircleShape* circ = new sf::CircleShape(10);
			circ->setOutlineThickness(1);
			circ->setFillColor(sf::Color::Transparent);
			circ->setOutlineColor(sf::Color::White);
			Transform t;
			sf::Vector2f pos = w.mapPixelToCoords(sf::Mouse::getPosition(w));
			t.position.x = pos.x;
			t.position.y = pos.y;
			circ->setPosition(sf::Vector2f(pos.x - 10, pos.y - 10));
			Rigidbody r(t, b, false, 25);
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
	sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2f(100, 1));
	/*line->rotate(90);
	line->setPosition(100, 100);
	line->setFillColor(sf::Color::White);
	sprites.push_back(line);
	sf::CircleShape* circ = new sf::CircleShape(30);
	circ->setOutlineThickness(1);
	circ->setFillColor(sf::Color::Transparent);
	circ->setOutlineColor(sf::Color::White);
	sprites.push_back(circ);
	sf::Vertex proj[2] = {
		sf::Vertex(sf::Vector2f(100, 100), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(1, 0), sf::Color::Blue)
	};

	sf::Vertex lineToCirc[2] = {
		sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red),
		sf::Vertex(sf::Vector2f(1, 0), sf::Color::Red)
	};
	Line l1;
	Line l2;
	lineToCirc[0].position = sf::Vector2f(100, 100);
	l2.a += 100;*//*
	sf::Vertex a[2] = {
		sf::Vertex(sf::Vector2f(100, 100), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(200, 100), sf::Color::Blue)
	};
	sf::Vertex b[2] = {
		sf::Vertex(sf::Vector2f(200, 100), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(200, 200), sf::Color::Blue)
	};
	sf::Vertex c[2] = {
		sf::Vertex(sf::Vector2f(200, 200), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(100, 200), sf::Color::Blue)
	};
	sf::Vertex d[2] = {
		sf::Vertex(sf::Vector2f(100, 200), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(100, 100), sf::Color::Blue)
	};
	Line lines[4] = {
		Line(Vector(100, 100), Vector(200, 100)),
		Line(Vector(200, 100), Vector(200, 200)),
		Line(Vector(200, 200), Vector(100, 200)),
		Line(Vector(100, 200), Vector(100, 100))
	};
	sf::CircleShape circ(1);
	circ.setFillColor(sf::Color::Red);
	sf::CircleShape proj(3);
	proj.setFillColor(sf::Color::Green);*/
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
		// circ.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		// Vector vec(circ.getPosition().x, circ.getPosition().y);
		Time::Tick();
		/*window.clear();
		f64 dis = std::numeric_limits<f64>::max();
		Vector closest;
		for (const Line& l: lines)
		{
			Vector prj = Vector::Projection(vec, l);
			if (Calc::Distance(prj, vec) < dis)
			{
				closest = prj;
				dis = geometry::Calc::Distance(prj, vec);
			}
		}
		std::vector<bool> bools;
		closest.x += 2;
		for (const Line& l: lines)
		{
			bools.push_back(l.VectorIsOnLine(closest - 1));
			std::cerr<<l<<"\t";
		}
		std::cout<<bools<<"\n";
		std::cerr<<closest<<"\n";
		proj.setPosition(sf::Vector2f(closest.x, closest.y));
		window.draw(a, 2, sf::Lines);
		window.draw(b, 2, sf::Lines);
		window.draw(c, 2, sf::Lines);
		window.draw(d, 2, sf::Lines);
		window.draw(proj);
		window.display();*/
		/*circ->setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		l2.b = Vector(circ->getPosition().x, circ->getPosition().y);
		lineToCirc[1].position = (circ->getPosition());
		circ->setPosition(circ->getPosition().x - 30, circ->getPosition().y - 30);
		//proj[0].position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		l1.a = Vector(proj[0].position.x, proj[0].position.y);
		Vector pos;
		pos = Vector::Projection(l2.b, Line(Vector(100, 100), Vector(100, 200)));
		proj[1].position.x = pos.x;
		proj[1].position.y = pos.y;
		l1.b = Vector(pos);
		std::cerr<<l1<<"\n";
		window.clear();
		for (sf::Drawable* d: sprites)
		{
			window.draw(*d);
		}
		window.draw(proj, 2, sf::Lines);
		window.draw(lineToCirc, 2, sf::Lines);
		window.display();*/
		if (!timeout)
		 	Generate(window, bodies, sprites);
		Update(bodies, sprites, collisions);
		Draw(sprites, &window, collisions);
	}
	for (sf::Drawable* d: sprites)
	{
		delete d;
	}
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
			if (a.NotEquals(b))
			{
				Collider& tmp = b.GetCollider();
				if (a.GetCollider().TestCollision(a.GetTransform(), &tmp, b.GetTransform()).hasCollision)
				{
					std::cerr<<"WHAT?\n";
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