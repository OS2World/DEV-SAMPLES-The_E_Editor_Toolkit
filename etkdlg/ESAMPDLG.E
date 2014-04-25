--
-- ESAMPDLG.E
--
-- Sample E code that works with SAMPDLG.DLL to create custom dialog boxes
-- from the E macro language.
-- Two examples commands are provided:
--      CreateSample1Dlg - Creates a modeless dialog box.  This box is
--                  -      useful when you wish the user to operate with
--                         the dialog box and the text file simultaneously.
--      CreateSample2Dlg - Creates a application modal dialog box.  This box is
--                  -      useful when it is important to get a response from
--                         the user before continuing with the rest of the macro.
--
--                                          JAC - 3/90


const SET_ENTRYDATA = 1000          -- WM_COMMAND sub-command number
      HWNDEDIT      = 5
      HWNDEDITFRAME = 6

-- Add a submenu to EPM's Action Bar when this module is linked in.
definit
   -- Add to EPM's Action Bar
   samplemenu='default'
   buildsubmenu  samplemenu, 1000, 'Sample', '', 0, 0
   buildmenuitem samplemenu, 1000, 10, 'Modeless Dialog Box Sample', 'CreateSample1Dlg', 0, 0
   buildmenuitem samplemenu, 1000, 20, 'Modal Dialog Box Sample',    'CreateSample2Dlg', 0, 0
   showmenu samplemenu

-- CreateSample1Dlg
-- Creates the Modeless dialog box.  That is the dialog box and the
-- edit window can operate asynchronously.
-- Note:  1) dynalink() expects the function that it is calling to be defined
--           as EXPENTRY (FAR PASCAL)
--        2) gethwnd() - returns important handle in E window frame.
--        3) Once this dialog box is created it uses the Sample1MacroProc
--           command to process events.
--                                          JAC - 3/90
defc CreateSample1Dlg
   call dynalink( 'ESAMPDLG',         -- dll name
                  'SAMPLE1DLGCREATE', -- dll function name
                  gethwnd(HWNDEDIT))  -- pass edit window handle

   -- done

-- This command is used to process events that occur within the DLG box.
-- You can almost think of this as a PM window or dialog procedure.
--                                          JAC - 3/90
defc Sample1MacroProc
   universal hwndDlg         -- set during the processing of the INITDLG action

   parse arg action mp1      -- parse arguments into an action and a value
                             -- 'action' is a string describing what just
                             -- happened in the dialog box
                             -- mp1 is used by some actions to give some details
                             -- about the action.
                                      -- **********
   if action='ENTER_PRESSED' then     -- the ENTER button was just pressed.
      -- mp1 contains the data in the entry field of the dialog box.
      -- now we display the data in a PM message box.
      call winmessagebox("Data Entered",mp1)
                                      -- **********
   elseif action='INITDLG' then       -- the Dialog box was just created.

      -- mp1 contains the handle to the dialog box just created.
      hwndDlg=mp1
      -- this can be used to initialize the entry field
      Call WinSendMsg( hwndDlg, SET_ENTRYDATA, "Gennaro Cuomo")

   elseif action='HELP_PRESSED' then  -- **********
                                      -- the HELP button was just pressed
       -- pop up a message box with the following message.
       call winmessagebox("Help Panel","Your not the only one who needs help!");

   endif

-- Creates the Modeless dialog box.   That is the macro doesnot continue
-- until the dialog box is closed.
--                                          JAC - 3/90
defc CreateSample2Dlg
   -- allocate string space
   strbuf='                             '
   -- create application modal dialog box. Pass create function edit windw
   -- frame handle and a pointer to a string buffer in which the entry field
   -- contents will be placed.
   call dynalink( 'ESAMPDLG',
                  'SAMPLE2DLGCREATE',
                  gethwnd(HWNDEDITFRAME) ||
                  selector(strbuf)       ||
                  offset(strbuf))

   sayerror '<'strbuf'>'  -- display results.


-- Sends a WM_COMMAND message to Sample dialog box.
defproc WinSendMsg( hwnd, msg, mp1 )
   mp1 = mp1 \0
   call windowmessage(1,  hwnd,
                      32,               -- WM_COMMAND
                      msg,
                      ltoa(offset(mp1) || selector(mp1), 10) )


--
-- Utility functions follow
--

-- this proc calls PM's WinMessageBox function
defproc winmessagebox(caption, text)

  msgtype = 4096                                        -- must be system modal.
  if arg(3) then
     msgtype=arg(3) + 4096 * (1 - (arg(3)%4096 - 2 * (arg(3)%8192)))  -- ensure x'1000' on
  endif
  caption = caption\0
  text    = text\0
  return dynalink( 'PMWIN',
                   'WINMESSAGEBOX',
                   atoi(0) || atoi(1) ||   -- Parent
                   atoi(0) || atoi(1) ||   -- Owner
                   selector(text)     ||   -- Text
                   offset(text)       ||
                   selector(caption)  ||   -- Title
                   offset(caption)    ||
                   atoi(0)            ||   -- Window
                   atoi(msgtype) )         -- Style

defproc atol_swap(num)
   hwnd=atol(num)
   return substr(hwnd,3,2) || substr(hwnd,1,2)

-- Returns the edit window handle, as a 4-digit decimal string.
defproc gethwnd(w)
   hwnd    = atol(getpminfo(w))   /* get edit window handle           */
                                  /* convert string to string pointer */
                                  /* interchange upper two bytes with */
                                  /* lower two bytes. (flip words)    */

   return substr(hwnd,3,2) || substr(hwnd,1,2)

/*
ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ The following are constants values that are to be used as parameters to    ³
³ the getpminfo internal function.                                           ³
³                                                                            ³
³ HAB           0  PARENTFRAME     4  EDITORMSGAREA      8   EDITVIOPS    12 ³
³ OWNERCLIENT   1  EDITCLIENT      5  EDITORVSCROLL      9   EDITTITLEBAR 13 ³
³ OWNERFRAME    2  EDITFRAME       6  EDITORHSCROLL      10  EDITCURSOR   14 ³
³ PARENTCLIENT  3  EDITSTATUSAREA  7  EDITORINTERPRETER  11                  ³
*³                                                                            ³
ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
*/
