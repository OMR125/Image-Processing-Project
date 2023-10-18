/*  FCAI-CU - OOP PROGRAMMING - 2023 - ASSIGNMENT-1
    Program Name: ImageProccessingSoftware.cpp
    Last modification date: 16/10/2023
    Author 1 and ID: Amr El-Sheriey - 20220450
    Author 2 and ID: Omar Mahfouz - 20220229
    TA: n/a
    Purpose: Demonstrate use of bmplip for handling
    bmp colored and grayscale images
    Program load a gray image and store in another file
    program also applies filters to images depending on the user's request */
    
#include <bits/stdc++.h>
#include "bmplib.h"
#include "bmplib.cpp"
#include <unistd.h>

using namespace std;
typedef function<void()> VoidFunction; // a typdef to make our CommandList work
unsigned char image[SIZE][SIZE][RGB];

int main();

void load_Image() {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
}

void save_Image() {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "What do you want to name the new image: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, image);
}

void Black_And_White() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = (image[i][j][k] >= 128 ? 255: 0);// see if the image is close to being black or white and change it completely
}

void Invert() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = 255 - image[i][j][k];// inverting the image by inverting the bits
}

void Merge() {
    unsigned char image2[SIZE][SIZE][RGB];
    // defining another image file to Merge
    char image2FileName[100];
    cout << "Please enter name of image file to merge with: ";
    cin >> image2FileName;
    strcat (image2FileName, ".bmp");
    readRGBBMP(image2FileName, image2);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2; // making the pixel (i,j,k) the average of the two pixels given to merge them
}

void Flip() {
    cout << "Flip (h)orizontally or (v)ertically ?\n";
    char choice;
    cin >> choice;
    choice = tolower(choice);
    char arr[SIZE][SIZE][RGB];
    if (choice == 'v') {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k = 0; k < RGB; k++)
                    arr[i][j][k] = image[SIZE - i][SIZE - j][k];//rotate 180
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k = 0; k < RGB; k++)
                    image[i][j][k] = arr[i][SIZE - j][k];//similar to mirroring left side
    } 
    else if (choice == 'h')
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE / 2; j++)
                for(int k = 0; k < RGB; k++)
                    swap(image[i][j][k], image[i][SIZE - j][k]);
    else {
        cout << "Make sure to enter a correct choice!\n";
        Flip();
    }
}

void Rotate() {
    cout << "Rotate (90), (180), (270) or (360) degrees?\n";
    int angle;
    cin >> angle;
    int n_rotations = 4 - angle/90;
    unsigned char image2[SIZE][SIZE][RGB];
    while (n_rotations--) { // rotating 90 degrees clockwise multiple times bases on user's desire since 90*2=180 and 90*3=270
        int rt = 0;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k = 0; k < RGB; k++)
                    image2[i][j][k] = image[i][j][k];
        for (int j = SIZE - 1; j >= 0; j--) {
            for (int i = 0; i < SIZE; i++)
                for(int k = 0; k < RGB; k++)
                    image[i][j][k] = image2[rt][i][k];
            rt++;
            // to rotate a 2d grid you make first row the last column , second row the penultimate column etc..
        }
    }
}

void Darken_or_lighten() {
    char choice;
    cout << "Do you want to (d)arken or (l)ighten?\n";
    cin >> choice;
    choice = tolower(choice);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++){
                if (choice == 'd')
                    image[i][j][k] /= 2; // darkens the image by 50% by dividing by 2 which makes it less bright overall
                else if (choice == 'l')
                    image[i][j][k] = min(255, image[i][j][k] + image[i][j][k] / 2);
                // lightens the image  by 50% by adding more bits to the pixels but making sure the value is within bounds
                else {
                    cout << "Please enter a correct choice\n";
                    Darken_or_lighten();
                }
            }
}

void Mirror() {
    char choice;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? \n";
    cin >> choice;
    if (choice = 'r')
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k = 0; k < RGB; k++)
                    image[i][j][k] = image[i][SIZE - j][k];
    else if (choice == 'l')
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE / 2; j < SIZE; j++)
                for(int k = 0; k < RGB; k++)
                    image[i][j][k] = image[i][SIZE - j][k];
    else if (choice == 'd')
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k = 0; k < RGB; k++)
                    image[i][j][k] = image[SIZE - i][j][k];
    else if (choice == 'u')
        for (int j = 0; j < SIZE; j++)
            for (int i = SIZE / 2; i < SIZE; i++)
                for(int k = 0; k < RGB; k++)
                    image[i][j][k] = image[SIZE - i][j][k];
    else {
        cout << "Make sure to input a correct letter\n";
        Mirror();
    }
}

void Blur() {
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            for(int k = 0; k < RGB; k++) {   
                int sum = 0;
                int count = 0;
                int blurSize = 4; // this is the blur size in this case its 4x4 for a minimal blur effect but you can increase it for more blur if you want to

                for (int di = -blurSize; di <= blurSize; di++)
                    for (int dj = -blurSize; dj <= blurSize; dj++) { // these loops just cut the image into 4x4 kernels
                        int Kerneli = i + di;
                        int Kernelj = j + dj;

                        if (Kerneli >= 0 && Kerneli < SIZE && Kernelj >= 0 && Kernelj < SIZE) {
                            sum += image[Kerneli][Kernelj][k]; //calculates the sum of bits in the pixels and counts how many there are
                            count++;
                        }
                    }
                image[i][j][k] = sum / count; // this is where the blur effect happens and it works by making the entire blur kernel the same number which is the average of them
            }
}

void Crop() {
    int white_image[256][256][RGB];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                white_image[i][j][k] = 255;

    cout << "Please enter X, Y, L, W: ";
    int x, y, l, w;
    cin >> x >> y >> l >> w;

    for (int i = x; i <= l; i++) 
        for (int j = y; j <= w; j++) 
            for(int k = 0; k < RGB; k++)
                white_image[i][j][k] = image[i][j][k];

    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = white_image[i][j][k];
}

void Die() {}

void Enlarge() { 
    // Determine the starting indices based on the quarter
    char quarter; 
    cout << "Which Quarter do you want to enlarge 1, 2, 3 or 4 ?\n";
    cin >> quarter;
    int startC, startR;

    // creating a white image
    unsigned char white_image[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                white_image[i][j][k] = 255;

    // how we decide which quarter should be enlarged and if its not 2, 3 or 4 then the default values will start in quarter 1
    if (quarter == '1'){
        startR = 0;
        startC = 0;
    }
    else if (quarter == '2'){
        startC = 128;
        startR = 0;
    }
    else if (quarter == '3'){
        startC = 0;
        startR = 128;
    }
    else if (quarter == '4'){
        startC == 128;
        startR == 128;
    }

    // Loop through the original image quarter
    for(int i = startR; i < (startR + 128); i++)
        for(int j = startC; j < (startC + 128); j++) 
            for(int k = 0; k < RGB; k++){
                // this is to skip over the enlarged pixels in the new image
                int enlargedI = (i - startR) * 2;
                int enlargedJ = (j - startC) * 2;
                // Enlarge the pixel to the new image by setting each pixel from the quarter to 4 pixels in the new 256x256 image
                white_image[enlargedI][enlargedJ][k] = image[i][j][k];
                white_image[enlargedI + 1][enlargedJ][k] = image[i][j][k];
                white_image[enlargedI][enlargedJ + 1][k] = image[i][j][k];
                white_image[enlargedI + 1][enlargedJ + 1][k] = image[i][j][k];
            }

    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = white_image[i][j][k];
}

void Shrink() {
    string lvl; // level of shrinking
    cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
    cin >> lvl;

    // creating a white image
    unsigned char white_image[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) 
            for(int k = 0; k < RGB; k++)
                white_image[i][j][k] = 255;

    // conditions to decide the new size of the image depending on the user input
    int new_size;
    if(lvl == "1/2")
        new_size = SIZE / 2;
    else if(lvl == "1/3")
        new_size = SIZE / 3;
    else if(lvl == "1/4")
        new_size = SIZE / 4;
    else {
        cout << "please enter a correct shrinking level\n";
        Shrink();
    }

    // creating a integer called blockS to decide what the block size we are going to use
    int blockS = SIZE / new_size;
    for(int i = 0; i < new_size; i++)
        for(int j = 0; j < new_size; j++)
            for(int k = 0; k < RGB; k++) {
            // Calculate the average of the block from the original image
            int sum = 0;
            for(int x = 0; x < blockS; x++)
                for(int y = 0; y < blockS; y++) 
                    sum += image[blockS * i + x][blockS * j + y][k];

            white_image[i][j][k] = sum / (blockS * blockS);
        }

    // transferring whats in the white_image into the original image for easier saving because the save function holds the original image
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) 
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = white_image[i][j][k];
}

void Shuffle() {
    cout << "Enter the new order of quarters (1-4): \n";
    int order[4];
    for (int i = 0; i < 4; i++)
        cin >> order[i];

    // creatign a white image to shuffle into so i don't edit on the actual image and ruin the shuffle
    unsigned char white_image[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                white_image[i][j][k] = 255;

    // this loop just run on the 1st quarter and copys the wanted quarter into it
    for (int i = 0; i < 128; i++) 
        for (int j = 0; j < 128; j++)
            for(int k = 0; k < RGB; k++)
                switch (order[0]) {
                    case 1: white_image[i][j][k] = image[i][j][k]; break;
                    case 2: white_image[i][j][k] = image[i][j + 128][k]; break;
                    case 3: white_image[i][j][k] = image[i + 128][j][k]; break;
                    case 4: white_image[i][j][k] = image[i + 128][j + 128][k]; break;
                }
    // this loop just run on the 2nd quarter and copys the wanted quarter into it
    for (int i = 0; i < 128; i++)
        for (int j = 0; j < 128; j++)
            for(int k = 0; k < RGB; k++)
                switch (order[1]) {
                    case 1: white_image[i][j + 128][k] = image[i][j][k]; break;
                    case 2: white_image[i][j + 128][k] = image[i][j + 128][k]; break;
                    case 3: white_image[i][j + 128][k] = image[i + 128][j][k]; break;
                    case 4: white_image[i][j + 128][k] = image[i + 128][j + 128][k]; break;
                }
    // this loop just run on the 3rd quarter and copys the wanted quarter into it
    for (int i = 0; i < 128; i++)
        for (int j = 0; j < 128; j++)
            for(int k = 0; k < RGB; k++)
                switch (order[2]) {
                    case 1: white_image[i + 128][j][k] = image[i][j][k]; break;
                    case 2: white_image[i + 128][j][k] = image[i][j + 128][k]; break;
                    case 3: white_image[i + 128][j][k] = image[i + 128][j][k]; break;
                    case 4: white_image[i + 128][j][k] = image[i + 128][j + 128][k]; break;
                }
    // this loop just run on the 4th quarter and copys the wanted quarter into it
    for (int i = 0; i < 128; i++)
        for (int j = 0; j < 128; j++)
            for(int k = 0; k < RGB; k++)
                switch (order[3]) {
                    case 1: white_image[i + 128][j + 128][k] = image[i][j][k]; break;
                    case 2: white_image[i + 128][j + 128][k] = image[i][j + 128][k]; break;
                    case 3: white_image[i + 128][j + 128][k] = image[i + 128][j][k]; break;
                    case 4: white_image[i + 128][j + 128][k] = image[i + 128][j + 128][k]; break;
                }
            
    // copying the white image into the original image for easier saving in the save function
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = white_image[i][j][k];
}

void Skew_Up() {}

void Skew_Right() {}

int cnt, flag = 1;
unordered_map<char, VoidFunction> Command_List;

// creating a map that hold all the commands to avoid making a lot of if conditions
void command_loop() {
    char command; //getting the command from the user
    cout << "Please select a filter to apply: \n";
    cout << "1- Black & White Filter \n2- Invert Filter \n3- Merge Filter \n";
    cout << "4- Flip Image \n5- Darken and Lighten Image \n6- Rotate Image \n";
    cout << "7- Detect Image Edges \n8- Enlarge Image \n9- Shrink Image \n";
    cout << "a- Mirror Image \nb- Shuffle Image \nc- Blur Image \nd- Crop Image \n";
    cout << "e- Skew Image to the Right \nf- Skew Image UP \ns- Save the Image\nr- Restart the Program\n0- Exit\n";
    // cout << "h- Print the Image to a File \n0- Exit\n";
    cin >> command;
    command = tolower(command);
    if (command == '0') {
        cout << "Have a good day and goodbye\n";
        flag = false;
        return;
    }
    if (Command_List.find(command) == Command_List.end()) {
        cnt++;
        if (cnt == 20) {
            cout << "Too many unsuccessful attempts.\nHalting the program";
            flag = 0;
            return;
        }
        cout << "INVALID OPTION, Please choose from the numbers/letters on the screen\n";
        command_loop();
    }
    Command_List[command]();
}

void Defining_Map() {
    // associating a void function with a number in a command map
    Command_List['1'] = Black_And_White; // needs work
    Command_List['2'] = Invert; // done in rgb
    Command_List['3'] = Merge; // done in rgb
    Command_List['4'] = Flip; // done in rgb
    Command_List['5'] = Darken_or_lighten; // done in rgb
    Command_List['6'] = Rotate; // done in rgb
    Command_List['7'] = Die; // [N/A]
    Command_List['8'] = Enlarge; // Done in rgb
    Command_List['9'] = Shrink; // Done in rgb
    Command_List['a'] = Mirror; // Done in rgb
    Command_List['b'] = Shuffle; // [N/A]
    Command_List['c'] = Blur; // done in rgb
    Command_List['d'] = Crop; // done in rgb
    Command_List['e'] = Skew_Right; // [N/A]
    Command_List['f'] = Skew_Up; // [N/A]
    Command_List['s'] = save_Image; // done in rgb
    Command_List['r'] = main;
}

int main() {
    Defining_Map();
    load_Image();
    cout << "Welcome To Our Image Processing Project\n";
    while (flag)
        command_loop();
}