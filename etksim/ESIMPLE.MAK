all  :  esimple.obj  esimple.exe  esimple.ex

esimple.obj :  esimple.c
      cl -c -W3 -Alfu -G2s -Zi -Zp esimple.c

esimple.exe : esimple.obj esimple.def
      link  esimple, /CO /NOI, esimple , os2 llibce, esimple

esimple.ex  : esimple.e
      etpm  esimple
