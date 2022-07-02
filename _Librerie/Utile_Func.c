#include "..\Login.h"

char controlloUser[30][10];
char controlloPass[30][10];

void SetOrario()
{
    char szOrario[100] = {0};
    char szData  [50]  = {0};
    time_t data;
    struct tm * timeinfo;
    static int vecchisecondi = -1;
    static int vecchigiorni  = -10;

    time(&data);
    timeinfo = localtime(&data);

    //InvalidateRect(hSfondo,(LPRECT) (NULL), TRUE);
    //InvalidateRect(ghwndApp, (LPRECT) (NULL), TRUE);
    RedrawWindow(ghwndApp, NULL, NULL, RDW_INVALIDATE);

    if(vecchigiorni != timeinfo->tm_mday)
    {
        strftime(szData, 50,"%A, %d  %B", timeinfo);
        SetWindowText(Data, szData);
        vecchigiorni = timeinfo->tm_mday;
    }
    if(vecchisecondi != timeinfo->tm_sec)
    {
        wsprintf(szOrario,"%.2d:%.2d:%.2d\n",timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        SetWindowText(Orario, szOrario);
        vecchisecondi = timeinfo->tm_sec;
    }
}

void ControlloAccount()
{
    char* szInputUser = {0};
    char* szInputPass = {0};

    szInputUser = (char*) malloc(30 * sizeof(char));
    szInputPass = (char*) malloc(30 * sizeof(char));

    if(verPressione == 1)
    {
        GetWindowText(UserName,szInputUser,29);
        GetWindowText(Password,szInputPass,29);
        UseControllo(szInputUser, szInputPass);
    }

    if(verControllo)
    {
        if(!strcmp(szInputUser, "ztanzi") || !strcmp(szInputUser, "zbertoga") || !strcmp(szInputUser, "zsichell"))
            SetWindowText(StCome,"Administrator");
        else
            SetWindowText(StCome,"    User    ");

        ShowWindow(StCome, SW_SHOW);
        ShowWindow(Convalida, SW_SHOW);
    }
    else
    {
        ShowWindow(StCome, SW_HIDE);
        ShowWindow(Convalida, SW_HIDE);
    }

verControllo = 0;
free(szInputUser);
free(szInputPass);
}

void UseControllo(char* szInputUser, char* szInputPass)
{
    int i;

    for(i = 0; i < NUMEROACCOUNT; i++)
        if(!strcmp(controlloUser[i], szInputUser) && !strcmp(controlloPass[i], szInputPass))
        {
            verControllo =  1;
            break;
        }
        else
            verControllo = 0;
}

void Nascondi(int dialog)
{
    if(dialog == 1)
    {
        ShowWindow(hUser, SW_HIDE);
        ShowWindow(hSfondoDiLogin, SW_HIDE);
        ShowWindow(Convalida, SW_HIDE);
        ShowWindow(CercaUser, SW_HIDE);
        ShowWindow(UserName, SW_HIDE);
        ShowWindow(Password, SW_HIDE);
        ShowWindow(StUser, SW_HIDE);
        ShowWindow(StPass, SW_HIDE);
        ShowWindow(StCome, SW_HIDE);

        EnableMenuItem(hHelpMenu, FILE_MENU_ZTANZI,   MF_DISABLED);
        EnableMenuItem(hHelpMenu, FILE_MENU_SBERTOGA1,MF_DISABLED);
        EnableMenuItem(hHelpMenu, FILE_MENU_SSICHELL, MF_DISABLED);

        verControllo = 0;
    }
    else
        EnableWindow(Cerca, 0);
}

void Mostra(int dialog)
{
    if(dialog == 1)
    {
        ShowWindow(hUser, SW_SHOW);
        ShowWindow(UserName, SW_SHOW);
        ShowWindow(Password, SW_SHOW);
        ShowWindow(CercaUser, SW_SHOW);
        ShowWindow(StUser, SW_SHOW);
        ShowWindow(StPass, SW_SHOW);

        EnableMenuItem(hHelpMenu, FILE_MENU_ZTANZI,   MF_ENABLED);
        EnableMenuItem(hHelpMenu, FILE_MENU_SBERTOGA1,MF_ENABLED);
        EnableMenuItem(hHelpMenu, FILE_MENU_SSICHELL, MF_ENABLED);
    }
}

void Font_Imposta(char* pSNome, LOGFONT* plf, int iDimensione)
{
    plf->lfHeight		      =-iDimensione;
    plf->lfWidth		      =0;
    plf->lfEscapement	      =0;
    plf->lfOrientation	      =0;
    plf->lfWeight		      =FW_NORMAL;
    plf->lfItalic		      =0;
    plf->lfUnderline	      =0;
    plf->lfStrikeOut	      =0;
    plf->lfCharSet		      =DEFAULT_CHARSET;
    plf->lfOutPrecision	      =OUT_DEFAULT_PRECIS;
    plf->lfClipPrecision      =CLIP_DEFAULT_PRECIS;
    plf->lfQuality		      =DEFAULT_QUALITY;
    plf->lfPitchAndFamily     =DEFAULT_PITCH;
    strcpy(plf->lfFaceName,pSNome);
}

void SetFont(int dialog)
{
    LOGFONT	lf;
    HFONT ghFont;

    if(dialog == 1)
    {
        Font_Imposta("Arial",&lf,80);
        ghFont = CreateFontIndirect(&lf);
        SetWindowFont(Orario,ghFont,TRUE);

        Font_Imposta("Times New Roman",&lf,40);
        ghFont = CreateFontIndirect(&lf);
        SetWindowFont(Data,ghFont,TRUE);

        Font_Imposta("Arial",&lf,30);
        ghFont = CreateFontIndirect(&lf);
        SetWindowFont(UserName,ghFont,TRUE);
        SetWindowFont(Password,ghFont,TRUE);

        Font_Imposta("Times New Roman",&lf,24);
        ghFont = CreateFontIndirect(&lf);
        SetWindowFont(StUser,ghFont,TRUE);
        SetWindowFont(StPass,ghFont,TRUE);
        SetWindowFont(CercaUser,ghFont,TRUE);
        SetWindowFont(Convalida,ghFont,TRUE);

        Font_Imposta("Times New Roman",&lf,20);
        ghFont = CreateFontIndirect(&lf);
        SetWindowFont(StCome,ghFont,TRUE);
    }
    else
    {
        Font_Imposta("Arial",&lf,13);
        ghFont = CreateFontIndirect(&lf);
        SetWindowFont(StIp,ghFont,TRUE);
        SetWindowFont(StMac,ghFont,TRUE);

        Font_Imposta("Arial",&lf,18);
        ghFont = CreateFontIndirect(&lf);
        SetWindowFont(IpAddress,ghFont,TRUE);
        SetWindowFont(MacAddress,ghFont,TRUE);

        Font_Imposta("Arial",&lf,30);
        ghFont = CreateFontIndirect(&lf);
        SetWindowFont(Cerca,ghFont,TRUE);
    }
}

void ControlloAddress()
{
    char* szInputIP = {0};
    char* szInputMAC = {0};

    szInputIP  = (char*) malloc(30 * sizeof(char));
    szInputMAC = (char*) malloc(30 * sizeof(char));

    GetWindowText(IpAddress ,szInputIP ,29);
    GetWindowText(MacAddress,szInputMAC,29);

    if(validateIP(szInputIP) && validateMAC(szInputMAC))
        EnableWindow(Cerca, 1);

    else
        EnableWindow(Cerca, 0);

free(szInputIP);
free(szInputMAC);
}

int validateIP(const char* s)
{
    char coda[16];
    int lunghezza = strlen(s);
    unsigned int partiIP[4];
    int ip;
    int i;

    if (lunghezza < 7 || lunghezza > 15)
        return 0;

    coda[0] = 0;

    ip = sscanf(s, "%3u.%3u.%3u.%3u%s", &partiIP[0], &partiIP[1], &partiIP[2], &partiIP[3], coda);

    if (ip != 4 || coda[0])
        return 0;

    for (i = 0; i < 4; i++)
        if (partiIP[i] > 255)
            return 0;

return 1;
}

int validateMAC(const char *s)
{
    int i;

    for(i = 0; i < 17; i++)
    {
        if(i % 3 != 2 && !isxdigit(s[i])) ///caratteri
            return 0;

        if(i % 3 == 2 && s[i] != ':')     ///i due punti che dividono l'indirizzo
            return 0;
    }

    if(s[17] != '\0')                     ///terminatore al 17 carattere
        return 0;

return 1;
}

/**
*Nascondo il prompt
*/
void Stealth(int nascosto)
{
    //ShowWindow (GetConsoleWindow(), SW_HIDE);
    if(nascosto == 1)
        ShowWindow(FindWindowA("ConsoleWindowClass", NULL), SW_HIDE);

    else
    {
        ShowWindow(FindWindowA("ConsoleWindowClass", NULL), SW_SHOW);
        //EndDialog (FindWindowA("ConsoleWindowClass", NULL), 0);
        //DestroyWindow(FindWindowA("ConsoleWindowClass",NULL));
    }
}

int LeggiAccount()
{
    FILE *in;
    int i = 0;

    ///Database degli account registarti
    if((in = fopen("_Librerie\\Account.txt", "r")) == NULL)
    {
        fprintf(stderr, "Impossibile aprire il file di input.\n");
    return 0;
    }

    while(!feof(in))
    {
        fscanf(in, "%s", controlloUser[i]);
        fscanf(in, "%s", controlloPass[i]);
    i++;
    }
fclose(in);
return i;//numero account
}

