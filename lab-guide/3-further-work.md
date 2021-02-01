# Step 3. Further work

After experimenting with this segmentation method, it should be clear that it is far from perfect.

Here are some things you can try in order to improve it:

- Try changing the color representation of the image from **RGB** to **Lab**, **HSV** or some other colorspace.
Does it make any difference for the segmentation? 

  Take a look at [cv::cvtColor](https://docs.opencv.org/4.0.1/d8/d01/group__imgproc__color__conversions.html#ga397ae87e1288a81d2363b61574eb8cab).

- Clean up the segmentation by using morphological operations on the binary image. 
[cv::morphologyEx](https://docs.opencv.org/4.0.1/d4/d86/group__imgproc__filter.html#ga67493776e3ad1a3df63883829375201f)
can be used for this.

- Connected component analysis [cv::connectedComponentsWithStats](https://docs.opencv.org/4.0.1/d3/dc0/group__imgproc__shape.html#gae57b028a2b2ca327227c2399a9d53241)
can be used to identify the largest connected component in the binary image and remove the smaller ones.

- Try using more than 3 features per pixel. This requires several changes to the code!
  - Derivatives
  - Measures of local uniformity
    - Local standard deviation
    - Local entropy