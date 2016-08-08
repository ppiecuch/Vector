//
//  VectorTest.h
//  VectorQtTest
//
//  Created by Danny Dulai on 2/1/13.
//  Copyright (c) 2013 Danny Dulai. All rights reserved.
//

class VectorTest
{
    long lastTicks;
    float cubeRotationAngle;

public:
	void draw(int t = 0);
	void prepare(int w, int h);
	void reshape(int w, int h);
};
