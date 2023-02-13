
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// int main()
// {
//     char *teste;
// 	char *prompt = "i-shell> ";

//     teste = readline(prompt);
//     // teste = "HEY";
//     printf("\n%s\n", teste);

// }


//move the cursor -- I dont get it

// #include <stdio.h>
// #include <termcap.h>
// #include <unistd.h>

// int main(void)
// {
//     char *cursor_movement;

//     cursor_movement = tgoto("cm", 10, 20);
//     tputs(cursor_movement, 1, putchar);

//     return 0;
// }


//get the numbers of columns / its printig -1, why?

// #include <termcap.h>
// #include <unistd.h>
// #include <stdio.h>

// int main(void)
// {
//     int columns;

//     /* Get the number of columns supported by the terminal */
//     columns = tgetnum("");

//     /* Print the number of columns */
//     printf("The terminal has %d columns.\n", columns);

//     return 0;
// }


//get boolean about automatic margins ont he terminal, the string as an argument should make a difference but it doenst

// #include <termcap.h>
// #include <unistd.h>
// #include <stdio.h>

// int main(void)
// {
//     int am;

//     /* Get the state of the automatic margins capability */
//     am = tgetflag("am");

//     /* Print the state of the automatic margins capability */
//     printf("The terminal %s automatic margins.\n", am ? "has" : "does not have");

//     return 0;
// }
