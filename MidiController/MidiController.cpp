// MidiController.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")


void CALLBACK cbMidiInProc(
	HMIDIIN   hMidiIn,
	UINT      wMsg,
	DWORD_PTR dwInstance,
	DWORD_PTR dwParam1,
	DWORD_PTR dwParam2
) {
	switch (wMsg) {
	case MM_MIM_OPEN:
		printf("Device opened\r\n");
		break;

	case MM_MIM_CLOSE:
		printf("Device closed\r\n");
		break;

	case MIM_DATA:	
	{
		DWORD dwTimestamp = dwParam2; //milliseconds since midiInStart was called.
		DWORD hiWord = HIWORD(dwParam1);
		DWORD loWord = LOWORD(dwParam1);
		BYTE hiwhib = HIBYTE(hiWord); // not used
		BYTE hiwlob = LOBYTE(hiWord); // amp (0 - 127)
		BYTE lowhib = HIBYTE(loWord); // key index
		BYTE lowlob = LOBYTE(loWord); // ??
		printf("MM_MIM_DATA: %ld %03d %03d %03d\r\n", dwTimestamp, hiwlob, lowhib, lowlob);
	}
	break;

	case MM_MIM_LONGDATA:
		printf("MM_MIM_LONGDATA");
		break;

	case MM_MIM_MOREDATA:
		printf("MM_MIM_MOREDATA");
		break;

	default:
		break;
	}
}


int main()
{

	UINT mic = midiInGetNumDevs();
	wprintf(L"MIDI In devices:\r\n");
	for (UINT i = 0; i < mic; i++) {
		MIDIINCAPS micaps = { 0 };
		midiInGetDevCaps(i, &micaps, sizeof(MIDIINCAPS));
		wprintf(L"%d) %s\r\n", i, micaps.szPname);
	}

	wprintf(L"\r\n"); 

	UINT moc = midiOutGetNumDevs();
	wprintf(L"MIDI Out devices:\r\n");
	for (UINT i = 0; i < moc; i++) {
		MIDIOUTCAPS mocaps = { 0 };
		midiOutGetDevCaps(i, &mocaps, sizeof(MIDIOUTCAPS));
		wprintf(L"%d) %s\r\n", i, mocaps.szPname);
	}
	
	wprintf(L"Press any key to continue...\r\n");

	_getch();

	HMIDIIN hMidiIn = NULL;
	midiInOpen(&hMidiIn, 0, (DWORD_PTR)cbMidiInProc, NULL, CALLBACK_FUNCTION| MIDI_IO_STATUS);
	if (hMidiIn) {
		midiInStart(hMidiIn);
		while (1) {
			if (::GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				break;
			}
			Sleep(100);
		}
		midiInStop(hMidiIn);
		midiInClose(hMidiIn);
	}
	
    return 0;
}

