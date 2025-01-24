from .DFA import DFA

from dataclasses import dataclass
from collections.abc import Callable

EPSILON = ''  # this is how epsilon is represented by the checker in the transition function of NFAs


@dataclass
class NFA[STATE]:
    S: set[str]
    K: set[STATE]
    q0: STATE
    d: dict[tuple[STATE, str], set[STATE]]
    F: set[STATE]

    def epsilon_closure(self, state: STATE) -> set[STATE]:
        current_states = {state}
        closure = {state}

        # parse the epsilon transitions of the current state
        while current_states:
            state = current_states.pop()
            if (state, EPSILON) in self.d:
                for next_state in self.d[(state, EPSILON)]:
                    # if the next state is not already in the closure, add it
                    if next_state not in closure:
                        closure.add(next_state)
                        # add the next state to the current states to parse
                        current_states.add(next_state)

        return closure

    def subset_construction(self) -> DFA[frozenset[STATE]]:
        # convert this nfa to a dfa using the subset construction algorithm
        dfa_states = set()
        dfa_transitions = dict()
        dfa_final_states = set()

        # add sink state (if needed)
        sink_state = frozenset()
        add_sink = False

        # compute the epsilon closure of the initial state
        q0 = frozenset(self.epsilon_closure(self.q0))
        dfa_states.add(q0)
        dfa_states_all = {q0}

        # eliminate EPSILON symbol from the alphabet
        new_S = self.S.copy()
        new_S.discard(EPSILON)

        # parse the states of the nfa
        while dfa_states_all:

            current_state = dfa_states_all.pop()

            for symbol in self.S:
                # initialize the next state
                next_state = set()

                for state in current_state:
                    # parse the transitions of the current state
                    if (state, symbol) in self.d:
                        next_state.update(self.d[(state, symbol)])

                # compute the epsilon closure of the next state after
                # parsing the transitions
                for state in next_state.copy():
                    next_state.update(self.epsilon_closure(state))

                # convert the next state to a frozenset
                next_state = frozenset(next_state)

                # if the next state is empty, add it to the sink state
                if not next_state:
                    add_sink = True
                    next_state = sink_state

                # add the next state to the dfa states and prepare it for
                # parsing
                if next_state not in dfa_states:
                    dfa_states.add(next_state)
                    dfa_states_all.add(next_state)

                # add the transition to the dfa transitions
                dfa_transitions[(current_state, symbol)] = next_state

        # add sink state if needed
        if add_sink:
            dfa_states.add(sink_state)
            for symbol in new_S:
                dfa_transitions[(sink_state, symbol)] = sink_state

        # add states that contain a final state to the final states
        for state in dfa_states:
            if state & self.F:
                dfa_final_states.add(state)

        # remap function for assurance of the frozenset type
        def map_state(new_state: set[STATE]) -> frozenset[STATE]:
            return frozenset(new_state)

        return DFA(S=new_S, K=dfa_states, q0=q0, d=dfa_transitions,
                   F=dfa_final_states).remap_states(map_state)

    def remap_states[OTHER_STATE](self, f: 'Callable[[STATE], OTHER_STATE]') -> 'NFA[OTHER_STATE]':
        # optional, but may be useful for the second stage of the project. Works similarly to 'remap_states'
        # from the DFA class. See the comments there for more details.

        # apply f function to all states
        new_K = {f(state) for state in self.K}
        new_q0 = f(self.q0)
        new_F = {f(state) for state in self.F}
        new_D = {
            (f(state), symbol): {f(n_state) for n_state in next_state}
            for (state, symbol), next_state in self.d.items()
        }
        return NFA(S=self.S, K=new_K, q0=new_q0, d=new_D, F=new_F)
