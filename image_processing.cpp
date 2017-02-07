
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "image_processing.h"

ImageProcessing::ImageProcessing(int width, int height) : width(width), height(height)
{
}

ImageProcessing::~ImageProcessing()
{
}

void ImageProcessing::erosion(unsigned char *data)
{
	unsigned char *buf = new unsigned char[width * height];
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			int wdec = std::max<int>(w - 1, 0);
			int winc = std::min<int>(w + 1, width - 1);
			int hdec = std::max<int>(h - 1, 0);
			int hinc = std::min<int>(h + 1, height - 1);
			unsigned char p1 = data[hdec * width + w   ];
			unsigned char p2 = data[h    * width + wdec];
			unsigned char p3 = data[h    * width + w   ];
			unsigned char p4 = data[h    * width + winc];
			unsigned char p5 = data[hinc * width + w   ];
			if(p1 && p2 && p3 && p4 && p5) {
				buf[h * width + w] = 1;
			} else {
				buf[h * width + w] = 0;
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];
	delete[] buf;
}

void ImageProcessing::dilation(unsigned char *data)
{
	unsigned char *buf = new unsigned char[width * height];
	for(int i = 0; i < width * height; i++)
		buf[i] = 0;
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			int wdec = std::max<int>(w - 1, 0);
			int winc = std::min<int>(w + 1, width - 1);
			int hdec = std::max<int>(h - 1, 0);
			int hinc = std::min<int>(h + 1, height - 1);
			unsigned char value = 1;
			if(data[h * width + w] != 0) {
				buf[hdec * width + w   ] = value;
				buf[h    * width + wdec] = value;
				buf[h    * width + w   ] = value;
				buf[h    * width + winc] = value;
				buf[hinc * width + w   ] = value;
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];
	delete[] buf;
}

void ImageProcessing::labeling(unsigned char *data)
{
	unsigned char *buf = new unsigned char[width * height];
	const int lookup_table_size = 256; /* 8bits */
	const int lookup_num = 4; /* left-up, up, right-up, left */
	int last_num = 0;
	int map[lookup_table_size];
	bool use_flag[lookup_table_size];
	std::vector<std::pair<int, int> > lookup_table;
	std::vector<int> table[lookup_table_size * 10];
	std::vector<int> list;
	int next_index = 1;
	int new_index_map[lookup_table_size];

	for(int i = 0; i < width * height; i++)	buf[i] = 0;
	for(int i = 0; i < lookup_table_size; i++) map[i] = i;
	for(int i = 0; i < lookup_table_size; i++) use_flag[i] = false;
	for(int i = 0; i < lookup_table_size; i++) new_index_map[i] = 0;

	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			if(data[h * width + w] != 0) {
				int wdec = std::max<int>(w - 1, 0);
				int winc = std::min<int>(w + 1, width - 1);
				int hdec = std::max<int>(h - 1, 0);
				unsigned char value[lookup_num];
				value[0] = buf[hdec * width + wdec];
				value[1] = buf[hdec * width + w   ];
				value[2] = buf[hdec * width + winc];
				value[3] = buf[h    * width + wdec];
				if(value[0] == 0 && value[1] == 0 && value[2] == 0 && value[3] == 0) {
					buf[h * width + w] = last_num + 1;
					last_num++;
					use_flag[last_num] = true;
					if(last_num >= lookup_table_size) { /* overflow */
						return;
					}
				} else {
					unsigned char min_value = lookup_table_size - 1;
					for(int i = 0; i < lookup_num; i++) {
						if(value[i] == 0) continue;
						if(value[i] < min_value)
							min_value = value[i];
					}
					buf[h * width + w] = min_value;
					for(int i = 0; i < lookup_num; i++) {
						if(value[i] != 0 && value[i] != min_value)
							lookup_table.push_back(std::make_pair(value[i], min_value));
					}
				}
			}
		}
	}
	if(lookup_table.size() != 0) {
		int index = lookup_table[0].first;
		int num = lookup_table[0].second;
		lookup_table.erase(lookup_table.begin());
		list.push_back(num);
		table[index] = list;
		for(int i = 0, j = 0; i < lookup_table.size(); i++) {
			if(lookup_table[i].first == num) {
				list.push_back(lookup_table[i].second);
			} else if(lookup_table[i].second == num) {
				list.push_back(lookup_table[i].first);
			} else {
				if(j >= list.size()) {
					table[index] = list;
					list.clear();
					j = 0;
				} else {
					num = list[j++];
				}
				continue;
			}
			lookup_table.erase(lookup_table.begin() + i);
			i--;
		}
	}
	for(int i = 0; i < 1000; i++) {
		for(int j = 0; j < table[i].size(); j++) {
			map[table[i][j]] = i;
		}
	}
	for(int i = 1; i < lookup_table_size; i++) {
		if(use_flag[i] == true) {
			if(new_index_map[map[i]] == 0) {
				new_index_map[map[i]] = next_index++;
				map[i] = new_index_map[map[i]];
			} else {
				map[i] = new_index_map[map[i]];
			}
		} else {
			map[i] = 0;
		}
	}
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			unsigned char value = buf[h * width + w];
			if(value != 0) {
				buf[h * width + w] = map[(int)value];
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];
	delete[] buf;
}

