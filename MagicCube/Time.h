#pragma once

#include <sys/timeb.h>

class Time {

private:

	INT64 mMilliseconds;

public:

	Time() {
		timeb t;
		ftime(&t);
		mMilliseconds = 1000 * t.time + t.millitm;
	}

	Time(INT64 milliseconds) : mMilliseconds(milliseconds){}

	Time(const Time& time) {
		if (&time != this) {
			mMilliseconds = time.mMilliseconds;
		}
	}

	~Time() {}

public:

	Time& operator =(const Time& time)
	{
		if (&time != this)
		{
			mMilliseconds = time.mMilliseconds;
		}
		return *this;
	}

	bool operator ==(const Time& time) const
	{
		return mMilliseconds == time.mMilliseconds;
	}

	bool operator !=(const Time& time) const
	{
		return mMilliseconds != time.mMilliseconds;
	}

	bool operator >(const Time& time) const
	{
		return mMilliseconds > time.mMilliseconds;
	}

	bool operator <(const Time& time) const
	{
		return mMilliseconds < time.mMilliseconds;
	}

	bool operator >=(const Time& time) const
	{
		return mMilliseconds >= time.mMilliseconds;
	}

	bool operator <=(const Time& time) const
	{
		return mMilliseconds <= time.mMilliseconds;
	}

	bool before(const Time& time) const
	{
		return mMilliseconds < time.mMilliseconds;
	}

	bool after(const Time& time) const
	{
		return mMilliseconds > time.mMilliseconds;
	}

	INT64 getTime() const
	{
		return mMilliseconds;
	}

	void setTime(INT64 milliseconds)
	{
		mMilliseconds = milliseconds;
	}

public:

	static INT64 getSystemTime()
	{
		timeb t;
		ftime(&t);
		return 1000 * t.time + t.millitm;
	}


};

