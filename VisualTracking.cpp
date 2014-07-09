/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "VisualTracking.h"

//#include "WPILib.h"
//#include "Vision/RGBImage.h"
//#include "Vision/BinaryImage.h"
#include "Math.h"


//Camera constants used for distance calculation
#define Y_IMAGE_RES 480		//X Image resolution in pixels, should be 120, 240 or 480
#define VIEW_ANGLE 49		//Axis M1013
//#define VIEW_ANGLE 41.7		//Axis 206 camera
//#define VIEW_ANGLE 37.4  //Axis M1011 camera
#define PI 3.141592653


//Score limits used for hot target determination
#define TAPE_WIDTH_LIMIT 50
#define VERTICAL_SCORE_LIMIT 50
#define LR_SCORE_LIMIT 50

//Minimum area of particles to be considered
#define AREA_MINIMUM 150

//Maximum number of particles to process
#define MAX_PARTICLES 8


// AxisCamera& g_Camera(AxisCamera::GetInstance("10.39.90.11"));

/* --------------------------------------------------------------------------- */
// Constructors 

VisualTracking::VisualTracking()
:  m_TargetToFind(c_VisTarget_None)
  ,m_IsActive(false)
  ,m_AccessCounter(0)
  ,m_HSVThresholds(110, 145, 100, 255, 100, 255)  //HSV threshold criteria, ranges are in that order ie. Hue is 60-100
{
}

VisualTracking::~VisualTracking()
{
}

/* --------------------------------------------------------------------------- */
// Methods 

void VisualTracking::FindTarget(bool& o_LeftTargetFound,  bool& o_LeftTargetHot,
                                bool& o_RightTargetFound, bool& o_RightTargetHot)
{
  o_LeftTargetFound  = false;
  o_LeftTargetHot    = false;
  o_RightTargetFound = false;
  o_RightTargetHot   = false;
 
  //AxisCamera &camera = AxisCamera::GetInstance("10.39.90.11");  //To use the Axis camera uncomment this line
  
//  printf("Is fresh:%d - #%d\n", (int)g_Camera.IsFreshImage(), m_AccessCounter++);
  
  if (m_IsActive )//&& g_Camera.IsFreshImage())
  {
    processImage(o_LeftTargetFound,  o_LeftTargetHot,
                 o_RightTargetFound, o_RightTargetHot);
  }
}

void VisualTracking::processImage(bool& o_LeftTargetFound,  bool& o_LeftTargetHot,
                                  bool& o_RightTargetFound, bool& o_RightTargetHot)
{
  Scores * scores;
  int verticalTargets[MAX_PARTICLES];
  int horizontalTargets[MAX_PARTICLES];
  int verticalTargetCount, horizontalTargetCount;
  ParticleFilterCriteria2 criteria[] = {  {IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false} };
                                          //Particle filter criteria, used to filter out small particles
    
  /**
    * Do the image capture with the camera and apply the algorithm described above. This
    * sample will either get images from the camera or from an image file stored in the top
    * level directory in the flash memory on the cRIO. The file name in this case is "testImage.jpg"
    */
  //image = new RGBImage("/testImage.jpg");    // get the sample image from the cRIO flash

  int result =  0; //g_Camera.GetImage(&m_Image);         //To get the images from the camera comment the line above and uncomment this one
  if (result)
  {
    int result_thres = m_Image.ThresholdHSV(m_HSVThresholds, m_ThresholdImage);  // get just the green target pixels
    if (result_thres)
    {
      //thresholdImage->Write("/threshold.bmp");
      int result_filtered = m_ThresholdImage.ParticleFilter(criteria, 1, m_FilteredImage);  //Remove small particles
      //filteredImage->Write("Filtered.bmp");
    
      if (result_filtered)
      {
        vector<ParticleAnalysisReport> *reports = m_FilteredImage.GetOrderedParticleAnalysisReports();  //get a particle analysis report for each particle
      
        verticalTargetCount   = 0;
        horizontalTargetCount = 0;
        //Iterate through each particle, scoring it and determining whether it is a target or not
        if (reports->size() > 0)
        {
          scores = new Scores[reports->size()];
          for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++)
          {
            ParticleAnalysisReport *report = &(reports->at(i));
              
            //Score each particle on rectangularity and aspect ratio
            scores[i].rectangularity        = scoreRectangularity(report);
            scores[i].aspectRatioVertical   = scoreAspectRatio(m_FilteredImage, report, true);
            scores[i].aspectRatioHorizontal = scoreAspectRatio(m_FilteredImage, report, false);      
              
            //Check if the particle is a horizontal target, if not, check if it's a vertical target
            if (scoreCompare(scores[i], false))
            {
              //printf("particle: %d  is a Horizontal Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
              horizontalTargets[horizontalTargetCount++] = i; //Add particle to target array and increment count
            }
            else if (scoreCompare(scores[i], true))
            {
              //printf("particle: %d  is a Vertical Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
              verticalTargets[verticalTargetCount++] = i;  //Add particle to target array and increment count
            }
            else
            {
              //printf("particle: %d  is not a Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
            }
      
            //printf("Scores rect: %f  ARvert: %f \n", scores[i].rectangularity, scores[i].aspectRatioVertical);
            //printf("ARhoriz: %f  \n", scores[i].aspectRatioHorizontal);  
          }
      
          //Zero out scores and set verticalIndex to first target in case there are no horizontal targets
          TargetReport target_left;
          TargetReport target_right;
          target_left.verticalIndex  = verticalTargets[0];
          target_right.verticalIndex = verticalTargets[0];
          
          printf("VisualTracking: %d vertical, %d horizontal\n", verticalTargetCount, horizontalTargetCount);
          
          for (int i = 0; i < verticalTargetCount; i++)
          {
            ParticleAnalysisReport *verticalReport = &(reports->at(verticalTargets[i]));
            for (int j = 0; j < horizontalTargetCount; j++)
            {
              ParticleAnalysisReport *horizontalReport = &(reports->at(horizontalTargets[j]));
              double horizWidth, horizHeight, vertWidth, leftScore, rightScore, tapeWidthScore, verticalScore, total_left, total_right;
      
              //Measure equivalent rectangle sides for use in score calculation
              imaqMeasureParticle(m_FilteredImage.GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);
              imaqMeasureParticle(m_FilteredImage.GetImaqImage(), verticalReport->particleIndex,   0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
              imaqMeasureParticle(m_FilteredImage.GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizHeight);
                
              //Determine if the horizontal target is in the expected location to the left of the vertical target
              leftScore      = ratioToScore(1.2*(verticalReport->boundingRect.left - horizontalReport->center_mass_x)/horizWidth);
              
              //Determine if the horizontal target is in the expected location to the right of the  vertical target
              rightScore     = ratioToScore(1.2*(horizontalReport->center_mass_x - verticalReport->boundingRect.left - verticalReport->boundingRect.width)/horizWidth);
              
              printf("leftScore: %f  rightScore: %f\n", leftScore, rightScore);
              
              //Determine if the width of the tape on the two targets appears to be the same
              tapeWidthScore = ratioToScore(vertWidth/horizHeight);
              
              //Determine if the vertical location of the horizontal target appears to be correct
              verticalScore  = ratioToScore(1-(verticalReport->boundingRect.top - horizontalReport->center_mass_y)/(4*horizHeight));
              //
              total_left  = leftScore  + tapeWidthScore + verticalScore;
              total_right = rightScore + tapeWidthScore + verticalScore;
                
              //If the target is the best LEFT detected so far store the information about it
              if (total_left > target_left.totalScore)
              {
                target_left.horizontalIndex = horizontalTargets[j];
                target_left.verticalIndex   = verticalTargets[i];
                target_left.totalScore      = total_left;
                target_left.leftScore       = leftScore;
                target_left.rightScore      = rightScore;
                target_left.tapeWidthScore  = tapeWidthScore;
                target_left.verticalScore   = verticalScore;
              }

              //If the target is the best RIGHT detected so far store the information about it
              if (total_right > target_right.totalScore)
              {
                target_right.horizontalIndex = horizontalTargets[j];
                target_right.verticalIndex   = verticalTargets[i];
                target_right.totalScore      = total_right;
                target_right.leftScore       = leftScore;
                target_right.rightScore      = rightScore;
                target_right.tapeWidthScore  = tapeWidthScore;
                target_right.verticalScore   = verticalScore;
              }
            }

            //Determine if the best targets are Hot target
            target_left.Hot  = hotOrNot(target_left);
            target_right.Hot = hotOrNot(target_right);
          }
          
          //printf("VisualTracking: %d HOT\n", (int)o_TargetHot);
          
          if (verticalTargetCount > 0)
          {
            if (target_left.leftScore > target_left.rightScore)
            {
              o_LeftTargetFound = true;
              if (target_left.Hot == true)
              {
                o_LeftTargetHot = true;
              }
            }
            else if (target_left.leftScore < target_left.rightScore)
            {
              o_RightTargetFound = true;
              if (target_left.Hot == true)
              {
                o_RightTargetHot = true;
              }
            }
            else
            {
              o_LeftTargetFound  = true;
              o_RightTargetFound = true;
            }
            
            //Information about the target is contained in the "target" structure
            //To get measurement information such as sizes or locations use the
            //horizontal or vertical index to get the particle report as shown below
            //ParticleAnalysisReport *distanceReport = &(reports->at(target.verticalIndex));
            //double distance = computeDistance(filteredImage, distanceReport);
            //if (target.Hot)
            //{
            //  //printf("Hot target located \n");
            //  //printf("Distance: %f \n", distance);
            //}
            //else
            //{
            //  //printf("No hot target present \n");
            //  //printf("Distance: %f \n", distance);
            //}
          }
        }
      
        // be sure to delete images after using them
        //delete filteredImage;
        //delete thresholdImage;
        //delete image;
          
        //delete allocated reports and Scores objects also
        delete scores;
        delete reports;
      }
    }
  }
}

/**
  * Computes the estimated distance to a target using the height of the particle in the image. For more information and graphics
  * showing the math behind this approach see the Vision Processing section of the ScreenStepsLive documentation.
  * 
  * @param image The image to use for measuring the particle estimated rectangle
  * @param report The Particle Analysis Report for the particle
  * @return The estimated distance to the target in feet.
  */
double VisualTracking::computeDistance (BinaryImage *image, ParticleAnalysisReport *report)
{
  double rectLong, height;
  int targetHeight;
    
  imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
  //using the smaller of the estimated rectangle long side and the bounding rectangle height results in better performance
  //on skewed rectangles
  height = min(report->boundingRect.height, rectLong);
  targetHeight = 32;
    
  return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/(180*2)));
}

/**
  * Computes a score (0-100) comparing the aspect ratio to the ideal aspect ratio for the target. This method uses
  * the equivalent rectangle sides to determine aspect ratio as it performs better as the target gets skewed by moving
  * to the left or right. The equivalent rectangle is the rectangle with sides x and y where particle area= x*y
  * and particle perimeter= 2x+2y
  * 
  * @param image The image containing the particle to score, needed to perform additional measurements
  * @param report The Particle Analysis Report for the particle, used for the width, height, and particle number
  * @param outer  Indicates whether the particle aspect ratio should be compared to the ratio for the inner target or the outer
  * @return The aspect ratio score (0-100)
  */
double VisualTracking::scoreAspectRatio(t4kBinaryImage& iImage, ParticleAnalysisReport *report, bool vertical)
{
  double rectLong, rectShort, idealAspectRatio, aspectRatio;
  idealAspectRatio = vertical ? (4.0/32) : (23.5/4);  //Vertical reflector 4" wide x 32" tall, horizontal 23.5" wide x 4" tall
  
  imaqMeasureParticle(iImage.GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
  imaqMeasureParticle(iImage.GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
    
  //Divide width by height to measure aspect ratio
  if (report->boundingRect.width > report->boundingRect.height)
  {
    //particle is wider than it is tall, divide long by short
    aspectRatio = ratioToScore(((rectLong/rectShort)/idealAspectRatio));
  }
  else
  {
    //particle is taller than it is wide, divide short by long
    aspectRatio = ratioToScore(((rectShort/rectLong)/idealAspectRatio));
  }

  return aspectRatio;    //force to be in range 0-100
}

/**
  * Compares scores to defined limits and returns true if the particle appears to be a target
  * 
  * @param scores The structure containing the scores to compare
  * @param vertical True if the particle should be treated as a vertical target, false to treat it as a horizontal target
  * 
  * @return True if the particle meets all limits, false otherwise
  */
bool VisualTracking::scoreCompare(Scores scores, bool vertical)
{
  bool isTarget = true;

  //float rectangularity = scores.rectangularity;
  //float rectangularity_limit = RECTANGULARITY_LIMIT;
  //printf("\nrectangularity %f > RECTANGULARITY_LIMIT %f\n", rectangularity, rectangularity_limit);
  isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
  if (vertical)
  {
    //float aspectRatioVertical = scores.aspectRatioVertical;
    //float aspectRatio_limit = ASPECT_RATIO_LIMIT;
    //printf("aspectRatioVertical %f > ASPECT_RATIO_LIMIT %f\n", aspectRatioVertical, aspectRatio_limit);
    isTarget &= scores.aspectRatioVertical > ASPECT_RATIO_LIMIT;
  }
  else
  {
    isTarget &= scores.aspectRatioHorizontal > ASPECT_RATIO_LIMIT;
  }

  //printf("isTarget %d\n\n", isTarget);
  return isTarget;
}

/**
  * Computes a score (0-100) estimating how rectangular the particle is by comparing the area of the particle
  * to the area of the bounding box surrounding it. A perfect rectangle would cover the entire bounding box.
  * 
  * @param report The Particle Analysis Report for the particle to score
  * @return The rectangularity score (0-100)
  */
double VisualTracking::scoreRectangularity(ParticleAnalysisReport *report)
{
  if (report->boundingRect.width*report->boundingRect.height !=0)
  {
    return 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
  }
    
  return 0;  
}

/**
  * Converts a ratio with ideal value of 1 to a score. The resulting function is piecewise
  * linear going from (0,0) to (1,100) to (2,0) and is 0 for all inputs outside the range 0-2
  */
double VisualTracking::ratioToScore(double ratio)
{
  return (max(0, min(100*(1-fabs(1-ratio)), 100)));
}

/**
  * Takes in a report on a target and compares the scores to the defined score limits to evaluate
  * if the target is a hot target or not.
  * 
  * Returns True if the target is hot. False if it is not.
  */
bool VisualTracking::hotOrNot(TargetReport target)
{
  bool isHot = true;
    
  isHot &= target.tapeWidthScore >= TAPE_WIDTH_LIMIT;
  isHot &= target.verticalScore >= VERTICAL_SCORE_LIMIT;
  isHot &= (target.leftScore > LR_SCORE_LIMIT) | (target.rightScore > LR_SCORE_LIMIT);
    
  return isHot;
}
