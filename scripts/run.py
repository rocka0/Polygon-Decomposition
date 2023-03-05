from rich.console import Console
from rich.prompt import Confirm
from os import system
from collections import deque


def inputToDesmos():
    with open("input.txt", "r") as file:
        data = [x.split() for x in file.read().strip().splitlines()[1:]]
    with open("desmosInput.txt", "w") as file:
        for point in data:
            x, y = point
            file.write(f"{x}, {y}\n")
        x, y = data[0]
        file.write(f"{x}, {y}\n")
    return


def outputToDesmos():
    with open("output.txt", "r") as file:
        data = file.read().splitlines()
    data = deque(data)
    M = int(data.popleft())
    with open("desmosOutput.txt", "w") as file:
        for _ in range(M):
            N = int(data.popleft())
            file.write(f"polygon(")
            while N > 1:
                x, y = data.popleft().split()
                file.write(f"({x}, {y}), ")
                N -= 1
            x, y = data.popleft().split()
            file.write(f"({x}, {y}))\n")
    return


console = Console()

with console.status("[bold red]Generating input.txt") as status:
    system("python3 scripts/gen.py > input.txt")
    console.log("[bold blue]Input written to [italic]input.txt")

if Confirm.ask("[bold green4]Generate desmos version of input.txt?", default=False):
    with console.status("[bold red]Generating input.txt") as status:
        inputToDesmos()
        console.log("[bold green]Desmos data written to [italic]desmosInput.txt")

with console.status("[bold red]Compiling app.cpp", spinner="arc") as status:
    system("g++ -std=c++17 src/app.cpp -o app")
    console.log("[bold yellow]src/app.c compiled to [italic]./app")

with console.status("[bold red]Running ./app on input.txt", spinner="circle") as status:
    system("./app < input.txt > output.txt")
    console.log("[bold orange1]Output written to [italic]output.txt")

if Confirm.ask("[bold green4]Generate desmos version of output.txt?", default=False):
    with console.status("[bold red]Generating output.txt") as status:
        outputToDesmos()
        console.log("[bold green]Desmos data written to [italic]desmosOutput.txt")

with console.status("[bold red]Generating plots", spinner="triangle") as status:
    system("python3 scripts/plot.py")
    console.log(
        "[bold light_pink1]Plots generated into [italic]polygon.png and decompositions.png"
    )

with console.status(
    "[bold red]Cleaning up executable", spinner="bouncingBall"
) as status:
    system("rm ./app")
    console.log("[bold slate_blue1]Removed [italic]./app")
