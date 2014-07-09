/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __T4K_HSV_IMAGE_H__
#define __T4K_HSV_IMAGE_H__

//#include "WPILib.h"

#include "Vision/ColorImage.h"

#include "t4kBinaryImage.h"


/**
 * A color image represented in HSV color space at 3 bytes per pixel.
 */
class t4kHSLImage : public ColorImage
{
public:
  t4kHSLImage();
  t4kHSLImage(const char *fileName);
  virtual ~t4kHSLImage();
  

  /**
   * Perform a threshold operation on a ColorImage.
   * Perform a threshold operation on a ColorImage using the ColorMode supplied
   * as a parameter.
   * @param colorMode The type of colorspace this operation should be performed in
   * @returns a pointer to a binary image
   */
  int ComputeThreshold(ColorMode colorMode,
                       int low1, int high1,
                       int low2, int high2,
                       int low3, int high3,
                       t4kBinaryImage& iResult);
  

  /**
   * Perform a threshold in HSV space.
   * @param threshold a reference to the Threshold object to use.
   * @returns A pointer to a BinaryImage that represents the result of the threshold operation.
   */
  int ThresholdHSV(Threshold &t, t4kBinaryImage& iResult);
  
};

#endif  // __T4K_HSL_IMAGE_H__
