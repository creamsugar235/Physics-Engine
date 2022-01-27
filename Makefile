all: compilePhysics link run
debug: debugCompilePhysics debugLink run

compileGeometry:
	g++ -c -Wall -std=c++17 src/geometry/Calc.cpp -o bin/o/Calc.o
	g++ -c -Wall -std=c++17 src/geometry/Line.cpp -o bin/o/Line.o
	g++ -c -Wall -std=c++17 src/geometry/Math.cpp -o bin/o/Math.o
	g++ -c -Wall -std=c++17 src/geometry/Vector.cpp -o bin/o/Vector.o
	ar rcs lib/geometry.a bin/o/Calc.o bin/o/Line.o bin/o/Vector.o bin/o/Math.o
	ranlib lib/geometry.a
	rm bin/o/*.o

checkSyntax:
	g++ -fsyntax-only -std=c++17 src/physics/*.cpp
	g++ -fsyntax-only -std=c++17 src/main.cpp

debugCompileGeometry:
	g++ -g -rdynamic -c -Wall -std=c++17 src/geometry/Calc.cpp -o bin/o/Calc.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/geometry/Line.cpp -o bin/o/Line.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/geometry/Math.cpp -o bin/o/Math.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/geometry/Vector.cpp -o bin/o/Vector.o
	ar rcs lib/geometry.a bin/o/Calc.o bin/o/Line.o bin/o/Vector.o bin/o/Math.o
	ranlib lib/geometry.a
	rm bin/o/*.o

compilePhysics:
	g++ -c -Wall -std=c++17 src/physics/Algo.cpp -o bin/o/Algo.o
	g++ -c -Wall -std=c++17 src/physics/BoxCollider.cpp -o bin/o/BoxCollider.o
	g++ -c -Wall -std=c++17 src/physics/CircleCollider.cpp -o bin/o/CircleCollider.o
	g++ -c -Wall -std=c++17 src/physics/Collision.cpp -o bin/o/Collision.o
	g++ -c -Wall -std=c++17 src/physics/Collider.cpp -o bin/o/Collider.o
	g++ -c -Wall -std=c++17 src/physics/CollisionObject.cpp -o bin/o/CollisionObject.o
	g++ -c -Wall -std=c++17 src/physics/Display.cpp -o bin/o/Display.o
	g++ -c -Wall -std=c++17 src/physics/DynamicCollider.cpp -o bin/o/DynamicCollider.o
	g++ -c -Wall -std=c++17 src/physics/Entity.cpp -o bin/o/Entity.o
	g++ -c -Wall -std=c++17 src/physics/MeshCollider.cpp -o bin/o/MeshCollider.o
	g++ -c -Wall -std=c++17 src/physics/OstreamOverloads.cpp -o bin/o/OstreamOverloads.o
	g++ -c -Wall -std=c++17 src/physics/Rigidbody.cpp -o bin/o/Rigidbody.o
	g++ -c -Wall -std=c++17 src/physics/Scene.cpp -o bin/o/Scene.o
	g++ -c -Wall -std=c++17 src/physics/Time.cpp -o bin/o/Time.o
	g++ -c -Wall -std=c++17 src/physics/World.cpp -o bin/o/World.o
	ar rcs lib/physics.a bin/o/*.o
	ranlib lib/physics.a
	rm bin/o/*.o

debugCompilePhysics:
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/Algo.cpp -o bin/o/Algo.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/BoxCollider.cpp -o bin/o/BoxCollider.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/CircleCollider.cpp -o bin/o/CircleCollider.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/Collision.cpp -o bin/o/Collision.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/Collider.cpp -o bin/o/Collider.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/CollisionObject.cpp -o bin/o/CollisionObject.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/Display.cpp -o bin/o/Display.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/DynamicCollider.cpp -o bin/o/DynamicCollider.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/Entity.cpp -o bin/o/Entity.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/MeshCollider.cpp -o bin/o/MeshCollider.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/OstreamOverloads.cpp -o bin/o/OstreamOverloads.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/Rigidbody.cpp -o bin/o/Rigidbody.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/Scene.cpp -o bin/o/Scene.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/test.cpp -o bin/o/Test.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/Time.cpp -o bin/o/Time.o
	g++ -g -rdynamic -c -Wall -std=c++17 src/physics/World.cpp -o bin/o/World.o
	ar rcs lib/physics.a bin/o/*.o
	ranlib lib/physics.a
	rm bin/o/*.o

link:
	g++ -lX11 -Wl,-rpath,bin -Wall -std=c++17 src/main.cpp -o bin/main lib/physics.a lib/geometry.a -L lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

debugLink:
	g++ -g -rdynamic -lX11 -pthread -Wl,-rpath,bin -Wall -std=c++17 src/main.cpp -o bin/main lib/physics.a lib/geometry.a -L lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

run:
	./bin/main