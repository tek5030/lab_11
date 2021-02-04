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

Take a look at [cv::calcCovarMatrix](https://docs.opencv.org/4.0.1/d2/de8/group__core__array.html#ga017122d912af19d7d0d2cccc2d63819f).
We want `mean_` to be a column vector. The [cv::CovarFlags](https://docs.opencv.org/4.0.1/d0/de1/group__core.html#ga719ebd4a73f30f4fab258ab7616d0f0f) in `cv::calcCovarMatrix()` can be combined like this: `flag1|flag2`.
See also [cv::invert](https://docs.opencv.org/4.0.1/d2/de8/group__core__array.html#gad278044679d4ecf20f7622cc151aaaa2).

In its current state, the method simply computes **`mean_` = [127; 127; 127]**, **`covariance_` = Identity** and **`inverse_covariance_` = Identity**.
You should replace this with the correct computations.
 
## 2. Implement the method `computeMahalanobisDistances` in `MultivariateNormalModel`
This method should compute the Mahalanobis distance between every pixel in the input image and the estimated multivariate
normal model described by `mean_` and `inverse_covariance_`.

![\mathit{d}_{\mathit{M}}(\mathbf{x}) = \sqrt{(\mathbf{x}-\boldsymbol{\mu})^{T} \boldsymbol{\Sigma}^{-1} 
(\mathbf{x} - \boldsymbol{\mu})}](img/mahalanobis_distance.png)

The method should return a `cv::Mat` of Mahalanobis distances, but in its current state it simply returns a matrix of 0.5's.
You should replace this with a proper implementation.

Take a look at [cv::Mahalanobis](https://docs.opencv.org/4.0.1/d2/de8/group__core__array.html#ga4493aee129179459cbfc6064f051aa7d).


## 3. Implement the method `update`  in `MultivariateNormalModel`
This method should update the multivariate normal model by replacing a fraction of the existing `old_samples_` with some 
`new_samples` and then retrain the model.

This should make the model gradually change over time and we should be able to control the rate of which it changes by 
adjusting the `update_ratio`.

The `update_ratio` should be a number between 0 and 1, where 0.1 means that a random 10% of `samples_` are being replaced
with new one each iteration.

Keypress **a** activates/deactivates the adaptive model.

In its current state, this method does not perform any update at all.
Your job is to implement this method so that i works as intended.

**Suggestion 1:**  You can for instance use [cv::randu]() to generate a matrix of random numbers between 0 and 1 with the
same number of columns as `samples_`. Loop through the columns and replace columns if their random number is smaller than
the `update_ratio`.

**Suggestion 2:** Another approach is to make use of [cv::randShuffle](). By first shuffling both `samples_` and `new_samples` you
can update the first N columns of `samples_` with the first N columns of `new_samples`. Here N should be determined based
on the `update_ratio`.

How does this adaptive model work? Try adjusting the `update_ratio`. Are the changes noticeable?

Now you should have a working adaptive segmentation method!
Please continue to the [next step](3-further-work.md) to make it a bit more advanced.