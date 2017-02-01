
#ifndef _COLORTABLE_H_
#define _COLORTABLE_H_

typedef unsigned long table;

class ColorTable
{
public:
	ColorTable();
	~ColorTable();
	void clearColorTable(unsigned int, table);
	void setColorTable(unsigned int, table);
	table getColorTable(unsigned int);
	bool clear(void);
	bool save(const char *);
	bool load(const char *);
	static const int max_categolies = 6;
	static enum {
		none = 0,
		ball = 1 << 0,
		goal = 1 << 1,
		white_line = 1 << 2,
		field = 1 << 3,
		robot = 1 << 4,
		background = 1 << 5,
	} categoly_list;
protected:
	table *color_table;
	int color_table_size;
};

#endif // _COLORTABLE_H_

