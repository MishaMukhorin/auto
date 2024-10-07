import csv

from store import MooreMachineStore, GenericTransition, MealyMachineStore


def read_mealy_csv(file) -> MealyMachineStore:
    with open(file) as f:
        reader = csv.reader(f, delimiter=';')
        machine = MealyMachineStore()
        machine.states = reader.__next__()[1:]
        for line in reader:
            signal = line[0]
            transitions = line[1:]
            machine.in_signals.append(signal)
            for transition, from_state in zip(transitions, machine.states):
                to_state, out_signal = transition.split('/')
                machine.transitions[GenericTransition(from_state, to_state, signal)] = out_signal
        return machine


def read_moore_csv(file) -> MooreMachineStore:
    with open(file) as f:
        reader = csv.reader(f, delimiter=';')
        machine = MooreMachineStore()
        out_signals = reader.__next__()[1:]
        states = reader.__next__()[1:]
        machine.states = dict(zip(states, out_signals))
        for line in reader:
            signal = line[0]
            to_states = line[1:]
            machine.in_signals.append(signal)
            for from_state, to_state in zip(machine.states, to_states):
                if to_state != '':
                    machine.transitions.add(GenericTransition(from_state, to_state, signal))
        return machine

