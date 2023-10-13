#ifndef HW2_GUARD
#define HW2_GUARD 1

#include "std_lib_facilities.h"

class BinaryBitmap {
public:
	BinaryBitmap(int w, int h);

	void clear();

	bool get(int x, int y) const;
	void set(int x, int y, bool v);

	int getWidth() const;
	int getHeight() const;
private:
	vector<bool> pixel_values;
	int width, height;
};

class CellularAutomata {
public:
	enum class InitType { CLEAN, RANDOM, BEEHIVE, GLIDER, OSCILLATOR };

	CellularAutomata(int w, int h);
	virtual ~CellularAutomata();

	void initialize(InitType t);
	void clear();
	bool copy(const CellularAutomata& automata);

	virtual void update();

	void set(int x, int y, bool v);
	bool get(int x, int y) const;

	int getWidth() const;
	int getHeight() const;
protected:
	BinaryBitmap* binary_bitmap;
	int c_width, c_height;
};

class LifeAutomata :public CellularAutomata {
public:
	LifeAutomata(int w, int h);
	void update() override;
};

class SeedAutomata : public CellularAutomata {
public:
	SeedAutomata(int w, int h);
	void update() override;
};


class ReplicatorAutomata : public CellularAutomata {
public:
	ReplicatorAutomata(int w, int h);
	void update() override;
};


#endif