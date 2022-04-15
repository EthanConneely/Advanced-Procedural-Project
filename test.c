void getPassword(char* password, int size)
{
    for (int i = 0; i < size; i++)
    {
        password[i] = getch();
        putch('*');
        // enter key finishes input
        if (password[i] == 13)
        {
            break;
        }
    };
}
