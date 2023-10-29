package cliframework

import (
	"bufio"
	"flag"
	"os"
	"strings"

	"github.com/summ-d/Compiler/src/cli/linkedlist"
)

type Command struct {
	count  int
	marker string
	args   linkedlist.LinkedList[string]
	flags  linkedlist.LinkedList[string]
}

func MakeCommand() Command {
	cs := Command{}
	return cs
}

type CommandScraper struct {
	commands linkedlist.LinkedList[Command]
	lines    linkedlist.LinkedList[string]
	fileName string
}

func MakeCommandScraper(fileName string) (CommandScraper, *error) {
	file, err := os.Open(fileName)
	if err != nil {
		//TODO:
	}
	file.Close()
	return CommandScraper{fileName: fileName}, nil
}

func (cs CommandScraper) GetLines() *error {
	file, err := os.Open(cs.fileName)
	if err != nil {
		return &err
	}
	reader := bufio.NewScanner(file)

	for reader.Scan() {
		cs.lines.Append(reader.Text())
	}
	if reader.Err() != nil {
		return &err
	}
	return nil
}

func (cs CommandScraper) ParseCommands() {
	cs.lines.ForEach(func(d string) {
		substrs := strings.SplitAfter(d, " ")
		c := MakeCommand()
		for i, s := range substrs {
			if i == 0 {
				c.marker = s
			}
			if s[0] == '-' {
				c.flags.Append(s)
			}
			if s[0] == '<' {
				c.args.Append(s)
			}
		}
	})
}

type CommandFramework struct {
	flags  *flag.FlagSet
	ExeFun func(cmd *CommandFramework, args []string)
}

func MakeCommandFramework() CommandFramework {
	return CommandFramework{}
}

func (c *CommandFramework) Init(args []string) error {
	return c.flags.Parse(args)
}

func (c *CommandFramework) Called() bool {
	return c.flags.Parsed()
}

func (c *CommandFramework) ExecuteFun() {
	c.ExeFun(c, c.flags.Args())
}
