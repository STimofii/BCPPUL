//include/bcppul/timer.h
#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "bcppul_expimp.h"
#include <iostream>
#include <chrono>


namespace bcppul {
	class BCPPUL_API Timer {
	public:
		Timer();
		~Timer();
		Timer(const Timer& other);
		Timer& operator=(const Timer& other);
		Timer(Timer&& other) noexcept;
		Timer& operator=(Timer&& other) noexcept;
		friend bool operator== (const Timer& f, const Timer& s);
		friend bool operator!= (const Timer& f, const Timer& s);
		friend bool operator> (Timer& f, Timer& s);
		friend bool operator< (Timer& f, Timer& s);
		friend bool operator>= (Timer& f, Timer& s);
		friend bool operator<= (Timer& f, Timer& s);
		friend BCPPUL_API std::ostream& operator<< (std::ostream& out, Timer& timer);

		virtual long long start();
		virtual long long stop();
		virtual void printTime();
		virtual void stopAndPrintTime();
		virtual long long getStart() const;
		virtual long long getStop() const;
		virtual long long getTime();
		virtual long long getRunning() const;
		virtual long long updateTime();
		virtual long double getTimeSeconds();
		virtual long double getTimeMilliseconds();
		virtual long double getTimeMicroseconds();
		virtual long long getTimeNanoseconds();

	protected:
		long long start_time;
		long long stop_time;
		long long time = 0;
		bool running = false;

	private:

	};

	class BCPPUL_API SimpleTimer : public Timer{
	public:
		SimpleTimer();
		~SimpleTimer();
	protected:
	private:
	};


} // namespace bcppul

#endif // TIMER_H