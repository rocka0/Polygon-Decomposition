from rich.console import Console
from os import system

console = Console()

T = 1000

system("g++ -std=c++17 src/app.cpp -o app")

for t in range(1, T + 1):
    system("python3 scripts/gen.py > input.txt")

    with console.status(f"[bold pink]Running Test Case [bold blue]{t}") as status:
        ret = system("./app < input.txt")

    if ret != 0:
        console.log(f"[bold red]ERR[/]: Test Case [bold blue]{t}")
        system("rm ./app")
        exit(0)
    else:
        console.log(f"[bold green]AC[/]: Test Case [bold blue]{t}")

    T -= 1

system("rm ./app input.txt after.txt before.txt")
