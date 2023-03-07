from rich.console import Console
from os import system

console = Console()

with console.status("[bold red]Generating input.txt") as status:
    system("python3 scripts/gen.py > input.txt")
    console.log("[bold blue]Input written to [italic]input.txt")

with console.status("[bold red]Compiling app.cpp", spinner="arc") as status:
    system("g++ -std=c++17 src/app.cpp -o app")
    console.log("[bold yellow]src/app.c compiled to [italic]./app")

with console.status("[bold red]Running ./app on input.txt", spinner="circle") as status:
    system("./app < input.txt")

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
