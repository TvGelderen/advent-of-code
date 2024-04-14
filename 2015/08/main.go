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
    escapes := 0

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
        line := scanner.Text()
		unquoted, err := strconv.Unquote(line)
        if err != nil {
            log.Fatalf("Error unquoting string: %v", err)
        }

        baseCount += len(line)
        count += len(unquoted)

        escapes += 2
        for _, char := range line {
            switch char {
            case '"', '\\':
                escapes++
            }
        }
	}

    fmt.Printf("Part 1: %d\n", baseCount - count)
    fmt.Printf("Part 2: %d\n", escapes)

	if err = scanner.Err(); err != nil {
		log.Fatalf("Error reading from file: %v\n", err)
	}
}
