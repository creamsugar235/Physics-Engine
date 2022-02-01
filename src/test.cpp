#include "test.hpp"
#include <iostream>
using namespace geometry;
bool test::TestCollisionChecking()
{
	{
		PolygonCollider d(Vector(0, 0), Vector(0, 0), Vector(10, 0), Vector(10, 10), {Vector(0, 10)});
		Transform t1;
		t1.position = Vector(0, 0);
		CircleCollider c(Vector(0, 0), 10);
		Transform t2;
		t2.position = Vector(0, 0);
		if (!d.TestCollision(t1, &c, t2).hasCollision || !c.TestCollision(t2, &d, t1).hasCollision)
		{
			std::cerr<<"Dynamic V Circle Collision failed\n";
			std::cerr<<"Collision was false when should have been true\n";
			return false;
		}
		t1.position += 1000;
		if (d.TestCollision(t1, &c, t2).hasCollision || c.TestCollision(t2, &d, t1).hasCollision)
		{
			std::cerr<<"Dynamic V Circle Collision failed\n";
			std::cerr<<"Collision was true when should have been false\n";
			return false;
		}
	}
	{
		BoxCollider b1(Vector(0, 0), Vector(100, 100));
		Transform t1;
		BoxCollider b2(Vector(0, 0), Vector(100, 100));
		Transform t2;
		for (int i = 0; i < 150; i++)
		{
			if ((b1.TestCollision(t1, &b2, t2).hasCollision) && i > 100)
			{
				std::cerr<<"failed: \n";
				return false;
			}
			if (!(b1.TestCollision(t1, &b2, t2).hasCollision) && i < 100)
			{
				std::cerr<<i<<t1.position<<" in but failed\n";
				return false;
			}
			t1.position += 1;
		}
	}
	{
		CircleCollider c1(Vector(0, 0), 4);
		Transform t1;
		t1.position = Vector(0, 0);
		CircleCollider c2(Vector(0, 0), 1);
		Transform t2;
		t2.position = Vector(0, 0);
		if (!c1.TestCollision(t1, &c2, t2).hasCollision || !c2.TestCollision(t2, &c1, t1).hasCollision)
		{
			std::cerr<<"Circle V Circle Collision failed\n";
			std::cerr<<"Collision was false when should have been true\n";
			return false;
		}
		t1.position += 1000;
		if (c1.TestCollision(t1, &c2, t2).hasCollision || c2.TestCollision(t2, &c1, t1).hasCollision)
		{
			std::cerr<<"Circle V Circle Collision failed\n";
			std::cerr<<"Collision was true when should have been false\n";
			return false;
		}
	}
	{
		
		PolygonCollider d1(Vector(0, 0), Vector(0, 0), Vector(10, 0), Vector(5, 10));
		Transform t1;
		t1.position = Vector(0, 0);
		PolygonCollider d2(Vector(0, 0), Vector(0, 0), Vector(10, 0), Vector(10, 10), {Vector(0, 10)});
		Transform t2;
		t2.position = Vector(0, 0);
		if (!d1.TestCollision(t1, &d2, t2).hasCollision || !d2.TestCollision(t2, &d1, t1).hasCollision)
		{
			std::cerr<<"Dynamic V Dynamic Collision failed\n";
			std::cerr<<"Collision was false when should have been true\n";
			return false;
		}
		t1.position += 1000;
		if (d1.TestCollision(t1, &d2, t2).hasCollision || d2.TestCollision(t2, &d1, t1).hasCollision)
		{
			std::cerr<<"Dynamic V Dynamic Collision failed\n";
			std::cerr<<"Collision was true when should have been false\n";
			std::cerr<<d1.TestCollision(t1, &d2, t2)<<"\n";
			std::cerr<<d2.TestCollision(t2, &d1, t1)<<"\n";
			return false;
		}
	}
	return true;
}

bool test::TestColliders()
{
	CircleCollider c1(Vector(10, 10), 40);
	CircleCollider* c2 = (CircleCollider*)c1.Clone();
	if (!(c1.radius == (c2)->radius && c1.center == (c2)->center))
	{
		std::cerr<<"CircleCollider Cloning has falied\n";
		return false;
	}
	PolygonCollider d1(Vector(10, 10), Vector(10, -10), Vector(10, 10), Vector(10, 10));
	PolygonCollider* d2 = (PolygonCollider*)d1.Clone();
	bool b = false;
	if (!(d1.pos == d2->pos && d1.points == d2->points))
	{
		std::cerr<<"PolygonCollider Cloning has falied\n";
		return false;
	}
	delete d2;
	delete c2;
	return true;
}

bool test::TestCollisionObject()
{
	Transform t;
	t.position = Vector(5000, 5000);
	PolygonCollider d(Vector(5000, 5000), Vector(0, 0), Vector(10, 10), Vector(5, 10));
	CollisionObject object(t, d, false);
	if (object.IsTrigger())
	{
		std::cerr<<"IsTrigger() failed, returned true\n";
	}
	if (object.IsDynamic())
	{
		std::cerr<<"IsDynamic() failed, returned true\n";
	}
	PolygonCollider d2 = (PolygonCollider&)object.GetCollider();
	if (!(d.pos == d2.pos && d.points == d2.points))
	{
		std::cerr<<"CollisionObject GetCollider() Function failed returned invalid collider\n";
	}
	if (object.GetPosition() != t.position)
	{
		std::cerr<<"GetPosition() failed, returned: "<<object.GetPosition()<<"\n";
	}
	/*if (!(DefaultQuaternion == object.GetRotation()))
	{
		std::cerr<<"GetRotation() failed, returned: "<<object.GetRotation()<<"\n";
	}*/
	if (!(t == object.GetTransform()))
	{
		std::cerr<<"GetTransform() failed, returned: "<<object.GetTransform()<<"\n";
	}
	return true;
}

bool test::TestRigidbody()
{
	//Rigidbody r(Transform(), PolygonCollider(Vector(0, 0), Vector(1, 1), Vector(2, 2), Vector(3, 3)), false, false);
	
	return true;
}