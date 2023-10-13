/*#include "Graph.h"
#include "Simple_window.h"
#include "HW2.h"

using namespace Graph_lib;

struct Bitmap_window : Window
{
	Bitmap_window(Point xy, int w, int h, const string& title);
	~Bitmap_window();

private:
	int win_width;
	int win_height;

	int grid_ncol = 20;
	int grid_nrow = 20;
	double timer_dt = 0.1;

	vector<BinaryBitmap*> bitmap_list;
	vector<vector<Graph_lib::Rectangle*>*> grid_list;

	void makeBitmaps();
	void makeGrids();

	vector<Graph_lib::Rectangle*>* makeGrid(BinaryBitmap* automata, Point xy, int w, int h);
	void updateGrids();

	//
	Button resize10x10_button;
	Button resize20x20_button;
	Button resize50x50_button;
	Button icon_button;
	Button random_button;
	Button clear_button;
	Button exit_button;

	void resize10x10();
	void resize20x20();
	void resize50x50();
	void icon();
	void random();
	void clear();
	void exit();

	static void cb_resize10x10(Address, Address window);
	static void cb_resize20x20(Address, Address window);
	static void cb_resize50x50(Address, Address window);
	static void cb_icon(Address, Address window);
	static void cb_random(Address, Address window);
	static void cb_clear(Address, Address window);
	static void cb_exit(Address, Address window);
};

Bitmap_window::Bitmap_window(Point xy, int w, int h, const string& title)
	: Window(xy, w, h, title),
	win_width(w),
	win_height(h),
	resize10x10_button(Point(10, 10), 70, 20, "10x10", cb_resize10x10),
	resize20x20_button(Point(90, 10), 70, 20, "20x20", cb_resize20x20),
	resize50x50_button(Point(170, 10), 70, 20, "50x50", cb_resize50x50),
	icon_button(Point(250, 10), 70, 20, "Icon", cb_icon),
	random_button(Point(330, 10), 70, 20, "Random", cb_random),
	clear_button(Point(410, 10), 70, 20, "Clear", cb_clear),
	exit_button(Point(810, 10), 70, 20, "Exit", cb_exit)
{
	attach(resize10x10_button);
	attach(resize20x20_button);
	attach(resize50x50_button);
	attach(icon_button);
	attach(random_button);
	attach(clear_button);
	attach(exit_button);

	makeBitmaps();
	makeGrids();

	redraw();
}

Bitmap_window::~Bitmap_window()
{
	for (BinaryBitmap* bitmap : bitmap_list)
	{
		delete bitmap;
	}

	for (vector<Graph_lib::Rectangle*>* grid : grid_list)
	{
		for (Graph_lib::Rectangle* rect : *grid)
		{
			delete rect;
		}
	}
}

void Bitmap_window::makeBitmaps()
{
	if (!bitmap_list.empty())
	{
		for (BinaryBitmap* bitmap : bitmap_list)
		{
			delete bitmap;
		}
		bitmap_list.clear();
	}

	BinaryBitmap* source_bitmap = new BinaryBitmap(grid_nrow, grid_ncol);
	BinaryBitmap* target_bitmap = new BinaryBitmap(grid_nrow, grid_ncol);
	*target_bitmap = *source_bitmap;

	bitmap_list.push_back(source_bitmap);
	bitmap_list.push_back(target_bitmap);
}

void Bitmap_window::makeGrids()
{
	if (bitmap_list.size() != 2)
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

	BinaryBitmap* source_bitmap = bitmap_list[0];
	BinaryBitmap* target_bitmap = bitmap_list[1];

	int grid_width = (win_width - 20) / 2;
	int grid_height = (win_height - 40);

	vector<Graph_lib::Rectangle*>* source_grid = makeGrid(source_bitmap, Point(10, 40), grid_width, grid_height);
	vector<Graph_lib::Rectangle*>* target_grid = makeGrid(target_bitmap, Point(10 + grid_width + 10, 40), grid_width, grid_height);

	grid_list.push_back(source_grid);
	grid_list.push_back(target_grid);
}

vector<Graph_lib::Rectangle*>* Bitmap_window::makeGrid(BinaryBitmap* bitmap, Point xy, int w, int h)
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
			if (bitmap->get(c, r))
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

void Bitmap_window::updateGrids()
{
	for (int i = 0; i < grid_list.size(); i++)
	{
		BinaryBitmap* bitmap = bitmap_list[i];
		vector<Graph_lib::Rectangle*>* grid = grid_list[i];

		for (int r = 0; r < grid_nrow; r++)
		{
			for (int c = 0; c < grid_ncol; c++)
			{
				Graph_lib::Rectangle* rect = (*grid)[r*grid_ncol + c];
				if (bitmap->get(c, r))
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

void Bitmap_window::resize10x10()
{
	if (grid_ncol != 10 || grid_ncol != 10)
	{
		for (BinaryBitmap* bitmap : bitmap_list)
		{
			delete bitmap;
		}
		bitmap_list.clear();

		//
		grid_ncol = 10;
		grid_nrow = 10;

		BinaryBitmap* source_bitmap = new BinaryBitmap(grid_nrow, grid_ncol);
		BinaryBitmap* target_bitmap = new BinaryBitmap(grid_nrow, grid_ncol);

		bitmap_list.push_back(source_bitmap);
		bitmap_list.push_back(target_bitmap);

		makeGrids();
		redraw();
	}
}

void Bitmap_window::resize20x20()
{
	if (grid_ncol != 20 || grid_ncol != 20)
	{
		for (BinaryBitmap* bitmap : bitmap_list)
		{
			delete bitmap;
		}
		bitmap_list.clear();

		//
		grid_ncol = 20;
		grid_nrow = 20;

		BinaryBitmap* source_bitmap = new BinaryBitmap(grid_nrow, grid_ncol);
		BinaryBitmap* target_bitmap = new BinaryBitmap(grid_nrow, grid_ncol);

		bitmap_list.push_back(source_bitmap);
		bitmap_list.push_back(target_bitmap);

		makeGrids();
		redraw();
	}
}

void Bitmap_window::resize50x50()
{
	if (grid_ncol != 50 || grid_ncol != 50)
	{
		for (BinaryBitmap* bitmap : bitmap_list)
		{
			delete bitmap;
		}
		bitmap_list.clear();

		//
		grid_ncol = 50;
		grid_nrow = 50;

		BinaryBitmap* source_bitmap = new BinaryBitmap(grid_nrow, grid_ncol);
		BinaryBitmap* target_bitmap = new BinaryBitmap(grid_nrow, grid_ncol);

		bitmap_list.push_back(source_bitmap);
		bitmap_list.push_back(target_bitmap);

		makeGrids();
		redraw();
	}
}

void Bitmap_window::icon()
{
	int w = 64, h = 64;

	// generated by https://www.digole.com/tools/PicturetoC_Hex_converter.php
	char image[] = {
		  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3f
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0x1f
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x8f
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xcf
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xc7
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xe7
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xe7
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xe7
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xc7
		, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xcf
		, 0xff, 0xff, 0xff, 0xe7, 0xfc, 0x7f, 0xff, 0x8f
		, 0xff, 0xff, 0xff, 0xe3, 0xf8, 0xff, 0xff, 0x1f
		, 0xff, 0xff, 0xff, 0xf1, 0xf1, 0xff, 0xf0, 0x3f
		, 0xff, 0xff, 0xff, 0xf8, 0xe3, 0xff, 0xe0, 0xff
		, 0xff, 0xff, 0xff, 0xfc, 0x47, 0xff, 0xc7, 0xff
		, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0x8f, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0x1f, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xfe, 0x3f, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xfc, 0x7f, 0xff
		, 0xff, 0xff, 0xff, 0xf8, 0xe3, 0xf8, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xf1, 0xf1, 0xf1, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xe3, 0xf8, 0xe3, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xc7, 0xdc, 0x47, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0x8f, 0x8e, 0x0f, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x1f, 0xff, 0xff
		, 0xff, 0xff, 0xfe, 0x3e, 0x3f, 0x8f, 0xff, 0xff
		, 0xff, 0xff, 0xfc, 0x7c, 0x7d, 0xc7, 0xff, 0xff
		, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xe3, 0xff, 0xff
		, 0xff, 0xff, 0xf1, 0xf1, 0xf1, 0xf1, 0xff, 0xff
		, 0xff, 0xff, 0xe3, 0xe3, 0xe3, 0xf8, 0xff, 0xff
		, 0xff, 0xff, 0xc7, 0xc7, 0xc7, 0xfc, 0x7f, 0xff
		, 0xff, 0xff, 0x8f, 0x8f, 0x8f, 0xfe, 0x3f, 0xff
		, 0xff, 0xff, 0x1f, 0x1f, 0x1f, 0xff, 0x7f, 0xff
		, 0xff, 0xfe, 0x3e, 0x3e, 0x3f, 0xff, 0xff, 0xff
		, 0xff, 0xfc, 0x7c, 0x7c, 0x7f, 0xff, 0xff, 0xff
		, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xf1, 0xf1, 0xf1, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xe3, 0xe3, 0xe3, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xc7, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0x1f, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0x3e, 0x3e, 0x3f, 0xff, 0xff, 0xff, 0xff
		, 0xfe, 0x7c, 0x7c, 0x7f, 0xff, 0xff, 0xff, 0xff
		, 0xfc, 0x78, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xf8, 0xfd, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xf9, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xf9, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xf3, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xf3, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xf3, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xe3, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xe7, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xe7, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};

	for (BinaryBitmap* bitmap : bitmap_list)
	{
		delete bitmap;
	}
	bitmap_list.clear();

	//
	this->grid_ncol = w;
	this->grid_nrow = h;

	BinaryBitmap* source_bitmap = new BinaryBitmap(w, h);
	for (int r = 0; r < h; r++)
	{
		for (int c = 0; c < w; c++)
		{
			int index = r * w + c;
			int byte_index = index / 8;
			int bit_index = 7 - index % 8;

			bool v = (image[byte_index] & (1 << bit_index));
			source_bitmap->set(c, r, v);
		}
	}

	BinaryBitmap* target_bitmap = new BinaryBitmap(w, h);
	*target_bitmap = *source_bitmap;

	bitmap_list.push_back(source_bitmap);
	bitmap_list.push_back(target_bitmap);

	makeGrids();
	redraw();
}

void Bitmap_window::random()
{
	BinaryBitmap* source_bitmap = bitmap_list[0];
	for (int r = 0; r < source_bitmap->getHeight(); r++)
	{
		for (int c = 0; c < source_bitmap->getWidth(); c++)
		{
			bool v = false;
			double dice = (double)rand() / (double)RAND_MAX;
			if (dice < 0.5)
			{
				v = true;
			}
			source_bitmap->set(c, r, v);
		}
	}

	BinaryBitmap* target_bitmap = bitmap_list[1];
	*target_bitmap = *source_bitmap;

	updateGrids();
}

void Bitmap_window::clear()
{
	BinaryBitmap* source_bitmap = bitmap_list[0];
	source_bitmap->clear();

	BinaryBitmap* target_bitmap = bitmap_list[1];
	*target_bitmap = *source_bitmap;

	updateGrids();
}

void Bitmap_window::exit()
{
	hide();
}

void Bitmap_window::cb_resize10x10(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).resize10x10();
}

void Bitmap_window::cb_resize20x20(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).resize20x20();
}

void Bitmap_window::cb_resize50x50(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).resize50x50();
}

void Bitmap_window::cb_icon(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).icon();
}

void Bitmap_window::cb_random(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).random();
}

void Bitmap_window::cb_clear(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).clear();
}

void Bitmap_window::cb_exit(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).exit();
}

int main()
{
	int win_width = 900;
	int win_height = 500;
	Point win_tl(0, 0);

	Bitmap_window win(win_tl, win_width, win_height, "Bitmap Test");
	return gui_main();
}
*/
