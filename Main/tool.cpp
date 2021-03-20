#define _CRT_SECURE_NO_WARNINGS
#include"tool.h"
void timeToString(time_t nowt, char* pBuf)
{
	struct tm* timeinfo;
	timeinfo = localtime(&nowt);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);
}
time_t stringToTime(char* pTime)
{
	struct tm tm1;
	time_t time1;
	scanf_s(pTime, "%d-%d-%d %d:%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min);
	tm1.tm_year -= 1900;
	tm1.tm_mon -= 1;
	tm1.tm_sec = 0;
	tm1.tm_isdst = -1;
	time1 = mktime(&tm1);
	return time1;

}
