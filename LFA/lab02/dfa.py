import sys
from typing import TypeVar, Generic, Dict, Optional

StateType = TypeVar("StateType")


class DFA(Generic[StateType]):
    def __init__(self):
        self.states: set[StateType] = set()
        self.initial_state: Optional[StateType] = None
        self.accepting_states: set[StateType] = set()
        self.alphabet: set[str] = set()
        self.transitions: Dict[StateType, Dict[str, StateType]] = {}
        self.current_state: Optional[StateType] = None

    def read_dfa(self, lines: list[str]) -> None:
        section = None

        for line in lines:
            line = line.strip()
            if line.startswith('#'):
                section = line[1:]  # Get section name without '#'
                continue

            if section == "states":
                self.states.add(line)  # State labels are strings
            elif section == "initial":
                self.initial_state = line
            elif section == "accepting":
                self.accepting_states.add(line)
            elif section == "alphabet":
                self.alphabet.add(line)
            elif section == "transitions":
                src, rest = line.split(':')
                char, dst = rest.split('>')
                if src not in self.transitions:
                    self.transitions[src] = {}
                self.transitions[src][char] = dst

        self.current_state = self.initial_state

    def reset(self) -> None:
        self.current_state = self.initial_state

    def next_state(self, from_state: StateType, token: str) -> Optional[StateType]:
        if from_state in self.transitions and token in self.transitions[from_state]:
            return self.transitions[from_state][token]
        return None

    def accept(self, word: str) -> bool:
        self.reset()
        for char in word:
            if char not in self.alphabet:
                return False  # Invalid character in the word
            next_state = self.next_state(self.current_state, char)
            if next_state is None:
                return False  # No valid transition
            self.current_state = next_state

        return self.current_state in self.accepting_states


def read_lines(file_path: str) -> list[str]:
    try:
        with open(file_path, 'r') as file:
            return file.readlines()
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        sys.exit(1)


def main() -> None:
    if len(sys.argv) != 3:
        print(f"Usage: python3 <file_path> <word>")
        sys.exit(1)

    file_path = sys.argv[1]
    word = sys.argv[2]

    lines = read_lines(file_path)

    dfa: DFA[str] = DFA()
    dfa.read_dfa(lines)

    if dfa.accept(word):
        print("The word is accepted by the DFA.")
    else:
        print("The word is not accepted by the DFA.")


if __name__ == "__main__":
    main()
