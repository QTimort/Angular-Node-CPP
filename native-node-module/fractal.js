function fractal() {
    var iX,iY;
    const iXmax = 12000;
    const iYmax = 12000;
    var Cx,Cy;
    const CxMin=-2.5;
    const CxMax=1.5;
    const CyMin=-2.0;
    const CyMax=2.0;
    var PixelWidth=(CxMax-CxMin)/iXmax;
    var PixelHeight=(CyMax-CyMin)/iYmax;
    var Zx, Zy;
    var Zx2, Zy2;
    var Iteration;
    const IterationMax=400;
    const EscapeRadius=2;
    var ER2=EscapeRadius*EscapeRadius;


    for(iY=0;iY<iYmax;iY++)
    {
        Cy=CyMin + iY*PixelHeight;
        if (Math.abs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
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
                console.log("impossible");
            }
            //std::cout << Iteration << " ";
        }
    }
}

fractal();
