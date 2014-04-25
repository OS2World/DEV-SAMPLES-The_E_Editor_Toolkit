all  :  esampdlg.obj esampdlg.res esampdlg.dll  esampdlg.ex

esampdlg.obj :  esampdlg.c
      cl -c -W3 -Alfu -G2s -Zi -Zp esampdlg.c

esampdlg.dll : esampdlg.obj esampdlg.res esampdlg.def
      link  esampdlg, /CO /NOI, esampdlg , os2 llibce, esampdlg
      rc esampdlg.rc esampdlg.dll

esampdlg.res : esampdlg.rc
      rc -r esampdlg.rc

esampdlg.ex  : esampdlg.e
      etpm  esampdlg
