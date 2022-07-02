#include "..\Login.h"

BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hDlg, WM_INITDIALOG, Dlg_OnInitDialog);
        HANDLE_MSG(hDlg, WM_COMMAND, Dlg_OnCommand);
        HANDLE_MSG(hDlg, WM_TIMER, Dlg_OnTimer);
        HANDLE_MSG(hDlg, WM_CLOSE, Dlg_OnClose);

        case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC) wParam;
            SetBkMode(hdcStatic, TRANSPARENT);
            SetBkColor(hdcStatic, TRANSPARENT);

            if(verPressione == 0)///Colore bianco sul primo sfondo
            {
                SetTextColor(hdcStatic, RGB(255,255,255));
                SetBkColor(hdcStatic, RGB(255,255,255));
            }
            else///Resetto a nero le static
            {
                SetTextColor(hdcStatic, RGB(0,0,0));
                SetBkColor(hdcStatic, RGB(0,0,0));
            }
        return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
        }
        break;

        default:
        break;
    }
return FALSE;
}

BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    ///Nascondo il prompt
    Stealth(1);

    ///Leggo gli account dal file
    NUMEROACCOUNT = LeggiAccount();

    ///DIALOG MAIN
    ghwndApp = hwnd;

    ///IMMAGINI
    hSfondo = GetDlgItem(hwnd,IDC_IMAGEBACKGROUND);
    hUser = GetDlgItem(hwnd,IDC_IMAGEPROFILE);
    hSfondoDiLogin = GetDlgItem(hwnd,IDC_SFONDODILOGIN);

    ///BUTTON
    CercaUser = GetDlgItem(hwnd,IDC_SEARCHACCOUNT);
    Convalida = GetDlgItem(hwnd,IDC_CONVALIDA);

    ///TEXT
    UserName = GetDlgItem(hwnd,IDC_USER);
    Password = GetDlgItem(hwnd,IDC_PASSWORD);

    ///STATIC IMPOSTAZIONI
    StUser = GetDlgItem(hwnd,IDC_STATICUSER);
    StPass = GetDlgItem(hwnd,IDC_STATICPASS);
    StCome = GetDlgItem(hwnd,IDC_STATICCOME);

    ///STATIC DATA & ORARIO
    Orario = GetDlgItem(hwnd,IDC_ORARIO);
    Data = GetDlgItem(hwnd,IDC_DATA);

    ///Immagine sul bottone di convalida
    hFreccia = LoadBitmap(ghinstApp,MAKEINTRESOURCE(IDB_BITMAP4));
    SendDlgItemMessage(hwnd, IDC_CONVALIDA , BM_SETIMAGE, (WPARAM)IMAGE_BITMAP , (LPARAM)(HANDLE)hFreccia);

    AddMenu(hwnd);

    SetFont(1);

    ///Nascondo cio che nella prima schermata è inutile come surname e password...
    Nascondi(1);

    ///Timer per il controllo dell'orario
    TempoTimer = SetTimer(hwnd,2,1, NULL);
return TRUE;
}

void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
        ///Casi che si posso avverare nel menu dropdown
        case FILE_MENU_ZTANZI:
            MessageBeep(MB_OK);
            SetWindowText(UserName, "ztanzi");
            SetWindowText(Password, "1234");
            ControlloAccount();
            break;
        case FILE_MENU_SBERTOGA1:
            MessageBeep(MB_ICONINFORMATION);
            SetWindowText(UserName, "zbertoga");
            SetWindowText(Password, "pippo");
            ControlloAccount();
            break;
        case FILE_MENU_SSICHELL:
            MessageBeep(MB_ICONINFORMATION);
            SetWindowText(UserName, "zsichell");
            SetWindowText(Password, "pluto");
            ControlloAccount();
            break;

        case FILE_MENU_LOGIN:
            verPressione = 1;
            TempoSfondo = SetTimer(hwnd,1,4, NULL);
            SetWindowText(UserName, "");
            SetWindowText(Password, "");
            ShowWindow(hSfondoDiLogin, SW_HIDE);
            break;

        case FILE_MENU_SEARCH:
            DialogBox(ghinstApp1, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Dlg_Proc1);
            break;

        ///Se si clicca sull'immagine l'immagine sale e ricompaione le cose...
        case IDC_IMAGEBACKGROUND:
            verPressione = 1;
            TempoSfondo = SetTimer(hwnd,1,4, NULL);
            break;

        ///Button OK che conferma l'accesso...
        case IDC_CONVALIDA:
            KillTimer(hwnd,2);
            verPressione = 0;
            Sleep(1000);
            Nascondi(1);
            ShowWindow(hSfondoDiLogin, SW_SHOW);
            break;

        ///Button che apre la seconda dialog dove ci sono IP e MAC
        case IDC_SEARCHACCOUNT:
            DialogBox(ghinstApp1, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Dlg_Proc1);
            break;

        ///Inserimento credenziali e controlli
        case IDC_USER:
            ControlloAccount();
            break;

        case IDC_PASSWORD:
            ControlloAccount();
            break;
    }
}

void Dlg_OnTimer(HWND hwnd, UINT id)
{
    static int spostamento = 0;

    if(id == 1)
    {
        if(spostamento > -641)
        {
            KillTimer(hwnd,id);
            spostamento -= 10;
            ShowWindow(Orario, SW_HIDE);
            ShowWindow(Data, SW_HIDE);

            //InvalidateRect(hSfondo,(LPRECT) (NULL), TRUE);
            //InvalidateRect(ghwndApp, (LPRECT) (NULL), TRUE);
            SetWindowPos(hSfondo,HWND_BOTTOM,0,spostamento,0,0,SWP_NOSIZE);

            ShowWindow(CercaUser, SW_SHOW);

            SetTimer(hwnd,1,TempoSfondo, NULL);
        }
        else
        {
            verPressione = 1;
            KillTimer(hwnd,id);
            Mostra(1);
        }
    }
    if(id == 2)
    {
        KillTimer(hwnd,id);
        if(!verPressione)
        {
            SetOrario();
            SetTimer(hwnd,id,1000, NULL);
        }
        verPressione = 0;
    }
}

void AddMenu(HWND hWnd)
{
    HMENU hMenu = CreateMenu();

    HMENU hBack = CreateMenu();

    hHelpMenu = CreateMenu();
    HMENU hPsdwZtanzi = CreateMenu();
    HMENU hPsdwZberto = CreateMenu();
    HMENU hPsdwZsicca = CreateMenu();

    AppendMenu(hBack, MF_STRING, FILE_MENU_LOGIN, "Login");
    AppendMenu(hBack, MF_SEPARATOR, (UINT_PTR)NULL, NULL);
    AppendMenu(hBack, MF_STRING, FILE_MENU_SEARCH, "Search");

    AppendMenu(hPsdwZtanzi, MF_STRING, FILE_MENU_ZTANZI, "1234");
    AppendMenu(hPsdwZberto, MF_STRING, FILE_MENU_SBERTOGA1, "pippo");
    AppendMenu(hPsdwZsicca, MF_STRING, FILE_MENU_SSICHELL, "pluto");

    AppendMenu(hHelpMenu, MF_POPUP, (UINT_PTR)hPsdwZtanzi, "Ztanzi");
    AppendMenu(hHelpMenu, MF_SEPARATOR, (UINT_PTR)NULL, NULL);
    AppendMenu(hHelpMenu, MF_POPUP, (UINT_PTR)hPsdwZberto, "Zbertoga");
    AppendMenu(hHelpMenu, MF_SEPARATOR, (UINT_PTR)NULL, NULL);
    AppendMenu(hHelpMenu, MF_POPUP, (UINT_PTR)hPsdwZsicca, "Zsichell");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hBack, "NEW");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

    SetMenu(hWnd, hMenu);
}

void Dlg_OnClose(HWND hwnd)
{
    //if (MessageBox(hwnd, "Vuoi uscire?", "Sicuro?", MB_OKCANCEL) == IDOK)

    Stealth(0);
    EndDialog(hwnd,0);
}
