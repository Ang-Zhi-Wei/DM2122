#pragma once
struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	Component& operator=(const Component& rhs)
	{
		Set(rhs.r, rhs.g, rhs.b);
		//dk why it wants me to return something when material does not need to
		Component a(rhs.r, rhs.g, rhs.b);
		return a;
	}

	void Set(float r, float g, float b)
	{
		this->r = r; this->g = g; this->b = b;
	}
	void Set(int color) {
		switch (color) {
		case Red:
			r = 1.0f;
			g = 0.f;
			b = 0.f;
			break;
		case Blue:
			r = 0.f;
			g = 1.f;
			b = 1.f;
			break;
		case Pink:
			r = 1.000f;
			g = 0.753f;
			b = 0.796f;
			break;
		case Orange:
			r = 1.000f;
			g = 0.647f;
			b = 0.f;
			break;
		case Purple:
			r = 0.502f;
			g = 0.f;
			b = 0.502f;
			break;
		case Yellow:
			r = 1.f;
			g = 1.f;
			b = 0.f;
			break;
		case Green:
			r = 0.000f;
			g = 0.502f;
			b = 0.000f;
			break;
		case Gray:
			r = 0.412f;
			g = 0.412f;
			b = 0.412f;
			break;
		case Brown:
			r = 0.545f;
			g = 0.271f;
			b = 0.075f;
			break;
		case Silver:
			r = 0.753f;
			g = 0.753f;
			b = 0.753f;
			break;
		case Wheat:
			r = 0.961f;
			g = 0.871f;
			b = 0.702f;
			break;
		case Black:
			r = 0.f;
			g = 0.f;
			b = 0.f;
			break;
		case Crimson:
			r = 0.863f;
			g = 0.078f;
			b = 0.235f;
			break;
		case White:
			r = 1.f;
			g = 1.f;
			b = 1.f;
			
		}
	}
};
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	int size;
	Material() {
		kAmbient = {
			1.0f,1.0f,1.0f
		};
		kDiffuse = {
			0.3f,0.3f,0.3f
		};
		kSpecular = {
			0.6f,0.6f,0.6f
		};
		kShininess = 1;
	}
	Material& operator=(const Material& rhs)
	{
		kAmbient = rhs.kAmbient;
		kDiffuse = rhs.kDiffuse;
		kSpecular = rhs.kSpecular;
		kShininess = rhs.kShininess;
		size = rhs.size;
	}

};	
