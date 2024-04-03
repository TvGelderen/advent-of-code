package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
    file, err := os.Open("input.txt")
    if err != nil {
        fmt.Printf("Unable to open file: %v", err)
        panic(err)
    }
    defer file.Close()

    count := 0
    pos := 1
    basementPos := -1

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        for _, ch := range scanner.Text() {
            if ch == '(' {
                count++
            }
            if ch == ')' {
                count--
                if basementPos == -1 && count == -1 {
                    basementPos = pos    
                }
            }
            pos++
        }
    }

    fmt.Printf("Part 1: %v\n", count)
    fmt.Printf("Part 2: %v\n", basementPos)

    if err = scanner.Err(); err != nil {
        fmt.Printf("Error reading from file: %v", err)
    }
}
