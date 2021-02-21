# Step 2: Implement simple color-based segmentation
First, read through [lab_11.cpp](https://github.com/tek5030/lab_11/blob/master/lab_11.cpp) to get an overview of the lab.

Then, take a look at the declarations and documentation in [multivariate_normal_model.h](https://github.com/tek5030/lab_11/blob/master/multivariate_normal_model.h)
and go to [multivariate_normal_model.cpp](https://github.com/tek5030/lab_11/blob/master/multivariate_normal_model.cpp).
Read through the code to get an overview of the class.

## 1. Implement the method `performTraining()` in `MultivariateNormalModel`
The multivariate normal distribution is characterized by a mean vector **&mu;** and a covariance matrix **&Sigma;**.

![\mathcal{N}(\mathbf{x}; \boldsymbol{\mu}, \boldsymbol{\Sigma}) =
\frac{1}{ (2\pi)^{\frac{k}{2}} \left|\boldsymbol{\Sigma}\right|^{\frac{1}{2}}}
\exp\left[-\textstyle\frac{1}{2}(\boldsymbol{\mu} - \mathbf{x})^{T}\boldsymbol{\Sigma}^{-1}
(\boldsymbol{\mu} - \mathbf{x}) \right]](img/multivariate_normal_distribution.png)

Given such a distribution, the Mahalanobis distance between a vector **x** and the distribution is a measure of how 
well the vector fits with the distribution.

![\mathit{d}_{\mathit{M}}(\mathbf{x}) = \sqrt{(\mathbf{x}-\boldsymbol{\mu})^{T} \boldsymbol{\Sigma}^{-1} 
(\mathbf{x} - \boldsymbol{\mu})}](img/mahalanobis_distance.png)

The method `MultivariateNormalModel::performTraining` should estimate the mean `mean_` and the covariance `covariance_` for the model based on the training samples `samples_` collected from the sampling region.
It must also compute the inverse of the covariance matrix `inverse_covariance`, which we later will use to compute the Mahalanobis distance.

Take a look at [cv::calcCovarMatrix](https://docs.opencv.org/4.0.1/d2/de8/group__core__array.html#ga017122d912af19d7d0d2cccc2d63819f)
and keep in mind that we want `mean_` to be a column vector.
The [cv::CovarFlags](https://docs.opencv.org/4.0.1/d0/de1/group__core.html#ga719ebd4a73f30f4fab258ab7616d0f0f) in `cv::calcCovarMatrix()` can be combined like this: `flag1|flag2`.
See also [cv::invert](https://docs.opencv.org/4.0.1/d2/de8/group__core__array.html#gad278044679d4ecf20f7622cc151aaaa2).

In its current state, the method simply returns **`mean_` = [127; 127; 127]**, **`covariance_` = Identity** and **`inverse_covariance_` = Identity**.
You should replace this with the correct computations.
 
## 2. Implement the method `computeMahalanobisDistances` in `MultivariateNormalModel`
This method should compute the Mahalanobis distance between every pixel in the input image and the estimated multivariate
normal model described by `mean_` and `inverse_covariance_`.

![\mathit{d}_{\mathit{M}}(\mathbf{x}) = \sqrt{(\mathbf{x}-\boldsymbol{\mu})^{T} \boldsymbol{\Sigma}^{-1} 
(\mathbf{x} - \boldsymbol{\mu})}](img/mahalanobis_distance.png)

The method should return a `cv::Mat` of Mahalanobis distances, but in its current state it simply returns a matrix of 0.5's.
You should replace this with a proper implementation.

Take a look at [cv::Mahalanobis](https://docs.opencv.org/4.0.1/d2/de8/group__core__array.html#ga4493aee129179459cbfc6064f051aa7d).


## 3. Implement the method `updateSamples`
In order to make our segmentation more relevant for dynamic situations, e.g. when the camera is moving, we would our 
multivariate normal model to change over time.

A simple solution would be to continously retrain the model based on the latest set of feature vectors from the sample region. 
This would make our model super adaptive. 
But since it is always based on feature vectors from a single image, the model (and the segmentation) is free to change 
dramatically from one image to the next.
We will instead implement a solution that makes the model behave more smoothly.
This is achieved by continously retraining the model based on a mixture of old and new feature vectors.

The method `updateSamples` is supposed to update `current_samples` by replacing a random subset of its feature vectors 
(columns) with feature vectors (columns) from `new_samples`. 
In its current state, this method does not perform any update at all.
Your job is to implement it so that it works as intended.

The parameter `adaptive_update_ratio` controls the portion of feature vectors that should be updated.
It should be a number between 0 and 1, so that 0.1 corresponds to 10% of the feature vectors being updated.
By changing this parameter we can adjust the adaptiveness of our model.

When running the project, keypress **a** alternates the model behaviour between static/adaptive.

**Suggestion 1:**  You can for instance use [cv::randu]() to generate a matrix of random numbers between 0 and 1 with the
same number of columns as `current_samples`. Loop through the columns and replace columns if their random number is smaller than
the `adaptive_update_ratio`.

**Suggestion 2:** Another approach is to make use of [cv::randShuffle](). By first shuffling both `current_samples` and `new_samples` you
can update the first N columns of `current_samples` with the first N columns of `new_samples`. Here N should be determined based
on the `adaptive_update_ratio`.

How does this adaptive model work? Try adjusting the `adaptive_update_ratio`. Are the changes noticeable?

Now you should have a working adaptive segmentation method!
Please continue to the [next step](3-further-work.md) to make it a bit more advanced.