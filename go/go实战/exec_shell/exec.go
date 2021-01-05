package exec_shell

import (
	"bytes"
	"log"
	"os/exec"
	"strings"
	"sync"
)

//  exec_shell 执行shell
func exec_shell(s string) {
	cmd := exec.Command("/bin/bash", "-c", s)

	var out bytes.Buffer

	cmd.Stdout = &out

	err := cmd.Run()

	if err != nil {
		log.Fatal(err)
	}
	log.Printf("%s\n", out.String())
}

//  exec_cmd 执行cmd命令
func exec_cmd(cmd string, wg *sync.WaitGroup) {
	log.Println(cmd)
	parts := strings.Fields(cmd)

	out, err := exec.Command(parts[0], parts[1]).Output()
	if err != nil {
		log.Fatal("error occurd")
		log.Printf("%s\n", err)
	}
	log.Printf("%s\n", out)
	wg.Done()
}
