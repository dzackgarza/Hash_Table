#ifndef MYFUNC_H
#define MYFUNC_H

// Generate random string of alphabetic characters
// Includes upper and lower case letters.
char* random_string( size_t length )
{
    char alphanum[] =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int alphaLength = sizeof(alphanum) - 1;
    char* Str = new char[length];

    for(unsigned int i = 0; i < length; ++i)
        Str[i] = alphanum[rand() % alphaLength];
    return Str;
}

// Generates random integer between fMin and fMax.
double iRand(int fMin, int fMax)
{
    int f = (int)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double TIME ( void )
{
    struct timeb t;
    ftime(&t);
    return ( ( (1000.0 * t.time) + t.millitm ) );
}
#endif
