#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <iostream>

// 定义事件
struct EvStart : boost::statechart::event<EvStart> {};
struct EvStop : boost::statechart::event<EvStop> {};

// 前向声明状态
struct StStopped;
struct StRunning;

// 定义状态机
struct StopWatch : boost::statechart::state_machine<StopWatch, StStopped> {};

// 定义状态
struct StStopped : boost::statechart::simple_state<StStopped, StopWatch> {
    // 事件处理
    typedef boost::statechart::custom_reaction<EvStart> reactions;
    boost::statechart::result react(const EvStart &event) {
        std::cout << "Handle EvStart" << std::endl;
        return transit<StRunning>();
    }

    StStopped() {
        std::cout << "StStopped Enter." << std::endl;
    }

    ~StStopped() {
        std::cout << "StStopped Exit." << std::endl;
    }

};

struct StRunning : boost::statechart::simple_state<StRunning, StopWatch> {
    // 事件处理
    typedef boost::statechart::custom_reaction<EvStop> reactions;
    boost::statechart::result react(const EvStop &event) {
        std::cout << "Handle EvStop" << std::endl;
        return transit<StStopped>();
    }

    StRunning() {
        std::cout << "StRunning Enter." << std::endl;
    }

    ~StRunning() {
        std::cout << "StRunning Exit." << std::endl;
    }
};

int main() {
    StopWatch stopwatch; // 创建状态机实例
    stopwatch.initiate(); // 初始化状态机

    stopwatch.process_event(EvStart()); // 触发事件，状态转为 Running
    stopwatch.process_event(EvStop());  // 触发事件，状态转为 Stopped

    return 0;
}
