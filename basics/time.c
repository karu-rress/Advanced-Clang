// basic time functions

#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

int main(void) {
    time_t now;
    struct tm tm_now, tm_next;

    now = time(NULL); // same as 'time(&now);'
    tm_now = *localtime(&now);
    tm_next = tm_now;

    tm_next.tm_mon += 10;
    tm_next.tm_mday += 30;
    tm_next.tm_hour += 5;

    mktime(&tm_next); // normalize the time structure

    printf("Today is %d-%d-%d %d:%d:%d\n",
        tm_now.tm_year + 1900, tm_now.tm_mon + 1,
        tm_now.tm_mday, tm_now.tm_hour);

    printf("Added date is %d-%d-%d %d:%d:%d\n",
        tm_next.tm_year + 1900, tm_next.tm_mon + 1,
        tm_next.tm_mday, tm_next.tm_hour);

    tm_now.tm_mon -= 10;
    tm_now.tm_mday -= 30;
    tm_now.tm_hour -= 5;

    mktime(&tm_now);
    printf("Subtracted date is %d-%d-%d %d:%d:%d\n",
        tm_now.tm_year + 1900, tm_now.tm_mon + 1,
        tm_now.tm_mday, tm_now.tm_hour);

    struct _timeb tb;
    struct tm t;
    char buff[100];

    _ftime(&tb);
    t = *localtime(&tb.time);

    printf("%4d-%d-%d %d:%d:%d.%d \n",
        t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
        t.tm_hour, t.tm_min, t.tm_sec, tb.millitm);

    puts(ctime(&tb.time));
    puts(asctime(&t));
    puts(_strdate(buff));
    puts(_strtime(buff));

    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S %p (%a)", &t);
    puts(buff);
    strftime(buff, sizeof(buff), "%c", &t);
    puts(buff);
    strftime(buff, sizeof(buff), "%x %X", &t);
    puts(buff);
    strftime(buff, sizeof(buff), "%#c", &t);
    puts(buff);
    strftime(buff, sizeof(buff), "%#x", &t);
    puts(buff);

    return 0;
}
