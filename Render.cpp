#include "Render.h"
#include "ScreenConstants.h"
#include "GlobalGameObjects.h"

// translate the modelView
void translateModelView(GLfloat x, GLfloat y, GLfloat z)
{
	//translate the modelView to the given cordinates
	mModelView = glm::translate<GLfloat>(glm::vec3(x, y, z));
}
//rotate the model view to the given cordinates
void rotateModelView(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	mModelView = glm::rotate<GLfloat>(mModelView, angle, glm::vec3(x, y, z));
}
//translate the projection matrix to the given cordinates
void translateProjectionView(GLfloat x, GLfloat y, GLfloat z)
{
	mProjection = glm::translate<GLfloat>(glm::vec3(x, y, z));
}
//scale the model view to the given scale
void scaleModelView(GLfloat x, GLfloat y, GLfloat z)
{
	glm::mat4 m = glm::translate(glm::vec3(camera.getX(), camera.getY(), 0.f));
	mModelView *= glm::scale<GLfloat>(m, glm::vec3(x, y, z));
}

//scale the projection view to the given scale
void scaleProjection(GLfloat x, GLfloat y, GLfloat z)
{
	glm::mat4 m = glm::translate(glm::vec3(camera.getX(), camera.getY(), 0.f));
	mProjection *= glm::scale<GLfloat>(m, glm::vec3(x, y, z));

}


//render the bullets on the list
void renderBullets()
{
	if ((bullets.rightLenght() + bullets.leftLenght()) > 0)
	{
		Bullet *bullet;

		bullets.setStart();

		bullets.getValue(bullet);
		for (int i = 0; i < (bullets.leftLenght() + bullets.rightLenght()); i++)
		{
			//translate the model view to the bullet position update the shader program
			translateModelView(bullet->getX(), bullet->getY(), 0.f);

			rectangleProgram.updateModelView(mModelView);

			//draw the bullet
			modelBullet.drawObject();

			bullets.next();


			//move to the next bullet
			bullets.getValue(bullet);


		}

		bullet = nullptr;

		delete bullet;
	}
}

//render the player
void renderPlayer(GLfloat scale) {
	//move to rendering position
	translateModelView(dungeoneer.getX() * scale, dungeoneer.getY() * scale, 0.f);
	scaleModelView(scale, scale, 0.f);
	rotateModelView(dungeoneer.getRotation(), 0, 0, 1);

	triangleProgram.updateModelView(mModelView);

	dungeoneer.drawObject();

}

//render all the mummies
void renderMummys(Dungeon * dungeon) {

	if (dungeon->mummys.totalLenght() > 0)
	{
		Mummy *currentMummy;

		dungeon->mummys.setStart();


		for (int i = 0; i < dungeon->mummys.totalLenght(); i++)
		{
			dungeon->mummys.getValue(currentMummy);
			translateModelView(currentMummy->getX(), currentMummy->getY(), 0.f);
			rectangleProgram.updateModelView(mModelView);

			modelMummy.drawObject();

			dungeon->mummys.next();
		}


		currentMummy = nullptr;
		delete currentMummy;

	}

}

//render slimes
void renderSlimes(Dungeon * dungeon) {
	if (dungeon->slimes.totalLenght() > 0)
	{


		Slime *currentSlime;

		dungeon->slimes.setStart();

		for (int i = 0; i < dungeon->slimes.totalLenght(); i++)
		{
			dungeon->slimes.getValue(currentSlime);

			//update the center point of the object, translate to position and update the shader program
			circleProgram.updateCenterPoint(currentSlime->getX(), currentSlime->getY());
			translateModelView(currentSlime->getX(), currentSlime->getY(), 0.f);
			circleProgram.updateModelView(mModelView);


			//draw the object
			currentSlime->drawObject();
			//modelSlime.drawObject();
			dungeon->slimes.next();

		}

		currentSlime = nullptr;
		delete currentSlime;
	}
}

//render the pharaoh object
void renderPharaoh(Dungeon *dungeon)
{
	if (dungeon->pharaohs.totalLenght() > 0)
	{
		Pharaoh * currentPharaoh;
		dungeon->pharaohs.setStart();
		for (int i = 0; i < dungeon->pharaohs.totalLenght(); i++)
		{
			dungeon->pharaohs.getValue(currentPharaoh);
			circleProgram.updateCenterPoint(currentPharaoh->getX(), currentPharaoh->getY());
			translateModelView(currentPharaoh->getX(), currentPharaoh->getY(), 0.f);
			circleProgram.updateModelView(mModelView);
			currentPharaoh->drawObject();
			dungeon->pharaohs.next();
		}

		currentPharaoh = nullptr;
		delete currentPharaoh;
	}

}

//render the pharaoh bullets
void renderPharaohBullets()
{

	if (pharaohBullets.totalLenght() > 0)
	{
		Bullet *bullet;

		pharaohBullets.setStart();

		pharaohBullets.getValue(bullet);
		for (int i = 0; i < pharaohBullets.totalLenght(); i++)
		{
			translateModelView(bullet->getX(), bullet->getY(), 0.f);

			rectangleProgram.updateModelView(mModelView);

			modelPharaohBullet.drawObject();

			pharaohBullets.next();

			pharaohBullets.getValue(bullet);


		}

		bullet = nullptr;

		delete bullet;

	}

}

//render the crates
void renderCrates(Dungeon *dungeon)
{

	if (dungeon->crates.rightLenght() + dungeon->crates.leftLenght() > 0)
	{
		Crate *crate;

		dungeon->crates.setStart();


		for (int i = 0; i < dungeon->crates.rightLenght() + dungeon->crates.leftLenght(); ++i)
		{
			dungeon->crates.getValue(crate);

			translateModelView(crate->getX(), crate->getY(), 0.f);

			rectangleProgram.updateModelView(mModelView);

			modelCrate.drawObject();

			dungeon->crates.next();
		}

		crate = nullptr;

		delete crate;

	}
}

//render the consumables
void renderConsumables(Dungeon *dungeon)
{

	if (dungeon->consumables.totalLenght() > 0)
	{
		Consumable *currentConsumable;

		dungeon->consumables.setStart();

		for (int i = 0; i < dungeon->consumables.totalLenght(); i++)
		{
			dungeon->consumables.getValue(currentConsumable);
			translateModelView(currentConsumable->getX(), currentConsumable->getY(), 0.f);
			rectangleProgram.updateModelView(mModelView);

			if (currentConsumable->getType() == modelHealthBox.getType()) modelHealthBox.drawObject();

			else modelAmmoBox.drawObject();

			dungeon->consumables.next();
		}
	}

}
//render traps
void renderTraps(Dungeon *dungeon)
{
	if (dungeon->traps.totalLenght() > 0)
	{

		Trap *currentTrap;
		dungeon->traps.setStart();
		for (int i = 0; i < dungeon->traps.totalLenght(); i++)
		{
			dungeon->traps.getValue(currentTrap);
			circleProgram.updateCenterPoint(currentTrap->getX(), currentTrap->getY());
			translateModelView(currentTrap->getX(), currentTrap->getY(), 0.f);
			circleProgram.updateModelView(mModelView);

			currentTrap->drawObject();
			dungeon->traps.next();
		}

		currentTrap = nullptr;
		delete currentTrap;
	}
}


void renderPillars(Dungeon *dungeon)
{
	if (dungeon->pillars.totalLenght() > 0)
	{
		Object * currentPillar;
		dungeon->pillars.setStart();

		for (int i = 0; i < dungeon->pillars.totalLenght(); i++)
		{
			dungeon->pillars.getValue(currentPillar);
			translateModelView(currentPillar->getX(), currentPillar->getY(), 0.f);
			rectangleProgram.updateModelView(mModelView);
			modelPillar.drawObject();

			dungeon->pillars.next();
		}
	}

}

//render the walls, this functions will also be used to render the map so we use a scaling variable for when rendering the map
void renderWalls(GLfloat x, GLfloat y, GLfloat scale)
{
	for (int i = 0; i < 4; i++)
	{
		//translate to the model view scale the cordinates if need scaling, scale the matrix and update the shader program
		translateModelView((WALLS[i].getX() * scale) + (x * scale), (WALLS[i].getY() * scale) + (y * scale), 0.f);
		scaleModelView(scale, scale, 0.f);
		rectangleProgram.updateModelView(mModelView);


		// if the i index is smalle than two then we draw a vertical wall, if i index is bigger we draw a vertical door
		if (i < 2) WALLS[0].drawObject();

		else WALLS[2].drawObject();


	}
}

//render the doors
void renderDoors()
{
	//we check if the dungeong has an edge at the top,bottom, left and right if an edge exist we draw a door in that postion
	if (dungeons->topIsEdge())
	{
		translateModelView(DOORS[0].getX(), DOORS[0].getY(), 0.f);
		rectangleProgram.updateModelView(mModelView);

		DOORS[0].drawObject();

	}

	if (dungeons->bottomIsEdge())
	{
		translateModelView(DOORS[1].getX(), DOORS[1].getY(), 0.f);
		rectangleProgram.updateModelView(mModelView);

		DOORS[0].drawObject();
	}
	if (dungeons->leftIsEdge())
	{
		translateModelView(DOORS[2].getX(), DOORS[2].getY(), 0.f);
		rectangleProgram.updateModelView(mModelView);

		DOORS[2].drawObject();
	}
	if (dungeons->rightIsEdge())
	{
		translateModelView(DOORS[3].getX(), DOORS[3].getY(), 0.f);
		rectangleProgram.updateModelView(mModelView);

		DOORS[2].drawObject();
	}


}

//render the amoount of ammo the player has
void renderAmmoCount()
{

	GLfloat y = 0;
	GLfloat x = 0;

	//if the player has ammo render the amount
	for (int i = 0; i < dungeoneer.getAmmo(); i++)
	{

		//start at the bottom of the screen if there is more than one bullet  slowly move to 1.5 the modelBullets with so that the objects won't touch each other, if i has reached more than 15  go up by 1.5 the model bullets width every time the bullet count goes past 15 more
		if (i % 15 == 0)
		{
			x = SCREEN_WIDTH * 0.1;
			y = SCREEN_HEIGHT * 0.9 - modelBullet.getHeight() * 3 * (1 + i / 15);
		}
		translateModelView(x + modelBullet.getWidth() * 3 * (i % 15), y, 0.f);
		rectangleProgram.updateModelView(mModelView);

		modelBullet.drawObject();
	}
}

//render the health
void renderHealth()
{
	//render the health bar for every i index draw the next health bar 1.5 the width of a health bar away from the last bar in order that they wont touch and get confused
	for (int i = 0; i < dungeoneer.getHealth(); i++)
	{
		translateModelView(healthBar.getX() - (healthBar.getWidth() * 3 * i), healthBar.getY(), 0.f);

		rectangleProgram.updateModelView(mModelView);

		healthBar.drawObject();
	}
}

//render the map using breath first search
void renderMap()
{
	// start variable which we will use to check which vertice we are checking it's edges a last value where we will store the edge that this vertice is connected too
	int start = currentLocation;
	int last = currentLocation;

	GLfloat scale = 0.1f;



	//2 arrays which we will store the postion every dungeon should be
	GLfloat* dungeonX = new GLfloat[dungeons->getSize()];
	GLfloat* dungeonY = new GLfloat[dungeons->getSize()];

	//this variable we will use to handle the edges of a vertice
	int next;

	// boolean variables that will return if a vertice has a top,bottom,left and right edge
	bool right, left, bottom, top;

	//we will save the curren vertice postion here
	GLfloat x = 0;
	GLfloat y = 0;

	/*location of the edge will be store here
	 if 0 = TOP
	 if 1 = BOTTOM
	 if 2 = LEFT
	 if 3 = RIGHT
	 */
	int location;


	//reset the queue list
	queue->reset();

	//remove all the postions in th double link list lastPos
	if (lastPos->totalLenght() != 0)
	{
		lastPos->setStart();
		while (lastPos->remove(last));

		last = currentLocation;
	}



	//initiate the queue
	queue->enqueue(start);

	//mark the first dungeon visitied
	dungeons->setMark(start, VISITED);
	rectangleProgram.bind();
	renderWalls(0, 0, scale);
	//check for edges location
	dungeons->edgesLocations(start, top, bottom, left, right);
	renderDoors(top, bottom, left, right, x, y, scale);
	renderPlayer(scale);


	//set the cordinate of the first dungeon
	dungeonX[start] = 0;
	dungeonY[start] = 0;

	//do while teh queue is not empty
	while (queue->lenght() != 0)
	{
		//set the list at the start
		lastPos->setStart();
		//deque the vertice to handle
		queue->dequeue(start);
		//if is the first vertice dont update position
		if (last != start)
		{
			//get the value of the last position
			lastPos->getValue(last);
			location = dungeons->edgeLocation(last, start);
			//while the last position does not match with teh current vertice do the loop to find the last position
			while (location == -1)
			{
				lastPos->next();
				lastPos->getValue(last);
				location = dungeons->edgeLocation(last, start);
			}

			//depending on the next location update the cordinates

			switch (location)
			{
			case TOP:
				y = dungeonY[last] - SCREEN_HEIGHT;
				x = dungeonX[last];
				break;
			case BOTTOM:
				y = dungeonY[last] + SCREEN_HEIGHT;
				x = dungeonX[last];
				break;
			case LEFT:
				y = dungeonY[last];
				x = dungeonX[last] - SCREEN_WIDTH;
				break;
			case RIGHT:
				y = dungeonY[last];
				x = dungeonX[last] + SCREEN_WIDTH;
				break;
			}


			//update the cordinates of this vertice
			dungeonX[start] = x;
			dungeonY[start] = y;
		}
		//get the first edge of the vertice
		next = dungeons->first(start);




		do
		{
			//vertice has been visited skip it
			if (dungeons->getMark(next) == UNVISITED)
			{
				//mark vertice as visited
				dungeons->setMark(next, VISITED);
				//enqueue teh vertice for later handling
				queue->enqueue(next);

				//get the edges of the vertice
				location = dungeons->edgeLocation(start, next);
				dungeons->edgesLocations(next, top, bottom, left, right);
				//render the vertice based on its position to the start vertice
				switch (location)
				{
				case TOP:

					renderWalls(x, y - SCREEN_HEIGHT, scale);
					renderDoors(top, bottom, left, right, x, y - SCREEN_HEIGHT, scale);
					break;
				case BOTTOM:
					renderWalls(x, y + SCREEN_HEIGHT, scale);
					renderDoors(top, bottom, left, right, x, y + SCREEN_HEIGHT, scale);
					break;
				case LEFT:
					renderWalls(x - SCREEN_WIDTH, y, scale);
					renderDoors(top, bottom, left, right, x - SCREEN_WIDTH, y, scale);
					break;
				case RIGHT:
					renderWalls(x + SCREEN_WIDTH, y, scale);
					renderDoors(top, bottom, left, right, x + SCREEN_WIDTH, y, scale);
					break;
				}
			}
			//get the next edge on the vertice
			next = dungeons->next(start, next);

		} while (next != -1); //if next returns -1 it means there is not more edges to handles

		//appen the start vertice to the list
		lastPos->append(start);
	}

	//when finished rendering reset the marks on the graph
	dungeons->resetMarks();

}



//render the doors this dunction is used mainly when renderin the map
void renderDoors(bool top, bool bottom, bool left, bool right, GLfloat x, GLfloat y, GLfloat scale)
{

	//based on the boolean values we will render the door if a boolean value is tru we will render its door.
	if (top)
	{
		translateModelView((DOORS[0].getX() * scale) + (x * scale), (DOORS[0].getY() * scale) + (y * scale), 0.f);
		scaleModelView(scale, scale, 0.f);

		rectangleProgram.updateModelView(mModelView);

		DOORS[0].drawObject();

	}

	if (bottom)
	{

		translateModelView((DOORS[1].getX() * scale) + (x * scale), (DOORS[1].getY() * scale) + (y * scale), 0.f);
		scaleModelView(scale, scale, 0.f);
		rectangleProgram.updateModelView(mModelView);

		DOORS[0].drawObject();
	}
	if (left)
	{

		translateModelView((DOORS[2].getX() * scale) + (x * scale), (DOORS[2].getY() * scale) + (y * scale), 0.f);
		scaleModelView(scale, scale, 0.f);

		rectangleProgram.updateModelView(mModelView);

		DOORS[2].drawObject();
	}
	if (right)
	{

		translateModelView((DOORS[3].getX() * scale) + (x * scale), (DOORS[3].getY() * scale) + (y * scale), 0.f);
		scaleModelView(scale, scale, 0.f);

		rectangleProgram.updateModelView(mModelView);

		DOORS[2].drawObject();
	}
}


//render the dungeon
void renderDungeon(Dungeon *dungeon, GLfloat scale)
{

	//bind the rectangle program and render all rectangle objects
	rectangleProgram.bind();

	renderPillars(dungeon);
	renderCrates(dungeon);
	renderConsumables(dungeon);
	renderBullets();
	renderPharaohBullets();
	renderMummys(dungeon);
	renderPlayer(scale);
	rectangleProgram.unbind();
	//bind the circle program and render all circle objects
	circleProgram.bind();

	renderTraps(dungeon);
	renderSlimes(dungeon);
	renderPharaoh(dungeon);

	circleProgram.unbind();
}

void renderDungeonArea(Dungeon * dungeon) 
{
	//bind the rectangle prgram
	rectangleProgram.bind();


	//render the walls and doors
	renderWalls();
	renderDoors();

	renderAmmoCount();
	renderHealth();


	rectangleProgram.unbind();


}