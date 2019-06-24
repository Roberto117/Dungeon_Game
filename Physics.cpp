#include "Physics.h"
#include "ScreenConstants.h"
#include "CreateObjects.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "LTextures.hpp"
#include "GlobalGameObjects.h"


//update the bullets
void updateBullets(Dungeon *dungeon,  double frameTimeDelta)
{



	//if there is player bulles in the dungeon handle them
	if ((bullets.totalLenght()) > 0)
	{
		Bullet *bullet;
		bool bulletDeleted = false;

		bullets.setStart();

		for (int i = 0; i < bullets.totalLenght(); i++)
		{
			bullets.getValue(bullet);

			bool bulletDeleted = false;
			// move the bullet
			bullet->move(frameTimeDelta);

			//if the bullet reched the edge of the screen delete it
			if ((bullet->getY() <= 20 || bullet->getY() >= SCREEN_HEIGHT - 20) || (bullet->getX() <= 20 || bullet->getX() >= SCREEN_WIDTH - 20))
			{
				//delet the bulled
				Bullet *tempBullet = new Bullet();
				bullets.remove(tempBullet);

				delete tempBullet;
				bulletDeleted = true;

				bullets.next();


				continue;

			}


			//check if bullet hits a wall

			if (checkPillarCollision(dungeon , *bullet))
			{
				Bullet *tempBullet = new Bullet();
				bullets.remove(tempBullet);

				delete tempBullet;
				bulletDeleted = true;

				bullets.next();


				continue;

			}

			//if there is mummy on the screen check for collision
			if (dungeon->mummys.totalLenght() > 0)
			{
				Mummy *currentMummy;

				dungeon->mummys.setStart();


				for (int i = 0; i < dungeon->mummys.totalLenght(); i++)
				{

					dungeon->mummys.getValue(currentMummy);

					if (checkCollision(*bullet, *currentMummy))
					{
						// if there is collision damage the mummy checked if killed
						Bullet *tempBullet;
						//check if the mummy is killed
						if (currentMummy->killed(bullet->getDamage()))
						{
							//if the mummys is killed delete teh mummy
							Mummy * tempMummy;
							dungeon->mummys.remove(tempMummy);
							delete tempMummy;
						}

						//remove the bullet
						bullets.remove(tempBullet);
						delete tempBullet;
						//move to the next bullet on the list
						bullets.next();

						bulletDeleted = true;
						break;

					}
					// move the the next mummy
					dungeon->mummys.next();
				}
				//delete mummy pointer
				currentMummy = nullptr;
				delete currentMummy;

			}
			if (bulletDeleted) continue;
			//if there is slimes on the screen check for collison.
			if (dungeon->slimes.totalLenght() > 0)
			{
				Slime * currentSlime;

				dungeon->slimes.setStart();


				for (int i = 0; i < dungeon->slimes.totalLenght(); i++)
				{
					//if there is collison damage the slime and checked if killed
					dungeon->slimes.getValue(currentSlime);
					if (checkCollision(*bullet, *currentSlime))
					{
						//
						Bullet *tempBullet;

						//check if the slime is killed
						if (currentSlime->killed(bullet->getDamage()))
						{
							//if killed remove it from the list.
							Slime *tempSlime;
							dungeon->slimes.remove(tempSlime);
							delete tempSlime;
						}
						// remove the buller from the list/
						bullets.remove(tempBullet);
						delete tempBullet;
						//move to the next bullet
						bullets.next();


						bulletDeleted = true;
						break;
					}
					//move to the next bullet

					dungeon->slimes.next();
				}
				//delete the slime pointer.
				currentSlime = nullptr;
				delete currentSlime;
			}
			if (bulletDeleted) continue;
			//if there is pharos in the dungeon check for collison
			if (dungeon->pharaohs.totalLenght() > 0)
			{

				Pharaoh *currentPharaoh;
				dungeon->pharaohs.setStart();


				for (int i = 0; i < dungeon->pharaohs.totalLenght(); i++)
				{
					dungeon->pharaohs.getValue(currentPharaoh);
					if (checkCollision(*bullet, *currentPharaoh))
					{
						//if there is collison damage the paharo and check if killed
						Bullet *tempBullet;

						if (currentPharaoh->killed(bullet->getDamage()))
						{
							//if killed remove the pharao from the list
							Pharaoh * tempPharaoh;
							dungeon->pharaohs.remove(tempPharaoh);
							delete tempPharaoh;
						}

						//remove the buller from the list
						bullets.remove(tempBullet);
						delete tempBullet;
						bullets.next();
						bulletDeleted = true;
						break;
					}
					dungeon->pharaohs.next();
				}
			}
			//if the bullet has been deleted continue to the next list.
			if (bulletDeleted) continue;


			// if there is crates on the screen check for collison
			if (dungeon->crates.totalLenght() > 0)
			{

				Crate *currentCrate;

				dungeon->crates.setStart();


				for (int j = 0; j < dungeon->crates.totalLenght(); ++j)
				{
					dungeon->crates.getValue(currentCrate);
					if (checkCollision(*bullet, *currentCrate))
					{
						//if there is collison remove the create and create a new consumable
						Bullet *tempBullet;
						Crate *tempCrate;
						Consumable *newConsumable = new Consumable();

						bullets.remove(tempBullet);
						dungeon->crates.remove(tempCrate);

						//create a new consumable where the crate was located
						createConsumable(newConsumable, tempCrate->getX(), tempCrate->getY(), modelHealthBox, modelAmmoBox);
						//append the consumable to the list
						dungeon->consumables.append(newConsumable);


						//delete the pointer and objects
						newConsumable = nullptr;
						delete newConsumable;
						delete tempCrate;
						delete tempBullet;

						break;
					}

					//move to the next crate on the list
					dungeon->crates.next();
				}
				//delete the pointer
				currentCrate = nullptr;
				delete currentCrate;
			}
			//move to the next bullet on the list
			bullets.next();

		}
		//delet the pointer
		bullet = nullptr;
		delete bullet;
	}


}

//update the player.
void updatePlayer(Dungeon *dungeon, double frameTimeDelta )
{
	//check if the effect on player can be removed
	//move the player

	sudoDungeoneer.copyMoves(dungeoneer);

	sudoDungeoneer.move(frameTimeDelta);

	if (!checkPillarCollision(dungeon , sudoDungeoneer))
	{
		dungeoneer.move(frameTimeDelta);
	}
	else if (dungeoneer.pushed)
	{
		dungeoneer.pushed = false;

	}

	//set the angel that the player is pointing at based on the mouse position
	float angle = atan2(dungeoneer.getY() - mouseY, dungeoneer.getX() - mouseX);


	//input the angle into the player class.
	dungeoneer.setRotation(angle);

	dungeoneer.removeEffect();

}

//update all mummy objects.
void updateMummys(Dungeon *dungeon, double frameTimeDelta)
{
	Player *player = &dungeoneer;
	//do the loop while there is objects to handle
	if (dungeon->mummys.totalLenght() > 0)
	{

		Mummy *currentMummy;

		dungeon->mummys.setStart();

		for (int i = 0; i < dungeon->mummys.totalLenght(); i++)
		{

			dungeon->mummys.getValue(currentMummy);

			//check if the mummy should move if yes then move
			if (currentMummy->isMoving())
			{
				//check if there is immint impcat if there is then stop the mummy from moving and reset the timer.
				if (currentMummy->checkIfJustStartedMoving())
				{
					sudoMummy.copyMoves(*currentMummy);
					while (!sudoMummy.sudoMove(frameTimeDelta))
					{
						if (checkPillarCollision(dungeon, sudoMummy))
						{
							currentMummy->resetTimer();
							sudoMummy.resetTimer();
							break;
						}
					}


				}
				else
				{
					currentMummy->move(frameTimeDelta);
				}
				// move the mummy

			}
			// if the mummy is not moving it will track the postion of the player this position is teh postion it will move to once it is time to move
			else
			{
				// get the angle pointing to the player from the current mummy
				float angle = atan2(dungeoneer.getY() - currentMummy->getY(), dungeoneer.getX() - currentMummy->getX());
				//give the angle to the mummy
				currentMummy->setRotation(angle);

				//give the postion of the player to the mummy the mummy wont stop movin until collison with the player or if arrive at this given postion.
				currentMummy->setTarget(dungeoneer.getX(), dungeoneer.getY());
			}

			// values to be used if the player collides with the current object

			GLfloat pushX;
			GLfloat pushY;

			bool right, down;

			if (checkCollision(*player, *currentMummy, pushX, pushY, right, down))
			{
				// if the player collided with object, damage the player and push the player to the opposite the direction of the object the speed and range pushed is based on the objects strengh
				dungeoneer.killed(currentMummy->getDamage());
				dungeoneer.pushedDown = down;
				dungeoneer.pushedRight = right;
				dungeoneer.gotPushed(currentMummy->getStrenght() * 4, currentMummy->getStrenght());
				currentMummy->resetTimer();

			}


			dungeon->mummys.next();


		}
		//delete the mummy object
		currentMummy = nullptr;
		delete  currentMummy;
	}

	//delete player pointer
	player = nullptr;

	delete player;


}

//updateall slime objects
void updateSlimes(Dungeon *dungeon, double frameTimeDelta) {
	Player *player = &dungeoneer;
	Slime sudoSlime;
	// if ther is slimes handle them
	if (dungeon->slimes.totalLenght() > 0)
	{
		//pointer used to get the addres of the current object to be handled

		Slime *currentSlime;

		//set the double linked list to the start.

		dungeon->slimes.setStart();

		// values to be used if the player collides with the current object
		GLfloat pushX;
		GLfloat pushY;

		bool right, down;

		//do the loop while there is objects to handle
		for (int i = 0; i < dungeon->slimes.totalLenght(); i++)
		{
			//get the value of the next object in the list.
			dungeon->slimes.getValue(currentSlime);


			//check if teh current slime should drop goo
			if (currentSlime->dropGoo())
			{

				//create a new trap which will be of type goo
				Trap *newTrap = new Trap();
				createdGoo(newTrap, currentSlime->getX(), currentSlime->getY(), modelGoo);

				//append the trap to the list
				dungeon->traps.append(newTrap);

				//delete the trap pointer
				newTrap = nullptr;
				delete newTrap;



			}

			//move the slime
			sudoSlime.copyMoves(*currentSlime);
			sudoSlime.move(frameTimeDelta);
			//check if the player collides with the current object
			
			if (!checkPillarCollision(dungeon, sudoSlime))currentSlime->move(frameTimeDelta);
			else currentSlime->resetTimer();
			
			if (checkCollision(*player, *currentSlime, pushX, pushY, right, down))
			{

				// if the player collided with object, damage the player and push the player to the opposite the direction of the object the speed and range pushed is based on the objects strengh
				dungeoneer.killed(currentSlime->getDamage());
				dungeoneer.pushedDown = down;
				dungeoneer.pushedRight = right;
				dungeoneer.gotPushed(currentSlime->getStrenght() * 4, currentSlime->getStrenght());

				//reset the slime timer
				currentSlime->resetTimer();
			}

			//move the the next object on the list
			dungeon->slimes.next();
		}

		//delete teh slime pointer
		currentSlime = nullptr;
		delete currentSlime;
	}


	//delete player pointer
	player = nullptr;

	delete player;


}

//update all pharaoh objects.
void updatePharaoh(Dungeon *dungeon, double frameTimeDelta)
{
	Player *player = &dungeoneer;
	// if there is pharaos in the curren dungeon update their movement.
	if (dungeon->pharaohs.totalLenght() > 0)
	{
		//pointer that will be used to store the address of the current pharaoh that we are handling
		Pharaoh *currentPharaoh;
		//set the double linke list to the start.
		dungeon->pharaohs.setStart();

		//do a loop while there is still pharaohs that have not been handled
		for (int i = 0; i < dungeon->pharaohs.totalLenght(); i++)
		{
			//get the address of the next pharaoh to handle
			dungeon->pharaohs.getValue(currentPharaoh);

			// values to be used if the player collides with a pharao
			GLfloat pushX;
			GLfloat pushY;
			bool right, down;
			//check if the player collides with a pharaoh
			if (checkCollision(*player, *currentPharaoh, pushX, pushY, right, down))
			{
				// if the player collided with object, damage the player and push the player to the opposite the direction of the object the speed and range pushed is based on the objects strengh
				dungeoneer.killed(currentPharaoh->getDamage());
				dungeoneer.pushedDown = down;
				dungeoneer.pushedRight = right;
				dungeoneer.gotPushed(currentPharaoh->getStrenght() * 4, currentPharaoh->getStrenght());

			}
			//check if is time for the pharaoh to shoot
			if (currentPharaoh->timeToShoot())
			{
				//if is time to shoot create bullet for every 30 degrees around the pharaph
				Bullet *newBullet;

				float i = -180;
				while (i <= 180)
				{
					float angle = 0;
					if (i != 0)
					{
						angle = i * (PI / 180);
					}

					newBullet = new Bullet();
					createPharaohBullet(newBullet, currentPharaoh->getX(), currentPharaoh->getY(), angle, modelPharaohBullet);
					pharaohBullets.append(newBullet);
					i += 45;
				}


				//reset the timer of the pharoh so that it can wait again before shooting
				currentPharaoh->resetTimer();
				//delete the bullet pointer
				newBullet = nullptr;
				delete newBullet;
			}
			//move to the next pharoh to handle
			dungeon->pharaohs.next();

		}
		//delete the pharaoh pointer
		currentPharaoh = nullptr;
		delete currentPharaoh;
	}


	//delete player pointer
	player = nullptr;

	delete player;


}

//update all pharoh bullet objects.
void updatePharaohBullets(Dungeon *dungeon,double frameTimeDelta) {
	Player *player = &dungeoneer;
	//if there is pharaoh bullets in the dungeon handle them
	if (pharaohBullets.totalLenght() > 0)
	{
		//pointer to be use to handle the current bullet
		Bullet *bullet;
		//boolean value used to check if the bulled has been deleted
		bool bulletDeleted = false;

		pharaohBullets.setStart();

		for (int i = 0; i < pharaohBullets.totalLenght(); i++)
		{
			bool bulletDeleted = false;
			pharaohBullets.getValue(bullet);

			// move the bullet
			bullet->move(frameTimeDelta);

			// if the bullet reached the edges of the screen deleted it
			if ((bullet->getY() <= 20 || bullet->getY() >= SCREEN_HEIGHT - 20) || (bullet->getX() <= 20 || bullet->getX() >= SCREEN_WIDTH - 20))
			{

				//remove the bulled from the list
				Bullet *tempBullet;
				pharaohBullets.remove(tempBullet);

				//delete teh bullet
				delete tempBullet;
				bulletDeleted = true;
				//move to the next bullet.
				pharaohBullets.next();

				// do another round of the loop
				continue;

			}

			//check if bullet hits a wall

			if (checkPillarCollision(dungeon, *bullet))
			{
				Bullet *tempBullet = new Bullet();
				pharaohBullets.remove(tempBullet);

				delete tempBullet;
				bulletDeleted = true;

				bullets.next();


				continue;

			}
			GLfloat pushX;
			GLfloat pushY;

			bool right, down;

			if (checkCollision(*player, *bullet, pushX, pushY, right, down))
			{
				//push the player to the oppisiote direection if collision occur and damage the player.
				dungeoneer.killed(modelPharaohBullet.getDamage());
				dungeoneer.pushedDown = down;
				dungeoneer.pushedRight = right;
				dungeoneer.gotPushed(80.f, 20.f);

				//delte the bullet
				Bullet *tempBullet = new Bullet();
				pharaohBullets.remove(tempBullet);

				delete tempBullet;
				bulletDeleted = true;

				//move to the next buller
				pharaohBullets.next();


				continue;
			}
			//move to the next bullet
			pharaohBullets.next();

		}

		//delete the bullet pointer
		bullet = nullptr;
		delete bullet;
	}


	//delete player pointer
	player = nullptr;

	delete player;


}



//update all consumables.
void updateConsumables(Dungeon *dungeon)
{
	Player *player = &dungeoneer;
	//if there are consumables on the current dungeon handle them
	if (dungeon->consumables.totalLenght() > 0)
	{
		//pointer used to get the addres of the current object to be handled
		Consumable *currentConsumable;
		//set the double linked list to the start.
		dungeon->consumables.setStart();


		//do the loop while there is objects to handle
		for (int i = 0; i < dungeon->consumables.totalLenght(); i++)
		{
			//get the value of the next object in the list.
			dungeon->consumables.getValue(currentConsumable);

			//check if the object collides with the player
			if (checkCollision(*player, *currentConsumable))
			{
				//creates a temp object to delete the object
				Consumable *tempConsumable;

				//remove the current object from the list
				dungeon->consumables.remove(tempConsumable);

				//the player consumes the object the consumable class will handle what to do with the player depending on the type of consumable it is if is an ammo box it will add ammo if it a health box it will add health
				tempConsumable->consume(dungeoneer);
				//delete the consumable and break out of the loop
				delete tempConsumable;
				break;
			}
			//go to the next consumable.
			dungeon->consumables.next();
		}

		//delete the pointer

		currentConsumable = nullptr;
		delete currentConsumable;

	}

	//delete player pointer
	player = nullptr;

	delete player;



}
//update all traps.
void updateTraps(Dungeon *dungeon) {
	Player *player = &dungeoneer;
	//if there is traps handle them.
	if (dungeon->traps.totalLenght() > 0)
	{
		//get the value of the next object in the list.

		Trap  *currentTrap;

		//set the double linked list to the start.
		dungeon->traps.setStart();

		//check if the player collides with the current object

		for (int i = 0; i < dungeon->traps.totalLenght(); i++)
		{
			dungeon->traps.getValue(currentTrap);

			//check if the player collides with the current object
			if (checkCollision(*currentTrap, *player))
			{
				// the trap class will handle that will happen if the object collides with the player for example if is goo then the player is slowed
				currentTrap->activate(player);

			}
			// go the next object
			dungeon->traps.next();
		}

	}


	//delete player pointer
	player = nullptr;

	delete player;



}

void checkCollitionWithDoor()
{
	//player objer that points at the player adress


	Player *player = &dungeoneer;





	//check if the player collides with the doors if yes then move to the desired dungeon

	// check collison with the top door
	if (checkCollision(*player, DOORS[0]))
	{
		//check if edge exist
		if (dungeons->topIsEdge())
		{
			//update the current dungeons enemies creates and consumables this will update their health, and position
			updateDungeon();
			//move to the top edge
			dungeons->moveTop();

			//get the next dungeons enemies, crates and consumables store them on Lutils lists for objects
			moveDungeon();
			//move the player to the bottom of the screen
			dungeoneer.setCoordY(SCREEN_HEIGHT - DOORS[0].getHeight() * 3);

		}
	}
	//check collison with bottom door
	else if (checkCollision(*player, DOORS[1]))
	{
		//check if edge exist
		if (dungeons->bottomIsEdge())
		{
			//update the current dungeons enemies creates and consumables this will update their health, and position
			updateDungeon();
			//move to the bottom edge
			dungeons->moveBottom();

			//get the next dungeons enemies, crates and consumables store them on Lutils lists for objects
			moveDungeon();

			//set the player postion to the top of the screen
			dungeoneer.setCoordY(DOORS[0].getHeight() * 3);
		}
	}
	//check collision with the ledt door
	else  if (checkCollision(*player, DOORS[2]))
	{
		//check edge exist
		if (dungeons->leftIsEdge())
		{
			//update the current dungeons enemies creates and consumables this will update their health, and position
			updateDungeon();
			// move to the left edge
			dungeons->moveLeft();
			//get the next dungeons enemies, crates and consumables store them on Lutils lists for objects
			moveDungeon();

			//move to the right of the screen
			dungeoneer.setCoordX(SCREEN_WIDTH - DOORS[2].getWidth() * 3);

		}
	}

	//check collison with the right door
	else  if (checkCollision(*player, DOORS[3]))
	{
		//check if edge exist
		if (dungeons->rightIsEdge())
		{
			//update the current dungeons enemies creates and consumables this will update their health, and position
			updateDungeon();
			//move to the right edge
			dungeons->moveRight();
			//get the next dungeons enemies, crates and consumables store them on Lutils lists for objects
			moveDungeon();

			//set the player cordinate to the left of the screen
			dungeoneer.setCoordX(DOORS[2].getWidth() * 3);
		}
	}



	//delete player pointer
	player = nullptr;

	delete player;


}


//update the dungeon before moving to the next dungeon
void updateDungeon()
{
	Dungeon *currentDungeon;


	dungeons->getValue(currentDungeon);
	//reset the timer of all enemies in the dungeon
	if (currentDungeon->mummys.totalLenght() > 0) resetMummyTimer(currentDungeon);
	if (currentDungeon->slimes.totalLenght() > 0) resetSlimeTimer(currentDungeon);
	if (currentDungeon->pharaohs.totalLenght() > 0) resetPharaohTimer(currentDungeon);
	deleteBullets();


	//udpate the objects inside the dungeon to their new health and position and if they were killed or not

	currentDungeon = nullptr;

	delete currentDungeon;
}

//move to the next dungeon
void moveDungeon()
{
	Dungeon *nextDungeon;

	dungeons->getValue(nextDungeon);
	currentLocation = dungeons->getPos();

	//reset the timer on all enemies
	if (nextDungeon->mummys.totalLenght() > 0) resetMummyTimer(nextDungeon);
	if (nextDungeon->slimes.totalLenght() > 0) resetSlimeTimer(nextDungeon);
	if (nextDungeon->pharaohs.totalLenght() > 0) resetPharaohTimer(nextDungeon);

	nextDungeon = nullptr;
	delete nextDungeon;
}


void deleteBullets()
{
	Bullet *temp;
	if (bullets.totalLenght() > 0)
	{
		bullets.setStart();
		
		while (bullets.remove(temp))
		{
			delete temp;
		}
	}

	if (pharaohBullets.totalLenght() > 0)
	{
		pharaohBullets.setStart();
		while (pharaohBullets.remove(temp))
		{
			delete temp;
		}
	}


}
//reset the times on all mummies on the list
void resetMummyTimer(Dungeon *dungeon)
{
	dungeon->mummys.setStart();

	Mummy *currentMumy;
	for (int i = 0; i < dungeon->mummys.totalLenght(); i++)
	{
		dungeon->mummys.getValue(currentMumy);
		currentMumy->resetTimer();
		dungeon->mummys.next();

	}


	currentMumy = nullptr;
	delete  currentMumy;
}
//resets the times for all slimes on the list
void resetSlimeTimer(Dungeon *dungeon)
{
	dungeon->slimes.setStart();

	Slime *currentSlime;
	for (int i = 0; i < dungeon->slimes.totalLenght(); i++)
	{
		dungeon->slimes.getValue(currentSlime);
		currentSlime->resetTimer();
		dungeon->slimes.next();
	}
}

//reset all pharohs on the list
void resetPharaohTimer(Dungeon *dungeon)
{
	dungeon->pharaohs.setStart();
	Pharaoh * currentPharaoh;

	for (int i = 0; i < dungeon->pharaohs.totalLenght(); i++)
	{
		dungeon->pharaohs.getValue(currentPharaoh);
		currentPharaoh->resetTimer();
		dungeon->pharaohs.next();
	}
}

//check if an object collides with a pillar
bool checkPlayerPillarCollision(Dungeon *dungeon)
{
	if (dungeon->pillars.totalLenght() > 0)
	{

		dungeon->pillars.setStart();
		Object * currentPillar;

		Player *player = &sudoDungeoneer;
		for (int i = 0; i < dungeon->pillars.totalLenght(); i++)
		{
			dungeon->pillars.getValue(currentPillar);

			GLfloat pushX;
			GLfloat pushY;
			bool right, down;
			//check if the player collides with a pharaoh
			if (checkCollision(*player, *currentPillar, pushX, pushY, right, down))
			{
				return true;
			}

			dungeon->pillars.next();
		}



		player = nullptr;
		currentPillar = nullptr;
		delete  player;
		delete currentPillar;
	}


	return false;

}







bool checkPillarCollision(Dungeon *dungeon, Object &a)
{
	if (dungeon->pillars.totalLenght() > 0)
	{

		dungeon->pillars.setStart();
		Object * currentPillar;
		for (int i = 0; i < dungeon->pillars.totalLenght(); i++)
		{
			dungeon->pillars.getValue(currentPillar);


			//check if the object collides with a pharaoh
			if (checkCollision(a, *currentPillar))
			{
				return true;
			}

			dungeon->pillars.next();
		}




		currentPillar = nullptr;
		delete currentPillar;
	}


	return false;

}

//check the collison betwen to object we use this function if we do no need for the object to move away from each other afeter collision
bool checkCollision(Object a, Object b)
{

	//using Axis-Align Bounding Box to check if to objects collide if they do return true if not return false
	if (abs(a.getX() - b.getX()) < a.getWidth() + b.getWidth() && abs(a.getY() - b.getY()) < a.getHeight() + b.getHeight())
	{

		return true;
	}
	return false;

}
//check collison between to object we use this function if after collision we desire for the objects not to touch eachother

bool checkCollision(Object a, Object b, GLfloat &x, GLfloat &y, bool &right, bool &down)
{

	//using AABB to check if to objects collide if they do return true , return and  x,y position that will not have both object colliding and return where an object should be pushed to be pushed away from the other object if not return false
	if (abs(a.getX() - b.getX()) < a.getWidth() + b.getWidth() && abs(a.getY() - b.getY()) < a.getHeight() + b.getHeight())
	{


		//check where the object a  should move to move away from the object b

		// object a x cordinates is smaller than object b then the object should move to the right  else the object should move right

		if (a.getX() < b.getX())
		{
			right = false;

			//get an x cordinate away from the other object b
			x = (b.getX() - b.getWidth()) - (a.getX() + a.getWidth());

		}
		else
		{
			right = true;

			x = (b.getX() + b.getWidth()) - (a.getX() - a.getWidth());


		}

		//if object a y cordinate is smaller than object b x cordinate then object a should move down else object a should move up
		if (a.getY() < b.getY())
		{
			down = false;
			y = (b.getY() - b.getHeight()) - (a.getY() + a.getHeight());

		}
		else
		{
			down = true;

			y = (b.getY() + b.getHeight()) - (a.getY() - a.getHeight());
		}



		x = a.getX() + x;

		y = a.getY() + y;

		return true;
	}
	return false;
}



