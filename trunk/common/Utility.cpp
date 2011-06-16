//
// Utility.cpp
//

#include "Utility.h"

std::vector<std::string> Utility::GetFileLines(const std::string &filename, unsigned int minLineLength)
{
    std::ifstream file(filename);
    std::vector<std::string> result;
    std::string curLine;
    while(!file.fail())
    {
        std::getline(file, curLine);
        if(!file.fail() && curLine.length() >= minLineLength)
        {
            result.push_back(curLine);
        }
    }
    return result;
}

GLuint Utility::MakeOpenGLBitmap(const std::string &filename)
{
#ifdef WIN32
    std::string commandLine = "../windows/exe/convert.exe " + filename + " temp.bmp";
#endif
    Utility::ExecuteCommand(commandLine.c_str());

    struct BitmapFileHeader {
        unsigned short    bfType;
        unsigned int      bfSize;
        unsigned short    bfReserved1;
        unsigned short    bfReserved2;
        unsigned int      bfOffBits;
    };

    struct BitmapInfoHeader {
        unsigned int      biSize;
        long              biWidth;
        long              biHeight;
        unsigned short    biPlanes;
        unsigned short    biBitCount;
        unsigned int      biCompression;
        unsigned int      biSizeImage;
        long              biXPelsPerMeter;
        long              biYPelsPerMeter;
        unsigned int      biClrUsed;
        unsigned int      biClrImportant;
    };

    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    FILE *file;

    //open the file and read in the headers
    file = fopen("temp.bmp", "rb");

    fread(&bmfh, 14, 1, file);
    fread(&bmih, 40, 1, file);

    unsigned int width = bmih.biWidth;
    unsigned int height = abs(bmih.biHeight);

    unsigned int *bitmapData = new unsigned int[width * height];
    if(bmih.biBitCount == 24)
    {
        unsigned int pitch = width * 3;
        unsigned int excessPitch = 0;
        while(double(pitch / 4) != double(pitch) / 4.0)
        {
            pitch++;
            excessPitch++;
        }

        unsigned char *dataStore = new unsigned char[pitch * height];
        fread(dataStore, 1, pitch * height, file);

        unsigned int dataIndex = 0;
        for(unsigned int y = 0; y < height; y++)
        {
            for(unsigned int x = 0; x < width; x++)
            {
                unsigned int curColor = 0;
                ((unsigned char *)&curColor)[2] = dataStore[dataIndex++];
                ((unsigned char *)&curColor)[1] = dataStore[dataIndex++];
                ((unsigned char *)&curColor)[0] = dataStore[dataIndex++];
                bitmapData[y * width + x] = curColor;
            }
            dataIndex += excessPitch;
        }

        delete[] dataStore;
    }
    else
    {
        std::cout << "Invalid bit count: " << bmih.biBitCount << std::endl;
    }
    fclose(file);

    GLuint texture;

    glGenTextures( 1, &texture );
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmapData);

    delete[] bitmapData;
    return texture;
}

#ifdef WIN32
#include <Windows.h>
void Utility::ExecuteCommand(const char *command)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    std::string commandCopy = command;

    // Start the child process. 
    if( !CreateProcess( NULL,   // No module name (use command line)
        &commandCopy[0],        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        std::cout << "Failed to create process\n";
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );
    
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}
#endif