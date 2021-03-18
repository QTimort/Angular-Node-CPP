//
// Created by Timothy Diguiet on 18/03/2021.
//
#include <iostream>
#include <string>
#include "entry_point.h"

void fractal() {
    int iX,iY;
    const int iXmax = 12000;
    const int iYmax = 12000;
    double Cx,Cy;
    const double CxMin=-2.5;
    const double CxMax=1.5;
    const double CyMin=-2.0;
    const double CyMax=2.0;
    double PixelWidth=(CxMax-CxMin)/iXmax;
    double PixelHeight=(CyMax-CyMin)/iYmax;
    double Zx, Zy;
    double Zx2, Zy2;
    int Iteration;
    const int IterationMax=400;
    const double EscapeRadius=2;
    double ER2=EscapeRadius*EscapeRadius;


    for(iY=0;iY<iYmax;iY++)
    {
        Cy=CyMin + iY*PixelHeight;
        if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
        for(iX=0;iX<iXmax;iX++)
        {
            Cx=CxMin + iX*PixelWidth;
            /* initial value of orbit = critical point Z= 0 */
            Zx=0.0;
            Zy=0.0;
            Zx2=Zx*Zx;
            Zy2=Zy*Zy;
            /* */
            for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
            {
                Zy=2*Zx*Zy + Cy;
                Zx=Zx2-Zy2 +Cx;
                Zx2=Zx*Zx;
                Zy2=Zy*Zy;
            };
			if (Iteration == 401) {
                std::cout << "imposible" << std::endl;
            }
            /* compute  pixel color (24 bit = 3 bytes) */
        }
    }
}

void EntryPoint(int argc, const char * argv) {
    #pragma EXPORT
    std::cout << "Hello, World!" << std::endl;
	fractal();
}
