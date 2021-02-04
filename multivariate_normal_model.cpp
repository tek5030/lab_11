#include "multivariate_normal_model.h"
#include "opencv2/imgproc.hpp"


MultivariateNormalModel::MultivariateNormalModel(const cv::Mat& samples)
{
  performTraining(samples);
}


void MultivariateNormalModel::performTraining(const cv::Mat& samples)
{
  // TODO 1.1: Train the multivariate normal model by estimating the mean and covariance given the samples.
  mean_ = cv::Mat::ones(3, 1, CV_64F) * 127.;  // Dummy, replace
  covariance_ = cv::Mat::eye(3, 3, CV_64F);    // Dummy, replace

  // TODO 1.2: Compute the inverse of the estimated covariance.
  inverse_covariance_ = cv::Mat::eye(3, 3, CV_64F);   // Dummy, replace
}


cv::Mat MultivariateNormalModel::computeMahalanobisDistances(const cv::Mat& image) const
{
  // We need to represent the distances in uint8 because of Otsu's method.
  // We get a pretty good representation by multiplying the distances with 1000.
  constexpr double dist_to_uint8_scale = 1000.0;

  cv::Mat mahalanobis_img(image.size(), CV_8UC1);

  //TODO 2: Compute the mahalanobis distance for each pixel feature vector wrt the multivariate normal model.
  mahalanobis_img.setTo(static_cast<uint8_t>(dist_to_uint8_scale * 1.0)); // Dummy, replace

  return mahalanobis_img;
}


cv::Mat MultivariateNormalModel::mean() const
{
  return mean_.clone();
}


cv::Mat MultivariateNormalModel::covariance() const
{
  return covariance_.clone();
}


cv::Mat MultivariateNormalModel::inverseCovariance() const
{
  return inverse_covariance_.clone();
}
