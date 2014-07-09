/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "t4kHSLImage.h"

/**
 * Create a new image that uses the Hue, Saturation, and Luminance planes.
 */
t4kHSLImage::t4kHSLImage() : ColorImage(IMAQ_IMAGE_HSL)
{
}

/**
 * Create a new image by loading a file.
 * @param fileName The path of the file to load.
 */
t4kHSLImage::t4kHSLImage(const char *fileName) : ColorImage(IMAQ_IMAGE_HSL)
{
  int success = imaqReadFile(m_imaqImage, fileName, NULL, NULL);
  wpi_setImaqErrorWithContext(success, "Imaq ReadFile error");
}

t4kHSLImage::~t4kHSLImage()
{
}


/**
 * Perform a threshold operation on a ColorImage.
 * Perform a threshold operation on a ColorImage using the ColorMode supplied
 * as a parameter.
 * @param colorMode The type of colorspace this operation should be performed in
 * @returns a pointer to a binary image
 */
int t4kHSLImage::ComputeThreshold(ColorMode colorMode,
                                  int low1, int high1,
                                  int low2, int high2,
                                  int low3, int high3,
                                  t4kBinaryImage& iResult)
{
  Range range1 = {low1, high1},
        range2 = {low2, high2},
        range3 = {low3, high3};
  
  int success = imaqColorThreshold(iResult.GetImaqImage(), m_imaqImage, 1, colorMode, &range1, &range2, &range3);
  wpi_setImaqErrorWithContext(success, "ImaqThreshold error");
  
  return success;
}


/**
 * Perform a threshold in HSV space.
 * @param threshold a reference to the Threshold object to use.
 * @returns A pointer to a BinaryImage that represents the result of the threshold operation.
 */
int t4kHSLImage::ThresholdHSV(Threshold &t, t4kBinaryImage& iResult)
{
  return ComputeThreshold(IMAQ_HSV, t.plane1Low, t.plane1High,
                                    t.plane2Low, t.plane2High,
                                    t.plane3Low, t.plane3High,
                                    iResult);
}
