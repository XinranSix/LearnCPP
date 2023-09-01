#include "boost/msm/front/states.hpp"
#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

struct PhoneStateMachine
    : boost::msm::front::state_machine_def<PhoneStateMachine> {
    bool angry { false };
};

struct OffHook : boost::msm::front::state<> {};

struct Connecting : boost::msm::front::state<> {
    template <typename Event, typename FSM>
    void on_entry(Event const &evt, FSM &) {
        std::cout << "We are connecting..." << std::endl;
    }

    template <typename Event, typename FSM>
    void on_exit(Event const &evt, FSM &) {
        std::cout << "We are disconnecting..." << std::endl;
    }
};

struct PhoneBeginDestroyed {
    template <typename EVT, typename FSM, typename SourceState,
              typename TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
        std::cout << "Phone breaks into a million pieces " << std::endl;
    }
};

struct CanDestoryPhone {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const &, FSM &fsm, SourceState &, TargetState &) {
        return fsm.angry;
    }
};

// struct transition_table : boost::mpl::vector<
// boost::msm::front::Row<OffHook, CallDialed, Connecting>
// > {};

int main(int argc, char *argv[]) { return 0; }
