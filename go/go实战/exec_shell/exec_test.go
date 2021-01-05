package exec_shell

import (
	"sync"
	"testing"
)

func TestExecShell(t *testing.T) {
	exec_shell("uname")
}

func TestExecCmd(t *testing.T) {
	wg := new(sync.WaitGroup)
	commands := []string{"echo newline >> foo.o", "echo newline >> f1.o", "echo newline >> f2.o"}
	for _, str := range commands {
		wg.Add(1)
		go exec_cmd(str, wg)
	}
	wg.Wait()
}
