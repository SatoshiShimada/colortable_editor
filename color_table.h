
#ifndef __COLORTABLE_H__
#define __COLORTABLE_H__

typedef unsigned long table;

class ColorTable
{
public:
	ColorTable();
	~ColorTable();
	void clearColorTable(unsigned int, table);
	void clearColorTable(unsigned int, table, int);
	void setColorTable(unsigned int, table);
	void setColorTable(unsigned int, table, int);
	table getColorTable(unsigned int);
	bool clear(void);
	bool clearCategory(table);
	bool save(const char *);
	bool load(const char *);
	bool apply(int, int, const unsigned char *, unsigned char *, table);
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

#endif // __COLORTABLE_H__

