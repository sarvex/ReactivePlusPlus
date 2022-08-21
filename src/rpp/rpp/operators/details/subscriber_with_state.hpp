//                   ReactivePlusPlus library
// 
//           Copyright Aleksey Loginov 2022 - present.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           https://www.boost.org/LICENSE_1_0.txt)
// 
//  Project home: https://github.com/victimsnino/ReactivePlusPlus

#pragma once

#include <rpp/observers/state_observer.hpp>
#include <rpp/observers/dynamic_observer.hpp>
#include <rpp/subscriptions/composite_subscription.hpp>
#include <rpp/subscribers/specific_subscriber.hpp>

namespace rpp::details
{
template<constraint::decayed_type             Type,
    typename                                  State,
    std::invocable<Type, State>               OnNext,
    std::invocable<std::exception_ptr, State> OnError,
    std::invocable<State>                     OnCompleted>
auto create_subscriber_with_state(rpp::composite_subscription sub,
                                  State&&                     state,
                                  OnNext&&                    on_next,
                                  OnError&&                   on_error,
                                  OnCompleted&&               on_completed)
{
    using TObs = state_observer<Type,
                                std::decay_t<OnNext>,
                                std::decay_t<OnError>,
                                std::decay_t<OnCompleted>,
                                std::decay_t<State>>;
    return make_specific_subscriber<Type, TObs>(std::move(sub),
                                                std::forward<OnNext>(on_next),
                                                std::forward<OnError>(on_error),
                                                std::forward<OnCompleted>(on_completed),
                                                std::forward<State>(state));
}

template<constraint::decayed_type             Type,
    typename                                  State,
    std::invocable<Type, State>               OnNext,
    std::invocable<std::exception_ptr, State> OnError,
    std::invocable<State>                     OnCompleted>
auto create_subscriber_with_dynamic_state(rpp::composite_subscription sub,
                                          State&&                     state,
                                          OnNext&&                    on_next,
                                          OnError&&                   on_error,
                                          OnCompleted&&               on_completed)
{
    using TObs = dynamic_state_observer<Type, std::decay_t<State>>;
    return make_specific_subscriber<Type, TObs>(std::move(sub),
                                                std::forward<OnNext>(on_next),
                                                std::forward<OnError>(on_error),
                                                std::forward<OnCompleted>(on_completed),
                                                std::forward<State>(state));
}
} // namespace rpp::details
