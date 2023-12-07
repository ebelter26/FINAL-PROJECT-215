#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
using namespace sfp;

const float KB_SPEED = 0.5;
const float KB_NSPEED = -0.5;

void paddleUpdate(PhysicsRectangle& paddle, int elapsedMS) {
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		Vector2f newPos(paddle.getCenter());
		newPos.x = newPos.x + (KB_SPEED * elapsedMS);
		paddle.setCenter(newPos);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		Vector2f newPos(paddle.getCenter());
		newPos.x = newPos.x + (KB_NSPEED * elapsedMS);
		paddle.setCenter(newPos);
	}
}
void paddleSize(PhysicsRectangle& paddle, PhysicsCircle& ball, int points) {
	if (points > 1 && points < 4) {
		paddle.setSize(Vector2f(90, 20));
		ball.setRadius(13);
	}
	if (points > 3 && points < 6) {
		paddle.setSize(Vector2f(80, 20));
		ball.setRadius(11);
	}
	if (points > 5 && points < 8) {
		paddle.setSize(Vector2f(70, 20));
		ball.setRadius(9);
	}
	if (points > 7 && points < 10) {
		paddle.setSize(Vector2f(60, 20));
		ball.setRadius(7);
	}
	if (points > 9) {
		paddle.setSize(Vector2f(50, 20));
		ball.setRadius(5);
	}
}



int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0,0.5));

	Music song;
	if (!song.openFromFile("song/epic.ogg")) {
		cout << "Couldn't play music";
	}
	song.play();

	Text gameOverText;
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition(400, 300);

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(150, 250));
	ball.setRadius(15);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(0.3, 0.6));

	//Create the paddle
	PhysicsRectangle paddle;
	paddle.setSize(Vector2f(100, 20));
	paddle.setCenter(Vector2f(400, 560));
	paddle.setStatic(true);
	world.AddPhysicsBody(paddle);

	//when ball hits paddle, add to return count
	int points(0);
	paddle.onCollision = [&points](PhysicsBodyCollisionResult result) {
		points++;
		cout << points << endl;
		if (points>3) {
			
		}
		};


	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	int count(0);

	//exits game when ball hits floor
	int endCount(0);
	floor.onCollision = [&endCount](PhysicsBodyCollisionResult result) {
		endCount++;
		if (endCount>2){
			cout << "GAME OVER"<< endl;
			exit(0);
		}
		};
	
	// Create the left wall
	PhysicsRectangle wallLeft;
	wallLeft.setSize(Vector2f(20, 600));
	wallLeft.setCenter(Vector2f(10, 300));
	wallLeft.setStatic(true);
	world.AddPhysicsBody(wallLeft);

	// Create the right wall
	PhysicsRectangle wallRight;
	wallRight.setSize(Vector2f(20, 600));
	wallRight.setCenter(Vector2f(790, 300));
	wallRight.setStatic(true);
	world.AddPhysicsBody(wallRight);

	// Create the ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);


	Clock clock;
	Time lastTime(clock.getElapsedTime());
	Time currentTime(lastTime);

	while (paddleUpdate) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		long deltaMS = deltaTime.asMilliseconds();
		if (deltaMS > 0) {
			lastTime = currentTime;
			world.UpdatePhysics(deltaMS);
			paddleUpdate(paddle, deltaMS);
			paddleSize(paddle, ball, points);

		}

		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(paddle);
		window.draw(floor);
		window.draw(wallLeft);
		window.draw(wallRight);
		window.draw(ceiling);
		//window.draw(gameOverText);

		window.display();

		//moves paddle left + right

	
	}
}
