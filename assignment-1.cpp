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

// void Get_Image(unsigned char img[SIZE][SIZE]) {
//     string Name, path = "\\images\\";
//     cout << "The Name of The Image: ";
//     cin >> Name;
//     path += Name;
//     path += ".bmp";
//     char cwd[PATH_MAX];
//     readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), img);
// }

// void Save_Image() {
//     string Name, path = "\\images\\";
//     cout << "The Name of The Image: ";
//     cin >> Name;
//     path += Name;
//     path += ".bmp";
//     char cwd[PATH_MAX];
//     writeGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), image);
// }

// void Print_Image() {
//     showGSBMP(image);
// }

void Black_And_White() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = (image[i][j] >= 128 ? 255: 0);// see if the image is close to being black or white and change it completely
}

void Invert() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = 255 - image[i][j];// inverting the image by inverting the bits
}

void Merge() {
    unsigned char image2[SIZE][SIZE];
    // defining another image file to Merge
    // Get_Image(image2);

    char image2FileName[100];
    cout << "Enter the source image file name: ";
    cin >> image2FileName;
    strcat (image2FileName, ".bmp");
    readGSBMP(image2FileName, image);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] =
                    (image[i][j] + image2[i][j]) / 2; // making the pixel (i,j) the average of the two pixels given
}

void Flip() {
    cout << "Press 0 for Horizontally , 1 for Vertically: ";
    int choice;
    cin >> choice;
    char arr[SIZE][SIZE];
    if (choice) {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                arr[i][j] = image[SIZE - i][SIZE - j];
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = arr[i][SIZE - j];
    } else
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE / 2; j++)
                swap(image[i][j], image[i][SIZE - j]);
}

void Rotate() {
    int choice;
    cout << "Press 1 For 90 Degree rotation\nPress 2 For 180 Degree\nPress 3 For 270 Degree\n";
    cin >> choice;
    unsigned char image2[SIZE][SIZE];
    while (choice--) { // rotating 90 degrees multiple times bases on user's desire since 90*2=180 and 90*3=270
        int k = 0;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image2[i][j] = image[i][j];
        for (int j = SIZE - 1; j >= 0; j--) {
            for (int i = 0; i < SIZE; i++)
                image[i][j] = image2[k][i];
            k++;
        }
    }
}

void Darken_or_lighten() {
    int choice;
    cout << "Press 0 for Lightening the image\nPress 1 for Darkening the image\n";
    cin >> choice;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (choice)
                image[i][j] /= 2; // darkens the image by 50% by dividing by 2 which makes it less bright overall
            else
                image[i][j] = min(255, image[i][j] + image[i][j] / 2);
            // lightens the image  by 50% by adding more bits to the pixels but making sure the value is within bounds
        }
}

void Mirror() {
    int choice;
    cout << "For Mirroring 1/2 Right Press 0\n";
    cout << "For Mirroring 1/2 Left Press 1\n";
    cout << "For Mirroring 1/2 Lower Press 2\n";
    cout << "For Mirroring 1/2 Up Press 3\n";
    cin >> choice;
    if (!choice)
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = image[i][SIZE - j];
    else if (choice == 1)
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE / 2; j < SIZE; j++)
                image[i][j] = image[i][SIZE - j];
    else if (choice == 2)
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = image[SIZE - i][j];
    else
        for (int j = 0; j < SIZE; j++)
            for (int i = SIZE / 2; i < SIZE; i++)
                image[i][j] = image[SIZE - i][j];
}

void Blur() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int sum = 0;
            int count = 0;
            int blurSize = 4; // this is the blur size in this case its 4x4 for a minimal blur effect but you can increase it for more blur if you want to

            for (int di = -blurSize; di <= blurSize; di++) {
                for (int dj = -blurSize; dj <= blurSize; dj++) { // these loops just cut the image into 4x4 kernels
                    int Kerneli = i + di;
                    int Kernelj = j + dj;

                    if (Kerneli >= 0 && Kerneli < SIZE && Kernelj >= 0 && Kernelj < SIZE) {
                        sum += image[Kerneli][Kernelj]; //calculates the sum of bits in the pixels and counts how many there are
                        count++;
                    }
                }
            }
            image[i][j] = sum / count; // this is where the blur effect happens and it works by making the entire blur kernel the same number which is the average of them
        }
    }
}

void Crop() {
    int white_image[256][256];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            white_image[i][j] = 255;
        }
    }

    cout << "Please enter X, Y, L, W: ";
    int x, y, l, w;
    cin >> x >> y >> l >> w;

    for (int i = x; i <= l; i++) {
        for (int j = y; j <= w; j++) {
            white_image[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = white_image[i][j];
        }
    }
}

void Die() {}

void Enlarge() { 
    // Determine the starting indices based on the quarter
    char quarter; 
    cout << "Which Quarter do you want to enlarge 1, 2, 3 or 4 ?\n";
    cin >> quarter;
    int startC, startR;

    // creating a white image
    unsigned char white_image[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            white_image[i][j] = 255;
        }
    }

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
    for(int i = startR; i < (startR + 128); i++) {
        for(int j = startC; j < (startC + 128); j++) {
            // this is to skip over the enlarged pixels in the new image
            int enlargedI = (i - startR) * 2;
            int enlargedJ = (j - startC) * 2;
            // Enlarge the pixel to the new image by setting each pixel from the quarter to 4 pixels in the new 256x256 image
            white_image[enlargedI][enlargedJ] = image[i][j];
            white_image[enlargedI + 1][enlargedJ] = image[i][j];
            white_image[enlargedI][enlargedJ + 1] = image[i][j];
            white_image[enlargedI + 1][enlargedJ + 1] = image[i][j];
        }
    }        
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = white_image[i][j];
        }
    }
}

void Shrink() {
    string lvl; // level of shrinking
    cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
    cin >> lvl;

    // creating a white image
    unsigned char white_image[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            white_image[i][j] = 255;
        }
    }

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
    for(int i = 0; i < new_size; i++) {
        for(int j = 0; j < new_size; j++) {
            // Calculate the average of the block from the original image
            int sum = 0;
            for(int x = 0; x < blockS; x++) {
                for(int y = 0; y < blockS; y++) {
                    sum += image[blockS * i + x][blockS * j + y];
                }
            }
            white_image[i][j] = sum / (blockS * blockS);
        }
    }

    // transferring whats in the white_image into the original image for easier saving because the save function holds the original image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = white_image[i][j];
        }
    }
}

void Shuffle() {}

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
    Command_List['1'] = Black_And_White; // done
    Command_List['2'] = Invert; // done
    Command_List['3'] = Merge; // done
    Command_List['4'] = Flip; // done
    Command_List['5'] = Darken_or_lighten; // done
    Command_List['6'] = Rotate; // done
    Command_List['7'] = Die; // [N/A]
    Command_List['8'] = Enlarge; // Almost Done but quarters 1,2 do not work
    Command_List['9'] = Shrink; // [N/A]
    Command_List['a'] = Mirror; // done
    Command_List['b'] = Shuffle; // [N/A]
    Command_List['c'] = Blur; // done
    Command_List['d'] = Crop; // done
    Command_List['e'] = Skew_Right; // [N/A]
    Command_List['f'] = Skew_Up; // [N/A]
    Command_List['s'] = save_Image; // done
    // Command_List['r'] = command_loop;
}

int main() {
    Defining_Map();
    load_Image();
    cout << "Welcome To Our Image Processing Project\n";
    while (flag)
        command_loop();
}
