#include "State.hh"
#include "Util.hh"
#include <magic_enum.hpp>
#include <format>

using namespace Util;

std::pair<std::string, bool> State::process(char const *msg) {
    Tokener tokener(msg);
    std::string typeToken = tokener.get().value_or("(none)");
    auto type = magic_enum::enum_cast<ActionType>(typeToken);
    if (type.has_value()) {
        switch (type.value()) {
            case ActionType::ADD_DSP:
                printf("add dsp\n");
                break;
            case ActionType::REMOVE_DSP:
                printf("remove dsp\n");
                break;
            case ActionType::ADD_DSP_DEPENDENCY:
                break;
            case ActionType::REMOVE_DSP_DEPENDENCY:
                break;
            case ActionType::HELLO:
                break;
        }
    } else {
        return {"incorrect message type", false};
    }
    return {msg, false};
}