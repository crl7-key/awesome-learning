package tcp_simple_client_server_test

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"testing"
)

func TestSimpleClient(t *testing.T) {
	// connect to this socket
	conn, _ := net.Dial("tcp", "localhost:8081")
	for {
		// read in input from stdin
		reader := bufio.NewReader(os.Stdin)
		fmt.Print("Text to send: ")
		text, _ := reader.ReadString('\n')
		// send to socket
		fmt.Fprintf(conn, text+"\n")
		// listen for reply
		message, _ := bufio.NewReader(conn).ReadString('\n')
		fmt.Print("Message from server: " + message)
	}
}
