package main

import (
	"fmt"

	cli "github.com/summ-d/Compiler/src/cli/src"
)

func setup(i cli.Interface) {

	helpFlags := [1]string{"--help"}
	helpCommand := cli.MakeCommand("beta", helpFlags[:], nil)
	helpCommand.SetCallback(func() {
		fmt.Println("Help: ")
		fmt.Println("Usage: ")
		fmt.Println("")
	})
}

func main() {
	inf := cli.MakeInterface("beta")
	setup(inf)
}
