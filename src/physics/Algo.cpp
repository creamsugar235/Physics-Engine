#include "../include/physics/Algo.hpp"
#include "../include/physics/OstreamOverloads.hpp"
#include <iostream>

namespace algo
{
	CollisionPoints FindCircleCircleCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		c.hasCollision = false;
		if (!a || !b) {return c;}
		f64 r = geometry::Calc::DistanceSquared(a->center + ta.position, b->center + tb.position);
		// If the sum of their radii is greater than or equal to the distance between their centers
		if (pow(a->radius + b->radius, 2) >= r)
		{
			geometry::Line l(a->center + ta.position, b->center + tb.position);
			c.a = l.GetVectorAlongLine(a->radius);
			c.b = l.GetVectorAlongLine(b->radius, false);
			c.depth = geometry::Calc::Distance(c.a, c.b);
			c.normal = c.b - c.a;
			c.normal.Normalize();
			c.hasCollision = true;
		}
		else
		{
			c.hasCollision = false;
		}
		return c;
	}

	CollisionPoints FindCircleBoxCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const BoxCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		if (!a || !b ) {return c;}
		//easier to find collision points as a PolygonCollider
		PolygonCollider* bb = new PolygonCollider(b->pos, b->pos,
			geometry::Vector(b->x + b->width, b->y), 
			geometry::Vector(b->x + b->width, b->y + b->height), {geometry::Vector(b->x , b->y + b->height)});
		return FindPolygonCircleCollisionPoints(bb, tb, a, ta);
	}

	CollisionPoints FindCircleMeshCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const MeshCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		c.hasCollision = false;
		if (!a || !b) {return c;}
		for (const Collider* ptr: b->colliders)
		{
			c = ptr->TestCollision(tb, a, ta);
			if (c.hasCollision) {return c;}
		}
		return c;
	}

	CollisionPoints FindPolygonCircleCollisionPoints(
		const PolygonCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		c.hasCollision = false;
		if (!a || !b) {return c;}
		if (a->points.size() < 3) {return c;}
		c = CircleInsidePolygon(a, ta, b, tb);
		if (c.hasCollision)
			return c;
		std::vector<geometry::Line> lines;
		for (unsigned i = 0; i < a->points.size(); i++)
		{
			lines.push_back(geometry::Line(a->points[i] + a->pos + ta.position, a->points[(i + 1) % a->points.size()] + a->pos + ta.position));
		}
		geometry::Vector closest = geometry::Infinity;
		geometry::Line closestLine;
		f64 dis = std::numeric_limits<f64>::max();
		// project the circle's center onto every line in the PolygonCollider
		for (const geometry::Line& l: lines)
		{
			geometry::Vector proj = geometry::Vector::Projection(b->center + tb.position, l);
			if (geometry::Calc::DistanceSquared(proj, b->center + tb.position) < dis)
			{
				// if the vector is on the line
				if (l.VectorIsOnLine(proj))
				{
					closest = proj;
					dis = geometry::Calc::DistanceSquared(proj, b->center + tb.position);
					closestLine = l;
				}
			}
		}
		if (dis == std::numeric_limits<f64>::max())
			return c;
		if (geometry::Calc::DistanceSquared(closest, b->center + tb.position) > b->radius * b->radius)
			return c;
		auto VectorInCircle = [&] (const geometry::Vector& center, const f64& radius, const geometry::Vector point) {
			f64 sqrDis = pow((center.x - point.x), 2) + pow((center.x - point.y), 2);
			return sqrDis <= radius * radius;
		};
		// if the polygon collider is inside the circle
		{
			geometry::Vector farthest = geometry::Infinity;
			f64 maxDis = std::numeric_limits<f64>::min();
			bool allInCircle = false;
			for (unsigned i = 0; i < a->points.size(); i++)
			{
				if (!VectorInCircle(b->center + tb.position, b->radius, a->points[i]))
					break;
				f64 distance = geometry::Calc::DistanceSquared(a->points[i], b->center + tb.position);
				if (distance > maxDis)
				{
					farthest = a->points[i];
					maxDis = distance;
				}
				if (i == a->points.size() - 1)
					allInCircle = true;
			}
			if (allInCircle)
			{
				c.a = closest;
				geometry::Line tmp(closest, b->center + tb.position);
				c.b = tmp.GetVectorAlongLine(b->radius, false);
				// reversed norm vector to push PolygonCollider out of circle				
				c.normal = c.a - c.b;
				c.depth = geometry::Calc::Distance(c.a, c.b);
				c.normal.Normalize();
				c.hasCollision = true;
				return c;
			}
		}
		//if the circle's center is inside the PolygonCollider
		if (PolygonColliderVectorIsColliding(a, ta, b->center + tb.position))
		{
			c.a = b->center + tb.position;
			c.b = closest;
			// reversed norm vector to push circle out of PolygonCollider
			c.normal = c.a - c.b;
			c.depth = geometry::Calc::Distance(c.a, c.b);
			c.normal.Normalize();
			c.hasCollision = true;
			return c;
		}
		// else 
		c.a = closest;
		geometry::Line radius(closest, b->center + tb.position);
		c.b = radius.GetVectorAlongLine(b->radius, false);
		c.normal = c.b - c.a;
		c.normal.Normalize();
		c.hasCollision = true;
		return c;
	}

	geometry::Vector getCentroid(std::vector<geometry::Vector> points)
	{
		if (points.size())
		{
			geometry::Vector first = points.at(0);
			geometry::Vector last = points.at(points.size() - 1);
			if (first.x != last.x || first.y != last.y)
			{
				points.push_back(first);
			}
			f64 twiceArea = 0, x = 0, y = 0, f = 0;
			geometry::Vector p1, p2;
			// absolutely no clue what this does, it just works lol
			for (size_t i = 0, j = points.size() - 1; i < points.size(); j=i++)
			{
				p1 = points[i]; p2 = points[j];
				f = (p1.y - first.y) * (p2.x - first.x) - (p2.y - first.y) * (p1.x - first.x);
				twiceArea += f;
				x += (p1.x + p2.x - 2 * first.x) * f;
				y += (p1.y + p2.y - 2 * first.y) * f;
			}
			f = twiceArea * 3;
			return geometry::Vector(x / f + first.x, y / f + first.y);
		}
		else
			return geometry::Origin;
	}

	CollisionPoints FindPolygonPolygonCollisionPoints(
		const PolygonCollider* a, const Transform& ta,
		const PolygonCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		c.hasCollision = false;
		if (!a || !b) {return c;}
		if (a->points.size() < 3 || b->points.size() < 3) {return c;}
		c = PolygonInsidePolygon(a, ta, b, tb);
		if (c.hasCollision)
			return c;
		//check every point in collider b if it intersects with a
		std::vector<geometry::Vector> pointIntersectsB;
		for (const geometry::Vector& p: b->points)
		{
			if (PolygonColliderVectorIsColliding(a, ta, p + b->pos + tb.position))
			{
				pointIntersectsB.push_back(p + b->pos + tb.position);
			}
		}
		if (!pointIntersectsB.size())
			return c;
		geometry::Vector closest = pointIntersectsB.at(0);
		bool reached = false;
		geometry::Vector centroidA = getCentroid(a->points) + a->pos + ta.position;
		for (const geometry::Vector& p: pointIntersectsB)
		{
			if (!reached)
			{
				reached = true; closest = p; continue;
			}
			if (geometry::Calc::DistanceSquared(p, centroidA) < geometry::Calc::DistanceSquared(closest, centroidA))
				closest = p; 
		}
		c.b = closest;
		std::vector<geometry::Vector> pointIntersectsA;
		for (const geometry::Vector& p: a->points)
		{
			if (PolygonColliderVectorIsColliding(b, tb, p + a->pos + ta.position))
			{
				pointIntersectsA.push_back(p + a->pos + ta.position);
			}
		}
		if (!pointIntersectsA.size())
			return c;
		closest = geometry::Origin;
		reached = false;
		geometry::Vector centroidB = getCentroid(b->points) + b->pos + tb.position;
		for (const geometry::Vector& p: pointIntersectsA)
		{
			if (!reached)
			{
				reached = true; closest = p; continue;
			}
			if (geometry::Calc::DistanceSquared(p, centroidB) < geometry::Calc::DistanceSquared(closest, centroidB))
			{
				closest = p;
			}
		}
		c.a = closest;
		c.depth = geometry::Calc::Distance(c.a, c.b);
		c.normal = (c.b - c.a);
		c.normal.Normalize();
		c.hasCollision = true;
		return c;
	}

	CollisionPoints FindPolygonBoxCollisionPoints(
		const PolygonCollider* a, const Transform& ta,
		const BoxCollider* b, const Transform& tb)
	{
		CollisionPoints c;
		if (!a || !b) {return c;}
		PolygonCollider* bb = new PolygonCollider(b->pos, b->pos,
			geometry::Vector(b->x + b->width, b->y), 
			geometry::Vector(b->x + b->width, b->y + b->height), {geometry::Vector(b->x , b->y + b->height)});
		return FindPolygonPolygonCollisionPoints(a, ta, bb, tb);
	}

	CollisionPoints FindPolygonMeshCollisionPoints(
		const PolygonCollider* a, const Transform& ta,
		const MeshCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		if (!a || !b) {return c;}
		for (const Collider* ptr: b->colliders)
		{
			c = ptr->TestCollision(tb, a, ta);
			if (c.hasCollision) {return c;}
		}
		return c;
	}

	CollisionPoints FindBoxBoxCollisionPoints(
		const BoxCollider* a, const Transform& ta,
		const BoxCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		if (!a || !b) {return c;}
		PolygonCollider* bb = new PolygonCollider(b->pos, b->pos,
			geometry::Vector(b->x + b->width, b->y), 
			geometry::Vector(b->x + b->width, b->y + b->height), {geometry::Vector(b->x , b->y + b->height)});
		PolygonCollider* aa = new PolygonCollider(a->pos, a->pos,
			geometry::Vector(a->x + a->width, a->y), 
			geometry::Vector(a->x + a->width, a->y + a->height), {geometry::Vector(a->x , a->y + a->height)});
		return FindPolygonPolygonCollisionPoints(aa, ta, bb, tb);
	}

	CollisionPoints FindBoxMeshCollisionPoints(
		const BoxCollider* a, const Transform& ta,
		const MeshCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		if (!a || !b) {return c;}
		for (const Collider* ptr: b->colliders)
		{
			c = ptr->TestCollision(tb, a, ta);
			if (c.hasCollision) {return c;}
		}
		return c;
	}

	CollisionPoints FindMeshMeshCollisionPoints(
		const MeshCollider* a, const Transform& ta,
		const MeshCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		if (!a || !b) {return c;}
		for (const Collider* ptrA: a->colliders)
		{
			for (const Collider* ptrB: a->colliders)
			{
				c = ptrA->TestCollision(ta, ptrB, tb);
				if (c.hasCollision) {return c;}
			}
		}
		return c;
	}

	bool LinePassesThroughCircle(
		const geometry::Line& a, const CircleCollider* b,
		const Transform& tb
	)
	{
		if (geometry::Calc::DistanceSquared(a.a, b->center + tb.position) <= b->radius * b->radius)
			return true;
		else if (geometry::Calc::DistanceSquared(a.b, b->center + tb.position) <= b->radius * b->radius)
			return true;
		geometry::Vector v = geometry::Vector::Projection(b->center + tb.position, a);
		return geometry::Calc::DistanceSquared(v, b->center + tb.position) <= b->radius * b->radius;
	}

	bool CircleInsideCircle(
		const CircleCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	)
	{
		return geometry::Calc::DistanceSquared(a->center + ta.position, 
			b->center + tb.position) < fabs(a->radius * a->radius - b->radius * b->radius);
	}

	CollisionPoints CircleInsidePolygon(
		const PolygonCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		c.hasCollision = false;
		if (!a || !b) return c;
		if (a->points.size() < 3) return c;
		if (!PolygonColliderVectorIsColliding(a, ta, b->center + tb.position))
			return c;
		geometry::Vector projections[a->points.size()];
		geometry::Vector closest;
		f64 distance = std::numeric_limits<f64>::infinity();
		for (size_t i = 0; i < a->points.size(); i++)
		{
			geometry::Line l(a->points[i] + a->pos + ta.position, 
				a->points[(i + 1) % a->points.size()] + a->pos + ta.position);
			projections[i] = geometry::Vector::Projection(b->center + tb.position, l);
			if (geometry::Calc::DistanceSquared(projections[i], b->center + tb.position) < b->radius * b->radius)
				return c;
			if (geometry::Calc::DistanceSquared(projections[i], b->center + tb.position) < distance)
			{
				closest = projections[i];
				distance = geometry::Calc::DistanceSquared(closest, b->center + tb.position);
			}
		}
		c.b = closest;
		c.a = geometry::Line(b->center + tb.position, closest).GetVectorAlongLine(b->radius);
		c.normal = c.a - c.b;
		c.normal.Normalize();
		c.hasCollision = true;
		c.depth = geometry::Calc::Distance(c.a, c.b);
		return c;
	}

	CollisionPoints PolygonInsidePolygon(
		const PolygonCollider* a, const Transform& ta,
		const PolygonCollider* b, const Transform& tb
	)
	{
		// farthest point from A's centroid
		geometry::Vector farthest;
		geometry::Vector centroidA = getCentroid(a->points) + a->pos + ta.position;
		f64 distance = std::numeric_limits<f64>::min();
		bool allInPolygon = false;
		for (size_t i = 0; i < a->points.size(); i++)
		{
			if (!PolygonColliderVectorIsColliding(b, tb, a->points[i] + a->pos + ta.position))
				break;
			if (geometry::Calc::DistanceSquared(a->points[i] + a->pos + ta.position, centroidA) > distance)
			{
				farthest = a->points[i] + a->pos + ta.position;
				distance = geometry::Calc::DistanceSquared(a->points[i] + a->pos + ta.position, centroidA);
			}
			if (i == a->points.size() - 1)
				allInPolygon = true;
		}
		if (allInPolygon)
		{
			geometry::Vector closest = geometry::Infinity;
			f64 dis = closest.x; // infinity
			for (size_t i = 0; i < b->points.size(); i++)
			{
				geometry::Line l(b->points[i] + b->pos + tb.position, b->points[(i + 1) % b->points.size()] + b->pos + tb.position);
				auto tmp = geometry::Vector::Projection(farthest, l);
				if (geometry::Calc::DistanceSquared(tmp, farthest) < dis)
				{
					closest = tmp;
					dis = geometry::Calc::DistanceSquared(tmp, farthest);
				}
			}
			CollisionPoints c;
			c.a = farthest;
			c.b = closest;
			// pushing collider a out of collider b
			c.normal = c.a - c.b;
			c.normal.Normalize();
			c.hasCollision = true;
			c.depth = geometry::Calc::Distance(c.a, c.b);
			return c;
		}
		else
		{
			distance = std::numeric_limits<f64>::min();
			// do not need to reset allInPolygon since it is already false
			geometry::Vector centroidB = getCentroid(b->points) + b->pos + tb.position;
			for (size_t i = 0; i < b->points.size(); i++)
			{
				if (!PolygonColliderVectorIsColliding(a, ta, b->points[i] + b->pos + tb.position))
					break;
				if (geometry::Calc::DistanceSquared(b->points[i] + b->pos + tb.position, centroidB) > distance)
				{
					farthest = b->points[i] + b->pos + tb.position;
					distance = geometry::Calc::DistanceSquared(b->points[i] + b->pos + tb.position, centroidB);
				}
				if (i == b->points.size() - 1)
					allInPolygon = true;
			}
			if (allInPolygon)
			{
				geometry::Vector closest = geometry::Infinity;
				f64 dis = closest.x; // infinity
				for (size_t i = 0; i < a->points.size(); i++)
				{
					geometry::Line l(a->points[i] + a->pos + ta.position, a->points[(i + 1) % a->points.size()] + a->pos + ta.position);
					auto tmp = geometry::Vector::Projection(farthest, l);
					if (geometry::Calc::DistanceSquared(tmp, farthest) < dis)
					{
						closest = tmp;
						dis = geometry::Calc::DistanceSquared(tmp, farthest);
					}
				}
				CollisionPoints c;
				c.b = farthest;
				c.a = closest;
				// pushing collider a out of collider b
				c.normal = c.b - c.a;
				c.normal.Normalize();
				c.hasCollision = true;
				c.depth = geometry::Calc::Distance(c.b, c.a);
				return c;
			}
		}
		return CollisionPoints();
	}

	bool PolygonColliderVectorIsColliding(
		const PolygonCollider* a, const Transform& ta,
		const geometry::Vector& b)
	{
		/*
		* All this does is draw a (horizontal)line from b to the farthest point in a, if the amount
		* of intersections with the polygon is even, b is not inside if it is odd b is inside.
		*/
		if (a->points.size() <3)/* ily too <3*/ {return false;}
		geometry::Vector max = (*max_element(a->points.begin(), a->points.end())) + a->pos + ta.position;
		geometry::Line line(b, geometry::Vector(max.x + (1 * max.x > b.x ? 1 : -1), b.y));
		std::vector<geometry::Vector> listOfIntersections = std::vector<geometry::Vector>();
		for (size_t i = 0; i < a->points.size(); i++)
		{
			geometry::Line l(a->points[i] + a->pos + ta.position, a->points[(i + 1) % a->points.size()] + a->pos + ta.position);
			if (geometry::Calc::Intersecting(l, line))
			{
				if (!listOfIntersections.size() || !std::count(listOfIntersections.begin(), listOfIntersections.end(), (geometry::Calc::VectorOfIntersect(l, line))))
					listOfIntersections.push_back(geometry::Calc::VectorOfIntersect(l, line));
			}
		}
		return listOfIntersections.size() % 2;
	}
}