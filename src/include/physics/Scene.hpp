#pragma once
#include <fstream>
#include "Collision.hpp"
#include "Entity.hpp"
#include "Display.hpp"
#include "World.hpp"

namespace physics
{
	class Scene;

	class Scene
	{
		private:
			class PhysicsSmoothStepSystem final
			{
				private:
					f64 _accumulator = 0;
					Scene* _s = NULL;
				public:
					PhysicsSmoothStepSystem() noexcept;
					PhysicsSmoothStepSystem(Scene& s) noexcept;
					void Step(f64 dt) noexcept;
					void PhysicsUpdate() noexcept;
					f64 physicsUpdateRate;
			};
			struct Counter final
			{
				unsigned int loops;
				f64 total;
				std::vector<f64> loopsPerSecond;
			};
			Counter _fpsCounter;
			Counter _physicsUpdateCounter;
			PhysicsSmoothStepSystem _smoother;
			f64 _dt;
			std::vector<std::unique_ptr<Entity>> _entities;
			DynamicsWorld _world;
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
			bool debugDraw;
		public:
			Scene(const geometry::Vector& gravity, f64 dt) noexcept;
			~Scene() noexcept;
			void SetGravity(const geometry::Vector& g) noexcept;
			void SetDt(f64 dt) noexcept;
			void AddEntity(Entity& e) noexcept;
			void RemoveEntity(Entity& e) noexcept;
			void Step(f64 dt) noexcept;
			f64 GetDt() const noexcept;
			const std::vector<std::unique_ptr<Entity>>& GetEntities() const noexcept;
			unsigned short physicsUpdateFrequency = 60;
			Display* display = NULL;
	};
	/*struct SceneState
	{
		geometry::Vector _gravity;
		SmootherAccumulator = 0;
		Scene::Counter fpsCounter;
		Scene::Counter physicsUpdateCounter;
		f64 dt;
		bool debugDraw;
		//std::vector<
	};*/
}