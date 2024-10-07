import csv
import graphviz
from collections import defaultdict
import itertools


class GenericTransition:
    def __init__(self, from_state, to_state, activator):
        self.from_state = from_state
        self.to_state = to_state
        self.signal = activator

    def __hash__(self):
        return hash((self.from_state, self.to_state, self.signal))

    def __eq__(self, other):
        return (self.from_state, self.to_state, self.signal) == (other.from_state, other.to_state, other.signal)

    def __repr__(self):
        return f"T({self.from_state} -> {self.to_state} on {self.signal})"


class MealyMachineStore:
    def __init__(self):
        self.in_signals: [str] = []
        self.states: [str] = []
        self.state_caches: [str] = []
        self.transitions: dict[GenericTransition, str] = dict()

    def visualize(self, output_file: str):
        dot = graphviz.Digraph(format='png')
        dot.attr(rankdir='LR')
        for state in self.states:
            dot.node(state, state)
        for tr, out_signal in self.transitions.items():
            label = f"{tr.signal}/{out_signal}"
            dot.edge(tr.from_state, tr.to_state, label=label)
        dot.render(output_file, cleanup=True)
        print(f"Mealy machine visualization saved to {output_file}.png")

    def write_csv(self, file):
        with open(file, 'w', newline='') as f:
            writer = csv.writer(f, delimiter=';')
            ordered_activators = sorted(self.in_signals)
            indexed_activators = dict(zip(ordered_activators, range(len(ordered_activators))))
            ordered_states = sorted(self.states)
            indexed_states = dict(zip(ordered_states, range(len(ordered_states))))
            writer.writerow([''] + ordered_states)
            transitions_matrix = [[activator] + [""] * len(ordered_states) for activator in ordered_activators]
            for tr, out in self.transitions.items():
                transitions_matrix[indexed_activators[tr.signal]] \
                    [indexed_states[tr.from_state] + 1] = tr.to_state + '/' + out
            writer.writerows(transitions_matrix)


class MooreMachineStore:
    def __init__(self):
        self.in_signals: [str] = []
        self.states: dict[str, str] = dict()
        self.transitions: set[GenericTransition] = set()

    def visualize(self, output_file: str):
        dot = graphviz.Digraph(format='png')
        dot.attr(rankdir='LR')

        for state, out_signal in self.states.items():
            label = f"{state}/{out_signal}"
            dot.node(state, label)
        for tr in self.transitions:
            dot.edge(tr.from_state, tr.to_state, label=tr.signal)
        dot.render(output_file, cleanup=True)
        print(f"Moore machine visualization saved to {output_file}.png")

    def write_csv(self, file):
        with open(file, 'w', newline='') as f:
            writer = csv.writer(f, delimiter=';')
            ordered_activators = sorted(self.in_signals)
            indexed_activators = dict(zip(ordered_activators, range(len(ordered_activators))))
            ordered_states = sorted(self.states.keys())
            indexed_states = dict(zip(ordered_states, range(len(ordered_states))))
            ordered_outputs = [self.states[state] for state in ordered_states]
            writer.writerow([''] + ordered_outputs)
            writer.writerow([''] + ordered_states)
            transitions_matrix = [[activator] + [""] * len(ordered_states) for activator in ordered_activators]
            for tr in self.transitions:
                transitions_matrix[indexed_activators[tr.signal]] \
                    [indexed_states[tr.from_state] + 1] = tr.to_state
            writer.writerows(transitions_matrix)
