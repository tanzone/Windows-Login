#include "..\Login.h"

BOOL CALLBACK Dlg_Proc1 (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, Dlg_OnInitDialog1);
        HANDLE_MSG(hDlg, WM_COMMAND, Dlg_OnCommand1);
        HANDLE_MSG(hDlg, WM_CLOSE, Dlg_OnClose1);

        default: break;
    }
return FALSE;
}

BOOL Dlg_OnInitDialog1(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    ///DIALOG Sec
    ghwndApp1 = hwnd;

    ///BUTTON
    Cerca = GetDlgItem(hwnd,IDC_CERCA);

    ///STATIC
    StIp  = GetDlgItem(hwnd,IDC_IPSTATIC);
    StMac = GetDlgItem(hwnd,IDC_MACSTATIC);

    ///INPUT
    IpAddress = GetDlgItem(hwnd,IDC_IPADDRESS);
    MacAddress = GetDlgItem(hwnd,IDC_MACADDRESS);

    SetFont(2);

    Nascondi(2);

    EnableWindow(ghwndApp, FALSE);

return TRUE;
}

void Dlg_OnCommand1(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
        case IDC_IPADDRESS:
            ControlloAddress();
            break;

        case IDC_MACADDRESS:
            ControlloAddress();
            break;

        case IDC_CERCA:
            MessageBox(NULL,"Search it...","CONNESSIONE",MB_ICONINFORMATION);
            break;
    }
}

void Dlg_OnClose1(HWND hwnd)
{
    EnableWindow(ghwndApp, 1);
    DestroyWindow(hwnd);
    //EndDialog(hwnd,0);
}
