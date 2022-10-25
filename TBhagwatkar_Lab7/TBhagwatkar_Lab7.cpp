// TBhagwatkar_Lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Creating the window, with a gravity of 0,1 
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Creating the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(450, 150));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(.5, .3));

	// Create the floor, ceiling, left and right walls 
	PhysicsRectangle floor, ceiling, wallLeft, wallRight, centerRect;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	wallLeft.setSize(Vector2f(20, 560));
	wallLeft.setCenter(Vector2f(10, 300));
	wallLeft.setStatic(true);
	world.AddPhysicsBody(wallLeft);

	wallRight.setSize(Vector2f(20, 560));
	wallRight.setCenter(Vector2f(790, 300));
	wallRight.setStatic(true);
	world.AddPhysicsBody(wallRight);

	//Center rectangle
	centerRect.setSize(Vector2f(150, 150));
	centerRect.setCenter(Vector2f(400, 300));
	centerRect.setStatic(true);
	world.AddPhysicsBody(centerRect);

	// Thud and Bang Counter
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount + 1 << endl; // writing 1 thud after every hit
		thudCount++; 
	};
	int bangCount(0);
	centerRect.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "BANG " << bangCount + 1 << endl; // writing 1 band after every hit
		bangCount++;
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (bangCount < 3) {
		// closes the window after the ball hits the center 3 times
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(wallLeft);
		window.draw(wallRight);
		window.draw(centerRect);
		window.display();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
