HOW TO RUN:
    --run "make"
    --run "./jash"

NAME OF EXECUTALE = "./jash"

This code briefly implements the bash shell.Following functions are implemented in corresponding files:-
Files with corresponding functions:
    shell.h -- header file
    shell.c -- main function
    built-in.c -- built-in functions(cd,pwd,echo)
    ls-impli.c -- implementation of (ls,-l,-a)
    prompt.c -- invokes prompt
    parse.c -- parses the input files
    pinfo.c -- implementation of pinfo
    execute.c -- Implementation of foreground & background processes with signal handling of a bacground process
    remind.c -- reminder function(bonus)
