/*  FCAI-CU - Object Oriented PROGRAMMING - 2023 - ASSIGNMENT-1
    Program Name: ImageProccessingSoftware.cpp
    Last modification date: 10/10/2023
    Author 1 and ID: Amr El-Sheriey - 20220450
    Author 2 and ID: Omar Mahfouz - 20220229
    Author 3 and ID: n/a
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
    char image2FileName[100];
    cout << "Please enter name Of image file to with: \n";
    cin >> image2FileName;
    strcat (image2FileName, ".bmp");
    readGSBMP(image2FileName, image);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] =
                    (image[i][j] + image2[i][j]) / 2; // making the pixel (i,j) the average of the two pixels given
}

void Flip() {
    cout << "Flip (h)orizontally or (v)ertically ?\n";
    char choice;
    cin >> choice;
    char arr[SIZE][SIZE];
    if (choice == 'v') {
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
    cout << "Rotate (90), (180), (270) or (360) degrees?\n";
    int angle;  
    cin >> angle;
    int n_rotations = angle/90;
    unsigned char image2[SIZE][SIZE];
    while (n_rotations--) { // rotating 90 degrees multiple times bases on user's desire since 90*2=180 and 90*3=270
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
    char choice;
    cout << "Do you want to (d)arken or (I)ighten?\n";
    cin >> choice;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (choice == 'd')
                image[i][j] /= 2; // darkens the image by 50% by dividing by 2 which makes it less bright overall
            else
                image[i][j] = min(255, image[i][j] + image[i][j] / 2);
            // lightens the image  by 50% by adding more bits to the pixels but making sure the value is within bounds
        }
}

int cnt, flag = 1;
unordered_map<char, VoidFunction> Command_List;

// creating a map that hold all the commands to avoid making a lot of if conditions and declutter it 
void command_loop() {
    char command; //getting the command from the user
    cout << "Please select a filter to apply or 0 to Exit: \n";
    cout << "1- Black & White Filter \n2- Invert Filter \n3- Merge Filter \n";
    cout << "4- Flip Image \n5- Darken and Lighten Image \n6- Rotate Image \n";
    cout << "s- Save the Image\n";
    
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
    // associating a void function with a number in a command list
    Command_List['1'] = Black_And_White; // done
    Command_List['2'] = Invert; // done
    Command_List['3'] = Merge; // done
    Command_List['4'] = Flip; // done
    Command_List['5'] = Darken_or_lighten; // done
    Command_List['6'] = Rotate; // done
    Command_List['s'] = save_Image; // done
}

int main() {
    Defining_Map();
    cout << "Welcome To Our Image Processing Project\n";
    load_Image();
    while (flag)
        command_loop();
}
