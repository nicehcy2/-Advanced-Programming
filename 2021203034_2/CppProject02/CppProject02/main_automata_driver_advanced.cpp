#include "Graph.h"
#include "Simple_window.h"
#include "HW2.h"

using namespace Graph_lib;

struct Automata_window : Window
{
	Automata_window(Point xy, int w, int h, const string& title);
	~Automata_window();

private:
	int win_width;
	int win_height;

	int grid_ncol = 50;
	int grid_nrow = 30;
	double timer_dt = 0.5;

	vector<CellularAutomata*> automata_list;
	vector<vector<Graph_lib::Rectangle*>*> grid_list;

	void makeAutomata();
	void makeGrids();

	vector<Graph_lib::Rectangle*>* makeGrid(CellularAutomata* automata, Point xy, int w, int h);
	void updateGrids();

	//
	Button random_button;
	Button beehive_button;
	Button glider_button;
	Button oscillator_button;
	Button next_button;
	Button play_button;
	Button stop_button;
	Button exit_button;

	void random();
	void beehive();
	void glider();
	void oscillator();
	void next();
	void play();
	void stop();
	void exit();
	void timer();

	static void cb_random(Address, Address window);
	static void cb_beehive(Address, Address window);
	static void cb_glider(Address, Address window);
	static void cb_oscillator(Address, Address window);
	static void cb_next(Address, Address window);
	static void cb_play(Address, Address window);
	static void cb_stop(Address, Address window);
	static void cb_exit(Address, Address window);
	static void cb_timer(Address window);
};

Automata_window::Automata_window(Point xy, int w, int h, const string& title)
	: Window(xy, w, h, title),
	win_width(w),
	win_height(h),
	random_button(Point(250, 10), 70, 20, "Random", cb_random),
	beehive_button(Point(330, 10), 70, 20, "Beehive", cb_beehive),
	glider_button(Point(410, 10), 70, 20, "Glider", cb_glider),
	oscillator_button(Point(490, 10), 70, 20, "Oscillator", cb_oscillator),
	next_button(Point(570, 10), 70, 20, "Next", cb_next),
	play_button(Point(650, 10), 70, 20, "Play", cb_play),
	stop_button(Point(730, 10), 70, 20, "Stop", cb_stop),
	exit_button(Point(810, 10), 70, 20, "Exit", cb_exit)
{
	attach(random_button);
	attach(beehive_button);
	attach(glider_button);
	attach(oscillator_button);
	attach(next_button);
	attach(play_button);
	attach(stop_button);
	attach(exit_button);

	//
	makeAutomata();
	makeGrids();

	redraw();
}

Automata_window::~Automata_window()
{
	for (CellularAutomata* automata : automata_list)
	{
		delete automata;
	}

	for (vector<Graph_lib::Rectangle*>* grid : grid_list)
	{
		for (Graph_lib::Rectangle* rect : *grid)
		{
			delete rect;
		}
	}
}

void Automata_window::makeAutomata()
{
	if (!automata_list.empty())
	{
		for (CellularAutomata* automata : automata_list)
		{
			delete automata;
		}
		automata_list.clear();
	}

	CellularAutomata* simple_automata = new CellularAutomata(grid_ncol, grid_nrow);
	CellularAutomata* life_automata = new LifeAutomata(grid_ncol, grid_nrow);
	CellularAutomata* seed_automata = new SeedAutomata(grid_ncol, grid_nrow);
	CellularAutomata* repl_automata = new ReplicatorAutomata(grid_ncol, grid_nrow);

	automata_list.push_back(simple_automata);
	automata_list.push_back(life_automata);
	automata_list.push_back(seed_automata);
	automata_list.push_back(repl_automata);

	for (CellularAutomata* automata : automata_list)
	{
		automata->initialize(CellularAutomata::InitType::CLEAN);
	}
}

void Automata_window::makeGrids()
{
	if (automata_list.size() != 4)
	{
		return;
	}

	if (!grid_list.empty())
	{
		for (vector<Graph_lib::Rectangle*>* grid : grid_list)
		{
			for (Graph_lib::Rectangle* rect : (*grid))
			{
				detach(*rect);
				delete rect;
			}
			delete grid;
		}
		grid_list.clear();
	}

	CellularAutomata* simple_automata = automata_list[0];
	CellularAutomata* life_automata = automata_list[1];
	CellularAutomata* seed_automata = automata_list[2];
	CellularAutomata* repl_automata = automata_list[3];

	int grid_width = (win_width - 20) / 2;
	int grid_height = (win_height - 40) / 2 - 10;

	vector<Graph_lib::Rectangle*>* simple_grid = makeGrid(simple_automata, Point(10, 40), grid_width, grid_height);
	vector<Graph_lib::Rectangle*>* life_grid = makeGrid(life_automata, Point(10 + grid_width + 10, 40), grid_width, grid_height);
	vector<Graph_lib::Rectangle*>* seed_grid = makeGrid(seed_automata, Point(10, 40 + grid_height + 10), grid_width, grid_height);
	vector<Graph_lib::Rectangle*>* repl_grid = makeGrid(repl_automata, Point(10 + grid_width + 10, 40 + grid_height + 10), grid_width, grid_height);

	grid_list.push_back(simple_grid);
	grid_list.push_back(life_grid);
	grid_list.push_back(seed_grid);
	grid_list.push_back(repl_grid);
}

vector<Graph_lib::Rectangle*>* Automata_window::makeGrid(CellularAutomata* automata, Point xy, int w, int h)
{
	vector<Graph_lib::Rectangle*>* grid = new vector<Graph_lib::Rectangle*>;

	int cell_width = w / grid_ncol;
	int cell_height = h / grid_nrow;

	for (int r = 0; r < grid_nrow; r++)
	{
		for (int c = 0; c < grid_ncol; c++)
		{
			Point rect_xy(xy.x + cell_width * c, xy.y + cell_height * r);
			Graph_lib::Rectangle* rect = new Graph_lib::Rectangle(rect_xy, cell_width, cell_height);
			rect->set_color(Color::black);
			if (automata->get(c, r))
			{
				rect->set_fill_color(Color::black);
			}
			else
			{
				rect->set_fill_color(Color::white);
			}
			grid->push_back(rect);

			attach(*rect);
		}
	}

	return grid;
}

void Automata_window::updateGrids()
{
	for (int i = 0; i < automata_list.size(); i++)
	{
		CellularAutomata* automata = automata_list[i];
		vector<Graph_lib::Rectangle*>* grid = grid_list[i];

		for (int r = 0; r < grid_nrow; r++)
		{
			for (int c = 0; c < grid_ncol; c++)
			{
				Graph_lib::Rectangle* rect = (*grid)[r*grid_ncol + c];
				if (automata->get(c, r))
				{
					rect->set_fill_color(Color::black);
				}
				else
				{
					rect->set_fill_color(Color::white);
				}
			}
		}
	}

	redraw();
}

void Automata_window::random()
{
	for (int i = 0; i < automata_list.size(); i++)
	{
		CellularAutomata* automata = automata_list[i];

		if (i == 0)
		{
			automata->initialize(CellularAutomata::InitType::RANDOM);
		}
		else
		{
			automata->copy(*(automata_list[0]));
		}
	}

	updateGrids();
}

void Automata_window::beehive()
{
	for (CellularAutomata* automata : automata_list)
	{
		automata->initialize(CellularAutomata::InitType::BEEHIVE);
	}

	updateGrids();
}

void Automata_window::glider()
{
	for (CellularAutomata* automata : automata_list)
	{
		automata->initialize(CellularAutomata::InitType::GLIDER);
	}

	updateGrids();
}

void Automata_window::oscillator()
{
	for (CellularAutomata* automata : automata_list)
	{
		automata->initialize(CellularAutomata::InitType::OSCILLATOR);
	}

	updateGrids();
}

void Automata_window::next()
{
	for (CellularAutomata* automata : automata_list)
	{
		automata->update();
	}

	updateGrids();
}

void Automata_window::play()
{
	Fl::add_timeout(timer_dt, cb_timer, (Address)this);
}

void Automata_window::stop()
{
	Fl::remove_timeout(cb_timer, (Address)this);
}

void Automata_window::exit()
{
	hide();
}

void Automata_window::timer()
{
	next();

	Fl::repeat_timeout(timer_dt, cb_timer, (Address)this);
}

void Automata_window::cb_random(Address, Address pw)
{
	reference_to<Automata_window>(pw).random();
}

void Automata_window::cb_beehive(Address, Address pw)
{
	reference_to<Automata_window>(pw).beehive();
}

void Automata_window::cb_glider(Address, Address pw)
{
	reference_to<Automata_window>(pw).glider();
}

void Automata_window::cb_oscillator(Address, Address pw)
{
	reference_to<Automata_window>(pw).oscillator();
}

void Automata_window::cb_next(Address, Address pw)
{
	reference_to<Automata_window>(pw).next();
}

void Automata_window::cb_play(Address, Address pw)
{
	reference_to<Automata_window>(pw).play();
}

void Automata_window::cb_stop(Address, Address pw)
{
	reference_to<Automata_window>(pw).stop();
}

void Automata_window::cb_exit(Address, Address pw)
{
	reference_to<Automata_window>(pw).exit();
}

void Automata_window::cb_timer(Address pw)
{
	reference_to<Automata_window>(pw).timer();
}

int main()
{
	int win_width = 1000;
	int win_height = 680;
	Point win_tl(100, 200);

	Automata_window win(win_tl, win_width, win_height, "Automata Test: Advanced");
	return gui_main();
}
