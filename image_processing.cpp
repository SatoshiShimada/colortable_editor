
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "image_processing.h"

ImageProcessing::ImageProcessing(int width, int height) : width(width), height(height), lookup_table_size(0xff * sizeof(int) /* max number of sizeof(int) byte */), size_threshold(1)

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

void ImageProcessing::labelingProcess(unsigned int *data)
{
	unsigned int *buf = new unsigned int[width * height];
	const int lookup_num = 4; /* left-up, up, right-up, left */
	unsigned int last_num = 0;
	unsigned int map[lookup_table_size];
	bool use_flag[lookup_table_size];
	std::vector<std::pair<unsigned int, unsigned int> > lookup_table;
	std::vector<unsigned int> *table = new std::vector<unsigned int>[lookup_table_size * 10];
	std::vector<unsigned int> list;
	unsigned int new_index_map[lookup_table_size];

	for(unsigned int i = 0; i < (unsigned int)(width * height); i++) buf[i] = 0;
	for(unsigned int i = 0; i < lookup_table_size; i++) map[i] = i;
	for(unsigned int i = 0; i < lookup_table_size; i++) use_flag[i] = false;
	for(unsigned int i = 0; i < lookup_table_size; i++) new_index_map[i] = 0;

	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			if(data[h * width + w] != 0) {
				int wdec = std::max<int>(w - 1, 0);
				int winc = std::min<int>(w + 1, width - 1);
				int hdec = std::max<int>(h - 1, 0);
				unsigned int value[lookup_num];
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
					unsigned int min_value = lookup_table_size - 1;
					for(int i = 0; i < lookup_num; i++) {
						if(value[i] == 0) continue;
						if(value[i] < min_value) min_value = value[i];
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
	while(lookup_table.size() != 0) {
		list.clear();
		list.push_back(lookup_table[0].first);
		list.push_back(lookup_table[0].second);
		lookup_table.erase(lookup_table.begin());
loop:
		bool none = true;
		for(unsigned int i = 0; i < lookup_table.size(); ) {
			unsigned int num1 = lookup_table[i].first;
			unsigned int num2 = lookup_table[i].second;
			bool found = false;
			for(int j = 0; j < list.size(); j++) {
				if(num1 == list[j]) {
					list.push_back(num2);
					found = true;
					none = false;
					break;
				} else if(num2 == list[j]) {
					list.push_back(num1);
					found = true;
					none = false;
					break;
				}
			}
			if(!found) {
				i++;
				continue;
			}
			lookup_table.erase(lookup_table.begin() + i);
		}
		std::sort(list.begin(), list.end());
		list.erase(std::unique(list.begin(), list.end()), list.end());
		if(!none) goto loop;
		if(list.size() != 0)
			table[list[0]] = list;
	}
	for(unsigned int i = 0; i < lookup_table_size * 10; i++) {
		if(table[i].size() != 0) {
			int index = table[i][0];
			for(unsigned int j = 1; j < table[i].size(); j++) {
				map[table[i][j]] = index;
			}
		}
	}
	for(unsigned int i = 1, next_index = 1; i < lookup_table_size; i++) {
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
			unsigned int value = buf[h * width + w];
			if(value != 0) {
				buf[h * width + w] = map[value];
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];

	delete[] buf;
	delete[] table;
}

void ImageProcessing::labeling(unsigned char *data)
{
	unsigned int *int_data = new unsigned int[width * height];

	for(int i = 0; i < width * height; i++)
		int_data[i] = (unsigned int)data[i];
	labelingProcess(int_data);
	for(int i = 0; i < width * height; i++)
		data[i] = (unsigned char)int_data[i];
	delete[] int_data;
}

void ImageProcessing::labelingWithSize(unsigned char *data)
{
	labelingWithSize(data, size_threshold);
}

void ImageProcessing::labelingWithSize(unsigned char *data, unsigned int threshold)
{
	unsigned int *int_data = new unsigned int[width * height];
	unsigned int region_size[lookup_table_size];
	int map[lookup_table_size];

	for(unsigned int i = 0; i < lookup_table_size; i++)
		region_size[i] = 0;
	for(int i = 0; i < width * height; i++)
		int_data[i] = (unsigned int)data[i];
	labelingProcess(int_data);
	for(int i = 0; i < width * height; i++)
		region_size[int_data[i]]++;
	for(unsigned int i = 0; i < lookup_table_size; i++) {
		if(region_size[i] < threshold) {
			map[i] = 0;
		} else {
			map[i] = i;
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = map[int_data[i]];
	delete[] int_data;
}

void ImageProcessing::eliminateIsolatedPixel(unsigned char *data)
{
	unsigned char *buf = new unsigned char[width * height];
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			if(data[h * width + w] != 0) {
				int wdec = std::max<int>(w - 1, 0);
				int winc = std::min<int>(w + 1, width - 1);
				int hdec = std::max<int>(h - 1, 0);
				int hinc = std::min<int>(h + 1, height - 1);
				unsigned char p1 = data[hdec * width + w   ];
				unsigned char p2 = data[h    * width + wdec];
				unsigned char p3 = data[h    * width + winc];
				unsigned char p4 = data[hinc * width + w   ];
				if(p1 || p2 || p3 || p4) {
					buf[h * width + w] = 1;
				} else {
					buf[h * width + w] = 0;
				}
			} else {
				buf[h * width + w] = 0;
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];
	delete[] buf;
}

void ImageProcessing::fill(unsigned char *data)
{
	unsigned char *buf = new unsigned char[width * height];
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			if(data[h * width + w] == 0) {
				int wdec = std::max<int>(w - 1, 0);
				int winc = std::min<int>(w + 1, width - 1);
				int hdec = std::max<int>(h - 1, 0);
				int hinc = std::min<int>(h + 1, height - 1);
				unsigned char p1 = data[hdec * width + w   ];
				unsigned char p2 = data[h    * width + wdec];
				unsigned char p3 = data[h    * width + winc];
				unsigned char p4 = data[hinc * width + w   ];
				if(p1 && p2 && p3 && p4) {
					buf[h * width + w] = 1;
				} else {
					buf[h * width + w] = 0;
				}
			} else {
				buf[h * width + w] = 1;
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];
	delete[] buf;
}

