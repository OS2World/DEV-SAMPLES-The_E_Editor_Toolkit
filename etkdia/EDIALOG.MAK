all  :  edialog.obj  edialog.exe  edialog.res edialog.ex

edialog.obj :  edialog.c
      cl -c -W3 -Alfu -G2s -Zi -Zp edialog.c

edialog.exe : edialog.obj edialog.def
      link  edialog, /CO /NOI, edialog , os2 llibce, edialog

edialog.res : edialog.rc  edialog.exe
      rc    edialog

edialog.ex  : edialog.e
      etpm  edialog
