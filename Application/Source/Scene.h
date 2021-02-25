#ifndef SCENE_H
#define SCENE_H
#include <cmath>
#include <string>
#include "Vector3.h"
#include "Mesh.h"
#include "irrKlang.h"


using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") 
class Scene
{
public:
	Scene() {
		ghost = nullptr;
		inventory = nullptr;
		flashlight_lifetime = 60;
		flashlight = false;
		
	}
	~Scene() {};
	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void PauseUpdate() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Set(Scene* scene) = 0;
	virtual void SetBackground()=0;


	struct Item
	{
		enum ITEM_TYPE
		{
			BATTERY,
			Screwdriver,
			FLOWER,
			ITEM3,
			SPARK_PLUG,
			Key,
			//add more depending on whta u need, don forget set in Set function
		};
	
		Vector3 pos; //only if u plan to reuse struct for rendering
		const char* image; //image of item in inventory
		int count; 
		int type; //type of item (for reusability e.g 100 batteries; easier setting)
		std::string name;  //Name that shows up in item display; can also be used to differentiate btw objects of same type but different, eg both keys but unlock diff doors, type = key but name different
		std::string description; //Short description of item that shows up in item display

		Item(std::string itemname, int itemtype, Vector3 pos)
		{
			count = 1;
			type = BATTERY;
			image = "Assigment2Images//batteryicon.tga";
			type = itemtype;
			name = itemname;
			this->pos = pos;
			switch (type)
			{
			case BATTERY:
				description = "Use to refill flashlight batteries aaaaaa idk";
				image = "Assigment2Images//batteryicon.tga";
				//set image and description
				break;
			case SPARK_PLUG:
				description = "A spark plug used for delivery current to the combustion chamber in a car's engine ";
				image = "Image//sparkplug_icon.tga";
				//set image and description
				break;
			case FLOWER:
				description = "A rose stalk. I wonder what it could be for?";
				image = "Image//rosestalk.tga";
				count = 7;
				break;
			case Screwdriver:
				description = "A screwdriver";
				image = "Assigment2Images/screwdrivericon.tga";
				break;
			case Key:
				description = "A key";
				image = "Assigment2Images/keyicon.tga";
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
			UNSPAWNED,
			NORMAL,
			CHASING,
			TOLOCKER,
			WAITING,
			SPEEDRUN,
			SPIN,
			DEATH,
		};
		int state;
		bool kill;
		Vector3 up;
		Vector3 pos;
		Vector3 facing; //ghost direction
		Vector3 rawPos;
		Vector3 axis;
		float speed; //TBC normal - 5, chasing - 25, speedrunning away - 50; //player is 20 normal and 40 sprinting
		float distance;
		float waitTime;
		float rotateY;
		int lockerIndex;

		Ghost()
		{
			up.Set(0, 1, 0);
			speed = 5;
			facing.Set(0, 0, -1);
			axis = facing.Cross(up);
			pos.Set(100, 3, 0); //far far away so no one knows its there
			rawPos.Set(100, 0, 0);
			rotateY = 0;
			state = UNSPAWNED;
			waitTime = 3;
			distance = 2000; //just anyth not < 100
			kill = false;
			lockerIndex = -1; //wtvr any number first
		}
		bool UpdateRotation(double dt)
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
			int dir = int((newangle - rotateY) / abs(newangle - rotateY));
			if ((int)rotateY != (int)newangle)
			{
				if (abs(newangle - rotateY) > 180) //so that it rotates ACW/CW the shortest path 
				{
					dir *= -1;
				}
				rotateY += float(dir * 100 * dt);
				return true;
			}
			else
			{
				return false;
			}
		}
		void UpdateMovement(double dt)
		{
			if (!UpdateRotation(dt))
			{
				pos += facing * speed * float(dt);
			}
			axis = facing.Cross(up).Normalized();
		}
		
	};
	Inventory* inventory;
	Ghost* ghost;

	ISoundEngine* Background;
	ISoundEngine* Jumpscare;
	ISoundEngine* Effect;
	ISoundEngine* Heartbeat;
	bool flashlight;
	float flashlight_lifetime;
	int ObjectivePhase;
	int screwDriverFound;
	int wrenchFound;
	int hammerFound;
	int SparkplugFound;
	Mesh* itemImage[8];



	
};

#endif