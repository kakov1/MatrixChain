from random import choice, randint


mtrcs_number = 10
start_test_number = int(input("Enter start test number:\n"))
tests_number = int(input("Enter tests number:\n"))
max_number = int(input("Enter max number:\n"))

for i in range(start_test_number, start_test_number + tests_number):
    with open(f"./benchmark/in/{i}test.in", "w") as test_file:
        for j in range(mtrcs_number + 1):
            test_file.write(f"{randint(1, max_number)} ")
        test_file.write("\n")
