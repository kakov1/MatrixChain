from random import choice, randint

benchmark_path = "./in/benchmark.in"
sizes_path = "./in/sizes.in"

mtrcs_number = int(input("Enter mtrx number:\n"))

mtrx_max_number = int(input("Enter max matrix number:\n"))
mtrx_max_size = int(input("Enter max matrix size:\n"))


def write_mtrx(x, y, file):
    file.write(f"{x} {y}\n")
    for i in range(x):
        for j in range(y):
            file.write(f"{randint(0, mtrx_max_number)} ")
        file.write("\n")


def main():
    with open(f"{sizes_path}", "w") as sizes_file:
        with open(f"{benchmark_path}", "w") as benchmark_file:
            benchmark_file.write(f"{mtrcs_number}\n")
            x, y = randint(1, mtrx_max_size), randint(1, mtrx_max_size)
            sizes_file.write(f"{x} {y} ")
            for i in range(mtrcs_number):
                if i != 0:
                    x, y = y, randint(1, mtrx_max_size)
                    sizes_file.write(f"{y} ")
                write_mtrx(x, y, benchmark_file)


if __name__ == "__main__":
    main()
