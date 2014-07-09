/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __T4K_BINARY_IMAGE_H__
#define __T4K_BINARY_IMAGE_H__


#include "Vision/BinaryImage.h"

/**
 * Included for ParticleAnalysisReport definition
 * TODO: Eliminate this dependency! 
 */
//#include "Vision2009/VisionAPI.h"

//#include <vector>
//#include <algorithm>
//using namespace std;

class t4kBinaryImage : public BinaryImage
{
public:
        t4kBinaryImage();
	virtual ~t4kBinaryImage();
	
	
	//int GetNumberParticles();
	//ParticleAnalysisReport GetParticleAnalysisReport(int particleNumber);
	//void GetParticleAnalysisReport(int particleNumber, ParticleAnalysisReport *par);
	//vector<ParticleAnalysisReport>* GetOrderedParticleAnalysisReports();
	//BinaryImage *RemoveSmallObjects(bool connectivity8, int erosions);
	//BinaryImage *RemoveLargeObjects(bool connectivity8, int erosions);
	//BinaryImage *ConvexHull(bool connectivity8);
	int ParticleFilter(ParticleFilterCriteria2 *criteria, int criteriaCount, t4kBinaryImage& iResult);
	//virtual void Write(const char *fileName);
	
private:
	//bool ParticleMeasurement(int particleNumber, MeasurementType whatToMeasure, int *result);
	//bool ParticleMeasurement(int particleNumber, MeasurementType whatToMeasure, double *result);
	//static double NormalizeFromRange(double position, int range);
	//static bool CompareParticleSizes(ParticleAnalysisReport particle1, ParticleAnalysisReport particle2);
};

#endif // __T4K_BINARY_IMAGE_H__
