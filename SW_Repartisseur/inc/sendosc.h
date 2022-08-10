#ifndef SEND_DEF
#define SEND_DEF

enum type{int_, string_, sine_};


int sendosc(type t, void* val, const char *host);


#endif
