package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatalf("Unable to open file: %v", err)
	}

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
        sum := 0
        vals := strings.FieldsFunc(scanner.Text(), split)

        for _, val := range vals {
            if n, err := strconv.Atoi(val); err == nil {
                sum += n
            }
        }
        
        fmt.Println(sum)
	}

	if err = scanner.Err(); err != nil {
		log.Fatalf("Error reading from file: %v\n", err)
	}
}

func split(r rune) bool {
    switch r {
    case '{', '}', '[', ']', ':', ',':
        return true
    default:
        return false
    }
} 
