#ifndef __AUTOUPDATE_H
#define __AUTOUPDATE_H


#include "stdafx.h"

#include "..\src\helper\linklist.h"
#include "..\src\helper\crc.h"
#include "BMLauncher.h"
#include "BMUpdater.h"

#include <chrono>
#include <vector>

struct UpdateServer;

//***************************************************************************************


class AutoUpdate
{
public:
	AutoUpdate(const UpdateServer& updateServer);
	
	~AutoUpdate() { dialog = 0; }

	void Update();
	void setDialog(HWND dlg) { dialog = dlg; }
	bool IsThereNewLauncher();


private:
	HWND dialog; // TODO replace UpdateTextBox with more generic logging interface
	bool newLauncher;
	const UpdateServer& m_updateServer;

	int DownloadFile(char *fileName);
	void UpdateTextBox(char* txt);
};

#endif
