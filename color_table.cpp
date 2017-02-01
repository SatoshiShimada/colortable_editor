
#include "color_table.h"

#include <fstream>
#include <iostream>

ColorTable::ColorTable()
{
	color_table_size = 256 * 3; /* 8bits RGB color */
	color_table = new table[color_table_size];
	for(int i = 0; i < color_table_size; i++) {
		color_table[i] = 0;
	}
}

ColorTable::~ColorTable()
{
	delete color_table;
}

void ColorTable::clearColorTable(unsigned int index, table value)
{
	index &= color_table_size - 1;
	color_table[index] &= ~value;
}

void ColorTable::setColorTable(unsigned int index, table value)
{
	index &= color_table_size - 1;
	color_table[index] |= value;
}

table ColorTable::getColorTable(unsigned int index)
{
	index &= color_table_size - 1;
	return color_table[index];
}

bool ColorTable::clear(void)
{
	for(int i = 0; i < color_table_size; i++) {
		color_table[i] = 0;
	}
	return true;
}

bool ColorTable::clearCategoly(table value)
{
	for(int i = 0; i < color_table_size; i++) {
		color_table[i] &= ~value;
	}
	return true;
}

bool ColorTable::save(const char *filename)
{
	std::ofstream fout(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	if(fout.fail()) return false;
	fout.write((char *)color_table, sizeof(table) * color_table_size);
	return true;
}

bool ColorTable::load(const char *filename)
{
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if(fin.fail()) return false;
	fin.read((char *)color_table, sizeof(table) * color_table_size);
	return true;
}

