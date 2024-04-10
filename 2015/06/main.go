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

    size := 1000
    grid := make([][]bool, size)
    for i := 0; i < size; i++ {
        grid[i] = make([]bool, 1000)
    }

    const (
        On = iota
        Off
        Toggle
    )

    var action int
    var start []string
    var end []string

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := strings.Split(scanner.Text(), " ")
        if line[0] == "turn" {
            if line[1] == "on" {
                action = On
            }
            if line[1] == "off" {
                action = Off
            }

            start = strings.Split(line[2], ",")
            end = strings.Split(line[4], ",")
        }
        if line[0] == "toggle" {
            action = Toggle

            start = strings.Split(line[1], ",")
            end = strings.Split(line[3], ",")
        }

        startX, err := strconv.ParseInt(start[0], 10, 16)
        startY, err := strconv.ParseInt(start[1], 10, 16)
        endX, err := strconv.ParseInt(end[0], 10, 16)
        endY, err := strconv.ParseInt(end[1], 10, 16)
        if err != nil {
            fmt.Printf("Error parsing coordinates: %v", err)
            os.Exit(1)
        }

        for x := startX; x <= endX; x++ {
            for y := startY; y <= endY; y++ {
                switch action {
                case On:
                    grid[y][x] = true
                case Off:
                    grid[y][x] = false
                case Toggle:
                    grid[y][x] = !grid[y][x]
                }
            }
        }
    }

    count := 0
    for _, row := range grid {
        for _, cell := range row {
            if cell {
                count++
            }
        }
    }

    fmt.Printf("Part 1: %d\n", count)

    if err = scanner.Err(); err != nil {
		fmt.Printf("Error reading from file: %v", err)
    }
}
