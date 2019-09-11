//
// Created by JOSHUA HADDAD on 2019-03-11.
//

#include "ImageProcessor.h"

int main(){
    ImageProcessor imageHandler = ImageProcessor();

    //Testing equality operator and equality function
    Image testEquality = imageHandler.loadImage("car.tga", "input");
    Image testEqual = imageHandler.loadImage("car.tga", "input");
    cout << "Equality test images loaded..." << endl;
    /*assert(testEquality == testEquality);
    assert(testEquality == testEqual);
    assert(imageHandler.checkImages("car.tga", "input", "car.tga", "input"));*/
    
    if(testEquality == testEquality && testEquality == testEqual && imageHandler.checkImages("car.tga", "input", "car.tga", "input"))
		cout << "Equality operator functioning properly \n" << endl;

    //Loading all images
    Image car = imageHandler.loadImage("car.tga", "input");
    Image circles = imageHandler.loadImage("circles.tga", "input");
    Image layer1 = imageHandler.loadImage("layer1.tga", "input");
    Image layer2 = imageHandler.loadImage("layer2.tga", "input");
    Image layerBlue = imageHandler.loadImage("layer_blue.tga", "input");
    Image layerGreen = imageHandler.loadImage("layer_green.tga", "input");
    Image layerRed = imageHandler.loadImage("layer_red.tga", "input");
    Image pattern1 = imageHandler.loadImage("pattern1.tga", "input");
    Image pattern2 = imageHandler.loadImage("pattern2.tga", "input");
    Image text = imageHandler.loadImage("text.tga", "input");
    Image text2 = imageHandler.loadImage("text2.tga", "input");
    cout << "Images loaded!" << endl;

    //Loading examples
    Image example1 = imageHandler.loadImage("EXAMPLE_part1.tga", "examples");
    Image example2 = imageHandler.loadImage("EXAMPLE_part2.tga", "examples");
    Image example3 = imageHandler.loadImage("EXAMPLE_part3.tga", "examples");
    Image example4 = imageHandler.loadImage("EXAMPLE_part4.tga", "examples");
    Image example5 = imageHandler.loadImage("EXAMPLE_part5.tga", "examples");
    Image example6 = imageHandler.loadImage("EXAMPLE_part6.tga", "examples");
    Image example7 = imageHandler.loadImage("EXAMPLE_part7.tga", "examples");
    Image example8b = imageHandler.loadImage("EXAMPLE_part8_b.tga", "examples");
    Image example8g = imageHandler.loadImage("EXAMPLE_part8_g.tga", "examples");
    Image example8r = imageHandler.loadImage("EXAMPLE_part8_r.tga", "examples");
    Image example9 = imageHandler.loadImage("EXAMPLE_part9.tga", "examples");
    Image example10 = imageHandler.loadImage("EXAMPLE_part10.tga", "examples");
    Image extraCred = imageHandler.loadImage("EXAMPLE_extraCredit.tga", "examples");
    cout << "Examples loaded!\n" << endl;

    int i = 1;

    //Test case one
    cout << "Beginning case 1 test..." << endl;
    Image caseOne = imageHandler.Multiply(layer1, pattern1);
    imageHandler.writeImage(caseOne, "part1.tga");
    /*assert(caseOne == example1);
    assert(imageHandler.checkImages("caseOne.tga", "output", "EXAMPLE_part1.tga", "examples"));*/
    
    if(caseOne == example1 && imageHandler.checkImages("part1.tga", "output", "EXAMPLE_part1.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;

    //Test case two
    cout << "Beginning case 2 test..." << endl;
    Image caseTwo = imageHandler.Subtract(layer2, car);
    imageHandler.writeImage(caseTwo, "part2.tga");
    /*assert(caseTwo == example2);
    assert(imageHandler.checkImages("caseTwo.tga", "output", "EXAMPLE_part2.tga", "examples"));*/
    
    if(caseTwo == example2 && imageHandler.checkImages("part2.tga", "output", "EXAMPLE_part2.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;
    

    //Test case three
    cout << "Beginning case 3 test..." << endl;
    Image temp = imageHandler.Multiply(layer1, pattern2);
    Image caseThree = imageHandler.Screen(text, temp);
    imageHandler.writeImage(caseThree, "part3.tga");
    /*assert(caseThree == example3);
    assert(imageHandler.checkImages("caseThree.tga", "output", "EXAMPLE_part3.tga", "examples"));*/
    if(caseThree == example3 && imageHandler.checkImages("part3.tga", "output", "EXAMPLE_part3.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;

    //Test case four
    cout << "Beginning case 4 test..." << endl;
    Image temp2 = imageHandler.Multiply(layer2, circles);
    Image caseFour = imageHandler.Subtract(pattern2, temp2);
    imageHandler.writeImage(caseFour, "part4.tga");
    /*assert(caseFour == example4);
    assert(imageHandler.checkImages("caseFour.tga", "output", "EXAMPLE_part4.tga", "examples"));*/
    
    if(caseFour == example4 && imageHandler.checkImages("part4.tga", "output", "EXAMPLE_part4.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;

    //Test case five
    cout << "Beginning case 5 test..." << endl;
    Image caseFive = imageHandler.Overlay(layer1, pattern1);
    imageHandler.writeImage(caseFive, "part5.tga");
    /*assert(caseFive == example5);
    assert(imageHandler.checkImages("caseFive.tga", "output", "EXAMPLE_part5.tga", "examples"));*/
    
    if(caseFive == example5 && imageHandler.checkImages("part5.tga", "output", "EXAMPLE_part5.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;


    //Test case six
    cout << "Beginning case 6 test..." << endl;
    Image caseSix = imageHandler.Add(car, 200, "green");
    imageHandler.writeImage(caseSix, "part6.tga");
    /*assert(caseSix == example6);
    assert(imageHandler.checkImages("caseSix.tga", "output", "EXAMPLE_part6.tga", "examples"));*/
    
    if(caseSix == example6 && imageHandler.checkImages("part6.tga", "output", "EXAMPLE_part6.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;


    //Test case seven
    cout << "Beginning case 7 test..." << endl;
    Image caseSeven = imageHandler.MultiplyChannel(car,4, "red");
    caseSeven = imageHandler.MultiplyChannel(caseSeven, 0, "blue");
    imageHandler.writeImage(caseSeven, "part7.tga");
    /*assert(caseSeven == example7);
    assert(imageHandler.checkImages("caseSeven.tga", "output", "EXAMPLE_part7.tga", "examples"));*/
    if(caseSeven == example7 && imageHandler.checkImages("part7.tga", "output", "EXAMPLE_part7.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;

    //Test case eight
    cout << "Beginning case 8 test..." << endl;
    imageHandler.writeChannels(car);
    Image red = imageHandler.loadImage("part8_r.tga", "output");
    Image green = imageHandler.loadImage("part8_g.tga", "output");
    Image blue = imageHandler.loadImage("part8_b.tga", "output");
    Image caseEight = imageHandler.Combine(red, green, blue);
    imageHandler.writeImage(caseEight, "part8.tga");
    /*assert(caseEight == car);
    assert(blue == example8b);
    assert(green == example8g);
    assert(red == example8r);
    assert(imageHandler.checkImages("part8_r.tga", "output", "EXAMPLE_part8_r.tga", "examples"));
    assert(imageHandler.checkImages("part8_g.tga", "output", "EXAMPLE_part8_g.tga", "examples"));
    assert(imageHandler.checkImages("part8_b.tga", "output", "EXAMPLE_part8_b.tga", "examples"));*/
    if(caseEight == car && blue == example8b && green == example8g && red == example8r && imageHandler.checkImages("part8_r.tga", "output", "EXAMPLE_part8_r.tga", "examples") && 
		imageHandler.checkImages("part8_g.tga", "output", "EXAMPLE_part8_g.tga", "examples") && imageHandler.checkImages("part8_b.tga", "output", "EXAMPLE_part8_b.tga", "examples"))
			cout << "Case " << i++ << " Pass\n" << endl;


    //Test case nine
    cout << "Beginning case 9 test..." << endl;
    Image caseNine = imageHandler.Combine(layerRed, layerGreen, layerBlue);
    imageHandler.writeImage(caseNine, "part9.tga");
    /*assert(caseNine == example9);
    assert(imageHandler.checkImages("caseNine.tga", "output", "EXAMPLE_part9.tga", "examples"));*/
    
    if(caseNine == example9 && imageHandler.checkImages("part9.tga", "output", "EXAMPLE_part9.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;


    //Test case ten
    cout << "Beginning case 10 test..." << endl;
    Image caseTen = imageHandler.Rotate(text2);
    imageHandler.writeImage(caseTen, "part10.tga");
    /*assert(caseTen == example10);
    assert(imageHandler.checkImages("rotate.tga", "output", "EXAMPLE_part10.tga", "examples"));*/
    
    if(caseTen == example10 && imageHandler.checkImages("part10.tga", "output", "EXAMPLE_part10.tga", "examples"))
		cout << "Case " << i++ << " Pass\n" << endl;

    //Test ec
    cout << "Beginning extra credit test... " << endl;
    Image caseEleven = imageHandler.extraCredit(circles,car,text,pattern1);
    imageHandler.writeImage(caseEleven, "part11.tga");
    imageHandler.writeImage(extraCred, "part12.tga");
    /*assert(caseEleven == extraCred);
    assert(imageHandler.checkImages("ec.tga", "output", "EXAMPLE_extraCredit.tga", "examples"));*/
    
    string ec = "No!";
    if(caseEleven == extraCred && imageHandler.checkImages("part12.tga", "output", "EXAMPLE_extraCredit.tga", "examples")){
		cout << "Extra credit case passed!\n" << endl;
		ec = "Yes!";
	}

    cout << "Tests passed: " << i-1 << "/10" << endl;
    cout << "Extra credit passed: " << ec << endl;

    return 0;
}



