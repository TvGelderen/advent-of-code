package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatalf("Unable to open file: %v", err)
	}
    
    baseCount := 0
    count := 0

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line, err := strconv.Unquote(scanner.Text())
        if err != nil {
            log.Fatalf("Error unquoting string: %v", err)
        }

        baseCount += len(scanner.Text())
        count += len(line)
	}

    fmt.Printf("Part 1: %d\n", baseCount - count)

	if err = scanner.Err(); err != nil {
		log.Fatalf("Error reading from file: %v\n", err)
	}
}
