#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>

int main(void)
{
    time_t now;
    struct tm tm_now, tm_next;
    
    time(&now);
    tm_now = *localtime(&now);
    
    tm_next = tm_now;
    
    tm_next.tm_mon  += 10;  // 10 개월
    tm_next.tm_mday += 30;  // 30 일
    tm_next.tm_hour +=  5;  //  5 시간
    
    mktime(&tm_next);
    
    printf("오늘은 %d년 %d월 %d일 %d시입니다.\n",
        tm_now.tm_year+1900, tm_now.tm_mon+1,
        tm_now.tm_mday     , tm_now.tm_hour);
    
    printf("더한 날짜는 %d년 %d월 %d일 %d시입니다. \n",
        tm_next.tm_year+1900, tm_next.tm_mon+1, 
        tm_next.tm_mday     , tm_next.tm_hour);
    
    tm_now.tm_mon  -= 10;   // 10 개월
    tm_now.tm_mday -= 30;   // 30 일
    tm_now.tm_hour -=  5;   //  5 시간
    
    mktime(&tm_now);
    printf("뺀 날짜는 %d년 %d월 %d일 %d시입니다. \n",
        tm_now.tm_year+1900, tm_now.tm_mon+1, 
        tm_now.tm_mday     , tm_now.tm_hour);


        struct _timeb tb;
    struct tm t;
    char buff[100];
    
    _ftime(&tb);
    
    t = *localtime(&tb.time);
    
    printf("%4d-%d-%d %d:%d:%d.%d \n", 
        t.tm_year+1900, t.tm_mon+1, t.tm_mday,
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
}