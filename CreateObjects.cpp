#include "CreateObjects.h"

//create a new bullet
void createBullet(Bullet *bullet, GLfloat x, GLfloat y, Bullet modelBullet, Player dungeoneer)
{
	//set the bullets cordinates
	bullet->setCoordX(x);
	bullet->setCoordY(y);
	//set the bullets width, height using the model bullet
	bullet->setObjectWidth(modelBullet.getWidth());
	bullet->setObjectHeight(modelBullet.getHeight());
	//set the bullets angle that it will move thorugh based on the players current rotation angle
	bullet->setRotation(dungeoneer.getRotation());
	//set the bullets speed based on the model bullets
	bullet->setSpeed(modelBullet.getSpeed());
	bullet->setDamage(modelBullet.getDamage());

}
// create a pharaoh buller
void createPharaohBullet(Bullet *bullet, GLfloat x, GLfloat y, float angle , Bullet modelPharaohBullet) {
	//set the bullets x y cordinated
	bullet->setCoordX(x);
	bullet->setCoordY(y);
	//set the bulles width and heigh bases on the model pharao bullet
	bullet->setObjectWidth(modelPharaohBullet.getWidth());
	bullet->setObjectHeight(modelPharaohBullet.getHeight());
	//set the angle the bullet will move by based on the given angle
	bullet->setRotation(angle);
	//set the bullets spped based on the model buller current speed
	bullet->setSpeed(modelPharaohBullet.getSpeed());
	

}

//create a new mummy using the modelMummy Object
void createMummy(Mummy *mummy, GLfloat x, GLfloat y, Mummy modelMummy)
{
	mummy->setCoordX(x);
	mummy->setCoordY(y);
	mummy->setObjectWidth(modelMummy.getWidth());
	mummy->setObjectHeight(modelMummy.getHeight());
	mummy->setHealth(modelMummy.getHealth());
	mummy->setSpeed(modelMummy.getSpeed());
	mummy->setTimer(modelMummy.getTimer());
	mummy->setStrenght(modelMummy.getStrenght());
	mummy->setDamage(modelMummy.getDamage());
}

//create a new slime
void createSlime(Slime * slime, GLfloat x, GLfloat y, Slime modelSlime)
{
	slime->setCoordX(x);
	slime->setCoordY(y);
	slime->setObjectWidth(modelSlime.getWidth());
	slime->setObjectHeight(modelSlime.getHeight());
	slime->setHealth(modelSlime.getHealth());
	slime->setSpeed(modelSlime.getSpeed());
	slime->setStrenght(modelSlime.getStrenght());
	slime->setDamage(modelSlime.getDamage());
	slime->setTimer(modelSlime.getTimer());
	slime->setRange(modelSlime.getRange());
	slime->setVAO(modelSlime.getVAO());
	slime->setNumVertice(4);
}
//create goo using the modelGoo object and setting the type of the trap to 0
void createdGoo(Trap * trap, GLfloat x, GLfloat y, Trap modelGoo)
{
	trap->setType(0);
	trap->setObjectWidth(modelGoo.getWidth());
	trap->setObjectHeight(modelGoo.getHeight());
	trap->setCoordX(x);
	trap->setCoordY(y);
	trap->setVAO(modelGoo.getVAO());
	trap->setNumVertice(4);

}
//create a new crate object
void createCrate(Crate *crate, GLfloat x, GLfloat y, Crate modelCrate)
{
	crate->setCoordX(x);
	crate->setCoordY(y);
	crate->setObjectHeight(modelCrate.getHeight());
	crate->setObjectWidth(modelCrate.getWidth());

}

void createPillar(Object * pillar, GLfloat x, GLfloat y, Object modelPillar) {
	pillar->setCoordX(x);
	pillar->setCoordY(y);
	pillar->setObjectWidth(modelPillar.getWidth());
	pillar->setObjectHeight(modelPillar.getHeight());
}

//create a consumable object it will randomize what item it could be if is a health box use the modelHealth box to model it if not use the ammo health box
void createConsumable(Consumable * consumable, GLfloat x, GLfloat y, Consumable modelHealthBox, Consumable modelAmmoBox)
{

	consumable->setType();
	if (consumable->getType() == modelHealthBox.getType()) consumable->setConsumeValue(modelHealthBox.getConsumeValue());

	else consumable->setConsumeValue(modelAmmoBox.getConsumeValue());
	consumable->setCoordX(x);
	consumable->setCoordY(y);
	consumable->setObjectWidth(modelHealthBox.getWidth());
	consumable->setObjectHeight(modelHealthBox.getHeight());


}


//create a pharaoh object
void createPharao(Pharaoh * pharaoh, GLfloat x, GLfloat y, Pharaoh modelPharaoh)
{
	pharaoh->setCoordY(y);
	pharaoh->setCoordX(x);
	pharaoh->setObjectWidth(modelPharaoh.getWidth());
	pharaoh->setObjectHeight(modelPharaoh.getHeight());
	pharaoh->setHealth(modelPharaoh.getHealth());
	pharaoh->setStrenght(modelPharaoh.getStrenght());
	pharaoh->setTimer(modelPharaoh.getTimer());
	pharaoh->setDamage(modelPharaoh.getDamage());
	pharaoh->setVAO(modelPharaoh.getVAO());
	pharaoh->setNumVertice(4);
}

