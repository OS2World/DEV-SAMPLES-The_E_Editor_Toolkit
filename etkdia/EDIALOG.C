/*
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
� What's it called: EDIALOG.C
�
� What does it do : Sample program that demonstrates how to imbed an E-MLE
�                   into a dialog box.
�
� .DLL functions  : EtkRegister
�                   EtkCreate
�
�
� Who and When    : Gennaro (Jerry) Cuomo                          2 -89
�
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
*/

/*
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
� Included Header Files:                                             GC 9-88 �
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/
#define INCL_WIN         // winthorn definitions (WIN function and WM_ msgs)
#define INCL_DOS         // Dosxxx functions
#define INCL_DEV         // Devxxx functions
#include <os2.h>         // start of the winthorn include chain
#include <stdio.h>       // C library functions...
#include <malloc.h>      // C library functions...
#include "edialog.h"     // Constants.
#include <edll.h>        // editor's custom message definitions

/*
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
� The following are Global   variables.                              GC 9-88 �
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/
HWND       hwndQ1;                // E-MLE 1
HWND       hwndQ2;                // E-MLE 2

/*
敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
�                                                                            �
� What's it called:  SampleDlgProc                                           �
�                                                                            �
� What does it do :  Drives a dialog box that contains 3 multi-line edit     �
�                    controls from the E toolkit.                            �
�                                                                            �
� Who and when    :  Gennaro A. Cuomo                               10-88    �
�                                                                            �
青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
*/
VOID FormatDialog( HWND hDlg )
{
  HWND  hStatRect1, hStatRect2;

  // Get the window handle of the 2 STATIC rectangle controls
  hStatRect1   = WinWindowFromID( hDlg, IDD_RECT1);
  hStatRect2   = WinWindowFromID( hDlg, IDD_RECT2);

  if (hStatRect1 && hStatRect2) {
     SWP  swpr1, swpr2;
     HWND hMLE1, hMLE2;
     hMLE1=WinQueryWindow( hwndQ1, QW_PARENT, FALSE );
     hMLE2=WinQueryWindow( hwndQ2, QW_PARENT, FALSE );
     // Make the E-MLE Frames children of the Dialog box
     WinSetParent(hMLE1,hDlg, FALSE);
     WinSetParent(hMLE2,hDlg, FALSE);

     // Get the position of the 2 STATIC rectangle controls
     WinQueryWindowPos( hStatRect1, &swpr1 );
     WinQueryWindowPos( hStatRect2, &swpr2 );

     // Move the 2 E-MLE's on top of the STATIC rectangle controls
     WinSetWindowPos(hMLE1, swpr1.hwndInsertBehind, (SHORT)swpr1.x ,(SHORT)swpr1.y ,(SHORT)swpr1.cx, (SHORT)swpr1.cy ,SWP_MOVE | SWP_SIZE | SWP_ACTIVATE | SWP_ZORDER | SWP_NOADJUST | SWP_SHOW);
     WinSetWindowPos(hMLE2, swpr2.hwndInsertBehind, (SHORT)swpr2.x ,(SHORT)swpr2.y ,(SHORT)swpr2.cx, (SHORT)swpr2.cy ,SWP_MOVE | SWP_SIZE | SWP_ACTIVATE | SWP_ZORDER | SWP_NOADJUST | SWP_SHOW);

  } /* endif*/
}

MRESULT EXPENTRY SampDlgProc ( HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2 )
{

  switch ( msg )  {
  /*
  敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
  �Initialize dialog box by positioning the edit windows in  �
  �the dialog box and re-assigning ownership of the edit     �
  �window to the dialog box.  This will make it easier to    �
  �control the edit windows from the dialog proc.            �
  青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
  */
  case WM_FORMATFRAME:
  case WM_SIZE:
  case WM_INITDLG:
    {  MRESULT rc;
       rc=WinDefDlgProc( hDlg, msg, mp1, mp2);
       FormatDialog( hDlg );
       return(rc);
    }
    break;

  case WM_COMMAND:
    if ( LOUSHORT( mp1 )==DID_OK || LOUSHORT( mp1 )==DID_CANCEL )  {
       HWND   hMLE1, hMLE2;
       /* Get frame handles of the edit windows */
       hMLE1 = WinQueryWindow( hwndQ1, QW_PARENT, FALSE );
       hMLE2 = WinQueryWindow( hwndQ2, QW_PARENT, FALSE );

       /* make them children of the desktop, because we are about to  */
       /* distroy the dialog box */
       WinSetParent(hMLE1, HWND_DESKTOP, FALSE);
       WinSetParent(hMLE2, HWND_DESKTOP, FALSE);

       if (LOUSHORT( mp1 )==DID_OK) {
          /* save data in the E-MLE windows */
          WinSendMsg( hwndQ1, EPM_EDIT_COMMAND, (PSZ)"SAVE", 0L );
          WinSendMsg( hwndQ2, EPM_EDIT_COMMAND, (PSZ)"SAVE", 0L );
       } /* endif */

       /* hide the MLE windows */
       WinShowWindow( hMLE1, FALSE );
       WinShowWindow( hMLE2, FALSE );

       /* distroy the dialog */
       WinShowWindow( hDlg, FALSE );
       WinDismissDlg( hDlg,TRUE);
    }
    break;

  default:
      return( (MRESULT)WinDefDlgProc( hDlg, msg, mp1, mp2 ) );
  }
  return( 0L );
}
/*
敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
�                                                                            �
� What's it called: TestWndProc()                                            �
�                                                                            �
� What does it do :                                                          �
�                                                                            �
�                                                                            �
�                                                                            �
� Who and when    : Gennaro (Jerry) Cuomo   9-88                             �
�                                                                            �
青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
*/
MRESULT FAR PASCAL TestWndProc( HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2 )
{
    switch (msg)   {
    /*
    敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
    �  This message is received when CLOSE is selected on the system       �
    �  menu of the Test Edit Application window.  When this is received,   �
    �  Send a destroy message to the Edit Windows.                         �
    青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
    */
    case WM_CLOSE:
       WinSendMsg( hwndQ1, WM_DESTROY, 0L, 0L );
       WinSendMsg( hwndQ2, WM_DESTROY, 0L, 0L );

       WinPostMsg( hwnd,              /* Edit Window was destroyed... */
                   WM_QUIT,           /* Now, quit application by     */
                   0L,                /* posting a quit message...    */
                   0L
                 );
       break;

    /*
    敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
    �  Application window has become invalid...                            �
    �  or window has changed size...                                       �
    青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
    */
    case WM_PAINT:
    case WM_SIZE:
       {
         HPS    hPS;      /* local handle to a cashed micro PS */
         hPS = WinBeginPaint( hwnd, (HPS)NULL, (PWRECT)NULL );
             GpiErase( hPS );
         WinEndPaint( hPS );
       }
       break;
    case WM_COMMAND:
       if (SHORT1FROMMP(mp1)==IDD_CMD) {
         /* display dialog box */
         WinDlgBox(HWND_DESKTOP, hwnd, (PFNWP)SampDlgProc, NULL, DLG_SAMP, (PCH)NULL);
       }
       break;

    default:
        return( WinDefWindowProc( hwnd, msg, mp1, mp2 ) );
        break;
    }
    return(0L);
}

//+------------------------------------------------------------------------------+
//|                                                                              |
//|  What's it called: CreateEditWindow                                          |
//|                                                                              |
//|  What does it do : Create an E-MLE window using the ETKExxx.DLL function     |
//|                    EtkCreate.    Note that key events are defined            |
//|                    by the ESIMPLE.EX  macro file. (See ESIMPLE.EX for deta   |
//|                                                                              |
//|  Who and when    : Gennaro (Jerry) Cuomo   9-88                              |
//|                                                                              |
//+------------------------------------------------------------------------------+
HWND CreateEditWindow( HAB hAB, HWND hwnd, PSZ Fname )
{
   #define MY_E_MLE  100         // Application ID - Used by ETK to distinguish E-MLE window
   EDITORINFO epm;               // Editor Application Information Struct
   SWP   swp;                    // E-MLE position
   HWND  hwndEdit;               // E-MLE (client) handle

   // allow for Line/Column at the bottom of application window
   WinQueryWindowPos(hwnd, &swp);
   swp.cy -=30; swp.y +=20;

   // fill in the editor information structure
   epm.hab         = hAB;                   // application anchor block
   epm.hwndparent  = HWND_DESKTOP;          // handle to parent of edit window
   epm.hwndowner   = hwnd;                  // handle to owner of edit window
   epm.pswp        = &swp;                  // positioning of edit window
   epm.filename    = (PSZ)Fname;            // file to be edited (with wildcard)
   epm.hEditorIcon = NULL;                  // E-MLE minimize ICON.
   epm.hEditPtr    =                        // handle to editor pointer icon.
   epm.hMarkPtr    =                        // handle to mark pointer icon.
                     WinQuerySysPointer( HWND_DESKTOP, SPTR_TEXT, FALSE);
   // internal editor options
   epm.editorstyle = EDIT_STYLE_ACTIVATEFOCUS | EDIT_STYLE_DISABLEOWNERAFFECTS |
                     EDIT_STYLE_CURSORON;
   // PM standard window styles (FCF_xxxx)
   epm.pmstyle     = (ULONG)NULL;

   epm.exfile      = (PSZ)"EDIALOG.EX";     // Pre-compiled macro code file.
   epm.topmkr      =                        // top and bottom file indicator
   epm.botmkr      = (PSZ)"";
   epm.editid      = MY_E_MLE;
   epm.exe_path     =                       // Origin directory
   epm.exsearchpath = "";                   // Environment variable name whose path contains .ex files

   /*----------  Create E-MLE Window -----------*/
   EtkCreate( (EDITORINFO far *)&epm, (PHWND)&hwndEdit );

   return( (HWND)hwndEdit );
}

/*
敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
�                                                                            �
� What's it called: main()                                                   �
�                                                                            �
� What does it do : creates a application window and creates a child edit    �
�                   window that contains file(s) specified on the system     �
�                   command line.                                            �
�                                                                            �
� Who and when    : Gennaro (Jerry) Cuomo   9-88                             �
�                                                                            �
青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
*/
void main( )
{
    HAB   hab;
    HMQ   hmq;
    QMSG  qmsg;                             /* queue message structure      */
    ULONG pmstyle;                          /* application window style     */
    RECTL rect;                             /* rectangle structure for pos. */
    HWND  hwndAppClient, hwndAppFrame;

    hab = WinInitialize(NULL);              /* Initialize app as a PM app   */

    hmq = WinCreateMsgQueue(hab, 0x100);    /* Create Queue                 */

    WinRegisterClass( hab,                  /* Register Application window  */
                      (PSZ)"TEST",          /*...class name                 */
                      (PFNWP)TestWndProc,   /*...application window proc    */
                      CS_SIZEREDRAW,        /*...window class style         */
                      0                     /*...no window data             */
                    );
                                            /* window style of application  */
    pmstyle = FCF_SIZEBORDER |              /*...size border                */
              FCF_TITLEBAR   |              /*...title bar, minimize-       */
              FCF_MINMAX     |              /*...maximize, system menu.     */
              FCF_SYSMENU    |
              FCF_MENU;

    hwndAppFrame =WinCreateStdWindow(       /* Create application window    */
                     HWND_DESKTOP,          /*...parent is the desk top wnd */
                     WS_VISIBLE,
                     &pmstyle,              /*...window style flags         */
                     (PSZ)"TEST",           /*...window class name          */
                     (PSZ)"Sample of an E-MLE in a Dialog Box",
                     0L,                    /*...                           */
                     (HMODULE)NULL,         /*...                           */
                     EDIALOG_RC,            /*...                           */
                     (PHWND)&hwndAppClient  /*...(return) client wnd handle */
                     );

    rect.xLeft   =  10;                     /* Position Application Window  */
    rect.yBottom =  10;
    rect.xRight  =  500;
    rect.yTop    =  400;

    WinSetWindowPos ((HWND)hwndAppFrame,   /* Set position of app window  */
                     (HWND)HWND_TOP,
                     (SHORT)rect.xLeft,
                     (SHORT)rect.yBottom,
                     (SHORT)rect.xRight,
                     (SHORT)rect.yTop,
                     SWP_MOVE | SWP_SIZE | SWP_SHOW);

   /*----------  Register Edit Window -------------*/
   EtkRegister( hab, CS_SIZEREDRAW );

   /*----------  Create Two Edit Windows   -------------*/
   hwndQ1=CreateEditWindow( hab, hwndAppClient, "QUEST1.DOC");
   hwndQ2=CreateEditWindow( hab, hwndAppClient, "QUEST2.DOC");

   /* dispatch messages to Test Application */
   while( WinGetMsg( hab, (PQMSG)&qmsg, (HWND)NULL, 0, 0 ) ) {
       WinDispatchMsg( hab, (PQMSG)&qmsg );
   }

   /* Close up shop  */

   WinDestroyWindow( hwndAppFrame );
   WinDestroyMsgQueue( hmq );
   WinTerminate( hab );
}
