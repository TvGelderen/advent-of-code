package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
    file, err := os.Open("input.txt")
    if err != nil {
        fmt.Printf("Unable to open file: %v", err)
        panic(err)
    }
    defer file.Close()

    var sum uint64 = 0

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := scanner.Text()
        x1 := strings.IndexByte(line, 'x')
        x2 := strings.IndexByte(line[x1 + 1:], 'x') + x1 + 1

        l, err := strconv.ParseUint(line[:x1], 10, 64)
        w, err := strconv.ParseUint(line[x1 + 1:x2], 10, 64)
        h, err := strconv.ParseUint(line[x2 + 1:], 10, 64)
        if err != nil {
            fmt.Printf("Unable to parse one of the dimensions: %v", err)
        }

        side1 := l * w
        side2 := w * h
        side3 := h * l
        var slack uint64

        if side1 < side2 {
            if side1 < side3 {
                slack = side1
            } else {
                if side2 < side3 {
                    slack = side2
                } else {
                    slack = side3
                }
            }
        } else {
            if side2 < side3 {
                slack = side2
            } else {
                slack = side3
            }
        }

        sum += 2 * side1 + 2 * side2 + 2 * side3 + slack
    }

    fmt.Printf("Part 1: %v\n", sum)

    if err = scanner.Err(); err != nil {
        fmt.Printf("Error reading from file: %v", err)
    }
}
