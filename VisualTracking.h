/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef VISUALTRACKING_H
#define VISUALTRACKING_H

#include "WPILib.h"
#include "t4kHSLImage.h"

#include "Config.h"


//Score limits used for target identification
#define RECTANGULARITY_LIMIT 40
#define ASPECT_RATIO_LIMIT 55

// extern AxisCamera& g_Camera;


class VisualTracking
{ 
    
public:
  
  // Constructors
  VisualTracking();
  ~VisualTracking();
  

  // Instances
  
  
  // Properties
  //Structure to represent the scores for the various tests used for target identification
  struct Scores
  {
    double rectangularity;
    double aspectRatioVertical;
    double aspectRatioHorizontal;
  };
  
  struct TargetReport
  {
    int    verticalIndex;
    int    horizontalIndex;
    bool   Hot;
    double totalScore;
    double leftScore;
    double rightScore;
    double tapeWidthScore;
    double verticalScore;
    
    TargetReport()
    {
      verticalIndex   = 0;
      horizontalIndex = 0;
      Hot             = false;
      totalScore      = 0.0;
      leftScore       = 0.0;
      rightScore      = 0.0;
      tapeWidthScore  = 0.0;
      verticalScore   = 0.0;
    }
  };
  
  enum TargetType
  {
    c_VisTarget_None    = 0,
    c_VisTarget_HotGoal = 1,
    c_VisTarget_BlockedBall,
  };

  enum TargetType m_TargetToFind;
  bool            m_IsActive;
  bool            m_AccessCounter;
  t4kHSLImage     m_Image;
  Threshold       m_HSVThresholds;  //HSV threshold criteria, ranges are in that order ie.
  t4kBinaryImage  m_ThresholdImage;
  t4kBinaryImage  m_FilteredImage;

  //
  // Methods
  //

  void processImage(bool& o_LeftTargetFound,  bool& o_LeftTargetHot,
                    bool& o_RightTargetFound, bool& o_RightTargetHot);


  /**
   * Image processing code to identify 2013 Vision targets
   */
  void ActivateTracking(bool iActive)
  {
    m_IsActive = iActive;
  }

  /**
   * Image processing code to identify 2013 Vision targets
   */
  void SelectTarget(enum TargetType iTarget)
  {
    m_TargetToFind = iTarget;
  }

  void FindTarget(bool& o_LeftTargetFound,  bool& o_LeftTargetHot,
                  bool& o_RightTargetFound, bool& o_RightTargetHot);
  

  /**
   * Computes the estimated distance to a target using the height of the particle in the image. For more information and graphics
   * showing the math behind this approach see the Vision Processing section of the ScreenStepsLive documentation.
   * 
   * @param image The image to use for measuring the particle estimated rectangle
   * @param report The Particle Analysis Report for the particle
   * @return The estimated distance to the target in feet.
   */
  double computeDistance (BinaryImage *image, ParticleAnalysisReport *report);


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
  double scoreAspectRatio(t4kBinaryImage& iImage, ParticleAnalysisReport *report, bool vertical);

  
  /**
   * Compares scores to defined limits and returns true if the particle appears to be a target
   * 
   * @param scores The structure containing the scores to compare
   * @param vertical True if the particle should be treated as a vertical target, false to treat it as a horizontal target
   * 
   * @return True if the particle meets all limits, false otherwise
   */
  bool scoreCompare(Scores scores, bool vertical);
    
  /**
   * Computes a score (0-100) estimating how rectangular the particle is by comparing the area of the particle
   * to the area of the bounding box surrounding it. A perfect rectangle would cover the entire bounding box.
   * 
   * @param report The Particle Analysis Report for the particle to score
   * @return The rectangularity score (0-100)
   */
  double scoreRectangularity(ParticleAnalysisReport *report);

  /**
   * Converts a ratio with ideal value of 1 to a score. The resulting function is piecewise
   * linear going from (0,0) to (1,100) to (2,0) and is 0 for all inputs outside the range 0-2
   */
  double ratioToScore(double ratio);
  
  /**
   * Takes in a report on a target and compares the scores to the defined score limits to evaluate
   * if the target is a hot target or not.
   * 
   * Returns True if the target is hot. False if it is not.
   */
  bool hotOrNot(TargetReport target);
  
};

#endif //VISUALTRACKING_H
