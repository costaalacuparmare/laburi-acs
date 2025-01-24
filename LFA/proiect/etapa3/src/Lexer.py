from .Regex import parse_regex, EPSILON
from .NFA import NFA

class Lexer:
    def __init__(self, spec: list[tuple[str, str]]) -> None:
        # Initialize the NFA for all the tokens - regexes in the specification
        self.nfa = NFA(S=set(), K=set(), q0=None, d=dict(), F=set())
        self.nfa.K.add(0)
        self.nfa.q0 = 0
        # Initialize the transitions for the start state
        self.nfa.d[(0, EPSILON)] = set()

        # Initialize the token priority dictionary
        self.token_priority = {}

        # Parse the regexes and create the NFAs for each token
        for priority, (token, regx) in enumerate(spec):
            regex = parse_regex(regx)
            inner_nfa = regex.thompson()

            # Remap the states of the inner NFA
            def remap_function(new_state):
                last_state_count = len(self.nfa.K)
                return new_state + last_state_count + 1

            remapped_nfa = inner_nfa.remap_states(remap_function)

            # Add the token priority
            for state in remapped_nfa.F:
                self.token_priority[state] = (token, priority)

            # Insert the remapped NFA into the main NFA
            self.nfa.S.update(remapped_nfa.S)
            self.nfa.K.update(remapped_nfa.K)
            self.nfa.d[(0, EPSILON)].add(remapped_nfa.q0)
            self.nfa.d.update(remapped_nfa.d)
            self.nfa.F.update(remapped_nfa.F)

        # Transform the NFA to a DFA
        self.dfa = self.nfa.subset_construction()


    def lex(self, word: str) -> list[tuple[str, str]] | None:
        # Initialize the result list, the current index
        result = []
        current_idx = 0

        # Parse the word to find the longest match for each token
        while current_idx < len(word):

            # Initialize the current state
            state = self.dfa.q0

            # Initialize the token, the longest match, and the check index
            token = ""
            longest_match = ""
            check_idx = current_idx

            # Parse to find the longest match
            while check_idx < len(word):
                # Get the next state
                state = self.dfa.d.get((state, word[check_idx]))

                # If no valid transition, break out of the loop
                if state is None:
                    break

                # Increment the check index
                check_idx += 1

                # Check if the current state is a final state
                final_states = self.nfa.F.intersection(state)
                if final_states:
                    # Select the state with the lowest priority (smallest ID)
                    def get_priority(s):
                        return self.token_priority[s][1]
                    final_state = min(final_states, key=get_priority)

                    # If a longer match is found, update the longest match and the token
                    longest_match = word[current_idx:check_idx]
                    token = self.token_priority[final_state][0]

            # Get character position and line number
            char_pos = current_idx - word.rfind('\n', 0, current_idx)
            current_line = word[:current_idx].count('\n')

            # If no match is found, return error message
            if longest_match == "":
                # Character is not in the alphabet
                if word[current_idx] not in self.dfa.S:
                    return [("", f"No viable alternative at character {char_pos - 1}, line {current_line}")]
                # End of file
                if current_idx == len(word) - 1:
                    return [("", f"No viable alternative at character EOF, line {current_line}")]
                # Other cases
                else:
                    return [("", f"No viable alternative at character {char_pos}, line {current_line}")]

            # Update result list and current index and reset the dfa for the
            # next token search starting from the end of the longest match
            result.append((token, longest_match))
            current_idx += len(longest_match)

        return result