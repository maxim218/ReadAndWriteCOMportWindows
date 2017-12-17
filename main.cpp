#include <math.h>
#include <string.h>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

void workWithString(const char * s)
{
	cout << s << "\n";
	cout << strlen(s) << "\n\n";
}

void getValueFromCom()
{
	// init name of comPort
	LPCTSTR sPortName = "COM3";
	
	// init properties of comPort
	HANDLE hSerial = ::CreateFile(sPortName,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	dcbSerialParams.BaudRate=CBR_9600;
	dcbSerialParams.ByteSize=8;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	
	// variables for getting result
	DWORD iSize;
	char ans[500];
	strcpy(ans,"");
	int count = 0;
	char sReceivedChar;
	
	char data[] = "X";
	DWORD dwSize = sizeof(data);
	DWORD dwBytesWritten; 
	bool iRet = WriteFile (hSerial, data, dwSize, &dwBytesWritten, NULL);
	
	while (true)
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0); 
	
	    // if we got something
		if (iSize > 0)
		{
			// if char is not the end of string
			if(sReceivedChar != '\n')
			{
				// add char to string ans
				ans[count] = sReceivedChar;
				ans[count+1] = '\0';
				count++;
			}
			else  // if we got the end of string from comPort
			{
				workWithString(ans);
				
				char data[] = "X";
				DWORD dwSize = sizeof(data);
				DWORD dwBytesWritten; 
				bool iRet = WriteFile (hSerial, data, dwSize, &dwBytesWritten, NULL);
				
				// reset string "ans"
				count = 0;
				strcpy(ans,"");
			}
		}	
	}	
}

int main(int argc, char** argv) 
{
	while(true)
	{
		getValueFromCom();
		Sleep(100);
	}
		
	return 0;
}
