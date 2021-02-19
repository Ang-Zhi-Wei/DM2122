#ifndef SCENE_H
#define SCENE_H
#include <cmath>
#include <string>
#include "Vector3.h"

class Scene
{
public:
	Scene() {}
	~Scene() {}

	struct Item
	{
		enum ITEM_TYPE
		{
			BATTERY,
			ITEM2,
			ITEM3,
			//add more depending on whta u need, don forget set in Set function
		};
		//Vector3 pos; //only if u plan to reuse struct for rendering
		const char* image; //image of item in inventory
		int count;
		ITEM_TYPE type; //type of item (for reusability e.g 100 batteries; easier setting)
		std::string name;  //Name that shows up in item display; can also be used to differentiate btw objects of same type but different, eg both keys but unlock diff doors, type = key but name different
		std::string description; //Short description of item that shows up in item display

		Item()
		{
			count = 1;
		}
		void Set(std::string name, ITEM_TYPE type)
		{
			//this->pos = pos; //if used for rendering uncomment, otherwise can remove pos from function arguments
			this->type = type;
			this->name = name;
			switch (type)
			{
			case BATTERY:
				this->description = "Use to refill flashlight batteries aaaaaa idk";
				this->image = "Image//fountaintexture.tga";
				//set image and description
				break;
			case ITEM2:
				this->description = "TESTESTTESTETSESTESTESTETST>--|-o";
				this->image = "Image//man1.tga";
				break;
			}
		}
	};

	struct Inventory
	{
		int selected;
		Item* items[8];
		bool open;

		Inventory()
		{
			for (int i = 0; i < 8; i++)
			{
				items[i] = nullptr;
			}
			open = false;
			selected = 0;
		}
	};

	struct Ghost
	{
		enum GHOST_STATE
		{
			NORMAL,
			CHASING,
			WAITING,
			SPEEDRUN
		};
		int state;
		Vector3 pos;
		Vector3 facing; //ghost direction
		float speed; //TBC normal - 5, chasing - 25, speedrunning away - 50; //player is 20 normal and 40 sprinting
		float distance;
		float waitTime;
		float rotateY;

		Ghost()
		{
			speed = 5;
			pos = (0, 0, 0); //TBC
			rotateY = 0;
			state = NORMAL;
			waitTime = 5;
		}

		void UpdateMovement(double dt)
		{
			float newangle = Math::RadianToDegree(atan(facing.x / facing.z)); //facing is vector that player/char shud be facing
																				//newangle is angle of rotation for playerr/char based on the vector

			//since tan inverse returns basic angle, gotta set the angle myself
			if (newangle == 0 && facing.z < 0)
			{
				newangle = 180;
			}
			else if (newangle < 0 && facing.x >= 0 && facing.z <= 0)
			{
				newangle = newangle + 180;
			}
			else if (newangle > 0 && facing.x <= 0 && facing.z <= 0)
			{
				newangle = newangle - 180;
			}

			//if angle exceeds one cycle, bring it back to within 0 to 360 cycle
			if (rotateY > 360)
			{
				rotateY -= 360;
			}
			if (rotateY < 0)
			{
				rotateY += 360;
			}
			if (newangle > 360)
			{
				newangle -= 360;
			}
			if (newangle < 0)
			{
				newangle += 360;
			}

			//int/float offset for checking
			if (abs(newangle - rotateY) < 5)
			{
				rotateY = newangle;
			}

			//update rotate angle(in render) to face/turn towards direction player is walking in
			int dir = (newangle - rotateY) / abs(newangle - rotateY);
			if ((int)rotateY != (int)newangle)
			{
				if (abs(newangle - rotateY) > 180) //so that it rotates ACW/CW the shortest path 
				{
					dir *= -1;
				}
				rotateY += float(dir * 20 * dt);
			}
			else
			{
				pos += facing * speed * dt;
			}
		}
	};
	Inventory* inventory;
	Ghost* ghost;

	bool flashlight;
	float flashlight_lifetime;

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Set(Scene* scene) = 0;

	
};

#endif