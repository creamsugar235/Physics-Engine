#include "../include/physics/World.hpp"
#include <iostream>

namespace physics
{
	//bouncing
	void ImpulseSolver:: Solve(std::vector<Collision>& collisions, f64 dt) noexcept
	{
		for (Collision& c: collisions)
		{
			if (!c.a->IsDynamic() || !c.b->IsDynamic()) continue;
			Rigidbody* a = (Rigidbody*) c.a;
			Rigidbody* b = (Rigidbody*) c.b;
			f64 e = std::min(a->GetRestitution(), b->GetRestitution());
			geometry::Vector rv = b->GetVelocity() - a->GetVelocity();
			f64 velAlongNormal = rv.Dot(c.points.normal);
			if (velAlongNormal > 0) continue;
			f64 j = -(1 + e) * velAlongNormal;
			j /= a->GetInvMass() + b->GetInvMass();
			double ratio = a->GetMass() / (a->GetMass() + b->GetMass());
			geometry::Vector impulse = c.points.normal * j;
			geometry::Vector aVel = a->GetVelocity();
			geometry::Vector bVel = b->GetVelocity();
			aVel -= ratio * impulse;
			ratio = b->GetMass() / a->GetMass() + b->GetMass();
			bVel += ratio * impulse;
			a->SetVelocity(aVel * dt);
			b->SetVelocity(bVel * dt);
		}
	}

	void PositionalCorrectionSolver::Solve(std::vector<Collision>& collisions, f64 dt) noexcept
	{
		for (Collision& c: collisions)
		{
			if (!c.a->IsDynamic() || !c.b->IsDynamic()) continue;
			Rigidbody* a = (Rigidbody*) c.a;
			Rigidbody* b = (Rigidbody*) c.b;
			double percentage = 0.2;
			double slop = 0.01;
			double correction = std::max(c.points.depth - slop, 0.0) / (a->GetInvMass() + b->GetInvMass()) * percentage;
			geometry::Vector aPos = a->GetPosition();
			geometry::Vector bPos = b->GetPosition();
			aPos -= a->GetInvMass() * correction * dt;
			bPos += b->GetInvMass() * correction * dt;
			a->SetPosition(aPos);
			b->SetPosition(bPos);
		}
	}

	template <typename T>
	T getMin(std::vector<T>& v)	
	{
		bool reachedVal = false;
		T minVal;
		for (T item: v)
		{
			if (!reachedVal)
			{
				minVal = item; reachedVal = true; continue;
			}
			if (minVal > item)
			{
				minVal = item;
			}
		}
		return minVal;
	}

	template <typename T>
	T getMax(std::vector<T>& v)	
	{
		bool reachedVal = false;
		T maxVal;
		for (T item: v)
		{
			if (!reachedVal)
			{
				maxVal = item; reachedVal = true; continue;
			}
			if (maxVal < item)
			{
				maxVal = item;
			}
		}
		return maxVal;
	}

	struct Square
	{
		f64 x = 0;
		f64 y = 0;
		f64 width = 0;
		f64 height = 0;
	};

	bool SquareOverLaps(const Square& a, const Square& b)
	{
		auto numInRange = [&] (double value, double minVal, double maxVal){
			return (value >= minVal) && (value <= maxVal);
		};
		bool xOverlaps = numInRange(a.x, b.x, b.x + b.width) ||
			numInRange(b.x, a.x, a.x + a.width);
		bool yOverlaps = numInRange(a.y, b.y, b.y + b.height) ||
			numInRange(b.y, a.y, a.y + a.height);
		return xOverlaps && yOverlaps;
	}

	void CollisionWorld::AddObject(CollisionObject* o) noexcept
	{
		_objects.push_back(o);
	}

	void CollisionWorld::AddSolver(Solver* s) noexcept
	{
		_solvers.push_back(s);
	}

	void CollisionWorld::ResolveCollisions(f64 dt) noexcept
	{
		std::vector<Collision> collisions;
		for (auto& a: _objects)
		{
			for (auto& b: _objects)
			{
				if (a == b) break;
				Square BoundingBoxA;
				Square BoundingBoxB;
				auto clone = a->GetCollider().Clone();
				if (dynamic_cast<CircleCollider*>(clone))
				{
					CircleCollider& cc = dynamic_cast<CircleCollider&>(a->GetCollider());
					geometry::Vector center = cc.center;
					f64 radius = cc.radius;
					BoundingBoxA.x = center.x - radius + a->GetTransform().position.x;
					BoundingBoxA.y = center.y - radius + a->GetTransform().position.y;
					BoundingBoxA.width = radius * 2;
					BoundingBoxA.height = radius * 2;
				}
				else if (dynamic_cast<DynamicCollider*>(clone))
				{
					DynamicCollider& dc = dynamic_cast<DynamicCollider&>(a->GetCollider());
					geometry::Vector minimum = getMin(dc.points);
					geometry::Vector maximum = getMax(dc.points);
					BoundingBoxA.x = minimum.x + a->GetTransform().position.x;
					BoundingBoxA.y = minimum.y + a->GetTransform().position.y;
					BoundingBoxA.width = maximum.x - minimum.x;
					BoundingBoxA.height = maximum.y - minimum.y;
				}
				else if (dynamic_cast<BoxCollider*>(clone))
				{
					BoxCollider& bc = (BoxCollider&)(a->GetCollider());
					BoundingBoxA.x = bc.x + a->GetTransform().position.x;
					BoundingBoxA.y = bc.y + a->GetTransform().position.y;
					BoundingBoxA.width = bc.width;
					BoundingBoxA.height = bc.height;
				}
				/*else if (dynamic_cast<MeshCollider*>(clone))
				{
					MeshCollider& mc = dynamic_cast<MeshCollider&>(a->GetCollider());
					geometry::Vector minimum = getMin(mc.colliders);
					geometry::Vector maximum = getMax(mc.colliders);
					BoundingBoxA.x = minimum.x;
					BoundingBoxA.y = minimum.y;
					BoundingBoxA.width = maximum.x - minimum.x;
					BoundingBoxA.height = maximum.y - minimum.y;
				}*/
				delete clone;
				clone = b->GetCollider().Clone();
				if (dynamic_cast<CircleCollider*>(clone))
				{
					CircleCollider& cc = dynamic_cast<CircleCollider&>(b->GetCollider());
					geometry::Vector center = cc.center;
					f64 radius = cc.radius;
					BoundingBoxB.x = center.x - radius + b->GetTransform().position.x;
					BoundingBoxB.y = center.y - radius + b->GetTransform().position.y;
					BoundingBoxB.width = radius * 2;
					BoundingBoxB.height = radius * 2;
				}
				else if (dynamic_cast<DynamicCollider*>(clone))
				{
					DynamicCollider& dc = dynamic_cast<DynamicCollider&>(b->GetCollider());
					geometry::Vector minimum = getMin(dc.points);
					geometry::Vector maximum = getMax(dc.points);
					BoundingBoxB.x = minimum.x + b->GetTransform().position.x;
					BoundingBoxB.y = minimum.y + b->GetTransform().position.y;
					BoundingBoxB.width = maximum.x - minimum.x;
					BoundingBoxB.height = maximum.y - minimum.y;
				}
				else if (dynamic_cast<BoxCollider*>(clone))
				{
					BoxCollider& bc = (BoxCollider&)b->GetCollider();
					BoundingBoxB.x = bc.x + b->GetTransform().position.x;
					BoundingBoxB.y = bc.y + b->GetTransform().position.y;
					BoundingBoxB.width = bc.width;
					BoundingBoxB.height = bc.height;
				}
				delete clone;
				if (SquareOverLaps(BoundingBoxA, BoundingBoxB))
				{
					std::cerr<<"OMG WE TOUCHED?\n";
					CollisionPoints points = a->GetCollider().TestCollision(
						a->GetTransform(), &b->GetCollider(), b->GetTransform()
					);
					if (points.hasCollision)
					{
						std::cerr<<"WE DIDDD!!\n";
						Collision c;
						c.a = a;
						c.b = b;
						c.points = points;
						collisions.push_back(c);
					}
				}
			}
		}
		for (auto solver: _solvers)
		{
			solver->Solve(collisions, dt);
		}
	}

	void CollisionWorld::RemoveObject(CollisionObject* o) noexcept
	{
		for (auto p = _objects.begin(); p < _objects.end(); p++)	
		{
			if (*p == o)
			{
				_objects.erase(p);
				return;
			}
		}
	}

	void CollisionWorld::RemoveSolver(Solver* s) noexcept
	{
		for (auto p = _solvers.begin(); p < _solvers.end(); p++)
		{
			if (*p == s)
			{
				_solvers.erase(p);
				return;
			}
		}
	}

	void CollisionWorld::SetCollisionCallBack(std::function<void(Collision&, f64)>& callback, f64 dt) noexcept
	{
		_onCollision = callback;
	}

	void CollisionWorld::SendCollisionCallBacks(std::vector<Collision>& collisions, f64 dt) noexcept
	{
		for (Collision& c : collisions)
		{
			_onCollision(c, dt);
			const auto& a = c.a->GetOnCollisionFunction();
			const auto& b = c.b->GetOnCollisionFunction();
			if (a) a(c, dt);
			if (b) b(c, dt);
		}
	}

	void DynamicsWorld::AddRigidbody(Rigidbody* r) noexcept
	{
		if (!r) {return;}
		if (r->UsesGravity())
		{
			r->SetGravity(_gravity);
		}
		else
		{
			r->SetGravity(geometry::Vector(0, 0));
		}
		_objects.push_back(r);
	}

	void DynamicsWorld::ApplyGravity(f64 dt) noexcept
	{
		for (auto& obj: _objects)
		{
			if (!obj->IsDynamic()) continue;
			Rigidbody* rigidbody = (Rigidbody*) obj;
			if (!rigidbody->UsesGravity()) continue;
			geometry::Vector grav = (rigidbody->GetGravity() / rigidbody->GetMass()) * dt;
			grav.x = 0;
			rigidbody->ApplyForce(grav);
		}
	}

	void DynamicsWorld::MoveObjects(f64 dt) noexcept
	{
		for (auto& obj: _objects)
		{
			if (!obj->IsDynamic()) continue;
			Rigidbody* rigidbody = (Rigidbody*)obj;
			geometry::Vector pos = geometry::Vector(rigidbody->GetPosition()) + rigidbody->GetVelocity() * dt;
			rigidbody->SetPosition(pos);
			rigidbody->SetForce(geometry::Vector(0, 0));
		}
	}

	void DynamicsWorld::Update(f64 dt) noexcept
	{
		ApplyGravity(dt);
		ResolveCollisions(dt);
		MoveObjects(dt);
	}

	DynamicsWorld::DynamicsWorld() noexcept
	{
	}
}