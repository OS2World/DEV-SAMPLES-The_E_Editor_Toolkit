-- Key definitions :    
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
def a_p      ='top';'proof'

-- This event procedure is called when an new edit window is opened.
-- arg(1) contains the string that was passed to EPM_EditWindowCreate
-- in the create structure as 'filename'.
defmain
   'xcom e 'arg(1)  -- assume arg(1) is a file and edit it
   .autosave     = 0
   .textcolor    = 240
   keys mykeys
