package cli

import "strings"

type Command struct {
	id       string
	callback func()
	flags    []string
	args     []string
	full     string
}

func MakeCommand(id string, flags []string, args []string) Command {
	command := Command{id: id, flags: flags, args: args, callback: nil}
	return command
}

func (c Command) SetCallback(callback func()) {
	if c.callback == nil {
		c.callback = callback
	}
}

type Array[Type any] []Type

func (a Array[Type]) ForEach(f func(Type)) {
	for _, str := range a {
		f(str)
	}
}

type Interface struct {
	commands     Array[Command]
	marker       string
	count        int
	parsedString Array[string]
}

func MakeInterface(marker string) Interface {
	inf := Interface{marker: marker, count: 0}
	return inf
}

func (i Interface) updateCount() {
	i.count += 1
}

func (i Interface) Add(c Command) {
	i.commands[i.count] = c
	i.updateCount()
}

func (i Interface) Parse(args string) {
	i.parsedString = strings.Split(args, " ")
}

func (i Interface) Match() {
	i.commands.ForEach(func(c Command) {
		i.parsedString.ForEach(func(s string) {

		})
	})
}
