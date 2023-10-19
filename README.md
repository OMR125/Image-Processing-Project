# Image-Processing-Project  
this is an image proccesing project required by FCAI-CU as an assignemnt

it works by taking the image name that has to be in the same file directory and then edits it depending on the user input and then procceds to save it    

the assignment-1.cpp file contains the functions to load and save 256x256 grayscale bitmap images as well as 15 unique filters that edit on the image   
it contains the following filters :  

Black and White : this filter works by taking input from the user and then checking if the grayscale level in each pixel is close to black or white and depending on that it completely sets it as either black or white thus produicing a black and white image.  

Invert: this filter works by inverting each pixel by removing the value of said pixel from 256.  

Merge: this filter works by going through each pixel in both selected images and taking the average of the same pixel placement in each image.  

Flip: now depending on whether the user want to flip horizontally or vertically we just replace the image pixels with the pixels that fit the orientation.  

Darken and Lighten: depending on user request of whether we Lighten or Darken it works as follows:
Darken: this filter divides each pixel value by 2 which makes the overall image appear darker.
Lighten: this filter works by trying to modify each pixel to make it 2 times it's original amount but trying our best to make sure it stays within the bounds of 255. 

Rotate:  

Detect Image Edges:    

Enlarge: this filters works through taking each pixel in the quarter the user selected and making that pixel value equal to 4 pixel values in the 256x256 image thus enlarging (upscaling) the selected quarter.

Shrink:

Mirror:

Shuffle:

Blur:

Crop: this filter just works by starting on the x,y positions that the user inputs and then travels l,w distance and saves them on a white background.  

Skew UP:  

Skew Right.  

The assignment-1-color.cpp file is the same program but works with 256X256 RGB bitmap images.
    
Made by: 
Amr El-Sheriey - 20220450 - amrsherieycll@gmail.com.
Omar Mahfouz - 20220229 - xxxxxxxxxxxxx.
