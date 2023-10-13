#include "HW2.h"

BinaryBitmap::BinaryBitmap(int w, int h)
	:width{ w }, height{ h }
{
	pixel_values.resize(width*height, false);
}

void BinaryBitmap::clear() {
	for (int i = 0; i < pixel_values.size(); i++) 
	{
		pixel_values[i] = false;
	}
}

bool BinaryBitmap::get(int x, int y) const
{
	if ((x >= 0 && x < width) && (y >= 0 && y < height))
	{
		if (pixel_values[(y * width + x)] == 1)
			return true;
		else
			return false;
	}
	else
		return false;
}

void BinaryBitmap::set(int x, int y, bool v)
{	
	if ((x >= 0 && x < width) && (y >= 0 && y < height))
		pixel_values[y*width+x] = v;
}

int BinaryBitmap::getWidth() const
{
	return width;
}

int BinaryBitmap::getHeight() const
{
	return height;
}

CellularAutomata::CellularAutomata(int w, int h) 
	: c_width{w}, c_height{h}
{
	binary_bitmap = new BinaryBitmap(w, h);
}

CellularAutomata::~CellularAutomata() {
	delete binary_bitmap;
}

void CellularAutomata::initialize(InitType t)
{
	switch (t)
	{
	case InitType::CLEAN:
	{
		for (int j = 0; j < getHeight(); j++) {
			for (int i = 0; i < getWidth(); i++) {
				set(i, j, false);
			}
		}
		break;
	}
	case InitType::RANDOM:
	{	
		srand((int)time(NULL));

		for (int i = 0; i < c_width; i++)
		{
			for (int j = 0; j < c_height; j++)
			{	
				if (rand() % 2 == 0)
					set(i, j, false);
				else
					set(i, j, true);
			}
		}
		
		break;
	}
	case InitType::BEEHIVE:
	{	
		clear();

		set(10, 10, 1);
		set(11, 10, 1);
		set(12, 11, 1);
		set(11, 12, 1);
		set(10, 12, 1);
		set(9, 11, 1);
		break;
	}
	case InitType::GLIDER:
		clear();

		set(11, 9, 1);
		set(10, 10, 1);
		set(10, 11, 1);
		set(11, 10, 1);
		set(9, 9, 1);
		
		break;
	case InitType::OSCILLATOR:
		binary_bitmap->clear();
		set(5, 12, true);
		set(5, 13, true);
		set(6, 12, true);
		set(6, 13, true);

		set(15, 10, true);
		set(14, 10, true);
		set(13, 11, true);
		set(12, 12, true);
		set(12, 13, true);
		set(12, 14, true);
		set(13, 15, true);
		set(14, 16, true);
		set(15, 16, true);
		set(16, 13, true);
		set(17, 11, true);
		set(17, 15, true);
		set(18, 12, true);
		set(18, 13, true);
		set(18, 14, true);
		set(19, 13, true);

		set(21, 12, true);
		set(21, 11, true);
		set(21, 10, true);
		set(22, 12, true);
		set(22, 11, true);
		set(22, 10, true);
		set(23, 9, true);
		set(23, 13, true);

		set(25, 9, true);
		set(25, 8, true);
		set(25, 13, true);
		set(25, 14, true);

		set(30, 8, true);
		set(30, 9, true);
		set(31, 8, true);
		set(31, 9, true);

		break;
	}
}


void CellularAutomata::clear()
{
	binary_bitmap->clear();
}

bool CellularAutomata::copy(const CellularAutomata& automata)
{	
	if (automata.getHeight() == binary_bitmap->getHeight() && automata.getWidth() == binary_bitmap->getWidth()) {
		for (int j = 0; j < getHeight(); j++) {
			for (int i = 0; i < getWidth(); i++) {
				set(i, j, automata.get(i, j));
			}
		}
		return true;
	}
	else
		return false;
}

void CellularAutomata::set(int x, int y, bool v)
{
	binary_bitmap->set(x, y, v);
}

void CellularAutomata::update(){}

bool CellularAutomata::get(int x, int y) const
{
	return binary_bitmap->get(x, y);
}

int CellularAutomata::getWidth() const
{
	return c_width;
}

int CellularAutomata::getHeight() const
{
	return c_height;
}

LifeAutomata::LifeAutomata(int w, int h)
	:CellularAutomata(w, h)
{

}

void LifeAutomata::update()
{
	BinaryBitmap* copy_map = new BinaryBitmap(getWidth(), getHeight());

	for (int j = 0; j < getHeight(); j++)
	{
		for (int i = 0; i < getWidth(); i++)
			copy_map->set(i, j, this->get(i, j));
	}
	for (int y = 0; y < getHeight(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			int cnt = 0;

			if (copy_map->get(x - 1, y - 1) == 1) { cnt++; }
			if (copy_map->get(x - 1, y - 0) == 1) { cnt++; }
			if (copy_map->get(x - 1, y + 1) == 1) { cnt++; }
			if (copy_map->get(x, y - 1) == 1) { cnt++; }
			if (copy_map->get(x + 1, y - 1) == 1) { cnt++; }
			if (copy_map->get(x, y + 1) == 1) { cnt++; }
			if (copy_map->get(x + 1, y + 0) == 1) { cnt++; }
			if (copy_map->get(x + 1, y + 1) == 1) { cnt++; }


			if (copy_map->get(x, y) == 1) {
				if (!(cnt == 2 || cnt == 3))
					set(x, y, false);
			}
			else {
				if (cnt == 3)
					set(x, y, true);
			}
		}
	}

	delete copy_map;
}
	

SeedAutomata::SeedAutomata(int w, int h) 
	:CellularAutomata(w, h)
{

}

void SeedAutomata::update() {
	BinaryBitmap* copy_map = new BinaryBitmap(getWidth(), getHeight());

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
			copy_map->set(x, y, get(x, y));
	}
	for (int y = 0; y < getHeight(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			int cnt = 0;

			if (copy_map->get(x - 1, y - 1) == 1) { cnt++; }
			if (copy_map->get(x - 1, y - 0) == 1) { cnt++; }
			if (copy_map->get(x - 1, y + 1) == 1) { cnt++; }
			if (copy_map->get(x, y - 1) == 1) { cnt++; }
			if (copy_map->get(x + 1, y - 1) == 1) { cnt++; }
			if (copy_map->get(x, y + 1) == 1) { cnt++; }
			if (copy_map->get(x + 1, y + 0) == 1) { cnt++; }
			if (copy_map->get(x + 1, y + 1) == 1) { cnt++; }


			if (copy_map->get(x, y) == 1) {
				set(x, y, false);
			}
			else {
				if (cnt == 2)
					set(x, y, true);
			}
		}
	}

	delete copy_map;
}

ReplicatorAutomata::ReplicatorAutomata(int w, int h) :CellularAutomata(w, h)
{

}

void ReplicatorAutomata::update() {
	CellularAutomata* copy_map = new CellularAutomata(getWidth(), getHeight());

	for (int y = 0; y < getHeight(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			int cnt = 0;

			if (get(x - 1, y - 1) == 1) { cnt++; }
			if (get(x - 1, y - 0) == 1) { cnt++; }
			if (get(x - 1, y + 1) == 1) { cnt++; }
			if (get(x, y - 1) == 1) { cnt++; }
			if (get(x + 1, y - 1) == 1) { cnt++; }
			if (get(x, y + 1) == 1) { cnt++; }
			if (get(x + 1, y + 0) == 1) { cnt++; }
			if (get(x + 1, y + 1) == 1) { cnt++; }

			if (get(x, y) == 1) {
				if (cnt == 1)
					copy_map->set(x, y, true);
				else if (cnt == 3)
					copy_map->set(x, y, true);
				else if (cnt == 5)
					copy_map->set(x, y, true);
				else if (cnt == 7)
					copy_map->set(x, y, true);
				else
					copy_map->set(x, y, false);
			}
			else {
				if (cnt == 1)
					copy_map->set(x, y, true);
				else if (cnt == 3)
					copy_map->set(x, y, true);
				else if (cnt == 5)
					copy_map->set(x, y, true);
				else if (cnt == 7)
					copy_map->set(x, y, true);
				else
					copy_map->set(x, y, false);
			}
		}
	}
	copy(*copy_map);

	delete copy_map;
}


