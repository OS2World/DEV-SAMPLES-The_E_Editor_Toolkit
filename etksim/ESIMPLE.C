//+------------------------------------------------------------------------------+
//|  What's it called: ESIMPLE.C
//|
//|  What does it do : Creates a simple E-MultiLine Edit Control Window.
//|                    The edit window uses SIMPLE.EX as its E-MLE profile (See ESIMPLE.E
//|
//|  .DLL functions  : EtkRegister
//|                    EtkCreate
//|                    EtkWndProc
//|                    EtkDestroy
//|
//|  Who and When    : Gennaro (Jerry) Cuomo                          9 -88
//|
//+------------------------------------------------------------------------------+

/*
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
� Included Header Files:                                             GC 9-88 �
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/
#define INCL_WIN         // winthorn definitions (WIN function and WM_ msgs)
#define INCL_DOS         // Dosxxx functions
#define INCL_GPI         // graphic functions
#include <os2.h>         // start of the winthorn include chain
#include <stdio.h>       // C library functions...
#include <stdlib.h>      // C library functions...
#include <string.h>      // C library functions...
#include <malloc.h>      // C library functions...
#include <edll.h>        // includes bindings to ETKExxx.DLL ETKRxxx.DLL

//+------------------------------------------------------------------------------+
//|                                                                              |
//|  What's it called: CreateEditWindow                                          |
//|                                                                              |
//|  What does it do : Create an E-MLE window using the ETKExxx.DLL function     |
//|                    EtkCreate.               Note that key events are defined |
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
   epm.hwndparent  =                        // handle to parent of edit window
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
   epm.pmstyle     = FCF_TITLEBAR | FCF_SIZEBORDER | FCF_VERTSCROLL;

   epm.exfile      = (PSZ)"ESIMPLE.EX";     // Pre-compiled macro code file.
   epm.topmkr      =                        // top and bottom file indicator
   epm.botmkr      = (PSZ)" ��������������������������������������������";
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
� What's it called: TestWndProc()                                            �
�                                                                            �
� What does it do : Handles messages sent to test application window.        �
�                   If a EPM_EDIT_CURSORMOVE message is received, display    �
�                   The current Line and column of the cursor.               �
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
   �  menu of the Test Edit Application window.                           �
   青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
   */
   case WM_CLOSE:
      WinPostMsg(hwnd,WM_QUIT,0L,0L);
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
         HPS    hPS;                    /* local handle to a cashed micro PS */
         hPS = WinBeginPaint( hwnd, (HPS)NULL, (PWRECT)NULL );
             GpiErase( hPS );
         WinEndPaint( hPS );
       }
       break;


  /*
  敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
  � This message notifies your app that an edit window has   �
  � been closed.                                             �
  青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
  */
   case EPM_EDIT_DESTROYNOTIFY:
      WinAlarm( HWND_DESKTOP, WA_NOTE);
      break;

  /*
  敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
  � Am E-MLE has become active.  Record the important        �
  � window information.   All command will be sent to this   �
  � edit window.                                             �
  �     mp1 = Edit Window Handle   (HWND)                    �
  �     mp2 = Active File Name     (PSZ)                     �
  青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
  */
  case EPM_EDIT_ACTIVEHWND:
     WinSetActiveWindow(HWND_DESKTOP,(HWND)mp1 );
     break;

  /*
  敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
  � The edit window has send a return code.                                �
  � This message is in response to the last EPM_EDIT_COMMAND               �
  � message issued by the active edit window.                              �
  �     mp1 = message string   (PSZ)                                       �
  �     mp2 = message number   (USHORT)                                    �
  青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
  */
  case EPM_EDIT_RETCODE:
     WinMessageBox ((HWND)HWND_DESKTOP,   /* Display editor return code   */
                    (HWND)hwnd,
                    (PSZ)mp1,
                    (PSZ)"E-MLE: Command Return Code",
                    NULL,
                    MB_ICONEXCLAMATION
                   );
     break;

    /*
    敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
    � This message is sent by the edit window to the owner.                  �
    � We process this message by displaying the current editor cursor pos.   �
    �     mp1 = line number      (ULONG)                                     �
    �     mp2 = column  number   (ULONG)                                     �
    青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
    */
    case EPM_EDIT_CURSORMOVE:
      {
        POINTL pt;
        HPS    hps;
        CHAR   text[80];
        USHORT l;
        RECTL  rc;

        hps = WinGetPS(hwnd);

        WinQueryWindowRect ( hwnd, (PRECTL)&rc );
        rc.yTop =  rc.yBottom + 20;
        WinFillRect(hps, &rc, CLR_RED );

        pt.x = 5L; pt.y = 3L;             /* Set the text coordinates,    */
        GpiSetColor( hps, CLR_WHITE );    /* Set color of the text        */

        l = sprintf(text,"Line = %lu ",(ULONG)mp1);
        GpiCharStringAt( hps, &pt, (ULONG)l, (PSZ)text); /* Draw Text       */

        pt.x = 82L;
        l = sprintf(text,"Column = %lu ",(ULONG)mp2);
        GpiCharStringAt( hps, &pt, (ULONG)l, (PSZ)text );

        WinReleasePS(hps);
      }
      break;
    default:
        return( WinDefWindowProc( hwnd, msg, mp1, mp2 ) );
        break;
    }
    return(0L);
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
void main(int argc, char **argv)
{
    QMSG    qmsg;                           // queue message structure
    ULONG   pmstyle;                        // application window style
    HMQ     hmq;                            // Queue Handle
    HAB     hab;                            // Anchor Block
    RECTL   rect;                           // rectangle structure for pos.
    CHAR    Fname[128];                     // Input file came
    HWND    hwndAppClient,hwndAppFrame;     // main application window hdn
    PSZ     class;                          // edit window class name
    UCHAR   EMLE_ClassName[128];            // edit window class name
    HWND    hwndEdit;                       // handle to E-MLE

    hab = WinInitialize(NULL);              // Initialize app as a PM app

    hmq = WinCreateMsgQueue(hab, 0x100);    // Create Queue

    WinRegisterClass( hab,                  // Register Application window
                      (PSZ)"TEST",          //...class name
                      (PFNWP)TestWndProc,   //...application window proc
                      CS_SIZEREDRAW,        //...window class style
                      4                     //...make room for instance data
                    );
                                            // window style of application
    pmstyle = FCF_SIZEBORDER |              //...size border
              FCF_TITLEBAR   |              //...title bar, minimize-
              FCF_MINMAX     | FCF_SYSMENU; //...maximize, system menu.

    hwndAppFrame =WinCreateStdWindow(       // Create application window
                     HWND_DESKTOP,          //...parent is the desk top wnd
                     WS_VISIBLE,            //...
                     &pmstyle,              //...window style flags
                     (PSZ)"TEST",           //...window class name
                     (PSZ)"Simple E-MLE Example",   //...title bar text.
                     0L,                    //...
                     (HMODULE)NULL,         //...
                     0,                     //...
                     (PHWND)&hwndAppClient  //...(return) client wnd handle
                     );

                                            // set instance data
    // WinSetWindowULong( hwndAppClient, 0, (ULONG)&instance);

    rect.xLeft   =  75;                     // Position Application Window
    rect.yBottom =  100;
    rect.xRight  =  500;
    rect.yTop    =  300;

    WinSetWindowPos ((HWND)hwndAppFrame,    // Set position of app window
                     (HWND)HWND_TOP,
                     (SHORT)rect.xLeft,
                     (SHORT)rect.yBottom,
                     (SHORT)rect.xRight,
                     (SHORT)rect.yTop,
                     SWP_MOVE | SWP_SIZE );


   //----------  Register Edit Window -------------
   class=EtkRegister( hab, CS_SIZEREDRAW );

   // register function returns window class name.
   strcpy( EMLE_ClassName, class);

   // are you loading a file from the command line
   if (argc > 1) {
      strcpy (Fname,argv[1]);
   } else
      strcpy (Fname,"sample.doc");

   // Create initial edit window.
   hwndEdit=CreateEditWindow( hab, hwndAppClient, Fname );

   WinShowWindow( hwndAppFrame, TRUE );


   // dispatch messages to Test Application
   while( WinGetMsg( hab, (PQMSG)&qmsg, (HWND)NULL, 0, 0 ) ) {
       WinDispatchMsg( hab, (PQMSG)&qmsg );
   }

   // Close up shop

   WinDestroyWindow( hwndAppFrame );
   WinDestroyMsgQueue( hmq );
   WinTerminate( hab );
}
