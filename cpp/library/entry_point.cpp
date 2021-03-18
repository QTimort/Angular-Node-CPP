//
// Created by Timothy Diguiet on 18/03/2021.
//
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "entry_point.h"

struct BmpHeader {
    char bitmapSignatureBytes[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile = 54;
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;
} bmpHeader;

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 512; // in pixels
    int32_t height = 512; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
} bmpInfoHeader;

struct BmpImage {
    BmpHeader header;
    BmpInfoHeader infoHeader;
    char *bytes;
};

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
        }
    }
}

void GetImageDataFromHBITMAP(HDC hdc, HBITMAP bitmap, char* pImageData) {
    BITMAPINFO bmpInfo;
    memset(&bmpInfo, 0, sizeof(BITMAPINFOHEADER));
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    GetDIBits(hdc, bitmap, 0, 0, nullptr, &bmpInfo, DIB_RGB_COLORS);
    bmpInfo.bmiHeader.biBitCount = 24;
    bmpInfo.bmiHeader.biCompression = BI_RGB;
    GetDIBits(hdc, bitmap, 0, bmpInfo.bmiHeader.biHeight, pImageData, &bmpInfo, DIB_RGB_COLORS);
}

// todo fixme, something is wrong with the screen saving, the image when saved shifts horizontally and vertically
BmpImage GetScreenShot(bool saveInClipboard) {
    int x1, y1, x2, y2, w, h;

    // get screen dimensions
    x1  = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1  = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2  = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2  = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    w   = x2 - x1;
    h   = y2 - y1;

    // copy screen to bitmap
    HDC     hScreen = GetDC(nullptr);
    HDC     hDC     = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet    = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);

    if (saveInClipboard) {
        // save bitmap to clipboard
        OpenClipboard(nullptr);
        EmptyClipboard();
        SetClipboardData(CF_BITMAP, hBitmap);
        CloseClipboard();
    }
    auto *pImageData = static_cast<char *>(malloc(w * h * 4));
    GetImageDataFromHBITMAP(hDC, hBitmap, pImageData);

    // clean up
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(nullptr, hScreen);
    DeleteObject(hBitmap);

    BmpImage image;
    image.bytes = pImageData;
    image.header.sizeOfBitmapFile += w * h * 4;
    image.infoHeader.width = w;
    image.infoHeader.height = h;
    return image;
}

void writeBmpImage(const BmpImage &image) {
    std::ofstream file("screenshot.bmp", std::ios::binary);
    file.write((char *) &image.header, 14);
    file.write((char *) &image.infoHeader, 40);
    file.write(image.bytes, image.infoHeader.width * image.infoHeader.height * 4);
}

void writeBmpImage(const char *image, size_t size) {
    std::ofstream file("screenshot.bmp", std::ios::binary);
    file.write(image, size);
}

std::pair<void *, size_t> EntryPoint(int argc, const char * argv) {
    #pragma EXPORT
    std::cout << "Hello, World!" << std::endl;
    BmpImage image = GetScreenShot(false);
    //writeBmpImage(image);
    const unsigned int headerSize = 14;
    const unsigned int infoHeaderSize = 40;
    const size_t imageSize = image.infoHeader.width * image.infoHeader.height * 4;
    char *imageBytes = static_cast<char *>(std::malloc(image.header.sizeOfBitmapFile));
    std::cout << std::to_string(image.header.sizeOfBitmapFile) << std::endl;
    std::memcpy(imageBytes, &image.header, headerSize);
    std::memcpy(imageBytes + headerSize, &image.infoHeader, infoHeaderSize);
    std::memcpy(imageBytes + headerSize + infoHeaderSize, image.bytes, imageSize);
    std::free(image.bytes);
    //writeBmpImage(imageBytes, image.header.sizeOfBitmapFile);
    return std::make_pair(imageBytes, image.header.sizeOfBitmapFile);
	//fractal();
}
