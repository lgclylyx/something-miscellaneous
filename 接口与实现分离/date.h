#ifndef _date_h
#define _date_h
class CDate{
public:
	explicit CDate(int month,int day,int year);
	~CDate();
	void Print(void);
private:
	int year;
	int mon;
	int day;
};
#endif