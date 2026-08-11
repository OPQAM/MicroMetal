
int X;

int funfas()
{
    extern void myFunct1(void); // declaration
    myFunct1(); // calling the function

    //extern void myStaticFunct(void); // The call below won't work. This function is static.
    //myStaticFunct();
    X = 42;
    return 0;
}
