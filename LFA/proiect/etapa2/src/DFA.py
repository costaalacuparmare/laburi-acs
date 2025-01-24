from collections.abc import Callable
from dataclasses import dataclass
from typing import TypeVar

STATE = TypeVar('STATE')


@dataclass
class DFA[STATE]:
    S: set[str]
    K: set[STATE]
    q0: STATE
    d: dict[tuple[STATE, str], STATE]
    F: set[STATE]

    def accept(self, word: str) -> bool:
        # simulate the dfa on the given word. return true if the dfa accepts
        # the word, false otherwise
        current_state = self.q0
        for char in word:
            if (current_state, char) in self.d:
                current_state = self.d.get((current_state, char))
            else:
                return False
        return current_state in self.F

    def remap_states[OTHER_STATE](self, f: Callable[[STATE], 'OTHER_STATE']) -> 'DFA[OTHER_STATE]':
        # optional, but might be useful for subset construction and the lexer to avoid state name conflicts.
        # this method generates a new dfa, with renamed state labels, while keeping the overall structure of the
        # automaton.

        # for example, given this dfa:

        # > (0) -a,b-> (1) ----a----> ((2))
        #               \-b-> (3) <-a,b-/
        #                   /     ⬉
        #                   \-a,b-/

        # applying the x -> x+2 function would create the following dfa:

        # > (2) -a,b-> (3) ----a----> ((4))
        #               \-b-> (5) <-a,b-/
        #                   /     ⬉
        #                   \-a,b-/

        # apply f function to all states
        new_K = {f(state) for state in self.K}
        new_q0 = f(self.q0)
        new_F = {f(state) for state in self.F}
        new_D = {
            (f(state), symbol): f(next_state)
            for (state, symbol), next_state in self.d.items()
        }
        return DFA(S=self.S, K=new_K, q0=new_q0, d=new_D, F=new_F)

    def minimize(self) -> 'DFA[STATE]':
        # used hopcroft's algorithm
        W = [self.F, self.K - self.F]
        P = [self.F, self.K - self.F]

        while W:
            Q = W.pop()
            for symbol in self.S:
                X = {state for state in self.K if (state, symbol) in self.d
                     and self.d[(state, symbol)] in Q}
                for R in P.copy():
                    R1 = X & R
                    R2 = R - X
                    if R1 and R2:
                        P.remove(R)
                        P.append(R1)
                        P.append(R2)
                        if R in W:
                            W.remove(R)
                            W.append(R1)
                            W.append(R2)
                        else:
                            if len(R1) <= len(R2):
                                W.append(R1)
                            else:
                                W.append(R2)
                    else:
                        P.remove(R)
                        P.append(R)

        # build new dfa using remap_state
        state_map = {state: frozenset(group) for group in P for state in group}

        # remap function
        def map_state(state: STATE) -> frozenset[STATE]:
            return state_map[state]

        return self.remap_states(map_state)
