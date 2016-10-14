#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TransformNode.h"

#define bodyScale 2
#define bodyX 20.0f
#define bodyY 60.0f

using namespace sf;

Event evt;
int globalWindmilIndex = 2;
float rotatePoint[3] = { 200, 400, 600 };
bool rotateAll = false;

int main(int argc, char* argv) 
{
  RenderWindow window(VideoMode(1200, 900), "Oleg Matviyishyn Project 1");
  
  RectangleShape* bodyRects[3];

  Texture cloudsTexture;
  cloudsTexture.loadFromFile("res/tiling_clouds.jpg");
  cloudsTexture.setRepeated(true);

  Sprite tilingCloudsSprite;
  tilingCloudsSprite.setTexture(cloudsTexture);
  tilingCloudsSprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

  Music music;
  music.openFromFile("res/le_melody.wav");


  for (int i = 0; i < 3; i++) {
	  bodyRects[i] = new RectangleShape(Vector2<float>(bodyX, bodyY));
	  Texture* towerTexture = new Texture();
	  towerTexture->loadFromFile("res/tower.png");
	  bodyRects[i]->setTexture(towerTexture, true);
	 
	  bodyRects[i] -> setOrigin(10.0f, (60.0f + 20.0f + 10.0f) / 2); // Calculating a center here. It's Y of body + diameter of circle + Y of blade divided by 2
  }

  CircleShape* circleShapes[3];
 
  for (int i = 0; i < 3; i++) {
	  circleShapes[i] = new CircleShape(5);
	  Texture* circleTexture = new Texture();
	  circleTexture->loadFromFile("res/planet.jpg");
	  circleShapes[i]->setTexture(circleTexture, true);
	  circleShapes[i]->setOrigin(5, 5);
	  circleShapes[i]->setPosition(10, 0);
  }

  RectangleShape* bladeRects[3][4];

  for (int i = 0; i < 3; i++) {
	  bladeRects[i][0] = new RectangleShape(Vector2<float>(5, 20));

	  bladeRects[i][1] = new RectangleShape(Vector2<float>(5, 20));
	  bladeRects[i][1]->rotate(90);
	  bladeRects[i][1]->setOrigin(0, 20);

	  bladeRects[i][2] = new RectangleShape(Vector2<float>(5, 20));
	  bladeRects[i][2]->rotate(90 * 3);
	  bladeRects[i][2]->setOrigin(-22.5, 22.5);

	  bladeRects[i][3] = new RectangleShape(Vector2<float>(5, 20));
	  bladeRects[i][3]->rotate(90 * 2);
	  bladeRects[i][3]->setOrigin(7.5, 27.5);

	  Texture* swordTexture = new Texture();
	  swordTexture->loadFromFile("res/sword.png");
	 
	  bladeRects[i][0]->setTexture(swordTexture, true);
	  bladeRects[i][1]->setTexture(swordTexture, true);
	  bladeRects[i][2]->setTexture(swordTexture, true);
	  bladeRects[i][3]->setTexture(swordTexture, true);

	  bladeRects[i][0]->setPosition(2.5, -20);
	  bladeRects[i][1]->setPosition(10, 2.5);
	  bladeRects[i][2]->setPosition(2.5, 30);
	  bladeRects[i][3]->setPosition(0, 2.5);
  }

  float posX = 350;
  for (int i = 0; i < 3; i++) {
	  bodyRects[i]->setPosition(posX, 450);
	  bodyRects[i]->setScale(bodyScale, bodyScale);
	  posX += 250;
  }
  
  TransformNode* bodies[3];
  TransformNode* blades[3][4];
  TransformNode* circles[3];
  for (int i = 0; i < 3; i++) {
	  bodies[i] = new TransformNode(bodyRects[i]);
	  circles[i] = new TransformNode(circleShapes[i]);
	  for (int j = 0; j < 4; j++) {
		  blades[i][j] = new TransformNode(bladeRects[i][j]);
		  circles[i]->AddChild(blades[i][j]);
	  }
	  bodies[i]->AddChild(circles[i]);
  }
 

  Clock deltaTime;
  Clock timer;
  timer.restart();


  IntRect backgroundRect = tilingCloudsSprite.getTextureRect();
  float secondTimer = 0.0f; 
  float movementSpeed = 150.0f;


  int mouseX = 0, mouseY = 0;
  int curMouseX = 0, curMouseY = 0;
  float offset = 100;
  bool growOffset = false, shrinkOffset = false;
  bool moving = false;
  float angle[3] = { 0, 0, 0 };
  bool showBackGroundSprite = false;

  while (window.isOpen())
  {  
	  float deltaTime = timer.restart().asSeconds();
	  while (window.pollEvent(evt)) {
		 switch (evt.type)
		  {
		  case sf::Event::MouseMoved:
			  curMouseX = mouseX;
			  curMouseY = mouseY;
			  mouseX = evt.mouseMove.x;
			  mouseY = evt.mouseMove.y;
			  moving = true;
			  break;
		  case sf::Event::KeyPressed:
			  switch (evt.key.code) {
			  case Keyboard::Num1: rotateAll = false; globalWindmilIndex = 0; rotatePoint[0] = 200; break;
			  case Keyboard::Num2: rotateAll = false; globalWindmilIndex = 1; rotatePoint[1] = 500; break;
			  case Keyboard::Num3: rotateAll = false; globalWindmilIndex = 2; rotatePoint[2] = 800; break;
			  case Keyboard::A:
			  case Keyboard::Num4: {
				  rotateAll = true;
				  float posX = 350;
				  for (int i = 0; i < 3; i++) {
					  bodyRects[i]->setPosition(posX, 450);
					  bodyRects[i]->rotate(360 - bodyRects[i]->getRotation());
					  posX += 250;
					  angle[i] = 0;
				  }
				  break;
			  }
			  case Keyboard::Space:
				  if (showBackGroundSprite) {
					  showBackGroundSprite = false;
					  music.stop();
				  }
				  else {
					  showBackGroundSprite = true;
					  music.play();
				  }					  
				  break;
			  }
			  break;
		  }
	  }

	
	 for (int i = 0; i < 3; i++) {
		 circleShapes[i]->rotate(90 * deltaTime);
	 }

	 if (curMouseX != mouseX && moving) {
		 float rotAngle = 0;
		 if (mouseX < curMouseX)
			 rotAngle = 0.3;
		 else
			 rotAngle = -0.3;

		 if (!rotateAll) {
			 bodyRects[globalWindmilIndex]->setOrigin(10.0f, (60.0f + 20.0f + 10.0f) / 2);
			 bodyRects[globalWindmilIndex]->rotate(rotAngle);
		 }
		 else {
			 for (int i = 0; i < 3; i++) {
				 bodyRects[i]->setOrigin(10.0f, (60.0f + 20.0f + 10.0f) / 2);
				 bodyRects[i]->rotate(rotAngle);
			 }
		 }
	 }

	 if (curMouseY != mouseY && moving && !rotateAll) {
		 if (angle[globalWindmilIndex] >= 180) 
			 angle[globalWindmilIndex] = 0;
		 if (mouseY < curMouseY)
		    angle[globalWindmilIndex] += 0.05;
		 else {
			 angle[globalWindmilIndex] -= 0.05;
		 }
		 bodyRects[globalWindmilIndex]->setPosition(rotatePoint[globalWindmilIndex] + 100 * cos(angle[globalWindmilIndex]), 300 + 100 * sin(angle[globalWindmilIndex]));
	 }

	 if (curMouseY != mouseY && moving && rotateAll) {
		 if (angle[globalWindmilIndex] >= 180)
			 angle[globalWindmilIndex] = 0;
		 angle[globalWindmilIndex] += 0.05;

		 bodyRects[0]->setPosition(500 + 100 * cos(angle[0]), 450 + 100 * sin(angle[0]));
		 bodyRects[1]->setPosition(bodyRects[0]->getPosition().x + 250 * cos(angle[1]), bodyRects[0]->getPosition().y + 250 * sin(angle[1]));
		 bodyRects[2]->setPosition(bodyRects[1]->getPosition().x + 250 * cos(angle[2]), bodyRects[1]->getPosition().y + 250 * sin(angle[2]));

		 if (mouseY < curMouseY) {
			 angle[0] += 0.02;
			 angle[1] += 0.06;
			 angle[2] += 0.09;
		 }
		 else {
			 angle[0] -= 0.02;
			 angle[1] -= 0.06;
			 angle[2] -= 0.09;
		 }
	 }

	 secondTimer += deltaTime;
	
	 sf::IntRect deltaRect = backgroundRect;
	 deltaRect.left = backgroundRect.left + (int)(movementSpeed * secondTimer);
	 tilingCloudsSprite.setTextureRect(deltaRect);

	
	 if (secondTimer > 1.0f)
	 {		
		 secondTimer -= 1.0f;
		 backgroundRect.left += (int)movementSpeed;
		 if (backgroundRect.left >= (float)cloudsTexture.getSize().x) {
			 backgroundRect.left -= cloudsTexture.getSize().x;
		 }
	 }


    window.clear(); 

	if (showBackGroundSprite)
	window.draw(tilingCloudsSprite);

	for (int i = 0; i < 3; i++) {
		bodies[i]->Draw(&window);
	}
	
    window.display();
	moving = false;
  }

  return 0;
}
