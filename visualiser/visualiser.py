import sys

from automata_io import read_mealy_csv, read_moore_csv


def main():
    if len(sys.argv) < 4:
        print("Usage: program.exe [visMoore|visMealy] input.csv output.csv")
        return

    command = sys.argv[1]
    input_file = sys.argv[2]
    output_file = sys.argv[3]
    visual_file = output_file.replace('.csv', '')

    if command == "visMealy":
        mealy_machine = read_mealy_csv(input_file)
        mealy_machine.visualize(visual_file)

    elif command == "visMoore":
        moore_machine = read_moore_csv(input_file)
        moore_machine.visualize(visual_file)

    else:
        print("Unknown command. Use either 'visMoore' or 'visMoore'.")


if __name__ == "__main__":
    main()
