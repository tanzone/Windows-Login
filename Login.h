#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "resource.h"

#define FILE_MENU_ZTANZI    (1)
#define FILE_MENU_SBERTOGA1 (2)
#define FILE_MENU_SSICHELL  (3)
#define FILE_MENU_LOGIN     (4)
#define FILE_MENU_SEARCH    (5)


HINSTANCE ghinstApp;
HINSTANCE ghinstApp1;
HWND ghwndApp;
HWND ghwndApp1;

HWND hSfondo;
HWND hUser;
HWND hFreccia;
HWND hSfondoDiLogin;

HWND CercaUser;
HWND Convalida;

HWND UserName;
HWND Password;

HWND StUser;
HWND StPass;
HWND StCome;

HWND Orario;
HWND Data;

HWND StIp;
HWND StMac;
HWND IpAddress;
HWND MacAddress;
HWND Cerca;

HMENU hHelpMenu;

UINT TempoSfondo;
UINT TempoTimer;

int verPressione;
int verControllo;
int NUMEROACCOUNT;

///Prototipi dialogMain
extern BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
extern void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
extern void Dlg_OnClose(HWND hwnd);
extern void Dlg_OnTimer(HWND hwnd, UINT id);
extern void AddMenu(HWND hWnd);  ///MENU DROPDOWN

///Prototipi dialog1
extern BOOL CALLBACK Dlg_Proc1(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL Dlg_OnInitDialog1(HWND hwnd, HWND hwndFocus, LPARAM lParam);
extern void Dlg_OnCommand1(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
extern void Dlg_OnClose1(HWND hwnd);

///Funzioni utili
extern void ControlloAccount();
extern void UseControllo(char* szInputUser, char* szInputPass);
extern void SetOrario();
extern void Nascondi(int dialog);
extern void Mostra(int dialog);
extern void SetFont(int dialog);
extern void ControlloAddress();
extern int validateIP(const char* s);
extern int validateMAC(const char *s);
extern void Stealth(int nascosto);
extern int LeggiAccount();

#endif // LOGIN_H_INCLUDED
