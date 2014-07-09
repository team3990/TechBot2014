/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "t4kBinaryImage.h"
//#include "WPIErrors.h"
//#include <cstring>

/** Private NI function needed to write to the VxWorks target */
//IMAQ_FUNC int Priv_SetWriteFileAllowed(uint32_t enable); 

t4kBinaryImage::t4kBinaryImage()
: BinaryImage()
{
}

t4kBinaryImage::~t4kBinaryImage()
{
}

int t4kBinaryImage::ParticleFilter(ParticleFilterCriteria2 *criteria, int criteriaCount, t4kBinaryImage& iResult)
{
  //t4kBinaryImage *result = new t4kBinaryImage();
  int numParticles;
  ParticleFilterOptions2 filterOptions = {0, 0, 0, 1};
  int success = imaqParticleFilter4(iResult.GetImaqImage(), m_imaqImage, criteria, criteriaCount, &filterOptions, NULL, &numParticles);
  wpi_setImaqErrorWithContext(success, "Error in particle filter operation");
  
  return success;
}
