//***************************************************************************************
// Main file designed to be the logical main for using PUMA.
//***************************************************************************************

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "puma.h"
#include "pumamesh.h"
#include "..\loginmode.h"
#include "..\helper\GeneralUtils.h"
#include "d3dutil.h"

#include "UIR_TextButton.h"
#include "UIR_TextBox.h"
#include "UIR_ScrollWindow.h"
#include "UIR_DragEdge.h"
#include "UIR_EditLine.h"

#include "..\network\NetWorldMessages.h"

#include "..\BBOServer.h"
#include "..\network\client.h"

//#include "loginmode.h"
#include "..\RobotMode.h"

#include "..\helper\autolog.h"





// The following macros set and clear, respectively, given bits
// of the C runtime library debug flag, as specified by a bitmask.
#ifdef   _DEBUG
#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)
#endif









BOOL bActive, flippedOut;
unsigned int lastTimeChecked;

int gScreenW = 640;
int gScreenH = 480;

BBOServer *server = NULL;
int createServerFlag = FALSE;

Client *	lclient;

char ipAddress[128];

//***************************************************************************************
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
   switch( msg )
   {
      case WM_DESTROY:
         PostQuitMessage( 0 );
         return 0;

	   case WM_KEYDOWN:
//			if (123 == wParam)
//	         PostQuitMessage( 0 );
			break;

	   case WM_ACTIVATE:
			bActive = LOWORD(wParam);
			if (bActive != WA_INACTIVE)
			{
//				SetTimer( puma->m_hWnd, TIMER_ID, TIMER_RATE, NULL );
		  		flippedOut = FALSE;
			}
			else
			{
		  		flippedOut = TRUE;
//		  		KillTimer( puma->m_hWnd , TIMER_ID);
			}

       	break;
		case WM_MOUSEMOVE:
			if (puma->m_bWindowed)
			{
				puma->mouseX = LOWORD(lParam);  // horizontal position of cursor  
				puma->mouseY = HIWORD(lParam);  // vertical position of cursor    
				if (puma->mouseX < 0)
					puma->mouseX = 0;
				if (puma->mouseX >= puma->ScreenW())
					puma->mouseX = puma->ScreenW()-1;
				
				if (puma->mouseY < 0)
					puma->mouseY = 0;
				if (puma->mouseY >= puma->ScreenH())
					puma->mouseY = puma->ScreenH()-1;
			}
			break;
   }

   return DefWindowProc( hWnd, msg, wParam, lParam );
}


int windowMode = FALSE;

//********************************************************************************
void ParseCommandLine(char * commandLine)
{
	unsigned int linePoint = 0; //, argPoint;

	while (linePoint < strlen(commandLine) && commandLine[linePoint])
	{
		if (!strnicmp( &(commandLine[linePoint]) , "-" , 1) ||
			!strnicmp( &(commandLine[linePoint]) , "/" , 1) )
		{
			linePoint += 1;
			
			if (!strnicmp( &(commandLine[linePoint]) , "W" , 1))
			{
				// draw in window
            windowMode = TRUE;

				while (	!isspace(commandLine[linePoint]) && commandLine[linePoint])
				{
					linePoint++;
				}
				while (	isspace(commandLine[linePoint]) && linePoint < strlen(commandLine) &&
						commandLine[linePoint])
				{
					linePoint++;
				}
			}
			else if (!strnicmp( &(commandLine[linePoint]) , "X" , 1))
			{
				// draw in window
				gScreenW = 800;
				gScreenH = 600;

				while (	!isspace(commandLine[linePoint]) && commandLine[linePoint])
				{
					linePoint++;
				}
				while (	isspace(commandLine[linePoint]) && linePoint < strlen(commandLine) &&
						commandLine[linePoint])
				{
					linePoint++;
				}
			}
			else if (!strnicmp( &(commandLine[linePoint]) , "Z" , 1))
			{
				// draw in window
				gScreenW = 1024;
				gScreenH = 768;

				while (	!isspace(commandLine[linePoint]) && commandLine[linePoint])
				{
					linePoint++;
				}
				while (	isspace(commandLine[linePoint]) && linePoint < strlen(commandLine) &&
						commandLine[linePoint])
				{
					linePoint++;
				}
			}
			else if (!strnicmp( &(commandLine[linePoint]) , "S" , 1))
			{
				// turn on server
//				createServerFlag = TRUE;

				while (	!isspace(commandLine[linePoint]) && commandLine[linePoint])
				{
					linePoint++;
				}
				while (	isspace(commandLine[linePoint]) && linePoint < strlen(commandLine) &&
						commandLine[linePoint])
				{
					linePoint++;
				}
			}
			else
			{
				// copy address
//				linePoint++;
				int start = linePoint;

				while (	!isspace(commandLine[linePoint]) && commandLine[linePoint])
				{
					linePoint++;
				}
				sprintf(ipAddress, &commandLine[start]);
				ipAddress[linePoint-start] = 0;

				while (	isspace(commandLine[linePoint]) && linePoint < strlen(commandLine) &&
						commandLine[linePoint])
				{
					linePoint++;
				}
			}
		}
	}
}

//********************************************************************************
int MaintainDeviceIntegrity(HWND hWnd)
{
   HRESULT hr;
//	D3DPRESENT_PARAMETERS   d3dpp;

//	return S_OK;

	// Test the cooperative level to see if it's okay to render
	if( FAILED( hr = puma->m_pd3dDevice->TestCooperativeLevel() ) )
	{
	   // If the device was lost, do not render until we get it back
	   if( D3DERR_DEVICELOST == hr )
	  		return D3DERR_DEVICELOST;

	   // Check if the device needs to be resized.
	   if( D3DERR_DEVICENOTRESET == hr )
	   {
//			vdMan->EraseAll();

			for (int i = 0; i < NUM_OF_PUMA_FONTS; i++)
			{
				if (puma->fonts[i].dxfont)
					puma->fonts[i].dxfont->InvalidateDeviceObjects();
			}


	  	   // Resize the device
	  	   if( SUCCEEDED( puma->m_pd3dDevice->Reset( &puma->m_d3dpp ) ) )
			{
	  	  	   // Initialize the app's device-dependent objects
				
				for (int i = 0; i < NUM_OF_PUMA_FONTS; i++)
				{
					if (puma->fonts[i].dxfont)
						puma->fonts[i].dxfont->RestoreDeviceObjects();
				}
				
				puma->m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
				puma->m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );



//				vdMan->RecoverAll();
  	  		   return S_OK;
			}

	  	   PostMessage( hWnd, WM_CLOSE, 0, 0 );
	   }
	   return hr;
	}

   return S_OK;
}

//***************************************************************************************
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine, INT )
{
	
   SET_CRT_DEBUG_FIELD( _CRTDBG_LEAK_CHECK_DF );

	aLog.Start();

	ParseCommandLine(lpCmdLine);

	puma = new CPuma();
   puma->m_dwCreationWidth   = gScreenW;
   puma->m_dwCreationHeight  = gScreenH;
	puma->Create(hInst, windowMode);

   if( puma->GetStarted( hInst, puma->m_hWnd, windowMode) )
   {
		puma->pumaCamera->m_fFarPlane   = 300.0f;
		puma->pumaCamera->Calculate();
		puma->pumaCamera->AssertView(puma->m_pd3dDevice);



      // Show the window
      ShowWindow( puma->m_hWnd, SW_SHOWDEFAULT );
      UpdateWindow( puma->m_hWnd );
		SetFocus(puma->m_hWnd);

		puma->CreateFont(0, "Verdana", 7);
		puma->CreateFont(1, "Verdana", 14);
		puma->CreateFont(2, "Verdana", 10);

		// add first mode here!

		currentGameMode = new RobotMode(0,"ROBOT_MODE");
		gameModeStack.Push(currentGameMode);
		currentGameMode->Activate();


      // Enter the message loop
      MSG msg;
      ZeroMemory( &msg, sizeof(msg) );
      while( msg.message!=WM_QUIT )
      {
         if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
         {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
         }
			else if (currentGameMode)
         {
            if (lastTimeChecked < timeGetTime() - (1000/40))
//            if (lastTimeChecked < timeGetTime() - (1000/130))
            {
               lastTimeChecked = timeGetTime();

					int deviceStatus = MaintainDeviceIntegrity(puma->m_hWnd);
//               if (!flippedOut)
               if (!flippedOut && S_OK == deviceStatus)
               {
						// call Tick() for the top game mode,
                  currentGameMode->Tick();

						// and see what the result is.
						switch (currentGameMode->retState)
						{
							case GMR_POP_ME:
							gameModeStack.Pop();
							currentGameMode->Deactivate();
							delete currentGameMode;
							if (newGameMode)
							{
								gameModeStack.Push(newGameMode);
							}								   
							if (!gameModeStack.Last())
							{
								MessageBox( puma->m_hWnd, "No game mode on stack; expected one!", "Game Failure", MB_OK );
								DestroyWindow( puma->m_hWnd );
							}
							currentGameMode = (GameMode *) gameModeStack.Last();
							if (currentGameMode)
							{
								currentGameMode->Activate();
								currentGameMode->retState = GMR_NORMAL;
							}
							break;

							case GMR_NEW_MODE:
							currentGameMode->Deactivate();
							if (newGameMode)
							{
								gameModeStack.Push(newGameMode);
							}
							else
							{
								 MessageBox( puma->m_hWnd, "No new game mode; expected one!", "Game Failure", MB_OK );
								  DestroyWindow( puma->m_hWnd );
							}
							currentGameMode = (GameMode *) gameModeStack.Last();
							if (currentGameMode)
							{
								currentGameMode->Activate();
								currentGameMode->retState = GMR_NORMAL;
							}
							break;
						}
               }
            }    
         }
		}
	
   }

   // Clean up everything and exit the app
	currentGameMode = (GameMode *) gameModeStack.Last();
	if (currentGameMode)
		currentGameMode->Deactivate();

	while (currentGameMode)
	{
		gameModeStack.Pop();
		delete currentGameMode;
		currentGameMode = (GameMode *) gameModeStack.Last();
	}

	puma->ShutDown();
	delete puma;
//   UnregisterClass( "Puma Main 1.0", wc.hInstance );

	ShowCursor(TRUE);


//   _CrtDumpMemoryLeaks( );

    
   return 0;
}


//*******************************************************************************
void DebugOutput(char *text)
{
	FILE *fp = fopen("debug.txt","a");
	fprintf(fp,text);
	fclose(fp);
}

/* end of file */
