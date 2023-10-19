# Image-Processing-Project  
This is an image-processing project required by FCAI-CU as an assignment

It works by taking the image name that has to be in the same file directory and then edits it depending on the user's input and then saving it    

The assignment-1.cpp file contains the functions to load and save 256x256 grayscale bitmap images as well as 15 unique filters that edit the image   
it contains the following filters :  

Black and White: This filter works by taking input from the user and then checking if the grayscale level in each pixel is close to black or white and depending on that it completely sets it as either black or white thus producing a black and white image.  

Invert: This filter works by inverting each pixel by removing the value of said pixel from 256.  

Merge: This filter works by going through each pixel in both selected images and taking the average of the same pixel placement in each image.  

Flip: now depending on whether the user wants to flip horizontally or vertically we just replace the image pixels with the pixels that fit the orientation.  

Darken and Lighten: depending on the user's request of whether we Lighten or Darken it works as follows:
    Darken: This filter divides each pixel value by 2 which makes the overall image appear darker.
    Lighten: This filter works by trying to modify each pixel to make it 2 times its original amount but trying our best to make sure it stays within the bounds of 255. 

Rotate: This filter works by the fact that to rotate a 2D grid you make the first row the last column, the second row the penultimate column, etc..., and considering the degrees given by the user we repeat the number of rotations if it's 90 then it's one rotation, 180 is 2 rotations and 270 is three rotations.

Detect Image Edges: This filter works by checking the pixel's neighbours and taking its average. if the current pixel is above the average then it's an edge and will be painted black otherwise it's not an edge hence it will be painted white.

Enlarge: This filter works by taking each pixel in the quarter the user selected and making that pixel value equal to 4 pixel values in the 256x256 image thus enlarging (upscaling) the selected quarter.

Shrink: After taking the desired level of shrinking from the user we decide on the new_size of the image and after doing that we create small blocks of pixels and these blocks help us by looping through them and taking the average of their values we get the shrinking (downscaling) effect.  

Mirror: This filter works by making the half that the user requested and duplicates it on the other side by a simple operation 

Shuffle: This filter works by making the original image into quarters and then depending on the user's request the quarters are sorted and swapped with the original image

Blur: Simmilar to shrinking we also try to make small blocks or windows of size : blursize which contributes to the blur effect ( the higher the blur size the bigger the windows created which correlates to the blurring effect generated after that we just loop through said windows and average the pixels to get our desired blur effect 

Crop: This filter just works by starting on the x,y positions that the user inputs and then travels l,w distance and saves them on a white background.  

Skew Up: First of all we need to shrink the image and make the image's length X and the rest of it white. The length X is calculated by basic trigonometry using the degree given by the user, after shrinking the pixels will be shifted by 256-X and multiplied by a constant named Y. Y is the percentage that is needed to make the skewed image fit the picture from the range between the pixels (255,0) and (0,255).

Skew Right: It's similar to Skewing up but we replace every operation done to columns with rows. 

The assignment-1-color.cpp file is the same program but works with 256X256 RGB bitmap images.
    
Made by: 
Amr El-Sheriey - 20220450 - amrsherieycll@gmail.com
Omar Mahfouz - 20220229 - omer12memo1212@gmail.com
