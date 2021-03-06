/*
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
� What's it called: ESAMPDLG.C                                               �
�                                                                            �
� What does it do : Contains  sample dynalink library functions that create  �
�                   two types of  PM dialog boxs, A Modeless and Modal dialog�
�                   box.    These dialog boxes can be created and controlled �
�                   through the use of EPM macros.   ESAMPDLG.E  contains    �
�                   macros to work with ESAMPDLG.DLL                         �
�                                                                            �
� .DLL functions  : Sample1DlgCreate -  Modeless Dialog box example.         �
�                   Sample1DlgProc   -                                       �
�                   Sample2DlgCreate -  Application Modal dialog box example.�
�                   Sample2DlgProc   -                                       �
�                                                                            �
� Who and When    : Gennaro (Jerry) Cuomo                          3 -90     �
�                                                                            �
� Version         : Uses ETKExxx.DLL version 5.5x                            �
�                                                                            �
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/

/*
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
� Included Header Files:                                             GC 9-88 �
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/
#define INCL_WIN         /* winthorn definitions (WIN function and WM_ msgs)*/
#define INCL_DOS         /* Dosxxx functions                                */
#include <os2.h>         /* start of the winthorn include chain             */
#include <stdio.h>       /* C library functions...                          */
#include <stdlib.h>      /* C library functions...                          */
#include <string.h>      /* C library functions...                          */
#include "esampdlg.h"    // include dialog box constant definitions
#include <etoolkt.h>     // include E-Toolkit bindings.

/*
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
� Function Prototypes                                                GC 9-88 �
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/
MRESULT EXPENTRY Sample1DlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
HWND    EXPENTRY Sample1DlgCreate( HWND hwndEdit );
MRESULT EXPENTRY Sample2DlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
VOID    EXPENTRY Sample2DlgCreate( HWND hwndEdit, PSZ stringbuffer );

/*
浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融
� Execute Procedure structure used by the EPM_EDIT_EXEC_PROC msg.    GC 9-88 �
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕
*/
typedef struct _ep {
   union {
      unsigned long  (pascal far *pProcLong)(void); // address of function (Pascal) returning a long
      unsigned short (pascal far *pProc)(void);     // address of function (Pascal) returning a short
      unsigned long  (cdecl  far *cProcLong)(void); // address of function (C) returning a long
      unsigned short (cdecl  far *cProc)(void);     // address of function (C) returning a short
   } ProcConv;
   unsigned short StackSize;                      // stack size in bytes
   char           *Stack;                         // pointer to the stack data
   unsigned short NumberOfReturnWords;            // number of return words in RC
   unsigned short StackRC;                        // TRUE if error in number of parameters
   unsigned long  RC;                             // return value of proc
   unsigned short PascalC;                        // pascal or C convention.
} EP, *PEP;

/*
敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
�                                                                            �
� What's it called: MyWinDlgBox                                              �
�                                                                            �
� What does it do : Calls WinDlgBox to create a PM Dialog from the           �
�                   information contained in the Dialog Box structure passed �
�                   in as param 1.                                           �
�                                                                            �
�                   The function serves as an example of indirectly calling  �
�                   code using the EPM_EDIT_EXEC_PROC.  This message is      �
�                   useful if you want to call 'C' code from the E macros    �
�                   that runs in the main PM thread.   This is necessary     �
�                   for functions that need a PM message queue.              �
�                                                                            �
� Who and when    : Gennaro (Jerry) Cuomo            9-92                    �
�                                                                            �
青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
*/
typedef struct _dlgbox {
   HWND hwndParent;
   HWND hwndOwner;
   PFNWP pfnDlgProc;
   HMODULE hmod;
   USHORT idDlg;
   PVOID pCreateParams;
} WINDLGBOX, *PWINDLGBOX;

USHORT MyWinDlgBox(PWINDLGBOX pDlgBox)
{
     #if 0
     return(WinDlgBox(pDlgBox->hwndParent,
                      pDlgBox->hwndOwner,
                      pDlgBox->pfnDlgProc,
                      pDlgBox->hmod,
                      pDlgBox->idDlg,
                      pDlgBox->pCreateParams));

     #else
     return((USHORT)WinLoadDlg(pDlgBox->hwndParent,
                      pDlgBox->hwndOwner,
                      pDlgBox->pfnDlgProc,
                      pDlgBox->hmod,
                      pDlgBox->idDlg,
                      pDlgBox->pCreateParams));
     #endif
}

/*
敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
�                                                                            �
� What's it called: Sample1DlgCreate                                         �
�                                                                            �
� What does it do : Create the sample dialog box.  Need to pass the handle   �
�                   to the edit window so the dialog box knows how to        �
�                   communicate results.                                     �
�                                                                            �
�                   The edit window handle is passed to the dialog proc      �
�                   and remembered by the dialog box.  This is done via      �
�                   the control data parameter.                              �
�                                                                            �
�                   This function creates a Modeless dialog box.             �
�                                                                            �
� Who and when    : Gennaro (Jerry) Cuomo            3-90                    �
�                                                                            �
青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
*/
HWND EXPENTRY Sample1DlgCreate( HWND hwndEdit )
{
    HMODULE hModule;   // handle to .DLL module

    // need to get a module to load resources from ESAMPDLG.DLL
    DosLoadModule( (PSZ)NULL, (USHORT)0, (PSZ)"ESAMPDLG",(PHMODULE)&hModule );

    #if 0
    // Calling WinDlgBox directly will work.  However, you will not
    // be able to type in the editor window.  This is because WinDlgBox
    // must be called from a thread that has a PM message queue.  Since
    // this function is being called from a E macro and E macros run in
    // a thread with out a PM message queue, we choose an alternate method
    // that executes WinDlgBox in the main PM thread.
    WinDlgBox( HWND_DESKTOP,      // parent
               WinQueryWindow(hwndEdit, QW_PARENT, FALSE),   // owner
               Sample1DlgProc,    // dialog procedure address
               hModule,           // resource id
               DLG_SAMPLE,        // dialog id
               (PVOID)hwndEdit    // pass edit window handle to dlg proc
             );
    #else
    {  static EP ep;          // Note EP is STATIC
       WINDLGBOX DlgBox;
       PWINDLGBOX pDlgBox=&DlgBox;

       DlgBox.hwndParent    =HWND_DESKTOP;     // parent
       DlgBox.hwndOwner     =WinQueryWindow(hwndEdit, QW_PARENT, FALSE); // HWND_DESKTOP;     // owner
       DlgBox.pfnDlgProc    =Sample1DlgProc;   // dialog procedure address
       DlgBox.hmod          =hModule;          // resource id
       DlgBox.idDlg         =DLG_SAMPLE;       // dialog id
       DlgBox.pCreateParams =(PVOID)hwndEdit;  // pass edit window handle to dlg proc

       // Set up the "Execute Procedure" message that is used
       // by the EPM_EDIT_EXEC_PROC message.
       ep.ProcConv.pProcLong  = (ULONG (pascal *)())MyWinDlgBox;
       ep.StackSize           = sizeof(PWINDLGBOX); // sizeof(WINDLGBOX);
       ep.Stack               = (PSZ)&pDlgBox;
       ep.NumberOfReturnWords = 1;
       ep.StackRC             = 0;
       ep.RC                  = 0;
       ep.PascalC             = 0;  // Pascal convention
       // execute procedure asynchronously in our first thread.
       WinPostMsg( hwndEdit, EPM_EDIT_EXEC_PROC, MPFROMP(&ep), 0L);
    }
    #endif

    DosFreeModule( hModule );
}

/*
敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
�                                                                            �
� What's it called: Sample1DlgProc                                           �
�                                                                            �
� What does it do : Handles messages sent to the the sample dialog box       �
�                                                                            �
� Who and when    : Gennaro (Jerry) Cuomo            3-90                    �
�                                                                            �
青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
*/
MRESULT EXPENTRY Sample1DlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)  {
    /*
    敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    �  Initialize Dialog Box.                                   �
    青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    */
    case WM_INITDLG:
      {
        CHAR   cmd[MAXCMD];
        CHAR   handle[MAXCMD];
        HWND   hwndEdit;

        // the edit window handle was passed as the ctrl data parameter
        // to WinDlgBox. see WinDlgBox in the Sample1DlgCreate function.
        hwndEdit=(HWND)mp2;

        // here is an interesting trick... We want the dlg box to remember
        // the edit windows handle, but we don't want to keep it in a
        // global variable because we want to be reentrant.  We can
        // use the user field of the DLG box window class to store
        // the edit window handle for safe keeping.
        WinSetWindowULong(hwnd, QWL_USER, (ULONG)hwndEdit);

        // form EPM defc command-  syntax: sample1dlg action [value]
        // in this case the [value] parameter is the dialog box handle.
        // the macros need to know this so they can communicate with
        // this newly created dialog box.
        strcpy( cmd, "SAMPLE1MACROPROC INITDLG ");
        ltoa((ULONG)hwnd,handle,10);
        strcat(cmd,handle);

        // tell edit window to execute the given command.
        WinSendMsg( hwndEdit,  EPM_EDIT_COMMAND, MPFROMP( cmd ), 0L);
      }
      break;
    /*
    敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    �  Command messages can be generated by selecting a dialog  �
    �  box button, or can be sent by a EPM macro.               �
    青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    */
    case WM_COMMAND:
      switch( SHORT1FROMMP( mp1 ) )  {

        /*
        敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
        �  The following three command messages are the result of   �
        �  the user selecting a button.  The buttons are processed  �
        �  by sending a messages to the edit window that created    �
        �  the dialog box.  (We registered the edit window as the   �
        �  dialog box owner when we created the dialog box.  There- �
        �  fore if we can query the owner of the dialog box to get  �
        �  the edit window handle.)    EDLLSAMP.E defines a command �
        �  called SAMPLE1DLG.  The message sent   to the edit window�
        �  instructs the window to execute the SAMPLE1DLG command.  �
        青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
        */
        case DID_OK:  /* Enter key or pushbutton pressed/ selected */
          {
            CHAR   entry[MAXENTRYLEN];
            CHAR   cmd[MAXCMD];
            HWND   hwndEdit;

            // read text from entry field.
            WinQueryDlgItemText( hwnd, DID_EDITFIELD, MAXENTRYLEN, (PSZ)entry );

            // the edit window is the registered owner of this dialog box
            // see WinDlgBox in the Sample1DlgCreate function.
            hwndEdit=(HWND)WinQueryWindowULong( hwnd, QWL_USER);

            // form EPM defc command-  syntax: sample1dlg action [value]
            strcpy( cmd, "SAMPLE1MACROPROC ENTER_PRESSED ");
            strcat( cmd, entry);

            // tell edit window to execute the given command.
            WinSendMsg( hwndEdit,   EPM_EDIT_COMMAND,
                        MPFROMP( cmd ), 0L);

            WinDismissDlg( hwnd, FALSE);
          }
          break;
        case DID_HELP:
          {
            CHAR   cmd[MAXCMD];
            HWND   hwndEdit;

            // the edit window is the registered owner of this dialog box
            // see WinDlgBox in the Sample1DlgCreate function.
            hwndEdit=(HWND)WinQueryWindowULong( hwnd, QWL_USER);

            // form EPM defc command-  syntax: sample1dlg action [value]
            strcpy( cmd, "SAMPLE1MACROPROC HELP_PRESSED");

            // tell edit window to execute the given command.
            WinSendMsg( hwndEdit,   EPM_EDIT_COMMAND,
                        MPFROMP( cmd ), 0L);
          }
          break;
        case DID_CANCEL: /* Escape key or CANCEL pushbutton pressed/selected */
          WinDismissDlg( hwnd, FALSE ); /* Finished with dialog box*/
          return(0L);
          break;
        /*
        敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
        �  The following command message is sent from an  EPM macro �
        �  to the dialog box.   When the EPM macro creates this     �
        �  dialog using the Sample1DlgCreate function we return     �
        �  the dialog boxes handle as a result.   The EPM macro     �
        �  the uses this handle to send this WM_COMMAND message.    �
        青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
        */
        case SET_NAME:
          WinSetDlgItemText(hwnd, DID_EDITFIELD, mp2 );
          break;
      }
      break;

    default:  /* Pass all other messages to the default dialog proc */
      return WinDefDlgProc( hwnd, msg, mp1, mp2 );
      break;
  } // end-switch
  return(0L);
}
/*
敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
�                                                                            �
� What's it called: Sample2DlgCreate                                         �
�                                                                            �
� What does it do : Create the sample dialog box.  Need to pass the handle   �
�                   to the edit window so the dialog box knows how to        �
�                   communicate results back to macro.                       �
�                                                                            �
�                   Unlike sample 1, this function doesn't terminate until   �
�                   the dialog box is closed.                                �
�                                                                            �
�                   This function creates an application model dialog box.   �
�                                                                            �
� Who and when    : Gennaro (Jerry) Cuomo            3-90                    �
�                                                                            �
青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
*/
VOID EXPENTRY  Sample2DlgCreate( HWND hwndEditFrame, PSZ stringbuffer )
{
    HMODULE hModule;   // handle to .DLL module
    USHORT  resultsel;        /* selector whos zero offset points to the    */
                              /* text entered on the entry field line.      */

    // need to get a module to load resources from ESAMPDLG.DLL
    DosLoadModule( (PSZ)NULL, (USHORT)0, (PSZ)"ESAMPDLG",(PHMODULE)&hModule );

    resultsel=WinDlgBox( HWND_DESKTOP,      // parent
                         hwndEditFrame,     // owner
                         Sample2DlgProc,    // dialog procedure address
                         hModule,           // resource id
                         DLG_SAMPLE,        // dialog id
                         NULL               // send pentry structure
                       );
    // the result segment contains any text entered in the entry field of
    // the sample dialog box.
    if (resultsel) {
       int i = 0; PSZ resultstr;
       SELECTOROF(resultstr)=resultsel;
       OFFSETOF(resultstr)=0;

       /* copy string  */
       while (resultstr[i] && i<MAXENTRYLEN ) {
          stringbuffer[i]=(char)resultstr[i];
          i++;
       }
       DosFreeSeg( resultsel );        // allocated in DlgProc
       if (i<MAXENTRYLEN) {
          stringbuffer[i]=0;           /* null terminate */
       } else {
          stringbuffer[0]=(char)'\0';  /* return null string */
       }
    } else {
       stringbuffer[0]=(char)'\0';
    }
    DosFreeModule( hModule );
}
/*
敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
�                                                                            �
� What's it called: Sample2DlgProc                                           �
�                                                                            �
� What does it do : Handles messages sent to the the sample dialog box       �
�                                                                            �
� Who and when    : Gennaro (Jerry) Cuomo            3-90                    �
�                                                                            �
青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰
*/
MRESULT EXPENTRY Sample2DlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)  {
    /*
    敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    �  Initialize Dialog Box.                                   �
    青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    */
    case WM_INITDLG:
      // Replace text in dialog box title bar.
      WinSetWindowText( hwnd, "Sample 2- Application Modal Dialog Box");
      break;
    /*
    敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    �  Command messages can be generated by selecting a dialog  �
    �  box button, or can be sent by a EPM macro.               �
    青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    */
    case WM_COMMAND:
      switch( SHORT1FROMMP( mp1 ) )  {

        /*
        敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
        �  The following three command messages are the result of   �
        �  the user selecting a button.  The buttons are processed  �
        �  by sending a messages to the edit window that created    �
        �  the dialog box.  (We registered the edit window as the   �
        �  dialog box owner when we created the dialog box.  There- �
        �  fore if we can query the owner of the dialog box to get  �
        �  the edit window handle.)    EDLLSAMP.E defines a command �
        �  called SAMPLE1DLG.  The message sent   to the edit window�
        �  instructs the window to execute the SAMPLE1DLG command.  �
        青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
        */
        case DID_OK:  /* Enter key or pushbutton pressed/ selected */
          {
            PSZ    entry;
            USHORT ret,rc;
            ret=DosAllocSeg( MAXENTRYLEN, (PSEL)&rc, FALSE );
            if (ret) {
               WinDismissDlg( hwnd, 0 ); /* out of memory */
               return(0L);
            }
            SELECTOROF(entry) = rc;
            OFFSETOF(entry) = 0;

            // read text from entry field.
            WinQueryDlgItemText( hwnd, DID_EDITFIELD, MAXENTRYLEN, (PSZ)entry );

            WinDismissDlg( hwnd, rc ); /* Finished with dialog box        */
                                       /* return selector of entry string */
          }
          break;
        case DID_HELP:
          {
          }
          break;
        case DID_CANCEL: /* Escape key or CANCEL pushbutton pressed/selected */
          WinDismissDlg( hwnd, FALSE ); /* Finished with dialog box*/
          return(0L);
          break;
        /*
        敖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
        �  The following command message is sent from an  EPM macro �
        �  to the dialog box.   When the EPM macro creates this     �
        �  dialog using the Sample1DlgCreate function we return     �
        �  the dialog boxes handle as a result.   The EPM macro     �
        �  the uses this handle to send this WM_COMMAND message.    �
        青陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
        */
        case SET_NAME:
          WinSetDlgItemText(hwnd, DID_EDITFIELD, mp1 );
          break;
      }
      break;

    default:  /* Pass all other messages to the default dialog proc */
      return WinDefDlgProc( hwnd, msg, mp1, mp2 );
      break;
  } // end-switch
  return(0L);
}
