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
unsigned char image[SIZE][SIZE];

int main();

void Load_Image() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void Save_Image() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "What do you want to name the new image: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void Black_And_White() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = (image[i][j] >= 128 ? 255 : 0);// see if the image is close to being black or white and change it completely
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
    cout << "Enter the name of the image file to merge with: ";
    cin >> image2FileName;
    strcat(image2FileName, ".bmp");
    readGSBMP(image2FileName, image2);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = (image[i][j] + image2[i][j]) / 2; // making the pixel (i,j) the average of the two pixels given to merge them
}

void Flip() {
    cout << "Flip (h)orizontally or (v)ertically ?\n";
    char choice;
    cin >> choice;
    choice = tolower(choice);
    if(!(choice=='h'||choice=='v')){
        cout << "INVALID INPUT, TRY AGAIN\n";
        Flip();
        return;
    }
    char arr[SIZE][SIZE];
    if (choice == 'v') {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                arr[i][j] = image[SIZE - i][SIZE - j];//rotate 180
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = arr[i][SIZE - j];//similar to mirroring left side
    } else
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE / 2; j++)
                swap(image[i][j], image[i][SIZE - j]);
}

void Rotate() {
    cout << "Rotate (90), (180), (270) or (360) degrees?\n";
    int angle;
    cin >> angle;
    set<int>Valid={90, 180, 270, 360};
    if(!Valid.count(angle)){
        cout << "INVALID DEGREE, TRY AGAIN\n";
        Rotate();
        return;
    }
    int n_rotations = 4 - angle / 90;
    unsigned char image2[SIZE][SIZE];
    while (n_rotations--) { // rotating 90 degrees anti-clockwise multiple times bases on user's desire since 90*2=180 and 90*3=270
        int x = 0;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image2[i][j] = image[i][j];
        for (int j = SIZE - 1; j >= 0; j--) {
            for (int i = 0; i < SIZE; i++)
                image[i][j] = image2[x][i];
            x++;
            // to rotate a 2d grid you make first row the last column , second row the penultimate column etc..
        }
    }
}

void Darken_or_Lighten() {
    char choice;
    cout << "Do you want to (d)arken or (l)ighten?\n";
    cin >> choice;
    choice = tolower(choice);
    if(!(choice == 'd'||choice == 'l')) {
        cout << "INVALID INPUT, TRY AGAIN\n";
        Darken_or_Lighten();
        return;
    }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (choice == 'd')
                image[i][j] /= 2; // darkens the image by 50% by dividing by 2 which makes it less bright overall
            else
                image[i][j] = min(255, image[i][j] + image[i][j] / 2);
            // lightens the image  by 50% by adding more bits to the pixels but making sure the value is within bounds
        }
}

void Mirror() {
    char choice;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? \n";
    cin >> choice;
    if (choice == 'r')
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = image[i][SIZE - j];
    else if (choice == 'l')
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE / 2; j < SIZE; j++)
                image[i][j] = image[i][SIZE - j];
    else if (choice == 'd')
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = image[SIZE - i][j];
    else if (choice == 'u')
        for (int j = 0; j < SIZE; j++)
            for (int i = SIZE / 2; i < SIZE; i++)
                image[i][j] = image[SIZE - i][j];
    else {
        cout << "INVALID INPUT, TRY AGAIN\n";
        Mirror();
        return;
    }
}

void Blur() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            int sum = 0;
            int count = 0;
            int blurSize = 4; // this is the blur size in this case its 4x4 for a minimal blur effect but you can increase it for more blur if you want to

            for (int di = -blurSize; di <= blurSize; di++)
                for (int dj = -blurSize; dj <= blurSize; dj++) { // these loops just cut the image into 4x4 kernels
                    int Window_i = i + di;
                    int Window_j = j + dj;

                    if (Window_i >= 0 && Window_i < SIZE && Window_j >= 0 && Window_j < SIZE) {
                        sum += image[Window_i][Window_j]; //calculates the sum of bits in the pixels and counts how many there are
                        count++;
                    }
                }
            image[i][j] = sum / count; // this is where the blur effect happens and it works by making the entire blur kernel the same number which is the average of them
        }
}

void Crop() {
    int white_image[256][256];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            white_image[i][j] = 255;

    cout << "Please enter X, Y, L, W: ";
    int x, y, l, w;
    cin >> x >> y >> l >> w;

    for (int i = x; i <= l; i++)
        for (int j = y; j <= w; j++)
            white_image[i][j] = image[i][j];

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = white_image[i][j];
}

void Detect_Edges() {
    int dx[] = {0, 0, -1, 1, 1, -1, -1, 1};
    int dy[] = {1, -1, 0, 0, -1, 1, -1, 1};
    // direction arrays to travers through the pixels to avoid making 8 if conditions
    int image2[SIZE][SIZE];
    Black_And_White();// making the image black and white to make it easier
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image2[i][j] = image[i][j]; // copying the image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int average = image[i][j], neighbours = 1;
            for (int k = 0; k < 8; k++) {
                int next_x = i + dx[k];
                int next_y = j + dy[k];
                if (next_x < 0 || next_y < 0 || next_x > 255 || next_y > 255) continue; // if out of boundaries continue
                neighbours++;
                average += image2[next_x][next_y];
            }
            average /= neighbours;
            if (image2[i][j] > average)
                image[i][j] = 0; // if the pixel value is bigger than the average then it's an edge
            else image[i][j] = 255;
        }
    }
}

void Enlarge() {
    // Determine the starting indices based on the quarter
    char quarter;
    cout << "Which Quarter do you want to enlarge 1, 2, 3 or 4 ?\n";
    cin >> quarter;
    int startC = 0, startR = 0;

    // creating a white image
    unsigned char white_image[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            white_image[i][j] = 255;

    // how we decide which quarter should be enlarged and if its not 2, 3 or 4 then the default values will start in quarter 1
    if (quarter == '1') {
        startR = 0;
        startC = 0;
    } else if (quarter == '2') {
        startC = 128;
        startR = 0;
    } else if (quarter == '3') {
        startC = 0;
        startR = 128;
    } else if (quarter == '4') {
        startC = 128;
        startR = 128;
    } else {
        cout << "INVALID INPUT, TRY AGAIN.";
        Enlarge();
        return;
    }

    // Loop through the original image quarter
    for (int i = startR; i < (startR + 128); i++)
        for (int j = startC; j < (startC + 128); j++) {
            // this is to skip over the enlarged pixels in the new image
            int enlargedI = (i - startR) * 2;
            int enlargedJ = (j - startC) * 2;
            // Enlarge the pixel to the new image by setting each pixel from the quarter to 4 pixels in the new 256x256 image
            white_image[enlargedI][enlargedJ] = image[i][j];
            white_image[enlargedI + 1][enlargedJ] = image[i][j];
            white_image[enlargedI][enlargedJ + 1] = image[i][j];
            white_image[enlargedI + 1][enlargedJ + 1] = image[i][j];
        }

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = white_image[i][j];
}

void Shrink() {
    string level; // level of shrinking
    cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
    cin >> level;

    // creating a white image
    unsigned char white_image[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            white_image[i][j] = 255;

    // conditions to decide the new size of the image depending on the user input
    int New_Size=1;
    if (level == "1/2")
        New_Size = SIZE / 2;
    else if (level == "1/3")
        New_Size = SIZE / 3;
    else if (level == "1/4")
        New_Size = SIZE / 4;
    else {
        cout << "INVALID INPUT, TRY AGAIN\n";
        Shrink();
        return;
    }

    // creating an integer called blockS to decide what the block size we are going to use
    int blockS = SIZE / New_Size;
    for (int i = 0; i < New_Size; i++)
        for (int j = 0; j < New_Size; j++) {
            // Calculate the average of the block from the original image
            int sum = 0;
            for (int x = 0; x < blockS; x++)
                for (int y = 0; y < blockS; y++)
                    sum += image[blockS * i + x][blockS * j + y];

            white_image[i][j] = sum / (blockS * blockS);
        }

    // transferring what's in the white_image into the original image for easier saving because the save function holds the original image
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = white_image[i][j];
}

void Shuffle() {
    int order[4];
    bool one, two, three, four;
    one = two = three = four = false;
    // I want to check if 1 and 2 and 3 and 4 occur in the input
    // else it's an invalid form of input
    cout << "New order of quarters ?";
    for (int i = 0; i < 4; i++) {
        cin >> order[i];
        one |= (order[i] == 1);
        two |= (order[i] == 2);
        three |= (order[i] == 3);
        four |= (order[i] == 4);
        order[i]--; // because 0-indexed is better
    }
    if (!(one && two && three && four)) {
        cout << "INVALID ORDER, TRY AGAIN\n";
        Shuffle();
        return;
    }
    int image2[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image2[i][j] = image[i][j];// copying the image
    map<int, pair < int, int>> start_pos = {{0, {0, 0}},{1, {0, SIZE / 2}},{2, {SIZE / 2, 0}},{3, {SIZE / 2, SIZE / 2}}};
    // this map contains the start for the rows and columns for each quarter (0,1,2,3)
    for (int k = 0; k < 4; k++) {
        int i = start_pos[k].first;
        int x = start_pos[order[k]].first;
        int stop_i = i + SIZE / 2;
        int stop_j = start_pos[k].second + SIZE / 2;
        // stop i and stop j after SIZE/2 steps since you only get to move half of the image in each quarter
        for (; i < stop_i; i++, x++) {
            for (int j = start_pos[k].second, y = start_pos[order[k]].second; j < stop_j; j++, y++) {
                image[i][j] = image2[x][y]; // make the kth quarter = the wanted quarter
            }
        }
    }
}

void Skew_Up() {
    double rad;
    cout << "Please enter degree to skew right: ";
    cin >> rad;
    if(rad>=90||rad<0){
        cout << "INVALID INPUT\n";
        cout << "Please enter a degree in the range [0,90[\n";        Skew_Up();
        Skew_Up();
        return;
    }
    rad = (rad*22)/(180*7);
    int length = tan(rad)*256/(tan(rad)+1);
    unsigned char White_Image[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            White_Image[i][j] = 255; // making a white image

    for (int j = 0; j < SIZE; j++)
        for (int i = 0; i < SIZE; i++)
            White_Image[i * length / SIZE][j] = image[i][j]; // Shrink procedure

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = White_Image[i][j];
            White_Image[i][j] = 255;
        }
    double move = (SIZE - length) / (1.0*SIZE);
    // every row there is a movement like a staircase when zooming in. this move variable helps doing it.
    for(int j=0;j<SIZE;j++)
        for(int i=0; i < length; i++)
            White_Image[(int)((SIZE - length) - j * move + i)][j] = image[i][j];
    // shifting every pixel to the designated row at SIZE-length) - j * move + i)

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = White_Image[i][j];
}

void Skew_Right() {
    double rad;
    cout << "Please enter degree to skew right: ";
    cin >> rad;
    if(rad>=90||rad<0){
        cout << "INVALID INPUT\n";
        cout << "Please enter a degree in the range [0,90[\n";        Skew_Right();
        Skew_Right();
        return;
    }
    rad = (rad*22)/(180*7);
    int length = tan(rad)*256/(tan(rad)+1);
    unsigned char White_Image[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            White_Image[i][j] = 255; // making a white image

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            White_Image[i][j * length / SIZE] = image[i][j]; // Shrink procedure

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = White_Image[i][j];
            White_Image[i][j] = 255;
        }
    double move = (SIZE - length) / (1.0*SIZE);
    // every row there is a movement like a staircase when zooming in. this move variable helps doing it.
    for(int i=0;i<SIZE;i++)
        for(int j=0; j < length; j++)
            White_Image[i][(int)((SIZE - length) - i * move + j)] = image[i][j];
    // shifting every pixel to the designated column at (SIZE-length) - i * move + j

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = White_Image[i][j];
}

int cnt, flag = 1;
unordered_map<char, function<void()>> Command_List;
// creating a map that hold all the commands to avoid making a lot of if conditions

void Command_Loop() {
    char Command; //getting the Command from the user
    cout << "Please select a filter to apply: \n";
    cout << "1- Black & White Filter \n2- Invert Filter \n3- Merge Filter \n";
    cout << "4- Flip Image \n5- Darken and Lighten Image \n6- Rotate Image \n";
    cout << "7- Detect Image Edges \n8- Enlarge Image \n9- Shrink Image \n";
    cout << "a- Mirror Image \nb- Shuffle Image \nc- Blur Image \nd- Crop Image \n";
    cout << "e- Skew Image Right \nf- Skew Image UP \ns- Save the Image\nr- Restart the Program\n0- Exit\n";

    cin >> Command;
    Command = tolower(Command);
    if (Command == '0') {
        cout << "Have a good day and goodbye\n";
        flag = false;
        return;
    }
    if (Command_List.find(Command) == Command_List.end()) {
        cnt++;
        if (cnt == 20) {
            cout << "Too many unsuccessful attempts.\nHalting the program";
            flag = 0;
            return;
        }
        cout << "INVALID OPTION, Please choose from the numbers/letters on the screen\n";
        Command_Loop();
        return;
    }
    Command_List[Command]();
}

void Defining_Map() {
    // associating a void function with a number in a command map
    Command_List['1'] = Black_And_White;
    Command_List['2'] = Invert;
    Command_List['3'] = Merge;
    Command_List['4'] = Flip;
    Command_List['5'] = Darken_or_Lighten;
    Command_List['6'] = Rotate;
    Command_List['7'] = Detect_Edges;
    Command_List['8'] = Enlarge;
    Command_List['9'] = Shrink;
    Command_List['a'] = Mirror;
    Command_List['b'] = Shuffle;
    Command_List['c'] = Blur;
    Command_List['d'] = Crop;
    Command_List['e'] = Skew_Right;
    Command_List['f'] = Skew_Up;
    Command_List['s'] = Save_Image;
    Command_List['r'] = main;
}

int main() {
    Defining_Map();
    Load_Image();
    cout << "Welcome To Our Image Processing Project\n";
    while (flag)
        Command_Loop();
}
