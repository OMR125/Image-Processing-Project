// FCAI-CU - OOP PROGRAMMING - 2023 - ASSIGNMENT-1//
// Program Name: ImageProccessingSoftware.cpp
// Last modification date: 6/10/2023
// Author-1 and ID: Amr El-Sheriey - 20220450
// Author-2 and ID: Omar Mahfouz - 20220229 i guess
// Author-3 and ID: N\A
// TA: n/a
// Version: 1.0
/* Purpose: Demonstrate use of bmplip for handling
          bmp colored and grayscale images
          Program load a gray image and store in another file
          program also applise filters to images depending on user request */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#define endl '\n'
using namespace std;

typedef function<void()> VoidFunction; // just defined it to make it look more elegant
unsigned char image[SIZE][SIZE];


void load_Image() {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

void save_Image() {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

void black_white_image() {
  // loop over the image
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
      if (image[i][j] > 127) // see if the image is close to being black or white and change it completely 
        image[i][j] = 255;
      else
        image[i][j] = 0;
    }
  }
}

void invert_image() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {  
      image[i][j] = 255 - image[i][j]; // inverting the image by inverting the bits
    }
  }
}

void merge_image() {
    char image2FileName[100];
    unsigned char image2[SIZE][SIZE]; // defining another image file 

    cout << "Enter the second image file name: "; // loading the second image file 
    cin >> image2FileName;
    strcat (image2FileName, ".bmp"); // adding the .bmp extension and reading it 
    readGSBMP(image2FileName, image2);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2; // ***********
        }
    }
}

void flip_image () {
  string VorH;
  cout << "do you want to flip the image (h)orizontally or (v))ertically ?" << endl;
  cin >> VorH;
  if(VorH == "h" || VorH == "H") {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) { // SIZE/2 BUT RMEOVED TO TEST SMTH
            unsigned char temp = image[i][j];
            image[i][j] = image[i][SIZE - j - 1];
            image[i][SIZE - j - 1] = temp;
        }
    }
  }
  else {
    for(int i = 0; i < SIZE / 2; i++) {
        for(int j = 0; j < SIZE; j++) {
            unsigned char temp = image[i][j];
            image[i][j] = image[SIZE - i - 1][j];
            image[SIZE - i - 1][j] = temp;
        }
    }
  }
}

void rotate_image() {  
    int angle;
    cout << "Please choose desired angle 90, 180, 270: ";
    cin >> angle;
    int numberOfLayers = SIZE / 2;
    int numberOfRotations = angle / 90;
    for(int r = 0; r < numberOfRotations; r++) {
        for(int i = 0; i < numberOfLayers; i++) { 
            for(int j = i; j < SIZE - i - 1; j++) {
                int temp = image[i][j]; // This just works on rotating the image depending on the number of rotations depends on the angle / 90 and is taken from the user
                image[i][j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = temp;
            }
        }
    }
}

void darken_lighten_image() {
  string input;
  cout << "Do you want to (d)arken or (l)ighten ? ";
  cin >> input;

  if(input == "d" || input == "D"){
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
          image[i][j] = image[i][j] / 2; // darkens the image by 50% by dividing by 2 which makes it less bright overall 
      }
    }
  }
  else {  
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        int temp = image[i][j] + image[i][j] / 2;  // lightens the image  by 50% by adding more bits to the pixels but making sure the value is within bounds
        image[i][j] = temp > 255 ? 255 : temp;  // Ensure the value is within the valid range
      }
    }
  }
}

void DIE_image() {

}

void enlarge_image() {

}

void shrink_image() {

}

void mirror_image() {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE / 2; j++) {\

        }
    }
}

void shuffle_image() {

}

void blur_image() {
 for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            int sum = 0;
            int count = 0;
            int blurSize = 4; // this is the blur size in this case its 4x4 for a minimal blur effect but you can increase it for more blur if you want to 
            
            for(int di = -blurSize; di <= blurSize; di++) { 
                for(int dj = -blurSize; dj <= blurSize; dj++) { // these loops just cut the image into 4x4 kernels 
                    int Kerneli = i + di;
                    int Kernelj = j + dj;

                    if(Kerneli >= 0 && Kerneli < SIZE && Kernelj >= 0 && Kernelj < SIZE) {
                        sum += image[Kerneli][Kernelj]; // this just calculates the sum of bits in the pixels in the kernel and counts how many there are  
                        count++;
                    }
                }
            }
          image[i][j] = sum / count; // this is where the blur effect happens and it works by making the enitre blur kernel the same number which is the average of them 
        }
  } 
}

void crop_image() {
  int white_image[256][256];
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      white_image[i][j] = 255;
    }
  }

  cout << "Please enter X, Y, L, W: ";
  int x, y, l ,w;
  cin >> x >> y >> l >> w;

  for (int i = x; i <= l; i++){
    for (int j = y; j <= w; j++){
      white_image[i][j] = image[i][j];
      } 
    }
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      image[i][j] = white_image[i][j];
    }
  }
}

void skew_image_right() {

}

void skew_image_up() {

}

int cnt;
bool flag = true;

void command_loop() {
  unordered_map<char, VoidFunction> CommandMap; // creating a map that hold all the commands and the char that triggers the commands 
  load_Image(); // loading the initial image 
    
  // just some basic commands to guide the user 
  char commandNumber;
  cout << "Please select a filter to apply or 0 to Exit: \n";
  cout << "1- Black & White Filter \n2- Invert Filter \n3- Merge Filter \n";
  cout << "4- Flip Image \n5- Darken and Lighten Image \n6- Rotate Image \n";
  cout << "7- Detect Image Edges [n/a]\n8- Enlarge Image [n/a]\n9- Shrink Image [n/a]\n";
  cout << "a- Mirror Image [n/a]\nb- Shuffle Image [n/a]\nc- Blur Image \nd- Crop Image [n/a]\n";
  cout << "e- Skew Image to the Right [n/a]\nf- Skew Image UP [n/a]\ns- Save the Image to a File \n0- Exit\n";
  cin >> commandNumber;

  if(commandNumber == '0'){
    cout << "Have a good day and goodbye\n";
    flag = false;
    return;
  }
  // im sorry this is just a temporary measure
  if(commandNumber != '1' && commandNumber != '2' && commandNumber != '3' && commandNumber != '4' && commandNumber != '5' && commandNumber != '6' && commandNumber != '7' && commandNumber != '8' && commandNumber != '9' && commandNumber != 'a' && commandNumber != 'b' && commandNumber != 'c' && commandNumber != 'd' && commandNumber != 'e' && commandNumber != 'f' && commandNumber != 's'){
      cnt++;
      if(cnt==20){
          cout << "Too many unsuccessful attempts.\nHalting the program";
          flag = 1;
          return;
      }
      cout << "INVALID OPTION, Please choose from the numbers/letters on the screen\n";
      command_loop();
  }

  // this just associates a voic function with a number in a command map 
  CommandMap['1'] = black_white_image; // done
  CommandMap['2'] = invert_image; // done 
  CommandMap['3'] = merge_image; // done
  CommandMap['4'] = flip_image; // done 
  CommandMap['5'] = darken_lighten_image; // done
  CommandMap['6'] = rotate_image; // done 
  CommandMap['7'] = DIE_image; // [N/A] imma leave it to omar
  CommandMap['8'] = enlarge_image; // [N/A]
  CommandMap['9'] = shrink_image; // [N/A]
  CommandMap['a'] = mirror_image; // [N/A] omar says it;s done
  CommandMap['b'] = shuffle_image; // [N/A]
  CommandMap['c'] = blur_image; // done
  CommandMap['d'] = crop_image; // i think its done
  CommandMap['e'] = skew_image_right; // [N/A]
  CommandMap['f'] = skew_image_up; // [N/A]
  CommandMap['s'] = save_Image; // done

  // iterating over the command map to find the proper number and execute the function associated with it
  auto it = CommandMap.find(commandNumber);
    if (it != CommandMap.end()) {
        it->second();
    }
    save_Image();
}

//\======================================================\//
int main(){
  cout << "Welcome to the image proccessing project \n";

  while(flag){
    command_loop();
  }
  return 0;
}
//\======================================================\//
