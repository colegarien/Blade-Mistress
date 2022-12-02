// AutoUpdate.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "../src/Helper/files.h";

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include <chrono>
#include <iostream>
#include <istream>
#include <streambuf>
#include <string>
#include <sstream>
#include <fstream>
#include <bitset>

#include "Autoupdate.h"
#include "UpdateServer.h"


AutoUpdate::AutoUpdate(const UpdateServer& updateServer) 
	: newLauncher(false)
	, m_updateServer(updateServer)
{ 
}

//*********************************************************************
int AutoUpdate::DownloadFile(char *fileName)
{
	char tmp[1024];
	sprintf_s( tmp, 1024, "Updating %s  ",fileName );
	UpdateTextBox( tmp );

    bool gotFile = false;
	char tempText[1024];


	// create output directory
	sprintf_s(tempText,1024,"%s\\%s",m_updateServer.pszServerName, fileName);
    auto outputFilePath = std::filesystem::path(tempText);
    if (!std::filesystem::exists(outputFilePath.parent_path())) {
        std::filesystem::create_directories(outputFilePath.parent_path());
    }

    if (std::filesystem::exists(outputFilePath) && (std::filesystem::status(outputFilePath).permissions() & std::filesystem::perms::owner_write) == std::filesystem::perms::none) {
        // do not have write permission to file!
        UpdateTextBox("ERROR: ");
        UpdateTextBox(tempText);
        UpdateTextBox(" is read only!\r\n");
        return false;
    }

    char remoteUrl[1024];
    sprintf_s(remoteUrl, 1024, "%s/%s", m_updateServer.pszServerURL, fileName);

    // download file from remote url
    std::ofstream outputStream(outputFilePath, std::ios::out | std::ios::binary | std::ios::trunc);
    gotFile = ReadRemoteFileToStream(&outputStream, remoteUrl);
    outputStream.close();

	if (gotFile)
		UpdateTextBox( "DONE\r\n" );
	else
		UpdateTextBox( "*** ERROR\r\n" );

	return gotFile;

}

//*********************************************************************
void AutoUpdate::Update()
{
	char tmp[256];
	newLauncher = false;
	UpdateTextBox( "Updating Blade Mistress\r\n\r\n" );

	// fill local list
	sprintf_s(tmp, 256, "%s", m_updateServer.pszServerName);
    auto localRecords = GetFileDetails(std::filesystem::path(tmp));

	// download and parse index file
    std::stringstream indexDataStream("");
    char urlString[1024];
    sprintf_s(urlString, 1024, "%s/index.dat", m_updateServer.pszServerURL);
    bool remoteSucess = ReadRemoteFileToStream(&indexDataStream, urlString);
    if (!remoteSucess) {
        UpdateTextBox("Unable to get index file from website.\r\n");
        return;
    }

    auto remoteRecords = ReadFileDetailsFromStream(&indexDataStream);

	int errorCount = 0;
    for(auto& remoteRecord : remoteRecords) {
        bool hasLocalCopy = false;
        for (auto& localRecord : localRecords) {
            if (!_strnicmp("auto", (char*)localRecord.relativePath.string().c_str(), strlen("auto")))
                continue;
            else if (!_strnicmp("BMLauncher", (char*)localRecord.relativePath.string().c_str(), strlen("BMLauncher")))
                continue;
            else if (!_strnicmp("BMLauncher", (char*)localRecord.relativePath.string().c_str(), strlen("BMLInstaller")))
                    newLauncher = true;

            if (remoteRecord.relativePath == localRecord.relativePath) {
                //	if the local file is old
                sprintf_s(tmp, 256, "checking %s\r\n", remoteRecord.relativePath.string().c_str());
                UpdateTextBox(tmp);

                if (localRecord.crc32 != remoteRecord.crc32) {
                    if (!DownloadFile((char*)remoteRecord.relativePath.string().c_str())) {
                        ++errorCount;
                    }
                }

                hasLocalCopy = true;
                break;
            }
        }

        if (!hasLocalCopy) {
			// copy the new version from the website
            if (!DownloadFile((char*)remoteRecord.relativePath.string().c_str())) {
                ++errorCount;
            }
		}

	}


	// clean up
	if (errorCount) 
	{
		sprintf_s( tmp, 256,"\r\n\r\n*** %d files could not be downloaded. **\r\n", errorCount );
		UpdateTextBox( tmp );
	}
}


void AutoUpdate::UpdateTextBox(char* txt)
{
	 SendMessage( dialog, WM_USER+1, (unsigned int)txt, NULL );
}

bool AutoUpdate::IsThereNewLauncher() { return newLauncher; }
