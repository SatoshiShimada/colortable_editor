
#ifndef __LABELINGIMAGEDATA_H__
#define __LABELINGIMAGEDATA_H__

#include <vector>

#include "color_table.h"
#include "image_processing.h"

class LabelingImageData
{
 public:
  LabelingImageData(int, int, int);
  ~LabelingImageData();
  void setData(int, unsigned char *);
  unsigned char *getData(int);
  unsigned char *getCurrentData(void);
  void loadColorTable(const char *);
  void saveColorTable(const char *);
  void clearAllColorTable(void);
  void clearColorTable(void);
  void applyColorTable();
  void clearBitColorTable(int, int);
  void setBitColorTable(int, int);
  void erosion();
  void dilation();
  void setIndex(int);
  void setMargin(int);
  void exportImage(const char *);
  void setImage(unsigned char *);
  unsigned char *original_data;
  std::vector<unsigned char *> bitmap_data;
 protected:
  const int width;
  const int height;
  const int category_num;
  int currentIndex;
  int margin;
  ColorTable colortable;
  ImageProcessing imageprocessing;
  table tableValue(int);
};

#endif // __LABELINGIMAGEDATA_H__

