package cliframework;
 
import(
	"flag"
)

type CommandScraper struct{
	count int;
	marker string;
	args []string;
	flags []string;
}

func MakeCommandScraper() CommandScraper{
	cs := CommandScraper{};
	return cs;
}

func (c CommandScraper) ReadFile(){
	
}

type CommandFramework struct{
	flags *flag.FlagSet;
	ExeFun func(cmd *CommandFramework, args []string);
}