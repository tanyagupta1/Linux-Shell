#-*- MakeFile -*-
target: makeDir dateTime rm cat ls shell
shell:shell.c echoF.c
	gcc shell.c echoF.c -o shell
ls: listdir.c
	gcc listdir.c -o ls
cat:catFile.c
	gcc catFile.c -o cat
rm: delete.c
	gcc delete.c -o rm
dateTime:dateTime.c
	gcc dateTime.c -o dateTime
makeDir:makeDir.c
	gcc makeDir.c -o makeDir
