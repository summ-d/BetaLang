package cli

type Command struct {
	id       string
	callback func()
	flags    []string
	args     []string
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

type Interface struct {
	commands []Command
	marker   string
}

func MakeInterface()

func (i Interface) Add(c Command) {

}

func (i Interface) Parse(args []string) {

}

func (i Interface) Match() {

}
