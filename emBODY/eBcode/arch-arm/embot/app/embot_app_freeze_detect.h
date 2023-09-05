#include "embot_core.h"
#include <queue>
#include <deque>

struct FreezeData
{
    float Iq;
    float Iq_target;
    float Vq;
    float angle;
    float velocity;
    uint8_t control_mode;
};

// Implement a fixed sized queue by inheriting from STL queue
template <typename T, int MaxLen, typename Container=std::deque<T>>
class FixedQueue : public std::queue<T, Container> {
public:
    void push(const T& value) {
    if (this->size() == MaxLen) {
       this->c.pop_front();
    }
        std::queue<T, Container>::push(value);
    }
};

// Class that is used to print a fixed amount of data, when the data freezes 
// for a configurable amount of samples
class FreezeDetect{
  FreezeData num_prev;
  uint8_t repeat_count, repeat_limit, repeat_sequences;
  FixedQueue<FreezeData, 250> msg_queue;
  bool ready_to_print;
  char msg_data_string[64];
  uint32_t print_cnt;

public:
    FreezeDetect(uint8_t limit) {
        repeat_limit = limit;
        repeat_sequences = 0;
        repeat_count = 0;
        ready_to_print = false;
    }
 
    void feed(FreezeData &n) {
        
        if(ready_to_print)
        {
            if(++print_cnt % 100000 == 0)
            {
                print_cnt = 0;
                print_queue();
                ready_to_print = false;
            }
        }
        
        if(isBitwiseEqual(n.Iq, num_prev.Iq))
        {
            if(++repeat_count >= repeat_limit)
            {
                repeat_count = 0;
                ready_to_print = true;
            }
        }
        else
        {
            repeat_count = 0;
            ready_to_print = true;
        }
        
        msg_queue.push(n);
        num_prev = n;
    }
    
    bool isBitwiseEqual(float a, float b) 
    {
        const int i_a = *reinterpret_cast<int*>(&a);
        const int i_b = *reinterpret_cast<int*>(&b);
                
        return (i_a == i_b);
    }
    
    void print_queue()
    {
        while(msg_queue.size() > 0)
        {
            FreezeData tmp = msg_queue.front();
            snprintf(msg_data_string, 64, "%.3f,%.3f,%.3f,%.3f,%.3f,%u", 
                     tmp.Iq, tmp.Iq_target, tmp.Vq, tmp.angle, tmp.velocity, tmp.control_mode);
            embot::core::print(msg_data_string);
            msg_queue.pop();
        }
        snprintf(msg_data_string, 64, "---");
        embot::core::print(msg_data_string);
    }
};
