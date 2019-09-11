//
// Created by JOSHUA HADDAD on 2019-03-11.
//

#include "ImageProcessor.h"


Image ImageProcessor::loadImage(string filename, string folder){
    Image loadedImage;
    Header head;

    //Open the file
    string filepath = "./";
    filepath += folder + "/";
    filepath += filename;
    ifstream fileReader(filepath, ios_base::binary);


    //Fill the header with information
    fileReader.read(&head.idLength, sizeof(head.idLength));
    fileReader.read(&head.colorMapType, sizeof(head.colorMapType));
    fileReader.read(&head.dataTypeCode, sizeof(head.dataTypeCode));
    fileReader.read((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
    fileReader.read((char*)&head.colorMapLength, sizeof(head.colorMapLength));
    fileReader.read(&head.colorMapDepth, sizeof(head.colorMapDepth));
    fileReader.read((char*)&head.xOrigin, sizeof(head.xOrigin));
    fileReader.read((char*)&head.yOrigin, sizeof(head.yOrigin));
    fileReader.read((char*)&head.width, sizeof(head.width));
    fileReader.read((char*)&head.height, sizeof(head.height));
    fileReader.read(&head.bitsPerPixel, sizeof(head.bitsPerPixel));
    fileReader.read(&head.imageDescriptor, sizeof(head.imageDescriptor));


    //Create pixel array
    int numPixel = head.width*head.height;

    //Fill pixel array with all the pixels
    for(unsigned int i = 0; i < numPixel; i++) {
        Pixel currentPixel;

        //Read each pixel byte by byte
        fileReader.read((char *) &currentPixel.blue, 1);
        fileReader.read((char *) &currentPixel.green, 1);
        fileReader.read((char *) &currentPixel.red, 1);

        loadedImage.pixels.push_back(currentPixel);

    }

    //Set the head and pixel vectors to their respective loaded variables
    loadedImage.head = head;
    loadedImage.size = numPixel;

    fileReader.close();

    return loadedImage;
}

//Takes an image object and writes the data to a specified string filepath.
bool ImageProcessor::writeImage(Image image, string filepath){

    //Open file
    string path = "./output/";
    path += filepath;
    ofstream fileWriter(path, ios_base::binary);
    //Write header
    fileWriter.write((char*)&image.head.idLength, sizeof(image.head.idLength));
    fileWriter.write((char*)&image.head.colorMapType, sizeof(image.head.colorMapType));
    fileWriter.write((char*)&image.head.dataTypeCode, sizeof(image.head.dataTypeCode));
    fileWriter.write((char*)&image.head.colorMapOrigin, sizeof(image.head.colorMapOrigin));
    fileWriter.write((char*)&image.head.colorMapLength, sizeof(image.head.colorMapLength));
    fileWriter.write((char*)&image.head.colorMapDepth, sizeof(image.head.colorMapDepth));
    fileWriter.write((char*)&image.head.xOrigin, sizeof(image.head.xOrigin));
    fileWriter.write((char*)&image.head.yOrigin, sizeof(image.head.yOrigin));
    fileWriter.write((char*)&image.head.width, sizeof(image.head.width));
    fileWriter.write((char*)&image.head.height, sizeof(image.head.height));
    fileWriter.write((char*)&image.head.bitsPerPixel, sizeof(image.head.bitsPerPixel));
    fileWriter.write((char*)&image.head.imageDescriptor, sizeof(image.head.imageDescriptor));


    //Write pixels
    for(int i = 0; i < image.size; i++){
        Pixel currentPixel = image.pixels.at(i);
        fileWriter.write((char*)&currentPixel.blue, 1);
        fileWriter.write((char*)&currentPixel.green, 1);
        fileWriter.write((char*)&currentPixel.red, 1);
    }

    fileWriter.close();
    return true;
}

//This takes two images and multiplies each pixel using the ColorProduct function 
Image ImageProcessor::Multiply(Image &top, Image &bottom){
    
    //Initialize the Image which will store the multiplied data
    Image C;
    C.size = top.size;
    C.head = top.head;

    //For each pixel, multiply the top and bottom pixel
    for(int i = 0; i < top.size; i++){
        Pixel productPixel;
        Pixel pixelA = top.pixels.at(i);
        Pixel pixelB = bottom.pixels.at(i);

        //Multiply each color component and save to the productPixel
        productPixel.red = ColorProduct(pixelA.red, pixelB.red)+.5;
        productPixel.green = ColorProduct(pixelA.green, pixelB.green)+.5;
        productPixel.blue = ColorProduct(pixelA.blue, pixelB.blue)+.5;

        //Add the created pixel to the product Image's pixel vector
        C.pixels.push_back(productPixel);
    }

return C;

}

//Takes two pixels and subtracts them, clamping at 0
Image ImageProcessor::Subtract(Image &top, Image &bottom){
    //Initalize an image object and copy header and size
    Image C;
    C.size = bottom.size;
    C.head = bottom.head;

    //Storage variable for the sum and variable with max value of char
    int sum;
    int max = 255;

    //For each pixel, if subtraction is less than 0 set to 0, otherwise set to the subtraction
    for(int i = 0; i < top.size; i++){
        Pixel sumPixel;

        sum = bottom.pixels.at(i).red - top.pixels.at(i).red;
        if(sum < 0)
            sum = 0;
        sumPixel.red = sum;

        sum = bottom.pixels.at(i).green - top.pixels.at(i).green;
        if(sum < 0)
            sum = 0;
        sumPixel.green = sum;

        sum = bottom.pixels.at(i).blue - top.pixels.at(i).blue;
        if(sum < 0)
            sum = 0;
        sumPixel.blue = sum;

        //Add the created pixel to the C image's pixel vector
        C.pixels.push_back(sumPixel);
    }

    return C;

}

//Takes the negative of A, essentially taking color component x and making new component y = 255-x
Image ImageProcessor::Negative(Image &A) {
    Image negativeA;
    float colorA;
    negativeA.size =  A.size;
    negativeA.head =  A.head;

    //For each pixel, take the negative using the ColorNegative function below
    for(unsigned int i = 0; i < A.size; i++){
        Pixel pixelA;
        Pixel pixelB;

        colorA = ColorNegative(A.pixels.at(i).red);
        pixelA.red = colorA + .5;

        colorA = ColorNegative(A.pixels.at(i).green);
        pixelA.green = colorA + .5;


        colorA = ColorNegative(A.pixels.at(i).blue);
        pixelA.blue = colorA + .5;

        negativeA.pixels.push_back(pixelA);

    }
    return negativeA;
}

//Multiplies the images then takes the negative of the product image
Image ImageProcessor::Screen(Image &A, Image &B){
    Image negativeA = Negative(A);
    Image negativeB = Negative(B);
    Image productAB = Multiply(negativeA, negativeB);
    return Negative(productAB);
}

//Uses the ColorOverlay function on each color component
Image ImageProcessor::Overlay(Image &A, Image &B) {
    Image overlayImage;
    overlayImage.head = A.head;
    overlayImage.size = A.size;
    for(unsigned int i = 0; i < A.size; i++){
        Pixel overLayAB;
        Pixel pixelA = A.pixels.at(i);
        Pixel pixelB = B.pixels.at(i);
        overLayAB.red = ColorOverlay(pixelA.red, pixelB.red) + .5;
        overLayAB.green = ColorOverlay(pixelA.green, pixelB.green) + .5;
        overLayAB.blue = ColorOverlay(pixelA.blue, pixelB.blue) + .5;

        overlayImage.pixels.push_back(overLayAB);
    }
    return overlayImage;
}

//Adds a specific value to one color channel of an Image, clamping at 255
Image ImageProcessor::Add(Image &A, unsigned char value, string channel){
    int storage;
    Image B;
    B.head = A.head;
    B.size = A.size;

    for(int i = 0; i < A.size; i++){
        Pixel currentPixel;

        //Determines which channel is being added to, adds the colors, clamps if needed, adds the pixel
        if(channel == "red"){
            storage = A.pixels.at(i).red + value;
            currentPixel.green = A.pixels.at(i).green;
            currentPixel.blue = A.pixels.at(i).blue;
            (storage < 255) ? currentPixel.red = storage : currentPixel.red = 255;

        }
        if(channel == "green"){
            storage = A.pixels.at(i).green + value;
            currentPixel.red = A.pixels.at(i).red;
            currentPixel.blue = A.pixels.at(i).blue;
            (storage < 255) ? currentPixel.green = storage : currentPixel.green = 255;
        }
        if(channel == "blue"){
            storage = A.pixels.at(i).blue + value;
            currentPixel.red = A.pixels.at(i).red;
            currentPixel.green = A.pixels.at(i).green;
            (storage < 255) ? currentPixel.blue = storage : currentPixel.blue = 255;
        }
        B.pixels.push_back(currentPixel);

    }
    return B;
}

//Similar to Add - Multiplies a specified channel by a float value, clamping at 255 if neeeded
//This function uses a different "multiply" method than ColorProduct which scales colors!
Image ImageProcessor::MultiplyChannel(Image &A, float value, string channel){
    Image B;
    B.head = A.head;
    B.size = A.size;
    float storage;
    float max = 255;
    Pixel newPixel;

    //For each pixel, multiply color in "channel" by the value, if more than 255, store 255 (clamp)
    for(int i = 0; i < A.size; i++){
        if(channel == "red"){
            newPixel.green = A.pixels.at(i).green;
            newPixel.blue = A.pixels.at(i).blue;
            storage = A.pixels.at(i).red*value;

            //If storage is greater than 255, set the pixels value to max, otherwise just set to storage
            (storage > max) ? newPixel.red = max : newPixel.red = storage;
        }
        if(channel == "green"){
            newPixel.red = A.pixels.at(i).red;
            newPixel.blue = A.pixels.at(i).blue;
            storage = A.pixels.at(i).green*value;
            (storage > max) ? newPixel.green = max : newPixel.green = storage;
        }
        if(channel == "blue"){
            newPixel.green = A.pixels.at(i).green;
            newPixel.red = A.pixels.at(i).red;
            storage = A.pixels.at(i).blue*value;
            storage = A.pixels.at(i).blue*value;
            (storage > max) ? newPixel.blue = max : newPixel.blue = storage;
        }

        B.pixels.push_back(newPixel);
    }
    return B;
}

//Multiplies color components by dividing by max, performing the multiplication, and multiplying by max
float ImageProcessor::ColorProduct(float A, float B){
    float max = 255;
    float product;
    product = max*((A/max)*(B/max));
    return product;
}

//Calculates a negative of a color by taking 255-color (scales first)
float ImageProcessor::ColorNegative(float A){
    float max = 255;
    float storage = 0;
    storage = max*(1-A/max);
    return storage;
}

//Overlays color A and color B depending on if B (scaled to [0,1]) >= .5
float ImageProcessor::ColorOverlay(unsigned char A, unsigned char B){
    float max = 255;
    float storage;
    unsigned char overlay;

    //Scale both colors by dividing by the max value
    float scaleB = B/max;
    float scaleA = A/max;

    //If B is less than .5, perform a product and multiply by two
    if(scaleB <= .5){
        storage = 2*(ColorProduct(A, B)) + .5;
    }

    //If B is greater than .5, take the negative of double the product of the negatives
    if(scaleB > .5){
        storage = 2*ColorProduct(ColorNegative(A), ColorNegative(B));
        storage = ColorNegative(storage) + .5;
    }

    overlay = storage;
    return overlay;
}

//Rotates the image by 180 degrees
Image ImageProcessor::Rotate(Image A){
    Image B;
    B.head = A.head;
    B.size = A.size;
    Pixel currentPixel;

    //keeps track of the end of the pixel array
    int j = A.size-1;


    //To be honest this loop probably could have just started at j.
    for(unsigned int i = 0; i < A.size; i++){
        currentPixel.red = A.pixels.at(j).red;
        currentPixel.green = A.pixels.at(j).green;
        currentPixel.blue = A.pixels.at(j).blue;
        B.pixels.push_back(currentPixel);
        j--;
    }
    return B;
}

//Same as the writeImage function except it writes a specific channel to separate them
void ImageProcessor::writeChannels(Image A){
    Image red;
    Image blue;
    Image green;

    red.head = A.head; blue.head = A.head; green.head = A.head;
    red.size = A.size; blue.size = A.size; green.size = A.size;

    for(int i = 0; i < A.size; i++){
        red.pixels.push_back(Pixel(A.pixels.at(i).red, A.pixels.at(i).red, A.pixels.at(i).red));
        green.pixels.push_back(Pixel(A.pixels.at(i).green, A.pixels.at(i).green, A.pixels.at(i).green));
        blue.pixels.push_back(Pixel(A.pixels.at(i).blue, A.pixels.at(i).blue, A.pixels.at(i).blue));
    }
    writeImage(red, "part8_r.tga");
    writeImage(green, "part8_g.tga");
    writeImage(blue, "part8_b.tga");

}

//From loaded image data that was separated R,G,and B channels, recombine into one image
//This could also be used to take only the R,G,B from an image (If you wanted to take green form another image)
Image ImageProcessor::Combine(Image &R, Image &G, Image &B){
    Image C;
    C.head = R.head;
    C.size = R.size;

    Pixel currentPixel;

    for(unsigned int i = 0; i < R.size; i++){
        currentPixel.red = R.pixels.at(i).red;
        currentPixel.green = G.pixels.at(i).green;
        currentPixel.blue = B.pixels.at(i).blue;
        C.pixels.push_back(currentPixel);
    }
    return C;
}

//Loads reads each byte of two images, comparing them to make sure they are identical
//This is another fail safe for if the writeFile method breaks, as the equality operator only checks Images
bool ImageProcessor::checkImages(string filenameOne, string folderOne, string filenameTwo, string folderTwo){
    string filepath = "./";
    filepath += folderOne + "/";
    filepath += filenameOne;
    ifstream fileReader(filepath, ios_base::binary);

    string filepathTwo = "./";
    filepathTwo += folderTwo + "/";
    filepathTwo += filenameTwo;
    ifstream fileReaderTwo(filepathTwo, ios_base::binary);

    int i = 0;
    while(!fileReaderTwo.eof()){
        int byteOne = 0;
        int byteTwo = 0;

        fileReader.read((char*)&byteOne, 1);
        fileReaderTwo.read((char*)&byteTwo, 1);

        if(byteOne != byteTwo){
            fileReader.close();
            fileReaderTwo.close();
            return false;
        }
        i++;
    }

    return true;
}

//This function takes four images and places them side by side. A upper left, B up right, C bot left
Image ImageProcessor::extraCredit(Image A, Image B, Image C, Image D){
    Image addedImages;
    addedImages.head = A.head;
    addedImages.head.width = A.head.width+B.head.width;
    addedImages.head.height = A.head.height+C.head.height;
    addedImages.size = addedImages.head.width*addedImages.head.height;

    //Trackers for the width, height, and which image we are currently looking at
    int widthTracker = 0;
    int heightTracker = 0;
    int firstTrack = 0;
    int secondTrack = 0;
    int thirdTrack = 0;
    int fourthTrack = 0;

    //For each row, take the pixels and add them to the image
    //Read D -> C -> B -> A
    for(unsigned int i = 0; i < addedImages.size; i++){
        Pixel currentPixel;

        //If the height is less than C/D's height, we are in the 3rd or 4th quadrant
        if(heightTracker < D.head.height){
            //If the height tracker is less than C's width, we are in the D region
            if(widthTracker < C.head.width){
                currentPixel.red = C.pixels.at(firstTrack).red;
                currentPixel.blue = C.pixels.at(firstTrack).blue;
                currentPixel.green = C.pixels.at(firstTrack).green;
                firstTrack++;
            }

            //If we passed C lengthwise, switch to D
            else{
                currentPixel.red = D.pixels.at(secondTrack).red;
                currentPixel.blue = D.pixels.at(secondTrack).blue;
                currentPixel.green = D.pixels.at(secondTrack).green;
                secondTrack++;
            }
        }

        //Within the 1-2 quadrant
        else{
            //Same as above but this time we are in B's quadrant
            if(widthTracker < D.head.width){
                currentPixel.red = B.pixels.at(thirdTrack).red;
                currentPixel.blue = B.pixels.at(thirdTrack).blue;
                currentPixel.green = B.pixels.at(thirdTrack).green;
                thirdTrack++;
            }
            else{
                currentPixel.red = A.pixels.at(fourthTrack).red;
                currentPixel.blue = A.pixels.at(fourthTrack).blue;
                currentPixel.green = A.pixels.at(fourthTrack).green;
                fourthTrack++;
            }
        }
        widthTracker++;

        //If the width is twice D and C, we need to reset the width counter and move up one height
        if(widthTracker == D.head.width*2){
            widthTracker = 0;
            heightTracker++;
        }
        addedImages.pixels.push_back(currentPixel);
    }
    return addedImages;
}