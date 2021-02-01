#include "multivariate_normal_model.h"
#include "opencv2/imgproc.hpp"

MultivariateNormalModel::MultivariateNormalModel()
    : is_trained_{false}
{}

bool MultivariateNormalModel::isTrained() const
{ return is_trained_; }

void MultivariateNormalModel::performTraining(const cv::Mat& samples)
{
  //TODO 1: Estimate inv_covar_ and mu_ for the given samples
  inv_covar_ = cv::Mat::eye(3,3,CV_64F);   //Replace
  mu_ = cv::Mat::ones(3,1,CV_64F) * 127.;  //Replace

  samples_ = samples.clone();
  is_trained_ = true;
}

cv::Mat MultivariateNormalModel::computeMahalanobisDistances(const cv::Mat& image) const
{
  cv::Mat image_64;
  image.convertTo(image_64, CV_64FC3);

  cv::Mat mahalanobis_dist(image.size(), CV_64FC1);

  //TODO 2: Compute the mahalanobis distance for each image pixel wrt the multivariate normal model
  mahalanobis_dist.setTo(0.5); //Not like this...

  return mahalanobis_dist;
}

cv::Mat MultivariateNormalModel::computeTransformedMahalanobisImage(const cv::Mat& image) const
{
  if (!is_trained_)
  { throw std::runtime_error("You forgot to train the model before trying to compute the transformed Mahalanobis image!"); }

  //TODO 3: Compute the transformed Mahalanobis image
  cv::Mat transformed_maha = cv::Mat::ones(image.rows, image.cols, CV_64F); //Replace

  return transformed_maha;
}

void MultivariateNormalModel::update(const cv::Mat& new_samples, const float update_ratio)
{
  // TODO 4: Implement a random update of samples_ by the given ratio of new_samples

  performTraining(samples_);
}

cv::Mat segmentImage(const cv::Mat& input_image, int threshold_value, bool use_otsu)
{
  int thresh_type = cv::THRESH_BINARY;
  if (use_otsu)
  { thresh_type |= cv::THRESH_OTSU; }

  cv::Mat segmented_image;
  cv::threshold(input_image, segmented_image, threshold_value, 255, thresh_type);
  return segmented_image;
}

cv::Rect getSamplingRectangle(const cv::Size& img_size)
{
  int center_x = img_size.width/2;
  int center_y = 4*img_size.height/5;
  int width = 100;
  int height = 80;
  int top_left_x = center_x - width/2;
  int top_left_y = center_y - height/2;

  const cv::Rect sampling_rectangle(top_left_x, top_left_y, width, height);
  const cv::Rect entire_image(0,0,img_size.width,img_size.height);

  // This operation ensures that the boundardies of the returned sampling rectange is within the image's dimentions,
  // just in case the chosen width or height is to large.
  return (sampling_rectangle & entire_image );
}

cv::Mat extractTrainingSamples(const cv::Mat& source_image, const cv::Rect& sampling_rectangle)
{
  cv::Mat patch = source_image(sampling_rectangle).clone();
  cv::Mat samples = patch.reshape(1, patch.total()).t();
  return samples;
}

void drawSamplingRectangle(cv::Mat& image, const cv::Rect& sampling_rectangle)
{
  const cv::Scalar color{0, 0, 255};
  constexpr int thickness = 2;
  cv::rectangle(image, sampling_rectangle, color, thickness);
}
