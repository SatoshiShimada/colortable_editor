
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

void ColorTable::clearColorTable(unsigned int index, table value, int margin)
{
	if(margin == 0) clearColorTable(index, value);
	int r = (index >> 16) & 0xff;
	int g = (index >>  8) & 0xff;
	int b = (index >>  0) & 0xff;
	for(int ri = std::max<int>(r - margin, 0); ri < std::min<int>(r + margin, 255); ri++) {
		for(int gi = std::max<int>(g - margin, 0); gi < std::min<int>(g + margin, 255); gi++) {
			for(int bi = std::max<int>(b - margin, 0); bi < std::min<int>(b + margin, 255); bi++) {
				index = ((ri << 16) | (gi << 8) | (bi << 0)) & (color_table_size - 1);
				color_table[index] &= ~value;
			}
		}
	}
}

void ColorTable::setColorTable(unsigned int index, table value)
{
	index &= color_table_size - 1;
	color_table[index] |= value;
}

void ColorTable::setColorTable(unsigned int index, table value, int margin)
{
	if(margin == 0) setColorTable(index, value);
	int r = (index >> 16) & 0xff;
	int g = (index >>  8) & 0xff;
	int b = (index >>  0) & 0xff;
	for(int ri = std::max<int>(r - margin, 0); ri < std::min<int>(r + margin, 255); ri++) {
		for(int gi = std::max<int>(g - margin, 0); gi < std::min<int>(g + margin, 255); gi++) {
			for(int bi = std::max<int>(b - margin, 0); bi < std::min<int>(b + margin, 255); bi++) {
				index = ((ri << 16) | (gi << 8) | (bi << 0)) & (color_table_size - 1);
				color_table[index] |= value;
			}
		}
	}
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

bool ColorTable::clearCategory(table value)
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

bool ColorTable::apply(int width, int height, const unsigned char *src, unsigned char *dst, table category)
{
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			unsigned char r = src[(h * width + w) * 3 + 0];
			unsigned char g = src[(h * width + w) * 3 + 1];
			unsigned char b = src[(h * width + w) * 3 + 2];
			unsigned int index = ((r << 16) | (g << 8) | (b << 0)) & (color_table_size - 1);
			if(color_table[index] & category) {
				dst[h * width + w] = 1;
			} else {
				dst[h * width + w] = 0;
			}
		}
	}
	return true;
}

