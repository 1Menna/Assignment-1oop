 // Program: demo2.cpp
 // Purpose: Demonstrate use of bmplip for handling
 // bmp colored and grayscale images
 //// Purpose: Get a Gray Scale image and produce a filtered image (any filter the user choose).
 // Author:  Mohammad El-Ramly
 // Date:    30 March 2018
 // Version: 1.0
 // Author and ID and : Habiba Mohamed   ,20220106.
 //Author and ID and :  Menna Allah Reda ,20221164.                        .
 //Author and ID and :                          .

 #include <iostream>
 #include <fstream>
 #include <cstring>
 #include <cmath>
 #include "bmplib.cpp"
 #define nl '\n'


 using namespace std;

 unsigned char image1[SIZE][SIZE];
 unsigned char image2[SIZE][SIZE];
 unsigned char new_image[SIZE][SIZE];
 unsigned char image3[SIZE][SIZE];
 unsigned char image4[SIZE][SIZE];

 void loadImage1();//
 void loadImage2();//
 void saveImage();//
 void shrink_image();
 void InvertImage();//
 void flipImage();//
 void RotateImage();//
 void light_And_darker();
 void mirrorFilter();//
 void cropFilter();//
 void MergeFilter();
 void blackAndWhite();//
 void detectEdgeFilter();//
 void shuffle();
 void Blure_image();
 void enlarge_filter();
 void printFilters();
 //-------------------------------------
 int main()
 {
     cout << "Ahlan ya user ya habiby^_^ :)  \n\n";
     loadImage1();
    printFilters();
     int filterNum;
     while(cin>>filterNum, filterNum){
         bool done = true;
         switch(filterNum) {
             case 1://done
                 blackAndWhite();
                 break;
             case 2://done
                 InvertImage();
                 break;
             case 3://done
                 loadImage2();
                 MergeFilter();
                 break;
             case 4:// done
                 flipImage();
                 break;
             case 5://done
                 RotateImage();
                 break;
             case 6:// done
                 light_And_darker();
                 break;
             case 7://done
                 detectEdgeFilter();
                 break;
             case 8://done
                 enlarge_filter();
                 break;
             case 9://done
                 cropFilter();
                 break;
             case 10 ://done
                 mirrorFilter();
                 break;
             case 11://done
                 shuffle();
                 break;
             case 12://done
                 shrink_image();
                 break;
             case 13 ://done
                 Blure_image();
                 break;
             default:
                 cout << "INVALID...";
                 done = false;
                 break;
         }
         cout << endl;
         cout <<(done? "THE FILTER APPLIED SUCCESSFULLY...\n":"Try again!\n");
         cout<<"Will you try another filter?\n\n";
         printFilters();
     }
     saveImage();
 }

 void loadImage1()
 {
     char first_image[100];

     // Get gray scale image file name
     cout << "Enter the first image file name: ";
     cin >> first_image;

     // Add to it .bmp extension and load image
     strcat ( first_image, ".bmp");
     readGSBMP( first_image, image1);
 }
 /////////////////////////////////////////////////

 void loadImage2(){
     char  second_image[100];

     // Get gray scale image file name
     cout << "Enter the second image name: ";
     cin >> second_image;

     // Add to it .bmp extension and load image
     strcat (second_image, ".bmp");
     readGSBMP(second_image, image2);
 }
 ///////////////////////////////////////////////
 void saveImage(){
     char new_image[100];

     // Get gray scale image target file name
     cout << "Enter the target image file name: ";
     cin >> new_image ;

     // Add to it .bmp extension and load image
     strcat (new_image, ".bmp");
     writeGSBMP(new_image,  image1);
 }

 void printFilters(){
     cout<<"Please select the filter to apply or 0 to Exit:\n";
     cout << "1-Black & White Filter \n";
     cout<< "2-Invert Filter \n";
     cout<<"3-Merge Filter \n";
     cout<<"4-Flip Image \n";
     cout<<"5-Rotate Image \n";
     cout<<"6-Darken and lighten Image\n";
     cout<<"7-Detect Edges Filter\n8-Enlarge Image \n";
     cout<<"9-Shrink image\n";
     cout<<"10-Mirror Filter\n";
     cout<<"11-Shuffle Filter\n";
     cout<<"12-Shrink_image\n";
     cout<<"13-Blur_image\n";
     cout<<"0-Exit \n";
     cout<<"Choose number: ";
 }
 /////////////////////////////////////////////
 void blackAndWhite(){
     for (int i = 0; i<SIZE; i++)
         for (int j = 0; j<SIZE; j++)
             image1[i][j] = (image1[i][j] < 128? 0:255);
 }
 //////////////////////////////////////////
 void flipImage(){
     cout<<"Enter H for horizontal flip, or V for vertical flip: ";
     char c;
     while (cin>>c, tolower(c) != 'h' && tolower(c) != 'v')
         cout<<"INVALID, please enter a valid letter! ";
     if (tolower(c) == 'h')
         for (int i = 0; i<SIZE/2; i++)
             for (int j = 0; j<SIZE; j++)
                 swap(image1[i][j],image1[SIZE-i][j]);
     else
         for (int i = 0; i<SIZE; i++)
             for (int j = 0; j<SIZE/2; j++)
                 swap(image1[i][j],image1[i][SIZE-j]);
 }
 //////////////////////////////////////////////
 void detectEdgeFilter(){
     for (int i = 0; i<SIZE; i++)
         for (int j = 0; j<SIZE; j++)
             if (abs(image1[i][j] - image1[i][j+1]) > 30 || abs(image1[i][j] - image1[i+1][j]) > 30 || (i && abs(image1[i][j] - image1[i-1][j]) > 30) || (j && abs(image1[i][j] - image1[i][j-1]) > 30))
                 image2[i][j] = 0;
             else
                 image2[i][j] = 255;
     for (int i = 0; i<SIZE; i++)
         for (int j = 0; j<SIZE; j++)
             image1[i][j] = image2[i][j];
 }
 /////////////////////////////////////////////
 void mirrorFilter(){
     cout<<"Enter 'L' to mirror the left half,"<<nl;
     cout<<"or 'R' for the right half,"<<nl;
     cout<<"or 'U' for the upper half,"<<nl;
     cout<<"or 'D' for the down half."<<nl;
     char c;
     while (cin>>c, tolower(c) != 'l' && tolower(c) != 'r' && tolower(c) != 'u' && tolower(c) != 'd')
         cout<<"INVALID, please enter a valid letter! ";
     if (tolower(c) == 'u')
         for (int i = 0; i<SIZE/2; i++)
             for (int j = 0; j<SIZE; j++)
                 image1[SIZE - i][j] = image1[i][j];
     else if (tolower(c) == 'd')
         for (int i = 0; i<SIZE/2; i++)
             for (int j = 0; j<SIZE; j++)
                 image1[i][j] = image1[SIZE - i][j];
     else if (tolower(c) == 'l')
         for (int i = 0; i<SIZE; i++)
             for (int j = 0; j<SIZE/2; j++)
                 image1[i][SIZE - j] = image1[i][j];
     else
         for (int i = 0; i<SIZE; i++)
             for (int j = 0; j<SIZE/2; j++)
                 image1[i][j] = image1[i][SIZE - j];
 }

 //////////////////////////////////////////////
 void MergeFilter(){
     for (int i = 0; i<SIZE; i++)
         for (int j = 0; j<SIZE; j++)
             image1[i][j] = (image1[i][j] + image2[i][j]) / 2;
 }
 //////////////////////////////////////////////
 void cropFilter(){
     int x,y,l,w;
     cout<<"Enter the coordinates of the beginning point: ";
     while (cin>>x>>y, x > 255 || y > 255)
         cout<<"Out Of Range, please enter a valid point! ";
     cout<<"Enter the dimensions of the needed image: ";
     while(cin>>l>>w, x+l > 255 || y+w > 255)
         cout<<"Out Of Range, please enter a valid point! ";
     for (int i = 0; i<SIZE; i++)
         for (int j = 0; j<SIZE; j++)
             if (i < x || i > x+l || j < y || j > y+w)
                 image1[i][j] = 255;
 }
 /////////////////////////////////////////////
 void light_And_darker()
 {
     cout <<"What do u want light(l)or darker(d)? ";
     char c ;
     cin >> c ;
     if(tolower(c)=='l'){
         for (int i = 0; i < SIZE; i++) {
             for (int j = 0; j< SIZE; j++) {

                 image1[i][j] = (255 + image1[i][j]) / 2;
             }
         }
     }
     else if(tolower(c)=='d')
     {
         for (int i = 0; i < SIZE; i++) {
             for (int j = 0; j< SIZE; j++) {
                 image1[i][j] =  image1[i][j] / 2;
             }
         }
     }
     else
     {
         cout<<"Invalid input Plz try again ^_^"<<nl;
         light_And_darker();
     }
 }
 /////////////////////////////////////////////////////////
 void  InvertImage() {
     for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
             image1[i][j] = 255 - image1[i][j];
         }
     }
 }///////////////////////////////////////////////////////
 void RotateImage(){
     int p=0;
     cout<<"choose the angle of rotate by clockwise\n";
     cout<<"1-90 degree\n2-180 degree\n3-270 degree\n";
     cin>>p;
     unsigned char copy[SIZE][SIZE];
     for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
             copy[i][j]=image1[i][j];}}
     for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
             if(p==1)
                 image1[i][j]=copy[255-j][i];
             else if(p==2)
                 image1[i][j]=copy[255-i][255-j];
             else if(p==3)
                 image1[i][j]=copy[j][255-i];}}
 }
 void enlarge_filter(){
     unsigned char copy[SIZE][SIZE];
     for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
             copy[i][j]=image1[i][j];}}
     //quarter1
     cout<<"choose the quarter that you want to enlarge\n ";
     int quarter;
     cin>>quarter;
     if(quarter==1){
         for (int i=0,k=0;i<=127;i++,k+=2) {
             for (int j=0,m=0;j<127;j++,m+=2) {
                 image1[k][m]=copy[i][j];
                 image1[k][m+1]=copy[i][j];
                 image1[k+1][m]=copy[i][j];
                 image1[k+1][m+1]=copy[i][j];
             }
         }}
     else if(quarter==2){
         for (int i=0,k=0;i<=127;i++,k+=2) {
             for (int j=127,m=0;j<SIZE;j++,m+=2) {
                 image1[k][m]=copy[i][j];
                 image1[k][m+1]=copy[i][j];
                 image1[k+1][m]=copy[i][j];
                 image1[k+1][m+1]=copy[i][j];
             }
         }
     }
     else if(quarter==3){
         for (int i=127,k=0;i<=SIZE;i++,k+=2) {
             for (int j=0,m=0;j<127;j++,m+=2) {
                 image1[k][m]=copy[i][j];
                 image1[k][m+1]=copy[i][j];
                 image1[k+1][m]=copy[i][j];
                 image1[k+1][m+1]=copy[i][j];
             }
         }
     }
     else if(quarter==4){
         for (int i=127,k=0;i<=SIZE;i++,k+=2) {
             for (int j=127,m=0;j<SIZE;j++,m+=2) {
                 image1[k][m]=copy[i][j];
                 image1[k][m+1]=copy[i][j];
                 image1[k+1][m]=copy[i][j];
                 image1[k+1][m+1]=copy[i][j];
             }
         }
     }
 }
 ////////////////////////////////////////////////////////////
 void shuffle(){
     unsigned char copy[SIZE][SIZE];
     for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
             copy[i][j]=image1[i][j];}}
     int q1,q2,q3,q4;
     cout<<"enter the order of quarters that you want\n";
     cin>>q1>>q2>>q3>>q4;
     //quarter1
     for (int i = 0; i < 127; i++) {
         for (int j = 0; j < 127; j++) {
             if(q1==1)
                 image1[i][j]=copy[i][j];
             else if(q1==2)
                 image1[i][j]=copy[i][j+127];
             else if(q1==3)
                 image1[i][j]=copy[i+127][j];
             else if(q1==4)
                 image1[i][j]=copy[i+127][j+127];
         }
     }
     //quarter2
     for (int i = 0; i < 127; i++) {
         for (int j = 127; j < SIZE; j++) {
             if(q2==1)
                 image1[i][j]=copy[i][j-127];
             else if(q2==2)
                 image1[i][j]=copy[i][j];
             else if(q2==3)
                 image1[i][j]=copy[i+127][j-127];
             else if(q2==4)
                 image1[i][j]=copy[i+127][j];
         }
     }
     //quarter3
     for (int i = 127; i < SIZE; i++) {
         for (int j = 0; j < 127; j++) {
             if(q3==1)
                 image1[i][j]=copy[i-127][j];
             else if(q3==2)
                 image1[i][j]=copy[i-127][j+127];
             else if(q3==3)
                 image1[i][j]=copy[i][j];
             else if(q3==4)
                 image1[i][j]=copy[i][j+127];
         }
     }
     //quarter4
     for (int i = 127; i < SIZE; i++) {
         for (int j = 127; j < SIZE; j++) {
             if(q4==1)
                 image1[i][j]=copy[i-127][j-127];
             else if(q4==2)
                 image1[i][j]=copy[i-127][j];
             else if(q4==3)
                 image1[i][j]=copy[i][j-127];
             else if(q4==4)
                 image1[i][j]=copy[i][j];
         }
     }
 }

 void shrink_image()
 {
     int size;
     cout<<"please enter the size of photo^_^\n";
     cin>> size;
     for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
             if(i <SIZE/size&& j<SIZE/size)
                 image1[i][j]=image1[i*size][j*size];
             else
                 image1[i][j]=255;
         }}}
 void Blure_image() {
     for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
             image1[i][j]=(image1[i][j]+image1[i+1][j+1]+image1[i-1][j-1]+image1[i+1][j]+image1[i][j+1]
             +image1[i+2][j+2]+image1[i-1][j]+image1[i][j-1]+image1[i+2][j]+
             image1[i][j+2]+image1[i-2][j]+image1[i][j-2]+
                     image1[i-2][j+1]+image1[i+2][j-1]+image1[i+1][j+2]+image1[i-1][j+2]+
                     image1[i+1][j-2])/17;

 //blur effect is achieved by manipulating the existing pixels in the image. When you apply a blur filter,
 // the software averages the color and intensity of neighboring pixels to create a smoother appearance.
         }
     }
 }

