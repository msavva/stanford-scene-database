//
// Utility.cpp
//

#include "Common.h"

bool Utility::FileExists(const std::string &filename)
{
    std::ifstream file(filename);
    return (!file.fail());
}

std::vector<std::string> Utility::GetFileLines(const std::string &filename, unsigned int minLineLength)
{
    if(!Utility::FileExists(filename))
    {
        std::cout << "Required file not found: " << filename << '\n';
        exit(1);
    }
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

std::vector<std::string> Utility::PartitionString(const std::string &s, const std::string &separator)
{
    std::vector<std::string> result;
    std::string curEntry;
    for(unsigned int outerCharacterIndex = 0; outerCharacterIndex < s.length(); outerCharacterIndex++)
    {
        bool isSeperator = true;
        for(unsigned int innerCharacterIndex = 0; innerCharacterIndex < separator.length() && outerCharacterIndex + innerCharacterIndex < s.length() && isSeperator; innerCharacterIndex++)
        {
            if(s[outerCharacterIndex + innerCharacterIndex] != separator[innerCharacterIndex])
            {
                isSeperator = false;
            }
        }

        if(isSeperator)
        {
            if(curEntry.length() > 0)
            {
                result.push_back(curEntry);
                curEntry.clear();
            }
            outerCharacterIndex += separator.length() - 1;
        }
        else
        {
            curEntry.push_back(s[outerCharacterIndex]);
        }
    }
    if(curEntry.length() > 0)
    {
        result.push_back(curEntry);
    }
    return result;
}

int Utility::StringToInt(const std::string &s)
{
    std::stringstream stream(std::stringstream::in | std::stringstream::out);
    stream << s;
    
    int result;
    stream >> result;
    return result;
}

float Utility::StringToFloat(const std::string &s)
{
    std::stringstream stream(std::stringstream::in | std::stringstream::out);
    stream << s;

    float result;
    stream >> result;
    return result;
}

std::vector<int> Utility::StringToIntegerList(const std::string &s, const std::string &prefix)
{
    std::string subString = Utility::PartitionString(s, prefix)[0];
    auto parts = Utility::PartitionString(subString, " ");

    std::vector<int> result(parts.size());
    for(unsigned int resultIndex = 0; resultIndex < result.size(); resultIndex++)
    {
        result[resultIndex] = Utility::StringToInt(parts[resultIndex]);
    }
    return result;
}

std::vector<float> Utility::StringToFloatList(const std::string &s, const std::string &prefix)
{
    std::string subString = Utility::PartitionString(s, prefix)[0];
    auto parts = Utility::PartitionString(subString, " ");

    std::vector<float> result(parts.size());
    for(unsigned int resultIndex = 0; resultIndex < result.size(); resultIndex++)
    {
        result[resultIndex] = Utility::StringToFloat(parts[resultIndex]);
    }
    return result;
}

GLuint Utility::MakeOpenGLBitmap(const std::string &filename)
{
#ifdef WIN32
    std::string commandLine = "../windows/exe/convert.exe " + filename + " temp.bmp";
#else
    std::string commandLine = "convert.exe " + filename + " temp.bmp";
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
    else if(bmih.biBitCount == 8)
    {
        unsigned int pitch = width;
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
                ((unsigned char *)&curColor)[0] = dataStore[dataIndex];
                ((unsigned char *)&curColor)[1] = dataStore[dataIndex];
                ((unsigned char *)&curColor)[2] = dataStore[dataIndex++];
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
#else
void Utility::ExecuteCommand(const char *command)
{
    system(command);
}
#endif
