#include <chrono>

class Timer 
{
private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;

public:
    inline Timer() 
    {
        Start();
    }

    inline void Start() 
    {
        startTime = std::chrono::steady_clock::now();
    }

    inline void Finish()
    {
        using namespace std::chrono;
        endTime = steady_clock::now();
    }

    inline long GetDurationMicroseconds()
    {
        using namespace std::chrono;
        auto duration = duration_cast<microseconds>(endTime - startTime);
        return duration.count();
    }
};