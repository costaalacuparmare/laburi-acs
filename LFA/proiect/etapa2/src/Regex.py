from .NFA import NFA

EPSILON = ''
SPECIAL_CHARS = ['(', ')', '*', '+', '?', '|', '[', ']', '\\']


class Regex:
    def thompson(self) -> NFA[int]:
        raise NotImplementedError('the thompson method of the Regex class'
                                  'should never be called')


# you should extend this class with the type constructors of regular
# expressions and overwrite the 'thompson' method with the specific nfa
# patterns. for example, parse_regex('ab').thompson()
# should return something like:

# >(0) --a--> (1) -epsilon-> (2) --b--> ((3))

# extra hint: you can implement each
# subtype of regex as a @dataclass extending Regex

class Character(Regex):
    def __init__(self, char):
        self.char = char

    def thompson(self) -> NFA[int]:
        q0, qf = 0, 1
        S = {self.char}
        transitions = {(q0, self.char): {qf}}
        return NFA(S, {q0, qf}, q0, transitions, {qf})


class Sugars(Regex):
    def __init__(self, form):
        if form == 'small':
            self.char = 'abcdefghijklmnopqrstuvwxyz'
        elif form == 'big':
            self.char = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
        elif form == 'digit':
            self.char = '0123456789'

    def thompson(self) -> NFA[int]:
        # create a regex for the first character in the range
        regx = Character(self.char[0])
        # create a union with the rest of the characters in the range
        for char in self.char[1:]:
            regx = Union(regx, Character(char))
        # return the thompson construction of the regex
        return regx.thompson()


class Concat(Regex):
    def __init__(self, regex1: Regex, regex2: Regex):
        self.regex1 = regex1
        self.regex2 = regex2

    def thompson(self) -> NFA:
        # Create NFAs for the two regexes
        nfa1 = self.regex1.thompson()
        nfa2 = self.regex2.thompson()

        # Define a remap function for nfa2 to avoid state conflicts
        def remap_function(state):
            max_state_nfa1 = max(nfa1.K)
            return state + max_state_nfa1 + 1

        # Apply remap_states to nfa2
        remapped_nfa2 = nfa2.remap_states(remap_function)

        # Combine NFAs
        K = nfa1.K.union(remapped_nfa2.K)
        S = nfa1.S.union(remapped_nfa2.S)
        transitions = {**nfa1.d, **remapped_nfa2.d}

        # Add epsilon transitions from nfa1's final states to nfa2's start state
        for final_state in nfa1.F:
            transitions[(final_state, EPSILON)] = {remapped_nfa2.q0}

        q0 = nfa1.q0
        F = remapped_nfa2.F

        return NFA(S, K, q0, transitions, F)


class Union(Regex):
    def __init__(self, regex1, regex2):
        self.regex1 = regex1
        self.regex2 = regex2

    def thompson(self) -> NFA[int]:
        nfa1 = self.regex1.thompson()
        nfa2 = self.regex2.thompson()

        # Define a remap function for nfa2 to avoid state conflicts
        def remap_function(state):
            max_state_nfa1 = max(nfa1.K)
            return state + max_state_nfa1 + 1

        # Apply remap_states to nfa2
        remapped_nfa2 = nfa2.remap_states(remap_function)

        # Combine NFAs
        K = nfa1.K.union(remapped_nfa2.K)
        S = nfa1.S.union(remapped_nfa2.S)
        transitions = {**nfa1.d, **remapped_nfa2.d}

        # Create new start and final states
        q0 = max(K) + 1
        qf = max(K) + 2

        # Add epsilon transitions from new start to nfa1 and nfa2 start states
        transitions[(q0, EPSILON)] = {nfa1.q0, remapped_nfa2.q0}

        # Add epsilon transitions from nfa1 and nfa2 final states to new final
        for final_state in nfa1.F:
            transitions[(final_state, EPSILON)] = {qf}

        for final_state in remapped_nfa2.F:
            transitions[(final_state, EPSILON)] = {qf}

        K = K.union({q0, qf})

        # Return the new NFA
        return NFA(S, K, q0, transitions, {qf})


class Star(Regex):
    def __init__(self, regx):
        self.regex = regx

    def thompson(self) -> NFA[int]:
        inner_nfa = self.regex.thompson()

        # Create new start and final states
        q0 = max(inner_nfa.K) + 1
        qf = max(inner_nfa.K) + 2

        # Add epsilon character to the alphabet and new start and final states
        S = inner_nfa.S.union({EPSILON})
        K = inner_nfa.K.union({q0, qf})

        # Add epsilon transitions from new start to final state and nfa start
        transitions = inner_nfa.d.copy()
        transitions[(q0, EPSILON)] = {inner_nfa.q0, qf}

        # Add epsilon transitions from nfa final states to new final state
        for final_state in inner_nfa.F:
            transitions[(final_state, EPSILON)] = {inner_nfa.q0, qf}

        return NFA(S, K, q0, transitions, {qf})


class Plus(Regex):
    def __init__(self, regx):
        self.regex = regx

    def thompson(self) -> NFA[int]:
        nfa = self.regex.thompson()

        # Create new start and final states
        q0 = max(nfa.K) + 1
        qf = max(nfa.K) + 2

        # Add new start and final states to the NFA
        K = nfa.K.union({q0, qf})

        # Add epsilon transitions from final states to new final state
        transitions = nfa.d.copy()
        for final_state in nfa.F:
            transitions[(final_state, EPSILON)] = {nfa.q0, qf}

        # Add epsilon transitions from nfa final states to nfa start state
        transitions[(q0, EPSILON)] = {nfa.q0}

        return NFA(nfa.S, K, q0, transitions, {qf})


class Optional(Regex):
    def __init__(self, regx):
        self.regex = regx

    def thompson(self) -> NFA[int]:
        inner_nfa = self.regex.thompson()

        # Create new start and final states
        q0 = max(inner_nfa.K) + 1
        qf = max(inner_nfa.K) + 2

        # Add new start and final states to the NFA
        K = inner_nfa.K.union({q0, qf})

        # Add epsilon transitions from new start to nfa start and final states
        transitions = inner_nfa.d.copy()
        transitions[(q0, EPSILON)] = {inner_nfa.q0, qf}

        # Add epsilon transitions from nfa final states to new final state
        for final_state in inner_nfa.F:
            transitions[(final_state, EPSILON)] = {qf}

        return NFA(inner_nfa.S, K, q0, transitions, {qf})


def parse_regex(regex: str) -> Regex:
    # Stacks for elements and operations
    regex_elem, operations = [], []
    # Tracks if the last processed token was an element
    is_prev = False
    # Index to iterate over the regex string
    i = 0

    while i < len(regex):
        char = regex[i]

        # Skip whitespace
        if char == ' ':
            i += 1
            continue

        # Handle regular characters and escaped sequences
        if char not in SPECIAL_CHARS:
            # Implicit concatenation
            if is_prev:
                operations.append('.')
            is_prev = True
            regex_elem.append(Character(char))
            i += 1
        elif char == '\\':  # Handle escape character
            if i + 1 < len(regex):
                i += 1
                char = regex[i]
                # Implicit concatenation
                if is_prev:
                    operations.append('.')
                is_prev = True
                regex_elem.append(Character(char))
            i += 1
        elif char == '(':  # Handle opening parenthesis
            # Implicit concatenation
            if is_prev:
                operations.append('.')
            operations.append('(')
            is_prev = False
            i += 1
        elif char == ')':  # Handle closing parenthesis
            while operations and operations[-1] != '(':
                operation = operations.pop()
                regex1 = regex_elem.pop()
                regex2 = regex_elem.pop()
                if operation == '.':
                    regex_elem.append(Concat(regex2, regex1))
                else:
                    regex_elem.append(Union(regex2, regex1))
            # Remove the opening parenthesis
            operations.pop()
            is_prev = True
            i += 1
        elif char in {'*', '+', '?'}:  # Handle repetition operators
            regex1 = regex_elem.pop()
            if char == '*':
                regex_elem.append(Star(regex1))
            elif char == '+':
                regex_elem.append(Plus(regex1))
            elif char == '?':
                regex_elem.append(Optional(regex1))
            is_prev = True
            i += 1
        elif char == '|':  # Handle union
            while operations and operations[-1] == '.':
                operations.pop()
                regex2 = regex_elem.pop()
                regex1 = regex_elem.pop()
                regex_elem.append(Concat(regex1, regex2))
            operations.append('|')
            is_prev = False
            i += 1
        elif char == '[':  # Handle range expression
            if is_prev:
                operations.append('.')
            closing_bracket_pos = regex.find(']', i)
            if closing_bracket_pos != -1 and closing_bracket_pos > i + 2:
                range_str = regex[i + 1:closing_bracket_pos]
                if range_str == 'a-z':
                    regex_elem.append(Sugars('small'))
                elif range_str == 'A-Z':
                    regex_elem.append(Sugars('big'))
                elif range_str == '0-9':
                    regex_elem.append(Sugars('digit'))
                else:
                    raise ValueError("Error in range expression")
                i = closing_bracket_pos + 1
                is_prev = True
            else:
                raise ValueError("Error in range expression")
        else:
            raise ValueError(f"Unexpected character '{char}' in regex.")

    # Process remaining operations to complete the parse tree
    while operations:
        operation = operations.pop()
        regex2 = regex_elem.pop()
        regex1 = regex_elem.pop()
        if operation == '.':
            regex_elem.append(Concat(regex1, regex2))
        else:
            regex_elem.append(Union(regex1, regex2))

    # Return the constructed parse tree
    if len(regex_elem) != 1:
        raise ValueError("Invalid regex structure.")
    return regex_elem[0]
