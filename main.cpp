#include <bits/stdc++.h>
#include "bmplib.h"
#include <unistd.h>
using namespace std;
unsigned char image[SIZE][SIZE];
int pick;
void GetImage(unsigned char img[SIZE][SIZE]){
    string Name,path="\\images\\";
    cout << "The Name of The Image: ";
    cin >> Name;
    path+=Name;
    path+=".bmp";
    char cwd[PATH_MAX];
    readGSBMP(strcat(getcwd(cwd,sizeof(cwd)),path.c_str()),img);
}
void BlackAndWhite(){
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            image[i][j]=(image[i][j]>=128?255:0);
}
void Invert(){
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            image[i][j]=(image[i][j]>=128?0:255);
}

void Merge(){
    unsigned char image2[SIZE][SIZE];
    GetImage(image2);
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            image[i][j]=(image[i][j]+image2[i][j])/2;
}
void Flip(){
    cout << "Press 0 for Horizontally , 1 for Vertically: ";
    int choice;
    cin >> choice;
    char arr[SIZE][SIZE];
    if(choice){
        for(int i=0;i<SIZE;i++)
            for (int j = 0; j < SIZE; j++)
                arr[i][j] = image[SIZE-i][SIZE-j];
        for(int i=0;i<SIZE;i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j]=arr[i][SIZE-j];
    }else{
        for(int i=0;i<SIZE;i++)
            for (int j = 0; j < SIZE/2; j++)
                swap(image[i][j],image[i][SIZE-j]);
    }
}
void Rotate(){
    int choice;
    cout << "Press 1 For 90 Degree rotation\nPress 2 For 180 Degree\nPress 3 For 270 Degree\n";
    cin >> choice;
    unsigned char image2[SIZE][SIZE];
    while(choice--){
        int k=0;
        for(int i=0;i<SIZE;i++)
            for(int j=0;j<SIZE;j++)
                image2[i][j]=image[i][j];
        for(int j=SIZE-1;j>=0;j--) {
            for (int i = 0; i < SIZE; i++)
                image[i][j] = image2[k][i];
            k++;
        }
    }
}
void Darken(){
    int choice;
    cout << "Press 0 for Lightening the image\nPress 1 for Darkening the image\n";
    cin >> choice;
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++) {
            if(choice)
                image[i][j]/=2;
            else
                image[i][j]=min(255,image[i][j]+image[i][j]/2);
        }

}
void mirror(){
    int choice;
    cout << "For Mirroring 1/2 Right Press 0\n";
    cout << "For Mirroring 1/2 Left Press 1\n";
    cout << "For Mirroring 1/2 Lower Press 2\n";
    cout << "For Mirroring 1/2 Up Press 3\n";
    cin >> choice;
    if(!choice)
        for(int i=0;i<SIZE;i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = image[i][SIZE-j];
    else if(choice==1)
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE / 2; j < SIZE; j++)
                image[i][j] = image[i][SIZE - j];
    else if(choice==2)
        for(int i=0;i<SIZE;i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = image[SIZE-i][j];
    else
        for (int j = 0; j < SIZE; j++)
            for (int i = SIZE / 2; i < SIZE; i++)
                image[i][j] = image[SIZE-i][j];
}
int cnt,flag;
void StartUp(){
    cout << "Press 1 for the Black And White filter\n";
    cout << "Press 2 for the inversion filter\n";
    cout << "Press 3 to Merge Two Images\n";
    cout << "Press 4 to Flip an Image\n";
    cout << "Press 5 to Rotate an Image\n";
    cout << "Press 6 for the Darkening filter\n";
    cout << "Press 7 to Mirror The Image\n";
    cout << "Press 8 to Print The Image\n";
    cout << "Press 9 to Close the Program\n";
    cin >> pick;
    if(pick==9){
        flag=1;
        return;
    }
    if(pick<1||pick>9){
        cnt++;
        if(cnt==20){
            cout << "Too many unsuccessful attempts.\nHalting the program";
            flag=1;
            return;
        }
        cout << "INVALID OPTION, Please choose from the numbers on the screen\n";
        StartUp();
    }
}
void CallTheFilter(){
    switch (pick) {
        case 1:
            BlackAndWhite();
            break;
        case 2:
            Invert();
            break;
        case 3:
            Merge();
            break;
        case 4:
            Flip();
            break;
        case 5:
            Rotate();
            break;
        case 6:
            Darken();
            break;
        case 7:
            mirror();
            break;
        case 8:
            showGSBMP(image);
            break;
    }
}
int main() {
    cout << "Welcome To Our Image Processing Project\n";
    GetImage(image);
    while(1){
        StartUp();
        if(flag)return 0;
        CallTheFilter();
    }
}
