-- This event procedure is called when an new edit window is opened.
-- arg(1) contains the string that was passed to EPM_EditWindowCreate
-- in the create structure as 'filename'.
defmain
   'xcom e 'arg(1)  -- assume arg(1) is a file and edit it
   .autosave     = 0
   keys mykeys
   -- Show window, EPM toolkit windows are initialy hidden
   -- post the EPM_EDIT_SHOW message
   call windowmessage(0, getpminfo(5),
                      5385,
                      upcase(arg(1))<>'OFF', -- 0 if OFF, else 1
                      0)

-- Key definitions :    EDLLSAMP.E defines a small set of active key...
-- Look at STDKEYS.E provided in EMACROS.FLS for other key definitions.

defkeys mykeys new

def space    =keyin ' '
def backspace=rubout
def enter    =insert;down;.col=1
def home     =begin_line
def ins      =insert_toggle
def left     =left
def pgup     =page_up
def pgdn     =page_down
def right    =right
def left     =left
def up       =up
def down     =down
def del=delete_char

-- Commands that are used by EDLLSAMP
-- Look at STDCMDS.E provided in EMACROS.FLS for other cmd definitions.

-- Close the edit window by posting it a PM destroy message.
defc close=
    /* WM_CLOSE */
    WindowMessage( 0, gethwnd(5), 41, 0, 0)

-- Returns the edit window handle, as a 4-digit decimal string.
defproc gethwnd(w)
   hwnd    = atol(getpminfo(w))   /* get edit window handle           */
                                  /* convert string to string pointer */
                                  /* interchange upper two bytes with */
                                  /* lower two bytes. (flip words)    */

   return substr(hwnd,3,2) || substr(hwnd,1,2)
