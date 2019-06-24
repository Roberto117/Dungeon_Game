#ifndef CreateObject_h
#define CreateObject_h
#include "Sprites.h"
//create a bullet object which will need a pointer to and addres of a bullet object and the x ,y position where it will be created, it will use the modelBullet object to create it
void createBullet(Bullet *bullet, GLfloat x, GLfloat y , Bullet modelBullet, Player dungeooner);
//create a pharaoBullet object  will need a pointer to and addres of a bullet object and the x ,y position where it will be created, it will use the modelPharaoh bullet object ot create it
void createPharaohBullet(Bullet *bullet, GLfloat x, GLfloat y, float angle , Bullet modelBullet);

//create a mummy object, it will need the pointer to and address of a mummy object and the x y cordinate where it will creates, it will sue the modelMummy object to create the mummy.
void createMummy(Mummy *mummy, GLfloat x, GLfloat y, Mummy modelMummy);
//create a crate object, it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createCrate(Crate *crate, GLfloat x, GLfloat y, Crate modelCrate);
//create a crate pillar, it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createPillar(Object * pillar, GLfloat x, GLfloat y, Object modelPillar);
//create a Consumable object , it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createConsumable(Consumable * consumable, GLfloat x, GLfloat y, Consumable modelConsumable, Consumable modelAmmoBox);

//create a slime object , it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createSlime(Slime * slime, GLfloat x, GLfloat y , Slime modelSlime);

//create a goo object, , it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createdGoo(Trap * trap, GLfloat x, GLfloat y, Trap modelTrap);

//crate a pharaoh object, it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createPharao(Pharaoh *pharaoh, GLfloat x, GLfloat y, Pharaoh modelPharaoh);


#endif // CreateObject_h
