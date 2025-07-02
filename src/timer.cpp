#include "bcppul/timer.h"


namespace bcppul {
	unsigned long long rdtsc() {
		#ifdef _MSC_VER
				return __rdtsc();
		#elif defined(__GNUC) || defined(clang)
				unsigned int lo, hi;
				asm volatile("rdtsc" : "=a" (lo), "=d" (hi));
				return ((unsigned long long)hi << 32) | lo;
		#else
				return 0;
		#endif
	}

	bcppul::Timer::Timer()
	{
		start_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	}

	bcppul::Timer::~Timer()
	{

	}

	Timer::Timer(const Timer& other) :
		start_time(other.start_time),
		stop_time(other.stop_time),
		time(other.time),
		running(other.running)
	{

	}
	Timer::Timer(Timer&& other) noexcept :
		start_time(other.start_time),
		stop_time(other.stop_time),
		time(other.time),
		running(other.running)
	{

	}

	Timer& Timer::operator=(const Timer& other)
	{
		if (this != &other) {
			this->start_time = other.start_time;
			this->stop_time = other.stop_time;
			this->time = other.time;
			this->running = other.running;
		}
		return *this;
	}
	Timer& Timer::operator=(Timer&& other) noexcept
	{
		if (this != &other) {
			this->start_time = other.start_time;
			this->stop_time = other.stop_time;
			this->time = other.time;
			this->running = other.running;
		}
		return *this;
	}

	bool operator==(const Timer& f, const Timer& s)
	{
		return f.running == s.running && f.start_time == s.start_time && f.stop_time == s.stop_time && f.time == s.time;
	}
	bool operator>(Timer& f, Timer& s)
	{
		return f.getTime() > s.getTime();
	}
	bool operator<(Timer& f, Timer& s)
	{
		return f.getTime() < s.getTime();
	}
	bool operator>=(Timer& f, Timer& s)
	{
		return f.getTime() >= s.getTime();
	}
	bool operator<=(Timer& f, Timer& s)
	{
		return f.getTime() <= s.getTime();
	}
	bool operator!=(const Timer& f, const Timer& s)
	{
		return !(f == s);
	}


	std::ostream& operator<< (std::ostream& out, Timer& timer)
	{
		out << std::fixed << "time: " << timer.getTimeSeconds() << "s" << std::endl;
		return out;
	}

	unsigned long long Timer::start() {
		running = true;
		start_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		return start_time;
	}

	unsigned long long Timer::stop()
	{
		stop_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		updateTime();
		running = false;
		return time;
	}

	void Timer::printTime()
	{
		std::cout << *this;
	}

	void Timer::stopAndPrintTime()
	{
		stop();
		printTime();
	}



	unsigned long long Timer::getStart() const {
		return start_time;
	}
	unsigned long long Timer::getStop() const {
		return stop_time;
	}

	unsigned long long Timer::updateTime() {
		if (running) {
			stop_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		}
		time = stop_time - start_time;
		return time;
	}

	unsigned long long Timer::getTime() {
		if (running) {
			updateTime();
		}
		return time;
	}
	unsigned long long Timer::getRunning() const
	{
		return running;
	}
	long double Timer::getTimeSeconds() {
		getTime();
		return static_cast<double>(time) / 1000000000;
	}
	long double Timer::getTimeMilliseconds() {
		getTime();
		return static_cast<double>(time) / 1000000;
	}
	long double Timer::getTimeMicroseconds() {
		getTime();
		return static_cast<double>(time) / 1000;
	}
	unsigned long long Timer::getTimeNanoseconds() {
		getTime();
		return time;
	}


	SimpleTimer::SimpleTimer() {
		running = true;
	}
	SimpleTimer::~SimpleTimer() {
		printTime();
	}


	CPUCyclesTimer::CPUCyclesTimer() {
		start_time = rdtsc();

	}
	CPUCyclesTimer::~CPUCyclesTimer() {

	}
	CPUCyclesSimpleTimer::CPUCyclesSimpleTimer() {
		running = true;
	}
	CPUCyclesSimpleTimer::~CPUCyclesSimpleTimer() {
		printTime();
	}

	unsigned long long CPUCyclesTimer::getCycles() {
		return getTime();
	}


	unsigned long long CPUCyclesTimer::start() {
		running = true;
		start_time = rdtsc();
		return start_time;
	}
	unsigned long long CPUCyclesTimer::stop() {
		stop_time = rdtsc();
		updateTime();
		running = false;
		return time;
	}

	unsigned long long CPUCyclesTimer::updateTime() {
		if (running) {
			stop_time = rdtsc();
		}
		time = stop_time - start_time;
		return time;
	}

	std::ostream& operator<< (std::ostream& out, CPUCyclesTimer& timer)
	{
		out << "cycles: " << timer.getTime() << std::endl;
		return out;
	}

	void CPUCyclesTimer::printTime() {
		std::cout << "cycles: " << this->getTime() << std::endl;
	}
} //namespace BCPPUL
